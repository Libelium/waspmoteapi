/*
 *  Library for managing the GPS v2.0 JN3 receiver
 * 
 *  Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.1
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */
  

/******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspGPS.h"


/******************************************************************************
 * Constructors
 ******************************************************************************/

WaspGPS::WaspGPS()
{
	// by default we choose NMEA's speed for the port 
	_baudRate = 4800;  
  
	// UART1 is the microcontrolelr used for the GPS	 
	_uart=1;				

	// basic GPS configuration
	flag = 0;	
	commMode = NMEA_MODE;	// communication mode: software or hardware serial
	pwrMode = GPS_ON;		// power on the GPS
	checksum=0;
}

/******************************************************************************
 * User API
 ******************************************************************************/


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/
 
/*
 * checkSum (gpsString) - calculate the NMEA checkSum, leave out $, *, and the 
 * checkSum bytes
 *
 * returns 1 if the checksum is right, 0 if error
 *
 */
uint8_t WaspGPS::checkSum(const char* gpsString) 
{
  // clear the checksum flag
  //flag &= ~(GPS_BAD_CHECKSUM);
	flag = 0;


  // return error if there is no asterisk at the end of the string
  if (gpsString[strlen(gpsString)-3] != '*') return 0;

  char check = 0;
  // iterate over the string, XOR each byte with the total sum:
  for (int c = 1; c < strlen(gpsString) - 3; c++) {
    check = char(check ^ gpsString[c]);
  }

  // get the checksum character for the string itself
  char stringCheckSum = (gpsString[strlen(gpsString)-2] - '0') << 4 | 
						(gpsString[strlen(gpsString)-1] - '0');
 
  uint8_t result = (check == stringCheckSum);

  //if (!result) flag |= GPS_BAD_CHECKSUM;

  // return the result
  return result;
}


/* getChecksum (gpsString) - calculate the NMEA checkSum, leave out $, *, and 
 * the checkSum bytes
 *
 * returns 1 if the checksum is right, 0 if error
 *
 * credit: Tom Igoe
 */
uint8_t WaspGPS::getChecksum(const char* gpsString)
{
  char check = 0;
  // iterate over the string, XOR each byte with the total sum:
  for (int c = 1; c < strlen(gpsString) - 3; c++) 
  {
    check = char(check ^ gpsString[c]);
  }
  return check;
}

/* getChecksum(buffer) - calculate checksum for a secuence given as a parameter
 *
 * It calculates the corresponding checksum for a secuence given as a parameter
 *
 * It stores in 'checkSUM' variable the result
 */
void WaspGPS::getChecksum(uint8_t* buffer)
{
	int a=4;
	int check=0;
	uint8_t aux=0, aux2=0;
	while( (buffer[aux]!=0xB0) || (buffer[aux+1]!=0xB3) )
	{
		aux++;
	}
	buffer[aux-1]=0x00;
	buffer[aux-2]=0x00;
	aux=0;
	while( (buffer[a]!=0xB0) || (buffer[a+1]!=0xB3) )
	{
		check+=buffer[a];
		check &= 0x7FFF;
		a++;
	}
	if(check>255)
	{
		aux=check/256;
		aux2=check-(aux*256);
		checkSUM[0]=aux;
		checkSUM[1]=aux2;
	}
	else
	{
		checkSUM[0]=0x00;
		checkSUM[1]=check;
	}
}


/* setChecksum(_checksum) - set checksum to the end of inBuffer
 *
 * it sets checksum to the end of inBuffer
 */
void WaspGPS::setChecksum()
{
	checksum= getChecksum(inBuffer);
	int aux=strlen(inBuffer);
	float aux2 = checksum%16;
	if(aux2==0.0)
	{
		inBuffer[aux-1]=48;
		inBuffer[aux-2]=(checksum/16)+48;
	}
	else
	{
		inBuffer[aux-2]=(int) (checksum/16) + 48;
		aux2 = checksum/16;
		inBuffer[aux-1]= (checksum-aux2*16)+48;
		
	}
}
 



