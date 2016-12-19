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


#include <WaspGPRS_SIM908.h>



const unsigned long GPS_SIGNAL_TIMEOUT = 120;		// Timeout for GPS fix in seconds

const char AT_GPS_POWER[]		PROGMEM = "+CGPSPWR";			//0
const char AT_GPS_RESET[]		PROGMEM = "+CGPSRST";			//1
const char AT_GPS_INFO[]		PROGMEM = "+CGPSINF";			//2
const char AT_GPS_STATUS[]		PROGMEM = "+CGPSSTATUS?";		//3
const char GPS_UNKNOW[]			PROGMEM = "Location Unknown";	//4
const char GPS_NOT_FIX[]		PROGMEM = "Location Not Fix";	//5
const char GPS_FIX_2D[]			PROGMEM = "Location 2D Fix";	//6
const char GPS_FIX_3D[]			PROGMEM = "Location 3D Fix";	//7

const char* const table_GPS[] PROGMEM = 
{
	AT_GPS_POWER,		//0
	AT_GPS_RESET,		//1
	AT_GPS_INFO,		//2
	AT_GPS_STATUS,		//3
	GPS_UNKNOW,			//4
	GPS_NOT_FIX,		//5
	GPS_FIX_2D,			//6
	GPS_FIX_3D,			//7
};




// Constructors ////////////////////////////////////////////////////////////////

WaspGPRS_SIM908::WaspGPRS_SIM908(){

}


// Private Methods /////////////////////////////////////////////////////////////



