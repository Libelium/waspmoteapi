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
 *  Version:		1.1
 *  Design:		David Gascón
 *  Implementation:	Alejandro Gállego
 */
  

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include "WaspGPRS_Pro.h"




// Constructors ////////////////////////////////////////////////////////////////

WaspGPRS_Pro::WaspGPRS_Pro(){
	_baudRate=GPRS_PRO_RATE;
	_pwrMode=GPRS_PRO_ON;
	_socket=1;
	not_ready=1;
}


// Private Methods /////////////////////////////////////////////////////////////

#if IP_FUSE
/* getIP() - Gets IP direction when configure a TCP/UDP profiles
 *
 * This function gets IP direction when configure a TCP/UDP profiles and stores it in 'IP_direction'
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro::getIP(){
	int i;
	long previous=0;
	
	serialFlush(_socket);
	sprintf(buffer_GPRS, "AT%s\r\n", AT_IP_GET_IP);
	printString(buffer_GPRS, _socket);
	
	previous=millis();
	i=0;
	do{
		while ((!serialAvailable(_socket)) && ((millis() - previous) < 1000));
		IP_dir[i]=serialRead(_socket);
		if (((0x2F < IP_dir[i]) && (IP_dir[i] < 0x3A)) || (IP_dir[i] == '.')) // Only moves the cursor when it's a number or a dot
		{
			i++;
		}
	}while (((!((IP_dir[i] == '\r') && (i != 0))) && (IP_dir[i] != 'E')) && ((millis() - previous) < 1000));	
	IP_dir[i]='\0';

	if (IP_dir[0] == '\0')
	{
		return 0;
	}
	
	return 1;
}

/* checkIPstatus() - get the status of the IP connection
 *
 * This function gets the status of the IP connection
 *
 * Returns a number with the state
*/
uint8_t WaspGPRS_Pro::checkIPstatus(){
	uint8_t answer=10;
	char	ip_status[50];
	int it=0;
	
	for (int i = 0; i < 50; i++)
	{
		ip_status[i] = '\0';
	}
		
	answer=sendCommand1(AT_IP_STATUS, AT_IP_STATUS_R);
	
	if (answer == 1)
	{
		do{
			ip_status[it]=serialRead(_socket);
			it++;
		}while (ip_status[it-1] != '\n');
		
		if (strstr(ip_status, "IP INITIAL") != NULL)
		{
			return 1;
		}
		if (strstr(ip_status, "IP START") != NULL)
		{
			return 2;
		}
		if (strstr(ip_status, "IP CONFIG") != NULL)
		{
			return 3;
		}
		if (strstr(ip_status, "IP GPRSACT") != NULL)
		{
			return 4;
		}
		if ((strstr(ip_status, "IP STATUS") != NULL) || (strstr(ip_status, "IP PROCESSING") != NULL))
		{
			return 5;
		}
		if ((strstr(ip_status, "TCP CONNECTING") != NULL) || (strstr(ip_status, "UDP CONNECTING") != NULL) || (strstr(ip_status, "SERVER LISTENING") != NULL))
		{
			return 6;
		}
		if (strstr(ip_status, "CONNECT OK") != NULL)
		{
			return 7;
		}
		if ((strstr(ip_status, "TCP CLOSING") != NULL) || (strstr(ip_status, "UDP CLOSING") != NULL))
		{
			return 8;
		}
		if ((strstr(ip_status, "TCP CLOSED") != NULL) || (strstr(ip_status, "UDP CLOSED") != NULL))
		{
			return 9;
		}
		if (strstr(ip_status, "PDP DEACT") != NULL)
		{
			return 10;
		}
		answer=0;
	}
	
	if (answer == 0) 
	{
		return 0;
	}
	
	return 11;
}
#endif


/* getIfReady() - gets if GPRS module is ready or not
 *
 * This function gets if GPRS module is ready or not
 *
 * Returns nothing. It changes the value of 'not_ready'
*/
void WaspGPRS_Pro::getIfReady(){
	uint8_t answer=0;
	
	printString(AT_COMMAND, _socket);
	printByte('\r', _socket);
	printByte('\n', _socket);
	delay(10);
	answer=waitForData("OK", 200, 0, 0);
	if (answer == 1)
	{
		not_ready=0;
	}
	else
	{
		not_ready=1;
	}
}

