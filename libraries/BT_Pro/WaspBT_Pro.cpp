/*
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		0.100
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */

#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspBT_Pro.h"

// Private Methods //

/*
 Function: Reads discovered devices from UART and saves them into specific array.
 Returns: '1' on success, '0' error parsing block, '-1' error parsing names, '-2' maybe device lost, '-3' error writting SD
 Parameters: 
	inquiryTime: wait for module answer during this time.
	MAX_DEVICES: Maximum number of deviced to discover.
	name: Enables friendly name scan.
	limit: Enables limited scan.
 Values: 
*/
int8_t  WaspBT_Pro::waitInquiryAnswer(long inquiryTime, uint16_t MAX_DEVICES, bool name, bool limited) 
{
	delay(100);
	uint8_t flag =1;
	char dummy[4];							// Keyword
	char block[BLOCK_SIZE+1];				// Block with MAC, CoD y RSSI
	char number[4];
	bool totalFound=false;
	char total[4];	
	total[3]='\0';
	int a;
		
	Utils.setLED(LED1, LED_ON);  // Inquiry while led on
    	
	long previous=millis();
	while( (millis()-previous<inquiryTime) && numberOfDevices < MAX_DEVICES ) 
	{
		for(uint8_t zz=0;zz<BLOCK_SIZE;zz++) block[zz]='\0';	// Clear array
	
		// Looks for keyword and save device.		
		if (serialAvailable(_uartBT))	
		{
			dummy[0]=serialRead(_uartBT);	
			if (dummy[0]=='I')
			{
				while(serialAvailable(_uartBT)<2);
				dummy[1]=serialRead(_uartBT);	
				if (dummy[1]=='A')
				{
					dummy[2]=serialRead(_uartBT);	
					if (dummy[2]=='L')
					{
						while(serialAvailable(_uartBT)<BLOCK_SIZE);
						for(uint8_t x=0;x<BLOCK_SIZE;x++) block[x]= serialRead(_uartBT);	
						// Saves device
						if (!(parseBlock(block))) flag=0;						
						numberOfDevices++;
						#ifdef DEBUG_MODE
						printBuffer2();
						#endif
					}
				}
			}
			// Search inquiry end
			if ((dummy[0]=='Y')&&(!totalFound))
			{ 
				while(serialAvailable(_uartBT)<2);
				dummy[1]=serialRead(_uartBT);	
				if (dummy[1]==' ')
				{
					// If here, total found.
					totalFound=true;
					while(serialAvailable(_uartBT)<3);
					total[0]=serialRead(_uartBT);
					total[1]=serialRead(_uartBT);
					total[2]=serialRead(_uartBT);
				}
			}
		}

	// Condition to avoid an overflow (DO NOT REMOVE)
    	if( millis()-previous < 0 ) previous=millis();
	}
	#ifdef ENABLE_FRIENDLY_NAME
	// If name, parse names
	if (name) 
	{
		if(!(parseNames())) flag=-1;
	}
	#endif

	if (!limited)
	{
		sprintf(number, "%02u", numberOfDevices);
		#ifdef DEBUG_MODE
		// Compare total of devices found and total of devices saved. 
		
		// convert from string to int
		a = atoi(total);
		
		if (a!=numberOfDevices)
		{
			USB.println(F("+Maybe dev lost+"));
			flag = -2;
		}
			USB.print(F("inquiried:"));
			USB.print(a);
			USB.print(F("; saved:"));
			USB.println(number);
		#endif

		if(!(SD.append(INQFILE,TOTAL)))
		{
			#ifdef DEBUG_MODE
			USB.print(F(ERRORSD1));
			#endif
			flag = -3;
		}
		
		if(!(SD.appendln(INQFILE,number)))
		{
			#ifdef DEBUG_MODE
			USB.println(F(ERRORSD1));
			#endif
			flag = -3;
		}
		numLinesAfter++;
	}
    	Utils.setLED(LED1, LED_OFF);  // Inquiry while led on
   	
   	return flag;
}

/*
 Function: Parses module answer trying to find specified MAC, stops inquiry when mac is found. if device is found, saved on position 0
 Returns: Returs 1 if found. 0 if not found.
 Parameters: 
	inquiryTime: wait for module answer during this time.
	mac: mac of desired device.
 Values: 
*/
bool  WaspBT_Pro::waitScanDeviceAnswer(long inquiryTime, char* mac) 
{
	delay(100);
	char dummy[4];						
	bool found = false;
	char * block;
	block = (char*)calloc(BLOCK_SIZE+1,sizeof(char));

	Utils.setLED(LED1, LED_ON);  // Inquiry while led on
    	
	long previous=millis();
	while( (millis()-previous<inquiryTime) && (!found) ) 
	{
		// Looks for keyword and save device.		
		if (serialAvailable(_uartBT))	
		{
			dummy[0]=serialRead(_uartBT);
			delay(50);
			if (dummy[0]=='I')
			{
				dummy[1]=serialRead(_uartBT);	
				delay(50);
				if (dummy[1]=='A')
				{
					dummy[2]=serialRead(_uartBT);	
					if (dummy[2]=='L')
					{
						while(serialAvailable(_uartBT)<BLOCK_SIZE);
						for(uint8_t x=0;x<BLOCK_SIZE;x++) block[x]= serialRead(_uartBT);
						if (lookForAnswer(block,mac)>=1)
						 {
							found=true;
							parseBlock(block);
							sendCommand("IC");
							numberOfDevices = 1;
							delay(200);
						}
					}
				}
			}
		}
	#ifdef DEBUG_MODE
	printBuffer();
	#endif	

	// Condition to avoid an overflow (DO NOT REMOVE)
    	if( millis()-previous < 0 ) previous=millis();
	}
	free(block);
	block=NULL;
    	Utils.setLED(LED1, LED_OFF);  // Inquiry while led on
 	return found;
}