//function with four answers
uint8_t WaspGPRS_SIM908::sendCommand4(const char* theText, 
										const char* expectedAnswer1, 
										const char* expectedAnswer2, 
										const char* expectedAnswer3, 
										const char* expectedAnswer4, 
										unsigned long max_timeout, 
										int num_tries)
{	
    unsigned long timeout = 0;
	
	#if GPRS_debug_mode>0
		USB.print(F("Send command with 4 answers: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

	// try sending the command
	// wait for serial response
    timeout = millis();
    serialFlush(_socket);
    while((!serialAvailable(_socket)) && ((millis() - timeout) < max_timeout))
	{
		if (num_tries > 0)
		{
            printString("AT", _socket);
            printString(theText, _socket);
            printString("\r\n", _socket);
			num_tries--;
        }
        delay(DELAY_ON_SEND);
    }
	
    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer4, max_timeout, timeout, 0, 4);
    
	#if GPRS_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	
    return answer;
}


uint8_t WaspGPRS_SIM908::waitForData(	const char* expectedAnswer1, 
										const char* expectedAnswer2, 
										const char* expectedAnswer3, 
										const char* expectedAnswer4, 
										unsigned long max_timeout, 
										unsigned long timeout,
										int seconds, 
										int n_answers)
{
	char theCommand[100];
	
	memset(theCommand, '\0', sizeof(theCommand));

	int theLength = 0;
	int minLength;
	int maxLength;
	int it=0;
	uint8_t first=1;
	char aux;
	
	#if GPRS_debug_mode>1
		USB.print(F("Answer 1: "));
		USB.println(expectedAnswer1);
		USB.print(F("Answer 2: "));
		USB.println(expectedAnswer2);
		USB.print(F("Answer 3: "));
		USB.println(expectedAnswer3);
		USB.print(F("Answer 4: "));
		USB.println(expectedAnswer4);
	#endif
	
	// Gets the maximum length and the minimum length of the all strings
	theLength=strlen(expectedAnswer1);
	minLength=theLength;
	maxLength=theLength;
	
	if (n_answers > 1)
	{
		theLength=strlen(expectedAnswer2);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
		}	
	}
	if (n_answers > 2)
	{
		theLength=strlen(expectedAnswer3);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
		}	
	}
	if (n_answers > 3)
	{
		theLength=strlen(expectedAnswer4);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
		}	
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	
	while ((millis() - timeout) < max_timeout)
	{
		while (!serialAvailable(_socket) && ((millis() - timeout) < max_timeout))
		{
			delay(10);
			
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < timeout) timeout = millis();
		}
		
		while (serialAvailable(_socket))
		{
			if ( first == 1 )	// Gets data from serial port until 'minLength'
			{
				for (it = 0; it < minLength; it++)
				{
					theCommand[it] = serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer1: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				if ((n_answers > 1) && (minLength < maxLength))
				{
					first = 2;
				}
				else
				{
					first = 0;
				}
			}
			else if (first == 2)	// Gets data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					it=minLength;
					minLength++;
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer2: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				if (minLength >= maxLength)
				{
					first=0;
				}
			}
			else
			{
				if (serialAvailable(_socket))
				{
					for (it=0; it<maxLength; it++)
					{
						theCommand[it] = theCommand[it+1];
					}
					theCommand[it-1] = serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer3: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
			}
			
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((strcmp(expectedAnswer1, ERROR_CME) == 0) || (strcmp(expectedAnswer1, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error "));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					
					do{ // Gets the length of the data string
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code,DEC);
					#endif
				}
				return 1;
			}

			if ((strstr(theCommand, expectedAnswer2) != NULL) && (n_answers > 1))
			{
				if ((strcmp(expectedAnswer2, ERROR_CME) == 0) || (strcmp(expectedAnswer2, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 2;
			}

			if ((strstr(theCommand, expectedAnswer3) != NULL) && (n_answers > 2))
			{
				if ((strcmp(expectedAnswer3, ERROR_CME) == 0) || (strcmp(expectedAnswer3, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 3;
			}

			if ((strstr(theCommand, expectedAnswer4) != NULL) && (n_answers > 3))
			{
				if ((strcmp(expectedAnswer4, ERROR_CME) == 0) || (strcmp(expectedAnswer4, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 4;
			}
  			
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < timeout) timeout = millis();
	}
	
	return 0;
}




// Inits GPS part
/* setTimeFromGPS() - sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 *
 * It returns 1 if success, 0 otherwise
 */
int8_t WaspGPRS_SIM908::GPS_ON(){
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));	//AT_GPS_POWER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=1", str_aux1);
	sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	delay(100);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[1])));	//AT_GPS_RESET
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=0", str_aux1);
	sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	delay(100);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));	//AT_GPS_POWER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=1", str_aux1);
	return sendCommand1(buffer_GPRS, OK_RESPONSE);
}

// Stops GPS part
int8_t WaspGPRS_SIM908::GPS_OFF(){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));	//AT_GPS_POWER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=0", str_aux1);
	return sendCommand1(buffer_GPRS, OK_RESPONSE);
}