/* checkGPRS() - checks if GPRS connection is OK
 *
 * This function checks if GPRS connection is OK
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro::checkGPRS(){

	uint8_t answer=0;
	
	answer=sendCommand2(AT_GPRS_CHECK, AT_GPRS_CHECK_ON, AT_GPRS_CHECK_OFF);

	if (answer != 1)
	{
		return 0;
	}
	
	return 1;
}


// AT Comands ///////////////////////////////////////////////////////////////////

uint8_t WaspGPRS_Pro::sendCommand1(const char* theText, const char* expectedAnswer){
    return sendCommand1(theText, expectedAnswer, DEFAULT_TIMEOUT, 0);
}

uint8_t WaspGPRS_Pro::sendCommand1(const char* theText, const char* expectedAnswer, int MAX_TIMEOUT, int sendOnce){
    char* theCommand = (char*) calloc(100, sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
    
	#if GPRS_debug_mode>0
		USB.print(F("Send command with 1 answer: "));
		USB.print(theCommand);
	#endif
	
	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while ( (!serialAvailable(_socket)) && ((timeout * (DELAY_ON_SEND / 10)) < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };
	
	free(theCommand);
	
	int answer= waitForData( expectedAnswer, MAX_TIMEOUT, timeout, 0);	
	
	#if GPRS_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	
    return answer;
}

uint8_t WaspGPRS_Pro::waitForData(const char* expectedAnswer, int MAX_TIMEOUT, int timeout, int seconds){
	char* theCommand = (char*) calloc(100, sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	int theLength = 0;
	int it=0;
	bool theSame=false;	
	uint8_t first=1;
	uint8_t match=0;
		
	for (it = 0; it < 100; it++)
	{
		theCommand[it] = '\0';
	}

	while (expectedAnswer[theLength] != '\0') 
	{
		theLength++;
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
		
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket) && !match)
		{
			if ( first )
			{
				for(it=0; it<theLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					#if GPRS_debug_mode>1
						USB.print(char(theCommand[it]));
					#endif
					delay(20);
				}
				first=0;
			}
			it=0;
		
			if ( serialAvailable(_socket))
			{
				theSame=true;
				for(it=0; it<theLength ; it++)
				{
					if(theCommand[it] != expectedAnswer[it])
					{
						theSame= false;
						break;
					}
				}
				if( theSame )
				{
					match=1;
					free(theCommand);
					return 1;
				}
				else
				{
					for(it=0; it<theLength-1 ; it++)
					{
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer: "));
						USB.print(theCommand);
						USB.print(F("   "));
						USB.printHex(theCommand[0]);
						USB.print(F("   "));
						USB.printHex(theCommand[1]);
						USB.println(F(""));
					#endif
				}
			}
		}
	}
	
	free(theCommand);
	
	if ( match )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


//functions with two answers
uint8_t WaspGPRS_Pro::sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2){	
    return sendCommand2(theText, expectedAnswer1, expectedAnswer2, DEFAULT_TIMEOUT, 0);
}

uint8_t WaspGPRS_Pro::sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int sendOnce){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText); 
	
	#if GPRS_debug_mode>0
		USB.print(F("Send command with 2 answers: "));
		USB.print(theCommand);
	#endif

	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while((!serialAvailable(_socket)) && ((timeout * (DELAY_ON_SEND / 10)) < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };

	free(theCommand);
	
    int answer= waitForData( expectedAnswer1, expectedAnswer2, MAX_TIMEOUT, timeout, 0);
    
	#if GPRS_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	
    return answer;
}

uint8_t WaspGPRS_Pro::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int timeout, int seconds){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
	for (int i = 0; i < 100; i++)
	{
		theCommand[i] = '\0';
	}

	int theLength1 = 0;
	int theLength2 = 0;
	int minLength;
	int maxLength;
	int it=0;
	bool theSame=false;	
	uint8_t first=1;
	int cont=0;
	int cont2=0;
	char aux;
	boolean ok;
	
	// Gets the maximum length and the minimum length of the 2 strings
	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;	
	}	
		
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it = 0; it <= minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer1: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					minLength++;
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer2: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				if (minLength == maxLength)
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
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer3: "));
						USB.println(theCommand);
						USB.print(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}
  
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer2) != NULL)
			{
				if ((expectedAnswer2 == ERROR_CME)||(expectedAnswer2 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
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
				free(theCommand);
				return 2;
			}
  			
		}
	}
	
	free(theCommand);
	
	return 0;
}

// 3 answers
uint8_t WaspGPRS_Pro::sendCommand3(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int sendOnce){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
	#if GPRS_debug_mode>0
		USB.print(F("Send command with 3 answers: "));
		USB.print(theCommand);
	#endif
    
	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while((!serialAvailable(_socket)) && ((timeout * (DELAY_ON_SEND / 10)) < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };
	
	free(theCommand);

    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, MAX_TIMEOUT, timeout, 0);
    
	#if GPRS_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
    
    return answer;
}

uint8_t WaspGPRS_Pro::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int timeout, int seconds){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
	uint8_t minLength;
	uint8_t maxLength;
	uint8_t theLength1;
	uint8_t theLength2;
	uint8_t theLength3;
	uint8_t it=0;
	bool theSame=false;	
	uint8_t first=1;
	uint8_t cont=0;
	uint8_t cont2=0;
	char aux;

	boolean ok;
	
	for (it = 0; it < 100; it++) // Initializes 'theCommand' string
	{
		theCommand[it] = '\0';
	}

	// Gets the maximum length and the minimum length of the 3 strings
	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;	
	}
	
	theLength3=strlen(expectedAnswer3);
	if(minLength>theLength3)
	{
		minLength=theLength3;
	}
	if(maxLength<theLength3)
	{
		maxLength=theLength3;	
	}
		
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	
	while(timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it = 0; it < minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer1: "));
						USB.println(theCommand);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					minLength++;
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer2: "));
						USB.println(theCommand);
					#endif
				}
				if (minLength == maxLength)
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
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer3: "));
						USB.println(theCommand);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}
  
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer2) != NULL)
			{
				if ((expectedAnswer2 == ERROR_CME)||(expectedAnswer2 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 2;
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer3) != NULL)
			{
				if ((expectedAnswer3 == ERROR_CME)||(expectedAnswer3 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 3;
			}
			
			cont=0;
			cont2=0;
			ok=false;
  			
		}
	}
	
	free(theCommand);
	
	return 0;
}

//4 answers
uint8_t WaspGPRS_Pro::sendCommand4(const char* theText,  const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int sendOnce) {
	
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;


	
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
    
	#if GPRS_debug_mode>0
		USB.print(F("Send command with 4 answers: "));
		USB.print(theCommand);
	#endif

	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while((!serialAvailable(_socket)) && ((timeout * (DELAY_ON_SEND / 10)) < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand,_socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };

	free(theCommand);
	
    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer4, MAX_TIMEOUT, timeout, 0);
    
	#if GPRS_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
    
    return answer;
}

uint8_t WaspGPRS_Pro::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int timeout, int seconds) {

	char* theCommand = (char*) calloc(100,sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	uint8_t minLength;
	uint8_t maxLength;
	uint8_t theLength1;
	uint8_t theLength2;
	uint8_t theLength3;
	uint8_t theLength4;
	uint8_t it=0;
	bool theSame=false;	
	uint8_t first=1;
	
	for (it = 0; it < 100; it++)
	{
		theCommand[it] = '\0';
	}
	
	uint8_t cont=0;
	uint8_t cont2=0;
	char aux;

	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;
	}
	
	theLength3=strlen(expectedAnswer3);
	if(minLength>theLength3)
	{
		minLength=theLength3;
	}
	if(maxLength<theLength3)
	{
		maxLength=theLength3;	
	}
	
	theLength3=strlen(expectedAnswer4);
	if (minLength>theLength4)
	{
		minLength=theLength4;	
	}
	if (maxLength<theLength4)
	{
		maxLength=theLength4;	
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while ( serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it=0; it < minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer1: "));
						USB.println(theCommand);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of theCommand from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					minLength++;
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer2: "));
						USB.println(theCommand);
					#endif
				}
				if (minLength == maxLength)
				{
					first=0;
				}
			}
			else
			{
				if (serialAvailable(_socket))
				{
					for (it=0; it < maxLength ; it++)
					{
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						USB.print(F("Command answer3: "));
						USB.println(theCommand);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			boolean ok=false;
			
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}
  
			cont=0;
			cont2=0;
			ok=false;
			

			if (strstr(theCommand, expectedAnswer2) != NULL)
			{
				if ((expectedAnswer2 == ERROR_CME)||(expectedAnswer2 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 2;
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer3) != NULL)
			{
				if ((expectedAnswer3 == ERROR_CME)||(expectedAnswer3 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 3;
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
  			if (strstr(theCommand, expectedAnswer4) != NULL)
			{
				if ((expectedAnswer4 == ERROR_CME)||(expectedAnswer4 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 4;
			}
		}
	}
	free(theCommand);
	return 0;
}


#if FTP_FUSE
//FTP private functions
int8_t WaspGPRS_Pro::sendDataFTP(const char* file, const char* path){
	char command[25];
		
	uint32_t file_size;
	long previous=0;
	uint8_t answer=0, count = 10;
	uint8_t end=0;
	uint32_t i,j=0;
	int max_FTP_data=0,aux2,n_bytes=0;

	#if GPRS_debug_mode>0
		USB.println(F("Inside sendDataFTP"));
	#endif
	
	previous = millis();
	while ((FTPstatus() == 2) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000))
	{
		delay(1000);
	}
	
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		#if GPRS_debug_mode>0
			USB.println(F("FTP busy"));
		#endif
		return -56;
	}
	
	// Sets server path and name	
	delay(50);
	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_PUT_NAME, strrchr(path, '/'));
	count=7;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -13;
	}
	else if(answer == 2)
	{
		return -48;
	}
	
	delay(50);
	if (path == strrchr(path, '/'))
	{
		sprintf(buffer_GPRS, "%s\"/\"", AT_FTP_PUT_PATH);
	}
	else
	{
		sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_PUT_PATH, path);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	count=7;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -14;
	}
	else if(answer == 2)
	{
		return -49;
	}
	
	delay(50);
	// Opens the FTP put session
	sprintf(buffer_GPRS, "%s1", AT_FTP_PUT);
	answer=sendCommand2(buffer_GPRS, "+FTPPUT:1,1,", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
	if(answer == 0)
	{
		return -15;
	}
	else if(answer == 2)
	{
		return -50;
	}
	
	max_FTP_data=0;
	
	// Gets the length of the data string
	aux2=serialRead(_socket);
	do{	
		max_FTP_data*=10;
		max_FTP_data+=aux2-0x30;
		previous=millis();
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 10000));
		aux2=serialRead(_socket);
		previous=millis();
	}while ((aux2 != '\r') && ((millis()-previous) < 20000));

	serialFlush(_socket);
	
	i=0;
	j=0;
	n_bytes=0;
	end=0;
	file_size=SD.getFileSize(file);
	
	#if GPRS_debug_mode>0
		USB.print(F("File size on SD: "));
		USB.println(file_size, DEC);
	#endif
	// Starts to send data
	do{	
		// Reads a fragment of the file
		if (max_FTP_data > 250)
		{
			strncpy(buffer_GPRS, SD.cat(file, n_bytes, 250), 250);
			buffer_GPRS[250]='\0';
			n_bytes+=250;
		}
		else
		{
			strcpy(buffer_GPRS, SD.cat(file, n_bytes, max_FTP_data));
			n_bytes+=max_FTP_data;
		}
		while (buffer_GPRS[j] != '\0' )
		{
			j++; // Gets the length of the fragment
		}
		file_size-=j;
		
		sprintf(command, "%s2,%u", AT_FTP_PUT, j); // Requests to send the data string		
		answer=sendCommand2(command, "+FTPPUT:2,", "+FTPPUT:1,0", AT_FTP_WAIT_CONNEC * 100, 0);
		if (answer != 1)
		{
			return -16;
		}
		
		// Sends the data from the file
		printString(buffer_GPRS, _socket);
		previous = millis();		
		while ( (!serialAvailable(_socket)) && ((millis()-previous) < 10000));	
		answer=waitForData("OK", AT_FTP_WAIT_CONNEC * 100, 0, 0);
		if (answer != 1)
		{
			return -17;
		}
		
		answer=waitForData("+FTPPUT:1,", AT_FTP_WAIT_CONNEC * 100, 0, 0);	
		if (answer != 1)
		{	
			return -18;
		}
		
		aux2=serialRead(_socket);
		if (aux2 != 0x31)
		{
			FTP_error_code=0;
			// Gets the number of the error
			do{	
				FTP_error_code*=10;
				FTP_error_code+=aux2-0x30;
				aux2=serialRead(_socket);
			}while (aux2 != '\r');
			
			sprintf(command, "AT%s2,0\r\n", AT_FTP_PUT);
			printString(command, _socket);
			previous=millis();		
			while ( (!serialAvailable(_socket)) && ((millis()-previous) < 10000));	
			answer=waitForData("+FTPPUT:1,0", AT_FTP_WAIT_CONNEC * 100, 0, 0);
			return -19;
		}
		serialRead(_socket); //Discard ',' character
		
		max_FTP_data=0;
		aux2=serialRead(_socket);
		// Gets the length of the data string
		do{
			max_FTP_data*=10;
			max_FTP_data+=aux2-0x30;
			aux2=serialRead(_socket);
		}while (aux2 != '\r');
		j=0;
	}while (file_size > 0);
		
	sprintf(buffer_GPRS, "%s2,0", AT_FTP_PUT);	
	answer=sendCommand2(buffer_GPRS, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
	if(answer == 0)
	{
		return -20;
	}
	else if(answer == 2)
	{
		return -51;
	}
		
	return 1;	
}

int8_t WaspGPRS_Pro::readDataFTP(const char* file, const char* path){
	char command[25];
	long previous=0;
	uint8_t answer=0, count=10;
	uint8_t end=0;
	uint32_t i,j=0;
	int FTP_data=0,aux2,n_bytes=0;
	
	#if GPRS_debug_mode>0
		USB.println(F("Inside readDataFTP"));
		USB.print(F("FTP file: "));
		USB.println(file);
		USB.print(F("SD file:"));
		USB.println(path);
	#endif	
	
	previous = millis();
	while ((FTPstatus() == 2) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000))
	{
		delay(1000);
	}
	
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		#if GPRS_debug_mode>0
			USB.println(F("FTP busy"));
		#endif
		return -56;
	}
	
	// First goes to the main directory
	if (SD.goRoot() != 1)
	{
		return -15;
	}
	
	SD.del(path);
	
	// Then goes to the file directory in SD card	
	if (SD.create(path) != 1)
	{
		return -16;
	}
	
	// Sets server path and name
	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_GET_NAME, strrchr(file, '/'));
	count=7;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -12;
	}
	else if(answer == 2)
	{
		return -48;
	}

	delay(50);
	if (file == strrchr(file, '/'))
	{
		sprintf(buffer_GPRS, "%s\"/\"", AT_FTP_GET_PATH);
	}
	else
	{
		sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_GET_PATH, file);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);
	if(answer == 0)
	{
		return -13;
	}
	else if(answer == 2)
	{
		return -49;
	}
	
	delay(50);
	// Opens the FTP get session
	sprintf(buffer_GPRS, "%s1", AT_FTP_GET);	
	count=3;
	do{
		answer=sendCommand2(buffer_GPRS, "+FTPGET:1,1", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -14;
	}
	else if(answer == 2)
	{
		return -50;
	}
	i=0;
	j=0;	

	delay(1000);
	sprintf(buffer_GPRS, "%s2,200", AT_FTP_GET);
	answer=sendCommand2(buffer_GPRS, "+FTPGET:2,", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
	if(answer == 0)
	{
		return -17;
	}
	else if(answer == 2)
	{
		return -51;
	}
	
	previous=millis();
	
	FTP_data=0;
	while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
	
	aux2 = serialRead(_socket);
	do{	// Gets the length of the data string
		FTP_data*=10;
		FTP_data+=aux2-0x30;
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
		aux2=serialRead(_socket);
	}while ((aux2 != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));

	serialRead(_socket);
	
		
		
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		return -17;
	}
	
	#if GPRS_debug_mode>0
		USB.print(F("FTP data: "));
		USB.println(FTP_data, DEC);
	#endif
	
	while ((FTP_data != 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000))
	{		
		previous=millis();
		while ((serialAvailable(_socket) < FTP_data) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
		
		for (i=0; i < FTP_data; i++)
		{
			buffer_GPRS[i] = serialRead(_socket);
		}
		if (SD.writeSD(path, (uint8_t*)buffer_GPRS, SD.getFileSize(path), FTP_data) != 1)
		{
			return -18;
		}
		
		sprintf(buffer_GPRS, "%s2,200", AT_FTP_GET);
		answer=sendCommand2(buffer_GPRS, "+FTPGET:2,", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
		if(answer == 0)
		{
			return -19;
		}
		else if(answer == 2)
		{
			return -52;
		}
		
		FTP_data=0;
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
		aux2=serialRead(_socket);
		do{	// Gets the length of the data string
			FTP_data*=10;
			FTP_data+=aux2-0x30;
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
			aux2=serialRead(_socket);
		}while ((aux2 != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
		serialRead(_socket);
		#if GPRS_debug_mode>0
			USB.print(F("FTP data: "));
			USB.println(FTP_data, DEC);
		#endif
	}
	
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		return -53;
	}
	
	return 1;
}

long WaspGPRS_Pro::getfilesizeFTP(const char* path){
	
	long size=0,previous=0;
	uint8_t answer=0;
	uint8_t end=0;
	uint32_t i,j=0;
	int aux2,n_bytes=0;

		
	#if GPRS_debug_mode>0
		USB.println(F("Inside FTPsize"));
	#endif
	
	previous = millis();
	while ((FTPstatus() == 2) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000))
	{
		delay(1000);
	}
	
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		#if GPRS_debug_mode>0
			USB.println(F("FTP busy"));
		#endif
		return -56;
	}
	
	// Sets server path and name
	delay(50);
	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_GET_NAME, strrchr(path,'/'));
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);	
	if(answer == 0)
	{
		return -21;
	}
	else if(answer == 2)
	{
		return -53;
	}

	delay(50);
	if (path == strrchr(path, '/'))
	{
		sprintf(buffer_GPRS, "%s\"/\"", AT_FTP_GET_PATH);
	}
	else
	{
		sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_GET_PATH, path);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG * 100, 0);
	if(answer == 0)
	{
		return -22;
	}
	else if(answer == 2)
	{
		return -54;
	}
	
	delay(50);	
	answer=sendCommand2(AT_FTP_GET_SIZE, "+FTPSIZE:1,0,", ERROR_CME, AT_FTP_WAIT_CONNEC * 100, 0);
	if(answer == 0)
	{
		return -23;
	}
	else if(answer == 2)
	{
		return -55;
	}
			
	size = 0;
	
	previous = millis();
	
	while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
	aux2 = serialRead(_socket);
	do{	// Gets the length of the data string
		size *= 10;
		size += aux2 - 0x30;
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
		aux2 = serialRead(_socket);
	}while ((aux2 != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC * 1000));
	
	if ((millis()-previous) > AT_FTP_WAIT_CONNEC * 1000)
	{
		#if GPRS_debug_mode>0
			USB.println(F("Timeout"));
		#endif
		return -56;
	}	
	
	#if GPRS_debug_mode>0
		USB.print(F("Size in FTP: "));
		USB.println(size, DEC);
	#endif
		
	return size;
	
}

/* FTPstatus() - Checks if the FTP is busy
 *
 * This function checks if the FTP is busy or idle
 *
 * Returns '2' if FTP is busy, '1' if FTP is idle and '0' if error.
*/
int8_t WaspGPRS_Pro::FTPstatus(){
	long previous;
	int8_t answer;
	
	answer = sendCommand2(AT_FTP_STATUS, AT_FTP_STATUS, ERROR_CME);
	if (answer == 1)
	{
		previous = millis();
		while((serialAvailable(_socket) < 2) && ((millis() - previous) < 2000));
		if ((millis() - previous) > 2000)
		{
			return 0;
		}
		
		serialRead(_socket);
		serialRead(_socket);
		return (serialRead(_socket) - 0x2F);
	}
	else if (answer == 2)
	{
		return -2;
	}
	return 0;
}
#endif