/*
 Function: Read nodeID from EEPROM and Date from RTC. Writes them into INQFILE.
 Returns: '1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
#ifdef ENABLE_DATE_AND_TIME
uint8_t WaspBT_Pro::getSetDateID()
{
	
	// Get ID
	getNodeID();
  	
  	// Get date and time 	
  	RTC.getTime();  

	// Build data and time string
	char * dateTime;
	dateTime = (char*) calloc(28,sizeof(char));
	sprintf(dateTime,"%02u-%02u-%02u;%02u:%02u; %s; ",RTC.date,RTC.month,RTC.year,RTC.hour,RTC.minute, identifier);

	if(!(SD.append(INQFILE,dateTime)))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
		
		return 0;
	}
	// free variables
	free(dateTime);
	dateTime=NULL;
	
	return 1;
}
#endif

/*
 Function: Looks for friendly names and stores them.
	NOTE: Inquiring with friendly names is avery slow process. 
	      Setting timeout (in milliseconds) the process can be aborted.
 Returns: '1' on success, '0' otherwise
 Parameters: 	
 Values: 
*/
#ifdef ENABLE_FRIENDLY_NAME
uint8_t WaspBT_Pro::parseNames()
{

uint8_t namesFound =0;
char dummy[4];	
uint8_t dummies = 0;					
for (i = 0; i < 40; i++) theCommand[i] = '\0';	// Clear variable
#ifdef DEBUG_MODE
USB.println(F("Scanning names..."));
#endif

if(!(SD.appendln(INQFILE,"Friendly names: ")))
{
	#ifdef DEBUG_MODE
	USB.print(F(ERRORSD1));
	#endif
}
numLinesAfter++;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
long timeout = 60000;	// Timeout to wait for name responses.			
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
long previous=millis();
while( (millis()-previous<timeout) && (namesFound<numberOfDevices)) 
{

	dummies=0;
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';	// Clear variable
	if (serialAvailable(_uartBT))	
	{
		dummy[0]=serialRead(_uartBT);
		if (dummy[0]=='A')
		{
			while(serialAvailable(_uartBT)<4);
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='M')
			{
				dummy[2]=serialRead(_uartBT);	
				if (dummy[2]=='E')
				{
					dummy[0]=serialRead(_uartBT);	//read space and miss it.			

					//if here, name sentence found. Now distinguish between ERROR and mac
					theCommand[0]=serialRead(_uartBT);
					if (theCommand[0]=='E')
					{
						//It is an error
						
						// read 11 dummy bytes
						while(serialAvailable(_uartBT)<11);
						for(uint8_t z=0;z<11;z++) dummy[0]=serialRead(_uartBT);
						
						// read and save corresponding mac
						while(serialAvailable(_uartBT)<BLOCK_MAC_SIZE);
						for(uint8_t x=0;x<BLOCK_MAC_SIZE;x++) theCommand[x]= serialRead(_uartBT);
						theCommand[BLOCK_MAC_SIZE+2]='N';
						theCommand[BLOCK_MAC_SIZE+3]='O';
						theCommand[BLOCK_MAC_SIZE+4]='N';
						theCommand[BLOCK_MAC_SIZE+5]='A';
						theCommand[BLOCK_MAC_SIZE+6]='M';
						theCommand[BLOCK_MAC_SIZE+7]='E';
						//save on SD
						if(!(SD.appendln(INQFILE,theCommand)))
						{
							#ifdef DEBUG_MODE
							USB.print(F(ERRORSD1));
							#endif
						}
						numLinesAfter++;
													
						namesFound++;
						#ifdef DEBUG_MODE
						printBuffer();
						#endif

					}
					else 
					{
						// It is a mac. Read mac (16bytes + one already read) + name
						while(serialAvailable(_uartBT)<20);		//!!
						for(uint8_t x=1;x<COMMAND_SIZE;x++) 
						{
							if(serialAvailable(_uartBT))
							{
							theCommand[x]= serialRead(_uartBT);
							if (theCommand[x]=='"') dummies++;
							if (dummies>=2) x = COMMAND_SIZE;
							}
						}
							
						// NAME read. Now save into SD
						if(!(SD.appendln(INQFILE,theCommand)))
						{
							#ifdef DEBUG_MODE
							USB.print(F(ERRORSD1));
							#endif
						}
						numLinesAfter++;		
						
						namesFound++;
						#ifdef DEBUG_MODE
						printBuffer();
						#endif

					}
					
				}
			}
		}
	}
	
	// Condition to avoid an overflow (DO NOT REMOVE)
    	if( millis()-previous < 0 ) previous=millis();
}

	// When lefting loop, If timeout is over
	if (millis()-previous<timeout) 
	{
		//scanNetworkCancel();	//NO HACE NADA, hay que hacer un reset.
		reset();
		#ifdef DEBUG_MODE
		USB.println(F("Timeout"));
		#endif
	}

#ifdef DEBUG_MODE
printBuffer2();
USB.println(F(""));
#endif

	return namesFound;
}
#endif

/* ------------CoD structure------------------
CoD has 24 bits divided into 3 main fields.
 - Service Class: 11bits (from 23 to 13)
 - Major Device Class: 5 bits (from 12 to 8)
 - Minor Device Class: 6 bits (from 7 to 2)

SERVICE CLASS:
	bit 23: Information 
	bit 22: Telephony
	bit 21: Audio
	bit 20: Object transfer
	bit 19: Capturing
 	bit 18: Rendering
	bit 17: Networking
	bit 16: Positioning
	bit 15:
	bit 14:
	bit 13:

MAJOR DEVICE CLASS:
	00000: Miscellaneous
	00001: Computer, PDA, notebook
	00010: Phone
	00011: Lan/network acces point
	00100: Audio/video (headset,speaker,stereo...)
	00101: peripheral (mouse, joystick, keyboard...)
	00110: Imaging (printing, scanner, camera, display)
	00111: Wearable
	01000: Toy
	11111: Uncategorized
	xxxxx: All other values reserved

MINOR DEVICE CLASS:
	This field has its own values for each major device class value.	

*/