/******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

/* ON(void) - opens UART1 and powers the GPS module
 *
 * It opens UART1 and powers the GPS module
 *
 * Returns 0 if not init OK, 1 if init OK
*/
uint8_t WaspGPS::ON()
{
	// power the GPS module
	setMode(GPS_ON);
	
	// set UART's MUX and open UART
	begin();
	
	// initialize the GPS on default parameters
	return init(); 
}

/* OFF(void) - closes UART1 and powers off the GPRS module
 *
 * This function closes UART1 and powers off the GPRS module
 *
 * Returns nothing
*/
void WaspGPS::OFF()
{
	// close uart and disable UART1 multiplexer output
	close();
	
	// switch GPS off
	setMode(GPS_OFF);
}



/*
 * init (void) - initialize the GPS using grouped parameters
 *
 * When the modlue is turned ON, it sends the "PSRF150,1*3E" command.
 * If this command is present, the modlue is OK to send.
 * 
 */
uint8_t WaspGPS::init()
{
	
	char dummyBuffer[14];
	unsigned long previous = millis();
	uint8_t i = 0;
	uint8_t valid = 0;	
	
	// Look for starting sentence
	while( (!valid) && (millis()-previous)<2000)
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			dummyBuffer[0] = serialRead(_uart); 
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<12) && (millis()-previous)<2000);
				for (i=1; i<13;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[13] = '\0';
				
				#if GPS_DEBUG
				USB.print(F("dummyBuffer:"));
				USB.print(dummyBuffer);
				#endif
				
				//check if starting sentence
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer,"$PSRF150,1*3E") ) 
				{
					#if GPS_DEBUG
					USB.println(F(", INIT OK:"));
					#endif
					valid=1;
					
				}
				else 
				{
					#if GPS_DEBUG
					USB.println(F(", init Failed."));
					#endif
				}
			}
		}
		
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 	
	}
	
	return valid;
	
}

/*
 * setCommMode (uint8_t mode) - switches between communication modes
 *
 * Switches between NMEA and binary (OSP) communication modes
 * 
 */
uint8_t WaspGPS::setCommMode(uint8_t mode)
{
  switch(mode)
  {
  case OSP_MODE:
    commMode = OSP_MODE;
    char buff[20];
    sprintf(buff,"$PSRF100,0,4800,8,1,0*0F\r\n");
    serialFlush(1);
    printString(buff,1);
    delay(100);
    break;

  case NMEA_MODE:
    commMode = NMEA_MODE;
    //A0 A2 00 18 81 02 01 01 00 01 01 01 05 01 01 01 00 01 00 01 00 00 00 01 00 00 12 C0 01 65 B0 B3
    uint8_t buff2[32] ={
      0xA0,0xA2,0x00,0x18,0x81,0x02,0x01,0x01,0x00,0x01,0x01,0x01,0x05,
      0x01,0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,
      0x12,0xC0,0x01,0x65,0xB0,0xB3};
    serialFlush(1);
    for(int b=0;b<32;b++)
    {
      printByte(buff2[b],1);
    }
    break;
  }
  return 1;

}


/* getCommMode() - get the communication mode
 *
 * It gets the communication mode in use.
 */	
uint8_t WaspGPS::getCommMode(void)
{
  return commMode;
}


/*
 * setMode (void) - sets the current internal Power Mode on the GPS
 *
 * GPS has two different power modes: ON, OFF.
 *
 */
void WaspGPS::setMode(uint8_t mode)
{
	pwrMode = mode;
	pinMode(GPS_PW,OUTPUT);
	
	// set the GPS in the defined power mode
	switch (pwrMode)
	{
		case GPS_ON:	digitalWrite(GPS_PW,HIGH);
						break;

		case GPS_OFF:	digitalWrite(GPS_PW,LOW);
						break;
	}
}

/*
 * getMode (void) - answers the current internal Power Mode on the GPS
 *
 */
uint8_t WaspGPS::getMode(void)
{
	return pwrMode;
}


/* check() - get if receiver is connected to some satellite
 *
 * It gets if receiver is connected to some satellite
 *
 * It returns '1' if connected, '0' if not
 */