// obtain GPS data
int8_t WaspGPRS_SIM908::getGPSData(int16_t NMEA_string, int8_t parse){

	int8_t answer;
	int aux, counter;
	long previous;
	char aux_str[25];
	int8_t x;
	char* aux_ptr;
	
	serialFlush(_socket);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[2])));	//AT_GPS_POWER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "AT%s=%d\r\n", str_aux1, NMEA_string);
	printString(buffer_GPRS, _socket);
	
	previous = millis();
	answer = 0;
	counter = -2;
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
	

	buffer_GPRS[counter - 4] = '\0';
	
	if (answer == 0)
	{
		return 0;
	}
	
	
	if (parse == 1)
	{
		// Parses the NMEA string
		switch(NMEA_string)
		{
			case BASIC:
				strtok(buffer_GPRS, ",");
				strcpy(longitude,strtok(NULL, ",")); // Gets longitude
				strcpy(latitude,strtok(NULL, ",")); // Gets latitude
				altitude = atof(strtok(NULL, ",")); // Gets altitude
				strcpy(aux_str,strtok(NULL, ".")); // Gets UTC time and date
				
				date[0]=aux_str[6];
				date[1]=aux_str[7];
				date[2]=aux_str[4];
				date[3]=aux_str[5];
				date[4]=aux_str[2];
				date[5]=aux_str[3];
				date[6]='\0';
				
				UTC_time[0]=aux_str[8];
				UTC_time[1]=aux_str[9];
				UTC_time[2]=aux_str[10];
				UTC_time[3]=aux_str[11];
				UTC_time[4]=aux_str[12];
				UTC_time[5]=aux_str[13];
				UTC_time[6]='\0';
				
				strtok(NULL, ",");
				TTFF = atoi(strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
				num_sat = atoi(strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
				speedOG = atof(strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
				courseOG = atof(strtok(NULL, ",")); // Gets course
				

				
				aux = (strchr(longitude, '.') - longitude) - 5;
				EW_indicator = 'E';
				if (longitude[0] == '-')
				{
					longitude[0] = '0';
					EW_indicator = 'W';
				}
				
				if(aux > 0)
				{
					do{
						for(int8_t x = 1; x < 14; x++)
						{
							longitude[x-1] = longitude[x];
						}
						longitude[13] = '0';
						longitude[14] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for(int8_t x = 13; x >= 0; x--)
						{
							longitude[x+1] = longitude[x];
						}
						longitude[0] = '0';
						longitude[14] = '\0';
						aux++;
					}while(aux < 0);
				}
				
				if (EW_indicator == 'W')
				{
					longitude[0] = '-';
				}				
				
				NS_indicator = 'N';
				aux = (strchr(latitude, '.') - latitude) - 4;
				if (latitude[0] == '-')
				{
					latitude[0] = '0';
					NS_indicator = 'S';
				}
				
				if(aux > 0)
				{
					do{
						for(x = 1; x < 13; x++)
						{
							latitude[x-1] = latitude[x];
						}
						latitude[12] = '0';
						latitude[13] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for(x = 12; x >= 0; x--)
						{
							latitude[x+1] = latitude[x];
						}
						latitude[0] = '0';
						latitude[13] = '\0';
						aux++;
					}while(aux < 0);
				}
				
				if (NS_indicator == 'S')
				{
					latitude[0] = '-';
				}
				
				break;
			
			case GGA:
				strtok(buffer_GPRS, ",");
				strcpy(UTC_time, strtok(NULL, ",")); // Gets UTC time
				strcpy(latitude, strtok(NULL, ",")); // Gets latitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets north or south
				NS_indicator = aux_str[0];
				strcpy(longitude, strtok(NULL, ",")); // Gets longitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets east or west
				EW_indicator = aux_str[0];
				strtok(NULL, ",");
				num_sat = atoi(strtok(NULL, ","));
				HDOP = atof(strtok(NULL, ",")); // Gets HDOP
				MSL_altitude = atof(strtok(NULL, ",")); // Gets MSL altitude
				strtok(NULL, ",");
				geoid_separation = atof(strtok(NULL, ",")); // Gets geoid separation
				
				aux = (strchr(longitude, '.') - longitude) - 5;				
				if(aux > 0)
				{
					do{
						for( x = 1; x < 14; x++)
						{
							longitude[x-1] = longitude[x];
						}
						longitude[13] = '0';
						longitude[14] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for( x = 13; x >= 0; x--)
						{
							longitude[x+1] = longitude[x];
						}
						longitude[0] = '0';
						longitude[14] = '\0';
						aux++;
					}while(aux < 0);
				}

				aux = (strchr(latitude, '.') - latitude) - 4;				
				if(aux > 0)
				{
					do{
						for(x = 1; x < 13; x++)
						{
							latitude[x-1] = latitude[x];
						}
						latitude[12] = '0';
						latitude[13] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for(x = 12; x >= 0; x--)
						{
							latitude[x+1] = latitude[x];
						}
						latitude[0] = '0';
						latitude[13] = '\0';
						aux++;
					}while(aux < 0);
				}
				
				break;
			case GLL:
				strtok(buffer_GPRS, ",");
				strcpy(latitude, strtok(NULL, ",")); // Gets latitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets north or south
				NS_indicator = aux_str[0];
				strcpy(longitude, strtok(NULL, ",")); // Gets longitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets east or west
				EW_indicator = aux_str[0];
				strcpy(UTC_time, strtok(NULL, ",")); // Gets UTC time
				strtok(NULL, ",");
				strcpy(aux_str, strtok(NULL, "\r")); // Gets mode
				mode = aux_str[0];
				
				aux = (strchr(longitude, '.') - longitude) - 5;				
				if(aux > 0)
				{
					do{
						for( x = 1; x < 14; x++)
						{
							longitude[x-1] = longitude[x];
						}
						longitude[13] = '0';
						longitude[14] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for( x = 13; x >= 0; x--)
						{
							longitude[x+1] = longitude[x];
						}
						longitude[0] = '0';
						longitude[14] = '\0';
						aux++;
					}while(aux < 0);
				}

				aux = (strchr(latitude, '.') - latitude) - 4;				
				if(aux > 0)
				{
					do{
						for(x = 1; x < 13; x++)
						{
							latitude[x-1] = latitude[x];
						}
						latitude[12] = '0';
						latitude[13] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for(x = 12; x >= 0; x--)
						{
							latitude[x+1] = latitude[x];
						}
						latitude[0] = '0';
						latitude[13] = '\0';
						aux++;
					}while(aux < 0);
				}
				
				break;
			case GSA:
				aux_ptr = strchr(buffer_GPRS,',');
				aux_ptr += 1;
				manual_auto = aux_ptr[0];	// Gets manual or auto mode
				aux_ptr += 2;
				FIX_2D_3D = aux_ptr[0];	// Gets 2D or 3D fix mode	
				aux_ptr += 2;
				
				
				for (x = 0; x < 12; x++)
				{
					aux_ptr = strchr(aux_ptr,',') + 1;
					memset(aux_str, '\0', 25);
					strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);
					sat_info[0][x] = atoi(aux_str);
				}
					
				PDOP = atof(strtok(aux_ptr, ",")); // Gets PDOP
				HDOP = atof(strtok(NULL, ",")); // Gets HDOP
				VDOP = atof(strtok(NULL, ",")); // Gets VDOP
				
				break;
			case GSV:
				
				aux_ptr = strchr(buffer_GPRS,',');
				aux_ptr += 1;
				memset(aux_str, '\0', sizeof(aux_str));
				strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);
				num_sat = atoi(aux_str);
				
				aux_ptr = strchr(aux_ptr,',') + 1;	// Next value
				for (x = 0; x < num_sat; x++)
				{
					memset(aux_str, '\0', 25);
					strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);
					sat_info[0][x] = atoi(aux_str);
					aux_ptr = strchr(aux_ptr,',') + 1;
					
					memset(aux_str, '\0', 25);
					strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);
					sat_info[1][x] = atoi(aux_str);
					aux_ptr = strchr(aux_ptr,',') + 1;
					
					memset(aux_str, '\0', 25);
					strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);
					sat_info[2][x] = atoi(aux_str);
					aux_ptr = strchr(aux_ptr,',') + 1;
					
					memset(aux_str, '\0', 25);
					if (strchr(aux_ptr, ',') != NULL)
					{
						strncpy(aux_str, aux_ptr, strchr(aux_ptr, ',') - aux_ptr);	
						aux_ptr = strchr(aux_ptr,',') + 1;
					}
					else
					{
						strcpy(aux_str, aux_ptr);
					}
					
					sat_info[3][x] = atoi(aux_str);
				}
				
				break;
			case RMC:
				
				strtok(buffer_GPRS, ",");
				strcpy(UTC_time, strtok(NULL, ".")); // Gets UTC time
				strtok(NULL, ",");
				strtok(NULL, ",");
				strcpy(latitude, strtok(NULL, ",")); // Gets latitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets north or south
				NS_indicator = aux_str[0];
				strcpy(longitude, strtok(NULL, ",")); // Gets longitude
				strcpy(aux_str, strtok(NULL, ",")); // Gets east or west
				EW_indicator = aux_str[0];
				speedOG = atof(strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
				courseOG = atof(strtok(NULL, ",")); // Gets course
				strcpy(date, strtok(NULL, ",")); // Gets date time
				strtok(NULL, ",");				
				strcpy(aux_str, strtok(NULL, "\r")); // Gets mode
				mode = aux_str[0];
				
				aux = (strchr(longitude, '.') - longitude) - 5;				
				if(aux > 0)
				{
					do{
						for( x = 1; x < 14; x++)
						{
							longitude[x-1] = longitude[x];
						}
						longitude[13] = '0';
						longitude[14] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for( x = 13; x >= 0; x--)
						{
							longitude[x+1] = longitude[x];
						}
						longitude[0] = '0';
						longitude[14] = '\0';
						aux++;
					}while(aux < 0);
				}

				aux = (strchr(latitude, '.') - latitude) - 4;

				
				if(aux > 0)
				{
					do{
						for(x = 1; x < 13; x++)
						{
							latitude[x-1] = latitude[x];
						}
						latitude[12] = '0';
						latitude[13] = '\0';
						aux--;
					}while(aux > 0);
				}
				else if(aux < 0)
				{
					do{
						for(x = 12; x >= 0; x--)
						{
							latitude[x+1] = latitude[x];
						}
						latitude[0] = '0';
						latitude[13] = '\0';
						aux++;
					}while(aux < 0);
				}
				break;
			case VTG:
				
				strtok(buffer_GPRS, ",");
				courseOG = atof(strtok(NULL, ",")); // Gets course
				strtok(NULL, ","); //reference, not saved
				strtok(NULL, ","); //reference, not saved
				strtok(NULL, ","); //speed in knots, not saved
				strtok(NULL, ","); //units, not saved
				speedOG = atof(strtok(NULL, ",")); // Gets speed over ground. Unit is km/h.
				strtok(NULL, ","); //units, not saved
				strcpy(aux_str, strtok(NULL, "\r")); // Gets mode
				mode = aux_str[0];
				
				break;
			case ZDA:
				
				strtok(buffer_GPRS, ",");
				strcpy(aux_str,strtok(NULL, ".")); // Gets UTC time
				
				UTC_time[0]=aux_str[0];
				UTC_time[1]=aux_str[1];
				UTC_time[2]=aux_str[2];
				UTC_time[3]=aux_str[3];
				UTC_time[4]=aux_str[4];
				UTC_time[5]=aux_str[5];
				UTC_time[6]='\0';
				
				strtok(NULL, ","); //decimals from time, not saved
				
				strtok(NULL, ","); 		//Gets day
				date[0]=aux_str[0];
				date[1]=aux_str[1];
				strcpy(aux_str,strtok(NULL, ",")); // Gets month
				date[2]=aux_str[0];
				date[3]=aux_str[1];
				strcpy(aux_str,strtok(NULL, ",")); // Gets year
				date[4]=aux_str[2];
				date[5]=aux_str[3];
				date[6]='\0';
				break;
			default:
				break;
		}
	}
	
	return 1;	
}