/*
 Function: Saves inquiry data into specific array and also in SD file.
 Returns: 
	'1' on success, '0' otherwise
 Parameters: 
	block: array which contains inquiry data.
 Values: 
*/
uint8_t WaspBT_Pro::parseBlock(char* block)
{
	uint8_t flag=1;
	char * dev;
	dev = (char*) calloc(60, sizeof(char));
	uint8_t x=1;
	for(uint8_t z=0;z<17;z++)
	{
	mac_address[z]=block[x];	// Saves mac
	x++;
	}
	x++;	
	for(uint8_t z=0;z<6;z++)
	{
	CoD[z]=block[x];		// Saves CoD
	x++;
	}		
	x= x+4;	
	for(uint8_t z=0;z<3;z++)
	{
	RSSI[z]=block[x];		// Saves RSSI
	x++;
	}
	
	// Classify CoD 	// Develop this part
		
	// Handsfree
	if (CoD[3]=='4')
	{
		//sprintf(devClass, "C"); // 'C' means Car
		devClass[0] = 'C';	// 'C' means Car
	}
	else 
	{
		// Mobile
		if (CoD[3]=='2')
		{
			devClass[0] = 'P'; // 'P' means Person
		}
		else 
		{
			//Others
			devClass[0] = 'O'; // 'O' means Other type or unclassified.
		}
	}
	//(...)
	
	sprintf(dev, "%s; %s; %s; %c;",mac_address,CoD,RSSI,devClass[0]);
		
	// Inside data, Check inquiry file
	if ((SD.isFile(INQFILE))!=1) 
	{
		#ifdef DEBUG_MODE		
		USB.println(F("No file1"));
		#endif
		SD.create(INQFILE);
	}
	if(!(SD.appendln(INQFILE,dev)))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
		flag = 0;
	}
	numLinesAfter++;
	free(dev);
	dev=NULL;

	return flag;
}

/*
 Function: Reads and stores module answer.
 Returns: 
 Parameters: 
 Values: 
*/
void WaspBT_Pro::readCommandAnswer() 
{
	for (i = 0; i < RX_BUFFER; i++) commandAnswer[i] = '\0';	// Clears variable	
	i=0;
	while(serialAvailable(_uartBT)) 
	{		
		commandAnswer[i]=serialRead(_uartBT);
		i++;
		delay(10);	
	}
}

/*
 Function: Searches a string in a text. 
 Returns: returns '0' if the string is not found or position of the expected answer.
 Parameters: 
	data: data where string is contained.
	expectedAnswer: string to be found.
 Values: 
*/
uint16_t WaspBT_Pro::lookForAnswer(uint8_t* data, const char* expectedAnswer) 
{
	
	char * received;
	received = (char*) calloc(RX_BUFFER, sizeof(char));

	uint8_t theLength = 0;
	uint8_t it=0;
	bool theSame=false;
	uint8_t first=1;
	uint8_t match=0;
	i=0;
    
	while( expectedAnswer[theLength]!='\0' ) theLength++;
	while( !match && data[i]!='\0' )
	{
		if( first )	
		{
			for(it=0;it<theLength;it++)
			{
				received[it]=data[i];
				i++;
			}
			first=0;
		}
		it=0;
		theSame=true;
		for(it=0; it<theLength ; it++)	
		{
			if(received[it]!=expectedAnswer[it])
			{
				theSame= false;
				break;
			}
		}
		if( theSame ) match=1;
		else	
		{
			for(it=0; it<theLength-1 ; it++)
			{
				received[it]=received[it+1];
			}
			received[it]=data[i];
			i++;
		}
	}
	
	if( !match ) i=0;

	free(received);
	received=NULL;
	return i;
}

/*
 Function: Searches a string in a text. 
 Returns: returns '0' if the string is not found or position of the expected answer
 Parameters: 
	data: data where string is contained.
	expectedAnswer: string to be found.
 Values: 
*/
uint16_t WaspBT_Pro::lookForAnswer(char* data, const char* expectedAnswer) 
{
	
	char * received;
	received = (char*) calloc(RX_BUFFER, sizeof(char));	

	uint8_t theLength = 0;
	uint8_t it=0;
	bool theSame=false;
	uint8_t first=1;
	uint8_t match=0;
	i=0;
    
	while( expectedAnswer[theLength]!='\0' ) theLength++;
	
	while( !match && data[i]!='\0' )
	{
		if( first ){
			for(it=0;it<theLength;it++)
			{
				received[it]=data[i];
				i++;
			}
			first=0;
		}
		it=0;
		theSame=true;
		for(it=0; it<theLength ; it++)
		{
			if(received[it]!=expectedAnswer[it])
			{
				theSame= false;
				break;
			}
		}
		if( theSame ) match=1;
		else
		{
			for(it=0; it<theLength-1 ; it++)
			{
				received[it]=received[it+1];
			}
			received[it]=data[i];
			i++;
		}
	}
	
	if( !match ) i=0;

	free(received);
	received=NULL;
	return i;
}

/*
 Function: Sends a given command to bluetooth module, adding CR+LF.
 Returns: 
 Parameters: 
	theText: Command to send.
 Values: 
*/
void WaspBT_Pro::sendCommand(const char* theText) 
{
    
    sprintf(theCommand, "%s\r\n", theText);		// Adds CR+LF
  	serialFlush(_uartBT);	
    printString(theCommand,_uartBT);
    delay(100);
}

/*				
 Function: Change TX power
 Returns: 
 Parameters: 
	power: TX power value.
 Values: 
*/
void WaspBT_Pro::changeInquiryPower(int8_t power) 
{

	// Sets first two values to maximum by default
	sprintf(theCommand, "SET BT POWER %d %d %d", TX_POWER_DEFAULT_WT12, TX_POWER_MAX_WT12, power);
	sendCommand(theCommand);
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';	// Clear variable
	txPower = power;
}

