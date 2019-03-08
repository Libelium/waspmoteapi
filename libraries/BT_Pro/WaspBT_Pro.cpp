/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */

#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspBT_Pro.h"


/******************************************************************************
 * FLASH DEFINITIONS
 ******************************************************************************/

/// table_BT /////////////////////////////////////////////////////////////////
const char	bt_string_00[]	PROGMEM = "%02u-%02u-%02u;%02u:%02u; %s; ";	// 0
const char	bt_string_01[]	PROGMEM = "Friendly names: ";   			// 1
const char	bt_string_02[]	PROGMEM = "%s; %s; %s; %c;";   				// 2
const char	bt_string_03[]	PROGMEM = "SET BT POWER %d %d %d";   		// 3
const char	bt_string_04[]	PROGMEM = "sleep";   						// 4
const char	bt_string_05[]	PROGMEM = "SET CONTROL CONFIG 0000 0101";   // 5
const char	bt_string_06[]	PROGMEM = "SET CONTROL CONFIG LIST";   		// 6
const char	bt_string_07[]	PROGMEM = "CONTROL CONFIG 0000 0101";   	// 7
const char	bt_string_08[]	PROGMEM = "SET BT POWER 3 3 -2";   			// 8
const char	bt_string_09[]	PROGMEM = "RESET";   						// 9
const char	bt_string_10[]	PROGMEM = "THOR";   						// 10
const char	bt_string_11[]	PROGMEM = "temp";   						// 11
const char	bt_string_12[]	PROGMEM = "SET";   							// 12
const char	bt_string_13[]	PROGMEM = "SET BT NAME %s_";   				// 13
const char	bt_string_14[]	PROGMEM = "ScanNetwork";   					// 14
const char	bt_string_15[]	PROGMEM = "inquiry %u";   					// 15
const char	bt_string_16[]	PROGMEM = "ScanNetworkLimited. ";   		// 16
const char	bt_string_17[]	PROGMEM = "inquiry 48";   					// 17
const char	bt_string_18[]	PROGMEM = "ScanDevice: ";   				// 18
const char	bt_string_19[]	PROGMEM = "Not found.";   					// 19
const char	bt_string_20[]	PROGMEM = "ScanNetworkName";   				// 20
const char	bt_string_21[]	PROGMEM = "inquiry %u name";   				// 21
const char	bt_string_22[]	PROGMEM = "1101";   						// 22
const char	bt_string_23[]	PROGMEM = "RFCOMM";   						// 23
const char	bt_string_24[]	PROGMEM = "call %s %s %s";   				// 24
const char	bt_string_25[]	PROGMEM = "CALL";   						// 25
const char	bt_string_26[]	PROGMEM = "CONNECT";   						// 26
const char	bt_string_27[]	PROGMEM = "NO CARRIER";   					// 27
const char	bt_string_28[]	PROGMEM = "CLOSE 0";   						// 28
const char	bt_string_29[]	PROGMEM = "ERROR 0";   						// 29
const char	bt_string_30[]	PROGMEM = "READY";   						// 30
const char	bt_string_31[]	PROGMEM = "LIST";   						// 31
const char	bt_string_32[]	PROGMEM = "RSSI %u";   						// 32
const char	bt_string_33[]	PROGMEM = "ERROR";   						// 33
const char	bt_string_34[]	PROGMEM = "Total: ";   						// 34
const char	bt_string_35[]	PROGMEM = "Discovered devices";   			// 35
const char	bt_string_36[]	PROGMEM = "---";   							// 36
const char bt_string_37[]  PROGMEM = "SET BT AUTH * %s";				// 37
const char bt_string_38[]  PROGMEM = "PAIR %s";						// 38
const char bt_string_39[]  PROGMEM = "OK";								// 39
const char bt_string_40[]  PROGMEM = "SET BT PAIR *";					// 40

