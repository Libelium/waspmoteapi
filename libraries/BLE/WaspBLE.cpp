/*
 *  Library for managing the Bluetooth low energy BLE112
 *
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.2
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */
#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspBLE.h"


/******************************************************************************
 * FLASH DEFINITIONS
 ******************************************************************************/

/// table_BLE ///////////////////////////////////////////////////////
const char	ble_string_00[]	PROGMEM = "0000070C";	// 0
const char ble_string_01[] PROGMEM = "Scan params: ";	// 1
const char ble_string_02[] PROGMEM = "1%02x%02x%02x%02x%02x%02x; %d; %u;\r\n";	// 2
const char ble_string_03[] PROGMEM = "D:%x%x%x%x%x%x; %d,"; // 3
const char ble_string_04[] PROGMEM = "; Index=%u\r\n"; // 4
const char ble_string_05[] PROGMEM = "Stop fail. err: %x\n"; // 5
const char ble_string_06[] PROGMEM = "Scan fail. err: %x\n"; // 6
const char ble_string_07[] PROGMEM = "Scan params: GAP mode=%u; scan_interval=%u: scan_window=%u; scan_duplicate_filtering=%u; TXPower=%u;\r\n"; // 7
const char ble_string_08[] PROGMEM = "Device %u; %02x%02x%02x%02x%02x%02x; RSSI:%d; Name:"; //8
const char ble_string_09[] PROGMEM = "error writing. err: %x\n"; //9
const char ble_string_10[] PROGMEM = "\t ec: %x\r\n"; //10
const char ble_string_11[] PROGMEM = "ADCval(HEX):%x\r\n"; //11
const char ble_string_12[] PROGMEM = "ADCval(DEC):%d\r\n"; //12
const char ble_string_13[] PROGMEM = "ADCValmV(DEC):%s\r\n"; // 13
const char ble_string_14[] PROGMEM = "Ta(DEC):%s\r\n"; //14
const char ble_string_15[] PROGMEM = "Attribute %u Indicated!\r\n"; //15

const char* const table_BLE[] PROGMEM =
{
	ble_string_00,		// 0
	ble_string_01,		// 1
	ble_string_02,		// 2
	ble_string_03, 		// 3
	ble_string_04,		// 4
	ble_string_05,		// 5
	ble_string_06,		// 6
	ble_string_07,		// 7
	ble_string_08,		// 8
	ble_string_09,		// 9
	ble_string_10,		// 10
	ble_string_11,		// 11
	ble_string_12,		// 12
	ble_string_13,		// 13
	ble_string_14,		// 14
	ble_string_15,		// 15
};

/******************************************************************************
 * User API
 ******************************************************************************/


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

/* Looks for initial command ,: 80 0C 00 00 01 00 02 00 01 00 03 00 01 01
 * First four bytes are the packet header:
 * 80 = packet type (0x80 = event)
 * 0C = data length (0x0C = 12 bytes)
 * 00 = class (0x00 = system)
 * 00 = specific event (0x00 = boot)
 * (...)
*/
/*
 Function: Initializes some variables and module parameters
 Returns: Return 1 if OK, 0 if error configuring a parameter. check flag.
 Parameters:
 Values:
*/
uint8_t WaspBLE::init()
{
	uint8_t flag = 0;

	// end other previous procedures
	endProcedure();

	// configure other default parameters:

	// set MAC filter ON. Mandatory to use discoveredDevices variable.
	if (setFiltering(BLE_MAC_FILTER_ENABLED) == 0)
	{
		// Update global
		scan_duplicate_filtering = BLE_MAC_FILTER_ENABLED;
	}
	else
	{
		#if BLE_DEBUG > 0
		PRINT_BLE(F("error MAC filter\n"));
		#endif
		flag = 2;
	}

	#ifdef ENABLE_EEPROM_SAVING
	// set EEPROM
	Utils.writeEEPROM(scanIndex,SCAN_END);
	Utils.writeEEPROM(scanIndex+1,SCAN_END);
	#endif

	if (flag != 0 )
	{
		return 0;
	}
	else
	{
		#if BLE_DEBUG > 0
		PRINT_BLE(F("BLE init ok\n"));
		#endif
		return 1;
	}
}


/* packet format - always without hardware flow control - with length field at the beginning
 *
 *  FIELD:   |  LENGTH  |  MSG TYPE  |  TECHNOLOGY TYPE  |  LENGTH HIGH  |  LENGTH LOW  |  CLASS ID  |  COMMAND ID  |  PAYLOAD       |
 *  LENGTH:  |  8 bit   |  1 bit     |      4 bit        |     3 bit     |    8 bit     |    8 bit   |    8 bit     |  0-2048 bytes  |
 *  EXAMPLE:      06          00                                                02           06             01            02 02
*/
/*
 Function: Sends a binary command to the BLE module by UART interface
 Returns: return 1 if command > 128 bytes; 0 otherwise.
 Parameters:
	max packet size = 64 bytes. Max payload size = 60 bytes.
	LL: payload length, low bits.
	CID: command class ID
	CMD: Command ID
	PL: payload
 Values:
*/
uint16_t WaspBLE::sendCommand(uint8_t LL, uint8_t CID, uint8_t CMD, uint8_t * PL)
{
	// variable to manage command index
	uint16_t index = 0;

	// Limit the size of the command for security to the maximum allowed by protocol. 60 bytes.
	if ( LL > 60)
	{
		// invalid command
		return 1;
	}

	// create local variable to store the command to be sent, according to command length
	uint8_t command[LL+5];

	// clear variable
	memset(command, 0x00, sizeof(command) );

	// First byte is total command length.
	// Only valid for payloads lower that 123 bytes which is the case of BGAPI.
	command[index++] = LL+4;

	// Message type : command
	command[index++] = 0x00;

	// Length low //
	command[index++] = LL;

	// Class ID
	command[index++] = CID;

	// Command ID
	command[index++] = CMD;

	// For frames with no payload,
	if (LL > 0)
	{
		for (uint8_t i = 0; i < LL; i++)
		{
			command[index++] = PL[i];
		}
	}

	#if BLE_DEBUG>1
	PRINT_BLE(F("Cmd: "));
	for(uint8_t i = 0; i < index; i++)
	{
		USB.printHex(command[i]);
	}
	USB.println();
	#endif

	// send
	serialFlush(_uartBT);
    for(uint8_t i = 0; i < index; i++)
    {
      printByte(command[i], _uartBT);
    }

	return 0;
}

/*
 Function: Sends a custom command to the BLE module. Packet mode is mandatory.
 Returns: return 1 if command > 64 bytes; 0 otherwise.
 Parameters:
	cusstomCommand: Command to be sent
	length: length of the command
 Values:
*/
uint16_t WaspBLE::sendCommand(uint8_t * customCommand, uint8_t length)
{
	// check if command is too long. Maximum allowed size is 64.
	if (length > 64)
	{
		return 1;
	}

	#if BLE_DEBUG>1
	PRINT_BLE(F("Custom Cmd: "));
	for(uint8_t i = 0; i < length; i++)
	{
		USB.printHex(customCommand[i]);
	}
	USB.println();
	#endif

	// send
	serialFlush(_uartBT);
    for(uint8_t i = 0; i < length; i++)
    {
		printByte(customCommand[i], _uartBT);
    }

	return 0;
}

/*
 Function: Sends a custom command to the BLE module. Packet mode is mandatory.
 Returns: return 1 if command > 64 bytes; 0 otherwise.
 Parameters:
	cusstomCommand: Command to be sent
 Values:
*/
uint16_t WaspBLE::sendCommand(char * customCommand)
{
	uint8_t customCommandLength = strlen(customCommand) / 2;

	// check length
	if (customCommandLength > 64)
	{
		return 1;
	}

	uint8_t customCommandArray[customCommandLength];
	Utils.str2hex(customCommand, customCommandArray);

	return sendCommand(customCommandArray, customCommandLength);
}