/*				
 Function: Sets time to wait inquiry answer
 Returns: Returns wait time in milliseconds
 Parameters: 
	time: time of inquiry in seconds. It is multiplied according to manufacturer
 Values: 
*/
uint16_t WaspBT_Pro::setInquiryTime(uint16_t time)
{
	uint16_t waitTime = 0;

	switch (time) {					
		case 0	:	waitTime = 1000;break;
		case 1  :	waitTime = 2000;break;
		case 2	:	waitTime = 2560;break;
		case 3  :	waitTime = 3840;break;
		case 4	:	waitTime = 5120;break;
		case 5  :	waitTime = 6400;break;
		case 6	:	waitTime = 7680;break;
		case 7  :	waitTime = 8960;break;
		case 8	:	waitTime = 10240;break;
		case 9  :	waitTime = 11520;break;
		case 10	:	waitTime = 12800;break;
		case 11 :	waitTime = 14080;break;
		case 12	:	waitTime = 15360;break;
		case 13 :	waitTime = 16640;break;
		case 14	:	waitTime = 17920;break;
		case 15 :	waitTime = 19200;break;
		case 16	:	waitTime = 20480;break;
		case 17 :	waitTime = 21760;break;
		case 18	:	waitTime = 23040;break;
		case 19 :	waitTime = 24320;break;
		case 20	:	waitTime = 25600;break;
		case 21 :	waitTime = 26880;break;
		case 22	:	waitTime = 28100;break;
		case 23 :	waitTime = 29500;break;
		case 24 :	waitTime = 30700;break;
		case 25	:	waitTime = 32000;break;
		case 26 :	waitTime = 33200;break;
		case 27	:	waitTime = 34500;break;
		case 28 :	waitTime = 35800;break;
		case 29	:	waitTime = 37000;break;
		case 30 :	waitTime = 38400;break;
		case 31	:	waitTime = 39600;break;
		case 32 :	waitTime = 40900;break;
		case 33 :	waitTime = 42200;break;
		case 34	:	waitTime = 43500;break;
		case 35 :	waitTime = 44800;break;
		case 36	:	waitTime = 46000;break;
		case 37 :	waitTime = 47300;break;
		case 38	:	waitTime = 48640;break;
		case 39 :	waitTime = 50000;break;
		case 40 :	waitTime = 51200;break;
		case 41	:	waitTime = 52500;break;
		case 42 :	waitTime = 53700;break;
		case 43	:	waitTime = 55000;break;
		case 44 :	waitTime = 56300;break;
		case 45	:	waitTime = 57600;break;
		case 46 :	waitTime = 59000;break;
		case 47	:	waitTime = 60000;break;
		case 48 :	waitTime = 61500;break;
		}
	return waitTime;
}

/*
 Function: Cancels an inquiry 
 Returns: 
 Parameters: 
 Values: 
*/
void WaspBT_Pro::scanNetworkCancel() 
{	
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';	// Clear variable
	sendCommand("IC");
}

/*
 Function: Erases files created by bluetooth module on SD card.
 Returns: '1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::eraseSDFiles()
{
	
	uint8_t flag =1;
	
	// reset all file lines counters
	numLinesBefore = 0;
	numLinesAfter = 0;
	
	// erase inqfile if exist.
	if ((SD.isFile(INQFILE))==1)
	{
		flag = SD.del(INQFILE);
		delay(100);
		#ifdef DEBUG_MODE
		USB.println(F("dl1"));
		#endif
	}
	return flag;
}

/*
 Function: Creates required files by bluetooth module into Sd card.
 Returns: '1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::createSDFiles()
{

	if ((SD.isFile(INQFILE))!=1) 
	{
		if(!(SD.create(INQFILE)))
		{
		#ifdef DEBUG_MODE
		USB.println(F(ERRORSD2));
		#endif
		return 0;
		}
		else 
		{
			SD.appendln(INQFILE,INQFILEHEAD);
			numLinesAfter++;
		}
	}
	return 1;
}

// Constructors //

/*				
 Function: Constructor
 Returns: 
 Parameters: 	
 Values: 
*/
WaspBT_Pro::WaspBT_Pro() 
{

	i=0;
	_baudrateBT=BT_BLUEGIGA_RATE;
	
	
}

// Public Methods //

/*
 Function: Turns on bluetooth module. 
 Returns: '1' os success, '0' error reset, '-1' error init, 
 Parameters: UartMode should be 0 for SOCKET0 and 1 for SOCKET1
 Values: 
*/
int8_t WaspBT_Pro::ON(uint8_t UartMode) 
{
	
	int8_t flag =1;
	// prevent bad uart number. By default UART1
	if (UartMode>=2) _uartBT = 1;
	else _uartBT=UartMode;	
		
	if(!_uartBT) 
	{
		pinMode(BT_PRO_PW_0,OUTPUT);	
		digitalWrite(BT_PRO_PW_0,HIGH);
	}
	else	
	{
		Utils.setMuxSocket1();
		pinMode(BT_PRO_PW_1,OUTPUT);
		digitalWrite(BT_PRO_PW_1,HIGH);		
	}
	
	beginSerial(_baudrateBT,_uartBT);
	serialFlush(_uartBT);
	
	if(!(reset())) flag=0;
	
	if(!(init())) flag=-1;
	
	return flag;
	
}

/*
 Function: Turns on bluetooth module. By default UART1
 Returns: '1' os success, '0' error reset, '-1' error init
 Parameters: 
 Values: 
*/
int8_t WaspBT_Pro::ON() 
{
	
	int8_t flag=1;
	flag = ON(SOCKET1);	
	return flag;
	
}

/*
 Function: Turns off bluetooth module. 
 Returns: 
 Parameters: 
 Values:
*/ 
void WaspBT_Pro::OFF() 
{
	
	closeSerial(_uartBT);

	if(!_uartBT) 
	{
		pinMode(BT_PRO_PW_0,OUTPUT);
		digitalWrite(BT_PRO_PW_0,LOW);
	}
	else 
	{
		Utils.setMux(MUX_TO_LOW,MUX_TO_LOW);
		pinMode(BT_PRO_PW_1,OUTPUT);
		digitalWrite(BT_PRO_PW_1,LOW);		
	}
	
	SD.OFF();
	
}

/*
 Function: Turns bluetooth module into sleep mode. 
 Returns: 
 Parameters: 
 Values:
*/ 
void WaspBT_Pro::sleep() 
{
	
	sendCommand("sleep");
	
}

