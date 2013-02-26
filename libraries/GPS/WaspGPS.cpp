/*
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.0
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles, Mikal Hart
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
	reboot=COLD;          // reboot the system or init the system the first time
	flag = ACK;			// init the flag at ACK
	commMode = GPS_NMEA;	// communication mode: software or hardware serial
	pwrMode = GPS_ON;		// power on the GPS
	clkOffset= (char*) "96000";
	timeOfWeek= (char*) "470000";
	weekNo= (char*) "1711";
	channel= (char*) "12";
	resetCfg= (char*) "1";
	coordinateLat = (char*) "41.680617"; // Zaragoza, Spain, coordinates for Libelium
	coordinateLon = (char*) "-0.886233"; // Zaragoza, Spain, coordinates for Libelium
	coordinateAl = (char*) "198"; // Zaragoza, Spain, coordinates for Libelium
	checksum=0;
}

/******************************************************************************
 * User API
 ******************************************************************************/


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/
 
 
/*
 * extractDate (void) - private function getting the Date from the GPS
 *
 * makes a call to the GPRMC sentence type to extract the date from the GPS, it
 * separates the data using 'inBuffer' and 'strtok' function
 *
 * Stores the final value in the dateGPS variable
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
void WaspGPS::extractDate(void)
{
	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;
	char* argument;
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	
	// get Date information
	serialFlush(_uart);
	previous=millis();
	while(!setCommMode(GPS_NMEA_RMC) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");
	 
	// check pattern   
	if( !strcmp(argument,"$GPRMC") ) 
	{		
		// Read previous arguments, seek the 10th
		for ( int i=0; i<9; i++)
		{	
		  argument = strtok (NULL, ",");
		}
	  
		// copy token		
		strncpy(dateGPS,argument,strlen(argument));
		dateGPS[strlen(argument)]='\0';
	}
	else
	{
		flag |=GPS_INVALID;
	}

	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000);	
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
}

/*
 * extractTime (void) - private function getting the Time from the GPS
 *
 * makes a call to the GPGGA sentence type to extract the time from the GPS, it
 * separates the data using 'inBuffer' and strtok function
 *
 * Stores the final value in the timeGPS variable
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
void WaspGPS::extractTime(void)
{
  	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;
	char* argument;
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

  	// get Time
	serialFlush(_uart);
	previous=millis();
	while(!setCommMode(GPS_NMEA_GGA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");
	
	if( !strcmp(argument,"$GPGGA") ) 
	{
	  	// 1 Read previous argument, seek the 2th
		for ( int i=0; i<1; i++)
		{	
		  argument = strtok (NULL, ",");
		}
	  
		// copy token		
		strncpy(timeGPS,argument,strlen(argument));
		timeGPS[strlen(argument)]='\0';
	}
	else
	{
		flag |= GPS_INVALID;
	}

  // return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000);	
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
}



/******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

/* ON(void) - opens UART1 and powers the GPS module
 *
 * It opens UART1 and powers the GPS module
 *
 * Returns nothing
*/
void WaspGPS::ON()
{
	// power the GPS module
	setMode(GPS_ON);
	
	// set UART's MUX and open UART
	begin();
	
	// initialize the GPS on default parameters
	init();
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
 * init (void) - initialize the GPS on default parms
 *
 * this function initializes the GPS with the default time, date, and 
 * coordinates taken from the constructor. It is possible to modify the 
 * corresponding public variables and then call init() to reconfigure the GPS 
 * with the new conditions
 *
 * The system is not answering anything, therefore it is not possible, at this
 * point to check whether the GPS is malfunctioning
 */
void WaspGPS::init()
{
	init(	coordinateLat, 
			coordinateLon, 
			coordinateAl, 
			clkOffset, 
			timeOfWeek, 
			weekNo, 
			channel, 
			resetCfg);
}

/*
 * init (void) - initialize the GPS using grouped parameters
 *
 * LLANavigationInitialization command is used to cause a restart of the 
 * receiver, and to specify the type of restart. It also initialize position 
 * (in latitude, longitude, and altitude), clock drift, GPS Time Of Week and 
 * GPS Week Number. This enables the receiver to search for the correct 
 * satellite signals at the correct signal parameters. Correct initialization 
 * parameters enable the receiver to quickly acquire signals. 
 *
 * The system is not answering anything, therefore it is not possible, at this
 * point to check whether the GPS is malfunctioning
 */
void WaspGPS::init(	const char* _coordinateLat, 
					const char* _coordinateLon, 
					const char* _coordinateAl, 
					const char* _clkOffset, 
					const char* _timeOfWeek, 
					const char* _weekNo, 
					const char* _channel, 
					const char* _resetCfg	)
{
	long previous=0;
	// set up the initial coordinates, time and date
	if(reboot)
	{
		begin();
		delay(3000); 
	}
	
	// create LLANavigationInitialization command	
	sprintf(inBuffer,"$PSRF104,%s,%s,%s,%s,%s,%s,%s,%s*00",	_coordinateLat,
															_coordinateLon,
															_coordinateAl,
															_clkOffset,
															_timeOfWeek,
															_weekNo,
															_channel,
															_resetCfg);
  
	setChecksum();
	serialFlush(_uart);
	printString(inBuffer,_uart);
	printByte('\r',_uart);
	printByte('\n',_uart);
  
	// By default, the GPS module starts using NMEA mode and this mode is 
	// changed when initializing it. 
	
	// Switch GPS mode from NMEA to Binary protocol
	previous=millis();
	while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	previous=millis();
	
	// set Message rate
	while(!setCommMode(GPS_BINARY_OFF) && (millis()-previous)<3000)
	{
		 //avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis();
	}
	serialFlush(_uart);
	reboot=HOT;
}


/* setCommMode(mode) - set the communication mode
 *
 * It sets the communication mode. There are several possibilities:
 * 	GPS_BINARY: Binary Mode
 * 	GPS_BINARY_OFF
 * 	GPS_NMEA
 * 	GPS_NMEA_GGA
 * 	GPS_NMEA_GLL
 * 	GPS_NMEA_GSA
 * 	GPS_NMEA_GSV
 * 	GPS_NMEA_RMC
 * 	GPS_NMEA_VTG
 * 
 * Transport Message format:
 *  ______________________________________________________________________________
 * |               |              |                     |           |             |
 * |  0xA01, 0xA2  |   Two-bytes  | Up to 2^10-1(<1023) | Two-bytes |  0xB0, 0xB3 |
 * |_______________|______________|_____________________|___________|_____________|
 *  Start Sequence  Payload Length       Payload          Checksum    End Sequence
 * 
 * 
 */
uint8_t WaspGPS::setCommMode(uint16_t mode)
{
	/* tempBuffer defines an example sequence in order to change from Binary to 
	 * NMEA protocol and sets message output rates and bit rate on the port. 
	 * This sequence will be changed depending on the selected mode.
	 * The example sequence consists of:
	 * 	A0A20018 - Start Sequence and Payload Length
	 * 	8102010100010001000100010001000100010001000112C00160B0B3 - Payload
	 * 	0160B0B3 - Message Checksum and End Sequence
	 */	
	uint8_t tempBuffer[32] =
	{0xA0,0xA2,0x00,0x18,0x81,0x02,0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x12,0xC0,0x01,0x60,
	0xB0,0xB3};
	
	/* tempBuffer2 defines the sequence which controls the output rate of 
	 * binary messages. In this frame, "enable/disable all messages" mode is 
	 * selected.
	 * The sequence consists of:
	 * 	A0A20008 - Start Sequence and Payload Length
	 * 	A602020000000000 - Payload
	 * 	00AAB0B3 - Message Checksum and End Sequence
	 */
	uint8_t tempBuffer2[16] =
	{0xA0,0xA2,0x00,0x08,0xA6,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,0xB0,
	0xB3};
	
	
	uint8_t byteIN[10];
	commMode = mode;
	uint8_t valid=0;
	char* argument;		
	char aux[GPS_BUFFER_SIZE]; // auxiliary buffer in order to use strtok
    
	switch(commMode)
	{
		/// GPS_BINARY /////////////////////////////////////////////////////////			
		case GPS_BINARY:
				// create command to set Binary 8N1 communication
				sprintf(inBuffer,"$PSRF100,0,%u,8,1,0*0F",_baudRate);
				serialFlush(_uart);
				printString(inBuffer,_uart);
				printByte('\r',_uart);
				printByte('\n',_uart);
				delay(10);
				//serialFlush(_uart);
				delay(10);
				if(serialAvailable(_uart))
				{
					byteIN[0]=serialRead(_uart);
					if( (byteIN[0]=='$') || 
						((byteIN[0]>'0') && (byteIN[0]<'Z'))  )
					{
						valid=0;
					}
					else valid=1;
				}
				break;
				
		/// GPS_BINARY_OFF /////////////////////////////////////////////////////			
		case GPS_BINARY_OFF:	
	  
				serialFlush(_uart);				
				for(int a=0;a<16;a++)
				{
					printByte(tempBuffer2[a],_uart);
				}
				delay(100);
				if(serialAvailable(_uart))
				{
					for(int a=0;a<10;a++)
					{
						byteIN[a]=serialRead(_uart);
					}
				}
				if(byteIN[5]==0xA6) valid=1;
				else valid=0;
		  		break;
		  
		/// GPS_NMEA    ////////////////////////////////////////////////////////		
		case GPS_NMEA:	
				
				tempBuffer[8]=0x01;
	  			tempBuffer[10]=0x01;
				tempBuffer[12]=0x01;
				tempBuffer[14]=0x01;
				tempBuffer[16]=0x01;
				tempBuffer[29]=0x65;
				for(int b=0;b<32;b++)
				{
					printByte(tempBuffer[b], _uart);
				}
				delay(10);
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPGGA") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		  		
		/// GPS_NMEA_GGA ///////////////////////////////////////////////////////				
		case GPS_NMEA_GGA:	
				
				for(int c=0;c<32;c++)
				{
					printByte(tempBuffer[c], _uart);
				}
				delay(10);
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPGGA") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		
		/// GPS_NMEA_GLL ///////////////////////////////////////////////////////				
		case GPS_NMEA_GLL:	
				
				tempBuffer[6]=0x00;
	  			tempBuffer[8]=0x01;
				for(int d=0;d<32;d++)
				{
					printByte(tempBuffer[d], _uart);
				}
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPGLL") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		  	
		/// GPS_NMEA_GSA ///////////////////////////////////////////////////////						
		case GPS_NMEA_GSA:	
	  
				tempBuffer[6]=0x00;
	  			tempBuffer[10]=0x01;
				for(int e=0;e<32;e++)
				{
					printByte(tempBuffer[e], _uart);
				}
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPGSA") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		  
		/// GPS_NMEA_GSV ///////////////////////////////////////////////////////								
		case GPS_NMEA_GSV:
	  	
				tempBuffer[6]=0x00;
	  			tempBuffer[12]=0x01;
				for(int f=0;f<32;f++)
				{
					printByte(tempBuffer[f], _uart);
				}
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 		
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPGSV") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		  
		/// GPS_NMEA_RMC ///////////////////////////////////////////////////////	
		case GPS_NMEA_RMC:	
				
				tempBuffer[6]=0x00;
	  			tempBuffer[14]=0x01;
				for(int g=0;g<32;g++)
				{
					printByte(tempBuffer[g], _uart);
				}
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPRMC") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
		 
		/// GPS_NMEA_VTG ///////////////////////////////////////////////////////		
		case GPS_NMEA_VTG:	
				
				tempBuffer[6]=0x00;
	  			tempBuffer[16]=0x01;
				for(int h=0;h<32;h++)
				{
					printByte(tempBuffer[h], _uart);
				}
				
				// Get data from GPS module. It is stored in 'inBuffer'
				getRaw(100);
				
				// use auxiliary buffer in order to use strtok 								
				strncpy(aux,inBuffer,strlen(inBuffer));
				aux[strlen(inBuffer)]='\0';
				
				// separate all the subarrays from 'inBuffer' to 'argument' pointer
				argument = strtok (aux,",");
				if( strcmp(argument,"$GPVTG") ) 
				{
					valid=0;
				}
				else valid=1;
		  		break;
  }

  return valid;
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
 * GPS has three different power modes: ON, OFF, STANDBY, we map it
 * to four different software ones: ON (ON), OFF (OFF), SLEEP (STANDBY), 
 * HIBERNATE (STANDBY). It is done this way to keep consistency with the
 * rest of the design
 *
 * The function will set up the GPS.pwrMode public variable to one of the
 * four values, but also send the serial command to the GPS module
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
 * this GPS has three different power modes: ON, OFF, STANDBY, we map it
 * to four different software ones: ON (ON), OFF (OFF), SLEEP (STANDBY), 
 * HIBERNATE (STANDBY). It is done this way to keep consistency with the
 * rest of the design
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
bool WaspGPS::check()
{	
	uint16_t currentSentences = commMode;
	bool connection=false;
	long previous=0;
	char* argument;
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
		
	serialFlush(_uart);
	while(!setCommMode(GPS_NMEA_GGA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");	
		
  	// the data is valid only if the GPGGA position 7 is 1 or bigger
	if( !strcmp(argument,"$GPGGA") ) 
	{
		// Read previous arguments, seek the 7th
		for ( int i=0; i<6; i++)
		{	
		  argument = strtok (NULL, ",");	
		}
		
		// Position Fix Indicator. '1' and '2' are valid values
		if( argument[0]=='1' || argument[0]=='2')
		{
		  connection=true;
		}
		else connection=false;
		
	}
	else connection=false;

  	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000);	
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	return connection;
}


/* waitForSignal() - check if receiver is connected to some satellite until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The time out is 4 minutes and is defined in GPS_SIGNAL_TIMEOUT
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
bool WaspGPS::waitForSignal(long timeout)
{
	long initTime = millis();
	long time = 0;
	bool status = 0;
	
	while(!status && time < timeout*1000)
	{
		status = check();
		delay(100);
		time = millis() - initTime;
		
		//avoid millis overflow problem
		if( millis() < initTime ) initTime=millis(); 	
	}
	
	return status;
}	


/*
 * getTime (void) - answers the current time on the GPS
 *
 * gets the time from the GPS and returns it in the format 
 * "065600.0000" - hhmmss.mmmm
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getTime(void)
{
	extractTime();
	return timeGPS;
}


/*
 * getDate (void) - answers the current date on the GPS
 *
 * gets the date from the GPS and returns it in the format "180509" - ddmmyy
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getDate(void)
{
	extractDate();
	return dateGPS;
}


/*
 * getLatitude (void) - gets the latitude from the GPS
 *
 * forces getLocation and responds the current value of the latitude 
 * variable (in degrees) as a string
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getLatitude(void)
{	
	flag &= ~(GPS_INVALID);
	char* argument;
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;

	// get latitude, longitude, altitude, but NOT time
	while(!setCommMode(GPS_NMEA_GGA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");    

	if( !strcmp(argument,"$GPGGA") ) 
	{
		// Read previous arguments, seek the 3th
		for ( int i=0; i<2; i++)
		{	
		  argument = strtok (NULL, ",");
		}		
		
		//copy token 
		strncpy(latitude,argument,strlen(argument));
		latitude[strlen(argument)]='\0';
		
		// read North (N) or South (S) latitude		 
		argument = strtok (NULL, ",");
		NS_indicator=argument[0];	
		
	}
	else
	{
		flag |=GPS_INVALID;
	}
	
	
	// the data is valid only if the GPGGA position 7 is 1 or bigger
	// 3 previous read arguments, now seek the 7th
	for ( int i=0; i<4; i++)
	{	
	      argument = strtok (NULL, ",");
	}
	fixValid = (argument[0] - '0');  
	if (!fixValid) flag |= GPS_INVALID;

	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

  	return latitude;
}

/*
 * convert2Degrees ( input , indicator ) - performs the conversion from input 
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
 * variable (in degrees) as a string
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getLongitude(void)
{	
	flag &= ~(GPS_INVALID);
	char* argument;

	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;

	// get latitude, longitude, altitude, but NOT time
	while(!setCommMode(GPS_NMEA_GGA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");     

	if( !strcmp(argument,"$GPGGA") ) 
	{
	  	// 1 previous read arguments, now seek the 5th
		for ( int i=0; i<4; i++)
		{	
		      argument = strtok (NULL, ",");
		}
		// copy token		
		strncpy(longitude,argument,strlen(argument));
		longitude[strlen(argument)]='\0';
				
		// read East (E) or West (W) longitude 
		argument = strtok (NULL, ",");
		EW_indicator=argument[0];		
	}
	else
	{
		flag |=GPS_INVALID;
	}
	
	// the data is valid only if the GPGGA position 7 is 1 or bigger
	// 5 previous read arguments, now seek the 7th
	for ( int i=0; i<2; i++)
	{	
	      argument = strtok (NULL, ",");
	}
	fixValid = (argument[0] - '0');  
	if (!fixValid) flag |= GPS_INVALID;

	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
		
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
  	
	return longitude;
}

/*
 * getSpeed (void) - gets the speed from the GPS
 *
 * makes a call to the GPVTG sentence type to extract the data from the GPS, it
 * separates the data using 'inBuffer' and 'strtok' function
 *
 * Stores the final value in the variable speed as string.
 * It does not update the fixValid variable to show whether the data from the
 * GPS is valid or not
 *
 * Returns the speed in Km/h
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getSpeed(void)
{
	char* argument;
  
	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	// get speed and course
	while(!setCommMode(GPS_NMEA_VTG) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");

	if( !strcmp(argument,"$GPVTG") ) 
	{
    	// 1 previous read argument, now seek the 7th
		for ( int i=0; i<6; i++)
		{	
			argument = strtok (NULL, ",");
		}
		// copy token		
		strncpy(speed,argument,strlen(argument));
		speed[strlen(argument)]='\0';	 
	}
	else
	{
		flag |=GPS_INVALID;
	}

	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF ) 
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}	
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

  return speed;
}

/*
 * getAltitude (void) - gets the altitude from the GPS
 *
 * forces getLocation and responds the current value of the altitude 
 * variable (in meters) as a string
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getAltitude(void)
{
	char* argument;
	flag &= ~(GPS_INVALID);

	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;

	// get latitude, longitude, altitude, but NOT time
	while(!setCommMode(GPS_NMEA_GGA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");
	
	if( !strcmp(argument,"$GPGGA") ) 
	{	  
	    // the data is valid only if the GPGGA position 8 is 1 or bigger
		// 1 previous read argument, now seek the 8th
		for ( int i=0; i<7; i++)
		{	
		    argument = strtok (NULL, ",");		  
		}
		fixValid = (argument[0] - '0');  
		if (!fixValid) flag |= GPS_INVALID;
		
		
	    // 8 previous read argument, now seek the 10th
		for ( int i=0; i<2; i++)
		{	
			argument = strtok (NULL, ",");
		}
		// copy token		
		strncpy(altitude,argument,strlen(argument));
		altitude[strlen(argument)]='\0';	
	}
	else
	{
		flag |=GPS_INVALID;
	}
	
	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF )
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000);
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	  
	}
	return altitude;
}


/*
 * getCourse (void) - gets the course from the GPS
 *
 * makes a call to the GPVTG sentence type to extract the data from the GPS, it
 * separates the data using the 'inBuffer' and 'strtok' function
 *
 * Stores the final value in the variable course as string. 
 * It does not update the fixValid variable to show whether the data from the 
 * GPS is valid or not
 *
 * The system could time out, it could be good to double check the GPS.flag for
 * the value GPS_TIMEOUT when not being sure about data consistency
 */
char* WaspGPS::getCourse(void)
{
	char* argument;

	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	
	// store current state to return to it later
	uint16_t currentSentences = commMode;
	long previous=0;

	// get speed and course
	while(!setCommMode(GPS_NMEA_VTG) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");

	if( !strcmp(argument,"$GPVTG") ) 
	{
	  	// 1 previous read argument, now seek the 2nd
		for ( int i=0; i<1; i++)
		{	
		      argument = strtok (NULL, ",");
		}
		// copy token		
		strncpy(course,argument,strlen(argument));
		course[strlen(argument)]='\0';
	}
	else
	{
		flag |=GPS_INVALID;
	}

	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF )
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}

	return course;
}


/*
 * getRaw (int) - gets a data string from the GPS
 *
 * store the next consisten NMEA sentence in the internal buffer inBuffer
 * if the input is 0, continue until the end of the GPS sentence or up to
 * the max buffer size (GPS_BUFFER_SIZE)
 *
 * The system could time out, it will set the GPS.flag with the
 * value GPS_TIMEOUT when the GPS is not answering after 1000 milliseconds
 *
 * It will return the string and not only update it in the inBuffer. In case
 * of error it will write GPS_TIMEOUT_em to the buffer
 */
char* WaspGPS::getRaw(int byteAmount)
{
	flag &= ~(GPS_TIMEOUT);
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	uint8_t byteGPS = 0;		// the last byte coming through the port
	int i = 0;					// count the amount of bytes read
	uint32_t timeout = 1000;	// millis to wait before declaring timeout

	if (byteAmount == 0)
	{
		byteAmount = GPS_BUFFER_SIZE;
	}
  
	// clear uart buffer
	serialFlush(_uart);	
	
	// clear 'inBuffer'
	clearBuffer();
	
	// wait until arrival of a byte
	while(!serialAvailable(_uart) && timeout > 0) 
	{
		delay(1); 
		timeout--; 
	}; 	

	if (timeout <= 0)
	{
		flag |= GPS_TIMEOUT;
		return GPS_TIMEOUT_em;
	}
	
	// read the first byte coming through the port  
	byteGPS = serialRead(_uart);	       

	while(byteGPS != '$')
	{ 
		if(serialAvailable(_uart) > 0) 
		{
			// flush incomplete sentences
			byteGPS = serialRead(_uart); 
		}
	}
	inBuffer[i]=byteGPS;  
	i++;
	while(i <= 1 || (byteGPS != '*' && byteGPS != '$' && i < byteAmount))
	{ 
		// read the GPS sentence
		if(serialAvailable(_uart) > 0)
		{
			byteGPS = serialRead(_uart);
			if (byteGPS != '*' && byteGPS != '$' && i < byteAmount) 
			{
				inBuffer[i]=byteGPS;               
			}
						             
			i++;
		}  
	}

	if (byteGPS == '\n' || i == byteAmount) inBuffer[i-1] = '\0';  
	else inBuffer[i] = '\0';
  
  return inBuffer; 
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

/* saveEphems() - save ephemeris into SD
 *
 * It saves ephemeris into SD. It creates a file named 'FILE_EPHEMERIS' and 
 * stores ephemeris into it.
 *
 * It returns 
 * 	'1' on succesful.
 * 	'0' when error on writing  
 *  '-1' when there is no SD card
 * 	'-2' when error creating file
 *  '-3' when no ephemerides are returned by GPS receiver, 
 */
int8_t WaspGPS::saveEphems()
{
	return saveEphems(FILE_EPHEMERIS);
}


/* saveEphems(filename) - save ephemeris into SD
 *
 * It saves ephemeris into SD. It creates a file named 'filename' and stores 
 * ephemeris into it.
 *
 * It returns 
 * 	'1' on succesful.
 * 	'0' when error on writing  
 *  '-1' when there is no SD card
 * 	'-2' when error creating file
 *  '-3' when no ephemerides are returned by GPS receiver, 
 */
int8_t WaspGPS::saveEphems(const char* filename)
{
	// tempBuffer creates the 'Poll Ephemeris' message
	uint8_t tempBuffer[11] ={0xA0,0xA2,0x00,0x03,0x93,0x00,0x00,0x00,0x00,0xB0,0xB3};
	uint8_t ByteIN[110];	
	uint8_t tempData[92];
	uint8_t endFile[7] ={0xAA,0xBB,0xCC,0xCC,0xBB,0xAA,0xAA};
	uint8_t counter3=0;
	uint8_t end=0;
	uint16_t interval=1000;
	long previous=millis();
	int8_t error=-3;
	
	// initialize the flags
	flag = 0;
	uint8_t aux=0; 
	
	// set SD on
	SD.ON();
	SD.flag = 0;
		
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	
	// check if the card is there or not
	if (!SD.isSD())
	{		
		return -1;
	}
	
	// if file exists -> delete it
	if (SD.isFile(filename)) SD.del(filename);
	
	// create ephemeris file
	if(!SD.create(filename))
	{
		return -2;
	}
	
	previous=millis();
	while(!setCommMode(GPS_BINARY_OFF) && (millis()-previous)<5000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	if(millis()-previous > 5000)
	{		
		return 0;
	}
	delay(100);
		
	// flush uart
	serialFlush(_uart);
	
	// Iterates asking the GPS about available ephemeris (0..32)
	for(int a=1;a<33;a++)
	{
		// set SV ID	
		tempBuffer[5]=a; 	
		
		// set checksum in command
		getChecksum(tempBuffer);
		tempBuffer[7]=checkSUM[0];
		tempBuffer[8]=checkSUM[1];
		
		// send 'Poll Ephemeris' command to GPS
		for(int b=0;b<11;b++)
		{
			printByte(tempBuffer[b],_uart);
		}
		
		// read ephemeris data and store into ByteIN
		while(end==0)
		{
			if(serialAvailable(_uart)>0)
			{
				ByteIN[counter3]=serialRead(_uart);
				counter3++;
				previous=millis();
			}
			if( (millis()-previous) > interval )
			{
				end=1;
				serialFlush(_uart);
			} 
		}
		
		// ephemeris available
		if( counter3>100 ) 
		{
			counter3=6;
			if( (ByteIN[0]!=0xA0) || (ByteIN[1]!=0xA2) ) break;
			
			while( counter3<96 )
			{
				tempData[counter3-6]=ByteIN[counter3];
				counter3++;
			}
			tempData[counter3]=0xAA;
			tempData[counter3+1]=0xAA;
			
			// write into file
			if(SD.writeSD(filename,tempData,aux*90)) 
			{
				error=1;
			}
			else 
			{
				error=0;
			}
			aux++;
		}
		counter3=0;
		end=0;
		previous=millis();
	}
	
	if (error==1) 
	{
		if(SD.writeSD(filename,endFile,aux*90)) 
		{
			error=1;
		}
	}

	return error;
}

/* loadEphems() - load ephemeris from SD to GPS receiver
 *
 * It loads ephemeris from SD to GPS receiver.
 *
 * It returns 
 * 	'1' on success
 * 	'0' on error loading ephemeris
 * 	'-1' when there is not SD card
 * 	'-2' when there is no ephemeris file
 */
int8_t WaspGPS::loadEphems()
{
	return loadEphems(FILE_EPHEMERIS);
}


/* loadEphems(filename) - load ephemeris from SD file 'filename' to GPS receiver
 *
 * It loads ephemeris from SD to GPS receiver.
 *
 * It returns 
 * 	'1' on success
 * 	'0' on error loading ephemeris
 * 	'-1' when there is not SD card
 * 	'-2' when there is no ephemeris file
 */
int8_t WaspGPS::loadEphems(const char* filename)
{
	uint8_t tempData[100];
	uint8_t answer[10];
	uint8_t endFile=0;
	uint16_t offset=0;
	uint8_t counter3=0;
	uint8_t end=0;
	uint16_t interval=1000;
	long previous=millis();
	long previous2;
	int8_t error=2;
	
	// initialize answer buffer
	memset(answer,0x00,10);
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	
	// set SD on
	SD.ON();
	SD.flag = 0;
	
	// check if the card is there or not
	if (!SD.isSD())
	{		
		return -1;
	}
	
	// flush UART
	serialFlush(_uart);
	
	/*** Disable All Binary Messages ***/
	while(!setCommMode(GPS_BINARY_OFF) && (millis()-previous)<5000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	if(millis()-previous > 5000)
	{
		return 0;
	}
	
	delay(100);
	
	// flush uart
	serialFlush(_uart);
	
	// check if file exists
	if( SD.isFile(filename) != 1 )
	{	
		// file does not exist
		return -2;
	}
	
	// get ephemeris from GPS module
	previous2=millis();
	while( !endFile && (millis()-previous2)<60000 )
	{	
		SD.catBin(filename,offset,5);			
			
		// check if there is SD error
		if(SD.flag!=0)
		{
			return 0;
		}			
		
		// if end of file exit while loop
		if( (SD.bufferBin[0]==0xAA) && 
			(SD.bufferBin[1]==0xBB) && 
			(SD.bufferBin[2]==0xCC) &&
			(SD.bufferBin[3]==0xCC) && 
			(SD.bufferBin[4]==0xBB) 	) 
		{
			endFile=1;
		}
					
		// if there is file to read keep sending commands
		if (!endFile)
		{						
			// set up ephemeris command
			tempData[0]=0xA0;
			tempData[1]=0xA2;
			tempData[2]=0x00;
			tempData[3]=0x5B;
			tempData[4]=0x95; // 0x95: set ephemeris ID
			
			// Copy first 5 already read bytes
			for(int a=0;a<5;a++) 
			{
				tempData[a+5]=SD.bufferBin[a];
			}
			offset+=5;
			SD.catBin(filename,offset,85);	
						
			// check if there is SD error
			if(SD.flag!=0)
			{
				return 0;
			}
			
			
			for(int b=10;b<95;b++)
			{
				tempData[b]=SD.bufferBin[b-10];
			}
			tempData[95]=0x00;
			tempData[96]=0x00;
			tempData[97]=0xB0;
			tempData[98]=0xB3;
			getChecksum(tempData);
			tempData[95]=checkSUM[0];
			tempData[96]=checkSUM[1];
			
			// send "Set Ephemeris" command to GPS module
			for(int c=0;c<99;c++)
			{
				printByte(tempData[c],_uart);
			}			
			delay(100);
			
			// get response to ephemeris command
			while(end==0)
			{
				if(serialAvailable(_uart)>0)
				{
					answer[counter3]=serialRead(_uart);
					counter3++;
					previous=millis();
				}
				
				// check internal timeout
				if( (millis()-previous) > interval )
				{
					end=1;
					serialFlush(_uart);
				}
				
				// avoid unlimited GPS info sending
				if (millis()-previous2 > 50000)
				{				
					// switch off GPS
					OFF();
					delay(1000);	
					
					// switch on GPS 
					ON();		
					
					// clean input buffer
					serialFlush(_uart);		
					return 0;
				}	  
				
				//avoid millis overflow problem
				if( millis()-previous < 0 ) previous=millis(); 
				
				//avoid millis overflow problem
				if( millis()-previous2 < 0 ) previous2=millis(); 
			}
			counter3=0;
			end=0;			
			
			// Check ACK from GPS module (0x0B: 'Successful ACK' ID)
			// A0A2-0002: start of the sequence and payload length
			// 0B-95 - Command Acknowledgment
			// 00A0-B0B3: Message Checksum and End Sequence
			previous=millis();
			if( (answer[0]==0xA0) && 
				(answer[1]==0xA2) && 
				(answer[2]==0x00) && 
				(answer[3]==0x02) &&
				(answer[4]==0x0B) && 
				(answer[5]==0x95) && 
				(answer[6]==0x00) &&
				(answer[7]==0xA0) && 
				(answer[8]==0xB0) && 
				(answer[9]==0xB3) ) 
			{
				// Successful answer
				error=1;
			}
			else 
			{		
				error=0;
			}
			offset+=85;
		}		
		
		//avoid millis overflow problem
		if( millis()-previous2 < 0 ) previous2=millis(); 
	}
	
	// check if time is out
	if(millis()-previous2 > 60000)
	{
		// timeout
		error=0;
	}

	return error;
	
}


/* getPosition() - gets the latitude, longitude, altitude, speed, course, time 
 * and date
 *
 * It gets the latitude, longitude, altitude, speed, course, time and date
 *
 * It returns '1' on success and '0' on error.
 */
uint8_t WaspGPS::getPosition()
{	
	flag &= ~(GPS_INVALID);
	
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
		
	uint16_t currentSentences = commMode;
	long previous=0;
	uint8_t complete = 0;
	
	uint8_t byteGPS = 0;		// the last byte coming through the port
	int i = 0;			// count the amount of bytes read
	uint32_t timeout = 1000;	// millis to wait before declaring timeout
	char* argument;
		
  	// get all NMEA sentences
	while(!setCommMode(GPS_NMEA) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	// separate all the subarrays from 'inBuffer' to 'argument' pointer
	argument = strtok (inBuffer,",");
	
	// Look for three NMEA sentences that provide all necessary information
	// These sentences are: $GPGGA, $GPRMC and $GPVTG
	previous = millis();
	while( complete<3 && (millis()-previous)<5000 )
	{	
	  
		if( !strcmp(argument,"$GPGGA") ) 
		{
			/// timeGPS
			// 1 read previous arguments, seek the 2nd	
			argument = strtok (NULL, ",");	
			// copy token		
			strncpy(timeGPS,argument,strlen(argument));
			timeGPS[strlen(argument)]='\0';
			
			/// latitude
			// 2 read previous arguments, seek the 3rd	
			argument = strtok (NULL, ",");	
			// copy token		
			strncpy(latitude,argument,strlen(argument));
			latitude[strlen(argument)]='\0';
			
			// read North (N) or South (S) latitude 
			argument = strtok (NULL, ",");
			NS_indicator=argument[0];	
			
			/// longitude
			// 4 read previous arguments, seek the 5th	
			argument = strtok (NULL, ",");
				
			// copy token		
			strncpy(longitude,argument,strlen(argument));
			longitude[strlen(argument)]='\0';
						
			// read East (E) or West (W) longitude
			argument = strtok (NULL, ",");
			EW_indicator=argument[0];	
			
			/// altitude
			// 6 read previous arguments, seek the 10th	
			for ( int i=0; i<4; i++)
			{	
			  argument = strtok (NULL, ",");
			}		
			// copy token		
			strncpy(altitude,argument,strlen(argument));
			altitude[strlen(argument)]='\0';		
	
			// increase counter
			complete++;
		}
		else if( !strcmp(argument,"$GPRMC") )
		{
		  	/// timeGPS
			// 1 read previous arguments, seek the 2nd	
			argument = strtok (NULL, ",");		
			// copy token		
			strncpy(timeGPS,argument,strlen(argument));
			timeGPS[strlen(argument)]='\0';
			
			/// dateGPS
			// 1 read previous argument, seek the 10th	
			for ( int i=0; i<8; i++)
			{	
			  argument = strtok (NULL, ",");
			}		
			// copy token		
			strncpy(dateGPS,argument,strlen(argument));
			dateGPS[strlen(argument)]='\0';
			
			// increase counter
			complete++;
		}
		else if( !strcmp(argument,"$GPVTG") )
		{		  		  
		  	/// course
			// 1 read previous arguments, seek the 2nd	
			argument = strtok (NULL, ",");		
			// copy token		
			strncpy(course,argument,strlen(argument));
			course[strlen(argument)]='\0';
			
			/// speed
			// 1 read previous argument, seek the 7th	
			for ( int i=0; i<5; i++)
			{	
				argument = strtok (NULL, ",");
			}		
			// copy token		
			strncpy(speed,argument,strlen(argument));
			speed[strlen(argument)]='\0';
			
			// increase counter
			complete++;
		}
		
		// wait for new data from GPS
		while(!serialAvailable(_uart) && timeout > 0) 
		{ 
			delay(1); 
			timeout--; 
		} 	
		
		// Check if time is out
		if (timeout <= 0)
		{			
			flag |= GPS_TIMEOUT;
			return 1;
		}
		
		// read the first byte coming through the port         
		byteGPS = serialRead(_uart);	
			
		// flush incomplete sentences
		while(byteGPS != '$')
		{ 
			if(serialAvailable(_uart) > 0)
			{ 
				// read byte from uart
				byteGPS = serialRead(_uart); 
			}
		}
		inBuffer[i]=byteGPS;  
		i++;
		while(i <= 1 || (byteGPS != '*' && byteGPS != '$' && i < 100))
		{ 	
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				byteGPS = serialRead(_uart);
				if (byteGPS != '*' && byteGPS != '$' && i < 100)
				{
				      inBuffer[i]=byteGPS;
				}
				i++;
			}  
		}
		
		if (byteGPS == '\n' || i == 100) inBuffer[i-1] = '\0';  
		else inBuffer[i] = '\0';
		
		i=0;		

		// separate all the subarrays from 'inBuffer' to 'argument' pointer
		argument = strtok (inBuffer,","); 
				
		//avoid millis overflow problem      
		if( millis()-previous < 0 ) previous=millis(); 
	}
	
	// return to previous state
	previous=millis();
	if (currentSentences == GPS_BINARY_OFF )
	{
		while( !setCommMode(GPS_BINARY) && (millis()-previous)<3000)
		{
			//avoid millis overflow problem
			if( millis()-previous < 0 ) previous=millis(); 
		}
	}
	delay(100);
	previous=millis();
	while(!setCommMode(currentSentences) && (millis()-previous)<3000)
	{
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous=millis(); 
	}
		
	if( flag & GPS_INVALID ) return 0;
	else return 1;
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
 * This will leave time for the GPS to warm up and open -internally- the 
 * communication port to Wasp. According to the Tyco GPS datasheet, it
 * should be possible to connect at faster speeds than 4800bps, and you
 * could change this internally in the _baudRate variable at the WaspGPS 
 * constructor, or at any poing in the code before calling GPS.begin(). This
 * has not been tested, though 
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
	reboot=COLD;
}


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
  flag &= ~(GPS_BAD_CHECKSUM);

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

  if (!result) flag |= GPS_BAD_CHECKSUM;

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


/* setChecksum(_checksum) - set checksum to the end of inBuffer
 *
 * it sets checksum to the end of inBuffer
 */
void WaspGPS::clearBuffer(void) {

for (int i = 0; i < GPS_BUFFER_SIZE; i++) inBuffer[i] = '\0';

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
	extractDate();
	extractTime();
	int day, month, year, hour, minute, second = 0;
  	day		= (dateGPS[0]-'0')*10 + (dateGPS[1]-'0');
  	month 	= (dateGPS[2]-'0')*10 + (dateGPS[3]-'0');
  	year 	= (dateGPS[4]-'0')*10 + (dateGPS[5]-'0');
  	hour 	= (timeGPS[0]-'0')*10 + (timeGPS[1]-'0');
  	minute	= (timeGPS[2]-'0')*10 + (timeGPS[3]-'0');
  	second	= (timeGPS[4]-'0')*10 + (timeGPS[5]-'0');
  	RTC.setTime(year, month, day, RTC.dow(year, month, day), hour, minute, second);
}

/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspGPS GPS = WaspGPS();