/*
 Function: Reads and stores module answer. The module last about 20 milliseconds  max to answer a command.
 * By default read max allowed bytes if possible
 Returns: error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::readCommandAnswer()
{
	return readCommandAnswer(MAX_PACKET_SIZE,1);
}


/*
 Function: Reads and stores module answer. The module last about 20 milliseconds max to answer a command.
 Returns: error code. 0 if OK, error code otherwise. FFFF means no module answer
 Parameters:
 Values:
*/
uint16_t WaspBLE::readCommandAnswer(uint8_t answerLength, uint8_t ExpectedErrCode)
{
	memset(answer, 0x00, sizeof(answer) );
	uint8_t i = 0;
	// while pending data or data available on RX buffer.
	// Added a timeout to avoid stopping the code.
	unsigned long previous = millis();
	//while( ((i < answerLength) && ((millis() - previous) < ANSWER_TIMEOUT)) || (serialAvailable(_uartBT)  ) )
	while( ((i < answerLength) || (serialAvailable(_uartBT)  ) ) && ((millis() - previous) < ANSWER_TIMEOUT) )
	{
		 if(serialAvailable(_uartBT) > 0)
		{
			answer[i] = serialRead(_uartBT);
			i++;

			// exit if maximum size is reached
			if( i >= answerLength )
			{
				break;
			}

			// exit if maximum size is reached
			if( i >= sizeof(answer) )
			{
				break;
			}
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// save error code. Take into account some answers with no error code.

	if (ExpectedErrCode == 1)
	{
		errorCode = ((uint16_t)answer[i-1] << 8) | answer[i-2];
	}
	else
	{
		errorCode = 0;
	}

	// Ensure there was module response, if not, set error code to
	if ( i == 0 )
	{
		// error code is set to FFFF to indicate there was no answer from module.
		errorCode = 65535;
	}

	#if BLE_DEBUG > 1
	// print answer
	PRINT_BLE(F("Ans: "));
	for (uint8_t a = 0; a < i; a++)
	{
		USB.printHex(answer[a]);
	}
	char message[30]= "";
	strcpy_P(message, (char*)pgm_read_word(&(table_BLE[10])));
	PRINT_BLE(F(""));
	USB.printf(message,errorCode);
	#endif

	return errorCode;
}


/*
 Function: parses a scan response event, saving each device data field separately.
 Returns: return 0 if not an ble_evt_gap_scan_response, 2 if EEPROM limit reached (only if EEPROM saving is valid)
 Parameters:
	friendlyName: used to save friendly name. 0 if not used, 1 otherwise.
 Values:
*/
/*
 * Field:	| Message type | Payload| Msg Class	| Msg ID | RSSI | packet type |    sender    | address type | bond |   data   |
 * Length:  |       1      |    1   |     1     |    1   |  1   |      1      |      6       |      1       |   1  |     x    |
 * Example: |      80      |   0E   |     06    |   00   |  C3  |     00      | B9C153800700 |      00      |  FF  | 03020106 |
 */
uint8_t WaspBLE::parseScanEvent(uint8_t friendlyName)
{

	// varable used to choice how to save friendly name.
	uint8_t nameFlag = 0;

	if ((event[0] != 0x80) && (event[2] != 0x06) && (event[3] != 0x00))
	{
		// not a scan event
		return 0;
	}

	uint8_t b = 5;
	for(uint8_t a = 0; a < 6 ; a++)
	{
		BLEDev.mac[a] = event[b+6];
		b--;
	}

	BLEDev.rssi = event[4];

	// save advertisement Data
	uint8_t advDataLength = event[14];
	// Protect against overflows. data can not be greater than 31 bytes.
	if (advDataLength > 31)
	{
		advDataLength = 31;
	}
	// erase previous advData
	memset(BLEDev.advData, 0x00, sizeof(BLEDev.advData));

	for(uint8_t a = 0; a < advDataLength+1 ; a++)
	{
		BLEDev.advData[a] = event[a+14];

	}

	// if friendly name is enabled, then try to parse it from advData.
	if (friendlyName == 1)
	{
		nameFlag = parseName();
	}
	else
	{
		//erase name variable to avoid conflicts
		memset(BLEDev.friendlyName, 0x20, sizeof(BLEDev.friendlyName));
	}

	//++++++++++++++++++++++++++++++++++++++
	// Count discovered devices.
	//++++++++++++++++++++++++++++++++++++++
	// When scan_duplicate_filtering is 1, each device will send two events (with active scanning)
	// When scan_duplicate_filtering is 0, each device produce multiple events, and variable numberofDevices will be -1.
	if (memcmp(BLEDev.mac, previousMAC,6) != 0)
	{
		//different device
		numberOfDevices++;
		memcpy(previousMAC,BLEDev.mac,6);

		#ifdef ENABLE_EEPROM_SAVING
		// save decice on EEPROM
		if (saveDevice(nameFlag) == 0)
		{
			return 2;
		}
		#endif
	}

	// information to show in debug mode:
	// | MAC | RSSI | packet type | data |
	#if BLE_DEBUG > 0
	// copy "%02x%02x%02x%02x%02x%02x; %d; %u;\r\n" from flash memory
	char message[50] = "";
	strcpy_P(message, (char*)pgm_read_word(&(table_BLE[2])));
	PRINT_BLE(F(""));
	USB.printf(message,BLEDev.mac[0],BLEDev.mac[1],BLEDev.mac[2],BLEDev.mac[3],BLEDev.mac[4],BLEDev.mac[5],BLEDev.rssi, event[5]);
	PRINT_BLE(F("BLEDev.advData:"));
	for (uint8_t a = 0; a < advDataLength+1; a++)
	{
		USB.printHex(BLEDev.advData[a]);
	}
	USB.println();
	USB.println();
	#endif
	return 1;
}

/*  Advertisement data structure (31 bytes) acording Bluetooth standard.
 * ------------------------------------------------------------------------------
 * |                            advertisement data                                |
 * ------------------------------------------------------------------------------
 * | advLength |          FIELD 1            |          FIELD 2            | (...)|
 * ---------------------------------------------------------------------------
 * |           | length1 |      data         | length2 |      data         | (...)|
 * ---------------------------------------------------------------------------
 * |           |         | AD_Type | AD_Data |         | AD_Type | AD_Data | (...)|
 * ------------------------------------------------------------------------------
*/
/*
 Function: looks into advertisement data and saves the friendly name of the device.
 Returns: 0 if name not found, 1 if complete name found, 2 if shortened name found.
 Parameters:
 Values:
*/
uint8_t WaspBLE::parseName()
{
	uint8_t nameFound = 0;
	uint8_t advLength = 0;
	uint8_t fieldLength = 0;
	uint8_t ADType = 0;

	// clear variable
	memset(BLEDev.friendlyName,0x00,sizeof(BLEDev.friendlyName));

	// look inside BLEDev.advData for the friendly name field.
	uint8_t i = 0;
	advLength = BLEDev.advData[i++];

	while ((!nameFound) && (i < advLength))
	{
		// read field
		fieldLength = BLEDev.advData[i++];
		ADType = BLEDev.advData[i++];

		if (ADType == 0x09)
		{
			// Complete local name field
			// limit name length to 31 bytes
			if (fieldLength > 31) fieldLength = 31;

			// Copy AD_Data field to BLEDev.friendlyName
			for(uint8_t a = 0; a < fieldLength-1; a++)
			{
				BLEDev.friendlyName[a] = BLEDev.advData[i++];
			}
			nameFound = 1;
		}
		else
		{
			if (ADType == 0x08)
			{
				// shortened local name field

				// limit name length to 31 bytes
				if (fieldLength > 31) fieldLength = 31;

				// Copy AD_Data field to BLEDev.friendlyName
				for(uint8_t a = 0; a < fieldLength-1; a++)
				{
					BLEDev.friendlyName[a] = BLEDev.advData[i++];
				}
				nameFound = 2;
			}
			else
			{
				// No local name field. read field and discard it.
				i = i + (fieldLength-1);
			}
		}
	}

	return nameFound;
}


/*
 Function: save discovered device on EEPROM
 * EEPROM managing.
 * Inquiries are saved from position SCAN_EEPROM_START_ADDRESS (1024), according to struct DiscoveredDevice.
 * saved devices are limited to 100 by default, but it can be changed.
 *
 * Note: if a device has no friendly name available, an empty field will be used.
 Returns: return 0 if limit reached. 1 otherwise.
 Parameters:
 Values:
*/
#ifdef ENABLE_EEPROM_SAVING
uint16_t WaspBLE::saveDevice(uint8_t nameFlag)
{
	// EEPROM usage for saving scans is limited to 700 bytes by default.
	// check if this limit is reached.
	if ( scanIndex == SCAN_EEPROM_LIMIT_ADDRESS)
	{
		return 0;
	}

	// save the MAC address
	for(uint8_t a = 0; a < 6 ; a++)
	{
		Utils.writeEEPROM(scanIndex,BLEDev.mac[a]);
		scanIndex++;
	}

	// save RSSI
	Utils.writeEEPROM(scanIndex,BLEDev.rssi);
	scanIndex++;

	/* NOTE: if the user does not want to save name when it is not present,
	name flag can be used for that purpose. unncomment part A, and comment part B.
	*/

	/*
	//PART A
	// save friendly name despite it can not be available
	// 0 if name not found, 1 if complete name found, 2 if shortened name found.
	if (nameflag == 1)
	{
		for(uint8_t a = 0; a < 31; a++)
		{
			Utils.writeEEPROM(scanIndex,BLEDev.friendlyName[a]);
			scanIndex++;
		}
	}
	//END of PART A
	*/


	// PART B
	// save friendly name despite it can not be available
	for(uint8_t a = 0; a < 31; a++)
	{
		Utils.writeEEPROM(scanIndex,BLEDev.friendlyName[a]);
		scanIndex++;
	}
	// end of PART B



	// add end of scan, but not increment scanIndex
	Utils.writeEEPROM(scanIndex,SCAN_END);
	Utils.writeEEPROM(scanIndex+1,SCAN_END);

	#if BLE_DEBUG > 1
	// copy from flash "D:%x%x....
	char message[30]= "";
	strcpy_P(message, (char*)pgm_read_word(&(table_BLE[3])));
	PRINT_BLE(F(""));
	USB.printf(message,
		BLEDev.mac[0],
		BLEDev.mac[1],
		BLEDev.mac[2],
		BLEDev.mac[3],
		BLEDev.mac[4],
		BLEDev.mac[5],
		BLEDev.rssi);
	PRINT_BLE(F(""));
	for(uint8_t a = 0; a < 31 ; a++)
	{
		USB.print(BLEDev.friendlyName[a]);
	}
	memset(message, 0x00, sizeof(message));
	// copy from flash "; Index=%u\r\n
	strcpy_P(message, (char*)pgm_read_word(&(table_BLE[4])));
	USB.printf(message,scanIndex);
	#endif

	return 1;
}
#endif


/******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

/*
 Function: Constructor
 Returns:
 Parameters:
 Values:
*/
WaspBLE::WaspBLE()
{
	_baudrateBT = BT_BLUEGIGA_RATE;

	errorCode = 0;

	memset(previousMAC, 0x00, sizeof(previousMAC));

	TXPower = TX_POWER_MAX;

	// Initialize scan parameters
	// default values of scanning parameters

	GAP_discover_mode = BLE_GAP_DISCOVER_OBSERVATION;
	GAP_discoverable_mode = BLE_GAP_NON_DISCOVERABLE;
	GAP_connectable_mode = BLE_GAP_NON_CONNECTABLE;

	scan_interval = 75;
	scan_window = 50;
	scan_policy = BLE_GAP_SCAN_POLICY_ALL;
	adv_policy = BLE_GAP_ADV_POLICY_ALL;


	// to manage EEPROM
	scanIndex = SCAN_EEPROM_START_ADDRESS;

}

/*
 Function: Turns on Bluetooth module.
 Returns: '1' on success, '0' if error.
 Parameters: UartMode should be 0 for SOCKET0 and 1 for SOCKET1
 Values:
*/
int8_t WaspBLE::ON(uint8_t UartMode)
{
	// prevent bad uart number. By default UART1
	if (UartMode >= 2) _uartBT = 1;
	else _uartBT = UartMode;

    // power on the socket
    PWR.powerSocket(_uartBT, HIGH);

	// delay to power up.
	delay(100);

	// Now enable wake up pin and look for wake up event. if not present, look if reset event.
	// if no reset event, software reset to check communication.
	// wake up returns 1 if ok, 0 if no event found or 2 if other envent.

	if (wakeUp() != 1)
	{
		#if BLE_DEBUG > 1
		PRINT_BLE(F("no wakeUp ev.\n"));
		#endif

		// check if event read is boot event
		if ((event[1] == 0x0C) && (event[2] == 0x00) && (event[3] == 0x00))
		{
			#if BLE_DEBUG > 1
			PRINT_BLE(F("reset ev.\n"));
			#endif
			// reset event found.
			return init();
		}

		// no wake up event found. software reset.
		if (reset() == 0)
		{
			#if BLE_DEBUG > 1
			PRINT_BLE(F("reset fail\n"));
			#endif
			PRINT_BLE(F("BLE module not detected\n"));

			// Set red led to advise user.
			Utils.setLED(LED0, LED_ON);
			delay(30000);
			Utils.setLED(LED0, LED_OFF);
			return 0;
		}
	}

	return init();
}

/*
 Function: Turns on Bluetooth module. By default UART1
 Returns: '1' os success, '0' if error.
 Parameters:
 Values:
*/
int8_t WaspBLE::ON()
{
	return ON(SOCKET1);
}

/*
 Function: Turns off Bluetooth module.
 Returns:
 Parameters:
 Values:
*/
void WaspBLE::OFF()
{
	// close UART.
	closeSerial(_uartBT);

	// update Waspmote Register
	if (_uartBT == SOCKET0)	WaspRegister &= ~(REG_SOCKET0);
	if (_uartBT == SOCKET1)	WaspRegister &= ~(REG_SOCKET1);

	// to disable wake up pin.
	sleep();

	// unselect multiplexer
    if (_uartBT == SOCKET0) Utils.setMuxUSB();
    if (_uartBT == SOCKET1) Utils.muxOFF1();

	// switch module OFF
	PWR.powerSocket(_uartBT, LOW);
}


/*
 Function: Set TX power.
 Returns: return 0 if OK, 1 if error. this command does not return error code.
 Parameters: Power: can be a value between 0 and 15 which give the real TX power from -23 to +3dBm
 Values:
*/
uint16_t WaspBLE::setTXPower(uint8_t power)
{
	char buffer[10] ="";

	// limit power to effective range.
	if (power > 15)
	{
		power = 15;
	}

	sendCommand(1,7,12,&power);

	// Response of 4 bytes, no error code.
	readCommandAnswer(4,0);

	// this command does not return error code.
	Utils.hex2str(answer,buffer,4);

	// copy "0000070c" from flash memory
	char answerOK[10] ="";
	strcpy_P(answerOK, (char*)pgm_read_word(&(table_BLE[0])));

	if (strcmp(buffer,answerOK) == 0)
	{
		// ok, update global
		TXPower = power;
		return 0;
	}
	else
	{
		// error
		return 1;
	}
}

/*
 Function: sends reset command to the module. Resets in normal mode
 Returns: '1' if reset OK, '0' if no answer from module.
 Parameters:
 Values:
*/
uint8_t WaspBLE::reset()
{
	// 00 01 09 00 00
	sendCommand(1,9,0,0);

	// delay till reset
	delay(500);

	// look for System Boot event.
	//readCommandAnswer(16,0);

	if(waitEvent(1000) == BLE_EVENT_SYSTEM_BOOT)
	{
		// reset event found.
		return 1;
	}
	else return 0;

}


/*
 Function: Makes an inquiry to discover specific device by its Mac.
 Returns: '0' if not found. '1' if found, error code otherwise.
 Parameters:
	Mac: Mac of device to discover
 Values:
*/
uint16_t WaspBLE::scanDevice(char * Mac)
{
	uint8_t macByteArray[6];

	//limit size of char * mac
	if (strlen(Mac) > 13)
	{
		Mac[12] = '\0';
	}

	// To uppercase
	strupr(Mac);
	Utils.str2hex(Mac, macByteArray);

	// by default, look for device during 30 seconds at TX power max.
	return scanDevice(macByteArray, DEFAULT_SCAN_TIME, TX_POWER_MAX);
}

/*
 Function: Makes an inquiry to discover specific device by its Mac.
 Returns: '0' if not found. '1' if found, error code otherwise.
 Parameters:
    Mac: Mac of device to discover
	maxTime: Maximum time searching device
	power: Allowed TX power levels
 Values:
*/
uint16_t WaspBLE::scanDevice(char* Mac, uint32_t maxTime, uint8_t TXPower)
{
	uint8_t macByteArray[6];

	//limit size of char * mac
	if (strlen(Mac) > 13)
	{
		Mac[12] = '\0';
	}

	// To uppercase
	strupr(Mac);
	Utils.str2hex(Mac, macByteArray);

	return scanDevice(macByteArray, maxTime, TXPower);
}


/*
 Function: Makes an inquiry to discover specific device by its Mac.
 Returns: '0' if not found. '1' if found, error code otherwise.
 Parameters:
	Mac: Mac of device to discover
	maxTime: Maximum time searching device
	power: Allowed TX power levels
 Values:
*/
uint16_t WaspBLE::scanDevice(uint8_t* Mac, uint32_t maxTime, uint8_t TXPower)
{
	uint8_t found = 0;
	numberOfDevices = 0;
	memset(previousMAC, 0x00, sizeof(previousMAC));

	// set tx power
	setTXPower(TXPower);

	// set MAC filter ON. Mandatory to use discoveredDevices variable.
	if (scan_duplicate_filtering != BLE_MAC_FILTER_ENABLED)
	{
		if (setFiltering(BLE_MAC_FILTER_ENABLED) == 0)
		{
			// Update global
			scan_duplicate_filtering = BLE_MAC_FILTER_ENABLED;
		}
		else
		{
			// if MAC filter is disabled, variable numberOfDevices has no sense.
			numberOfDevices = -1;
			return errorCode;
		}
	}

	// scan command, check if error starting scan
	sendCommand(1,6,2,&GAP_discover_mode);

	if (readCommandAnswer(6,1) != 0)
	{
		#if BLE_DEBUG > 0
		// copy from flash "Scan fail. err: %x\n"
		char message[25] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[6])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif

		// Now it is necessary to stop scan.
		if(endProcedure() != 0)
		{
			#if BLE_DEBUG > 0
			// copy "Stop fail. err: %x\n" form flash
			char message[25] ="";
			strcpy_P(message, (char*)pgm_read_word(&(table_BLE[5])));
			PRINT_BLE(F(""));
			USB.printf(message, errorCode);
			#endif
			return errorCode;
		}

		return errorCode;
	}

	// convert time to microseconds, limit if necessary
	unsigned long scanTime = maxTime * 1000;

	/* Limit scan time to 5 minutes to avoid overflows of millis.
	*  The user can modify tthis limit, but always must be smaller
	*  than millis maximum value.
	*/
	if (scanTime > 300000)
	{
		scanTime = 300000;
	}

	// if no error, then parse events during time.
	unsigned long previous = millis();
	while((found == 0) && (millis() - previous < scanTime))
	{
		if (waitEvent(1000) == BLE_EVENT_GAP_SCAN_RESPONSE)
		{
			parseScanEvent(0);

			if (memcmp(previousMAC, Mac,6) == 0 )
			{
				found = 1;
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// Now it is necessary to stop scan.
	if(endProcedure() != 0)
	{
		#if BLE_DEBUG > 0
		// copy "Stop fail. err: %x\n" form flash
		char message[25] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[5])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif
		return errorCode;
	}

	return found;
}


/*
 Function: Scans network to find other BLE modules.
 Returns: return 0 if scan OK, errorCode if error.
 Parameters:
	time: Time to be looking for this device
    TXPower: TX power used during the scan
 Values:
*/
// used for compatibility with old codes.
uint16_t WaspBLE::scanNetwork(uint8_t time, uint8_t TXPower)
{
	// set tx power
	setTXPower(TXPower);

	// by default, observation scanning
	return scanNetwork(time);
}


/*
 Function: Scans network to find other BLE modules.
 Returns: return 0 if scan OK, errorCode if error.
 Parameters:
	time: Time to be looking for this device
 Values:
*/
uint16_t WaspBLE::scanNetwork(uint8_t time)
{
	numberOfDevices = 0;
	memset(previousMAC, 0x00, sizeof(previousMAC));

	#ifdef ENABLE_EEPROM_SAVING
	// Set starting EEPROM address to save the scanned devices
	scanIndex = SCAN_EEPROM_START_ADDRESS;
	// write scan end on eeprom
	Utils.writeEEPROM(scanIndex,SCAN_END);
	Utils.writeEEPROM(scanIndex+1,SCAN_END);
	#endif

	// set MAC filter ON. Mandatory to use discoveredDevices variable.
	if (scan_duplicate_filtering != BLE_MAC_FILTER_ENABLED)
	{
		if (setFiltering(BLE_MAC_FILTER_ENABLED) == 0)
		{
			// Update global
			scan_duplicate_filtering = BLE_MAC_FILTER_ENABLED;
		}
		else
		{
			// if MAC filter is disabled, variable numberOfDevices has no sense.
			numberOfDevices = -1;
			return errorCode;
		}
	}

	//scan command, check if error starting scan
	sendCommand(1,6,2,&GAP_discover_mode);

	if (readCommandAnswer(6,1) != 0)
	{
		#if BLE_DEBUG > 0
		// copy from flash "Scan fail. err: %x\n"
		char message[25] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[6])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif
		return errorCode;
	}

	// convert time to microseconds, limit if necessary
	unsigned long scanTime = time * 1000;

	/* Limit scan time to 5 minutes to avoid overflows of millis.
	*  The user can modify tthis limit, but always must be smaller
	*  than millis maximum value.
	*/
	if (scanTime > 300000)
	{
		scanTime = 300000;
	}

	// if no error, then parse events during time.

	unsigned long previous = millis();
	while(millis() - previous < scanTime)
	{
		if (waitEvent(1000) == BLE_EVENT_GAP_SCAN_RESPONSE)
		{
			parseScanEvent(0);
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// Now it is necessary to stop scan. Return error code.
	return endProcedure();
}

/*
 Function: Scans network till find specified number of devices.
 Returns: return errorCode
 Parameters:
	MaxDevices: Number of devices to be found before stop scanning.
    power: TX power used during the scan
 Values:
*/
uint16_t WaspBLE::scanNetworkLimited(int16_t MaxDevices, uint8_t TXPower)
{
	setTXPower(TXPower);

	return scanNetworkLimited(MaxDevices);
}

/*
 Function: Scans network till find specified number of devices.
 Returns: return errorCode
 Parameters:
	MaxDevices: Number of devices to be found before stop scanning.
 Values:
*/
uint16_t WaspBLE::scanNetworkLimited(int16_t MaxDevices)
{
	numberOfDevices = 0;
	memset(previousMAC, 0x00, sizeof(previousMAC));

	#ifdef ENABLE_EEPROM_SAVING
	// Set starting EEPROM address to save the scanned devices
	scanIndex = SCAN_EEPROM_START_ADDRESS;
	// write scan end on eeprom
	Utils.writeEEPROM(scanIndex,SCAN_END);
	Utils.writeEEPROM(scanIndex+1,SCAN_END);
	#endif

	// Force MAC Filter ON to work with numberOfDevices.
	// set MAC filter ON. Mandatory to use discoveredDevices variable.
	if (scan_duplicate_filtering != BLE_MAC_FILTER_ENABLED)
	{
		if (setFiltering(BLE_MAC_FILTER_ENABLED) == 0)
		{
			// Update global
			scan_duplicate_filtering = BLE_MAC_FILTER_ENABLED;
		}
		else
		{
			// if MAC filter is disabled, variable numberOfDevices has no sense.
			numberOfDevices = -1;
			return errorCode;
		}
	}

	//scan command, check if error starting scan
	sendCommand(1,6,2,&GAP_discover_mode);

	if (readCommandAnswer(6,1) != 0)
	{
		#if BLE_DEBUG > 0
		// copy from flash "Scan fail. err: %x\n"
		char message[25] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[6])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif
		return errorCode;
	}

	// DEFAULT TIME FOR DEVICE LIMITED SCANS IS 30 seconds
	// convert time to microseconds, limit if necessary
	unsigned long scanTime = DEFAULT_SCAN_TIME * 1000;

	// if no error, then parse events during time.

	unsigned long previous = millis();
	while((numberOfDevices < MaxDevices) && (millis() - previous < scanTime))
	{
		if (waitEvent(1000) == BLE_EVENT_GAP_SCAN_RESPONSE)
		{
			parseScanEvent(0);
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// Now it is necessary to stop scan. Return error code.
	return endProcedure();
}

/*
 Function: Cancels a scan procedure.
 Returns: return 0 if OK, err code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::scanNetworkCancel()
{
	return endProcedure();
}

/*
 Function: Scans network to find other BLE modules, including friendly name. Uses active scanning.
 Returns: return error code in any case.
 Parameters:
	time: Time to be looking for devices
    TXPower: TX power used during the scan
 Values:
*/
uint8_t WaspBLE::scanNetworkName(uint8_t time, uint8_t TXPower)
{
	setTXPower(TXPower);

	return scanNetworkName(time);
}

/*
 Function: Scans network to find other BLE modules, including friendly name. Uses active scanning.
 Returns: return error code in any case.
 Parameters:
	time: Time to be looking for devices
 Values:
*/
uint8_t WaspBLE::scanNetworkName(uint8_t time)
{
	// configure active scanning, mandatory for looking for friendly name.
	setScanningParameters(BLE_ACTIVE_SCANNING);
	if (errorCode != 0) return errorCode;

	// make a normal scan, but parsing names also.
	numberOfDevices = 0;
	memset(previousMAC, 0x00, sizeof(previousMAC));

	#ifdef ENABLE_EEPROM_SAVING
	// Set starting EEPROM address to save the scanned devices
	scanIndex = SCAN_EEPROM_START_ADDRESS;
	// write scan end on eeprom
	Utils.writeEEPROM(scanIndex,SCAN_END);
	Utils.writeEEPROM(scanIndex+1,SCAN_END);
	#endif

	// set MAC filter ON. Mandatory to use discoveredDevices variable.
	if (scan_duplicate_filtering != BLE_MAC_FILTER_ENABLED)
	{
		if (setFiltering(BLE_MAC_FILTER_ENABLED) == 0)
		{
			// Update global
			scan_duplicate_filtering = BLE_MAC_FILTER_ENABLED;
		}
		else
		{
			// if MAC filter is disabled, variable numberOfDevices has no sense.
			numberOfDevices = -1;
			return errorCode;
		}
	}

	//scan command, check if error starting scan
	sendCommand(1,6,2,&GAP_discover_mode);

	if (readCommandAnswer(6,1) != 0)
	{
		#if BLE_DEBUG > 0
		// copy from flash "Scan fail. err: %x\n"
		char message[25] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[6])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif
		return errorCode;
	}

	// convert time to microseconds, limit if necessary
	unsigned long scanTime = time * 1000;

	/* Limit scan time to 5 minutes to avoid overflows of millis.
	*  The user can modify tthis limit, but always must be smaller
	*  than millis maximum value.
	*/
	if (scanTime > 300000)
	{
		scanTime = 300000;
	}

	// if no error, then parse events during time.

	unsigned long previous = millis();
	while(millis() - previous < scanTime)
	{

		if (waitEvent(1000) == BLE_EVENT_GAP_SCAN_RESPONSE)
		{
			// parse only packet type = 4 to pair each name with each device. needs active scanning.
			// Fix if device loosing is detected.
			if (event[5] == 4)
			{
				parseScanEvent(1);
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// Now it is necessary to stop scan. Return error code.
	return endProcedure();
}


/*
 * GAP discoverable mode:
 * 0 = gap_non_discoverable
 * 1 = gap_limited_discoverable
 * 2 = gap_general_discoverable
 * 3 = gap_broadcast
 * 4 = gap_user_data
 * 5 = gap_enhanced_broadcasting
 *
 * GAP connectable mode
 * 0 = gap_non_connectable
 * 1 = gap_directed_connectable
 * 2 = gap_undirected_connectable
 * 3 = gap_scannable_connectable
*/

/*
 Function: This function configures the discover mode.
 * default observation mode.
 Returns: return 0 if ok, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::setDiscoverMode(uint8_t discover)
{
	// Check if valid value
	if (discover > 2)
	{
		// return error code 0x0180 manually, for coherence.
		return  384;
	}

	// Just update global
	GAP_discover_mode = discover;

	return 0;
}

/*
 Function: This functions configures the discoverability mode.
 * default general discoverable mode.
 Returns: return 0 if ok, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::setDiscoverableMode(uint8_t discoverable)
{
	uint8_t payload[2];

	payload[0] = discoverable;
	payload[1] = GAP_connectable_mode;

	// set mode command
	sendCommand(2,6,1,payload);

	readCommandAnswer(6,1);

	if (errorCode == 0)
	{
		// Update global
		GAP_discoverable_mode = discoverable;
	}

	return errorCode;
}


/*
 Function: This functions configures the discoverability and connectability mode.
 * default non connectable mode.
 Returns: return 0 if ok, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::setConnectableMode(uint8_t connectable)
{
	uint8_t payload[2];

	payload[0] = GAP_discoverable_mode;
	payload[1] = connectable;

	// set mode command
	sendCommand(2,6,1,payload);

	readCommandAnswer(6,1);

	if (errorCode == 0)
	{
		// Update global
		GAP_connectable_mode = connectable;
	}

	return errorCode;
}


/*
 Function: This function ends the current procedure, like a scan.
 Returns: return error code in any case
 Parameters:
 Values:
*/
uint16_t WaspBLE::endProcedure()
{
	sendCommand(0,6,4,0);
	return readCommandAnswer(6,1);
}


/*
 Function: This function sets advertisement parameters
 Returns: return error code.
 Parameters:
 * default values: adv_interval_min = 0x200; adv_interval_max = 0x200 (Example: 0x200 = 512; 512 * 625 us = 320 ms)
 * units of 625 us.
 * adv_channels: 0x07 = three channels (37,38,39); 0x03 = channels 37 and 38; 0x04 = channel 39.
 * example default = setAdvParameters(320,320,7);
 *
 * note: any changes set using this command will not take effect until stop and re-start advertising again.
 Values:
*/
uint16_t WaspBLE::setAdvParameters(uint16_t adv_min, uint16_t adv_max, uint8_t adv_ch)
{
	uint8_t payload[5];

	//limit ranges. minimum = 0x20, max = 0x4000
	if(adv_min < 0x20)
	{
		adv_min = 0x20;
	}
	else if (adv_min > 0x4000)
	{
		adv_min = 0x4000;
	}
	if(adv_max < 0x20)
	{
		adv_max = 0x20;
	}
	else if (adv_max > 0x4000)
	{
		adv_max = 0x4000;
	}

	// little endian.
	payload[0] = (uint8_t)(adv_min & 0x00FF);
	payload[1] = (uint8_t)((adv_min & 0xFF00) >> 8);
	payload[2] = (uint8_t)(adv_max & 0x00FF);
	payload[3] = (uint8_t)((adv_max & 0xFF00) >> 8);
	payload[4] = adv_ch;

	sendCommand(5, 6, 8, payload);

	readCommandAnswer(6,1);

	if (errorCode == 0)
	{
		// update globals
		adv_interval_max = adv_max;
		adv_interval_min = adv_min;
		adv_channels = adv_ch;
	}

	return errorCode;
}



/*
 Function: Set Advertisement scan Response data. If data greater than 31 bytes, it will be truncated
 Returns: 0 if ok, error code otherwise.
 Parameters:
	set_scanrsp: advertisement data type; 0 sets advertisement data. 1 sets scan response data.
    adv_data: data to send

    custom data is only used in discoverable mode
	data must be formatted according to the Core specification.

 	Advertisement data type
	0 : sets advertisement data
	1 : sets scan response data
 Values:
*/
uint16_t WaspBLE::setAdvData(uint8_t set_scanrsp, char* adv_data)
{
	uint8_t advDataArray[32];

	//limit size of char * mac
	if (strlen(adv_data) > 31)
	{
		adv_data[31] = '\0';
	}

	memcpy(advDataArray, adv_data, strlen(adv_data));


	return setAdvData(set_scanrsp, advDataArray, strlen(adv_data));

}

/*
 Function: Set Advertisement scan Response data. If data greater than 31 bytes, it will be truncated
 Returns: 0 if ok, error code otherwise.
 Parameters:
	set_scanrsp: advertisement data type; 0 sets advertisement data. 1 sets scan response data.
    adv_data: data to send
    adv_data_length: length of adv data.

    custom data is only used in discoverable mode
	data must be formatted according to the Core specification.

 	Advertisement data type
	0 : sets advertisement data
	1 : sets scan response data
 Values:
*/
uint16_t WaspBLE::setAdvData(uint8_t set_scanrsp, uint8_t* adv_data, uint8_t adv_data_length)
{
	// if greater than, data will be truncated.
	if (adv_data_length > 31)
	{
		adv_data_length = 31;
	}

	uint8_t payload[33];
	payload[0] = set_scanrsp;
	payload[1] = adv_data_length;

	for(uint8_t a = 0; a < adv_data_length; a++)
	{
		payload[a+2] = adv_data[a];
	}

	sendCommand(adv_data_length+2, 6, 9, payload);

	return readCommandAnswer(6, 1);
}

/*
 Function: This function sets scanning parameters. Introduce parameters in decimal values.
 Returns: return 0 if ok, error code otherwise.
 Parameters:
	scan_interval:  default 75 (46.875ms)
	scan_window: default 50 (31.250 ms)
	scanning: 1 = use active scanning; 0 = use passive scanning.
 Values:
*/
uint16_t WaspBLE::setScanningParameters(uint16_t scan_interv, uint16_t scan_win, uint8_t scanning)
{
	uint8_t payload [5];

	//limit ranges. minimum = 0x04, max = 0x4000
	if(scan_interv < 0x04)
	{
		scan_interv = 0x04;
	}
	else if (scan_interv > 0x4000)
	{
		scan_interv = 0x4000;
	}
	if(scan_win < 0x04)
	{
		scan_win = 0x04;
	}
	else if (scan_win > 0x4000)
	{
		scan_win = 0x4000;
	}

	// code into little endian.
	payload[0] = (uint8_t)(scan_interv & 0x00FF);
	payload[1] = (uint8_t)((scan_interv & 0xFF00) >> 8);
	payload[2] = (uint8_t)(scan_win & 0x00FF);
	payload[3] = (uint8_t)((scan_win & 0xFF00) >> 8);
	payload[4] = scanning;

	sendCommand(5,6,7,payload);

	readCommandAnswer(6, 1);

	if (errorCode == 0)
	{
		// store state in class variables
		active = scanning;
		scan_interval = scan_interv;
		scan_window = scan_win;
	}

	return errorCode;
}

/*
 Function: This function sets scanning parameters
 Returns: return 0 if ok, error code otherwise.
 Parameters:
	active: 1 = use active scanning; 0 = use passive scanning.
 Values:
*/
uint16_t WaspBLE::setScanningParameters(uint8_t active)
{
	return setScanningParameters(scan_interval, scan_window, active);
}


/*
 Function: Return current scanning parameters
 Returns: returns current scanning parameters: GAP Mode, scan_interval,
	scan_window, active/passive, scan_duplicate_filtering, TX_POWER
 Parameters:
 Values:
*/
void  WaspBLE::getScanningParameters()
{
	char message[120] ="";
	// Copy form flash "Scan params: GAP mode ....."
	strcpy_P(message, (char*)pgm_read_word(&(table_BLE[7])));
	USB.printf(message, GAP_discover_mode, scan_interval, scan_window, scan_duplicate_filtering, TXPower);
}


/*
 Function: Set scan, connection, and advertising filtering parameters, based on the whitelist
 Returns: return 0 if OK, error code otherwise.
 Parameters:
 * Scan Policy: 0 = gap_scan_policy_all; 1 = gap_scan_policy_whitelist
 * Advertising policy: 0 = gap_adv_policy_all ; 1 = gap_adv_policy_whitelist_scan ; 2 = gap_adv_policy_whitelist_connect; 3 = gap_adv_policy_whitelist_all;
 * Duplicate filtering: 0 = do not filter; 1 = filter duplicates.
 Values:
*/
uint16_t WaspBLE::setFiltering(uint8_t scan_pol, uint8_t adv_pol, uint8_t scan_duplicate_filter)
{
	uint8_t payload[3];

	payload[0] = scan_pol;
	payload[1] = adv_pol;
	payload[2] = scan_duplicate_filter;

	sendCommand(3,6,6,payload);
	readCommandAnswer(6, 1);

	if (errorCode == 0)
	{
		// Update globals
		scan_policy = scan_pol;
		adv_policy = adv_pol;
		scan_duplicate_filtering = scan_duplicate_filter;
	}

	return errorCode;
}

/*
 Function: Set advertising filtering parameters, based on the whitelist.
 * same but only with MAC filter.
 Returns: return 0 if OK, error code otherwise.
 Parameters:
	scan Duplicate filtering: 0 = do not filter; 1 = filter duplicates.
 Values:
*/
uint16_t WaspBLE::setFiltering(uint8_t scan_duplicate_filtering)
{
	// by default scan_policy = 0; and adv_policy = 0.
	return setFiltering(scan_policy, adv_policy, scan_duplicate_filtering);
}

/*
 Function: Reads the internal Temperature sensor of the BLE112. Not calibrated. +-10ªC accuracy.
 Returns: return temperature if ok, 0 if error reading.
 Parameters:
 Values:
*/
// return temperature if ok, 0 if error reading.
float WaspBLE::getTemp()
{
	float temperature = 0;

	float ADCValuemV = 0;

	// if no error sending command
	if (ADCRead(0x0e,3,0) != 0)
	{
		// temperature conversion for 12 bit decimation.
		// 12 bits left aligned. last nibble not relevant. shift 4 bits to the right.
		ADCValue = ADCValue / 16;

		// approximated temperature conversion
		// 25ºC = 890 mV
		// 0ªC  = 750 mV
		// ADC value to mV
		ADCValuemV = (1.240 * ADCValue) / 2047;

		// mV to ºC
		// Approximated Temp coef used: 2.7259 mV/1°C
		// Offset used 800mV
		temperature = (ADCValuemV - 0.800) / 2.7259;
		temperature = temperature * 1000;
		#if BLE_DEBUG > 0
		char a[20] ="";
		char message[40] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[11])));
		PRINT_BLE(F(""));
		USB.printf(message,ADCValue);
		memset(message, 0x00, sizeof(message));

		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[12])));
		PRINT_BLE(F(""));
		USB.printf(message,ADCValue);
		memset(message, 0x00, sizeof(message));

		Utils.float2String(ADCValuemV,a,4);
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[13])));
		PRINT_BLE(F(""));
		USB.printf(message,a);
		memset(message, 0x00, sizeof(message));

		Utils.float2String(temperature,a,4);
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[14])));
		PRINT_BLE(F(""));
		USB.printf(message,a);
		#endif

		return temperature;
	}
	else
	{
		return 0;
	}
}