const char* const table_BT[] PROGMEM =
{
	bt_string_00,		// 0
	bt_string_01,		// 1
	bt_string_02,		// 2
	bt_string_03,		// 3
	bt_string_04,		// 4
	bt_string_05,		// 5
	bt_string_06,		// 6
	bt_string_07,		// 7
	bt_string_08,		// 8
	bt_string_09,		// 9
	bt_string_10,		// 10
	bt_string_11,		// 11
	bt_string_12,		// 12
	bt_string_13,		// 13
	bt_string_14,		// 14
	bt_string_15,		// 15
	bt_string_16,		// 16
	bt_string_17,		// 17
	bt_string_18,		// 18
	bt_string_19,		// 19
	bt_string_20,		// 20
	bt_string_21,		// 21
	bt_string_22,		// 22
	bt_string_23,		// 23
	bt_string_24,		// 24
	bt_string_25,		// 25
	bt_string_26,		// 26
	bt_string_27,		// 27
	bt_string_28,		// 28
	bt_string_29,		// 29
	bt_string_30,		// 30
	bt_string_31,		// 31
	bt_string_32,		// 32
	bt_string_33,		// 33
	bt_string_34,		// 34
	bt_string_35,		// 35
	bt_string_36,		// 36
	bt_string_37,		// 37
	bt_string_38,		// 38
	bt_string_39,		// 39
	bt_string_40,		// 40
};



/******************************************************************************
 * CLASS METHODS
 ******************************************************************************/

// Private Methods //

/*
 Function: Reads discovered devices from UART and saves them into specific array.
 Returns:
  '1' on success,
  '0' error parsing block,
  '-1' error parsing names,
  '-2' maybe device lost,
  '-3' error writting SD
 Parameters:
	inquiryTime: wait for module answer during this time.
	MAX_DEVICES: Maximum number of deviced to discover.
	name: Enables friendly name scan.
	limit: Enables limited scan.
 Values:
*/
int8_t  WaspBT_Pro::waitInquiryAnswer(	unsigned long inquiryTime,
										uint16_t MAX_DEVICES,
										bool name,
										bool limited)
{
	delay(100);
	uint8_t flag =1;
	char dummy[4] ="";							// Keyword
	char block[BLOCK_SIZE+1];				// Block with MAC, CoD y RSSI
	char number[4] ="";
	bool totalFound=false;

	#ifdef DEBUG_MODE
	char total[4] = "";
	#endif

	Utils.setLED(LED1, LED_ON);  // Inquiry while led on

	unsigned long previous=millis();
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
					#ifdef DEBUG_MODE
					total[0]=serialRead(_uartBT);
					total[1]=serialRead(_uartBT);
					total[2]=serialRead(_uartBT);
					#endif
				}
			}
		}

	// Condition to avoid an overflow (DO NOT REMOVE)
    if( millis() < previous ) previous=millis();
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
		snprintf(number, sizeof(number), "%02u", numberOfDevices);
		#ifdef DEBUG_MODE
		// Compare total of devices found and total of devices saved.

		// convert from string to int
		uint16_t a = atoi(total);

		if (a!=numberOfDevices)
		{
			PRINT_BT(F("+Maybe dev lost+\n"));
			flag = -2;
		}
			PRINT_BT(F("inquiried:"));
			USB.print(a);
			USB.print(F("; saved:"));
			USB.println(number);
		#endif

		// copy "Total: " from flash memory
		char TOTAL[20] ="";
		strcpy_P(TOTAL, (char*)pgm_read_word(&(table_BT[34])));

		if(!(SD.append(INQFILE,TOTAL)))
		{
			#ifdef DEBUG_MODE
			PRINT_BT(F(ERRORSD1));
			#endif
			flag = -3;
		}

		if(!(SD.appendln(INQFILE,number)))
		{
			#ifdef DEBUG_MODE
			PRINT_BT(F(ERRORSD1));
			USB.println();
			#endif
			flag = -3;
		}
		numLinesAfter++;
	}
    	Utils.setLED(LED1, LED_OFF);  // Inquiry while led on

   	return flag;
}