/* try to connect GPS
 * 
 */
int8_t WaspGPRS_SIM908::checkGPS(){

	
	char str_aux4[17];
	char str_aux5[17];
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[3])));	//AT_GPS_STATUS
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_GPS[4])));	//GPS_UNKNOW
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_GPS[5])));	//GPS_NOT_FIX
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_GPS[6])));	//GPS_FIX_2D
	strcpy_P(str_aux5, (char*)pgm_read_word(&(table_GPS[7])));	//GPS_FIX_3D
	return sendCommand4(str_aux1, str_aux2, str_aux3, str_aux4, str_aux5, millis(), SEND_ONCE);
	
}

/* waitForGPSSignal() - check if receiver is connected to some satellite 
 * until default time out
 *
 * It checks continuously if receiver is connected to some satellite 
 * until default time out.
 * 
 *
 * It returns '1' if connected '0' if not
 */
uint8_t WaspGPRS_SIM908::waitForGPSSignal()
{
	// call function with default timeout
	return waitForGPSSignal(GPS_SIGNAL_TIMEOUT);
}	

/* waitForGPSSignal(timeout) - check if receiver is connected to some satellite 
 * until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The timeout is set as an input parameter defined in seconds
 *
 * It returns '1' if connected '0' if not
 */
uint8_t WaspGPRS_SIM908::waitForGPSSignal(long timeout)
{
	long initTime = millis();
	long time = 0;
	uint8_t status = 0;
	
	while( (status < 3) && (time < (timeout * 1000)))
	{
		status = checkGPS();
		
		delay(100);
		time = millis() - initTime;
		
		//avoid millis overflow problem
		if( millis() < initTime ) initTime = millis(); 	
	}
	
	if (status >= 3)
	{
		return 1;
	}
	
	return 0;
}	