/*
 Function: Reads the internal ADC of the BLE112. Waits for ADC event before exit.
 Returns: ADC value (bigEndian) if OK. 0 error or ADC event not found.
 Parameters:
 Values:
*/
int16_t WaspBLE::ADCRead(uint8_t input, uint8_t decimation, uint8_t reference_selection)
{
	uint8_t payload[3];
	ADCValue = 0;

	payload[0] = input;
	payload[1] = decimation;
	payload[2] = reference_selection;

	sendCommand(3,7,2,payload);

	readCommandAnswer(6, 1);

	//check if no error
	if(errorCode == 0)
	{
		// wait&read ADC event during 1 second
		if (waitEvent(1000) == BLE_EVENT_HARDWARE_ADC_RESULT)
		{
			// value stored in event[5:6] in little endian.
			// first bit is sign

			// to uint16_t and big endian.
			ADCValue = ((uint16_t)event[6] << 8) | event[5];

			#if BLE_DEBUG > 0
			char message[40] ="";
			strcpy(message, (char*)pgm_read_word(&(table_BLE[12])));
			PRINT_BLE(F(""));
			USB.printf(message,ADCValue);
			#endif

			return ADCValue;
		}
		else
		{
			// if here, no ADC event found.
			return 0;
		}
	}

	// if here, error ocurred
	return 0;

}