/* closeGPRS_HTTP_FTP_connection(uint8_t) - closes at opened connection for FTP or HTTP
 *
 * This function closes a GPRS connection with the carrier server to get access to the HTTP and FTP applications
 *
 * It can closes 3 different profiles (1-3)
 *
 * Returns '1' on success, '0' if error and '-2' error with CME error code available
*/
int8_t WaspGPRS_Pro::closeGPRS_HTTP_FTP_connection(uint8_t n_conf){

	int answer;
	char command[15];
	
	
	sprintf(command, "%s0,%u", AT_GPRS_CFG, n_conf); // Closes connection
	answer=sendCommand2(command, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 1;
}


#if HTTP_FUSE
int8_t WaspGPRS_Pro::closeHTTP(){

	uint8_t answer;
	
	answer=sendCommand2(AT_HTTP_TERM, OK_RESPONSE, ERROR_CME);	
	if (answer == 0)
	{
		return -9;
	}
	else if (answer == 2)
	{
		return -15;
	}	

}
#endif
// Public Methods //////////////////////////////////////////////////////////////


//Power functions
/* ON(void) - opens UART1 and powers the SIM900 module
 *
 * It opens UART1 and powers the SIM900 module
 *
 * Returns nothing
*/
int8_t WaspGPRS_Pro::ON(){
	
	detachInterrupt(RXD1_PIN);
	detachInterrupt(TXD1_PIN);
	
	#if GPRS_debug_mode==1
		USB.println(F("Debug mode 1"));
	#endif
	#if GPRS_debug_mode==2
		USB.println(F("Debug mode 2"));
	#endif
	
	if (RTC.isON == 0 )
	{
		RTC.ON();
		RTC.clearAlarmFlag();
		RTC.OFF();
	}
	else
	{
		RTC.clearAlarmFlag();
	}
	begin();
	return (setMode(GPRS_PRO_ON));
}

/* begin(void) - initialize SIM900 module
 *
 * This function powers up the SIM900 module and open Serial Port at velocity selected by the user
 * By default, it will be at 38400bps
 *
 * Returns nothing
*/
void WaspGPRS_Pro::begin(){
	_baudRate=GPRS_PRO_RATE;
	Utils.setMuxSocket1();
	beginSerial(_baudRate, _socket);
}

/* close(void) - closes UART used by SIM900 module
 *
 * This function closes UART used by SIM900 module
 *
 * Returns nothing
*/
void WaspGPRS_Pro::close(){
	closeSerial(_socket);
	Utils.setMux(MUX_TO_LOW, MUX_TO_LOW);
}

/* OFF(void) - closes UART1 and powers off the SIM900 module
 *
 * This function closes UART1 and powers off the SIM900 module
 *
 * Returns nothing
*/
void WaspGPRS_Pro::OFF(){
    setMode(GPRS_PRO_POWER_OFF);
	close();
	if ( RTC.isON == 2 )
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

/* setMode(uint8_t) - Sets GPRS Power Mode
 *
 * This function selects the active power mode among: ON, SLEEP/HIBERNATE and OFF
 * It does not close the serial port, only sends the proper command to GPRS module
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
int8_t WaspGPRS_Pro::setMode(uint8_t pwrMode){

	uint8_t answer=0;
	uint8_t counter, global_counter;
    
	switch (pwrMode)
	{		
		case GPRS_PRO_ON:
			
			//GPRS_Pro v1.0
			
			// Comment the next two lines if there aren't transistors (jumper must be soldered)
			//pinMode(DIGITAL6, OUTPUT);
			//digitalWrite(DIGITAL6, HIGH);
			
			
			/*pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			getIfReady();
			#if GPRS_debug_mode>0
				USB.print("not_ready: ");
				USB.println(not_ready, DEC);
			#endif
			if (not_ready == 1) // if the module is started skip the start pulse
			{
				delay(500);
				digitalWrite(GPRS_PW, HIGH);
				delay(2000);
				digitalWrite(GPRS_PW, LOW);
			}
			
			counter=10;
			global_counter = 5;
			while ((not_ready == 1) && (global_counter > 0))
			{
				getIfReady();
				
				#if GPRS_debug_mode>0
					USB.print("not_ready: ");
					USB.println(not_ready, DEC);
				#endif
				counter--;
				if (counter == 0)
				{
					delay(500);
					digitalWrite(GPRS_PW, HIGH);
					delay(2000);
					digitalWrite(GPRS_PW, LOW);
					counter=10;
					global_counter--;
				}
			}*/
			
			
			// GPRS_Pro v2.0
			pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			delay(500);
			digitalWrite(GPRS_PW, HIGH);
			getIfReady();
			#if GPRS_debug_mode>0
				USB.print(F("not_ready: "));
				USB.println(not_ready, DEC);
			#endif
			
			counter = 15;
			global_counter = 3;
			while ((not_ready == 1) && (global_counter > 0))
			{
				getIfReady();
				#if GPRS_debug_mode>0
					USB.print(F("not_ready: "));
					USB.println(not_ready, DEC);
				#endif
				counter--;
				delay(1000);
				if (counter == 0)
				{	
					#if GPRS_debug_mode>0
						USB.println(F("Restarting"));
					#endif
					delay(500);
					digitalWrite(GPRS_PW, LOW);
					delay(2000);
					digitalWrite(GPRS_PW, HIGH);
					counter=20;
					global_counter--;
				}
			}
			
			if (global_counter > 0)
			{
				// All versions
				
				// Enables numeric error codes:
				sendCommand1("+CMEE=1",OK_RESPONSE);
				// Disables command echoes:
				sendCommand1("E0",OK_RESPONSE);
				
				answer=sendCommand1(POWER_NO_SLEEP, OK_RESPONSE);
				
				answer=sendCommand2(POWER_FULL, OK_RESPONSE, ERROR_CME);
				
				if (PWR.getBatteryLevel() < 20)
				{	
					USB.println(F("********************"));
					USB.println(F("Danger! Low battery!"));
					USB.println(F("********************"));
					answer = 3;
				}
			}
			else
			{	
				digitalWrite(GPRS_PW, LOW);
				answer = 0;
			}
			
			break;

		case GPRS_PRO_FULL:
			answer=sendCommand1(POWER_NO_SLEEP, OK_RESPONSE);
			answer=sendCommand2(POWER_FULL, OK_RESPONSE, ERROR_CME);
			break;
			
		case GPRS_PRO_RF_OFF:
			answer=sendCommand1(POWER_NO_SLEEP, OK_RESPONSE);
			answer=sendCommand2(POWER_RF_OFF, OK_RESPONSE, ERROR_CME);
			break;

		case GPRS_PRO_MIN:
			answer=sendCommand1(POWER_NO_SLEEP, OK_RESPONSE);
			answer=sendCommand2(POWER_MIN, OK_RESPONSE, ERROR_CME);
			break;
			
		case GPRS_PRO_SLEEP:
			answer=sendCommand1(POWER_SLEEP, OK_RESPONSE);
			break;

		case GPRS_PRO_POWER_OFF:
			// GPRS_Pro v1.0
			/*delay(500);
			digitalWrite(GPRS_PW, HIGH);
			delay(2000);
			digitalWrite(GPRS_PW, LOW);
			delay(500);
			
			// Comment the next two lines if there aren't transistors (jumper must be soldered)
			//pinMode(DIGITAL6, OUTPUT);
			//digitalWrite(DIGITAL6, LOW);
			
			getIfReady();
			if (not_ready == 1)
			{
				answer=0;
			}
			else
			{
				answer=1;
			}*/
				
			// GPRS_Pro v2.0
			pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			answer=1;
			_pwrMode=pwrMode;
			
			// All versions
			
			break;
	}	
	if (answer == 1)
	{
		_pwrMode=pwrMode;
		return 1;
	}
	else if (answer > 1)
	{
		return -answer;
	}
		
	return 0;
}

/* getMode(void) - Gets GPRS_Pro Power Mode
 *
 * This function gets the actual GPRS_Pro Power Mode. Possible values are ON, FULL, RF_OFF, MIN, SLEEP and POWER_OFF
 *
 * Returns the power mode
*/
uint8_t	WaspGPRS_Pro::getMode(){
	return	_pwrMode;
}

/* setTime() - Sets time and date to GPRS_Pro module from RTC
 *
 * Sets time and date to GPRS_Pro module from RTC
 *
 * Returns '1' on success , '0' if error and '2' if error with CME error response.
*/
uint8_t WaspGPRS_Pro::setTime(){
	
	bool RTC_ant=false;
	int8_t answer;
	
	if (RTC.isON != 1) // Checks if the RTC is on
	{
		RTC_ant=true;
		RTC.ON();
	}
	
	RTC.getTime(); //Gets time from RTC
	
	sprintf( buffer_GPRS, "%s\"%02u/%02u/%02u,%02u:%02u:%02u+02\"", SET_TIME, RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);

	if (RTC_ant) // Powers off the RTC if before it was off
	{
		RTC.OFF();
	}
	
	answer=sendCommand2( buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer == 2)
	{
		return -answer;
	}
	else
	{
		return answer;
	}
}

/* check(uint8_t) - Checks if GPRS is connected to the network
 *
 * This function checks if GPRS module is connected to the network. If not, it has no sense working with GPRS.
 *
 * It sends a command to GPRS module DEFAULT_TIMEOUT times. If GPRS module does not connect within these tries, function
 * exits.
 *
 * Returns '1' when connected and '0' if not
*/
int8_t WaspGPRS_Pro::check(uint16_t time){
	
	unsigned long previous;
	int8_t answer;
	
	previous = millis();
	
	do{	
		// Sends the command and waits for the answer (0,1 for home network and 0,5 for roaming)
		answer = sendCommand2("+CREG?", "+CREG: 0,1", "+CREG: 0,5");
	}while ((answer == 0) && ((millis() - previous) < (time * 1000)));
	
	if ((answer == 0) || ((millis() - previous) > (time * 1000)))
	{
		return 0;
	}
	
	return 1;
}


//SIM functions
/* setPIN(const char*) - sets PIN to the SIM
 *
 * This function sets the specified PIN to the SIM
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t	WaspGPRS_Pro::setPIN(const char* pin){
	
	uint8_t answer=0;

	sprintf(buffer_GPRS, "%s\"%s\"", AT_PIN, pin);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;
}

/* changePIN(const char*, const char*) - changes PIN number to the SIM
 *
 * This function changes the PIN number to the SIM
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::changePIN(const char* old_pin, const char* new_pin){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s\"SC\",\"%s\",\"%s\"", AT_CHANGE_PASSWORD, old_pin, new_pin);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;
	
}

/* getIMEI() - gets the IMEI from the SIM card
 *
 * This function gets the IMEI from the SIM card. It stores the IMEI into 'buffer_GPRS' variable.
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro::getIMEI(){
	
	int8_t answer,counter;
	long previous;

	answer=sendCommand1(AT_GPRS_IMEI, "\r\n");
	
	if (answer == 1)
	{
		counter=0;
		do{
			previous=millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) <= 2000));
			buffer_GPRS[counter]=serialRead(_socket);
			if ((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n'))
			{
				counter++;
			}
		}while ((buffer_GPRS[counter] != '\r') && ((millis()-previous) <= 2000));
				
		if (buffer_GPRS[counter] == '\r')
		{
			buffer_GPRS[counter]='\0';
			return 1;
		}			
	}
	
	return 0;
		
}

/* getIMSI() - gets the IMSI from the SIM card
 *
 * This function gets the IMSI from the SIM card. It stores the IMSI into 'buffer_GPRS' variable.
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::getIMSI(){

	unsigned long previous=millis();
	int8_t counter=0,answer=0;
	
	answer=sendCommand2(AT_GPRS_IMSI, "\r\n", ERROR_CME);
	
	if (answer == 1)
	{
		previous=millis();
		counter=0;
		do{
			previous=millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
			buffer_GPRS[counter]=serialRead(_socket);
			if ((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n'))
			{
				counter++;
			}
		}while ((((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n')) || (counter == 0)) && ((millis()-previous) < 3000));
			
		if (buffer_GPRS[counter] == '\r')
		{
			buffer_GPRS[counter]='\0';
			return 1;
		}
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 0;
}


#if GSM_FUSE
//Call functions
/* makeCall(const char*) - makes a call to the seleted telephone number
 *
 * This function makes a call to the given telephone number.
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::makeCall(const char* tlfNumber){

	uint8_t answer=0;

	sprintf(buffer_GPRS, "%s%s;", AT_CALL, tlfNumber);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
	
}

/* makelostCall(const char* , uint8_t) - makes a lost call to the seleted telephone number
 *
 * This function makes a call to the given telephone number and its duration is specified by the other input.
 * After 'timeCall' seconds, hang the call up.
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::makeLostCall(const char* tlfNumber, uint8_t timeCall){

	uint8_t answer=0;

	sprintf(buffer_GPRS, "%s%s;", AT_CALL, tlfNumber);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer == 1)
	{
		for (int a=0; a < timeCall ; a++)
		{
			delay(1000);
		}
		hangUp();
		return 1;
	}
	
	return 0;
}

/* setInfoIncomingCall() - set the info shown when an incoming call is received
 *
 * This function sets the info shown when an incoming call is received
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
 */
int8_t	WaspGPRS_Pro::setInfoIncomingCall(){
	
	uint8_t answer=0;

	answer=sendCommand2(AT_ID_INCALL, OK_RESPONSE, ERROR_CME);
	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 1;
}

/* readCall(const char*) - set in 'tlfIN' variable the tlf number of the incoming call
 *
 * This function sets in 'tlfIN' variable the tlf number of the incoming call
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * 'data' must contains the tlfn number, something like that: aaaa"+34666999888"aaa
 *
 * Returns '1' on success and '0' if error
*/
uint8_t	WaspGPRS_Pro::readCall(const char* data){
	uint8_t a=0;
	uint8_t b=0;

    tlfIN[0]='\0';
	while ( (data[a] != '"') && (a < 45) )
	{
		a++;
	}
	a++;
	if (a >= 45)
	{
		return 0;
	}
	while ( (data[a] != '"') && (a < 45) && (b < 15) )
	{
		tlfIN[b]=data[a];
		a++;
		b++;
	}
    if ( b >= 15 )
	{
		tlfIN[b-1]='\0';
	}
    else
	{
		tlfIN[b]='\0';
	}
	return 1;
}

/* hangUp() - hangs the call up
 *
 * This function hangs all the active calls up.
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro::hangUp(){
	uint8_t answer=0;
	
	answer=sendCommand1(AT_HANG, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* setMonitorVolume(uint8_t) - Sets the monitor speaker loudness
 *
 * This function sets the monitor speaker loudness from 0 to 9
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::setMonitorVolume(uint8_t volume){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_SPEAKER_VOLUME, volume);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;	
}

/* setMonitorMode(uint8_t) - Sets the monitor speaker mode
 *
 * This function sets the monitor speaker mode from 0 to 9
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::setMonitorMode(uint8_t mode){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_SPEAKER_MODE, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
	
}

/* setCLIPresentation(uint8_t) - Enables or disables the presentation of the incoming call 
 *
 * This function enables or disables the presentation of the incoming call
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::setCLIPresentation(uint8_t mode){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_CLIP_MODE, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
	
}

/* setCLIRestriction(uint8_t) - Restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * This function restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * Allowed modes DEFAULT_CLIR='0', INVOKE_CLIR='1' or SUPPRESS_CLIR='2'
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::setCLIRestriction(uint8_t mode){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_CLIR_MODE, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
	
}

/* getPhoneStatus() - Gets the phone activity status
 *
 *This function gets the phone activity status
 *
 *Return '0' for error, '1'= Ready, '2'= Unknown,'3'= Ringing, '4'= Call in progress
*/
uint8_t WaspGPRS_Pro::getPhoneActStatus(){
	uint8_t answer=0;
	
	answer=sendCommand2(AT_PHONE_ACTIVITY, AT_PHONE_ACTIVITY_R, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	else
	{
		serialRead(_socket);
		answer=serialRead(_socket)-0x30;
		if (answer == 0)
		{
			answer=1;
		}
	}	
	
	return answer;
}

/* setLoudspeakerLevel() - Sets loudspeaker volume 
 *
 * This function sets loudspeaker volume level between 0-100
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
uint8_t WaspGPRS_Pro::setLoudspeakerLevel(uint8_t volume){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_SPEAKER_LEVEL, volume);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 1;
}

/* setCallAlert(uint8_t) - Configures the mode of calls alert
 *
 * This function configures the mode of calls alert
 *
 * Returns '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
 * '-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
 * '-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
*/
uint8_t WaspGPRS_Pro::setCallAlert(uint8_t mode){
	return setCallAlert(mode, 0, 0);
}

/* setCallAlert(uint8_t,uint8_t, uint8_t) - Configures the mode of calls alert
 *
 * This function configures the mode of calls alert
 *
 * Returns '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
 * '-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
 * '-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
*/
uint8_t WaspGPRS_Pro::setCallAlert(uint8_t mode,uint8_t sound_type, uint8_t ring_level){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_ALERT_SOUND_MODE, mode);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	sprintf(buffer_GPRS, "%s%u", AT_ALERT_SOUND_LEVEL, sound_type);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return -3;
	}
	else if (answer == 2)
	{
		return -4;
	}
	
	sprintf(buffer_GPRS, "%s%u", AT_RINGER_SOUND_LEVEL, ring_level);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);	
	if (answer == 0)
	{
		return -5;
	}
	else if (answer == 2)
	{
		return -6;
	}
	
	return 1;
}