/*
 Function: Wake up Bluetotoh module from Sleep mode. 
 Returns: '1' on success, '0' otherwise
 Parameters: 
 Values:
*/ 
uint8_t WaspBT_Pro::wakeUp() 
{
	
	char dummy[2];
	uint8_t flag=0;
	
	
	// Necessary some dummy chars to wake up module by UART.
	sendCommand("at");
	sendCommand("at");
	sendCommand("at");
	delay(100);
		
	// Read an OK to confirm wake up process
	long timeout = millis();
	while(serialAvailable(_uartBT) && (millis()-timeout < 2000))
	{
		dummy[0]=serialRead(_uartBT);	
		if (dummy[0]=='O')
		{
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='K')
			{
				
				// If here, wake up OK.
				flag=1;
				serialFlush(_uartBT);	
				}
			}
	}
	
	return flag;
	
}

/*
 Function: Initialize some variables of the module
 Returns: '1' on success, '0' configuration failed, '-1' erasing SD files failed, 
		  '-2' creating SD files failed, '-3' SD card not present
 Parameters: 
 Values:
*/ 
int8_t WaspBT_Pro::init() 
{
	
	int8_t flag=1;
	
	// Enable RSSI for inquiry	
	sendCommand("SET CONTROL CONFIG 0000 0101");			
	delay(1000);

	//check if configuration is OK
	sendCommand("SET CONTROL CONFIG LIST");
	readCommandAnswer();
	
	#ifdef DEBUG_MODE
	//if(lookForAnswer(commandAnswer,"CONTROL CONFIG 0000 0000 0101")){
	if(lookForAnswer(commandAnswer,"CONTROL CONFIG 0000 0101"))
	{
		USB.println(F("Configuration OK"));
	}
	else
	{
		
		USB.println(F("Configuration failed"));
		flag=0;
	}
	#endif
	//SET defaul tx power to TX_POWER_5
	sendCommand("SET BT POWER 3 3 -2");			
	txPower = -2;	

	// Prepare SD
	SD.ON();
    delay(200);
    if (SD.isSD()==0) 
    {
		USB.println(F("SD Card not present"));
		flag = -3;
	}

	SD.cd("..");

	// Erase files
	if(!(eraseSDFiles())) flag=-1;

	// Create necessary files to ensure their existence.
	if(!(createSDFiles())) flag = -2;
	
	// Turn on RTC for date and time features
	#ifdef ENABLE_DATE_AND_TIME
	RTC.ON();
	#endif
	
	return flag;

}

/*
 Function: Resets bluetooth module.
 Returns: '1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::reset() 
{ 	
	
	uint8_t flag =1;	
	sendCommand("RESET");
	delay(2000);					// Reboot time
	readCommandAnswer();
	if (lookForAnswer(commandAnswer,"Bluegiga"))
	{	// Searches keyword on answer. 
		#ifdef DEBUG_MODE
		USB.println(F("Ready"));
		#endif
	}
	else{	
		#ifdef DEBUG_MODE
		USB.println(F("Reset failed"));
		#endif
		flag = 0;
	}
	return flag;
}

/*
 Function: Saves Bluetooth Node indentifier into EEPROM
 Returns: 
 Parameters: NodeID: Bluetootn Node identifier. It must be 8 char length
 Values: 
*/
void WaspBT_Pro::setNodeID(char * ID)
{
	
	// Default EEPROM memory addres. Do not change.
  	mem_addr=BT_NODE_ID_ADDR;
	
	for (int i=0; i<8; i++)
	{
	  // write EEPROM
	  eeprom_write_byte((unsigned char *) mem_addr, ID[i]);
	  
	  // Also updates public variable.
	  identifier[i]=ID[i];
	  mem_addr++; 
	}   
	
}

/*
 Function: Reads Bluetooth Node Identifier.
 Returns: Bluetooth node identifier stored in EEPROM
 Parameters: 
 Values: 
*/
char * WaspBT_Pro::getNodeID()
{
	
	// Default EEPROM memory addres. Do not change.
	mem_addr=BT_NODE_ID_ADDR;
	// Read node identifier from EEPROM
	for (int i=0; i<8; i++) 
	{
	identifier[i]=Utils.readEEPROM(mem_addr); 
    	mem_addr++; 
  	}
	
	return identifier;
}

// Not working on UART 0.
/*
 Function: Reads internal temperature sensor of bluetooth module. 
 Returns: Temperature
 Parameters: 
 Values: 
*/
long WaspBT_Pro::getTemp()
{
	long a;
	char dummy[3];
	char temperature[4];
	for (uint8_t i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';	// Clear variable
	for (uint8_t i = 0; i < 3; i++) temperature[i] = '\0';
	sendCommand("temp");
	delay(500);	// Necessary
	
	long timeout = millis();
	while(serialAvailable(_uartBT) && (millis()-timeout < 2000))
	{
		dummy[0]=serialRead(_uartBT);	
		if (dummy[0]=='M'){
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='P'){
				dummy[0]=serialRead(_uartBT);
				temperature[0]=serialRead(_uartBT);
				temperature[1]=serialRead(_uartBT);
				temperature[2]='\0';
		
				// convert from string to int
				a = atoi(temperature);
				}
			}
	}
return a;
}

/*
 Function: Gets Bluetooth module MAC address
 Returns: 
	Own mac Address of bluetooth module.
 Parameters: 
 Values: 
*/
char * WaspBT_Pro::getOwnMac()
{
	
	char dummy[4];
	i=0;
	sendCommand("SET");
		
	delay(500);
	long timeout = millis();
	while(serialAvailable(_uartBT) && (millis()-timeout < 2000))
	{
		dummy[0]=serialRead(_uartBT);	
		if (dummy[0]=='A')
		{
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='D')
			{
				dummy[0]=serialRead(_uartBT);
				if (dummy[0]=='D')
				{
					dummy[1]=serialRead(_uartBT);
					if (dummy[1]=='R')
					{
						dummy[0]=serialRead(_uartBT);
						for(i=0; i<17; i++)	mac_address[i]=serialRead(_uartBT);
												
					}
				}
			}
		}
	}
	delay(500);
	serialFlush(_uartBT);	// delete all other dummy information	
	delay(200);
	return mac_address;
	
}