/*
 Function: Returns the BLE module MAC address
 Returns: Returns the BLE module MAC address
 Parameters:
 Values:
*/
char * WaspBLE::getOwnMac()
{
	uint8_t dummy[6];

	// this command does not return error code.
	sendCommand(0,0,2,0);

	readCommandAnswer(10,0);

	uint8_t b = 6;
	for(uint8_t a = 0; a < 6 ; a++)
	{
		dummy[a] = answer[b+3];
		b--;
	}

	Utils.hex2str(dummy,my_bd_addr,6);

	return my_bd_addr;
}

/*
 Function: print last scan saved on EEPROM by USB.
 Returns: return number of devices printed.
 Parameters:
 Values:
*/
uint8_t WaspBLE::printInquiry()
{
	int BLEAddr = SCAN_EEPROM_START_ADDRESS;
	uint8_t deviceCounter = 0;

	// show scan parameters of last scan
	getScanningParameters();

	// Now print devices till find end of SCAN
	while (BLEAddr <= SCAN_EEPROM_LIMIT_ADDRESS)
	{
		// update end variable to see if end of scan reached,
		// looking for SCAN_END in EEPROM. do not increment address.
		BLEDev.mac[0] = Utils.readEEPROM(BLEAddr);
		BLEDev.mac[1] = Utils.readEEPROM(BLEAddr+1);

		if ((BLEDev.mac[0] == SCAN_END) && (BLEDev.mac[1] == SCAN_END))
		{
			break;
		}

		// read device from EEPROM MAC, RSSI and friendly name
		for (uint8_t i = 0; i < 6; i++)
		{
			BLEDev.mac[i] = Utils.readEEPROM(BLEAddr++);
		}
		BLEDev.rssi = Utils.readEEPROM(BLEAddr++);

		for (uint8_t i = 0; i < 31; i++)
		{
			BLEDev.friendlyName[i] = Utils.readEEPROM(BLEAddr++);
		}

		// Copy form flash " "Device %u; %02x%02x%02x%0...
		char message[80] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[8])));
		USB.printf(message, deviceCounter,
		BLEDev.mac[0],
		BLEDev.mac[1],
		BLEDev.mac[2],
		BLEDev.mac[3],
		BLEDev.mac[4],
		BLEDev.mac[5],
		BLEDev.rssi);

		for(uint8_t a = 0; a < 31 ; a++)
		{
			USB.print(BLEDev.friendlyName[a]);
		}
		USB.println();

		deviceCounter++;
	}

	return deviceCounter;
}