uint8_t WaspGPS::check()
{	
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	serialFlush(_uart);
	signalStatus=0;
	
	#if GPS_DEBUG
	USB.println(F("check"));
	#endif
	
	unsigned long previous = millis();
	// Wait here till timeout or status=connected
	while((!signalStatus) && (millis()-previous)<5000)
	{
		// Updates global status	
		signalStatus = parseRMC();
						
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 
	}
	
	if (signalStatus == 1) return 1;
	else return 0;	
	
}


/* waitForSignal() - check if receiver is connected to some satellite until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The time out is 1 minute and is defined in GPS_SIGNAL_TIMEOUT
 *
 * It returns '1' if connected, '0' if not
 */
bool WaspGPS::waitForSignal()
{
	// call function with default timeout
	return waitForSignal(GPS_SIGNAL_TIMEOUT);
}


/* waitForSignal(timeout) - check if receiver is connected to some satellite 
 * until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The timeout is set as an input parameter defined in seconds
 *
 * It returns '1' if connected, '0' if not
 */
bool WaspGPS::waitForSignal(unsigned long timeout)
{
	unsigned long initTime = millis();
	unsigned long time = 0;
	bool status = 0;
	
	while(!status && (time < timeout*1000))
	{
		status = check();
		delay(100);
		time = millis() - initTime;
		
		//avoid millis overflow problem
		if( millis() < initTime ) initTime=millis(); 	
	}
	
	#if GPS_DEBUG
	USB.print(F("status_waitforsignal="));
	USB.println(status);
	#endif
	
	return status;
}	


/*
 * getTime (void) - answers the current time on the GPS
 *
 * gets the time from the GPS and returns it in the format 
 * "175600.0000" - hhmmss.mmmm
 *
 * return time if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getTime(void)
{
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update time variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return timeGPS;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}


/*
 * getDate (void) - answers the current date on the GPS
 *
 * gets the date from the GPS and returns it in the format "180509" - ddmmyy
 *
 * return date if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getDate(void)
{
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update date variable
		while((flag != 1) && (millis()-previous)<5000)
		{
	
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return dateGPS;
		}
	}
	else
	{		
		return 0;
	}
}


/*
 * getLatitude (void) - gets the latitude from the GPS
 *
 * forces getLocation and responds the current value of the latitude 
 * variable as a string
 *
 * return latitude if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getLatitude(void)
{	
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update latitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return latitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * convert2Degrees ( input , indicator ) - performs the conversion from input 
 * parameters in  DD°MM.mmm’ notation to DD.dddddd° notation. 
 * 
 * Sign '+' is set for positive latitudes/longitudes (North, East)
 * Sign '-' is set for negative latitudes/longitudes (South, West)
 * 
 * parameter: 'input' is a string indicating the latitude/longitude in 
 * DDDmm.mmmm' notation for latitude and DDDmm.mmmm' notation for longitude
 * parameter: 'indicator' is a char indicating 'N' for North, 'S' for South, 'E'
 * for East and 'W' for West
 * Returns: a float indicating the latitude in DD.dddddd° notation
 *  
 */
float WaspGPS::convert2Degrees(char* input, char indicator)
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

/*
 * getLongitude (void) - gets the longitude the GPS
 *
 * forces getLocation and responds the current value of the longitude
 * variable as a string
 *
 * return longitude if ok, 0 if timeout or no gps signal.
 */
  // 