/* setTimeFromGPS() - sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 *
 * It returns 1 if success, 0 otherwise
 */
bool WaspGPRS_SIM908::setRTCTimeFromGPS()
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
    year[0] = date[4];
    year[1] = date[5];
    year[2] = '\0';
    month[0] = date[2];
    month[1] = date[3];
    month[2] = '\0';
    day[0] = date[0];
    day[1] = date[1];
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


/* convert2Degrees ( input ) - performs the conversion from input 
 * parameters in  DD°MM.mmm’ notation to DD.dddddd° notation. 
 * 
 * Sign '+' is set for positive latitudes/longitudes (North, East)
 * Sign '-' is set for negative latitudes/longitudes (South, West)
 * 
 * parameter: 'input' is a string indicating the latitude/longitude in 
 * DDmm.mmmm' notation for latitude and DDDmm.mmmm' notation for longitude
 * parameter: 'indicator' is a char indicating 'N' for North, 'S' for South, 'E'
 * for East and 'W' for West
 * Returns: a float indicating the latitude in DD.dddddd° notation
 *  
 */
float WaspGPRS_SIM908::convert2Degrees(char* input, char indicator)
{
	// final latitude expresed in degrees
	float degrees;
	float minutes;
	
	//auxiliar variable
	char aux[10];
	
	// check if 'indicator' is a valid input
	if ( indicator!='N' && indicator!='S' && indicator!='E' && indicator!='W' )
	{
		// invalid indicator
		return 0;
	}	
	
	// get 'degrees' from input parameter
	if ( indicator=='N' || indicator=='S' )
	{
		//latitude format: DDmm.mmmm'
		aux[0]=input[0];
		aux[1]=input[1];
		aux[2]='\0';
	}
	else if( indicator=='E' || indicator=='W')
	{
		//longitude format: DDDmm.mmmm'
		aux[0]=input[0];
		aux[1]=input[1];
		aux[2]=input[2];
		aux[3]='\0';
	}
	
	// convert string to integer and add it to final float variable
	degrees=atoi(aux);
	
	// get 'minutes' from input parameter 
	if ( indicator=='N' || indicator=='S' )
	{
		//latitude format: DDmm.mmmm'
		for ( int i=0; i<7; i++ )
		{
			aux[i]=input[i+2];
		}
		aux[7]='\0';
	}
	else if( indicator=='E' || indicator=='W')
	{
		//latitude format: DDmm.mmmm'
		for ( int i=0; i<7; i++ )
		{
			aux[i]=input[i+3];
		}
		aux[7]='\0';
	}	
	
	// convert string to integer and add it to final float variable
	minutes=atof(aux);
	
	// add minutes to degrees 
	degrees=degrees+minutes/60;
	
	// add sign: '+' for North/East; '-' for South/West
	if( indicator=='S' || indicator=='W')
	{
		degrees*=-1.0;
	}
	
	return degrees;
	
}



// Preinstantiate Objects //////////////////////////////////////////////////////

WaspGPRS_SIM908 GPRS_SIM908 = WaspGPRS_SIM908();