/* setMute(uint8_t) - Enables or disables mute during a call
 *
 * This function enables or disables mute during a call
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
uint8_t WaspGPRS_Pro::setMute(uint8_t mute_mode){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_MUTE, mute_mode);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	return 1;
}


//SMS functions
/* setTextModeSMS() - set the text mode to the sms
 *
 * This function sets the text mode to the sms
 *
 * Returns '1' on success and '0' if error
 */
uint8_t WaspGPRS_Pro::setTextModeSMS(){
	
	uint8_t answer=0;

	answer=sendCommand1(AT_SMS_MODE, OK_RESPONSE);
		
	if (answer != 1)
	{
		return 0;
	}
	
	return 1;
}

/* sendSMS(const char*, const char*) - sends a SMS to the specified number
 *
 * This function sends an SMS to the specified number.
 *
 * Returns '1' on success,'0' if error, '-2' if error sending the SMS and '-3' if error sending the SMS with CMS error code available
*/
int8_t WaspGPRS_Pro::sendSMS(const char* smsText, const char* tlfNumber){
	
	uint8_t answer=0;

	setTextModeSMS();
	
	sprintf(buffer_GPRS, "%s\"%s\"", AT_SMS, tlfNumber);
	answer=sendCommand1(buffer_GPRS, AT_SMS_R);
	if (answer != 1)
	{
		return 0;
	}
	
	sprintf(buffer_GPRS, "%s%c", smsText, 0x1A);
	printString(buffer_GPRS, _socket);
	answer=waitForData(OK_RESPONSE, ERROR_CMS, DEFAULT_TIMEOUT, 0, 0);
	
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return -3;
	}
	
	return 1;
}

/* setInfoIncomingSMS() - set the info shown when an incoming SMS is received
 *
 * This function sets the info shown when an incoming SMS is received
 *
 * Returns '1' on success and '0' if error
 */
uint8_t WaspGPRS_Pro::setInfoIncomingSMS(){
	
	uint8_t answer=0;

	answer=sendCommand1(AT_SMS_INFO, OK_RESPONSE);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* readSMS() - set in 'tlfIN' and 'sms' variables the tlf number and text of the incoming SMS
 *
 * This function sets in 'tlfIN' and 'sms' variables the tlf number and text of the incoming SMS
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns '1' on success, '0' if error and '-1' if no memory
*/
int8_t WaspGPRS_Pro::readSMS(const char* data){
	
	uint8_t a=0,b=0,c=0;
	char* command = (char*) calloc(30, sizeof(char));
	if ( command == NULL )
	{
		return -1;
	}
	uint8_t* byteIN = (uint8_t*) calloc(200, sizeof(uint8_t));
	if ( byteIN == NULL )
	{
		free(command);
		return -1;
	}
	long previous=0;
	uint8_t counter=0;
	
    tlfIN[0]='\0';
    sms[0]='\0';
    sms_index[0]='\0';
	
	while ( (data[a] != ',') && (a < 45) )
	{
		a++;
	}
	a++;
	if (a >= 45)
	{
		free(command);
		free(byteIN); 
		return 0;
	}
	while ( data[a] != 13 )
	{
		sms_index[b]=data[a];
		a++;
		b++;
	}
	sms_index[b]='\0';
	sprintf(command, "AT%s%s\r\n", AT_SMS_READ, sms_index);
	printString(command, _socket);
	previous=millis();
	while (!serialAvailable(_socket) && ((millis()-previous) < 2000) );
	previous=millis();
	a=0;
	while ( (millis()-previous) < 2000 )
	{
		while( serialAvailable(_socket) && (millis()-previous) < 2000 )
		{
			byteIN[a]=serialRead(_socket);
			
			#if GPRS_debug_mode>0
				USB.print(byteIN[a]);
			#endif
			a++;
		}
	}
	a=0;
	while ( counter < 3 )
	{
		while( (byteIN[a] != '"') && (a < 200) )
		{
			a++;
		}
		a++;
		counter++;
	}
	if (a >= 200)
	{
		free(command);
		free(byteIN); 
		return 0;
	}
	counter=0;
	while ( (byteIN[a] != '"') && (a < 200) && (c < 15) )
	{
		tlfIN[c]=byteIN[a];
		#if GPRS_debug_mode>0
			USB.print(tlfIN[c]);
		#endif
		a++;
		c++;
	}
	
	if ( c >= 15 )
	{
		tlfIN[c-1]='\0';
	}
	else
	{
		tlfIN[c]='\0';
	}
	
	while ( counter < 5 )
	{
		while ( (byteIN[a] != '"') && (a < 200) )
		{
			a++;
		}
		a++;
		counter++;
	}
	if (a >= 200)
	{
		free(command);
		free(byteIN); 
		return 0;
	}
	a++;
	a++;
	b=0;
	
	while ( (byteIN[a] != 13) && (a < 200) && (b < 100) )
	{
		sms[b]=byteIN[a];
		
		#if GPRS_debug_mode>0
			USB.print(sms[b]);
		#endif
		b++;
		a++;
	}
	
	if (a >= 200){
		free(command);
		free(byteIN); 
		return 0;
	}
	
	if ( b >= 100 )
	{
		sms[b-1]='\0';
	}
	else
	{
		sms[b]='\0';
	}
	
	free(command);
	free(byteIN); 
	return 1;
}

/* getTotalSMS() - Gets the number of total SMS stored in the SIM
 *
 * This function gets the number of total SMS stored in the SIM
 *
 * Returns the number of SMS or '-2' if error
*/
uint8_t WaspGPRS_Pro::getTotalSMS(){
	
	int8_t answer, count;
	long previous;
	
	sprintf(buffer_GPRS, "%s\"SM\",\"SM\",\"SM\"", AT_SMS_MEMORY);  
	answer=sendCommand1(buffer_GPRS, AT_SMS_MEMORY_R);

	
	if (answer == 1)
	{
		count=serialRead(_socket);
		answer=0;	
		
		previous = millis();
		// Gets the number of SMS in the memory
		do{
			answer*=10;
			answer+=count-0x30;
			count=serialRead(_socket);
		}while ((count != ',') && ((millis()-previous) < 1000));
		
		return answer;
	}
	return -2;
}

/* deleteSMS(uint8_t ) - deletes a sms in the memory
 *
 * This function deletes a sms in the memory selected by sms_index
 *
 * Returns '1' on success '0' if error and '-2' if error with CMS error code available
*/
uint8_t WaspGPRS_Pro::deleteSMS(uint8_t sms_index){

	int8_t answer;
    
	sprintf(buffer_GPRS, "%s%u", AT_SMS_DELETE, sms_index);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CMS);
	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 1;
}
#endif


/* manageIncomingData() - manage incoming data from serial port, executing proper functions to store received data
 *
 * This function manages incoming data from serial port, executing proper functions to store received data
 *
 * Returns '1' for call, '2' for SMS, '3' for IP data and '0' for error or not data
*/
int8_t	WaspGPRS_Pro::manageIncomingData(){
	char* byteIN = (char*) calloc(200, sizeof(char));
	if ( byteIN == NULL )
	{
		return -1;
	}
	uint8_t a=0; //counter and auxiliar variable
	long previous=0;
	
	while (a < 100)
	{
		byteIN[a]='\0';
		a++;
	}
	a=0;
	
	serialFlush(_socket);
	previous=millis();
	while (!serialAvailable(_socket) && ((millis()-previous) < 20000));
	previous=millis();
	while ( (millis()-previous) < 2000 )
	{
		while( serialAvailable(_socket) && ((millis()-previous) < 2000) )
		{
			byteIN[a]=serialRead(_socket);
			a++;
		}
	}

	if (a > 0) // this if is conditionated by the fuses selected in WaspGPRS_Pro.h
	{
#if GSM_FUSE&&IP_FUSE	
		if ((strstr(byteIN, "+CLIP")) != NULL)
		{
			readCall(byteIN);
			a=1;
		}
		else if ((strstr(byteIN, "+CMTI")) != NULL)
		{
			readSMS(byteIN);
			a=2;
		}
		else
		{
			readIPData(byteIN);
			a=3;
		}
#endif
#if GSM_FUSE&&(~IP_FUSE)
		if ((strstr(byteIN, "+CLIP")) != NULL)
		{
			readCall(byteIN);
			a=1;
		}
		else if ((strstr(byteIN, "+CMTI")) != NULL)
		{
			readSMS(byteIN);
			a=2;
		}
#endif
#if (~GSM_FUSE)&&IP_FUSE
		readIPData(byteIN);
		a=3;
#endif
	}
	else
	{
		a=0;
	}
	free(byteIN);
	if (a == 0)
	{
		return 0;
	}
	return a;
}

/*switchtoDataMode() - switchs from command mode to data mode
 *
 * This function switchs from command mode to data modes
 *
 * Returns '1' on success, '0' if error and '-2' if connection is not successfully resumed
*/
int8_t WaspGPRS_Pro::switchtoDataMode(){
	
	uint8_t answer=0;
	
	answer=sendCommand2(AT_DATA_MODE, AT_DATA_MODE_R, AT_DATA_MODE_FAIL);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 1;
}

/*switchtoCommandMode() - switchs from data mode to command mode
 *
 * This function switchs from data mode to command mode
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro::switchtoCommandMode(){

	uint8_t answer=0;
	
	delay(1000);	//waits one second after the last data send
	printByte('+', _socket);
	printByte('+', _socket);
	printByte('+', _socket);
	answer=waitForData(OK_RESPONSE, 500, 0, 0);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* sendCommand(ATcommand) - sends any command to GPRS module
 *
 * This function sends any command to GPRS module
 *
 * It stores in 'buffer_GPRS' variable the answer returned by the GPRS module
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::sendCommand(const char* ATcommand){
	
	uint8_t timeout=0;
	uint8_t i=0;
	
	sprintf(buffer_GPRS, "AT%s%c%c", ATcommand, '\r', '\n');

	serialFlush(_socket);
	
	printString(buffer_GPRS, _socket);
	delay(DELAY_ON_SEND);
	
	while ( timeout < 5 )
	{
		while (!serialAvailable(_socket) && (timeout < 5))
		{
			timeout++;
			delay(1000);
		}
		while (serialAvailable(_socket) && (timeout < 5))
		{
			if (i < BUFFER_SIZE)
			{
				buffer_GPRS[i] = serialRead(_socket);
				i++;
			}
			else
			{
				serialRead(_socket);
			}
			delay(20);
			timeout=0;
			if (i >= 199)
			{
				timeout=5;
			}
		}
	}
	
	if (i < BUFFER_SIZE)
	{
		buffer_GPRS[i] = '\0';
	}
	else
	{
		buffer_GPRS[i - 1] = '\0';
	}	
	
	if ( i < 5 )
	{
		return 0;
	}
	return 1;
}

//HTTP and FTP functions
/* configureGPRS_HTTP_FTP(uint8_t) - configures GPRS connection with login, password and other parameters
 *
 * This function creates a GPRS connection with the carrier server to get access to the HTTP and FTP applications
 *
 * It can configures 3 different profiles (1-3)
 *
 * Returns '1' on success, '0' if error and '-2' if error setting the type of internet connection, 
 * '-3' if error setting the apn, '-4' if error setting the user name, '-5' if error setting the password
 * and '-6' if error saving the configuration
*/
int8_t WaspGPRS_Pro::configureGPRS_HTTP_FTP(uint8_t n_conf){

	int count=5;

    sprintf(buffer_GPRS, "%s3,%u,\"%s\",\"%s\"", AT_GPRS_CFG, n_conf, "Contype", "GPRS"); // Configures the connection	
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
	
    if (count == 0)
	{
        return -2;
    }
    
    sprintf(buffer_GPRS, "%s3,%u,\"%s\",\"%s\"", AT_GPRS_CFG, n_conf, "APN", AT_GPRS_APN);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -3;
    }
    
    sprintf(buffer_GPRS, "%s3,%u,\"%s\",\"%s\"", AT_GPRS_CFG, n_conf, "USER", AT_GPRS_LOGIN);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -4;
    }
    
    sprintf(buffer_GPRS, "%s3,%u,\"%s\",\"%s\"", AT_GPRS_CFG, n_conf, "PWD", AT_GPRS_PASSW);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -5;
    }
    
    sprintf(buffer_GPRS, "%s5,%u", AT_GPRS_CFG, n_conf); // Saves configuration
	count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -6;
    }

    return 1; 
}