char* WaspGPS::getLongitude(void)
{	
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update longitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return longitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getSpeed (void) - gets the speed from the GPS
 *
 *
 * Stores the final value in the variable speed as string.
 *
 * Returns the speed in Km/h if ok, 0 if timeout or no gps signal.
 *
 */
char* WaspGPS::getSpeed(void)
{
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update speed variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return speed;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
	
}

/*
 * getAltitude (void) - gets the altitude from the GPS
 *
 * forces getLocation and responds the current value of the altitude 
 * variable (in meters) as a string
 *
 * return altitude if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getAltitude(void)
{
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update altitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return altitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getCourse (void) - gets the course from the GPS
 *
 * makes a call to the GPRMC sentence type to extract the data from the GPS, it
 * separates the data using the 'inBuffer' and 'strtok' function
 *
 * Stores the final value in the variable course as string. 
 *
 * return course if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getCourse(void)
{
	unsigned long previous=millis();
	flag = 0;
	
	// check if GPS signal
	if (signalStatus == 1)
	{
		//update course variable
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return course;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
	
}

/* getPosition() - gets the latitude, longitude, altitude, speed, course, time 
 * and date
 *
 * It gets the latitude, longitude, altitude, speed, course, time and date
 *
 * It returns '1' on success and '0' on error.
 */
int8_t WaspGPS::getPosition()
{	
	unsigned long previous=millis();
	flag = 0;
	int8_t flag2 = 0;
		
	// check if GPS signal
	if (signalStatus == 1)
	{
		// update date, time, speed, latitude, longitude and course variables
		while((flag != 1) && (millis()-previous)<5000)
		{
		
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
		
		// update altitude variable
		previous=millis();
		while((flag2 != 1) && (millis()-previous)<5000)
		{
		
			flag2 = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
				
		//if timeout, date not updated.
		if ((flag != 1) || (flag2 != 1))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		// No gps signal
		return -1;
	}		
}


/******************************************************************************
 * Serial communication functions
 ******************************************************************************/

/*
 * begin (void) - set UART1's multiplexer to GPS and open the serial port
 *
 * opens the serial port at 4800. You should be careful and
 * always add a delay of approximately 3 seconds after calling this command. 
 * Otherwise you risk that the GPS module won't be ready to accept data and your
 * commands to it wouldn't be heard
 *
 *
 * On Wasp, calling GPS.begin() means initializing the internal UART drivers
 * inside the ATMEGA1281 processor. In order to push the power consumption to
 * the minimum you should remember calling GPS.close() after working with the
 * GPS
 */
void WaspGPS::begin(void)
{
 	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
  
	// open UART
	beginSerial(_baudRate,_uart);

}

/*
 * close (void) - close the serial port
 *
 * closes the serial port and unset the UART1's multiplexer
 *
 * An example on the use of this on the code is:
 *
 *   GPS.close();
 *
 * On Wasp, calling GPS.close() means disconnecting the internal UART drivers
 * inside the ATMEGA1281 processor. This will push the power consumption to
 * the minimum, since the UART is making a massive use of resources 
 */
void WaspGPS::close()
{
	// close UART
	closeSerial(_uart);
	
	// Disable UART1's multiplexer
	Utils.setMux(MUX_TO_LOW,MUX_TO_LOW);
	
	// set reboot variable
	//reboot=COLD;
}

/* setTimeFromGPS() - sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 * It sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 * It returns nothing
 */
void WaspGPS::setTimeFromGPS()
{
	RTC.ON();
	getDate();
	getTime();
	int day, month, year, hour, minute, second = 0;
  	day		= (dateGPS[0]-'0')*10 + (dateGPS[1]-'0');
  	month 	= (dateGPS[2]-'0')*10 + (dateGPS[3]-'0');
  	year 	= (dateGPS[4]-'0')*10 + (dateGPS[5]-'0');
  	hour 	= (timeGPS[0]-'0')*10 + (timeGPS[1]-'0');
  	minute	= (timeGPS[2]-'0')*10 + (timeGPS[3]-'0');
  	second	= (timeGPS[4]-'0')*10 + (timeGPS[5]-'0');
  	RTC.setTime(year, month, day, RTC.dow(year, month, day), hour, minute, second);
}

/* parseRMC() - listen to serial port and parse the NMEA RMC sentence, 
 * updating necessary global variables.
 * 
 * return '0' if not connected yet, '-1' if no RMC sentence parsed, 
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseRMC()
{
	#if GPS_DEBUG
	USB.println(F("parseRMC"));
	#endif
		
	char* argument;	
	char dummyBuffer[7];
	uint8_t i = 0;
	bool valid = 0;	
	bool end = 0;
	
	// Look for starting NMEA RMC characters '$GPRMC'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			dummyBuffer[0] = serialRead(_uart); 
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';
				
				#if GPS_DEBUG
				USB.print(F("dummyBuffer:"));
				USB.print(dummyBuffer);
				#endif
				
				//check if RMC sentence
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer,"$GPRMC") ) 
				{
					#if GPS_DEBUG
					USB.println(F(", valid:"));
					#endif
					valid=1;
				}
				else 
				{
					#if GPS_DEBUG
					USB.println(F(", not valid:"));
					#endif
				}
			}
		}
		
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 	
	}
	
	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#if GPS_DEBUG
		USB.println(F("no GPS data"));
		#endif
		return -2;
	}
	
	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{	 
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				inBuffer[i] = serialRead(_uart);
				if (inBuffer[i] == '*' || inBuffer[i] == '$') 
				{
					// end of NMEA or new one.
					end = 1;
					inBuffer[i+1] = '\0';
				}
				i++;
			}  
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}	
		
		// Now parse the read NMEA sentence	
		// separate all the subarrays from 'inBuffer' to 'argument' pointer					
		strncpy(inBuffer2,inBuffer,strlen(inBuffer));
		inBuffer2[strlen(inBuffer)]='\0';
		
		#if GPS_DEBUG
		USB.print(F("inbuffer2:"));
		USB.println(inBuffer2);
		#endif
		
		//first of all, look if connected
		argument = strtok (inBuffer2,",");
		//strcmp returns '0' if both equal
		if(!strcmp(argument,"V") ) 
		{
			strncpy(state,argument,strlen(argument));
			state[strlen(argument)]='\0';
		}
		else
		{
			// time is set before getting possition	
			strncpy(timeGPS,argument,strlen(argument));
			timeGPS[strlen(argument)]='\0';
			
			#if GPS_DEBUG
			USB.print(F("timeGPS:"));
			USB.println(timeGPS);
			#endif
			
			// status		
			argument = strtok(NULL,",");
			strncpy(state,argument,strlen(argument));
			state[strlen(argument)]='\0';
			
			#if GPS_DEBUG
			USB.print(F("state:"));
			USB.println(state);
			#endif
		}
	
		if (state[0] == 'A') 
		{
			#if GPS_DEBUG
			USB.println(F("connected:"));
			#endif
			 //connected. keep extracting tokens.
			 // latitude		
			argument = strtok(NULL,",");
			strncpy(latitude,argument,strlen(argument));
			latitude[strlen(argument)]='\0';
			
			// North/South		
			argument = strtok(NULL,",");
			NS_indicator = argument[0];
						 
			 // Longitude		
			argument = strtok(NULL,",");
			strncpy(longitude,argument,strlen(argument));
			longitude[strlen(argument)]='\0';
			
			// East / West			
			argument = strtok(NULL,",");
			EW_indicator = argument[0];
						
			// Speed		
			argument = strtok(NULL,",");
			strncpy(speed,argument,strlen(argument));
			speed[strlen(argument)]='\0';
			
			// convert speed from knots to Km/h
			//1 Knot = 1,852 Km/h
			float speedKM = atof(speed);
			speedKM = speedKM * 1.852;
			Utils.float2String(speedKM,speed,2);
			i = strlen(speed);
			speed[i]='\0';
			
			// Course deegrees		
			argument = strtok(NULL,",");
			strncpy(course,argument,strlen(argument));
			course[strlen(argument)]='\0';
			
			// date		
			argument = strtok(NULL,",");
			strncpy(dateGPS,argument,strlen(argument));
			dateGPS[strlen(argument)]='\0';
			
			// mode		
			argument = strtok(NULL,",");
			strncpy(RMCMode,argument,strlen(argument));
			RMCMode[strlen(argument)]='\0';
			
			#if GPS_DEBUG
			USB.print(F("latitude:"));
			USB.println(latitude);
			USB.print(F("NS_indicator:"));
			USB.println(NS_indicator);
			USB.print(F("longitude:"));
			USB.println(longitude);
			USB.print(F("EW_indicator:"));
			USB.println(EW_indicator);
			USB.print(F("speed:"));
			USB.println(speed);
			USB.print(F("course:"));
			USB.println(course);
			USB.print(F("date:"));
			USB.println(dateGPS);
			#endif
						
			return 1;
		}
		else 
		{
			if (state[0] == 'V') 
			{
				#if GPS_DEBUG
				USB.println(F("not connected"));
				#endif
				// Not connected
				return 0;
			}
			
			// If state is not V and it is not connected, must be an error parsing
			return -1;
		}
	}
	else 
		{
			#if GPS_DEBUG
			USB.println(F("not RMC NEMEA"));
			#endif
			// Not RMC NMEA sentence
			valid=0;
			return -1;
		}
}


/* parseGGA() - listen to serial port and parse the NMEA GGA sentence, 
 * updating necessary global variables.
 * 
 * return '0' if not connected yet, '-1' if no GGA sentence parsed, 
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseGGA()
{
	#if GPS_DEBUG
	USB.println(F("parseGGA"));
	#endif
		
	char* argument;	
	char dummyBuffer[7];
	uint8_t i = 0;
	bool valid = 0;	
	bool end = 0;
	
	// Look for starting NMEA GGA characters '$GPGGA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			dummyBuffer[0] = serialRead(_uart); 
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5)&& (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';
				
				#if GPS_DEBUG
				USB.print(F("dummyBuffer:"));
				USB.print(dummyBuffer);
				#endif
				
				//check if GGA sentence
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer,"$GPGGA") ) 
				{
					#if GPS_DEBUG
					USB.println(F(", valid:"));
					#endif
					valid=1;
				}
				else 
				{
					#if GPS_DEBUG
					USB.println(F(", not valid:"));
					#endif
				}
			}
		}
		
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 	
	}
	
	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#if GPS_DEBUG
		USB.println(F("no GPS data"));
		#endif
		return -2;
	}
	
	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{	 
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				inBuffer[i] = serialRead(_uart);
				if (inBuffer[i] == '*' || inBuffer[i] == '$') 
				{
					// end of NMEA or new one.
					end = 1;
					inBuffer[i+1] = '\0';
				}
				i++;
			}  
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}	
		
		// Now parse the read NMEA sentence	
		// separate all the subarrays from 'inBuffer' to 'argument' pointer					
		strncpy(inBuffer2,inBuffer,strlen(inBuffer));
		inBuffer2[strlen(inBuffer)]='\0';
		
		#if GPS_DEBUG
		USB.print(F("inbuffer2:"));
		USB.println(inBuffer2);
		#endif
		
		//first of all, look if connected
		argument = strtok (inBuffer2,",");
		//strcmp returns '0' if both equal
		if(!strcmp(argument,"0") ) 
		{
			strncpy(state,argument,strlen(argument));
			state[strlen(argument)]='\0';
		}
		else
		{
			// time is set before getting possition	
			//argument = strtok(NULL,",");
			strncpy(timeGPS,argument,strlen(argument));
			timeGPS[strlen(argument)]='\0';
			
			#if GPS_DEBUG
			USB.print(F("timeGPS:"));
			USB.println(timeGPS);
			#endif

			// status or LAT?		
			argument = strtok(NULL,",");
			if(!strcmp(argument,"0") ) 
			{
				strncpy(state,argument,strlen(argument));
				state[strlen(argument)]='\0';
				
				#if GPS_DEBUG	
				USB.print(F("state:"));
				USB.println(state);
				#endif
			}
			else
			{
				#if GPS_DEBUG
				USB.println(F("connected:"));
				#endif
				 //connected. keep extracting tokens.
				 // latitude		
				strncpy(latitude,argument,strlen(argument));
				latitude[strlen(argument)]='\0';
				
				// North/South		
				argument = strtok(NULL,",");
				NS_indicator = argument[0];
								 
				 // Longitude		
				argument = strtok(NULL,",");
				strncpy(longitude,argument,strlen(argument));
				longitude[strlen(argument)]='\0';
				
				// East / West			
				argument = strtok(NULL,",");
				EW_indicator = argument[0];
								
				//position FIX
				argument = strtok(NULL,",");
				strncpy(state,argument,strlen(argument));
				state[strlen(argument)]='\0';
				
				// satellites used
				argument = strtok(NULL,",");
				strncpy(satellites,argument,strlen(argument));
				satellites[strlen(argument)]='\0';
				
				// Precision	
				argument = strtok(NULL,",");
				strncpy(accuracy,argument,strlen(argument));
				accuracy[strlen(argument)]='\0';
				
				// Altitude	
				argument = strtok(NULL,",");
				strncpy(altitude,argument,strlen(argument));
				altitude[strlen(argument)]='\0';
				
				// units of altitude, geoid separation and units, not parsed
				
				#if GPS_DEBUG			
				USB.print(F("latitude:"));
				USB.println(latitude);
				USB.print(F("NS_indicator:"));
				USB.println(NS_indicator);
				USB.print(F("longitude:"));
				USB.println(longitude);
				USB.print(F("EW_indicator:"));
				USB.println(EW_indicator);
				USB.print(F("state:"));
				USB.println(state);
				USB.print(F("satellites:"));
				USB.println(satellites);
				USB.print(F("precision:"));
				USB.println(accuracy);
				USB.print(F("Altitude:"));
				USB.println(altitude);
				#endif
							
				return 1;
			}
		}
		
		#if GPS_DEBUG
		USB.println(F("not connected"));
		#endif
		// Not connected
		return 0;
	}
	else 
		{
			#if GPS_DEBUG
			USB.println(F("not GGA NEMEA"));
			#endif
			// Not RMC NMEA sentence
			valid=0;
			return -1;
		}
}

/* parseGSA() - listen to serial port and parse the NMEA GSA sentence, 
 * updating necessary global variables.
 * 
 * return '0' if possition not fixed, '-1' if not NMEA sentence, '1' otherwise
 */
int8_t WaspGPS::parseGSA()
{
	#if GPS_DEBUG
	USB.println(F("parseGSA"));
	#endif
		
	char* argument;	
	char dummyBuffer[7];
	uint8_t i = 0;
	bool valid = 0;	
	bool end = 0;
	
	// Look for starting NMEA GSA characters '$GPGSA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			dummyBuffer[0] = serialRead(_uart); 
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';
				
				#if GPS_DEBUG
				USB.print(F("dummyBuffer:"));
				USB.print(dummyBuffer);
				#endif
				
				//check if GSA sentence
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer,"$GPGSA") ) 
				{
					#if GPS_DEBUG
					USB.println(F(", valid:"));
					#endif
					valid=1;
				}
				else 
				{
					#if GPS_DEBUG
					USB.println(F(", not valid:"));
					#endif
				}
			}
		}
		
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 	
	}
	
	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#if GPS_DEBUG
		USB.println(F("no GPS data"));
		#endif
		return -2;
	}
	
	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{	 
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				inBuffer[i] = serialRead(_uart);
				if (inBuffer[i] == '*' || inBuffer[i] == '$') 
				{
					// end of NMEA or new one.
					end = 1;
					inBuffer[i+1] = '\0';
				}
				i++;
			}  
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}	
		
		// Now parse the read NMEA sentence	
		// separate all the subarrays from 'inBuffer' to 'argument' pointer					
		strncpy(inBuffer2,inBuffer,strlen(inBuffer));
		inBuffer2[strlen(inBuffer)]='\0';
		
		#if GPS_DEBUG
		USB.print(F("inbuffer2:"));
		USB.println(inBuffer2);
		#endif
		
		// Mode 1		
		argument = strtok (inBuffer2,",");
		strncpy(GSAMode1,argument,strlen(argument));
		GSAMode1[strlen(argument)]='\0';
		
		// Mode 2
		argument = strtok(NULL,",");
		strncpy(GSAMode2,argument,strlen(argument));
		GSAMode2[strlen(argument)]='\0';
		
		if (GSAMode2[0] == '1')
		{
			// position not fixed, exit.
			#if GPS_DEBUG
			USB.println(F("Position not fixed yet"));
			#endif
			return 0;
		}
		else
		{
			// Precision Posicion	
			argument = strtok(NULL,",");
			strncpy(dummyBuffer,argument,strlen(argument));
			
			previous = millis();
			while (((strlen(argument) == 2) || (dummyBuffer[0] == '*')) && ((millis()-previous)<1000))
			{
				argument = strtok(NULL,",");
				strncpy(dummyBuffer,argument,strlen(argument));
				//avoid millis overflow problem
				if( millis() < previous ) previous=millis(); 
			}
					 	
			strncpy(PDOPAccuracy,argument,strlen(argument));
			PDOPAccuracy[strlen(argument)]='\0';
	
			// Precision horizontal	
			argument = strtok(NULL,",");
			strncpy(HDOPAccuracy,argument,strlen(argument));
			HDOPAccuracy[strlen(argument)]='\0';
			
			// Precision vertical	
			argument = strtok(NULL,"*");
			strncpy(VDOPAccuracy,argument,strlen(argument));
			VDOPAccuracy[strlen(argument)]='\0';
			
			#if GPS_DEBUG			
			USB.print(F("mode1:"));
			USB.println(GSAMode1);
			USB.print(F("mode2:"));
			USB.println(GSAMode2);
			USB.print(F("PDOP:"));
			USB.println(PDOPAccuracy);
			USB.print(F("HDOP:"));
			USB.println(HDOPAccuracy);
			USB.print(F("VDOP:"));
			USB.println(VDOPAccuracy);
			#endif
			
			return 1;
		}
	}
	else 
	{
		#if GPS_DEBUG
		USB.println(F("not GSA NEMEA"));
		#endif
		// Not RMC NMEA sentence
		valid=0;
		return -1;
	}
}