/*
 Function: similar to AT -> OK
 Returns:  return 1 if ok, 0 if no response
 Parameters:
 Values:
*/
uint8_t WaspBLE::sayHello()
{
	sendCommand(0,0,1,0);

	readCommandAnswer(4, 0);

	uint8_t dummy[4] = {0x00,0x00,0x00,0x01};
	if (memcmp(answer,dummy,4) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 Function: Define the remote devices allowed to establish a connection.
 * if the white list is empty they will not be active. Do not use this
 * command while advertising, scanning, or while being connected.
 * The current list is discarded upon reset or power-cycle.
 Returns: return error code
 Parameters:
	BLEAdrress: MAC of the remote module
 Values:
*/
uint16_t WaspBLE::whiteListAppend(char * BLEAddress)
{
	uint8_t macByteArray[6];

	//limit size of char * BLEAddress
	if (strlen(BLEAddress) > 13)
	{
		BLEAddress[12] = '\0';
	}

	strupr(BLEAddress);
	Utils.str2hex(BLEAddress, macByteArray);

	uint8_t payload[7];

	uint8_t b = 5;
	for (uint8_t i = 0 ; i < 6 ; i++)
	{
		payload[i] = macByteArray[b];
		b--;
	}

	payload[6] = BLE_GAP_ADDRESS_TYPE_PUBLIC;

	sendCommand(7,0,10,payload);

	return readCommandAnswer(6, 1);
}

/*
 Function: Delete all entries of the white list at once. Do not use
 * this command while advertising or while being connected.
 Returns: 1 if ok, o if error
 Parameters:
 Values:
*/
//
uint8_t WaspBLE::whiteListClear()
{
	sendCommand(0,0,12,0);

	readCommandAnswer(4, 0);

	uint8_t dummy[4] = {0x00,0x00,0x00,0x0C};
	if (memcmp(answer,dummy,4) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 Function: Remove an entry from the running white list. Do not use
 * this command while advertising or while being connected.
 Returns:
 Parameters:
	BLEAdrress: MAC of the remote module
  Values:
*/
uint16_t WaspBLE::whiteListRemove(char * BLEAddress)
{
	uint8_t macByteArray[6];

	//limit size of char * BLEAddress
	if (strlen(BLEAddress) > 13)
	{
		BLEAddress[12] = '\0';
	}

	strupr(BLEAddress);
	Utils.str2hex(BLEAddress, macByteArray);

	uint8_t payload[7];

	uint8_t b = 5;
	for (uint8_t i = 0 ; i < 6 ; i++)
	{
		payload[i] = macByteArray[b];
		b--;
	}

	payload[6] = BLE_GAP_ADDRESS_TYPE_PUBLIC;

	sendCommand(7,0,11,payload);

	return readCommandAnswer(6, 1);
}

/*
 Function: This function will start direct connection establishment procedure to a dedicated BLE device.
 Returns: return 0 if invalid parameters, 1 if connection is successful, error code otherwise.
 Parameters:
 * BLEAddress: address to connect
 Values:
*/
uint16_t WaspBLE::connectDirect(char * BLEAddress)
{
	// connect with the default values
	return connectDirect(BLEAddress, 60, 76, 100, 0);
}

/*
 Function: This function will start direct connection establishment procedure to a dedicated BLE device.
 Returns: return 0 if invalid parameters, 1 if connection is successful, error code if error sending conenctDirect command, event identification number otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::connectDirect(char * BLEAddress, uint16_t conn_interval_min, uint16_t conn_interval_max, uint16_t timeout, uint16_t latency)
{
	uint8_t macByteArray[6];
	Utils.str2hex(BLEAddress, macByteArray);

	// check values before sending them
	// conn_interval_max must be equal or bigger than conn_interval_min
	if (conn_interval_max < conn_interval_min)	conn_interval_max = conn_interval_min;

	// timeout must be between 10 and 3200 (100ms and 32 s in units of 10 ms)
	if (timeout < 10) timeout = 10;
	if (timeout > 3200) timeout = 3200;

	// latency must be lower than 500.
	if (latency > 500) latency = 500;

	uint8_t payload[15];
	// MAC must be inversed. little endian
	payload[0] = macByteArray[5];
	payload[1] = macByteArray[4];
	payload[2] = macByteArray[3];
	payload[3] = macByteArray[2];
	payload[4] = macByteArray[1];
	payload[5] = macByteArray[0];
	payload[6] = BLE_GAP_ADDRESS_TYPE_PUBLIC;
	payload[7] = (uint8_t)(conn_interval_min & 0x00FF);
	payload[8] = (uint8_t)((conn_interval_min & 0xFF00) >> 8);
	payload[9] = (uint8_t)(conn_interval_max & 0x00FF);
	payload[10] = (uint8_t)((conn_interval_max & 0xFF00) >> 8);
	payload[11] = (uint8_t)(timeout & 0x00FF);
	payload[12] = (uint8_t)((timeout & 0xFF00) >> 8);
	payload[13] = (uint8_t)(latency & 0x00FF);
	payload[14] = (uint8_t)((latency & 0xFF00) >> 8);

	sendCommand(15,6,3,payload);

	// this command does not return error code. See if result is 0 (OK), like errorcode
	readCommandAnswer(7, 0);

	errorCode = ((uint16_t)answer[5] << 8) | answer[4];
	if (errorCode == 0)
	{
		//connected OK, save connection handle in global variable
		connection_handle = answer[6];
		//return 1;
	}
	else
	{
		// an error has occurred.
		return errorCode;
	}

	uint8_t flag = waitEvent(1000);

	// Wait a bit to allow next commands.
	delay(100);

	// if connection event found and flag ok, then connection success.
	// bit 0 = 1 means connection active.
	// bit 1 = 1 means connection encrypted.
	// bit 2 = 1 means connection created.
	// bit 3 = 1 means parameters have changed.
	if (( flag == BLE_EVENT_CONNECTION_STATUS) && (event[5] == 0x05))
	{
		//connection success
		return 1;
	}
	else
	{
		// flag has returning value of wait event. return 1 if found, 0 no event found. otherwise other event found
		return flag;
	}

}

/*
 Function: his function disconnects an active connection
 Returns: return 1 if connection handle is not right. error code if error sending command. event identifier if disconnection event not found. 0 if ok.
 Parameters:
 * param connection: connection handle.
 Values:
*/
uint16_t WaspBLE::disconnect(uint8_t connection)
{
	uint8_t flag = 0;

	sendCommand(1,3,0,&connection);

	readCommandAnswer(7, 1);

	// check if right connection handle
	if (connection_handle != answer[4]) return 1;

	// check if result is 0. means that disconnection is started successfully
	errorCode = ((uint16_t)answer[6] << 8) | answer[5];

	if (errorCode == 0)
	{
		flag = waitEvent(10000);
		if (flag == BLE_EVENT_CONNECTION_DISCONNECTED)
		{
			uint16_t reason =  ((uint16_t)event[6] << 8) | event[5];

			// reason 0 menas disconnected by local user.
			return reason;
		}
		else
		{
			// inquiry for the status to ensure disconnection.


			return flag;
		}
	}

	#if BLE_DEBUG > 1
	PRINT_BLE(F("error.\n"));
	#endif

	return errorCode;
}

/*
 Function: get RSSI of the given link.
 Returns: return 0 if error, rssi otherwise.
 Parameters:
 Values:
*/
int8_t WaspBLE::getRSSI(uint8_t connection)
{
	sendCommand(1,3,1,&connection);

	// this command does not return error code. Only in case there is no answer,
	// errorCode is set manually to FFFF
	readCommandAnswer(6, 0);

	if ((answer[4] == connection) && (errorCode != 0xFFFF))
	{
		return answer[5];
	}
	else return 0;
}



/*
 Function: Disables wake up pin of the BLE module (disables UART interface)
 * allowing module low power modes.
 Returns: void
 Parameters:
 Values:
*/
void WaspBLE::sleep()
{
	if( _uartBT == SOCKET0 )
	{
		// set sleep pin low in SOCKET0, to disable AURT interface
		pinMode(BLE_SLEEP, OUTPUT);
    	digitalWrite(BLE_SLEEP,LOW);
    }
    else if( _uartBT == SOCKET1 )
    {
		// set sleep pin low in SOCKET1, to disable UART interface
		pinMode(DIGITAL7, OUTPUT);
    	digitalWrite(DIGITAL7,LOW);
    }
}

/*
 Function: Enables Wakeup pin (enables AURT interface) and wake up BLE from low power modes
 Returns:return 1 if wake up OK (event found), 0 if no event found, event identification number otherwise.
 Parameters:
 Values:
*/
uint8_t WaspBLE::wakeUp()
{
	if( _uartBT == SOCKET0 )
	{
		Utils.setMuxSocket0();
		beginSerial(_baudrateBT,_uartBT);
		serialFlush(_uartBT);

		// set sleep pin high in SOCKET0, to enable UART interface
		pinMode(BLE_SLEEP, OUTPUT);
    	digitalWrite(BLE_SLEEP,HIGH);
    }
    else if( _uartBT == SOCKET1 )
    {
		Utils.setMuxSocket1();
		beginSerial(_baudrateBT,_uartBT);
		serialFlush(_uartBT);

		// set sleep pin high in SOCKET1, to enable UART interface
		pinMode(DIGITAL7, OUTPUT);
    	digitalWrite(DIGITAL7,HIGH);
    }

   	// update Waspmote Register
	if(_uartBT == SOCKET0)	WaspRegister |= REG_SOCKET0;
	if(_uartBT == SOCKET1)	WaspRegister |= REG_SOCKET1;

    uint8_t flag = waitEvent(1000);

    // look for I/O port status event to show interrupt on wake up pin
    if (flag == BLE_EVENT_HARDWARE_IO_PORT_STATUS)
    {
		return 1;
	}
	else
	{
		if (flag == 0)
		{
			return 0;
		}
		else
		{
			return flag;
		}
	}
}

/*
 Function: wait for specified time for an event.
 Returns:return 0 if no event found,  event identification number otherwise.
 Parameters: time: time in seconds to wait for an event.
 Values:
*/
uint8_t WaspBLE::waitEvent(unsigned long time)
{
	uint8_t i = 0;
	memset(event, 0x00, sizeof(event) );

	// while pending data or data available on RX buffer.
	// Added a timeout to avoid stopping the code.
	unsigned long previous = millis();
	//while( ((i < totalLength) || (serialAvailable(_uartBT))) && ((millis() - previous) < time) && (flag == 0) )
	while( (millis() - previous) < time)
	{
		i=0;
		if(serialAvailable(_uartBT) > 3)
		{
			event[0] = serialRead(_uartBT);

			//check if event start byte 0x80
			if (event[0] == 0x80)
			{

				//check if expected class and method
				event[1] = serialRead(_uartBT); // payload Length
				event[2] = serialRead(_uartBT); // Class
				event[3] = serialRead(_uartBT); // Method


				//Keep reading till end of event.
				//wait till all bytes arrives to buffer
				unsigned long previous2 = millis();
				while ((serialAvailable(_uartBT) < event[1]) && ((millis() - previous2) < time) )
				{

					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous2 ) previous2=millis();
				}

				for (i = 4; i < event[1]+4; i++)
				{
					event[i] = serialRead(_uartBT);

					// exit if maximum size is reached
					if( i >= sizeof(event) )	break;
				}

				#if BLE_DEBUG > 1
					PRINT_BLE(F("ev:"));
					for (uint8_t a = 0; a < event[1]+4; a++)
					{
						USB.printHex(event[a]);

						// added for security.
						if (a > MAX_PACKET_SIZE) break;

					}
					USB.println();
				#endif
				// if here, event found, exit loop
				break;
			}
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();
	}

	// Identify wich event has arrived
	return parseEvent();

}






/*
 Function: Encrypts current connection
 Returns: Errorcode
 Parameters: handle: connection handle
 Values:
*/
uint16_t WaspBLE::encryptConnection(uint8_t handle)
{
	// enable bonding by default
	return encryptConnection(handle,BLE_ENABLE_BONDING);
}

/*
 Function: Start encryption form the given connection
 Returns: ErrorCode
 Parameters:
 Values:
*/
// return 0 if ok, errorCode otherwise
uint16_t WaspBLE::encryptConnection(uint8_t handle, uint8_t bondable)
{
	uint8_t flag = 0;
	uint8_t payload[2];

	payload[0] = handle;
	payload[1] = bondable;

	sendCommand(2,5,0,payload);

	readCommandAnswer(7, 1);

	// if error starting encryption, return error code.
	if (errorCode != 0)
	{
		// Error code will never be '1'.
		return errorCode;
	}

	flag = waitEvent(10000);

	// Now wait for connection status event
	// flag = 3 means connection active and encrypted
	if ((flag == BLE_EVENT_CONNECTION_STATUS) && (event[5] == 3))
	{
		return 1;
	}
	else
	{
		// note: flag is only '1' if a boot event is received.
		// This is not going to happen.
		return flag;
	}
}

/*
 Function: Enables bonding on the device
 Returns: returns 1 if OK, 0 otherwise
 Parameters: bondable: 0 if not bondable, 1 if bondable.
 Values:
*/
uint16_t WaspBLE::setBondableMode(uint8_t bondable)
{
	sendCommand(1,5,1,&bondable);

	readCommandAnswer(4, 0);

	uint8_t dummy[4] = {0x00,0x00,0x05,0x01};
	if (memcmp(answer,dummy,4) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 Function: Set encryption key. Range 000000-999999
 Returns: return 1 if invalid key, errorCode otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::setKey(uint8_t handle, uint32_t passkey)
{
	uint8_t payload[5];

	if (passkey > 999999)
	{
		return 1;
	}

	payload[0] = handle;

	// uint32_t to uint8
	payload[1] = (passkey & 0x000000ff);
	payload[2] = (passkey & 0x0000ff00) >> 8;
	payload[3] = (passkey & 0x00ff0000) >> 16;
	payload[4] = (passkey & 0xff000000) >> 24;

	#if BLE_DEBUG > 1
		PRINT_BLE(F("key:"));
		for (uint8_t a = 1; a < 4; a++)
		{
			USB.printHex(payload[a]);
		}
		USB.println();
	#endif

	sendCommand(5,5,4,payload);

	readCommandAnswer(6, 1);

	return errorCode;

}

/*
 Function: deletes all devices bonded
 Returns: ErrorCode.
 Parameters:
 Values:
*/
uint16_t WaspBLE::deleteBonding()
{
	// delete all bonds with handle 0xFF
	uint8_t all = 0xFF;

	sendCommand(1,5,2, &all);

	readCommandAnswer(6, 1);

	return errorCode;

}

/*
 Function: return number of bonded devices. maximum of 8
 Returns:
 Parameters:
 Values:
*/
uint16_t WaspBLE::getBonding()
{
	sendCommand(0,5,5,0);

	readCommandAnswer(5, 0);

	// return number of bonds
	return answer[4];
}

/*
 Function: Configures security manager
 Returns: return 0 if OK, 1 otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::setSecurityParameters(uint8_t mitm, uint8_t min_key_size, uint8_t io_cap)
{
	uint8_t payload[3];

	//limit key size inside range
	if (min_key_size < 7)
	{
		min_key_size = 7;
	}
	if (min_key_size > 16)
	{
		min_key_size = 16;
	}

	payload[0] = mitm;
	payload[1] = min_key_size;
	payload[2] = io_cap;

	sendCommand(3,5,3,payload);

	// does not return error code.
	readCommandAnswer(4, 0);

	uint8_t dummy[4] = {0x00,0x00,0x05,0x03};
	if (memcmp(answer,dummy,4) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
 Function:  read an attribute from the local database of the BLE device.
 Returns: return error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::readLocalAttribute(uint16_t handle)
{
	// By default, ofset is 0.
	return readLocalAttribute(handle, 0);
}

/*
 Function:  read an attribute from the local database of the BLE device.
 Returns: return error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::readLocalAttribute(uint16_t handle, uint16_t offset)
{
	uint8_t aux = 0;
	uint8_t payload[4];
	payload[0] = (uint8_t)(handle & 0x00FF);
	payload[1] = (uint8_t)((handle & 0xFF00) >> 8);
	payload[2] = (uint8_t)(offset & 0x00FF);
	payload[3] = (uint8_t)((offset & 0xFF00) >> 8);

	sendCommand(4,2,1,payload);

	// does not return error code.
	readCommandAnswer(33, 0);

	// parse error code
	errorCode = ((uint16_t)answer[9] << 8) | answer[8];

	if (errorCode == 0)
	{
		// read succesful. parse data, 32 bytes max

		// first byte is data length
		// save first byte as length of the value.
		// Value is stored from possition
		aux = answer[10];

		if (aux > 32)
		{
			aux = 32;
		}
		attributeValue[0] = aux;

		for (uint8_t i = 1; i < aux+1; i++)
		{
			attributeValue[i] = answer[i+10];
		}
	}

	#if BLE_DEBUG>1
	PRINT_BLE(F("read local att: "));
	for(uint8_t i = 0; i < aux; i++)
	{
		USB.printHex(attributeValue[i]);
	}
	USB.println();
	#endif

	return errorCode;
}


/*
 Function: write local attribute to the local GATT database of the BLE device
 Returns: return error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::writeLocalAttribute(uint16_t handle, char * data)
{
	memset(attributeValue, 0x00, sizeof(attributeValue));

	// attribute data is variable. save the length.
	uint8_t datalength = strlen(data);

	//limit size to  max write size: 54 bytes
	if (datalength > 54)
	{
		datalength = 54;
	}

	memcpy(attributeValue, data, datalength);

	// default indicate disabled
	return writeLocalAttribute(handle, BLE_INDICATE_DISABLED, attributeValue, datalength);
}

/*
 Function: write local attribute to the local GATT database of the BLE device
 Returns: return error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::writeLocalAttribute(uint16_t handle, uint8_t indicate, char * data)
{
	memset(attributeValue, 0x00, sizeof(attributeValue));

	// attribute data is variable. save the length.
	uint8_t datalength = strlen(data);

	//limit size to  max write size: 54 bytes
	if (datalength > 54)
	{
		datalength = 54;
	}

	memcpy(attributeValue, data, datalength);

	return writeLocalAttribute(handle, indicate, attributeValue, datalength);
}

/*
 Function: write local attribute to the local GATT database of the BLE device
 Returns: return error code. 0 if OK, error code otherwise.
 Parameters:
 Values:
*/
uint16_t WaspBLE::writeLocalAttribute(uint16_t handle, uint8_t * data, uint8_t length)
{
	// default indicate disabled
	return writeLocalAttribute(handle, BLE_INDICATE_DISABLED, data, length);
}

/*
 Function:write local attribute to the local GATT database of the BLE device
 Returns: return 0 if OK, 1 if write ok and indicated ok, error code if error writting, event identification number if other event found
 Parameters:
 Values:
*/
uint16_t WaspBLE::writeLocalAttribute(uint16_t handle, uint8_t indicate, uint8_t * data, uint8_t length)
{
	// maximum writtable data is 54 bytes length
	uint8_t payload[54];

	uint8_t flag = 0;

	if (length > 54)
	{
		length = 54;
	}

	payload[0] = (uint8_t)(handle & 0x00FF);
	payload[1] = (uint8_t)((handle & 0xFF00) >> 8);
	payload[2] = 0;
	payload[3] = length;

	for (uint8_t i = 0; i<length; i++)
	{
		payload[i+4] = data[i];
	}

	#if BLE_DEBUG>1
	PRINT_BLE(F("write local att: "));
	for(uint8_t i = 0; i < length; i++)
	{
		USB.printHex(payload[i+4]);
	}
	USB.println();
	#endif

	sendCommand(length+4,2,0,payload);

	readCommandAnswer(6, 1);

	// if indicated, wait till ack event.
	if (indicate == BLE_INDICATE_ENABLED )
	{
		flag = waitEvent(10000);
		if (flag == BLE_EVENT_ATTCLIENT_INDICATED)
		{
			#if BLE_DEBUG>1
			uint16_t handler = ((uint16_t)event[6] << 8) | event[5];
			char message[40] ="";
			strcpy(message, (char*)pgm_read_word(&(table_BLE[15])));
            USB.printf(message, handler);
			#endif
			return 1;
		}
		else
		{
			return flag;
		}
	}

	return errorCode;
}

/*
 Function: read an attribute from a remote BLE device
 Returns:
 Parameters:
 Values: return error Code. 0 if OK, 1 if event value not found, error code if error sending command. Event identification number otherwise.
*/
uint16_t WaspBLE::attributeRead(uint8_t connection_handle, uint16_t att_handle)
{
	memset(attributeValue, 0x00, sizeof(attributeValue));

	uint16_t aux;
	uint8_t aux2;
	uint8_t payload[3];
	payload[0] = connection_handle;
	payload[1] = (uint8_t)(att_handle & 0x00FF);
	payload[2] = (uint8_t)((att_handle & 0xFF00) >> 8);

	sendCommand(3,4,4,payload);

	readCommandAnswer(7, 1);

	if (errorCode != 0)
	{
		// error ocurred,
		return errorCode;
	}

	uint8_t flag = waitEvent(2000);

	// unknown event length
	if (flag == 0)
	{
		return 1;
	}
	else
	{
		if (flag != BLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE)
		{
			return flag;
		}
	}

	// Check if event attribute is the one we read
	aux = ((uint16_t)event[6] << 8) | event[5];

	if ((event[4] == connection_handle) && (aux == att_handle))
	{

		// save first byte as length of the value.  22 bytes max
		// Value is stored from possition
		aux2 = event[8];

		if (aux2 > 22)
		{
			aux2 = 22;
		}

		// If datalength is 0, then write a zero ascii manually
		if (aux2 == 0)
		{
			attributeValue[0] = 1;
			attributeValue[1] = 0x30;
		}
		else
		{
			for (uint8_t i = 0; i < aux2+1; i++)
			{
				attributeValue[i] = event[i+8];
			}
		}
	}

	// If here, no error while reading.
	return 0;

}

/*
 Function: write an attribute from a remote BLE device
 * att handle in decimal.
 Returns: return errorCode in any case. 0 means success. event identification number if write procedure completed event not received.
 Parameters:
 Values:
*/
uint16_t WaspBLE::attributeWrite(uint8_t connection, uint16_t atthandle, char * data)
{
	memset(attributeValue, 0x00, sizeof(attributeValue));

	// attribute data is variable. save the length.
	uint8_t dataLength = strlen(data);

	//limit size to  max write size: 20 bytes
	if (dataLength > 20)
	{
		dataLength = 20;
	}

	memcpy(attributeValue, data, dataLength);

	return attributeWrite(connection, atthandle, attributeValue, dataLength);
}

/*
 Function: write an attribute from a remote BLE device
 * att handle in decimal.
 Returns: return errorCode in any case. 0 means success. event identification number if write procedure completed event not received.
 Parameters:
 Values:
*/
uint16_t WaspBLE::attributeWrite(uint8_t connection, uint16_t atthandle, uint8_t * data, uint8_t length)
{

	uint8_t payload[length];

	payload[0] = connection;
	payload[1] = (uint8_t)(atthandle & 0x00FF);
	payload[2] = (uint8_t)((atthandle & 0xFF00) >> 8);

	// Now add datalength to first byte of uint8arrray, to comply with BGAPI protocol

	payload[3] = length;

	for(uint8_t i = 0; i < length; i++)
	{
		payload[i+4] = data[i];
	}

	// LL for the command must be the data_lenght+4, because data is uint8array
	sendCommand(length+4,4,5,payload);

	if (readCommandAnswer(7,1) != 0)
	{
		#if BLE_DEBUG > 0
		// copy from flash "error writing. err: %x\n"
		char message[30] ="";
		strcpy_P(message, (char*)pgm_read_word(&(table_BLE[9])));
		PRINT_BLE(F(""));
		USB.printf(message, errorCode);
		#endif
	}
	else
	{
		// wait event attclient_procedure_completed 80 05 04 01 [connection] [result] [chrhandle]

		uint8_t flag = waitEvent(1000);

		if (flag != BLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED)
		{
			return flag;
		}
		// Parse result to determine if write was successfull
		// resul stored in positions 5 and 6
		errorCode = ((uint16_t)event[6] << 8) | event[5];
	}

	return errorCode;
}

/*
 Function: identify event saved on event buffer.
 Returns: return event identification number accordint to next list.
 Parameters:
 Values:
*/
/* Event identification number list
 * // System events
 * BLE_EVENT_SYSTEM_BOOT =							  	1;
 * BLE_EVENT_SYSTEM_DEBUG =							  	2;
 * BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_RX =			  	3;
 * BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_TX =			  	4;
 * BLE_EVENT_SYSTEM_SCRIPT_FAILURE =				  	5;
 * BLE_EVENT_SYSTEM_NO_LICENSE_KEY =				  	6;
 * // Persistent store events
 * BLE_EVENT_FLASH_PS_KEY =								7;
 * // Attribute database events
 * BLE_EVENT_ATTRIBUTES_VALUE =							8;
 * BLE_EVENT_ATTRIBUTES_USER_READ_REQUEST =				9;
 * BLE_EVENT_ATTRIBUTES_STATUS =						10;
 * // Connection
 * BLE_EVENT_CONNECTION_STATUS =						11;
 * BLE_EVENT_CONNECTION_VERSION_IND =					12;
 * BLE_EVENT_CONNECTION_FEATURE_IND	 =					13;
 * BLE_EVENT_CONNECTION_RAW_RX =						14;
 * BLE_EVENT_CONNECTION_DISCONNECTED =					15;
 * // Attribute cliente events
 * BLE_EVENT_ATTCLIENT_INDICATED =						16;
 * BLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED =			17;
 * BLE_EVENT_ATTCLIENT_GROUP_FOUND =					18;
 * BLE_EVENT_ATTCLIENT_ATTRIBUTE_FOUND =				19;
 * BLE_EVENT_ATTCLIENT_FIND_INFORMATION_FOUND =			20;
 * BLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE =				21;
 * BLE_EVENT_ATTCLIENT_READ_MULTIPLE_RESPONSE =			22;
 * // Security manager events
 * BLE_EVENT_SM_SMP_DATA =								23;
 * BLE_EVENT_SM_BONDING_FAIL =							24;
 * BLE_EVENT_SM_PASSKEY_DISPLAY =						25;
 * BLE_EVENT_SM_PASSKEY_REQUEST	 =						26;
 * BLE_EVENT_SM_BOND_STATUS	 =							27;
 * // Gerneric access profile events.
 * BLE_EVENT_GAP_SCAN_RESPONSE =						28;
 * BLE_EVENT_GAP_MODE_CHANGED =							29;
 * // Hardware events
 * BLE_EVENT_HARDWARE_IO_PORT_STATUS =					30;
 * BLE_EVENT_HARDWARE_SOFT_TIMER =						31;
 * BLE_EVENT_HARDWARE_ADC_RESULT =						32;
 */
uint8_t WaspBLE::parseEvent()
{

	// if no event preset on event buffer, exit.
	if (event[0] == 0)
	{
		return 0;
	}

	// check class and method bytes

	if (event[2] == 0)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_SYSTEM_BOOT;
			case 1:	return BLE_EVENT_SYSTEM_DEBUG;
			case 2:	return BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_RX;
			case 3:	return BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_TX;
			case 4:	return BLE_EVENT_SYSTEM_SCRIPT_FAILURE;
			case 5:	return BLE_EVENT_SYSTEM_NO_LICENSE_KEY;

		}
	}
	else if (event[2] == 1)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_FLASH_PS_KEY;
		}
	}
	else if (event[2] == 2)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_ATTRIBUTES_VALUE;
			case 1:	return BLE_EVENT_ATTRIBUTES_USER_READ_REQUEST;
			case 2:	return BLE_EVENT_ATTRIBUTES_STATUS;
		}
	}
	else if (event[2] == 3)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_CONNECTION_STATUS;
			case 1:	return BLE_EVENT_CONNECTION_VERSION_IND;
			case 2:	return BLE_EVENT_CONNECTION_FEATURE_IND;
			case 3:	return BLE_EVENT_CONNECTION_RAW_RX;
			case 4:	return BLE_EVENT_CONNECTION_DISCONNECTED;
		}
	}
	else if (event[2] == 4)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_ATTCLIENT_INDICATED;
			case 1:	return BLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED;
			case 2:	return BLE_EVENT_ATTCLIENT_GROUP_FOUND;
			case 3:	return BLE_EVENT_ATTCLIENT_ATTRIBUTE_FOUND;
			case 4:	return BLE_EVENT_ATTCLIENT_FIND_INFORMATION_FOUND;
			case 5:	return BLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE;
			case 6:	return BLE_EVENT_ATTCLIENT_READ_MULTIPLE_RESPONSE;
		}
	}
	else if (event[2] == 5)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_SM_SMP_DATA;
			case 1:	return BLE_EVENT_SM_BONDING_FAIL;
			case 2:	return BLE_EVENT_SM_PASSKEY_DISPLAY;
			case 3:	return BLE_EVENT_SM_PASSKEY_REQUEST;
			case 4:	return BLE_EVENT_SM_BOND_STATUS;
		}
	}
	else if (event[2] == 6)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_GAP_SCAN_RESPONSE;
			case 1:	return BLE_EVENT_GAP_MODE_CHANGED;
		}
	}
	else if (event[2] == 7)
	{
		switch (event[3])
		{
			case 0:	return BLE_EVENT_HARDWARE_IO_PORT_STATUS;
			case 1:	return BLE_EVENT_HARDWARE_SOFT_TIMER;
			case 2:	return BLE_EVENT_HARDWARE_ADC_RESULT;
		}
	}

	// if here, an error ocurred.
	return 0;

}

/*
 Function: sends the get status command to know the state of a connection.
 Returns: return 255 if status not received, connection status otherwise.
 Parameters:
 Values:
*/
uint8_t WaspBLE::getStatus(uint8_t connection)
{
	uint8_t connectionStatus = 0;

	sendCommand(1,3,7,&connection);

	// ignore answer.
	//readCommandAnswer(5,0);

	uint8_t flag = waitEvent(5000);

	if (flag == BLE_EVENT_CONNECTION_STATUS)
	{
		// parse the status: 0 not connected; 1 connected; 2 encrypted;
		// 4 connection completed; 8 parameters changed
		connectionStatus = event[5];

		return connectionStatus;
	}
	else
	{
		//no status received

		USB.println(flag,DEC);

		return 255;
	}
}


/// Preinstantiate Objects /////////////////////////////////////////////////////
WaspBLE BLE = WaspBLE();		//object