#if FTP_FUSE
/* uploadFile(const char*, const char*, const char*, const char*, const char* , const char*, uint8_t) - uploads a file to a FTP server
 *
 * This function uploads a file to a FTP server
 *
 * Returns '1' on success and '0' if error opening connection with the GPRS provider, '-2' if error getting the IP address
 * '-3' if error setting the FTP/HTTP ID, '-4' if error setting the FTP mode, '-5' if error setting the FTP type,
 * '-6' if error setting the FTP server, '-7' if error setting the FTP port, '-8' if error setting the user name,
 * '-9' if error setting the password, '-10' if error starting the SD, '-11' if error taking the file size in the SD,
 * '-13' if error setting the file name in the FTP server, '-14' if error setting the path of the file in the FTP server
 * '-15' if error opening the FTP session, '-16' if error when request to send data, '-17' error sending data to the FTP,
 * '-18' if error waiting for send more data, '-20' if error closing the FTP session, '-21' setting the file name in the FTP to get the file size
 * '-22' setting the path in the FTP to get the file size, '-23' if error getting the file size
 * '-41' if error setting the FTP/HTTP ID with CME error code available, '-42' if error setting the FTP mode with CME error code available,
 * '-43' if error setting the FTP type with CME error code available, '-44' if error setting the FTP server with CME error code available,
 * '-45' if error setting the FTP port with CME error code available, '-46' if error setting the user name with CME error code available,
 * '-47' if error setting the password with CME error code available, '-48' if error starting the SD with CME error code available,
 * '-49' if error setting the path of the file in the FTP server with CME error code available, '-50' if error opening the FTP session with CME error code available,
 * '-51' if error closing the FTP session with CME error code available, '-53' setting the file name in the FTP to get the file size with CME error code available,
 * '-54' setting the path in the FTP to get the file size with CME error code available, '-55' if error getting the file size with CME error code available
*/
int8_t WaspGPRS_Pro::uploadFile(const char* file, const char* path, const char* user, const char* passw, const char* ftp_server, const char* ftp_port, uint8_t n_conf){

	long previous=0;
	uint8_t answer=0;
	uint8_t id=0;
	uint8_t i=0,j=0;
	uint8_t count=10;
	long sd_size=0;
	long ftp_size=0;
	
	closeGPRS_HTTP_FTP_connection(n_conf);
	
	sprintf(buffer_GPRS, "%s1,%u", AT_GPRS_CFG, n_conf); // Opens connection
	count = 10;
    do{	
        count--;
		answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
    }while ((answer != 1) && (count != 0));
	
    if (count == 0)
	{
        return 0;
    }

    sprintf(buffer_GPRS, "AT%s2,%u\r\n", AT_GPRS_CFG, n_conf); // Gets IP direction
	count=5;
	
    do{
        count--;
		previous=millis();
        printString(buffer_GPRS, _socket);
        do{
            while ((!serialAvailable(_socket)) && (millis()-previous < 5000));
        }while ((serialRead(_socket) != '"') && (millis()-previous < 5000));
        i=0;
        do{
            while ((!serialAvailable(_socket)) && (millis()-previous < 5000));
            IP_dir[i]=serialRead(_socket);
            i++;
        }while ((IP_dir[i-1] != '"') && (millis()-previous < 5000));
        IP_dir[i-1]='\0';
    }while ((IP_dir[0] == '+') && (count != 0));

    if (count == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
        return -2;
    }

	// Connects to FTP Server
	sprintf(buffer_GPRS, "%s%u", AT_FTP_ID, n_conf);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -3;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -41;
	}

	sprintf(buffer_GPRS, "%s=1", AT_FTP_MODE);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -42;
	}

	sprintf(buffer_GPRS, "%s\"I\"", AT_FTP_TYPE);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -43;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_SERVER, ftp_server);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -44;
	}

	sprintf(buffer_GPRS, "%s%s", AT_FTP_PORT, ftp_port);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -45;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_UN, user);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -8;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -46;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_PW, passw);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -9;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -47;
	}

	
	SD.ON();
	// First goes to the main directory
	if (SD.goRoot() != 1)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		SD.OFF();
		return -10;
	}

	
	count=10;
	do{
		sd_size=SD.getFileSize(file);
		count--;
	}while ((sd_size == -1) && (count != 0));
	
	
	
	if (count == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		SD.OFF();
		return -11;
	}
		
	count=10;
	do{
		answer = sendDataFTP(file, path);	
		count--;
		ftp_size=getfilesizeFTP(path);
	}while (!( ftp_size == sd_size) && (count != 0));
	
	SD.OFF();
	
	if (count == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		if (answer != 1)
		{
			return answer;
		}
		else 
		{
			return ftp_size;
		}
	}
	
	closeGPRS_HTTP_FTP_connection(n_conf);
	
	return 1;
}

/* downloadFile(const char*, const char*, const char*, const char*, const char* , const char*, uint8_t) - downloads a file from a FTP server
 *
 * This function downloads a file from a FTP server
 *
 * Returns '1' on success and '0' if error opening connection with the GPRS provider, '-1' error downloading the file, '-2' if error getting the IP address
 * '-3' if error setting the FTP/HTTP ID, '-4' if error setting the FTP mode, '-5' if error setting the FTP type,
 * '-6' if error setting the FTP server, '-7' if error setting the FTP port, '-8' if error setting the user name,
 * '-9' if error setting the password, '-12' if error setting the file name in the FTP server, 
 * '-13' if error setting the path of the file in the FTP server, '-14' if error opening the FTP session,
 * '-15' if error starting the SD, '-16' if error creating the file, '-17' error requesting data to the FTP,
 * '-18' if error saving data into the SD, '-19' if error requesting more data to the FTP, '-21' setting the file name in the FTP to get the file size
 * '-22' setting the path in the FTP to get the file size, '-23' if error getting the file size
 * '-41' if error setting the FTP/HTTP ID with CME error code available, '-42' if error setting the FTP mode with CME error code available,
 * '-43' if error setting the FTP type with CME error code available, '-44' if error setting the FTP server with CME error code available,
 * '-45' if error setting the FTP port with CME error code available, '-46' if error setting the user name with CME error code available,
 * '-47' if error setting the password with CME error code available, '-48' if error setting the file name in the FTP server with CME error code available,
 * '-49' if error setting the path of the file in the FTP server with CME error code available, '-50' if error opening the FTP session with CME error code available,
 * '-51' if error requesting data to the FTP with CME error code available, '-52' if error requesting more data to the FTP with CME error code available,
 * '-53' setting the file name in the FTP to get the file size with CME error code available,
 * '-54' setting the path in the FTP to get the file size with CME error code available, '-55' if error getting the file size with CME error code available
 * and '-56' if FTP is busy
*/
int8_t WaspGPRS_Pro::downloadFile(const char* file, const char* path, const char* user, const char* passw, const char* ftp_server, const char* ftp_port, uint8_t n_conf){
	
	long previous=0;
	int8_t answer=0;
	uint8_t id=0;
	uint8_t i=0,j=0;
	uint8_t count=10;
	unsigned long sd_size=0;
	unsigned long ftp_size=0;
	
	closeGPRS_HTTP_FTP_connection(n_conf);
	
	sprintf(buffer_GPRS, "%s1,%u", AT_GPRS_CFG, n_conf); // Opens connection
	count = 5;
    do
	{
        count--;
		answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
    }while ((answer != 1) && (count != 0));
	
    if (count == 0)
	{
        return 0;
    }

    sprintf(buffer_GPRS, "AT%s2,%u\r\n", AT_GPRS_CFG, n_conf); // Gets IP direction
	count=10;
	
    do{
        count--;
		previous=millis();
        printString(buffer_GPRS, _socket);
        do{
            while ((!serialAvailable(_socket)) && (millis()-previous < 2000));
        }while ((serialRead(_socket) != '"') && (millis()-previous < 2000));
        i=0;
        do{
            while ((!serialAvailable(_socket)) && (millis()-previous < 2000));
            IP_dir[i]=serialRead(_socket);
            i++;
        }while ((IP_dir[i-1] != '"') && (millis()-previous < 2000));
        IP_dir[i-1]='\0';
    }while ((IP_dir[0] == '+') && (count != 0));

    if (count == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
        return -2;
    }

	// Connects to FTP Server
	sprintf(buffer_GPRS, "%s%u", AT_FTP_ID, n_conf);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -3;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -41;
	}

	sprintf(buffer_GPRS, "%s=1", AT_FTP_MODE);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -42;
	}

	sprintf(buffer_GPRS, "%s\"I\"", AT_FTP_TYPE);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -43;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_SERVER, ftp_server);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -44;
	}

	sprintf(buffer_GPRS, "%s%s", AT_FTP_PORT, ftp_port);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -45;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_UN, user);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -8;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -46;
	}

	sprintf(buffer_GPRS, "%s\"%s\"", AT_FTP_PW, passw);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -9;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -47;
	}
	
	SD.ON();
	count = 3;
	do{
		answer = readDataFTP(file, path);
		ftp_size = getfilesizeFTP(file);
		#if GPRS_debug_mode>0
			USB.print(F("Return from readDataFTP: "));
			USB.println(answer, DEC);
			USB.print(F("ftp_size: "));
			USB.println(ftp_size, DEC);
			USB.print(F("count: "));
			USB.println(count, DEC);
			USB.print(F("file size SD: "));
			USB.println(SD.getFileSize(path), DEC);
		#endif
		count--;
	}while (((answer != 1)  || (ftp_size != SD.getFileSize(path))) && (count != 0));
	SD.OFF();

	if ((count == 0) && (ftp_size != SD.getFileSize(path)))
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		if (answer == 1)
		{
			return -1;
		}
		return answer;
	}

	closeGPRS_HTTP_FTP_connection(n_conf);

	return 1;
}
#endif

#if HTTP_FUSE

/* readURL(const char*, uint8_t) - access to the specified URL and stores the info read in 'buffer_GPRS' variable
 *
 * This function access to the specified URL and stores the info read in 'buffer_GPRS' variable
 *
 * Returns '1' on success and '0' if error, '-2' if error opening the connection,'-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service, '-10' if error initializing the HTTP service with CME error code available,
 * '-5' if error setting CID the HTTP service, '-11' if error setting CID the HTTP service with CME error code available,
 * '-6' if error setting the url the HTTP service, '-12' if error setting the url the HTTP service with CME error code available,
 * '-7' if error starting HTTP sesion, '-13' if error starting HTTP sesion with CME error code available,
 * '-8' if error getting data from url, '-14' if error getting data from url with CME error code available,
 * '-9' if error closing the HTTP service, '-15' if error closing the HTTP service with CME error code available,
 * '2' if buffer_GPRS is full. The answer from the server is limited by the length of buffer_GPRS. To increase the length
 * of the answer, increase the BUFFER_SIZE constant.
 */
int8_t WaspGPRS_Pro::readURL(const char* url, uint8_t n_conf){
		return (readURL(url, NULL, 0, n_conf));
}

/* readURL(const char*, uint8_t, int, uint8_t) - access to the specified URL and stores the info read in 'buffer_GPRS' variable
 *
 * This function access to the specified URL and stores the info read in 'buffer_GPRS' variable
 *
 * Returns '1' on success and '0' if error, '-2' if error opening the connection,'-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service, '-10' if error initializing the HTTP service with CME error code available,
 * '-5' if error setting CID the HTTP service, '-11' if error setting CID the HTTP service with CME error code available,
 * '-6' if error setting the url the HTTP service, '-12' if error setting the url the HTTP service with CME error code available,
 * '-7' if error starting HTTP sesion, '-13' if error starting HTTP sesion with CME error code available,
 * '-8' if error getting data from url, '-14' if error getting data from url with CME error code available,
 * '-9' if error closing the HTTP service, '-15' if error closing the HTTP service with CME error code available,
 * '2' if buffer_GPRS is full. The answer from the server is limited by the length of buffer_GPRS. To increase the length
 * of the answer, increase the BUFFER_SIZE constant.
 */