/*
 Function: Gets public name of bluetooth device.
 Returns: 
	public name of bluetooth device. Max length manually limited to 20 characters. 
	* Hardware allows til 256 chars.
 Parameters: 
 Values: 
*/
char * WaspBT_Pro::getOwnName()
{
	
	char friendlyName[24];
	char dummy[4];
	uint8_t end=1;
	long timeout;
	
	for (i = 0; i < 24; i++) friendlyName[i] = '\0';	// Clear variable
	
	sendCommand("SET");
	
	delay(600);
	timeout = millis();
	while(serialAvailable(_uartBT)  && (millis()-timeout < 2000))
	{
		dummy[0]=serialRead(_uartBT);	
		if (dummy[0]=='A')
		{
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='M')
			{
				dummy[0]=serialRead(_uartBT);
				if (dummy[0]=='E')
				{
					dummy[1]=serialRead(_uartBT);
					
					i=0;			
					while((end) && (i<24))
					{
						friendlyName[i]=serialRead(_uartBT);
						if (friendlyName[i]=='_') 
						{
							end=0;	// If name ends with '_', exit loop. 
							friendlyName[i] = '\0';
						}
						i++;
					}
				}
			}
		}
	}
	delay(500);
	serialFlush(_uartBT);	// delete all other dummy information	
	delay(200);
	return friendlyName;
	
}

/*
 Function: Set public name on bluetooth device module. Maximum length is 20 chars.
 Returns: 
	'1' on success, '0' if maximum length is exceeded
	* * Spaces are not allowed.
 Parameters: 
	publicName: Visible name of bluetooth device. Use short names without spaces
 Values: 
*/
uint8_t WaspBT_Pro::setOwnName(char * publicName)
{
	
	
	char namePublic[40];
	i=0;
	uint8_t length = 0;
	
	while(publicName[i]!='\0') i++;
	length=i;
	
	// limit name length to 20
	if(length<20) 
	{
		sprintf(namePublic,"SET BT NAME %s_",publicName);	// add end char for parsing public name
		sendCommand(namePublic);
		delay(200);
	}
	else if(length>=20) return 0;		// Name too long. Max allowed length=20
	
	return 1;
}