/* parseGSV() - listen to serial port and parse the NMEA GSV sentence, 
 * updating necessary global variables.
 * 
 * return '-1' if not GSV NMEA sentence, '1' if 0k, '-2' if no gps data.
 */
// 
int8_t WaspGPS::parseGSV()
{
	#if GPS_DEBUG
	USB.println(F("parseGSV"));
	#endif
		
	char* argument;	
	char dummyBuffer[7];
	uint8_t i = 0;
	bool valid = 0;	
	bool end = 0;
	
	// Look for starting NMEA GSA characters '$GPGSA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<8000)
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			dummyBuffer[0] = serialRead(_uart); 
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';
				
				#if GPS_DEBUG
				USB.print(F("dummyBuffer:"));
				USB.print(dummyBuffer);
				#endif
				
				//check if GSV sentence
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer,"$GPGSV") ) 
				{
					#if GPS_DEBUG
					USB.println(F(", valid:"));
					#endif
					valid=1;
				}
				else 
				{
					#if GPS_DEBUG
					USB.println(F(", not valid:"));
					#endif
				}
			}
		}
		
		//avoid millis overflow problem
		if( millis() < previous ) previous=millis(); 	
	}
	
	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#if GPS_DEBUG
		USB.println(F("no GPS data"));
		#endif
		return -2;
	}
	
	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{	 
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				inBuffer[i] = serialRead(_uart);
				if (inBuffer[i] == '*' || inBuffer[i] == '$') 
				{
					// end of NMEA or new one.
					end = 1;
					inBuffer[i+1] = '\0';
				}
				i++;
			}  
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}	
		
		// Now parse the read NMEA sentence	
		// separate all the subarrays from 'inBuffer' to 'argument' pointer					
		strncpy(inBuffer2,inBuffer,strlen(inBuffer));
		inBuffer2[strlen(inBuffer)]='\0';
		
		#if GPS_DEBUG
		USB.print(F("inbuffer2:"));
		USB.println(inBuffer2);
		#endif
		
		// Number of messages not saved
		argument = strtok (inBuffer2,",");
		
		// Message number not saved
		argument = strtok(NULL,",");
				
		// Satellites in view
		argument = strtok(NULL,",");
		strncpy(satellitesInView,argument,strlen(argument));
		satellitesInView[strlen(argument)]='\0';
		
		// Rest of satellite data not saved
		
		#if GPS_DEBUG
		USB.print(F("satellites in View:"));
		USB.println(satellitesInView);
		#endif
		
		return 1;
	}
	else 
	{
		#if GPS_DEBUG
		USB.println(F("not GSA NEMEA"));
		#endif
		// Not RMC NMEA sentence
		valid=0;
		return -1;
	}
}

/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspGPS GPS = WaspGPS();