int8_t WaspGPRS_Pro::readURL(const char* url, uint8_t* data, int length, uint8_t n_conf){
	
	char command[30];
	uint8_t answer=0,i=0;
	char aux;
	long HTTP_data, previous;
	uint16_t counter=0;
	
	
	sprintf(buffer_GPRS, "%s1,%u", AT_GPRS_CFG, n_conf); // Opens connection
	counter=10;
    do{
        counter--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (counter != 0));
    if (counter == 0)
	{
        return -2;
    }

	sprintf(buffer_GPRS, "%s2,%u\r\n", AT_GPRS_CFG, n_conf); // Gets IP address
	counter=10;
    do{
		previous=millis();
        counter--;
        answer=sendCommand1(buffer_GPRS, "+SAPBR: 1,1,\"");
		if (answer == 1)
		{
			i=0;
			do{
				while ((!serialAvailable(_socket)) && (millis()-previous < 10000));
				IP_dir[i]=serialRead(_socket);
				i++;
			}while ((IP_dir[i-1] != '"') && (millis()-previous < 10000));
			IP_dir[i-1]='\0';
		}
    }while ((answer != 1) && (counter != 0));

    if (counter == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
        return -3;
    }
  
    
	serialFlush(_socket);
	answer=sendCommand2(AT_HTTP_INIT, OK_RESPONSE, ERROR_CME); // Initializes HTTP service
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == 2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -10;
	}
	
	sprintf(buffer_GPRS, "%s\"%s\",%u", AT_HTTP_PARAM, "CID", n_conf); // Sets HTTP values
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -11;
	}
	
	sprintf(buffer_GPRS, "AT%s\"%s\",\"%s", AT_HTTP_PARAM, "URL", url);
	counter=strlen(buffer_GPRS);
	for(int x=0; x < counter; x++)
	{
		printByte(buffer_GPRS[x], _socket);
	}
	for(int x=0; x < length; x++)
	{
		printByte(data[x], _socket);
	}
	printByte('"', _socket);
	printByte('\r', _socket);
	printByte('\n', _socket);
	
	answer=waitForData(OK_RESPONSE, ERROR_CME, DEFAULT_TIMEOUT, 0, 0);
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -12;
	}
	
	sprintf(buffer_GPRS, "%s0", AT_HTTP_ACTION); // Starts HTTP sesion
	answer=sendCommand2(buffer_GPRS, AT_HTTP_ACTION_R, ERROR_CME, 3000, 0);
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -13;
	}	
		
	while (serialAvailable(_socket) != 0)
	{
		serialRead(_socket);
	}	
	
	counter=0;
	do{
		sprintf(command, "%s=%u,100", AT_HTTP_READ, counter); // Reads url data
		answer=sendCommand2(command, AT_HTTP_READ_R, ERROR_CME, 2000, 0);
		if (answer == 0)
		{
			closeHTTP();
			closeGPRS_HTTP_FTP_connection(n_conf);
			return -8;
		}
		else if (answer == 2)
		{
			closeHTTP();
			closeGPRS_HTTP_FTP_connection(n_conf);
			return -14;
		}
		
		// Gets the length of the data string
		HTTP_data=0;
		aux=serialRead(_socket);
		previous=millis();
		do{ 
			HTTP_data*=10;
			HTTP_data+=aux-0x30;
			aux=serialRead(_socket);
		}while ((aux != '\r') && (millis()-previous < 2000));
		
		#if GPRS_debug_mode>0
			USB.print(F("HTTP data: "));
			USB.println(HTTP_data, DEC);
		#endif
		
		serialRead(_socket);
		
		previous=millis();
		while ((serialAvailable(_socket) < HTTP_data) && (millis()-previous < 10000));
		
		aux=0;
		previous=millis();
		do{	//gets the length of the data string
			if (counter < BUFFER_SIZE)
			{
				buffer_GPRS[counter]=serialRead(_socket);
				counter++;
			}
			else
			{ 
				serialRead(_socket);
			}			
			aux++;
		}while ((aux < HTTP_data) && (millis()-previous < 10000));
		waitForData("OK", 20, 0, 0);
	
	}while ((HTTP_data == 100) && (counter < BUFFER_SIZE) && (millis()-previous < 10000));
	
	if (counter < BUFFER_SIZE)
	{
		buffer_GPRS[counter] = '\0';
	}
	else
	{
		buffer_GPRS[counter - 1] = '\0';
	}
	
	closeHTTP();		
	
	closeGPRS_HTTP_FTP_connection(n_conf);
	
	if (counter >= BUFFER_SIZE)
	{
		return 2;
	}
	
	return 1;
}

#endif

/* getcurrentOperator() - Gets the currently selected operator from network
 *
 * This function gets the currently selected operator from network and stores it in 'operator_name'
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::getcurrentOperator(){
	
	uint8_t answer=0;
	int i;
	long previous;
	
	serialFlush(_socket);
	
	answer=sendCommand2(AT_GET_OPERATOR, AT_GET_OPERATOR_R, ERROR_CME);
	if (answer == 1)
	{
		previous=millis();
		while ((serialRead(_socket) != '"') && (millis()-previous < 10000));
		i=0;
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000));
			buffer_GPRS[i]=serialRead(_socket);
			i++;
		}while ((buffer_GPRS[i-1] != '"') && (millis()-previous < 10000));
		buffer_GPRS[i-1]='\0';
		
		return 1;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return 0;
}

/* getAvailableOperators() - Gets the currently available operators from network
 *
 * This function gets the currently available operators from network and stores it in 'operators_list'
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::getAvailableOperators(){
	
	uint8_t answer=0;
	int i,j,aux;
	long previous;
	
	serialFlush(_socket);
	
	answer=sendCommand2(AT_OPERATOR_LIST, AT_OPERATOR_LIST_R, ERROR_CME);
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	
	
	previous=millis();
	j=0;
	do{
		while ((serialRead(_socket) !=  ',') && ((millis()-previous)< 10000)); // Gets format used
		i=0;
		aux=serialRead(_socket);
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000));
			operators_list[j].format=aux-0x30;
			aux=serialRead(_socket);
		}while ((aux != ',') && (millis()-previous < 10000));
		while ((serialRead(_socket)!='"') && (millis()-previous < 10000)); // Gets operator name
		i=0;
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000));
			operators_list[j].operator_name[i]=serialRead(_socket);
			i++;
		}while ((operators_list[j].operator_name[i-1] != '"') && (millis()-previous < 10000));
		operators_list[j].operator_name[i-1]='\0';
		j++;
	}while ((waitForData("OK", AT_OPERATOR_LIST_R, 20, 0, 0) == 2)  && (millis()-previous < 10000) && (j < 5));
	
	return 1;	
}


/* setPreferredOperator(int, uint8_t, const char*) - Sets the preferred operator in the operators list into GPRS module
 *
 * This function sets the preferred operator in the operators list into GPRS module
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::setPreferredOperator(int index, uint8_t format, const char* preferred_operator){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u,%u,\"%s\"", AT_SET_PREF_OPERATOR, index, format, preferred_operator);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	return answer;
}

/* getCellInfo() - gets the information from the cell where the module is connected
 *
 * This function gets the information from the cell where the module is connected
 *
 * It stores in 'RSSI' and 'cellID' variables the information from the cell
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro::getCellInfo(){
	
	unsigned long previous=millis();
	uint8_t counter=0;
	uint8_t a,b=0;
	int answer=0;
	

	sprintf(buffer_GPRS, "%s=1", AT_GPRS_CELLID);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return 0;
	}
	
	serialFlush(_socket);
	sprintf(buffer_GPRS, "AT%s?\r\n", AT_GPRS_CELLID);
	printString(buffer_GPRS, _socket);
	
	while ( (!serialAvailable(_socket)) && ((millis()-previous) < 3000) );
	previous=millis();
	a=0;
	while ( (millis()-previous) < 2000 )
	{
		while ((serialAvailable(_socket) && (millis()-previous) < 2000) && (a < 200))
		{
			buffer_GPRS[a]=serialRead(_socket);
			a++;
		}
	}
	
	a=0;
	
	counter=0;
	while ( counter < 8 )
	{
		while ((buffer_GPRS[a] != ',') && (a < 200))
		{
			a++;
		}
		a++;
		counter++;
	}
	// Gets cellID
	b=0;
	while ((buffer_GPRS[a] != ',') && (a < 200))
	{
		cellID[b]=buffer_GPRS[a];
		a++;
		b++;
	}
	a++;
	cellID[b]='\0';
	
	sprintf(buffer_GPRS, "%s=0", AT_GPRS_CELLID);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return 0;
	}
	
	
	answer=sendCommand2(AT_GPRS_RSSI, AT_GPRS_RSSI, ERROR_CME);
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	
	RSSI=0; // Gets RSSI value, converts it from ASCII to -dBm
	
	previous=millis();
	while ((serialRead(_socket) != ' ') && ((millis()-previous) < 3000));
	
	b=serialRead(_socket);
	previous=millis();
	
	do{
		RSSI*=10;
		RSSI+=(b-0x30);
		b=serialRead(_socket);
	}while ((b != ',') && ((millis()-previous) < 3000));
	
	#if GPRS_debug_mode>0
		USB.print(F("Raw RSSI: "));
		USB.println(RSSI, DEC);
	#endif
	
	switch(RSSI)
	{
		case 0:
			RSSI= -115;
			break;
			
		case 1:
			RSSI= -111;
			break;
			
		case 31:
			RSSI= -52;
			break;
			
		case 99:
			RSSI= 0;
			break;
			
		default:
			RSSI= ((RSSI - 2) * 2) - 110;
	}
	
	#if GPRS_debug_mode>0
		USB.print(F("Processed RSSI: "));
		USB.println(RSSI, DEC);
	#endif

	return 1;
}

#if IP_FUSE
//TCP and UDP functions
/* configureGPRS_TCP_UDP(uint8_t) - configures GPRS connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a GPRS connection with the carrier server to get access to the internet
 *
 * Returns '1' on success, '0' if error, '-2' if error dettaching the GPRS connection, 
 * '-3' if error attaching the GPRS connection, '-4' if error setting the application mode,
 * '-5' if error setting the connection mode, '-6' if error establishing the connection with the GPRS provider, 
 * '-15' if error dettaching the GPRS connection with CME error code available, 
 * '-16' if error attaching the GPRS connection with CME error code available.
*/
int8_t WaspGPRS_Pro::configureGPRS_TCP_UDP(uint8_t mode){
	return( configureGPRS_TCP_UDP(mode, 0));
}