/*
 Function: Makes an inquiry to discover new devices.
 Returns: returns number of devices found.
 Parameters: 
	time: Inquiry time.
	power: Allowed TX power levels
 Values: 
*/
int8_t WaspBT_Pro::scanNetwork(uint8_t time, int8_t power) 
{	
	
	long inquiryTime= 0;
	bool name=false;
	bool limited=false;
	uint16_t maxDevices = DEFAULT_MAX_INQUIRY_RESULTS;	

	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		// Clears variable
	if (txPower != power)changeInquiryPower(power);		// checks previous value. Change only if different.

	if (time==0) time =1;					// Min inquiry time
	if (time>48) time = 48;					// Max inquiry time
	
			
	inquiryTime = setInquiryTime(time);
	
	// write header for inquiry file
	SD.cd("..");
	
	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;
	
	#ifdef DEBUG_MODE
	USB.print(F("numlines before:"));		
	USB.println(numLinesBefore);
	#endif
		
	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif
	if(!(SD.appendln(INQFILE,"ScanNetwork")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;

	sprintf(theCommand, "inquiry %u", time);		
	sendCommand(theCommand);
	
	numberOfDevices = 0;
	waitInquiryAnswer(inquiryTime, maxDevices, name, limited);
	
	// write line
	if(!(SD.appendln(INQFILE,ENDSTRING)))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;
	
	return numberOfDevices;
}

/*
 Function: It scans network and stops when finds "MAX_DEVICES". If max not reaches it scans max time (60s).
 Returns: Returns number of devices found.
 Parameters: 
	MAX_DEVICES: Maximum number of devices to find.
	power: Allowed TX power levels
 Values: 
*/
int8_t WaspBT_Pro::scanNetworkLimited(uint16_t MAX_DEVICES, int8_t power) 
{	
	
	long inquiryTime = 0;
	bool name=false;
	bool limited=true;
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		// Clears variable
	if (txPower != power)changeInquiryPower(power);		// Checks previous value. Change only if different.
	
	
	inquiryTime = setInquiryTime(48);
	
	// write header for inquiry file
	SD.cd("..");
	
	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	USB.print(F("numlines before:"));		
	USB.println(numLinesBefore);
	#endif

	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif
	if(!(SD.appendln(INQFILE,"ScanNetworkLimited. ")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;
	
	sprintf(theCommand, "inquiry 48");			// Inquiry command for max time
	sendCommand(theCommand);
	
	numberOfDevices = 0;
	waitInquiryAnswer(inquiryTime, MAX_DEVICES, name,limited);

	if (numberOfDevices>=MAX_DEVICES)
	{
	scanNetworkCancel();				
	}
	else 
	{
	#ifdef DEBUG_MODE
	USB.println(F("Maximum not reached"));
	#endif
	}

	// write end line
	if(!(SD.appendln(INQFILE,";")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;
	
	//numLinesAfter = SD.numln(INQFILE);
	
	return numberOfDevices;
}

/*
 Function: Makes an inquiry to discover specific device by its Mac.
 Returns: '0' if not found. '1' if found
 Parameters: 
	Mac: Mac of device to discover
	maxTime: Maximum time searching device
	power: Allowed TX power levels
 Values: 
*/
int16_t WaspBT_Pro::scanDevice(char* Mac, uint8_t maxTime, int8_t power) 
{	
	
	long inquiryTime= 0;
	uint16_t maxDevices = DEFAULT_MAX_INQUIRY_RESULTS;					

	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		// Clears variable
	if (txPower != power)changeInquiryPower(power);		// Checks previous value. Change only if different.
	
	if (maxTime==0) maxTime =1;				// Min inquiry time
	if (maxTime>48) maxTime = 48;				// Max inquiry time

	
	inquiryTime = setInquiryTime(maxTime);

	// write header for inquiry file
	SD.cd("..");
	

	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	USB.print(F("numlines before:"));		
	USB.println(numLinesBefore);
	#endif

	
	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif
	if(!(SD.append(INQFILE,"ScanDevice: ")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	if(!(SD.appendln(INQFILE,Mac)))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;

	sprintf(theCommand, "inquiry %u", maxTime);			
	sendCommand(theCommand);

	numberOfDevices = 0;

	if(waitScanDeviceAnswer(inquiryTime,Mac)) 
	{
		// write end line
		if(!(SD.appendln(INQFILE,";")))
		{
			#ifdef DEBUG_MODE		
			USB.println(F(ERRORSD1));
			#endif
		}
		numLinesAfter++;
		//numLinesAfter = SD.numln(INQFILE);
		
		return 1;
	}
	else 
	{
		// write end line
		if(!(SD.appendln(INQFILE,"Not found.")))
		{
			#ifdef DEBUG_MODE		
			USB.println(F(ERRORSD1));
			#endif
		}
		numLinesAfter++;
		if(!(SD.appendln(INQFILE,";")))
		{
			#ifdef DEBUG_MODE		
			USB.println(F(ERRORSD1));
			#endif
		}
		numLinesAfter++;
		//numLinesAfter = SD.numln(INQFILE);
		
		return 0;
	}	
}

/*
 Function: Makes an inquiry to discover new devices
 Returns: returns number of devices found.
 Parameters: 
	time: Inquiry time.
	power: Allowed TX power levels
 Values: 
*/
#ifdef ENABLE_FRIENDLY_NAME
int8_t WaspBT_Pro::scanNetworkName(uint8_t time, int8_t power) 
{	
	
	long inquiryTime= 0;
	bool name=true;
	bool limited=false;
	uint16_t maxDevices = DEFAULT_MAX_INQUIRY_RESULTS;	

	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		// Clears variable
	if (txPower != power)changeInquiryPower(power);		// checks previous value. Change only if different.

	if (time==0) time =1;					// Min inquiry time
	if (time>48) time = 48;					// Max inquiry time
	
	
	inquiryTime = setInquiryTime(time);
	
	// write header for inquiry file
	SD.cd("..");
	

	// Set line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	USB.print(F("numlines before:"));		
	USB.println(numLinesBefore);
	#endif

	
	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif
	if(!(SD.appendln(INQFILE,"ScanNetworkName")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;
	
	sprintf(theCommand, "inquiry %u name", time);		
	sendCommand(theCommand);
	
	numberOfDevices = 0;
	
	waitInquiryAnswer(inquiryTime, maxDevices, name, limited);

	// write end line
	if(!(SD.appendln(INQFILE,";")))
	{
		#ifdef DEBUG_MODE		
		USB.println(F(ERRORSD1));
		#endif
	}
	numLinesAfter++;
	//numLinesAfter = SD.numln(INQFILE);
	//delay(3000);
	return numberOfDevices;
}
#endif

/*
 Function: Prints data of last inquiry on USB
 * Use only for debuging purposes. 
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::printInquiry()
{

	
	USB.println(F(""));
	i=0;
	
	for(i=numLinesBefore+1;i<numLinesAfter-1;i++)
	{
		USB.print(SD.catln(INQFILE,i,1));
	}
	
	// Always '1'
	return 1;
}



/*
 Function: Create a transparent connection with other bluetooth module using serial port profile
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
		mac: device mac address to be connected
 Values: 
*/
uint8_t WaspBT_Pro::createConnection(char * mac)
{
	long timeout;
	char target[5] = "1101";
	char connectMode[7] = "RFCOMM";
	uint8_t connected = 0;
	
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		

	// Build call command. Example: CALL 00:07:80:80:52:27 1101 RFCOMM
	sprintf(theCommand, "call %s %s %s", mac, target, connectMode);	
	
	// Send call command
	sendCommand(theCommand);
	
	// Wait CALL {link_id}
	readCommandAnswer();
	if (!lookForAnswer(commandAnswer, "CALL"))
	{
		// Call command not executed
		return 0;
	}
	else
	{
		// save link ID. NOT USED
		// uint pos = lookForAnswer(commandAnswer, "CALL");
		// uint8_t linkID = commandAnswer[pos + 6];
		
	}
		
	// wait CONNECT {link_id} {SCO | RFCOMM | A2DP | HID | HFP | HFP-AG {target} [address]}
	// CONNECT 0 RFCOMM 1
	// if "NO CARRIER", connection unsuccessful
		
	timeout = millis();
	while((!connected) && (millis()-timeout < 5000))
	{	
		readCommandAnswer();
		if(lookForAnswer(commandAnswer, "CONNECT"))
		{
			connected = 1;
			commandMode = 0;
		}
		else if (lookForAnswer(commandAnswer, "NO CARRIER")) return 0;
	}
		
	if (connected) 
	{
		activeConnections++;
		return 1;
	}
	else return 0;
	
}

/*
 Function: Removes a transparent connection. by default linkID=0.
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::removeConnection()
{
	long timeout;
	uint8_t flag =0;
	
	// enter command mode
	if (!enterCommandMode()) return 0;
	
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		

	// send close command CLOSE {link_id}
	// Build call command. By default, linkID=0.
	sprintf(theCommand, "CLOSE 0");	
	
	// Send call command
	sendCommand(theCommand);

	// Check if connection removed OK
	// NO CARRIER {link_id} ERROR {error_code}
	timeout = millis();
	while((!flag) && (millis()-timeout < 10000))
	{	
		readCommandAnswer();
		
		// look for error code = 0
		if(lookForAnswer(commandAnswer, "ERROR 0"))
		{
			// removed OK
			flag = 1;
			
			// add check for link ID
			// Not used. By default linkID=0.
		}
		else
		{
			// error removing
			flag=0;
			
			// check error code.
			// Not used.
		}
	}

	if (flag) 
	{
		activeConnections--;
		return 1;
	}
	else return 0;

}

/*
 Function: Sends data trough a transparent connection with other bluetooth module using serial port profile
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
		data: data to be sent
 Values: 
*/
uint8_t WaspBT_Pro::sendData(char * data)
{
	// check data length not bigger than payload.
	// By default is 667 bytes. Maximum is 1000. see MTU.
	// Not used.
	
	// check if there is an active connection
	if(!activeConnections) return 0;
	
	// check if command mode not active
	if (commandMode) return 0;
	
	// send data
	serialFlush(_uartBT);	
    printString(data,_uartBT);
    delay(100);
	
	return 1;
}


/*
 Function: Sends data trough a transparent connection with other bluetooth module using serial port profile
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
		data: data to be sent
 Values: 
*/
uint8_t WaspBT_Pro::sendData(uint8_t* data, uint16_t length)
{
	// check data length not bigger than payload.
	// By default is 667 bytes. Maximum is 1000. see MTU.
	// Not used.
	
	// check if there is an active connection
	if(!activeConnections) return 0;
	
	// check if command mode not active
	if (commandMode) return 0;
	
	// send data
	serialFlush(_uartBT);	
	for (int i = 0; i < length; i++)
	{
		printByte(data[i],_uartBT);
	}    
    delay(100);
	
	return 1;
}

/*
 Function: Enters command mode of bluetooth module. Take at least two seconds.
 Returns: 	'1' on success, '0' otherwise
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::enterCommandMode()
{
	long timeout;
	
	// check if already in command mode
	if (commandMode)
	{
		USB.print(F("already in CM"));
		return 1;
	}
	
	// mandatory delay 1 second before and after escape sequence
	delay(1100);
	// send +++ witout endline
	serialFlush(_uartBT);	
    printString("+++",_uartBT);
    delay(1100);
	
	// look for ready
	timeout = millis();
	while((!commandMode) && (millis()-timeout < 5000))
	{	
		readCommandAnswer();
		if(lookForAnswer(commandAnswer, "READY"))
		{
			commandMode = 1;
		}
	}
	
	if (commandMode) return 1;
	else return 0;
	
}

/*
 Function: Switches from command mode to data mode. Takes at lest 2 seconds
 Returns: 	'1' on success, '0' if no active connections.
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::returnToDataMode()
{
	// check if there is an active connection
	if(!activeConnections) return 0;
	
	// mandatory delay 1 second before and after escape sequence
	delay(1100);
	// send +++ witout endline
	serialFlush(_uartBT);	
    printString("+++",_uartBT);
    delay(1100);

	commandMode=0;
	
	return 1;
}

/*
 Function: Checks if there are active conections. Maximun connections are 7
 Returns: 	0-7 number of active connections, -1 error entering command mode.
 Parameters: 
 Values: 
*/
int8_t WaspBT_Pro::checkActiveConnections()
{
	uint8_t flag = 0;
	int actives =0;
	uint8_t found = 0;
	char dummy[4];
	char active[2] ="x";
	long timeout;
	
	// check if already in command mode
	if (!commandMode)
	{
		if(enterCommandMode()) flag =1;
		else return -1;
	}
		
	// LIST {num_of_connections}
	// Send call command
	sendCommand("LIST");

	// parse answer 
	delay(500);
	
	// read first dummy bytes
	if(serialAvailable(_uartBT) )
	{
		for(uint8_t i=0;i<5;i++) dummy[0]=serialRead(_uartBT);	
	}

	timeout = millis();
	while(serialAvailable(_uartBT) && (!found) && (millis()-timeout < 10000))
	{
		dummy[0]=serialRead(_uartBT);	
		if (dummy[0]=='L')
		{
			dummy[1]=serialRead(_uartBT);	
			if (dummy[1]=='I')
			{
				dummy[0]=serialRead(_uartBT);
				if (dummy[0]=='S')
				{
					dummy[1]=serialRead(_uartBT);
					if (dummy[1]=='T')
					{
						dummy[0]=serialRead(_uartBT);
						active[0]=serialRead(_uartBT);
						active[1]= '\0';
						found=1;
					}
				}
			}
		}
	}
	delay(200);
	serialFlush(_uartBT);	// delete all other dummy information	
		
	// if came from data mode, 
	if (flag) returnToDataMode();	
		
	actives = atoi(active);
	
	// update global variable
	activeConnections = actives;
	
	return actives;
}


/*
 Function: Returns the Receiver Signal Strength Indication of the link given as a parameter
 Returns: 	'1' if RSSI obtained, '0' if no connections, '-1' if error in command mode, '-2' if link not active. 
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::getRSSI()
{
	return getRSSI(0);
}

/*
 Function: Updates the Receiver Signal Strength Indication of the variable linkRSSI of the link given as a parameter
 Returns: 	'1' if RSSI obtained, '0' if no connections, '-1' if error in command mode, '-2' if link not active. 
 Parameters: 
 Values: 
*/
uint8_t WaspBT_Pro::getRSSI(uint8_t linkID)
{
	
	int flag=0;
	uint8_t pos;
	
	
	if (!activeConnections) return 0;
		
	// check if already in command mode
	if (!commandMode)
	{
		if(enterCommandMode()) flag =1;
		else return -1;
	}
	
	
	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';		

	// send rssi command RSSI {link_id}
	sprintf(theCommand, "RSSI %u", linkID);	
	
	// Send call command
	sendCommand(theCommand);
	
	delay(200);	
	
	// response: RSSI {bd_addr} {rssi}
	// syntax error if linkID not active.
		
	readCommandAnswer();
	if(lookForAnswer(commandAnswer, "ERROR")) return -2;
	else
	{
		pos = lookForAnswer(commandAnswer, " -");
		
		pos--;
		// parse RSSI
		for (i=0;i<3;i++) 
		{
			linkRSSI[i]=commandAnswer[pos];				
			pos++;
		}
		linkRSSI[3]='\0';
	}
	
	// if came from data mode, 
	if (flag) returnToDataMode();	
	
	return 1;
	
}



#ifdef DEBUG_MODE
// Test purposes only
void WaspBT_Pro::printBuffer()
{
	int flag= serialAvailable(_uartBT);
	if (flag>900)	USB.println(F("_-OVERFLOW-_"));
	
}

// Test purposes only
void WaspBT_Pro::printBuffer2()
{
	int flag= serialAvailable(_uartBT);
	if (flag>900)	USB.println(F("_-*OVERFLOW in summary*-_"));
	
}
#endif

WaspBT_Pro BT_Pro=WaspBT_Pro();		//object
