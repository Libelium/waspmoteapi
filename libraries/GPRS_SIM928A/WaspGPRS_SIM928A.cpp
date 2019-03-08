/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */
  

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include <WaspGPRS_SIM928A.h>



const unsigned long GPS_SIGNAL_TIMEOUT = 120;		// Timeout for GPS fix in seconds

const char GNSS_COMM_UART[]	PROGMEM = "+CGNSDBG=";			//0
const char GNSS_INFO[]			PROGMEM = "+CGNSINF";			//1
const char GNSS_STATUS[]		PROGMEM = "+CGNSCMD";			//2
const char SYNC_TIME[]			PROGMEM = "+CGNSSYN";			//3

const char* const table_GPS[] PROGMEM = 
{
	GNSS_COMM_UART,			//0
	GNSS_INFO,				//1
	GNSS_STATUS,			//2
	SYNC_TIME,				//3
};




// Constructors ////////////////////////////////////////////////////////////////

WaspGPRS_SIM928A::WaspGPRS_SIM928A(){

}


// Public Methods /////////////////////////////////////////////////////////////

/* Function: 	This function switches on the GPS engine
 * Returns 		1 if success
 * 				0 if error
*/
int8_t WaspGPRS_SIM928A::GPS_ON()
{
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));		//GNSS_COMM_UART
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1", str_aux1);
	return sendCommand1(buffer_GPRS, OK_RESPONSE);
}

/* Function: 	This function switches off the GPS engine
 * Returns 		1 if success
 * 				0 if error
*/
int8_t WaspGPRS_SIM928A::GPS_OFF()
{
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));		//GNSS_COMM_UART
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
	return sendCommand1(buffer_GPRS, OK_RESPONSE);
}

/* Function: 	This function reads the data from satellites
 * Parameters:	parse.	0 to return the data string in buffer_GPRS
 * 						1 to parse data and update GPS variables
 * Returns 		1 if success
 * 				-1 if timeout
 * 				-2 if error
*/
int8_t WaspGPRS_SIM928A::getGPSData(bool parse)
{

	int8_t answer;
	int aux, counter;
	long previous;
	char aux_str[25];
	int8_t x;
	char* aux_ptr;
	
	serialFlush(_socket);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[1])));		//GNSS_INFO
	snprintf(str_aux2, sizeof(str_aux2), "%s: ", str_aux1);
	answer = sendCommand2(str_aux1, str_aux2, ERROR);	
	
	if (answer == 1)
	{
		previous = millis();
		answer = 0;
		counter = 0;
		do{
			// Gets number of available bytes 
			do{
				aux = serialAvailable(_socket);
				
				//avoid millis overflow problem
				if( millis() < previous ) previous = millis(); 
				
			}while((aux == 0) && ((millis()-previous) < 3000));
			
			#if GPRS_debug_mode>0
				USB.print(F("Available bytes: "));
				USB.println(aux, DEC);
			#endif
				
			// Gets available bytes
			while (aux > 0){
				
				if (counter < 0)
				{
					// Skips first 2 bytes (\r\n)
					serialRead(_socket);
				}
				else if(counter < BUFFER_SIZE)
				{
					buffer_GPRS[counter] = serialRead(_socket);
				}
				else
				{
					serialRead(_socket);	
				}
				counter++;
				aux--;
			}
			
			buffer_GPRS[counter] = '\0';
			
			// check if the buffer_GPRS contains "OK"
			if (strstr(buffer_GPRS, "OK") != NULL)    
			{
					answer = 1;
			}
			
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis(); 
				
		}while((answer == 0) && ((millis()-previous) < 3000));
		
		
		
	}
	else if (answer == 2)
	{
		return -2;
	}
	else
	{
		return -1;
	}

	buffer_GPRS[counter - 4] = '\0';

	if (parse == 1)
	{			
		#if GPRS_debug_mode>0
			USB.println(buffer_GPRS);
		#endif
		GPS_status = atoi(strtok(buffer_GPRS, ",")); // Gets fix status
		fix_status = atoi(strtok(NULL, ",")); // Gets fix status
		strcpy(aux_str,strtok(NULL, ",")); // Gets date and time
		
		memset(date, '\0', sizeof(date));
		strncpy(date, aux_str, 8);		
		memset(UTC_time, '\0', sizeof(UTC_time));
		strncpy(UTC_time, aux_str+ 8, 6);
		
		latitude = atof(strtok(NULL, ",")); // Gets latitude
		longitude = atof(strtok(NULL, ",")); // Gets longitude
		altitude = atof(strtok(NULL, ",")); // Gets altitude
		speedOG = atof(strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
		courseOG = atof(strtok(NULL, ",")); // Gets course
		
		mode = atoi(strtok(NULL, ",")); // Gets mode
		
		HDOP = atof(strtok(NULL, ",")); // Gets HDOP
		PDOP = atof(strtok(NULL, ",")); // Gets PDOP
		VDOP = atof(strtok(NULL, ",")); // Gets VDOP
		
		sats_in_view = atoi(strtok(NULL, ",")); // Gets sats_in_view
		sats_in_use = atoi(strtok(NULL, ",")); // Gets sats_in_use
		SNR = atoi(strtok(NULL, ",")); // Gets SNR
		
		#if GPRS_debug_mode>0
			USB.print(F("GPS_status: "));
			USB.println(GPS_status, DEC);
			USB.print(F("fix_status: "));
			USB.println(fix_status, DEC);
		
			USB.print(F("Latitude (in degrees): "));
			USB.println(latitude);
			USB.print(F("Longitude (in degrees): "));
			USB.println(longitude);
			USB.print(F("Date: "));
			USB.print(date);
			USB.print(F("   UTC_time: "));
			USB.println(UTC_time);
			USB.print(F("Altitude: "));
			USB.println(altitude);
			USB.print(F("SpeedOG: "));
			USB.println(speedOG);
			USB.print(F("Course: "));
			USB.println(courseOG);

			USB.print(F("Satellites in view: "));
			USB.println(sats_in_view, DEC); 
			USB.print(F("Satellites in use: "));
			USB.println(sats_in_use, DEC);


			USB.print(F("Mode: "));
			USB.println(mode,DEC);   
			USB.print(F("SNR: "));
			USB.println(SNR,DEC);      


			USB.print("PDOP: ");
			USB.println(PDOP);
			USB.print("HDOP: ");
			USB.println(HDOP);
			USB.print("VDOP: ");
			USB.println(VDOP);
		#endif
	}
	
	return 1;	
}