/* configureGPRS_TCP_UDP(uint8_t, uint8_t) - configures GPRS connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a GPRS connection with the carrier server to get access to the internet
 *
 * Returns '1' on success, '0' if error, '-2' if error dettaching the GPRS connection, 
 * '-3' if error attaching the GPRS connection, '-4' if error setting the application mode,
 * '-5' if error setting the connection mode, '-6' if error establishing the connection with the GPRS provider, 
 * '-15' if error dettaching the GPRS connection with CME error code available,
 * '-16' if error attaching the GPRS connection with CME error code available
*/
int8_t WaspGPRS_Pro::configureGPRS_TCP_UDP(uint8_t mode, uint8_t app_mode){
	
	uint8_t answer=0;
	uint8_t count;
	uint8_t state;
	long previous;
	
	for (count = 0; count < 16; count++)
	{
		IP_dir[count] = '\0';
	}
	
	
	// First restart TCP/UDP connection
	
	state=checkIPstatus(); // Checks the GPRS state to send the correct shutdown order
	
	count=10;
	
	if (checkGPRS() == 1) // Dettachs GPRS
	{	
		do{
			answer=sendCommand2(AT_GPRS_ATT_OFF, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((count != 0) && (answer != 1));
		
		if(answer == 0)
		{
			return -2;
		}
		else if(answer == 2)
		{
			return -15;
		}
	}	
	
	
	
	// Attaching...
	count=10;
	do{
		answer=sendCommand2(AT_GPRS_ATT_ON, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((count != 0) && (answer != 1));
	if(answer == 0)
	{
		return -3;
	}
	else if(answer == 2)
	{
		return -16;
	}
	
	previous = millis();
	while ((checkGPRS() != 1) && ((millis() - previous) < 60000));
	
	if ((millis() - previous) > 60000)
	{
		return -17;
	}
	
	// Set the application mode: transparent or not transparent
	if (app_mode == 0)
	{
		sprintf(buffer_GPRS, "%s0", AT_IP_APP_MODE);
	}
	else
	{
		sprintf(buffer_GPRS, "%s1", AT_IP_APP_MODE);

	}
	
	count=10;
	do{
		answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
		count--;
	}while ((count != 0) && (answer != 1));
	if(answer == 0)
	{
		return -4;
	}
	
	IP_app_mode=app_mode;
	
	// Now it must be in state 1: IP INITIAL
	
	// Sets the connection mode: single or multiple
	switch (mode)
	{
		case 0:
			answer=sendCommand1(AT_SINGLE_CONN, OK_RESPONSE);
			break;
		case 1:
			answer=sendCommand1(AT_MULTI_CONN, OK_RESPONSE);
			break;
	}
	if(answer == 0)
	{
		return -5;
	}

	IP_mode=mode;
	
	
	count=10;
	state=checkIPstatus();
	
	do{
		switch (state) // Here, 'answer' contains the IP state
		{
			case 1: // Sets apn, username and password for IP connection
				sprintf(buffer_GPRS, "%s\"%s\",\"%s\",\"%s\"",AT_IP_SET_APN, AT_GPRS_APN, AT_GPRS_LOGIN, AT_GPRS_PASSW);
				answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
				break;
			case 2: // Brings up wireless connection	
				answer=sendCommand1(AT_IP_BRING, OK_RESPONSE);
				break; 
			case 3:
				delay(500);
				count--;
				break;
			case 4: // Gets IP direction
				answer=getIP();
				break;
			default:
				delay(500);
				count--;
				break;
		}
	
		if (answer != 1) //here, answer contains the response from the module
		{
			count--;
		}
		
		state=checkIPstatus();
	}while ((count != 0) && (state != 5));
	
	if ((count == 0) || (IP_dir[0] == '\0'))
	{
		return -6;
	}
	else
	{
		return 1;
	}
}

/* setLocalPort(const char*, uint16_t) - Sets the number of the internal port for TCP or UDP connections
 *
 * This function sets the number of the internal port for TCP or UDP connections
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::setLocalPort(const char* mode, uint16_t port){
		
	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s\"%s\",%u", AT_IP_LOCAL_PORT, mode, port);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
	
}

/* saveGPRS_TCP_UDPconfiguration() - Saves the configuration into the internal NVRAM of the GPRS module
 *
 * This function saves the configuration into the internal NVRAM of the GPRS module
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::saveGPRS_TCP_UDPconfiguration(){
	return( sendCommand1(AT_IP_SAVE_CONF, OK_RESPONSE));
}

/* createSocket(uint8_t, const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro::createSocket( uint8_t working_mode, const char* port){
	return( createSocket( working_mode, 0, 0, port));
}

/* createSocket(uint8_t, const char*,const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro::createSocket( uint8_t working_mode, const char* ip,const char* port){
	return( createSocket( working_mode, 0, ip, port));
}

/* createSocket(uint8_t, uint8_t, const char*, const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro::createSocket( uint8_t working_mode, uint8_t n_connection, const char* ip, const char* port){
	
	uint8_t answer=0;
	
	switch (IP_mode)
	{
		case 0: // Single mode
			switch (working_mode)
			{
				case UDP_CLIENT:
					sprintf(buffer_GPRS, "%s0", AT_IP_UDP_EXTENDED);
					answer|=sendCommand1(buffer_GPRS, OK_RESPONSE);
					sprintf(buffer_GPRS, "%s\"%s\",\"%s\",\"%s\"", AT_IP_CLIENT, AT_UDP, ip, port);
					answer|=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_CLIENT:
					sprintf(buffer_GPRS, "%s\"%s\",\"%s\",\"%s\"", AT_IP_CLIENT, AT_TCP, ip, port);
					answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_SERVER:
					sprintf(buffer_GPRS, "%s1,\"%s\"", AT_IP_SERVER, port);
					answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
					break;
				case UDP_EXTENDED:
					sprintf(buffer_GPRS, "%s1", AT_IP_UDP_EXTENDED);
					answer|=sendCommand1(buffer_GPRS, OK_RESPONSE);
					sprintf(buffer_GPRS, "%s\"%s\",\"%s\",\"%s\"", AT_IP_CLIENT, AT_UDP, ip, port);
					answer|=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					sprintf(buffer_GPRS, "%s2,\"%s\",\"%s\"", AT_IP_UDP_EXTENDED, ip, port);
					answer|=sendCommand1(buffer_GPRS, OK_RESPONSE);	
					break;
			}
			break;
			
		case 1: // Multi mode	
			switch (working_mode)
			{
				case UDP_CLIENT:
					sprintf(buffer_GPRS, "%s%u,\"%s\",\"%s\",\"%s\"", AT_IP_CLIENT, n_connection, AT_UDP, ip, port);
					answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_CLIENT:
					sprintf(buffer_GPRS, "%s%u,\"%s\",\"%s\",\"%s\"", AT_IP_CLIENT, n_connection, AT_TCP, ip, port);
					answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_SERVER:
					sprintf(buffer_GPRS, "%s1,\"%s\"", AT_IP_SERVER, port);
					answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
					break;
			}
			break;
	}
	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)	
	{
		return -2;
	}
	
	if (working_mode < 2)
	{
		// Waits 20 seconds to connect
		if (IP_app_mode == 0)
		{
			answer=waitForData(AT_CONNECTED_OK, AT_CONNECTED_FAIL, 2000, 0, 5);
		}
		else
		{
			answer=waitForData("CONNECT\r\n", AT_CONNECTED_FAIL, 2000, 0, 5);
		}
		
		if (answer == 0)
		{
			return -3;
		
		}
	}
	return 1;
}

/* sendData(const char*) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'. In single connection not specifies 'n_connection'.
 *
 * Returns '1' on success, '0' if error waiting the response of the module, '-2' if error with CME error code available
 * '-3' if no feedback detected and '-4' if the send fails
*/
int8_t WaspGPRS_Pro::sendData(const char* data){
	return( sendData((uint8_t*)data, strlen(data), NULL));
}

/* sendData(const char*, uint8_t) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'. In single connection not specifies 'n_connection'.
 *
 * Returns '1' on success, '0' if error waiting the response of the module, '-2' if error with CME error code available
 * '-3' if no feedback detected and '-4' if the send fails
*/
int8_t WaspGPRS_Pro::sendData(const char* data, uint8_t n_connection){
	return( sendData((uint8_t*)data, strlen(data), n_connection));
}

/* sendData(uint8_t*, int) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'. In single connection not specifies 'n_connection'.
 *
 * Returns '1' on success, '0' if error waiting the response of the module, '-2' if error with CME error code available
 * '-3' if no feedback detected and '-4' if the send fails
*/
int8_t WaspGPRS_Pro::sendData(uint8_t* data, int length){
	return( sendData(data, length, NULL));
}

/* sendData(uint8_t*, int, uint8_t) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'. In single connection not specifies 'n_connection'.
 *
 * Returns '1' on success, '0' if error waiting the response of the module, '-2' if error with CME error code available
 * '-3' if no feedback detected and '-4' if the send fails
*/
int8_t WaspGPRS_Pro::sendData(uint8_t* data, int length, uint8_t n_connection){

	uint8_t answer=0, count=10;
	
	if (IP_app_mode == 0)
	{
		// Non transparent mode
		switch (IP_mode){
			case 0: // Single mode
				sprintf(buffer_GPRS, "%s=%d", AT_IP_SEND, length);
				break;
			case 1: // Multi mode
				sprintf(buffer_GPRS, "%s=%c,%d", AT_IP_SEND, n_connection+0x30, length);
				break;
		}
		
		count=5;
		// Waits the connection  to send data
		do{
			answer=sendCommand2(buffer_GPRS, ">", ERROR_CME);
			count--;
		}while ((answer != 1) && (count != 0));
		
		if (answer == 0)
		{
			return 0;
		}
		else if (answer == 2)	
		{
			return -2;
		}
		
		// Sends data 
		count=5;
		
		do{
			// Sends data and waits 30 seconds for the feedback
			for(int x=0; x<length; x++)
			{
				printByte(data[x], _socket);
			}
			
			answer=waitForData(AT_IP_SEND_R, AT_IP_SEND_FAIL, 3000, 0, 0);
			count--;
		}while ((answer != 1) && (count != 0));

		if (answer == 0)
		{
			return -3;
		}
		else if (answer == 2)	
		{
			return -4;
		}
	}
	else
	{
		// Transparent mode
		for(int x=0; x<length; x++)
		{
			printByte(data[x], _socket);
		}
	}
	
	return 1;
}

/* readIPData(char*) - Gets data receive from a TCP or UDP connection and stores it in 'buffer_GPRS'
 *
 * This function gets data receive from a TCP or UDP connection and stores it in 'buffer_GPRS'.
 *
 * In multi connection mode also stores the connection number in 'IP_data_from.
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro::readIPData(char* dataIN){
	int IP_data_length=0,IP_data_from=0;
	int i=0,j;
	int8_t answer=0;
	for ( j=0; j < 255; j++)
	{
		buffer_GPRS[j]='\0';
	}
	
	if (IP_mode == 0)
	{
		// Single connection mode
		if (IP_app_mode == 0)
		{	
			// Non transparent mode
			if (strstr(dataIN, "+CIPRXGET") != NULL)
			{
				answer=GetDataManually(150, 0);
			}
			else if (strstr(dataIN, "+IPD") != NULL)
			{
				do{
					i++;
				}while (dataIN[i] != ':');
				
				do{ // Gets the length of the data string
				IP_data_length*=10;
				IP_data_length=dataIN[i];
				i++;
				}while (dataIN[i] != ',');
				
				do{
					i++;
				}while (dataIN[i] != ':');
				
				for ( j=0; j < IP_data_length; j++)
				{
					if (j < BUFFER_SIZE - 1)
					{
						buffer_GPRS[j]=dataIN[i+j];
					}					
				}
				
			}
			else
			{
					// copy dataIN to buffer_GPRS
				if (strlen(dataIN) < BUFFER_SIZE)
				{
					strcpy(buffer_GPRS, dataIN);
				}
				else
				{
					strncpy(buffer_GPRS, dataIN, BUFFER_SIZE - 2);
				}
			}
				
		}
		else
		{
			// Transparent mode
			// copy dataIN to buffer_GPRS
			if (strlen(dataIN) < BUFFER_SIZE)
			{
				strcpy(buffer_GPRS, dataIN);
			}
			else
			{
				strncpy(buffer_GPRS, dataIN, BUFFER_SIZE - 2);
			}
		}
	}
	else
	{
		// Multiconnection mode		
		if (strstr(dataIN, "+CIPRXGET") != NULL)
		{
			while (dataIN[i] != ',')
			{
				i++;
			}		
			IP_data_from=dataIN[i+1]-0x30;	// Gets the connection number
			answer=GetDataManually(150, IP_data_from);
		}
		else
		{			
			while (dataIN[i] != ',')
			{
				i++;
			}
		
			IP_data_from=dataIN[i+1]-0x30;	// Gets the connection number

			i+=3;
			IP_data_length=0;
			do{ // Gets the length of the data string
				IP_data_length*=10;
				IP_data_length=dataIN[i];
				i++;
			}while (dataIN[i] != '\r');
			i++; //skips \n
	
			for (int x=0; x < IP_data_length; x++)
			{
				buffer_GPRS[x]=dataIN[i+x];
			}
		}
	}
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* closeSocket() - closes the socket specified by 'socket'
 *
 * This function closes the connection specified by 'n_connection'.In single not specifies number of connenction. For server use 8
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::closeSocket(){
	return( closeSocket(NULL));
}

/* closeSocket(uint8_t) - closes the socket specified by 'socket'
 *
 * This function closes the connection specified by 'n_connection'.In single not specifies number of connenction. For server use 8
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::closeSocket(uint8_t n_connection){

	uint8_t answer=0;

	if (n_connection == 8)
	{
		// Closes TCP server
		sprintf(buffer_GPRS, "%s0", AT_IP_SERVER);
		answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	}
	else
	{	
		// Closes TCP or UDP client
		switch (IP_mode)
		{
			case 0: // Single mode
				sprintf(buffer_GPRS, "%s0", AT_IP_CLOSE);
				break;
			case 1: // Multiconnection mode
				sprintf(buffer_GPRS, "%s%c,0", AT_IP_CLOSE, n_connection+0x30);
				break;
		}
		 
		answer = sendCommand1(buffer_GPRS, AT_IP_CLOSE_R);
	}
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* QuickcloseSocket(socket) - Enables/disables to close the connection quickly
 *
 * This function enables/disables to close the connection quickly. 
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::QuickcloseSocket(uint8_t mode){

	uint8_t answer=0;

	switch (mode)
	{
		case 0:	
			sprintf(buffer_GPRS, "%s0", AT_IP_QCLOSE);
			break;
		case 1:
			sprintf(buffer_GPRS, "%s1", AT_IP_QCLOSE);
			break;
	}
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* getIPfromDNS(const char*) - Gets the IP direction from a URL using DNS servers
 *
 * This function gets the IP direction from a URL using DNS servers
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro::getIPfromDNS(const char* IP_query){
	
	long previous;
	char aux;
	
	sprintf(buffer_GPRS, "%s\"%s\"", AT_IP_QUERY_DNS, IP_query);
	aux = sendCommand2(buffer_GPRS, AT_IP_QUERY_DNS_R, ERROR);
	if (aux == 1)
	{
		previous = millis();
		aux = serialRead(_socket);
		if (aux == '0')
		{ 
			return 0;
		}
		aux = 0;
		while ((aux < 3) && ((millis()- previous) < 1000))
		{
			while((serialRead(_socket) != '"') && ((millis()- previous) < 1000));
			aux++;
		}
		aux=0;
		do{
			buffer_GPRS[aux]=serialRead(_socket);
			aux++;
		}while ((buffer_GPRS[aux-1] != '"') && ((millis()- previous) < 1000));
		buffer_GPRS[aux-1]='\0';
		return 1;
	}
	else
	{
		return 0;
	}
	return 1;
}

/* IPHeader(uint8_t) - Adds an IP head at the beginning of a package received
 *
 * This function adds an IP head at the beginning of a package received
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::IPHeader(uint8_t on_off){
	
	uint8_t answer=0;

	sprintf(buffer_GPRS, "%s%u", AT_IP_HEADER, on_off);
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
		
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* SetAutoSendingTimer(uint8_t) - Sets a timer when module is sending data
 *
 * This function sets a timer when module is sending data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::SetAutoSendingTimer(uint8_t mode){
	return( SetAutoSendingTimer(mode, 0));
}

/* SetAutoSendingTimer(uint8_t, uint8_t) - Sets a timer when module is sending data
 *
 * This function sets a timer when module is sending data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::SetAutoSendingTimer(uint8_t mode, uint8_t time){
	
	uint8_t answer=0;

	switch (mode)
	{
		case 0:
			sprintf(buffer_GPRS, "%s0", AT_IP_AUTOSENDING);
			break;
		case 1:
			sprintf(buffer_GPRS, "%s1,%u", AT_IP_AUTOSENDING, time);
			break;
	}
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* ShowRemoteIP(uint8_t) - Enables or disables to show remote IP address and port when received data
 *
 * This function enables or disables to show remote IP address and port when received data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::ShowRemoteIP(uint8_t on_off){
	
	uint8_t answer=0;
	sprintf(buffer_GPRS, "%s%u", AT_IP_SHOW_REMOTE_IP, on_off);
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* ShowProtocolHeader(uint8_t) - Enables or disables to show transfer protocol in IP head when received data
 *
 * This function enables or disables to show transfer protocol in IP head when received data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::ShowProtocolHeader(uint8_t on_off){

	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_IP_PROTOCOL_HEADER, on_off);
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* DiscardInputATData(uint8_t) - Enables or disables to discard input AT data in TCP data send
 *
 * This function enables or disables show to discard input AT data in TCP data send
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::DiscardInputATData(uint8_t on_off){
	
	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s%u", AT_IP_DISCARD_AT_DATA, on_off);
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);	

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* SetDataManually(uint8_t) - Enables or disables to get data manually from a TCP or UDP connection
 *
 * This function enables or disables show to get data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::SetDataManually(uint8_t on_off){
	return SetDataManually(on_off, 0);
}

/* SetDataManually(uint8_t, uint8_t) - Enables or disables to get data manually from a TCP or UDP connection
 *
 * This function enables or disables show to get data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::SetDataManually(uint8_t on_off, uint8_t id){

	uint8_t answer=0;
	
	if (IP_mode == 0)
	{
		sprintf(buffer_GPRS, "%s=%u", AT_IP_GET_MANUALLY, on_off);
	}
	else
	{
		sprintf(buffer_GPRS, "%s=%u,%u", AT_IP_GET_MANUALLY, on_off, id);
	}
	
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);
	
	if (answer != 1)
	{
		return 0;
	}
	
	return 1;
}

/* GetDataManually(uint16_t) - Gets data manually from a TCP or UDP connection
 *
 * This function gets data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::GetDataManually(uint16_t data_length){
	return GetDataManually(data_length, 0);
}

/* GetDataManually(uint16_t, uint8_t) - Gets data manually from a TCP or UDP connection
 *
 * This function gets data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error and '2' if buffer_GPRS is full. The answer from the server is 
 * limited by the length of buffer_GPRS. To increase the length of the answer, increase the BUFFER_SIZE constant.
*/
int8_t WaspGPRS_Pro::GetDataManually(uint16_t data_length, uint8_t id){

	uint8_t answer=0;
	uint8_t i=0,IP_data_length;
	char aux;
	long previous;
	
	
	if (IP_mode == 0)
	{
		sprintf(buffer_GPRS, "%s=2,%u", AT_IP_GET_MANUALLY, data_length);
	}
	else
	{
		sprintf(buffer_GPRS, "%s=2,%u,%u", AT_IP_GET_MANUALLY, id, data_length);
	}
	answer = sendCommand2(buffer_GPRS, "+CIPRXGET=2,", ERROR);
	
	switch (answer)
	{
		case 0:
			return 0;
			break;
		case 1:	
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
			}while ((serialRead(_socket) != ':') && ((millis() - previous) < 10000));
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
			}while ((serialRead(_socket) != ',') && ((millis() - previous) < 10000));
			
			if (IP_mode == 1)
			{
				do{
					while((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
				}while ((serialRead(_socket) != ',') && ((millis() - previous) < 10000));
			}
			
			// Gets the length of the data string
			IP_data_length=0;
			aux=serialRead(_socket);
			do{
				IP_data_length*=10;
				IP_data_length+=(aux-0x30);
				aux=serialRead(_socket);
			}while ((aux != ',') && ((millis() - previous) < 10000));
		
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
			}while ((serialRead(_socket) != '\n') && ((millis() - previous) < 10000));
		
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
				if (i < BUFFER_SIZE)
				{
					buffer_GPRS[i] = serialRead(_socket);
				}
				else
				{
					serialRead(_socket);
				}
				i++;
			}while ((i < (IP_data_length-1)) && ((millis() - previous) < 10000));
			
			buffer_GPRS[BUFFER_SIZE - 1] = '\0';
			
			break;
			
		case 2:
			return 0;
			break;
	}
	
	if (i >= BUFFER_SIZE)
	{
		return 2;
	}
	
	return 1;
}
#endif

/* setDNS() - Sets the directions of DNS servers from GPRS_Proconstants.h
 *
 * This function sets the directions of DNS servers from GPRS_Proconstants.h
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
uint8_t WaspGPRS_Pro::setDNS(){
	
	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s\"%s\",\"%s\"", AT_IP_SET_DNS, AT_GPRS_DNS1, AT_GPRS_DNS2);

	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
		
	return answer;
}

/* setDNS(const char*) - Sets the direction of DNS server
 *
 * This function sets the direction of DNS server
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
uint8_t WaspGPRS_Pro::setDNS(const char* DNS_dir){
	
	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s\"%s\"", AT_IP_SET_DNS, DNS_dir);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
		
	return answer;
}

/* setDNS(const char*, const char*) - Sets the directions of DNS servers
 *
 * This function sets the directions of DNS servers
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
uint8_t WaspGPRS_Pro::setDNS(const char* DNS_dir1, const char* DNS_dir2){
	
	uint8_t answer=0;
	
	sprintf(buffer_GPRS, "%s\"%s\",\"%s\"", AT_IP_SET_DNS, DNS_dir1, DNS_dir2);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;
}

/* whoamI() - Gets the model of the module
 *
 * This function gets the model of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::whoamI(){
	int8_t answer, x;
	long previous;
	
	// Sends the command:
	answer=sendCommand1(AT_WHO_AM_I, "\r\n");

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_GPRS[x]=serialRead(_socket);
			x++;
		}while ((buffer_GPRS[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_GPRS[x-1]='\0';
	}
	
	return answer;

}

/* firmware_version() - Gets the firmware version of the module
 *
 * This function gets the firmware version of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro::firmware_version(){
	int8_t answer, x;
	long previous;
	
	// Sends the command:
	answer=sendCommand1(AT_FIRMWARE, AT_FIRMWARE_R);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_GPRS[x]=serialRead(_socket);
			x++;
		}while ((buffer_GPRS[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_GPRS[x-1]='\0';
	}
	
	return answer;

}

/* show_APN() - Shows the apn, login and password constants
 *
 * This function shows the apn, login and password constants
 *
 * Returns nothing
*/
void WaspGPRS_Pro::show_APN(){
	// APN parameters depends on SIM
	USB.print(F("APN: "));
	USB.println(AT_GPRS_APN);
	USB.print(F("LOGIN: "));
	USB.println(AT_GPRS_LOGIN);
	USB.print(F("PASSWORD: "));
	USB.println(AT_GPRS_PASSW);
} 

#if OTA_FUSE
/* requestOTA(const char*, const char*, const char*, const char*) - It downloads a new OTA file if OTA is necessary
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns '1' if success, '-2' if error and '-4' if error setting the type of internet connection, 
 * '-5' if error setting the apn, '-6' if error setting the user name, '-7' if error setting the password
 * '-8' if error saving the configuration, '-9' if error opening connection with the GPRS provider, '-10' error downloading OTA version file, '-11' if error getting the IP address
 * '-12' if error setting the FTP/HTTP ID, '-13' if error setting the FTP mode, '-14' if error setting the FTP type,
 * '-15' if error setting the FTP server, '-16' if error setting the FTP port, '-17' if error setting the user name,
 * '-18' if error setting the password, '-21' if error setting the file name in the FTP server, 
 * '-22' if error setting the path of the file in the FTP server, '-23' if error opening the FTP session,
 * '-24' if error starting the SD, '-25' if error creating the file, '-26' error requesting data to the FTP,
 * '-27' if error saving data into the SD, '-28' if error requesting more data to the FTP, '-30' setting the file name in the FTP to get the file size
 * '-31' setting the path in the FTP to get the file size, '-32' if error getting the file size
 * '-50' if error setting the FTP/HTTP ID with CME error code available, '-51' if error setting the FTP mode with CME error code available,
 * '-52' if error setting the FTP type with CME error code available, '-53' if error setting the FTP server with CME error code available,
 * '-54' if error setting the FTP port with CME error code available, '-55' if error setting the user name with CME error code available,
 * '-56' if error setting the password with CME error code available, '-57' if error setting the file name in the FTP server with CME error code available,
 * '-58' if error setting the path of the file in the FTP server with CME error code available, '-59' if error opening the FTP session with CME error code available,
 * '-60' if error requesting data to the FTP with CME error code available, '-61' if error requesting more data to the FTP with CME error code available,
 * '-62 setting the file name in the FTP to get the file size with CME error code available,
 * '-63' setting the path in the FTP to get the file size with CME error code available, '-64' if error getting the file size with CME error code available,
 * '-65' if FTP is busy, '-66' if there isn't FILE tag, '-67' if there isn't PATH tag, '-68' if there isn't VERSION tag,'-69' if OTA is not necessary, 
 * '-70' if OTA files are the same program version, '-71' if error opening connection with the GPRS provider, '-72' error downloading OTA file, '-73' if error getting the IP address
 * '-74' if error setting the FTP/HTTP ID, '-75' if error setting the FTP mode, '-76' if error setting the FTP type,
 * '-77' if error setting the FTP server, '-78' if error setting the FTP port, '-79' if error setting the user name,
 * '-80' if error setting the password, '-83' if error setting the file name in the FTP server, 
 * '-84' if error setting the path of the file in the FTP server, '-85' if error opening the FTP session,
 * '-86' if error starting the SD, '-87' if error creating the file, '-88' error requesting data to the FTP,
 * '-89' if error saving data into the SD, '-90' if error requesting more data to the FTP, '-92' setting the file name in the FTP to get the file size
 * '-93' setting the path in the FTP to get the file size, '-94' if error getting the file size
 * '-112' if error setting the FTP/HTTP ID with CME error code available, '-113' if error setting the FTP mode with CME error code available,
 * '-114' if error setting the FTP type with CME error code available, '-115' if error setting the FTP server with CME error code available,
 * '-116' if error setting the FTP port with CME error code available, '-117' if error setting the user name with CME error code available,
 * '-118' if error setting the password with CME error code available, '-119' if error setting the file name in the FTP server with CME error code available,
 * '-120' if error setting the path of the file in the FTP server with CME error code available, '-121' if error opening the FTP session with CME error code available,
 * '-122' if error requesting data to the FTP with CME error code available, '-123' if error requesting more data to the FTP with CME error code available,
 * '-124' setting the file name in the FTP to get the file size with CME error code available,
 * '-125' setting the path in the FTP to get the file size with CME error code available, '-126' if error getting the file size with CME error code available
 * and '-127' if FTP is busy
*/
int8_t WaspGPRS_Pro::requestOTA(const char* FTP_server, const char* FTP_port, const char* FTP_username, const char* FTP_password){

	int8_t answer;
	char aux_ver[4];
	uint8_t version;
	char* str_pointer;
	char aux_name[8];
	char programID[8];
	char* path = (char*) calloc(60, sizeof(char));
	if ( path == NULL )
	{
		return -1;
	}
	
	SD.ON();
	SD.goRoot();
	SD.del(OTA_ver_file);
	SD.OFF();
	answer = configureGPRS_HTTP_FTP(1);
	if (answer == 1)
	{
		#if GPRS_debug_mode>0
			USB.println(F("Downloading OTA VER FILE"));
		#endif
		sprintf(path, ".gprs%s", OTA_ver_file);
		answer = downloadFile(path, OTA_ver_file, FTP_username, FTP_password, FTP_server, FTP_port, 1);
		if (answer == 1)
		{

			SD.ON();
			SD.goRoot();
			
			// Reads the file
			strcpy(buffer_GPRS, SD.cat(OTA_ver_file, 0, BUFFER_SIZE));
			// Searchs the file name
			str_pointer = strstr(buffer_GPRS, "FILE:");
			if (str_pointer != NULL)
			{	
				
				strncpy(aux_name, strchr(buffer_GPRS, ':') + 1, 7);
				aux_name[7] = '\0';
				
				#if GPRS_debug_mode>0
					USB.print(F("OTA file: "));
					USB.println(aux_name);	
				#endif
				// Searchs the file name
				str_pointer = strstr(buffer_GPRS, "PATH:");
				if (str_pointer != NULL)
				{
					strncpy(path, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));
					
					path[strchr(path, '\n') - path] = '\0';
					
					#if GPRS_debug_mode>0
						USB.print(F("File path: "));
						USB.println(path);
					#endif
					strcat(path,"/");
					strcat(path,aux_name);
					
					str_pointer = strstr(buffer_GPRS, "VERSION:");
					
					if (str_pointer != NULL)
					{
					
						strncpy(aux_ver, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));					
						aux_ver[strchr(aux_ver, '\n') - aux_ver] = '\0';
						
						version = atoi(aux_ver);
						
						#if GPRS_debug_mode>0
							USB.print(F("Version: "));
							USB.println(version, DEC);
						#endif
					
						SD.del(aux_name);
		
						if (strcmp(aux_name, NO_OTA) != 0)
						{
							#if GPRS_debug_mode>0
								USB.println(F("Downloading OTA FILE"));
							#endif
							
							Utils.getProgramID(programID);
							// check if the program have a new version or if it is a different code
							if (((strcmp(aux_name, programID) == 0) && (version > Utils.getProgramVersion())) || (strcmp(aux_name, programID) != 0))
							{
								sprintf(buffer_GPRS, ".gprs%s", path);
								strcpy(path, buffer_GPRS);
								answer = downloadFile(path, aux_name, FTP_username, FTP_password, FTP_server, FTP_port, 1);
								if (answer == 1)
								{
									#if GPRS_debug_mode>0
										SD.ON();
										SD.ls();
										SD.OFF();
									#endif
									Utils.loadOTA(aux_name, version);
									free(path);
									return 1;
								}
								else
								{
									
									SD.OFF();
									free(path);
									return answer - 71;
								}
							}
							else
							{
								#if GPRS_debug_mode>0
									USB.println(F("Same program version, no OTA required"));
								#endif
								SD.OFF();
								free(path);
								return -70;
							}
						}
						else
						{
							
							#if GPRS_debug_mode>0
								USB.println(F("No OTA"));
							#endif
							SD.OFF();
							free(path);
							return -69;
						}
					}
					else
					{
						SD.OFF();
						free(path);
						return -68;
					}
				}
				else
				{
					SD.OFF();
					free(path);
					return -67;
				}
					
			}
			else
			{
				SD.OFF();
				free(path);
				return -66;
			}
		}
		else
		{
			free(path);
			return answer - 9;
		}
	}
	else
	{	
		free(path);
		return answer - 2;
	}
	
	return 0;

}

#endif
// Preinstantiate Objects //////////////////////////////////////////////////////

WaspGPRS_Pro GPRS_Pro = WaspGPRS_Pro();