/*
 Function: Parses module answer trying to find specified MAC, stops inquiry when
 mac is found. if device is found, saved on position 0
 Returns: Returs 1 if found. 0 if not found.
 Parameters:
	inquiryTime: wait for module answer during this time.
	mac: mac of desired device.
 Values:
*/
bool  WaspBT_Pro::waitScanDeviceAnswer(unsigned long inquiryTime, char* mac)
{
	delay(100);
	char dummy[4] ="";
	bool found = false;
	char block[BLOCK_SIZE+1] ="";

	Utils.setLED(LED1, LED_ON);  // Inquiry while led on

	unsigned long previous=millis();
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
    	if( millis() < previous ) previous=millis();
	}

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

	// copy "%02u-%02u-%02u;%02u:%02u; %s; " from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[0])));

	// Build data and time string
	char dateTime[28] ="";
	snprintf(dateTime, sizeof(dateTime), aux,RTC.date,RTC.month,RTC.year,RTC.hour,RTC.minute, identifier);

	if(!(SD.append(INQFILE,dateTime)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif

		return 0;
	}

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
	char dummy[4] ="";
	uint8_t dummies = 0;

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

	#ifdef DEBUG_MODE
	PRINT_BT(F("Scanning names...\n"));
	#endif

	// copy "Friendly names: " from flash memory
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[1])));

	// appendln "Friendly names: "
	if(!(SD.appendln(INQFILE,aux)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		#endif
	}

numLinesAfter++;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long timeout = 60000;	// Timeout to wait for name responses.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned long previous=millis();
while( (millis()-previous<timeout) && (namesFound<numberOfDevices))
{

	dummies=0;

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

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
							PRINT_BT(F(ERRORSD1));
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
							PRINT_BT(F(ERRORSD1));
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
    if( millis() < previous ) previous=millis();
}

	// When lefting loop, If timeout is over
	if (millis()-previous<timeout)
	{
		//scanNetworkCancel();	//NO HACE NADA, hay que hacer un reset.
		reset();
		#ifdef DEBUG_MODE
		PRINT_BT(F("Timeout\n"));
		#endif
	}

#ifdef DEBUG_MODE
printBuffer2();
USB.println();
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
	char dev[60] ="";
	uint8_t x=1;

	// Saves mac
	for(uint8_t z=0;z<17;z++)
	{
		mac_address[z]=block[x];
		x++;
	}
	x++;

	// Saves CoD
	for(uint8_t z=0;z<6;z++)
	{
		CoD[z]=block[x];
		x++;
	}
	x= x+4;

	// Saves RSSI
	for(uint8_t z=0;z<3;z++)
	{
		RSSI[z]=block[x];
		x++;
	}

	// Classify CoD 	// Develop this part

	// Handsfree
	if (CoD[3]=='4')
	{
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

	// copy "%s; %s; %s; %c;" from flash memory
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[2])));

	snprintf(dev, sizeof(dev), aux, mac_address, CoD, RSSI, devClass[0]);

	// Inside data, Check inquiry file
	if ((SD.isFile(INQFILE))!=1)
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F("No file1\n"));
		#endif
		SD.create(INQFILE);
	}
	if(!(SD.appendln(INQFILE,dev)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
		flag = 0;
	}
	numLinesAfter++;

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
	memset(commandAnswer, 0x00, sizeof(commandAnswer) );
	i=0;
	while(serialAvailable(_uartBT))
	{
		commandAnswer[i]=serialRead(_uartBT);
		i++;
		// exit if maximum size is reached
		if( i >= sizeof(commandAnswer) )
		{
			break;
		}
		delay(10);
	}

	#ifdef DEBUG_MODE
	// print answer
	PRINT_BT(F("Command:"));
	for (uint8_t a = 0; a < i; a++)
	{
		USB.print(commandAnswer[a]);
	}
	USB.print(F("\t"));
	USB.println(F(""));
	#endif

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
	// define buffer
	char received[RX_BUFFER] ="";

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

	char received[RX_BUFFER] ="";
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

    snprintf(theCommand, sizeof(theCommand), "%s\r\n", theText);		// Adds CR+LF
  	serialFlush(_uartBT);
    printString(theCommand,_uartBT);
    delay(100);
}