/* Function: 	This function checks if the GPS position is fixed or not
 * Returns 		0 if timeout
 * 				1 if position is fixed
 * 				2 if not fixed
*/
int8_t WaspGPRS_SIM928A::checkGPS()
{
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[1])));	//GNSS_INFO
	snprintf(str_aux2, sizeof(str_aux2), "%s: 1,1", str_aux1);
	snprintf(str_aux3, sizeof(str_aux3), "%s: 1,0", str_aux1);
	return sendCommand2(str_aux1, str_aux2, str_aux3);
	
}

/* Function: 	This function checks continuously if receiver is connected to
 * 				some satellites until time out.
 * Returns 		0 if not connected
 * 				1 if connected
*/
uint8_t WaspGPRS_SIM928A::waitForGPSSignal()
{
	// call function with default timeout
	return waitForGPSSignal(GPS_SIGNAL_TIMEOUT);
}	

/* Function: 	This function checks continuously if receiver is connected to
 * 				some satellites until time out.
 * Parameters:	timeout: max time to wait in seconds
 * Returns 		0 if not connected
 * 				1 if connected
*/
uint8_t WaspGPRS_SIM928A::waitForGPSSignal(long timeout)
{
	long initTime = millis();
	long time = 0;
	uint8_t status = 0;
	
	while( (status != 1) && (time < (timeout * 1000)))
	{
		status = checkGPS();
		
		delay(100);
		time = millis() - initTime;
		
		//avoid millis overflow problem
		if( millis() < initTime ) initTime = millis(); 	
	}
	
	if (status == 1)
	{
		return 1;
	}
	
	return 0;
}	

/* Function - This function sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 * Rreturns 	1 if success
 * 				0 otherwise
 */
bool WaspGPRS_SIM928A::setRTCTimeFromGPS()
{
	char timeString[22];
	bool RTC_state = 1;
	char year[3], month[3], day[3];
	char hours[3], minutes[3], seconds[3];
	
	if (RTC.isON != 1) // Checks if the RTC is on
	{
	    RTC.ON();
		RTC_state = 0;
	}
	
	//Get Date: char date[9]; date: 20130507
    year[0] = date[2];
    year[1] = date[3];
    year[2] = '\0';
    month[0] = date[4];
    month[1] = date[5];
    month[2] = '\0';
    day[0] = date[6];
    day[1] = date[7];
	day[2] = '\0';

	
	// Calculate Day of week
	uint8_t yearInt = atoi(year);
	uint8_t monthInt = atoi(month);
	uint8_t dayInt = atoi(day);
	int dow = RTC.dow(yearInt, monthInt, dayInt);
	
	// Get time from variable char UTC_time[11]; UTC_time: 151434.000
	hours[0] = UTC_time[0];
    hours[1] = UTC_time[1];
    hours[2] = '\0';
    minutes[0] = UTC_time[2];
    minutes[1] = UTC_time[3];
    minutes[2] = '\0';
    seconds[0] = UTC_time[4];
    seconds[1] = UTC_time[5];
    seconds[2] = '\0';

	sprintf(timeString, "%s:%s:%s:%02d:%s:%s:%s%c", year, month, day, dow, hours, minutes, seconds, '\0');
	
	RTC.setTime(timeString);
	delay(100);
	RTC.getTime();
	
	if (RTC_state == 0) // Checks if the RTC is on
	{
	    RTC.OFF();
	}
	
	uint8_t hoursInt = atoi(hours);
	uint8_t minutesInt = atoi(minutes);
	
	if((RTC.year == yearInt) && (RTC.month = monthInt) && (RTC.date == dayInt) && (RTC.hour == hoursInt) && (RTC.minute == minutesInt))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspGPRS_SIM928A GPRS_SIM928A = WaspGPRS_SIM928A();