/*
 Function: Sends a given command to bluetooth module, adding CR+LF.
 Returns:
 Parameters:
	theCommand: Command to send.
	length: command length.
 Values:
*/
void WaspBT_Pro::sendCommand(uint8_t * theCommand, uint16_t length)
{
    #ifdef DEBUG_MODE
	PRINT_BT(F("Command:"));
	USB.print(F("\t"));
	for(uint16_t a = 0; a < length; a++)
	{
		USB.printHex(theCommand[a]);
	}
	USB.println(F(""));
	#endif

	serialFlush(_uartBT);
    for(uint16_t b = 0; b < length; b++)
    {
      printByte(theCommand[b], _uartBT);
    }
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
	// copy "SET BT POWER %d %d %d" from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[3])));

	// Sets first two values to maximum by default
	snprintf(theCommand, sizeof(theCommand), aux, TX_POWER_DEFAULT_WT12, TX_POWER_MAX_WT12, power);
	sendCommand(theCommand);

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

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
	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

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
		PRINT_BT(F("dl1\n"));
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
		PRINT_BT(F(ERRORSD2));
		USB.println();
		#endif
		return 0;
		}
		else
		{
			// copy "INQFILEHEAD" from flash memory
			char INQFILEHEAD[20] ="";
			strcpy_P(INQFILEHEAD, (char*)pgm_read_word(&(table_BT[35])));

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

	i = 0;
	_baudrateBT = BT_BLUEGIGA_RATE;
	commandMode = 1;

	// set default name to avoid weird chars inside EEPROM
	char defaultName[] = "DEF_NAME";
	setNodeID(defaultName);


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

	// select multiplexer
    if (_uartBT == SOCKET0)	Utils.setMuxSocket0();
    if (_uartBT == SOCKET1)	Utils.setMuxSocket1();

	// open uart
	beginSerial(_baudrateBT,_uartBT);

	// power on the socket
    PWR.powerSocket(_uartBT, HIGH);

	// update Waspmote Register
	if (_uartBT == SOCKET0)	WaspRegister |= REG_SOCKET0;
	if (_uartBT == SOCKET1)	WaspRegister |= REG_SOCKET1;

	//~ beginSerial(_baudrateBT,_uartBT);
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
	// close uart
	closeSerial(_uartBT);

	// update Waspmote Register
	if (_uartBT == SOCKET0)	WaspRegister &= ~(REG_SOCKET0);
	if (_uartBT == SOCKET1)	WaspRegister &= ~(REG_SOCKET1);

	// unselect multiplexer
    if (_uartBT == SOCKET0) Utils.setMuxUSB();
    if (_uartBT == SOCKET1) Utils.muxOFF1();

	// switch module OFF
	PWR.powerSocket(_uartBT, LOW);

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
	// copy "sleep" from flash memory
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[4])));

    // send "sleep" command
	sendCommand(aux);

}

/*
 Function: Wake up Bluetotoh module from Sleep mode.
 Returns: '1' on success, '0' otherwise
 Parameters:
 Values:
*/
uint8_t WaspBT_Pro::wakeUp()
{

	char dummy[2] ="";
	uint8_t flag=0;


	// Necessary some dummy chars to wake up module by UART.
	sendCommand("at");
	sendCommand("at");
	sendCommand("at");
	delay(100);

	// Read an OK to confirm wake up process
	unsigned long previous = millis();
	while(serialAvailable(_uartBT) && (millis()-previous < 2000))
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

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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

	// copy "SET CONTROL CONFIG 0000 0101" from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[5])));

	// Enable RSSI for inquiry
	sendCommand(aux);
	delay(1000);

	// copy "SET CONTROL CONFIG LIST" from flash memory
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[6])));

	//check if configuration is OK
	sendCommand(aux);
	readCommandAnswer();

	#ifdef DEBUG_MODE
	//if(lookForAnswer(commandAnswer,"CONTROL CONFIG 0000 0000 0101")){

	// copy "CONTROL CONFIG 0000 0101" from flash memory
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[7])));
	if(lookForAnswer(commandAnswer, aux))
	{
		PRINT_BT(F("Configuration OK\n"));
	}
	else
	{

		PRINT_BT(F("Configuration failed\n"));
		flag=0;
	}
	#endif

	// copy "SET BT POWER 3 3 -2" from flash memory
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[8])));

	//SET defaul tx power to TX_POWER_5
	sendCommand(aux);
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

	// copy "RESET" from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[9])));

	sendCommand(aux);
	delay(2000);					// Reboot time
	readCommandAnswer();

	// copy "THOR" from flash memory
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[10])));
	if (lookForAnswer(commandAnswer,aux))
	{	// Searches keyword on answer.
		#ifdef DEBUG_MODE
		PRINT_BT(F("Ready\n"));
		#endif
	}
	else
	{
		PRINT_BT(F("BT_PRO module not detected\n"));
		#ifdef DEBUG_MODE
		PRINT_BT(F("Reset failed\n"));
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
	long a=0;
	char dummy[3] ="";
	char temperature[4] ="";

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

	// copy "temp" from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[11])));

	sendCommand(aux);
	delay(500);	// Necessary

	unsigned long previous = millis();
	while(serialAvailable(_uartBT) && (millis()-previous < 2000))
	{
		dummy[0]=serialRead(_uartBT);
		if (dummy[0]=='M')
		{
			dummy[1]=serialRead(_uartBT);
			if (dummy[1]=='P')
			{
				dummy[0]=serialRead(_uartBT);
				temperature[0]=serialRead(_uartBT);
				temperature[1]=serialRead(_uartBT);
				temperature[2]='\0';

				// convert from string to int
				a = atoi(temperature);
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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
	char dummy[4] ="";
	i=0;

	// copy "SET" from flash memory
	char aux[10] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[12])));

	// send "SET" command
	sendCommand(aux);

	delay(500);
	unsigned long previous = millis();
	while(serialAvailable(_uartBT) && (millis()-previous < 2000))
	{
		// check if "ADDR" is read:
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

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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
	char dummy[4] ="";
	uint8_t end=1;
	unsigned long previous;

	// Clear variable
	memset(friendlyName, 0x00, sizeof(friendlyName));

	// copy "SET" from flash memory
	char aux[10] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[12])));

	sendCommand(aux);

	delay(600);
	previous = millis();
	while(serialAvailable(_uartBT)  && (millis()-previous < 2000))
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
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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

	char namePublic[40] ="";
	i=0;
	uint8_t length = 0;

	while(publicName[i]!='\0') i++;
	length=i;

	// limit name length to 20
	if(length<20)
	{
		// copy "SET BT NAME %s_" from flash memory
		char aux[40] ="";
		strcpy_P(aux, (char*)pgm_read_word(&(table_BT[13])));

		// add end char for parsing public name
		snprintf(namePublic, sizeof(namePublic), aux, publicName);
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

	// Clear variable
	memset(theCommand, 0x00, sizeof(theCommand));

	if (txPower != power)changeInquiryPower(power);		// checks previous value. Change only if different.

	if (time==0) time =1;					// Min inquiry time
	if (time>48) time = 48;					// Max inquiry time


	inquiryTime = setInquiryTime(time);

	// write header for inquiry file
	SD.cd("..");

	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	PRINT_BT(F("numlines before:"));
	USB.println(numLinesBefore);
	#endif

	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif

	// copy "ScanNetwork" from flash memory
	char aux[40] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[14])));

	if(!(SD.appendln(INQFILE,aux)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	numLinesAfter++;

	// copy "inquiry %u" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[15])));

	snprintf(theCommand, sizeof(theCommand), aux, time);
	sendCommand(theCommand);

	numberOfDevices = 0;
	waitInquiryAnswer(inquiryTime, maxDevices, name, limited);

	// copy "---" from flash memory
	char ENDSTRING[20] ="";
	strcpy_P(ENDSTRING, (char*)pgm_read_word(&(table_BT[36])));

	// write line
	if(!(SD.appendln(INQFILE,ENDSTRING)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	numLinesAfter++;

	return numberOfDevices;
}

/*
 Function: It scans network and stops when finds "MAX_DEVICES". If max not
 reaches it scans max time (60s).
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

	// Clear variable
	memset(theCommand, 0x00, sizeof(theCommand));

	if (txPower != power)changeInquiryPower(power);		// Checks previous value. Change only if different.


	inquiryTime = setInquiryTime(48);

	// write header for inquiry file
	SD.cd("..");

	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	PRINT_BT(F("numlines before:"));
	USB.println(numLinesBefore);
	#endif

	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif

	// copy "ScanNetworkLimited. " from flash memory
	char aux[40] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[16])));

	if(!(SD.appendln(INQFILE,aux)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	numLinesAfter++;

	// copy "inquiry 48" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[17])));

	// Inquiry command for max time
	sendCommand(aux);

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
		PRINT_BT(F(ERRORSD1));
		USB.println();
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

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

	// Checks previous value. Change only if different.
	if (txPower != power)changeInquiryPower(power);

	if (maxTime==0) maxTime =1;				// Min inquiry time
	if (maxTime>48) maxTime = 48;				// Max inquiry time


	inquiryTime = setInquiryTime(maxTime);

	// write header for inquiry file
	SD.cd("..");


	// Read line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	PRINT_BT(F("numlines before:"));
	USB.println(numLinesBefore);
	#endif


	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif

	// copy "ScanDevice: " from flash memory
	char aux[40] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[18])));

	// append "ScanDevice: "
	if(!(SD.append(INQFILE,aux)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	if(!(SD.appendln(INQFILE,Mac)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	numLinesAfter++;

	// copy "inquiry %u" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[15])));
	snprintf(theCommand, sizeof(theCommand), aux, maxTime);
	sendCommand(theCommand);

	numberOfDevices = 0;

	if(waitScanDeviceAnswer(inquiryTime,Mac))
	{
		// write end line
		if(!(SD.appendln(INQFILE,";")))
		{
			#ifdef DEBUG_MODE
			PRINT_BT(F(ERRORSD1));
			USB.println();
			#endif
		}
		numLinesAfter++;
		//numLinesAfter = SD.numln(INQFILE);

		return 1;
	}
	else
	{
		// copy "Not found." from flash memory
		strcpy_P(aux, (char*)pgm_read_word(&(table_BT[19])));

		// write end line
		if(!(SD.appendln(INQFILE,aux)))
		{
			#ifdef DEBUG_MODE
			PRINT_BT(F(ERRORSD1));
			USB.println();
			#endif
		}
		numLinesAfter++;
		if(!(SD.appendln(INQFILE,";")))
		{
			#ifdef DEBUG_MODE
			PRINT_BT(F(ERRORSD1));
			USB.println();
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

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );

	if (txPower != power)changeInquiryPower(power);		// checks previous value. Change only if different.

	if (time==0) time =1;					// Min inquiry time
	if (time>48) time = 48;					// Max inquiry time


	inquiryTime = setInquiryTime(time);

	// write header for inquiry file
	SD.cd("..");


	// Set line number before start a new inquiry
	numLinesBefore = numLinesAfter;

	#ifdef DEBUG_MODE
	PRINT_BT(F("numlines before: "));
	USB.println(numLinesBefore);
	#endif


	#ifdef ENABLE_DATE_AND_TIME
	getSetDateID();
	#endif

	// copy "ScanNetworkName" from flash memory
	char aux[40] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[20])));

	// append "ScanNetworkName"
	if(!(SD.appendln(INQFILE, aux)))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
		#endif
	}
	numLinesAfter++;

	// copy "inquiry %u name" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[21])));

	snprintf(theCommand, sizeof(theCommand), aux, time);
	sendCommand(theCommand);

	numberOfDevices = 0;

	waitInquiryAnswer(inquiryTime, maxDevices, name, limited);

	// write end line
	if(!(SD.appendln(INQFILE,";")))
	{
		#ifdef DEBUG_MODE
		PRINT_BT(F(ERRORSD1));
		USB.println();
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

	USB.println();
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
	unsigned long previous;
	uint8_t connected = 0;

	// copy "ScanNetworkName" from flash memory
	char target[10] ="";
	char connectMode[10] ="";
	char aux[20] ="";
	// copy "1101" from flash memory
	strcpy_P(target, (char*)pgm_read_word(&(table_BT[22])));
	// copy "RFCOMM" from flash memory
	strcpy_P(connectMode, (char*)pgm_read_word(&(table_BT[23])));
	// copy "call %s %s %s" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[24])));

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );


	// Build call command. Example: CALL 00:07:80:80:52:27 1101 RFCOMM
	snprintf(theCommand, sizeof(theCommand), aux, mac, target, connectMode);

	// Send call command
	sendCommand(theCommand);

	// Wait CALL {link_id}
	readCommandAnswer();

	// copy "CALL" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[25])));

	if (!lookForAnswer(commandAnswer, aux))
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

	// copy "CONNECT" from flash memory
	char CONNECT[20] ="";
	strcpy_P(CONNECT, (char*)pgm_read_word(&(table_BT[26])));

	// copy "NO CARRIER" from flash memory
	char NO_CARRIER[20] ="";
	strcpy_P(NO_CARRIER, (char*)pgm_read_word(&(table_BT[27])));

	previous = millis();
	while((!connected) && (millis()-previous < 5000))
	{
		readCommandAnswer();

		if(lookForAnswer(commandAnswer, CONNECT))
		{
			connected = 1;
			commandMode = 0;
		}
		else if (lookForAnswer(commandAnswer, NO_CARRIER))
		{
			return 0;
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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
	unsigned long previous;
	uint8_t flag =0;

	// enter command mode
	if (!enterCommandMode()) return 0;

	for (i = 0; i < COMMAND_SIZE; i++) theCommand[i] = '\0';

	// copy "CLOSE 0" from flash memory
	char aux[20] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[28])));

	// send close command CLOSE {link_id}
	// Build call command. By default, linkID=0.
	snprintf(theCommand, sizeof(theCommand), aux);

	// Send call command
	sendCommand(theCommand);

	// copy "ERROR 0" from flash memory
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[29])));

	// Check if connection removed OK
	// NO CARRIER {link_id} ERROR {error_code}
	previous = millis();
	while((!flag) && (millis()-previous < 10000))
	{
		readCommandAnswer();

		// look for error code = 0
		if(lookForAnswer(commandAnswer, aux))
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
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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
	for (uint16_t i = 0; i < length; i++)
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
	unsigned long previous;

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

	// copy "READY" from flash memory
	char READY[20] ="";
	strcpy_P(READY, (char*)pgm_read_word(&(table_BT[30])));

	// look for ready
	previous = millis();
	while((!commandMode) && (millis()-previous < 5000))
	{
		readCommandAnswer();
		if(lookForAnswer(commandAnswer, READY))
		{
			commandMode = 1;
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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
	char dummy[4] ="";
	char active[2] ="x";
	unsigned long previous;

	// check if already in command mode
	if (!commandMode)
	{
		if(enterCommandMode()) flag =1;
		else return -1;
	}

	// copy "LIST" from flash memory
	char LIST[20] ="";
	strcpy_P(LIST, (char*)pgm_read_word(&(table_BT[31])));

	// LIST {num_of_connections}
	// Send call command
	sendCommand(LIST);

	// parse answer
	delay(500);

	// read first dummy bytes
	if(serialAvailable(_uartBT) )
	{
		for(uint8_t i=0;i<5;i++) dummy[0]=serialRead(_uartBT);
	}

	previous = millis();
	while(serialAvailable(_uartBT) && (!found) && (millis()-previous < 10000))
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
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
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

	// copy "RSSI %u" from flash memory
	char aux[20] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[32])));

	// send rssi command RSSI {link_id}
	snprintf(theCommand, sizeof(theCommand), aux, linkID);

	// Send call command
	sendCommand(theCommand);

	delay(200);

	// copy "ERROR" from flash memory
	char ERROR[20] ="";
	strcpy_P(ERROR, (char*)pgm_read_word(&(table_BT[33])));

	// response: RSSI {bd_addr} {rssi}
	// syntax error if linkID not active.

	readCommandAnswer();
	if(lookForAnswer(commandAnswer, ERROR)) return -2;
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
	if (flag>900)	PRINT_BT(F("_-OVERFLOW-_\n"));

}

// Test purposes only
void WaspBT_Pro::printBuffer2()
{
	int flag= serialAvailable(_uartBT);
	if (flag>900)	PRINT_BT(F("_-*OVERFLOW in summary*-_\n"));

}
#endif

/*
 Function: Pair with other module. Default code 123456.
 Returns: 	'1' if pairing ok, '0' otherwise.
 Parameters: char* macAddress: Mac address of the device to pair.
 Values:
*/
uint8_t WaspBT_Pro::pair(char* macAddress)
{
	char pinCode[] = "123456";
	return pair(macAddress, pinCode);
}

/*
 Function: Pair with other module, specifying Pin code. It has a timeout
 * of 20 seconds.
 * Note: the AUTH event can be enabled to see when a device is
 * trying to pair.
 Returns: 	'1' if pairing ok, '0' otherwise.
 Parameters: char* macAddress: Mac address of the device to pair.
 * char * pincode: PIN code for the connection.
 Values:
*/
uint8_t WaspBT_Pro::pair(char* macAddress, char * pinCode)
{
	// set code for pairing
	// copy "SET BT AUTH * %s" from flash memory
	uint8_t found = 0;
	char dummy[3] ="";
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[37])));
    snprintf(theCommand, sizeof(theCommand), aux, pinCode);
	sendCommand(theCommand);

	// clear variable
	memset(theCommand, 0x00, sizeof(theCommand) );
	memset(aux, 0x00, sizeof(aux) );

	// Now try to pair, copy from flash "PAIR %s"
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[38])));
	snprintf(theCommand, sizeof(theCommand), aux, macAddress);
	sendCommand(theCommand);

	memset(aux, 0x00, sizeof(aux) );
	strcpy_P(aux, (char*)pgm_read_word(&(table_BT[39])));

	// wait 20 seconds for succesfull pairing.
	unsigned long previous = millis();
	while((millis()-previous < 20000) && !found)
	{
		//default answers: if OK: PAIR [MAC] OK; if fail: PAIR [MAC] FAIL.
		// look for 'OK'
		// check if "PAIR" is read:
		if (serialAvailable(_uartBT))
		{
			dummy[0]=serialRead(_uartBT);
			if (dummy[0]=='O')
			{
				dummy[1]=serialRead(_uartBT);
				if (dummy[1]=='K')
				{
					found = 1;
				}
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	if (found)
	{
		// paired OK.
		return 1;
	}

	// Paired failed
	return 0;
}

/*
 Function: removes all paired devices.
 Returns:
 Parameters:
 Values:
*/
void WaspBT_Pro::removePairedDevices()
{
	// copy "SET BT PAIR *" from flash memory
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[40])));
    sendCommand(aux);

}

/*
 Function: removes all paired devices.
 * mac address must not have capital leters:
 * ok    --> "00:1a:f0:90:b3:c8"
 * wrong --> "00:1A:F0:90:B3:C8"
 Returns: 	returns '1' if pared, '0' otherwise
 Parameters: char * deviceMac: device to check pairing.
 Values:
*/
uint8_t WaspBT_Pro::isPaired(char * deviceMac)
{
	uint8_t found = 0;
	char dummy[4] ="";
	i=0;
	// copy "SET" from flash memory
	char aux[20] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_BT[12])));
    sendCommand(aux);

    memset(aux, 0x00, sizeof(aux));

    /*example of SET response:
     *  SET BT BDADDR
        (...)
		SET BT PAGEMODE 3 2000 1
		SET BT PAIR 2c:44:01:7f:f8:03 9edc4e7e8ecdc556cd361f70eb510405
		SET BT PAIR 00:1a:70:90:b3:28 f92e3335a4119e73b339d71ae3fccca3
		SET BT POWER 3 3 -2
		SET BT ROLE 0 f 7d00
	*/

    // answer to look to be buffered, look dinamically.
    delay(500);
	unsigned long previous = millis();
	while(serialAvailable(_uartBT) && (millis()-previous < 2000) && !found)
	{
		// check if "PAIR" is read:
		dummy[0]=serialRead(_uartBT);
		if (dummy[0]=='P')
		{
			dummy[1]=serialRead(_uartBT);
			if (dummy[1]=='A')
			{
				dummy[0]=serialRead(_uartBT);
				if (dummy[0]=='I')
				{
					dummy[1]=serialRead(_uartBT);
					if (dummy[1]=='R')
					{
						dummy[0]=serialRead(_uartBT);
						if (dummy[0]==' ')
						{

							// check mac of paired device
							for (i=0; i<17; i++)
							{
								aux[i]=serialRead(_uartBT);
							}

							#ifdef DEBUG_MODE
							PRINT_BT("aux: ");
							USB.println(aux);
							PRINT_BT("device mac: ");
							USB.println(deviceMac);
							#endif

							// check if right device
							if(!strcmp(deviceMac, aux) )
							{
								found = 1;
							}
						}
					}
				}
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}
	delay(500);
	serialFlush(_uartBT);	// delete all other dummy information
	delay(200);

	if (found)
	{
		return 1;
	}

	return 0;
}

WaspBT_Pro BT_Pro=WaspBT_Pro();		//object
