/*
 *  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.8
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_CORE /////////////////////////////////////////////////////////////////

const char get_own_mac_low[]	PROGMEM	= 	"7E00040852534C06"; 	// AT+SL
const char get_own_mac_high[] 	PROGMEM	= 	"7E0004085253480A"; 	// AT+SH
const char set_own_net_address[] PROGMEM = 	"7E000608524D59000000";	// AT+MY
const char get_own_net_address[] PROGMEM = 	"7E000408524D59FF";		// AT+MY
const char set_baudrate[] 		PROGMEM = 	"7E0005085242440000";	// AT+BD
const char set_api_mode[] 		PROGMEM = 	"7E0005085241500000";	// AT+AP
const char set_api_options[] 	PROGMEM = 	"7E00050852414F0000";	// AT+AO
const char set_pan[] 			PROGMEM = 	"7E000608524944000000";	// AT+ID
const char set_pan_zb[] 		PROGMEM = 	"7E000C08524944000000000000000000";	// AT+ID
const char get_pan[] 			PROGMEM = 	"7E00040852494418";		// AT+ID
const char set_sleep_mode_xbee[] PROGMEM = 	"7E00050852534D0000";	// AT+SM
const char get_sleep_mode_xbee[] PROGMEM = 	"7E00040852534D05";		// AT+SM
const char set_awake_time[] 	PROGMEM = 	"7E000608525354000000";		// AT+ST
const char set_awake_time_DM[] 	PROGMEM = 	"7E00070852535400000000";	// AT+ST
const char set_sleep_time[] 	PROGMEM = 	"7E000608525350000000";		// AT+SP
const char set_sleep_time_DM[] 	PROGMEM = 	"7E00070852535000000000";	// AT+SP
const char set_channel[] 		PROGMEM = 	"7E0005085243480000";	// AT+CH
const char get_channel[] 		PROGMEM = 	"7E0004085243481A";		// AT+CH
const char get_NI[] 			PROGMEM = 	"7E000408524E490E";		// AT+NI
const char set_scanning_time[] 	PROGMEM = 	"7E000508524E540000";	// AT+NT
const char set_scanning_time_DM[] PROGMEM = "7E000608524E54000000";	// AT+NT
const char get_scanning_time[] 	PROGMEM = 	"7E000408524E5403";		// AT+NT
const char set_discov_options[] PROGMEM = 	"7E000508524E4F0000";	// AT+NO
const char get_discov_options[] PROGMEM = 	"7E000408524E4F08";		// AT+NO
const char write_values[] 		PROGMEM = 	"7E000408525752FC";		// AT+WR
const char set_scanning_channel[] PROGMEM = "7E000608525343000000";	// AT+SC
const char get_scanning_channel[] PROGMEM = "7E0004085253430F";		// AT+SC
const char get_duration_energy[] PROGMEM = 	"7E0004085253440E";		// AT+SD
const char set_link_key[] 		PROGMEM = 	"7E001408524B590000000000000000000000000000000000";	// AT+KY
const char set_encryption[] 	PROGMEM = 	"7E0005085245450000";	// AT+EE
const char get_encryption[] 	PROGMEM = 	"7E0004085245451B";		// AT+EE
const char set_power_level[] 	PROGMEM = 	"7E00050852504C0000";	// AT+PL
const char get_power_level[] 	PROGMEM = 	"7E00040852504C09";		// AT+PL
const char get_RSSI[] 			PROGMEM = 	"7E0004085244421F";		// AT+DB
const char get_hard_version[] 	PROGMEM = 	"7E00040852485607";		// AT+HV
const char get_soft_version[] 	PROGMEM = 	"7E000408525652FD";		// AT+VR
const char set_RSSI_time[] 		PROGMEM = 	"7E0005085252500000";	// AT+RP
const char get_RSSI_time[] 		PROGMEM	= 	"7E00040852525003";		// AT+RP
const char apply_changes[] 		PROGMEM = 	"7E00040852414321";		// AT+AC
const char reset_xbee[] 		PROGMEM = 	"7E0004085246520D";		// AT+FR
const char reset_defaults_xbee[] PROGMEM = 	"7E0004085252450E";		// AT+RE
const char set_sleep_options_xbee[] PROGMEM = "7E00050852534F0000";	// AT+SO
const char get_sleep_options_xbee[] PROGMEM = "7E00040852534F03";	// AT+SO
const char scan_network	[] 		PROGMEM = 	"7E000408524E4413";		// AT+ND
const char set_duration_energy[] PROGMEM = 	"7E0005085245440000"; 	// AT+ED
const char set_duration_energy_ZB[] PROGMEM="7E0005085253440000"; 	// AT+SD
const char get_low_dest_address[] PROGMEM =	"7E00040852444C15"; 	// AT+DL
const char timestamp_packet[] 	PROGMEM =	"%2u%2u%2u%2u%2u%2u%2u%c%2u%2u";

const char* const table_CORE[] PROGMEM=
{
	get_own_mac_low, 		// 0
	get_own_mac_high,		// 1
	set_own_net_address,	// 2
	get_own_net_address,	// 3
	set_baudrate,			// 4
	set_api_mode,			// 5
	set_api_options,		// 6
	set_pan,				// 7
	set_pan_zb,				// 8
	get_pan,				// 9
	set_sleep_mode_xbee,	// 10
	get_sleep_mode_xbee,	// 11
	set_awake_time,			// 12
	set_awake_time_DM,		// 13
	set_sleep_time,			// 14
	set_sleep_time_DM,		// 15
	set_channel,			// 16
	get_channel,			// 17
	get_NI,					// 18
	set_scanning_time,		// 19
	set_scanning_time_DM,	// 20
	get_scanning_time,		// 21
	set_discov_options,		// 22
	get_discov_options,		// 23
	write_values,			// 24
	set_scanning_channel,	// 25
	get_scanning_channel,	// 26
	get_duration_energy,	// 27
	set_link_key,			// 28
	set_encryption,			// 29
	get_encryption,			// 30
	set_power_level,		// 31
	get_power_level,		// 32
	get_RSSI,				// 33
	get_hard_version,		// 34
	get_soft_version,		// 35
	set_RSSI_time,			// 36
	get_RSSI_time,			// 37
	apply_changes,			// 38
	reset_xbee,				// 39
	reset_defaults_xbee,	// 40
	set_sleep_options_xbee,	// 41
	get_sleep_options_xbee,	// 42
	scan_network,			// 43
	set_duration_energy,	// 44
	set_duration_energy_ZB,	// 45
	get_low_dest_address,	// 46
	timestamp_packet,		// 47
};


/// table_OTA //////////////////////////////////////////////////////////////////

const char NEW_FIRMWARE_MESSAGE_OK[] 		PROGMEM	="PROGRAM RECEIVED OK$$$$$$$$$$$$$";
const char NEW_FIRMWARE_MESSAGE_ERROR[] 	PROGMEM	="PROGRAM RECEIVED ERROR$$$$$$$$$$";
const char UPLOAD_FIRWARE_MESSAGE_OK[] 		PROGMEM	="START WITH FIRMWARE OK$$$$$$$$$$$$$$$$$$$$$$$$$$";
const char UPLOAD_FIRWARE_MESSAGE_ERROR[] 	PROGMEM ="START WITH FIRMWARE ERROR$$$$$$$$$$$$$$$$$$$$$$$";
const char REQUEST_BOOTLIST_MESSAGE[] 		PROGMEM	="READ BOOTLIST$$$$$$$$$$$$$$$$$";
const char ANSWER_START_WITH_FIRMWARE_OK[] 	PROGMEM	="NEW PROGRAM RUNNING$$$$$$$$$$$$$";
const char ANSWER_START_WITH_FIRMWARE_ERR[]	PROGMEM	="PREVIOUS PROGRAM RUNNING$$$$$$$$";
const char RESET_MESSAGE[] 					PROGMEM	="RESTARTING$$$$$$$$$$$$$$$$$$$$$$";
const char DELETE_MESSAGE_OK[] 				PROGMEM	="FIRMWARE DELETED$$$$$$$$$$$$$$$$";
const char DELETE_MESSAGE_ERROR[] 			PROGMEM	="FIRMWARE NOT DELETED$$$$$$$$$$$$";
const char START_SECTOR[] 					PROGMEM	="FIRMWARE_FILE_FOR_WASPMOTE######";
const char FILEAUX[] 						PROGMEM ="FILEAUX";


const char* const table_OTA[] PROGMEM=
{
	NEW_FIRMWARE_MESSAGE_OK, 		// 0
	NEW_FIRMWARE_MESSAGE_ERROR,		// 1
	UPLOAD_FIRWARE_MESSAGE_OK,		// 2
	UPLOAD_FIRWARE_MESSAGE_ERROR,	// 3
	REQUEST_BOOTLIST_MESSAGE,		// 4
	ANSWER_START_WITH_FIRMWARE_OK,	// 5
	ANSWER_START_WITH_FIRMWARE_ERR,	// 6
	RESET_MESSAGE,					// 7
	DELETE_MESSAGE_OK,				// 8
	DELETE_MESSAGE_ERROR,			// 9
	START_SECTOR,					// 10
	FILEAUX,						// 11
};



/******************************************************************************
 * Class methods
 ******************************************************************************/


/*
 * Function: Get the 32 lower bits of my MAC address
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 	Values: When it is executed stores the returned value by SL command in the
 *			global "sourceMacLow[4]" variable
 */
uint8_t WaspXBeeCore::getOwnMacLow()
{
    int8_t error=2;
    error_AT=2;
    char buffer[17];

	// get_own_mac_low
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[0])));
    if(buffer==NULL)return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(error==0)
    {
		sourceMacLow[0]=data[0];
		sourceMacLow[1]=data[1];
		sourceMacLow[2]=data[2];
		sourceMacLow[3]=data[3];
    }
    return error;
}

/*
 Function: Get the 32 higher bits of my MAC address
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: When it is executed stores the returned value by SH in the global
         "sourceMacHigh[4]" variable
*/
uint8_t WaspXBeeCore::getOwnMacHigh()
{
    int8_t error=2;
    error_AT=2;
    char buffer[17];

	// get_own_mac_high
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[1])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(error==0)
    {
		sourceMacHigh[0]=data[0];
		sourceMacHigh[1]=data[1];
		sourceMacHigh[2]=data[2];
		sourceMacHigh[3]=data[3];
    }
    return error;
}

/*
 Function: Get the 64 bits of my MAC address
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes functions getOwnMacLow() and getOwnMacHigh()
*/
 uint8_t WaspXBeeCore::getOwnMac()
{
    int8_t error=2;
    error=getOwnMacLow();
    if(error==0)
    {
        error=getOwnMacHigh();
    }
    return error;
}

/*
 Function: Set the 16b network address
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   NA_H : Higher byte of Network Address (0x00-0xFF)
   NA_L : Lower byte of Network Address (0x00-0xFF)
   Values: Stores in global "sourceNA[2]" variable the 16b address set by the user
 */
uint8_t WaspXBeeCore::setOwnNetAddress(char* NA)
{
	uint8_t networkAddress[2];
	Utils.str2hex( (char*)NA, (uint8_t*)networkAddress );

    return setOwnNetAddress( networkAddress[0], networkAddress[1]);
}

/*
 Function: Set the 16b network address
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   NA_H : Higher byte of Network Address (0x00-0xFF)
   NA_L : Lower byte of Network Address (0x00-0xFF)
   Values: Stores in global "sourceNA[2]" variable the 16b address set by the user
 */
uint8_t WaspXBeeCore::setOwnNetAddress(uint8_t* NA)
{
    return setOwnNetAddress( NA[0], NA[1] );
}

/*
 Function: Set the 16b network address
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   NA_H : Higher byte of Network Address (0x00-0xFF)
   NA_L : Lower byte of Network Address (0x00-0xFF)
   Values: Stores in global "sourceNA[2]" variable the 16b address set by the user
 */
uint8_t WaspXBeeCore::setOwnNetAddress(uint8_t NA_H, uint8_t NA_L)
{
    int8_t error=2;
    char buffer[21];

    if(protocol==XBEE_802_15_4)
    {
        error_AT=2;

		// set_own_net_address
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[2])));
        if(buffer==NULL) return 1;

        gen_data(buffer,NA_H,NA_L);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }

    if(!error)
    {
        sourceNA[0]=NA_H;
        sourceNA[1]=NA_L;
    }
    return error;
}
/*
 * Function: Get the 16-bit network address
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2  --> The command has not been executed
 * 	error=1  --> There has been an error while executing the command
 * 	error=0  --> The command has been executed with no errors
 * 	error=-1 --> Forbidden command in this protocol
 *
 * Values: Stores in global "sourceNA[2]" variable the returned 16b network
 * address by MY command
*/
uint8_t WaspXBeeCore::getOwnNetAddress()
{
    int8_t error=2;
    char buffer[17];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;

        // get_own_net_address
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[3])));
        if(buffer==NULL) return 1;

        gen_data(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }

    if(!error)
    {
        sourceNA[0]=data[0];
        sourceNA[1]=data[1];
    }
    return error;
}


/*
 Function: Set Baudrate to use
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   baud_rate: integer that contains the baudrate
   Values: Stores in global "baudrate" variable the baudrate
 */
uint8_t WaspXBeeCore::setBaudrate(uint8_t baud_rate)
{
    int8_t error=2;
    error_AT=2;
    char buffer[19];

	// set_baudrate
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[4])));
    if(buffer==NULL) return 1;

    gen_data(buffer,baud_rate);
    gen_checksum(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        baudrate=baud_rate;
    }
    return error;
}

/*
 Function: Set API values
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   api_value: integer that contains the api value
   Values: Stores in global "apiValue" variable the baudrate
 */
uint8_t WaspXBeeCore::setAPI(uint8_t api_value)
{
    int8_t error=2;
    error_AT=2;
    char buffer[19];

	// set_api_mode
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[5])));
    if(buffer==NULL) return 1;

    gen_data(buffer,api_value);
    gen_checksum(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        apiValue=api_value;
    }
    return error;
}

/*
 Function: Set API options. Enable ZIgBee Application Layer Addressing
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command in this protocol
 Parameters:
   api_options: integer that contains the baudrate
 */
uint8_t WaspXBeeCore::setAPIoptions(uint8_t api_options)
{
    int8_t error=2;
    char buffer[19];

    if( (protocol!=XBEE_802_15_4) )
    {
        error_AT=2;

		// set_api_options
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[6])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,api_options);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    return error;
}

/*
 Function: Set the network identifier
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Parameters:
   PANID: Array of integers than contains the 16b or 64b PAN ID
 Values: Stores in global "PAN_ID" variable the recent set PAN ID value
 */
uint8_t WaspXBeeCore::setPAN(uint8_t* PANID)
{
    int8_t error=2;
    char buffer[33];

    if( (protocol == XBEE_802_15_4)
	||	(protocol == DIGIMESH)
	||	(protocol == XBEE_900)
	|| 	(protocol == XBEE_868)
	|| 	(protocol == XBEE_868LP)
	|| 	(protocol == XBEE_900HP) )
    {
        error_AT=2;

		// set_pan
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[7])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,PANID);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if(protocol==ZIGBEE)
    {
        error_AT=2;
		flush();
		// set_pan_zb
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[8])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,PANID);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if(!error)
    {
		if( (protocol == XBEE_802_15_4)
		||	(protocol == DIGIMESH)
		||	(protocol == XBEE_900)
		|| 	(protocol == XBEE_868)
		|| 	(protocol == XBEE_868LP)
		|| 	(protocol == XBEE_900HP) )
		{
			PAN_ID[0] = PANID[0];
			PAN_ID[1] = PANID[1];
        }

        if( protocol == ZIGBEE )
        {
			PAN_ID[0] = PANID[0];
			PAN_ID[1] = PANID[1];
			PAN_ID[2] = PANID[2];
			PAN_ID[3] = PANID[3];
			PAN_ID[4] = PANID[4];
			PAN_ID[5] = PANID[5];
			PAN_ID[6] = PANID[6];
			PAN_ID[7] = PANID[7];
        }
    }
    return error;
}

/*
 Function: Get Network ID
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "error" variable any error happened while execution
	 Stores in global "PAN_ID" variable the 16b or 64b network PAN ID
*/
uint8_t WaspXBeeCore::getPAN()
{
    int8_t error=2;

    error_AT=2;
    char buffer[20];

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[9]))); // get_pan
    if(buffer==NULL) return 1;

    gen_data(buffer);
    if( protocol==ZIGBEE ) error=gen_send(buffer);
    else error=gen_send(buffer);

    if(!error)
    {
		if( (protocol == XBEE_802_15_4)
		||	(protocol == DIGIMESH)
		||	(protocol == XBEE_900)
		|| 	(protocol == XBEE_868)
		|| 	(protocol == XBEE_868LP)
		|| 	(protocol == XBEE_900HP) )
		{
			PAN_ID[0] = data[0];
			PAN_ID[1] = data[1];
        }
        if(protocol==ZIGBEE)
        {
			PAN_ID[0] = data[0];
			PAN_ID[1] = data[1];
			PAN_ID[2] = data[2];
			PAN_ID[3] = data[3];
			PAN_ID[4] = data[4];
			PAN_ID[5] = data[5];
			PAN_ID[6] = data[6];
			PAN_ID[7] = data[7];
        }
    }
    return error;
}

/*
 Function: Set the module to the sleep mode specified.
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores the returned value by SM command in the global "sleepMode" variable
 Parameters:
   sleep: Defines the sleep mode to use by the XBee (0-5)
*/
uint8_t WaspXBeeCore::setSleepMode(uint8_t sleep)
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[10]))); // set_sleep_mode_xbee
    if(buffer==NULL) return 1;

    gen_data(buffer,sleep);
    gen_checksum(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        sleepMode=sleep;
    }
    return error;
}

/*
 Function: Get the XBee mode
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores the XBee mode in the global "sleepMode" variable
*/
uint8_t WaspXBeeCore::getSleepMode()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[11]))); // get_sleep_mode_xbee
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(error==0)
    {
        sleepMode=data[0];
    }
    return error;
}

/*
 Function: Set the time the module has to be idle before start sleeping
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the ST parameter in XBee module
	 Stores in global "awakeTime" the value of this time
 Parameters:
   awake: Array of integers that specifies the time to be awake before sleep
 */
uint8_t WaspXBeeCore::setAwakeTime(uint8_t* awake)
{
    int8_t error=2;
    char buffer[23];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) || (protocol==XBEE_868) || (protocol==XBEE_868LP) )
    {
        error_AT=2;

		// set_awake_time
     	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[12])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,awake);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if( (protocol==DIGIMESH) || (protocol==XBEE_900) || (protocol==XBEE_900HP) )
    {
        error_AT=2;

        // set_awake_time_DM
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[13])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,awake);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if(!error)
    {
        if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) || (protocol==XBEE_868) || (protocol==XBEE_868LP) )
        {
            awakeTime[0]=awake[0];
            awakeTime[1]=awake[1];
        }
        if( (protocol==DIGIMESH) || (protocol==XBEE_900) || (protocol==XBEE_900HP) )
        {
            awakeTime[0]=awake[0];
            awakeTime[1]=awake[1];
            awakeTime[2]=awake[2];
        }
    }
    return error;
}

/*
 Function: Set the cyclic sleeping time of the node
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the SP parameter in the XBee module
	 Stores in global "sleepTime" the value of this time
 Parameters:
   sleep: Array of Integers that specifies the amount of time the module spends sleeping
*/
uint8_t WaspXBeeCore::setSleepTime(uint8_t* sleep)
{
    int8_t error=2;
    char buffer[23];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) || (protocol==XBEE_868) || (protocol==XBEE_868LP) )
    {
        error_AT=2;

        // set_sleep_time
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[14])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,sleep);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if( (protocol==DIGIMESH) || (protocol==XBEE_900) || (protocol==XBEE_900HP) )
    {
        error_AT=2;

		// set_sleep_time_DM
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[15])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,sleep);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if(!error)
    {
        if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) || (protocol==XBEE_868) || (protocol==XBEE_868LP) )
        {
            sleepTime[0]=sleep[0];
            sleepTime[1]=sleep[1];
        }
        if( (protocol==DIGIMESH) || (protocol==XBEE_900) || (protocol==XBEE_900HP) )
        {
            sleepTime[0]=sleep[0];
            sleepTime[1]=sleep[1];
            sleepTime[2]=sleep[2];
        }
    }
    return error;
}

/*
 Function: Set the channel frequency where the module is going to work
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Stores the selected channel in the global "channel" variable
 Parameters:
   _channel: Channel used to transmit (0x0B-0x1A)
*/
uint8_t WaspXBeeCore::setChannel(uint8_t _channel)
{
    int8_t error=2;
    char buffer[20];


    if( (protocol==XBEE_802_15_4) || (protocol==DIGIMESH) || (protocol==XBEE_900) )
    {
        error_AT=2;

		// set_channel
    	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[16])));
    	if(buffer==NULL) return 1;

        gen_data(buffer,_channel);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(!error)
    {
        channel=_channel;
    }

    return error;
}

/*
 Function: Get the actual frequency channel
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores the frequency channel in the global "channel" variable
*/
uint8_t WaspXBeeCore::getChannel()
{
    int8_t error=2;
    char buffer[20];

    error_AT=2;

	// get_channel
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[17])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        channel=data[0];
    }
    return error;
}

/*
 Function: Set the Node Indentifier
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NI to the selected in the function
         The NI must be a 20 character max string
         Stores the given NI in the global "nodeID" variable
 Parameters:
   node: string that specifies the node indentifier
*/
uint8_t WaspXBeeCore::setNodeIdentifier(const char* node)
{
    uint8_t NI[30];

    NI[0]=0x7E;
    NI[1]=0x00;
    NI[3]=0x08;
    NI[4]=0x52;
    NI[5]=0x4E;
    NI[6]=0x49;
    int8_t error=2;
    uint8_t counter=0;
    uint8_t checksum=0;
	int index = 0;

	// init flag
    error_AT = 2;

    while( (node[index]!='\0') )
    {
        NI[index+7] = uint8_t(node[index]);
        index++;
    }
    NI[2] = 4+index;

    for(int i=3; i<(7+(NI[2]-4));i++)
    {
        checksum=checksum+NI[i];
    }
    while( (checksum>255))
    {
        checksum=checksum-256;
    }
    checksum=255-checksum;
    NI[7+NI[2]-4]=checksum;
    while(counter<(8+NI[2]-4))
    {
		// print byte through correspondent UART
		printByte( NI[counter], uart);
        counter++;
    }
    counter=0;
    clearCommand();
    command[5]=0x4E;
    command[6]=0x49;
    error=parse_message(command);

    if(error==0)
    {
        for(int i=0 ; i<NI[2]-4 ; i++)
        {
            nodeID[i] = node[i];
        }
    }

    return error;
}

/*
 Function: Get the Node Identifier
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores the NI in the global "nodeID" variable
*/
uint8_t WaspXBeeCore::getNodeIdentifier()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// get_NI
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[18])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        for( uint16_t i=0 ; i<data_length ; i++)
        {
            nodeID[i] = char(data[i]);
        }
    }
    return error;
}

/*
 Function: Scans for brothers in the same channel and same PAN ID
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores given info (SH,SL,MY,RSSI,NI) in global array "scannedBrothers" variable
         Stores in global "totalScannedBrothers" the number of founded brothers
 Parameters:
    node: 20-byte max string containing NI of the node to search
*/
uint8_t WaspXBeeCore::scanNetwork(const char* node)
{
    uint8_t ND[30]; //{0x7E, 0x00, 0x04, 0x08, 0x52, 0x4E, 0x44, 0x13};
    ND[0]=0x7E;
    ND[1]=0x00;
    ND[3]=0x08;
    ND[4]=0x52;
    ND[5]=0x4E;
    ND[6]=0x44;
    int8_t error = 2;
    uint8_t counter = 0;
    uint16_t checksum = 0;
    int index = 0;

    // init flag
    error_AT = 2;
    totalScannedBrothers = 0;

    while( (node[index]!='\0') )
    {
        ND[index+7] = uint8_t(node[index]);
        index++;
    }
    ND[2]=4+index;


    for(int i=3 ; i<(7+(ND[2]-4)) ; i++)
    {
        checksum=checksum+ND[i];
    }
    while( (checksum>255))
    {
        checksum=checksum-256;
    }
    checksum=255-checksum;
    ND[7+ND[2]-4]=checksum;
    while(counter<(8+ND[2]-4))
    {
		// print byte through correspondent UART
		printByte(ND[counter],  uart);
        counter++;
    }
    counter=0;
    clearCommand();
    command[5]=ND[5];
    command[6]=ND[6];
    error=parse_message(command);

    return error;
}


/*
 * Function: Defines the amount of time the scanNetwork() function is scanning
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * Values: Changes the NT command and stores in global "scanTime" variable the
 * 	recent set time
 * Parameters:
 * 	time: amount of time ND is scanning for brothers. Time = NT[x 100 ms]
 */
uint8_t WaspXBeeCore::setScanningTime(uint8_t* time)
{
    int8_t error=2;
    char buffer[30];

    if( protocol==XBEE_802_15_4 ||
		protocol==ZIGBEE 		)
    {
        error_AT=2;

		// set_scanning_time
		strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[19])));
		if(buffer==NULL)return 1;

        gen_data(buffer,time);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }

    if( ( protocol == XBEE_868)
    ||  ( protocol == XBEE_868LP)
	|| 	( protocol == DIGIMESH)
	|| 	( protocol == XBEE_900)
	||	( protocol == XBEE_900HP) )
    {
        error_AT=2;
		// set_scanning_time_DM
		strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[20])));
		if(buffer==NULL)return 1;

        gen_data(buffer,time);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }


    if(!error)
    {
        if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
        {
            scanTime[0]=time[0];
        }
        if( (protocol==DIGIMESH)
		|| (protocol==XBEE_868)
		|| (protocol==XBEE_868LP)
		|| (protocol==XBEE_900)
		|| (protocol==XBEE_900HP) )
        {
            scanTime[0]=time[0];
            scanTime[1]=time[1];
        }
    }
    return error;
}

/*
 Function: Get the Scanning Time
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "error" variable any error happened while execution
	 Stores in global "scanTime" the value of scanning time
*/
uint8_t WaspXBeeCore::getScanningTime()
{
    int8_t error=2;
    char buffer[20];

    error_AT=2;

	// get_scanning_time
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[21])));
    if(buffer==NULL)return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        if( (protocol==XBEE_802_15_4) )
        {
            scanTime[0]=data[0];
        }
        if( (protocol==ZIGBEE))
        {
            scanTime[0]=data[1];
        }
        if( (protocol==DIGIMESH)
        || (protocol==XBEE_868)
        || (protocol==XBEE_868LP)
        || (protocol==XBEE_900)
        || (protocol==XBEE_900HP) )
        {
            scanTime[0]=data[0];
            scanTime[1]=data[1];
        }
    }
    return error;
}

/*
 Function: Set the options value for the network discovery command
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NO command
 Parameters:
   options: chosen option (0x00-0x03)
*/
uint8_t WaspXBeeCore::setDiscoveryOptions(uint8_t options)
{
    char buffer[20];

    int8_t error=2;

	// set_discov_options
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[22])));
    if(buffer==NULL)return 1;

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;
        gen_data(buffer,options);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(!error)
    {
        discoveryOptions=options;
    }
    return error;
}

/*
 Function: Get the options value for the network discovery command
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NO command. Stores in global "discoveryOptions" variable the options
*/
uint8_t WaspXBeeCore::getDiscoveryOptions()
{
    int8_t error=2;
    char buffer[20];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;

		// get_discov_options
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[23])));
        if(buffer==NULL) return 1;

        gen_data(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(error==0)
    {
        discoveryOptions=data[0];
    }
    return error;
}

/*
 Function: Performs a quick search.
	   802.15.4 : It keeps in DL the MY of the looked up NI brother
	   ZIGBEE : Stores in global "paquete" naD,macDH,macDL from the searched device
	   DIGIMESH: Stores in global "paquete" macDH,macDL from the searched device
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes DN command.
 Parameters:
   node: string that specifies the NI that identifies the searched brother
*/
uint8_t WaspXBeeCore::nodeSearch(const char* node, uint8_t* address)
{
    uint8_t DN[30]; //{0x7E, 0x00, 0x??, 0x08, 0x52, 0x44, 0x4E, 0x??};
    DN[0]=0x7E;
    DN[1]=0x00;
    DN[3]=0x08;
    DN[4]=0x52;
    DN[5]=0x44;
    DN[6]=0x4E;
    int8_t error=2;
    uint8_t counter=0;
    uint8_t checksum=0;
    int index=0;

	// init flag
    error_AT=2;

	// set string with node name to AT command
    while( (node[index]!='\0') )
    {
        DN[index+7]=uint8_t(node[index]);
        index++;
    }

    // set length field in AT command
    DN[2]=4+index;

    // set checksum to AT command
    for(int i=3 ; i<(7+(DN[2]-4)) ; i++)
    {
        checksum=checksum+DN[i];
    }
    while( (checksum>255))
    {
        checksum=checksum-256;
    }
    checksum=255-checksum;
    DN[7+DN[2]-4]=checksum;

	// send AT command to XBee module
    while(counter<(8+DN[2]-4))
    {
		// print byte through correspondent UART
		printByte(DN[counter],  uart);
        counter++;
    }

    counter=0;
    clearCommand();
    command[5]=0x44;
    command[6]=0x4E;
    error=parse_message(command);

    if(error==0)
    {
		// get destination address
		if(getDestinationAddress(address) != 0)
		{
			error=1;
		}
    }

    return error;
}

/*
 Function: Write the current parameters to a non volatil memory
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the WR command
*/
uint8_t WaspXBeeCore::writeValues()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[24])));//write_values
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    return error;
}

/*
 Function: Specifies the list of channels to scan when performing an energy scan
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Change the SC command. Stores in global "scanChannels" variable the
	list of channels
 Parameters:
   channel_H: higher byte of list of channels (0x00-0xFF)
   channel_L: lower byte of list of channels (0x00-0xFF)
   Channels are scpedified as a bitmap where depending on the bit a channel is
   selected --> Bit (Channel):
	0 (0x0B)	4 (0x0F)	8 (0x13) 	12 (0x17)
	1 (0x0C) 	5 (0x10) 	9 (0x14) 	13 (0x18)
	2 (0x0D) 	6 (0x11) 	10 (0x15) 	14 (0x19)
	3 (0x0E) 	7 (0x12)	11 (0x16)  	15 (0x1A)
*/
uint8_t WaspXBeeCore::setScanningChannels(uint8_t channel_H, uint8_t channel_L)
{
    int8_t error=2;
    char buffer[20];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;

		// set_scanning_channel
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[25])));
        if(buffer==NULL) return 1;

        gen_data(buffer,channel_H,channel_L);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(error==0)
    {
        scanChannels[0]=channel_H;
        scanChannels[1]=channel_L;
    }
    return error;
}

/*
 Function: Get the list of channels to scan when performing an energy scan
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Stores in global "scanChannels" variable the scanning channel list
*/
uint8_t WaspXBeeCore::getScanningChannels()
{
    int8_t error=2;
    char buffer[20];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;

        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[26])));//get_scanning_channel
        if(buffer==NULL) return 1;

        gen_data(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(error==0)
    {
		scanChannels[0]=data[0];
		scanChannels[1]=data[1];
    }
    return error;
}

/*
 Function: It gets the time the energy scan will be performed
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Change the SD command. Stores in global "timeEnergyChannel" variable the time the energy
	 scan will be performed
*/
uint8_t WaspXBeeCore::getDurationEnergyChannels()
{
    int8_t error=2;
    char buffer[20];

    if( (protocol==XBEE_802_15_4) || (protocol==ZIGBEE) )
    {
        error_AT=2;

        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[27])));//get_duration_energy
        if(buffer==NULL) return 1;

        gen_data(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(!error)
    {
        timeEnergyChannel=data[0];
    }
    return error;
}

/*
 Function: Sets the encryption key to be used in the 128b AES algorithm
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the KY command. Stores in global "linkKey" variable the key has been set
 Parameters:
   key: 16 byte array of chars that specifies the 128b AES key
*/
uint8_t WaspXBeeCore::setLinkKey(const char* key)
{
    int8_t error=2;
    char buffer[50];
    error_AT=2;

	// set_link_key
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[28])));
    if(buffer==NULL) return 1;

    gen_data(buffer,key);
    gen_checksum(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        for(int i=0 ; i<16 ; i++)
        {
            linkKey[i]=char(key[i]);
            if(key[i]=='\0') break;
        }
    }
    return error;
}

/*
 Function: Sets the encryption mode on/off
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EE command. Stores in global "encryptMode" variable the encryption mode
 Parameters:
   mode: on/off the encryption mode (1/0)
*/
uint8_t WaspXBeeCore::setEncryptionMode(uint8_t mode)
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// set_encryption
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[29])));
    if(buffer==NULL) return 1;

    gen_data(buffer,mode);
    gen_checksum(buffer);
    error=gen_send(buffer);
    if(!error)
    {
        encryptMode=mode;
    }
    return error;
}




/*
 Function: Gets the encryption mode on/off
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EE command. Stores in global "encryptMode" variable the encryption mode
 Parameters:
   mode: on/off the encryption mode (1/0)
*/
uint8_t WaspXBeeCore::getEncryptionMode()
{
	int8_t error=2;
    char buffer[20];
	error_AT=2;

	// get_encryption
	strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[30])));
	if(buffer==NULL) return 1;

	gen_data(buffer);
	error=gen_send(buffer);

    if(!error)
    {
        encryptMode=data[0];
    }
    return error;
}



/*
 Function: Select the power level at which the RF module transmits
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the PL command. Stores in global "powerLevel" the power level at which RF tx
 Parameters:
   value: power level of transmission (0-4)
*/
uint8_t WaspXBeeCore::setPowerLevel(uint8_t value)
{
    int8_t error=2;
    char buffer[20];

    if(protocol!=XBEE_900)
    {
        error_AT=2;

		// set_power_level
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[31])));
        if(buffer==NULL) return 1;

        gen_data(buffer,value);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    if(!error)
    {
        powerLevel=value;
    }
    return error;
}


/*
 Function: Get the power level at which the RF module transmits
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Read the PL command. Stores in global "powerLevel" the power level at
		 which RF tx
 Parameters:
   value: power level of transmission (0-4)
*/
uint8_t WaspXBeeCore::getPowerLevel()
{
    int8_t error=2;
    char buffer[20];

    if(protocol!=XBEE_900)
    {
        error_AT=2;

        // get_power_level
		strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[32])));
		if(buffer==NULL) return 1;

		gen_data(buffer);
		error=gen_send(buffer);
    }

    if(!error)
    {
        powerLevel=data[0];
    }
    return error;
}


/*
 Function: Get the Received Signal Strength Indicator of the last received packet
 Returns: Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "valueRSSI" variable the RSSI value of last received packet
*/
uint8_t WaspXBeeCore::getRSSI()
{
    int8_t error = 2;
    uint8_t ByteIN[40];
    uint8_t i=0;
    char buffer[20];

    //clear buffer
    memset( ByteIN, 0x00, sizeof(ByteIN) );

    if( (protocol == XBEE_802_15_4 ) || (protocol==ZIGBEE) || (protocol==XBEE_868LP) || (protocol==XBEE_900HP) )
    {
        error_AT=2;

        // get_RSSI
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[33])));
        if(buffer==NULL) return 1;

        gen_data(buffer);
        error = gen_send(buffer);

        if (error == 0)
        {
            valueRSSI[0] = data[0];
        }
    }
    else if( (protocol== DIGIMESH) || (protocol==XBEE_868) || (protocol==XBEE_900) )
    {
        delay(200);
        flush();
        printString("+++", uart);
        delay(2000);
        flush();
        printString("atdb\r\n", uart);
        delay(1000);
        error_AT = 2;
        while(serialAvailable(uart)>0)
        {
            ByteIN[i]=serialRead(uart);
            error = 0;
            i++;
            error_AT = 0;
            if(i>=sizeof(ByteIN)-1)
            {
                break;
            }
        }
        printString("atcn\r\n", uart);

        // in the case only one byte is read, compose a 2-byte hexadecimal
        if(i==2)
        {
            ByteIN[1]=ByteIN[0];
            ByteIN[0]=0x30;
        }
        ByteIN[i]='\0';
        i=0;
        valueRSSI[0]=Utils.str2hex(ByteIN);

    }

    return error;
}

/*
 Function: Get the Harware Version
 Returns: Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "hardVersion" variable the Hardware Version
*/
uint8_t WaspXBeeCore::getHardVersion()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[34])));//get_hard_version
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    if(!error)
    {
        hardVersion[0]=data[0];
        hardVersion[1]=data[1];
    }
    return error;
}

/*
 Function: Get the version of the firmware
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "softVersion" variable the firmware version
*/
uint8_t WaspXBeeCore::getSoftVersion()
{
    int8_t error=2;
    char buffer[20];

    error_AT=2;

	// get_soft_version
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[35])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    if(error==0)
    {
        softVersion[0]=data[0];
        softVersion[1]=data[1];
        softVersion[2]=data[2];
        softVersion[3]=data[3];

    }
    return error;
}


/*
 Function: Set the RSSI time
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the RP command. Stores in global "timeRSSI" variable the RSSI time
 Parameters:
   time: amount of time to do the pwm (0x00-0xFF)
*/
uint8_t WaspXBeeCore::setRSSItime(uint8_t time)
{
    int8_t error=2;
    char buffer[20];

    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[36])));//set_RSSI_time
    if(buffer==NULL) return 1;

    gen_data(buffer,time);
    gen_checksum(buffer);
    error=gen_send(buffer);
    if(!error)
    {
        timeRSSI=time;
    }
    return error;
}

/*
 Function: Get the RSSI time
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "timeRSSI" variable the RSSI time
*/
uint8_t WaspXBeeCore::getRSSItime()
{
    int8_t error=2;
    char buffer[20];

    error_AT=2;

    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[37])));//get_RSSI_time
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    if(!error)
    {
        timeRSSI=data[0];
    }
    return error;
}

/*
 Function:  Immediately applies new settings without exiting command mode
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the AC command
*/
uint8_t WaspXBeeCore::applyChanges()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// apply_changes
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[38])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    return error;
}


/*
 Function: Reset the XBee Firmware
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the FR command
*/
uint8_t WaspXBeeCore::reset()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// reset_xbee
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[39])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    return error;
}

/*
 Function: Set the parameteres to the factory defaults
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the RE command
*/
uint8_t WaspXBeeCore::resetDefaults()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// reset_defaults_xbee
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[40])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    return error;
}

/*
 Function: Configure options for sleep
 Returns: Integer that determines if there has been any error
   error=2 -->  The command has not been executed
   error=1 -->  There has been an error while executing the command
   error=0 -->  The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Change the SO command. Stores in global "sleepOptions" variable the options
 Parameters:
   soption: options for sleep (0x00-0xFF)
*/
uint8_t WaspXBeeCore::setSleepOptions(uint8_t soption)
{
    int8_t error=2;
    char buffer[20];

    if(( protocol == ZIGBEE )
    || ( protocol == DIGIMESH )
    || ( protocol == XBEE_900 )
    || ( protocol == XBEE_868 )
    || ( protocol == XBEE_868LP)
    || ( protocol == XBEE_900HP ) )
    {
        error_AT = 2;

		// set_sleep_options_xbee
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[41])));
        if(buffer==NULL) return 1;

        gen_data(buffer,soption);
        gen_checksum(buffer);
        error = gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(!error)
    {
        sleepOptions = soption;
    }
    return error;
}

/*
 Function: Reads the options for sleep
 Returns: Integer that determines if there has been any error
   error=2 -->  The command has not been executed
   error=1 -->  There has been an error while executing the command
   error=0 -->  The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Executes the SO command. Stores in global "sleepOptions" variable the options
*/
uint8_t WaspXBeeCore::getSleepOptions()
{
    int8_t error=2;
    char buffer[20];

	// get_sleep_options_xbee
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[42])));
    if(buffer==NULL) return 1;

    if(( protocol == ZIGBEE )
    || ( protocol == DIGIMESH )
    || ( protocol == XBEE_900 )
    || ( protocol == XBEE_868 )
    || ( protocol == XBEE_868LP)
    || ( protocol == XBEE_900HP ) )
    {
        error_AT = 2;
        gen_data(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }
    if(!error)
    {
        sleepOptions = data[0];
    }
    return error;
}


/*
 Function: Scans for brothers in the same channel and same PAN ID
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores given info (SH,SL,MY,RSSI,NI) in global array "scannedBrothers" variable
         Stores in global "totalScannedBrothers" the number of found brothers
*/
uint8_t WaspXBeeCore::scanNetwork()
{
    uint8_t error=2;
    char buffer[20];
    error_AT=2;

	// scan_network
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[43])));
    if(buffer==NULL) return 1;

    totalScannedBrothers=0;
    gen_data(buffer);
    error=gen_send(buffer);

    return error;
}



/*
 Function: It sets the time the energy scan will be performed
 Returns: Integer that determines if there has been any error
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Change the ED command. Stores in global "energyChannel" variable the
	energy in each channel. The actual scan time on each channel is measured as
	Time = [(2 ^ED) * 15.36] ms
 Parameters:
   duration: amount of time that the energy scan will be performed (0-6)
*/
uint8_t WaspXBeeCore::setDurationEnergyChannels(uint8_t duration)
{
    int8_t error=2;
    char buffer[20];

    if( (protocol==XBEE_802_15_4) )
    {
        error_AT=2;

		// set_duration_energy
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[44])));

        gen_data(buffer,duration);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else if( (protocol==ZIGBEE) )
    {
        error_AT=2;

        // set_duration_energy_ZB
        strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[45])));

        gen_data(buffer,duration);
        gen_checksum(buffer);
        error=gen_send(buffer);
    }
    else
    {
        error_AT=-1;
        error=-1;
    }

    if(error==0)
    {
        if(protocol==XBEE_802_15_4)
        {
            for( uint16_t i=0 ; i<data_length ; i++)
            {
                energyChannel[i] = data[i];
            }
        }
        if(protocol==ZIGBEE)
        {
            timeEnergyChannel=data[0];
        }
    }
    return error;
}



/*
 * Function: get destination address from XBee module
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 -->  The command has not been executed
 * 	error=1 -->  There has been an error while executing the command
 * 	error=0 -->  The command has been executed with no errors
 * 	error=-1 --> Forbidden command for this protocol
 *
 */
uint8_t WaspXBeeCore::getDestinationAddress(uint8_t* naD)
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// get_low_dest_address
    strcpy_P(buffer, (char*)pgm_read_word(&(table_CORE[46])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);

    if(!error)
    {
		if( protocol == XBEE_802_15_4)
		{
			naD[0]=data[2];
			naD[1]=data[3];
		}
		else if(( protocol == ZIGBEE )
				|| 	( protocol == DIGIMESH )
				||  ( protocol == XBEE_900 )
				||  ( protocol == XBEE_868)
				||  ( protocol == XBEE_868LP)
				||  ( protocol == XBEE_900HP)	 )
		{
			naD[0]=0x00;
			naD[1]=0x13;
			naD[2]=0xA2;
			naD[3]=0x00;
			naD[4]=data[0];
			naD[5]=data[1];
			naD[6]=data[2];
			naD[7]=data[3];

			// check for bad answer
			if( (naD[4] == 0x00)
			||	(naD[5] == 0x00)
			||	(naD[6] == 0xFF)
			||	(naD[7] == 0xFF))
			{
				return 1;
			}
		}
    }
    return error;

}




/*
 Function: Transparent function. The user introduces an AT command within a
 string and the function executes it without knowing its meaning

 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Parameters:
  atcommand : String to specify the AT command to execute
*/
uint8_t WaspXBeeCore::sendCommandAT(const char* atcommand)
{
    uint8_t AT[30];// {0x7E, 0x00, 0x00, 0x08, 0x52, 0x00, 0x00, 0x00};
    AT[0]=0x7E;
    AT[1]=0x00;
    AT[3]=0x08;
    AT[4]=0x52;
    int8_t error=2;
    int index = 0;
    uint8_t it2=0;
    uint8_t counter=0;
    uint8_t checksum=0;
    uint16_t length=0;

    // init flag
    error_AT=2;

    while( atcommand[it2]!='#' )
    {
        if( index>=2 )
        {
            if( atcommand[it2+1]!='#' )
            {
                AT[index+5]=Utils.converter(atcommand[2*(index-1)],atcommand[2*(index-1)+1]);
                it2+=2;
            }
            else
            {
                switch( atcommand[it2] )
                {
                    case '0':	AT[index+5]=0;
                    break;
                    case '1':	AT[index+5]=1;
                    break;
                    case '2':	AT[index+5]=2;
                    break;
                    case '3':	AT[index+5]=3;
                    break;
                    case '4':	AT[index+5]=4;
                    break;
                    case '5':	AT[index+5]=5;
                    break;
                    case '6':	AT[index+5]=6;
                    break;
                    case '7':	AT[index+5]=7;
                    break;
                    case '8':	AT[index+5]=8;
                    break;
                    case '9':	AT[index+5]=9;
                    break;
                    case 'A':	AT[index+5]='A';
                    break;
                    case 'B':	AT[index+5]='B';
                    break;
                    case 'C':	AT[index+5]='C';
                    break;
                    case 'D':	AT[index+5]='D';
                    break;
                    case 'E':	AT[index+5]='E';
                    break;
                    case 'F':	AT[index+5]='F';
                    break;
                }
                it2++;
            }
        }
        else
        {
            AT[index+5]=atcommand[index];
            it2++;
        }
        index++;
    }
    length = index;

    AT[2]=2+length;
    for(uint16_t i=3 ; i<(5+length) ; i++)
    {
        checksum=checksum+AT[i];
    }
    while( (checksum>255))
    {
        checksum=checksum-256;
    }
    checksum=255-checksum;
    AT[5+length]=checksum;
    while(counter<(6+length))
    {
		// print Byte through correspondent UART
		printByte(AT[counter], uart);
        counter++;
    }
    counter=0;
    clearCommand();
    command[5]=AT[5];
    command[6]=AT[6];
    data_length=0;
    error=parse_message(command);
    if(error==0)
    {
        if(data_length>0)
        {
            for(uint16_t i=0 ; i<data_length ; i++)
            {
                commandAT[i]=data[i];
            }
        }
        else
        {
            commandAT[0]=0x4F;
            commandAT[1]=0x4B;
        }
    }

    return error;
}

uint8_t WaspXBeeCore::ON()
{
	return ON(SOCKET0);
}

/*
 Function: Connect XBee, activating switch in Waspmote
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::ON(uint8_t uart_used)
{
    uint8_t error=2;

    // call initialization function
    init(uart_used);

    // select multiplexer
    if (uart == SOCKET0)
    {
		Utils.setMuxSocket0();
	}
    if (uart == SOCKET1)
    {
		Utils.setMuxSocket1();

		// update WaspRegister for SPI interferences in Waspv15
		WaspRegister &= ~(REG_XBEE_SOCKET0);
	}

    // begin serial communication
	beginSerial(XBEE_RATE, uart);

    // power on the socket
    PWR.powerSocket(uart, HIGH);

    //~ if (_boot_version >= 'G')
	//~ {
		//~ // update SPI flag
		//~ SPI.isSocket0 = true;
	//~ }

	// update Waspmote Register
	if(uart_used==SOCKET0)	WaspRegister |= REG_SOCKET0;
	if(uart_used==SOCKET1)	WaspRegister |= REG_SOCKET1;

    if( protocol == ZIGBEE) delay(500);
    else if( protocol == XBEE_868LP) delay(500);
    else if( protocol == XBEE_900HP) delay(500);
    else if( protocol == DIGIMESH) delay(500);
    else delay(270);
    error=0;
    XBee_ON=1;

    // clear input buffer before using the XBee
	flush();

	// wake up Xbee module in case Sleep Mode is activated
	if( uart==SOCKET0 )
    {
		pinMode(XBEE_SLEEP, OUTPUT);
		digitalWrite(XBEE_SLEEP,LOW);
    }
    else if( uart==SOCKET1 )
    {
		pinMode(DIGITAL7, OUTPUT);
    	digitalWrite(DIGITAL7,LOW);
    }

    delay(50);

    return error;
}


/*
 Function: disconnects XBee, switching it off and closing the UART
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::OFF()
{
    uint8_t error=2;

    // close UART
	closeSerial(uart);

	// unselect multiplexer
    if (uart == SOCKET0)	Utils.setMuxUSB();
    if (uart == SOCKET1)	Utils.muxOFF1();

    // switch module OFF
	PWR.powerSocket(uart, LOW);

	//~ if (_boot_version >= 'G')
	//~ {
		//~ // update SPI flag
		//~ SPI.isSocket0 = false;
	//~ }

	// update Waspmote Register
	if(uart == SOCKET0)	WaspRegister &= ~(REG_SOCKET0);
	if(uart == SOCKET1)	WaspRegister &= ~(REG_SOCKET1);

    error=0;
    XBee_ON=0;
    return error;
}



/*
 Function: Set XBee to sleep, asserting PIN 9
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::sleep()
{
    uint8_t error=2;
    if( uart==SOCKET0 )
    {
		// set sleep pin high in SOCKET0
		pinMode(XBEE_SLEEP, OUTPUT);
    	digitalWrite(XBEE_SLEEP,HIGH);
    }
    else if( uart==SOCKET1 )
    {
		// set sleep pin high in SOCKET1
		pinMode(DIGITAL7, OUTPUT);
    	digitalWrite(DIGITAL7,HIGH);
    }

    // close UART and Multiplexer
	closeSerial(uart);
	Utils.setMuxUSB();

    error=0;
    return error;
}

/*
 Function: Wake up XBee, de-asserting PIN 9
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::wake()
{
    uint8_t error=2;

    if( uart==SOCKET0 )
    {
		pinMode(XBEE_SLEEP, OUTPUT);
		digitalWrite(XBEE_SLEEP,LOW);
    }
    else if( uart==SOCKET1 )
    {
		pinMode(DIGITAL7, OUTPUT);
    	digitalWrite(DIGITAL7,LOW);
    }

	Utils.setMuxSocket0();
    beginSerial(XBEE_RATE, uart);

    delay(50);
    error=0;
    return error;
}


/*
 * Function: Send a packet from one XBee to another XBee in API mode
 *
 * Parameters:
 * 	'packet' : A struct of packetXBee type
 *
 * Returns: Integer that determines if there has been any error
 *	error=2 --> The command has not been executed
 *	error=1 --> There has been an error while executing the command
 *	error=0 --> The command has been executed with no errors
 *
 * --> DIGI's XBee Packet inner structure:
 *
 * StartDelimiter(1B) + Length(2B) +  Frame Data(variable) + Checksum(1B)
 *  ______________     ___________     __________________     __________
 * |              |   |     |     |   |                  |   |          |
 * |     0x7E     | + | MSB | LSB | + |    Frame Data    | + |  1 Byte  |
 * |______________|   |_____|_____|   |__________________|   |__________|
 *
 */
uint8_t WaspXBeeCore::sendXBee(struct packetXBee* packet)
{
    Utils.setMuxSocket0();
    uint16_t maxPayload=0;
    int8_t error=2;

	// set general counter to zero
    it=0;

	// set maximum payload depending on the
	// protocol, encryption mode, addressing mode
	switch (protocol)
	{
		case XBEE_802_15_4:
						if(encryptMode==0)
						{
							maxPayload=100;
						}
						else
						{
							if(packet->mode==BROADCAST)
							{
								maxPayload=95;
							}
							else
							{
								if(packet->address_type==_16B)
								{
									maxPayload=98;
								}
								else
								{
									maxPayload=94;
								}
							}
						}
						break;

		case ZIGBEE:	if(encryptMode==0)
						{
							if(packet->mode==BROADCAST)
							{
								maxPayload=92;
							}
							else
							{
								maxPayload=84;
							}
						}
						else
						{
							if(packet->mode==BROADCAST)
							{
								if(apsEncryption) maxPayload=70;
								else maxPayload=74;
							}
							else
							{
								if(apsEncryption) maxPayload=62;
								else maxPayload=66;
							}
						}
						break;

		case DIGIMESH: 	maxPayload=73;
						break;

		case XBEE_900:  if(encryptMode) maxPayload=80;
						else maxPayload=100;
						break;

		case XBEE_868:	maxPayload=100;
						break;

		case XBEE_900HP:maxPayload=0xFF;
						break;

		case XBEE_868LP:maxPayload=0xFF;
						break;

		default:		break;

	}

    // Check if fragmentation is necessary due to packet length
    // is greater than maximum payload
    if(packet->data_length > maxPayload)
    {
		// Truncation needed
        packet->data_length=maxPayload;
    }


	/// send the prepared packet using the virtual function sendXBeePriv
	error = sendXBeePriv(packet);

	return error;

}



/*
 Function: Treats any data from the XBee UART
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
int8_t WaspXBeeCore::treatData()
{
	int8_t error=2;
	uint8_t pos_aux=0;
	uint8_t pos_old=0;
	uint8_t pos_disor=0;
	uint8_t pos_max=0;
	uint8_t first_stop=1;
	uint8_t frameType;

	// initialize RX flag
	error_RX = 2;

	command[0]=0xEE;
	error=parse_message(command);

	pos_max=pos;
	pos_old=pos;
	pos_aux=pos;
	if(pos_aux>1) pos=1;

	if( !error_RX )
	{
		while(pos_aux>0)
		{
			// get frame type
			frameType=packet_finished[pos-1]->data[3];

			switch(frameType)
			{
				case NEW_FIRM_RECEIVED_FRAME:
					error=new_firmware_received();
					if(!error)
					{
						while(pos_max>0)
						{
							free(packet_finished[pos_max-1]);
							packet_finished[pos_max-1]=NULL;
							pos_max--;
							pos_old--;
						}
						pos_aux=1;
					}
					break;

				case NEW_FIRM_PACKET_FRAME:
					new_firmware_packets();
					if( !firm_info.paq_disordered )
					{
						free(packet_finished[pos-1]);
						packet_finished[pos-1]=NULL;
						pos_old--;
					}
					else if(firm_info.paq_disordered==1)
					{
						pos_disor=pos;
					}
					break;

				case NEW_FIRM_END_FRAME:
					new_firmware_end();
					while(pos_max>0)
					{
						free(packet_finished[pos_max-1]);
						packet_finished[pos_max-1]=NULL;
						pos_max--;
						pos_old--;
					}
					pos_aux=1;
					break;

				case UPLOAD_FIRM_FRAME:
					upload_firmware();
					pos_old--;
					break;


				case REQUEST_ID_FRAME:
					request_ID();
					free(packet_finished[pos-1]);
					packet_finished[pos-1]=NULL;
					pos_old--;
					break;

				case REQUEST_BOOT_FRAME:
					request_bootlist();
					free(packet_finished[pos-1]);
					packet_finished[pos-1]=NULL;
					pos_old--;
					break;

				case DELETE_FRAME:
					delete_firmware();
					free(packet_finished[pos-1]);
					packet_finished[pos-1]=NULL;
					pos_old--;
					break;

				case CHECK_NEW_PROG_FRAME:
					free(packet_finished[pos-1]);
					packet_finished[pos-1]=NULL;
					pos_old--;
					break;

				default:
					if( programming_ON )
					{
						free(packet_finished[pos-1]);
						packet_finished[pos-1]=NULL;
						pos_old--;
					}
					break;
			}
			// Handle disordered packets
			if(!firm_info.paq_disordered && !pos_disor)
			{
				pos_aux--;
				pos++;
			}
			else if(firm_info.paq_disordered==1)
			{
				pos++;
				pos_aux--;
			}
			else if(pos_disor==1)
			{
				if( pos_old <= 1)
				{
					pos=1;
					pos_aux=1;
					pos_disor=0;
				}
				else if( first_stop )
				{
					pos=pos_max;
					first_stop=0;
				}
				else pos--;

			}
		}
	}
	else
	{
		// Clear reception struct
		clearFinishArray();
		pos_old=0;

		// Flush input UART
		serialFlush(uart);
	}

	pos=pos_old;

	return error;
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											const char* data)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, MAC_TYPE);
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the origin identification type (using this function call, it only
 *    	can be used MAC_TYPE)
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											const char* data,
											uint8_t type	)
{
	// conversion from uint8_t* to char*
	char macDest[17];
	Utils.hex2str(address, macDest);

	return setDestinationParams(paq,macDest,data,type);
}





/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											const char* data	)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, MAC_TYPE);
}




/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the origin identification type: MAC_TYPE or MY_TYPE
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											const char* data,
											uint8_t type)
{
    uint8_t destination[8];
    uint8_t i=0;
    uint8_t j=0;
    char aux[2];

    // make sure the MAC address is defined with upper case letters
    strupr((char*)address);

    if( type==MAC_TYPE )
    {
		while(j<8)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}

		// set 64-b destination mac address
		paq->macDH[0] = destination[0];
		paq->macDH[1] = destination[1];
		paq->macDH[2] = destination[2];
		paq->macDH[3] = destination[3];
		paq->macDL[0] = destination[4];
		paq->macDL[1] = destination[5];
		paq->macDL[2] = destination[6];
		paq->macDL[3] = destination[7];

		paq->address_type=_64B;
	}
	if( type==MY_TYPE )
	{
		while(j<2)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}
		paq->naD[0] = destination[0];
		paq->naD[1] = destination[1];
		paq->address_type=_16B;
	}

    // set 'data_ind' global variable to zero in order to start filling the
    // data field from the beginning
    data_ind=0;


    // fill data field until the end of the string
    i=0;
    while( data[i] != '\0' )
    {
        paq->data[data_ind]=data[i];
        i++;
        data_ind++;

        // in the case MAX_DATA is reached, then data field is truncated
        if( data_ind>=MAX_DATA ) break;
    }

    // set data length with the actual counter value
    paq->data_length=data_ind;

    return 1;
}


/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											uint8_t* data,
											uint16_t length	)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, length, MAC_TYPE);
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the destination identifier type (MAC_TYPE or MY_TYPE )
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											uint8_t* data,
											uint16_t length,
											uint8_t type	)
{
	// conversion from uint8_t* to char*
	char macDest[17];
	Utils.hex2str(address, macDest);

	return setDestinationParams(paq, macDest, data, length, type);
}




/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											uint8_t* data,
											uint16_t length	)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, length, MAC_TYPE);
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the destination identifier type (MAC_TYPE or MY_TYPE)
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											uint8_t* data,
											uint16_t length,
											uint8_t type	)
{
	uint8_t destination[8];
    uint8_t i=0;
    uint8_t j=0;
    char aux[2];

    // make sure the MAC address is defined with upper case letters
    strupr((char*)address);

	if( type==MAC_TYPE )
	{
		while(j<8)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}

		// set 64-b destination mac address
		paq->macDH[0] = destination[0];
		paq->macDH[1] = destination[1];
		paq->macDH[2] = destination[2];
		paq->macDH[3] = destination[3];
		paq->macDL[0] = destination[4];
		paq->macDL[1] = destination[5];
		paq->macDL[2] = destination[6];
		paq->macDL[3] = destination[7];

		paq->address_type=_64B;
	}
	if( type==MY_TYPE )
	{
		while(j<2)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}
		paq->naD[0] = destination[0];
		paq->naD[1] = destination[1];
		paq->address_type=_16B;
	}

	// set 'data_ind' global variable to zero in order to start filling the
	// data field from the beginning
	data_ind=0;


    // fill data field until the end of the string
    for( uint16_t i=0 ; i < length ; i++ )
    {
        paq->data[data_ind]=data[i];
        data_ind++;

        // in the case MAX_DATA is reached, then data field is truncated
        if( data_ind>=MAX_DATA ) break;
    }

    // set data length with the actual counter value
    paq->data_length=data_ind;

    return 1;

}




/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											int data	)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, MAC_TYPE);
}


/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the origin identification type (using this function call, it only
 *    	can be used MAC_TYPE)
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											uint8_t* address,
											int data,
											uint8_t type)
{
	// conversion from uint8_t* to char*
	char macDest[17];
	Utils.hex2str(address, macDest);

	return setDestinationParams(paq,macDest,data,type);
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											int data	)
{
	// call setDestinationParams function using MAC_TYPE
	return setDestinationParams(paq, address, data, MAC_TYPE);
}



/* Function: Sets the destination address and data to 'paq' structure
 * Parameters:
 * 	'paq' is a packetXBee structure where some parameters should have been filled
 * 		before calling this function. After this call, this structure is filled
 * 		with the corresponding address and data
 *  'address' is the receiver MAC
 *  'data' is the data to send
 *  'type' is the destination identifier type (MAC_TYPE or MY_TYPE )
 *
 * Returns '1' on success
 */
int8_t WaspXBeeCore::setDestinationParams(	packetXBee* paq,
											const char* address,
											int data,
											uint8_t type	)
{

    uint8_t destination[8];
    uint8_t i=0;
    uint8_t j=0;
    char aux[2];
    char numb[10];

	if( type==MAC_TYPE )
	{
		while(j<8)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}

		// set 64-b destination mac address
		paq->macDH[0] = destination[0];
		paq->macDH[1] = destination[1];
		paq->macDH[2] = destination[2];
		paq->macDH[3] = destination[3];
		paq->macDL[0] = destination[4];
		paq->macDL[1] = destination[5];
		paq->macDL[2] = destination[6];
		paq->macDL[3] = destination[7];

		paq->address_type=_64B;
	}
	if( type==MY_TYPE )
	{
		while(j<2)
		{
			aux[i-j*2]=address[i];
			aux[(i-j*2)+1]=address[i+1];
			destination[j]=Utils.str2hex(aux);
			i+=2;
			j++;
		}
		paq->naD[0]=destination[0];
		paq->naD[1]=destination[1];
		paq->address_type=_16B;
	}

	// set 'data_ind' global variable to zero in order to start filling the
	// data field from the beginning
	data_ind=0;


    // fill data field making the data conversion from int to char array
    i=0;
    Utils.long2array(data,numb);
    while( numb[i]!='\0' )
    {
        paq->data[data_ind]=numb[i];
        data_ind++;
        i++;
        if( data_ind>=MAX_DATA ) break;
    }

    // set data length with the actual counter value
    paq->data_length=data_ind;

    return 1;
}



/*
 * Function: Treats and parses the read bytes wich are a message sent by a
 * remote XBee
 *
 * Parameters:
 * 	data :	this is the pointer to new packet received by the XBee module. It
 * 			might be a fragment or a packet itself
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 	error=-1 --> No more memory available
 *
 * 	'packet_finished' : is the attribute where a maximum of 5 packets are
 * 		created in order to contain all received information
 *
 * Values: Stores in global "packet_finished" array the received message
 *
 *
 * ====> 16-bit address frame type (ONLY XBEE-802.15.4)<=====
 * 'data' includes from 'Src Add' to 'checksum'
 *  __________________________________________________________________________
 * |      |           |           |         |      |     |         |          |
 * | 0x7E |   Length  | FrameType | Src Add | RSSI | Ops | RF Data | checksum |
 * |      | MSB | LSB |  (0x81)   |         |      |     |         |          |
 * |______|_____|_____|___________|_________|______|_____|_________|__________|
 *    0      1     2       3          4-5       6     7      8-n       n+1
 *
 *  ====> 64-bit address frame type <=====
 * 'data' includes from 'Src Add' to 'checksum'
 *  __________________________________________________________________________
 * |      |           |           |         |      |     |         |          |
 * | 0x7E |   Length  | FrameType | Src Add | RSSI | Ops | RF Data | checksum |
 * |      | MSB | LSB |  (0x81)   |         |      |     |         |          |
 * |______|_____|_____|___________|_________|______|_____|_________|__________|
 *    0      1     2       3          4-11     12     13     14-n       n+1
 *
 *
 * ====> Receive packet 0x90 format (ONLY XBEE-802.15.4)<=====
 * 'data' includes from 'Src Add' to 'checksum'
 *  _________________________________________________________________________________
 * |      |           |           |         |             |     |         |          |
 * | 0x7E |   Length  | FrameType | 64-bit  |   Reserved  | Ops | RF Data | checksum |
 * |      | MSB | LSB |  (0x90)   | Src Add | 0xFF | 0xFE |     |         |          |
 * |______|_____|_____|___________|_________|______|______|_____|_________|__________|
 *    0      1     2       3          4-11     12     13     14     15-n       n+1
 *
 *
 * ====> Explicit Rx Indicator 0x91 format <=====
 * 'data' includes from 'Src Add' to 'checksum'
 *  _______________________________________________________________________________________________________
 * |      |           |           |         |             |    |    |     |     |     |         |          |
 * | 0x7E |   Length  | FrameType | 64-bit  |   Reserved  | SD | DE | CID | PID | Opt | RF Data | checksum |
 * |      | MSB | LSB |  (0x90)   | Src Add | 0xFF | 0xFE |    |    |     |     |     |         |          |
 * |______|_____|_____|___________|_________|______|______|____|____|_____|_____|_____|_________|__________|
 *    0      1     2       3          4-11     12     13    14   15  16-17 18-19   20     21-n       n+1
 *
 *
*/
int8_t WaspXBeeCore::readXBee(uint8_t* data)
{
	uint8_t header=0;
    uint8_t finishIndex=0;

	#if DEBUG_XBEE > 1
    PRINTLN_XBEE(F("New packet"));
	#endif

	// increment "pos" packet counter
    pos++;

    // get next index to complete the following packet_finished
	finishIndex=getFinishIndex();

	// check if number of packets received is larger than maximum
	if( pos > MAX_FINISH_PACKETS )
	{
		switch( replacementPolicy )
		{
			case	XBEE_FIFO:	// recalculate index to put the new packet
								// based on a FIFO policy
								finishIndex=getIndexFIFO();
								break;
			case	XBEE_LIFO:	// recalculate index to put the new packet
								// based on a LIFO policy
								finishIndex=getIndexLIFO();
								break;
			case	XBEE_OUT:	// last received packet must be discarded
								pos--;
								return 2;
								break;
		}
	}

	// memory allocation for a new packet
	packet_finished[finishIndex] = (packetXBee*) calloc(1,sizeof(packetXBee));

	// if no available memory then exit with error
	if(packet_finished[finishIndex]==NULL)
	{
		return 1;
	}

    /**************************************************************************
    * Store packet fields in packet_finished structure depending on the RX
    * frame type. There are four possibilities:
    * 	_16B --> for 16-Bit address RX frames (only XBee-802.15.4 protocol)
    * 	_64B --> for 64-bit address RX frames (only XBee-802.15.4 protocol)
    * 	NORMAL_RX --> for normal RX frames (for all XBee protocols but 802.15.4)
    * 	EXPLICIT_RX --> for explicit RX indicator frames (for all XBee protocols but 802.15.4)
    **************************************************************************/
	switch(rxFrameType)
	{
		case _16B:
		////////////////////////////////////////////////////////////////////////
		// when a 16-bit address is used for XBee-802.15.4: (frame type=0x81)
		////////////////////////////////////////////////////////////////////////

			// store information in pendingFragments structure
			packet_finished[finishIndex]->address_typeS=_16B;
			packet_finished[finishIndex]->time=millis();

			// store source address
			packet_finished[finishIndex]->naS[0]=data[0];
			packet_finished[finishIndex]->naS[1]=data[1];

			// store RSSI
			packet_finished[finishIndex]->RSSI=data[2];
			packet_finished[finishIndex]->opt=data[3];

			// set BROADCAST mode if 'Options' indicate so
			// set UNICAST mode otherwise
			if( packet_finished[finishIndex]->opt==0x01 ||
				packet_finished[finishIndex]->opt==0x02 )
			{
				packet_finished[finishIndex]->mode=BROADCAST;
			}
			else
			{
				packet_finished[finishIndex]->mode=UNICAST;
			}

			// calculate cmdData header's length as the following length summatory:
			// Src Address (2B) + RSSI (1B) + Options (1B)
			header = 2+1+1;

			if( header > data_length ) data_length=header;

			// set the fragment length as DATA length
			// 'data_length' is cmdData length
			// 'header' is the header included in cmdData
			packet_finished[finishIndex]->data_length = data_length - header;


			// copy DATA field to packet fragment structure
			for( uint16_t j=0 ; j<packet_finished[finishIndex]->data_length ; j++ )
			{
				packet_finished[finishIndex]->data[j] = char(data[j+header]);
			}

			break;


		case _64B:
		////////////////////////////////////////////////////////////////////////
		// when a 64-bit address is used for XBee-802.15.4: (frame type=0x80)
		////////////////////////////////////////////////////////////////////////

			// store information in pendingFragments structure
			packet_finished[finishIndex]->address_typeS=_64B;
			packet_finished[finishIndex]->time=millis();

			// store High Source Address
			packet_finished[finishIndex]->macSH[0]=data[0];
			packet_finished[finishIndex]->macSH[1]=data[1];
			packet_finished[finishIndex]->macSH[2]=data[2];
			packet_finished[finishIndex]->macSH[3]=data[3];

			// store Low Source Address
			packet_finished[finishIndex]->macSL[0]=data[4];
			packet_finished[finishIndex]->macSL[1]=data[5];
			packet_finished[finishIndex]->macSL[2]=data[6];
			packet_finished[finishIndex]->macSL[3]=data[7];

			packet_finished[finishIndex]->RSSI = data[8];
			packet_finished[finishIndex]->opt = data[9];

			// Depending on the selected 'Options',
			// UNICAST or BROADCAST mode is chosen
			if( (packet_finished[finishIndex]->opt == 0x01) ||
				(packet_finished[finishIndex]->opt == 0x02) 	)
			{
				packet_finished[finishIndex]->mode=BROADCAST;
			}
			else
			{
				packet_finished[finishIndex]->mode=UNICAST;
			}

			// calculate cmdData header's length as the following length summatory:
			// Src Address (8B) + RSSI (1B) + Options (1B)
			header=8+1+1;

			if( header>data_length ) data_length=header;

			// set the packet length as DATA length
			// 'data_length' is cmdData length
			// 'header' is the header included in cmdData
			packet_finished[finishIndex]->data_length = data_length - header;

			// copy DATA field to packet fragment structure
			for( uint16_t j=0 ; j<packet_finished[finishIndex]->data_length ; j++ )
			{
				packet_finished[finishIndex]->data[j] = char(data[j+header]);
			}

			break;


		case NORMAL_RX:
		////////////////////////////////////////////////////////////////////////
		// when a normal received packet which Frame Type is: 0x90 (NORMAL_RX)
		////////////////////////////////////////////////////////////////////////

			// store timeStamp
			packet_finished[finishIndex]->time=millis();

			// store High MAC address from source
			packet_finished[finishIndex]->macSH[0] = data[0];
			packet_finished[finishIndex]->macSH[1] = data[1];
			packet_finished[finishIndex]->macSH[2] = data[2];
			packet_finished[finishIndex]->macSH[3] = data[3];

			// store Low MAC address from source
			packet_finished[finishIndex]->macSL[0] = data[4];
			packet_finished[finishIndex]->macSL[1] = data[5];
			packet_finished[finishIndex]->macSL[2] = data[6];
			packet_finished[finishIndex]->macSL[3] = data[7];

			// store network address from source
			packet_finished[finishIndex]->naS[0] = data[8];
			packet_finished[finishIndex]->naS[1] = data[9];

			// set UNICAST mode in packet
			packet_finished[finishIndex]->opt = data[10];

			// set BROADCAST mode if 'Options' indicate so
			if( (packet_finished[finishIndex]->opt & 0x0F) == 0x02 )
			{
				packet_finished[finishIndex]->mode = BROADCAST;
			}
			else
			{
				packet_finished[finishIndex]->mode=UNICAST;
			}

			// calculate cmdData header's length as the following length summatory:
			// Src_Add (8B) + Reserved(2B) + Options(1B)
			header=8+2+1;

			if( header>data_length ) data_length=header;

			// set the fragment length as DATA length
			// 'data_length' is cmdData length
			// 'header' is the header included in cmdData
			packet_finished[finishIndex]->data_length=data_length-header;

			// copy DATA field to packet fragment structure
			for( uint16_t j=0 ; j < packet_finished[finishIndex]->data_length ; j++ )
			{
				packet_finished[finishIndex]->data[j] = char(data[j+header]);
			}

			// no RSSI information in XBee packets
			packet_finished[finishIndex]->RSSI=0;

			break;



		case EXPLICIT_RX:
		////////////////////////////////////////////////////////////////////////
		// when an explicit RX packet which Frame Type is: 0x91 (EXPLICIT_RX)
		////////////////////////////////////////////////////////////////////////

			// store timeStamp
			packet_finished[finishIndex]->time = millis();

			// store High MAC address from source
			packet_finished[finishIndex]->macSH[0]=data[0];
			packet_finished[finishIndex]->macSH[1]=data[1];
			packet_finished[finishIndex]->macSH[2]=data[2];
			packet_finished[finishIndex]->macSH[3]=data[3];

			// store Low MAC address from source
			packet_finished[finishIndex]->macSL[0]=data[4];
			packet_finished[finishIndex]->macSL[1]=data[5];
			packet_finished[finishIndex]->macSL[2]=data[6];
			packet_finished[finishIndex]->macSL[3]=data[7];

			// store network address from source
			packet_finished[finishIndex]->naS[0]=data[8];
			packet_finished[finishIndex]->naS[1]=data[9];

			// store cluster information
			packet_finished[finishIndex]->mode=CLUSTER;
			packet_finished[finishIndex]->SD=data[10];
			packet_finished[finishIndex]->DE=data[11];

			// store Cluster ID
			packet_finished[finishIndex]->CID[0]=data[12];
			packet_finished[finishIndex]->CID[1]=data[13];

			// Store Profile ID
			packet_finished[finishIndex]->PID[0]=data[14];
			packet_finished[finishIndex]->PID[1]=data[15];

			// Store Options
			packet_finished[finishIndex]->opt = data[16];

			// set BROADCAST mode if 'Options' indicate so
			if( (packet_finished[finishIndex]->opt & 0x0F) == 0x02)
			{
				packet_finished[finishIndex]->mode=BROADCAST;
			}

			// calculate cmdData header's length as the following length summatory:
			// Src Address(8B) + Reserved(2B) + SE(1B) + DE(1B) + CID(2B) + PID(2B) + Opts(1B)
			header = 8+2+1+1+2+2+1;

			if( header>data_length ) data_length=header;

			// set the fragment length as DATA length
			// 'data_length' is cmdData length
			// 'header' is the header included in cmdData
			packet_finished[finishIndex]->data_length = data_length-header;

			// copy DATA field to packet fragment structure
			for( uint16_t j=0 ; j < packet_finished[finishIndex]->data_length ; j++ )
			{
				packet_finished[finishIndex]->data[j] = char(data[j+header]);
			}
			break;

			// no RSSI information in XBee packets
			packet_finished[finishIndex]->RSSI=0;

		default:
			break;

	}


    return 0;
}





/*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 	param : The param to set
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void WaspXBeeCore::gen_data(const char* data, uint8_t param)
{
    uint8_t inc=0;
    uint8_t inc2=0;

    clearCommand();

	// get length
    inc=strlen(data);

    // divide by 2 because each byte is
    // represented by two hexadecimals
    inc/=2;

    while(inc2<inc)
    {
        command[inc2]=Utils.converter(data[2*inc2],data[2*inc2+1]);
        inc2++;
    }

    command[inc-2]=param;
}


/*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void WaspXBeeCore::gen_data(const char* data)
{
    uint8_t inc=0;
    uint8_t inc2=0;

    clearCommand();

	// get length
    inc=strlen(data);

    // divide by 2 because each byte is
    // represented by two hexadecimals
    inc/=2;

    while(inc2<inc){
        command[inc2]=Utils.converter(data[2*inc2],data[2*inc2+1]);
        inc2++;
    }
}


/*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 	param1 : The param to set
 	param2 : The param to set
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void WaspXBeeCore::gen_data(const char* data, uint8_t param1, uint8_t param2)
{
    uint8_t inc=0;
    uint8_t inc2=0;

    clearCommand();

	// get length
    inc=strlen(data);

    // divide by 2 because each byte is
    // represented by two hexadecimals
    inc/=2;

    while(inc2<inc){
        command[inc2]=Utils.converter(data[2*inc2],data[2*inc2+1]);
        inc2++;
    }

    command[inc-3]=param1;
    command[inc-2]=param2;
}


/*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 	param : The param to set
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void WaspXBeeCore::gen_data(const char* data, uint8_t* param)
{
    uint8_t inc=0;
    uint8_t inc2=0;

    clearCommand();

	// get length
    inc=strlen(data);

    // divide by 2 because each byte is
    // represented by two hexadecimals
    inc/=2;

    while(inc2<inc){
        command[inc2]=Utils.converter(data[2*inc2],data[2*inc2+1]);
        inc2++;
    }

    if(inc==24)
    {
        for( int i=0 ; i<16 ; i++)
        {
            command[inc-17+i]=param[i];
        }
    }
    else if(inc==16)
    {
        for( int i=0 ; i<8 ; i++)
        {
            command[inc-9+i]=param[i];
        }
    }
    else if(inc==12)
    {
        for(int i=0 ; i<4 ; i++)
        {
            command[inc-5+i]=param[i];
        }
    }
    else if(inc==11)
    {
        for(int i=0 ; i<3 ; i++)
        {
            command[inc-4+i]=param[i];
        }
    }
    else if(inc==10)
    {
        for(int i=0 ; i<2 ; i++)
        {
            command[inc-3+i]=param[i];
        }
    }
    else command[inc-2]=param[0];
}


/*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 	param : The param to set
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void WaspXBeeCore::gen_data(const char* data, const char* param)
{
    gen_data(data,(uint8_t*) param);
}


/*
 * Function: Generates the checksum API frame to send to the XBee module
 *
 * Parameters:
 * 	data : The string that contains part of the API frame
 * Returns: the calculated cheksum
 * Values: Stores in 'command' variable the checksum API frame to send to the
 * XBee module
*/
uint8_t WaspXBeeCore::gen_checksum(const char* data)
{
    uint8_t inc=0;
    uint8_t checksum=0;

	// get length
    inc=strlen(data);

    // divide by 2 because each byte is
    // represented by two hexadecimals
    inc/=2;

    for(it=3;it<inc;it++)
    {
        checksum=checksum+command[it];
    }
    while( (checksum>255))
    {
        checksum=checksum-256;
    }
    checksum=255-checksum;
    command[inc-1]=checksum;

    return checksum;
}


/*
 Function: Sends the API frame stored in 'command' variable to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::gen_send(const char* data)
{
    int8_t error_int=2;
    uint8_t TX[100];
	int length=0;

	// generate frame with possible escaped characters
	gen_escaped_frame(TX, command, &length);

	#if DEBUG_XBEE > 1
	PRINT_XBEE(F("TX:"));
	for(int i = 0; i < length; i++)
	{
		USB.printHex(TX[i]);
	}
	USB.println();
	#endif

	serialFlush(uart);

   	// switch MUX in case SOCKET1 is used
	if( uart==SOCKET1 )
	{
		Utils.setMuxSocket1();
	}

	for (int i = 0; i < length; i++)
	{
		printByte(TX[i], uart);
	}

    error_int = parse_message(command);

    return error_int;
}


/*
 * Function: Generates the RF Data field for a TX frame
 *
 * This function is used to generate the XBee data payload
 *
 * Parameters:
 * 	_packet : the packetXBee structure where the data to send is stored
 * 	TX_array : the array where the API frame is stored
 * 	start_pos : starting position in API frame
 *
 * Returns: Nothing
*/
void WaspXBeeCore::genDataPayload(	struct packetXBee* _packet,
									uint8_t* TX_array,
									uint8_t start_pos	)
{

	// set data field
	for( uint16_t j=0 ; j<_packet->data_length ; j++)
	{
		TX_array[start_pos+j]=uint8_t(_packet->data[j]);
	}

}


/*
 * Function: Generates the escaped API frame when a TX is done
 *
 * Parameters:
 * 	_packet : the packetXBee structure where the data to send is stored
 * 	TX_array : the array where the API frame is stored
 * 	protect : specifies the number of chars that had been escaped
 * 	type : specifies the type of send
 *
 * Returns: Nothing
*/
void WaspXBeeCore::gen_frame_ap2(	struct packetXBee* _packet,
									uint8_t* TX_array,
									uint8_t &protect,
									uint8_t type	)
{
	// define variables
    uint16_t index = 1;
    bool final = false;
    uint16_t aux = 0;
    uint16_t aux2 = 0;

	// Enter while loop until all bytes are done escaping if necessary
    while( index < ( _packet->data_length + type + protect) )
    {
        if( ( TX_array[index] == 0x11)
		||	( TX_array[index] == 0x13)
		||	( TX_array[index] == 0x7E)
		||	( TX_array[index] == 0x7D) )
        {
            TX_array[index] = TX_array[index] xor 0x20;
            protect++;
            aux = TX_array[index];
            TX_array[index] = 0x7D;
            uint16_t k = index - 1;

            // after including the escpaing indicator: 0x7D
            // include the escaped value and copy the rest of the buffer
            while( final == false )
            {
                aux2 = TX_array[k+2];
                TX_array[k+2] = aux;
                if( ( k + 3 ) >= ( _packet->data_length + type + protect ) )
                {
                    final = true;
                    break;
                }
                aux = TX_array[k+3];
                TX_array[k+3] = aux2;
                if( ((k+4)>=(_packet->data_length+type+protect)) )
                {
                    final = true;
                    break;
                }
                k++;
                k++;
            }
            final = false;
        }
        index++;
    }
}


/*
 * Function: Parses the answer received by the XBee module, calling the
 * appropriate function
 *
 * Parameters:
 * 	frame : an array that contains the API frame that is expected to receive
 * 			answer from if it is an AT command
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
int8_t WaspXBeeCore::parse_message(uint8_t* frame)
{
    uint8_t memory[MAX_PARSE];
    uint16_t i=0;
    uint8_t num_mes=0;
    uint8_t num_esc=0;
    uint16_t num_data=0;
    uint16_t length_mes=0;
    uint16_t length_prev=0;
    int8_t error=2;
    unsigned long interval=50;
    unsigned long intervalMAX=40000;
    uint8_t good_frame=0;
    uint8_t maxFrame=30;

	// If a frame was truncated before, we set the first byte as 0x7E
	// and we add a new packet to 'num_mes' counter
    if( frameNext )
    {
        frameNext=0;
        memory[0]=0x7E;
        i=1;
        num_mes=1;
    }

    // If a RX we reduce the interval
    if( frame[0]==0xEE )
    {
        interval=5;
        maxFrame=109;
    }

    // Check if a ED is performed
    if( frame[5]==0x45 &&
		frame[6]==0x44 &&
		protocol==XBEE_802_15_4 )
	{
		interval = 3000 + (uint32_t)(pow(2,frame[7]))*16*10;
	}

    // Check if a DN is performed
    if( frame[5]==0x44 && frame[6]==0x4E )
    {
		interval=1000;
	}

    // Check if a ND is performed
    if( frame[5]==0x4E && frame[6]==0x44 )
    {
        interval=20000;
        if(protocol==DIGIMESH) interval=40000;
        else if( (protocol==XBEE_900) || (protocol==XBEE_868) || ( protocol == XBEE_868LP) )
        {
            interval=14000;
        }
    }

    // Check if a DN is performed
    if( frame[5]==0x44 && frame[6]==0x42 )
    {
		interval=500;
    }
	
    // Check if a WR is performed
    if( frame[5]==0x57 && frame[6]==0x52 )
    {
		interval=150;
    }

    // get execution time instant
    uint8_t timeout1=0;
    uint8_t timeout2=0;
    unsigned long previous=millis();
    unsigned long previous2=millis();

	////////////////////////////////////////////////////////////////////////////
    // Read data from XBee module when any condition is broken
    // 'timeout1' limits the maximum period of time between each read byte
    // 'timeout2' limits the maximum time to read all incoming data
    // 'MAX_PARSE' determines the maximum number of bytes to be received
    ////////////////////////////////////////////////////////////////////////////
    while( !timeout1 && !timeout2 	&&	i < MAX_PARSE	&& 	!frameNext 	)
    {
		// check if there are available data
		if(serialAvailable(uart))
		{
			// read Byte from correspondent UART
			memory[i]=serialRead(uart);
			i++;

			// check if a new frame Start Delimiter is read
			if(memory[i-1]==0x7E)
			{
				// if there is no memory available for a whole new packet then
				// we escape and select frameNext=1 in order to get it the
				// next time we read from XBee
				if( (MAX_PARSE-i) < maxFrame )
				{
					frameNext=1;
				}
				else
				{
					// increment the number of received messages
					num_mes++;
				}
			}
			previous=millis();
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous=millis();

		//avoid millis overflow problem
        if( millis() < previous2 ) previous2=millis();


        // check timeout1
        if(millis()-previous > interval)
        {
			//timeout
			timeout1=1;
		}

        // check timeout2
        if(millis()-previous2 > intervalMAX)
        {
			//timeout
			timeout2=1;
		}
    }

	// Store number of received bytes in "num_data"
    num_data=i;
    i=1;

	#if DEBUG_XBEE > 1
	PRINT_XBEE(F("RX:"));
    for(uint16_t i = 0; i < num_data ; i++)
	{
		USB.printHex(memory[i]);
	}
	USB.println();
	#endif

	// If some corrupted frame has appeared we jump it
    if( memory[0]!=0x7E )
    {
		// jump until a new frame start delimiter is found
		while( memory[i] != 0x7E &&  i < num_data )
        {
			i++;
		}
	}
	else
	{
		// reset index to starting byte
		i=0;
	}

	// initialize the starting pointer of a valid frame (0x7E)
	length_prev = i;

	// increment index to the byte that follows up the start delimiter
	i++;

	// if no frame has been received properly then return error
	if( i > num_data)
	{
		return 1;
	}

	////////////////////////////////////////////////////////////////////////////
	// Parse the received messages from the XBee module
	// while there are stored messages to be parsed
	////////////////////////////////////////////////////////////////////////////
    while( num_mes>0 )
    {
		// get length of the packet until another start delimiter
		// is found or the end of read bytes is reached
        while( memory[i]!=0x7E && i<num_data )
		{
			i++;
		}
        length_mes=i-length_prev;

		// If any byte has been escaped, it must be converted before parsing it
		// So first count number of escaped bytes and then make conversion
        for( it=0; it < length_mes ; it++ )
        {
            if( memory[it+length_prev]==0x7D ) num_esc++;
        }

        // if there are escaped bytes, make conversion
        if( num_esc )
        {
			des_esc(memory,length_mes,i-length_mes);
		}

		/**********************************************************************
		 *  Call parsing function depending on the Frame Type
		 *  _______________________________________________
		 * |      |     |     |    		   |			   |
		 * | 0x7E | MSB | LSB | Frame Type |    ......     |
		 * |______|_____|_____|____________|_______________|
		 * 	  0	     1     2        3          variable
		 **********************************************************************/
        switch( memory[(i-length_mes)+3] )
        {
            case 0x88 :	// AT Command Response
						error=atCommandResponse(memory,frame,length_mes-num_esc+length_prev,i-length_mes);
						error_AT=error;
						break;

            case 0x8A :	// Modem Status
						error=modemStatusResponse(memory,length_mes-num_esc+length_prev,i-length_mes);
						break;

            case 0x80 :	// XBee802 - RX (Receive) Packet: 64-bit Address
            case 0x81 :	// XBee802 - RX (Receive) Packet: 16-bit Address
            case 0x90 :	// XBee Receive Packet (AO=0)
            case 0x91 :	// XBee Explicit Rx Indicator (AO=1)
						error = rxData(	memory,	length_mes-num_esc+length_prev,	i-length_mes);
						error_RX = error;
						break;

            default   :	break;
        }

		// decrement number of pending packets to be treated
        num_mes--;

        // update previous index in input buffer in order to carry on with the
        // following message stored in 'memory'
        length_prev=i;
        i++;
        num_esc=0;

        // if the message has been parsed successfully,
        // then increment the good_frame counter
        if(!error)
        {
			good_frame++;
		}
    }

	// if there is any well parsed message, then return 'success'
    if(good_frame)
    {
		return 0;
	}
    else
    {
		return error;
	}
}


/*
 Function: Generates the correct API frame from an escaped one
 Parameters:
 	data_in : The string that contains the escaped API frame
 	end : the end of the frame
 	start : the start of the frame
 Returns: Nothing
*/
void WaspXBeeCore::des_esc(uint8_t* data_in, uint16_t end, uint16_t start)
{
    uint16_t i=0;
    uint16_t aux=0;

    while( i<end )
    {
        while( data_in[start+i]!=0x7D && i<end ) i++;
        if( i<end )
        {
            aux=i+1;
            switch( data_in[start+i+1] )
            {
                case 0x31 : 	data_in[start+i]=0x11;
                break;
                case 0x33 : 	data_in[start+i]=0x13;
                break;
                case 0x5E : 	data_in[start+i]=0x7E;
                break;
                case 0x5D : 	data_in[start+i]=0x7D;
                break;
            }
            i++;
            end--;
            while( i<(end) ){
                data_in[start+i]=data_in[start+i+1];
                i++;
            }
            i=aux;
        }
    }
}


/*
 Function: Parses the AT command answer received by the XBee module
 Parameters:
 	data_in : the answer received by the module
 	frame : an array that contains the API frame that is expected to receive
			answer from if it is an AT command
 	end : the end of the frame
 	start : the start of the frame
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::atCommandResponse(	uint8_t* 	data_in,
											uint8_t* 	frame,
											uint16_t 	end,
											uint16_t 	start	)
{
	// Check the checksum
    if(checkChecksum(data_in,end,start))
    {
		return 1;
	}

	// Check the AT Command Response is from the command expected
    if( data_in[start+5]!=frame[5] || data_in[start+6]!=frame[6] )
    {
		return 1;
	}

	// Check if there is data in the AT Command Response frame
    if( (end-start)==9 )
    {
        if( data_in[start+7]==0 )
        {
			return 0;
		}
        else
        {
			return 1;
		}
    }

	// check AT command response result
    if( data_in[start+7]!=0 )
    {
		// FIXME: Digimesh/868/900 typo
		if( (protocol == DIGIMESH ||
			 protocol == XBEE_900 ||
			 protocol == XBEE_868 ||
			 protocol == XBEE_868LP ||
			 protocol == XBEE_900HP	) && data_in[start+7]==0x40 )
		{
			// do nothing. it is a valid response because these protocols
			// answer command_status = 0x40 when doing a Discovery
			// Node (DN). This should be fixed in the future
		}
		else
		{
			return 1;
		}
	}

	// Store the data in the response frame
    for(it=0;it<(end-start-9);it++)
    {
        data[it]=data_in[8+it+start];
    }

	// Check if a ND is performed
    data_length=end-start-9;
    if( frame[5]==0x4E && frame[6]==0x44 )
    {
        if( data_length>1 ) totalScannedBrothers++;
        treatScan();
    }

    return 0;
}


/*
 Function: Parses the Modem Status message received by the XBee module
 Parameters:
 	data_in : the answer received by the module
 	end : the end of the frame
 	start : the start of the frame
 Returns: Integer that determines if there has been any error
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::modemStatusResponse(uint8_t* data_in, uint16_t end, uint16_t start)
{
	// Check the checksum
    if(checkChecksum(data_in,end,start)) return 1;

    modem_status=data_in[start+4];
    return 0;
}


/*
 * Function: Parses the TX Status message received by the XBee module
 *
 * Parameters:
 * 	data_in : the answer received by the module
 * 	end : the end of the frame
 * 	start : the start of the frame
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::txStatusResponse()
{
	// create reception buffer
	uint8_t ByteIN[MAX_PARSE];
    unsigned long previous=millis();

     // set number of bytes that TX Status frame (0x89) has
    uint16_t numberBytes=7;
    uint8_t end=0;
    uint16_t counter3=0;
    uint8_t undesired=0;
    uint8_t status=0;
    uint16_t num_TX=0;
    uint8_t num_esc=0;
    uint16_t interval=5000;
    uint8_t num_mes=0;
    uint16_t i=1;
    uint16_t length_mes=0;
    uint16_t length_prev=0;
    uint8_t maxFrame=110;

    error_TX=2;

	// If a frame was truncated before, we set the first byte as 0x7E
	// and we add a new packet to 'num_mes' counter
    if( frameNext )
    {
        ByteIN[0]=0x7E;
        counter3=1;
        num_mes=1;
        frameNext=0;
    }

	// Read data from XBee while data is available
    while( end==0 && !frameNext )
    {
		// check available data
		if(serialAvailable(uart)>0)
        {
			// read byte from correspondent uart
           	ByteIN[counter3]=serialRead(uart);
           	counter3++;
           	previous=millis();

           	// check if a new frame is received
           	if(ByteIN[counter3-1]==0x7E)
			{
				// if there is no memory available for a whole new packet
				// then we escape and select frameNext=1 in order to get it
				// the next time we read from XBee
           		if( (MAX_PARSE-counter3) < maxFrame )
           		{
					frameNext=1;
				}
                else num_mes++;
            }

            // If some corrupted frame has appeared, it is discarded,
            // counter3 is set to zero again
            if( (counter3==1) && (ByteIN[counter3-1]!=0x7E) )
            {
				counter3=0;
			}

			// if counter3 reaches the maximum data to parse, then finish
            if( counter3>=MAX_PARSE )
            {
				end=1;
			}

			// Discard any non-TX status frame which are determined by a frame
			// type which may be 0x89(TX Status) or 0x8A(Modem Status)
            if( (counter3 == (4 + (uint16_t)status*6 + undesired))
				&& (undesired != 1)  )
            {
                if( (ByteIN[counter3-1]!= 0x89) && (ByteIN[counter3-1]!=0x8A) )
				{
					// increment undesired counter
	                undesired=1;

	                // sum 3 new bytes corresponding to
	                // start delimiter (1Byte) + length (2Bytes)
                    numberBytes+=3;
               	}
            }

            // if undesired counter is active, increment 'numberBytes'
            if( undesired == 1 )
            {
				numberBytes++;
			}

            // If a escape character (0x7D) is found increment 'numberBytes'
	        if( (ByteIN[counter3-1]==0x7D) && (!undesired) )
        	{
        	    numberBytes++;
        	}

        	/* If a modem status frame (0x8A)
             *  ____________________________________________________
             * |      |     |     |            |         |          |
             * | 0x7E | MSB | LSB | Frame Type | cmdData | checksum |
             * |______|_____|_____|____________|_________|__________|
             *    0      1     2        3           4         5
             */
        	if( (ByteIN[counter3-1] == 0x8A) && (counter3 == (4+(uint16_t)status*6)) )
        	{
				// increment in 6Bytes 'numberBytes'
        	    numberBytes+=6;

        	    // increment 'status' in order to add a new 'modem status frame'
        	    status++;
        	}

        	// If a new frame is read after reading any undesired frame,
        	// decrement 'numberBytes' and set undesired
        	if( (ByteIN[counter3-1] == 0x7E) && (undesired == 1) )
        	{
        	   	numberBytes--;
        	    undesired=numberBytes-7;
        	}

        	// if 'counter3' is the same as 'numberBytes' we finish
        	// This means that TX status has been found
        	if(counter3 == numberBytes)
        	{
				end=1;
        	}
        }

        // avoid millis overflow problem
        if( millis() < previous ) previous=millis();

        // check if time is out
        if( (millis()-previous) > interval )
        {
            end=1;
            serialFlush(uart);
        }
    }

    // Store number of read bytes
    num_TX=counter3;
    counter3=0;

	#if DEBUG_XBEE > 0
	PRINT_XBEE(F("RX:"));
    for(uint16_t i = 0; i < num_TX ; i++)
	{
		USB.printHex(ByteIN[i]);
	}
	USB.println();
	#endif

    // If some corrupted frame has appeared we jump it
    if( ByteIN[0]!=0x7E )
    {
		// jump until a new frame start delimiter is found
		while( ByteIN[i]!=0x7E && i<num_TX )
        {
			i++;
		}
	}

    // Parse the received messages from the XBee
    while( num_mes>0 )
    {
		// get length of the packet until another start delimiter
		// is found or the end of read bytes is reached
        while( ByteIN[i]!=0x7E && i<num_TX )
		{
			i++;
		}
        length_mes=i-length_prev;

		// If any byte has been escaped, it must be converted before parsing it
		// So first count number of escaped bytes and then make conversion
		for( it=0; it < length_mes ; it++)
        {
            if( ByteIN[it+length_prev]==0x7D ) num_esc++;
        }

        // if there are escaped bytes, make conversion
        if( num_esc )
        {
			des_esc(ByteIN,length_mes,i-length_mes);
		}

		/* Call parsing function depending on the Frame Type
		 *  _______________________________________________
		 * |      |     |     |    		   |			   |
		 * | 0x7E | MSB | LSB | Frame Type |    ......     |
		 * |______|_____|_____|____________|_______________|
		 * 	  0	     1     2        3          variable
		 */
        switch( ByteIN[(i-length_mes)+3] )
        {
            case 0x8A :	//Modem Status
						modemStatusResponse(ByteIN,length_mes-num_esc+length_prev,i-length_mes);
						break;

            case 0x80 :	// XBee_802 - RX (Receive) Packet: 64-bit Address
            case 0x81 :	// XBee_802 - RX (Receive) Packet: 16-bit Address
						error_RX=rxData(ByteIN,length_mes-num_esc+length_prev,i-length_mes);
						break;

            case 0x89 :	// TX (Transmit) Status
						delivery_status=ByteIN[i-length_mes+5];
						if( delivery_status == 0 )
						{
							error_TX=0;
						}
						else
						{
							error_TX=1;
						}
						break;

            default   :	break;
        }

		// decrement number of pending packets to be treated
        num_mes--;

        // update previous index in input buffer in order to carry on with the
        // following message stored in 'memory'
        length_prev=i;
        i++;
        num_esc=0;

    }

    return error_TX;
}

/*
 * Function: Parses the ZB TX Status message received by the XBee module
 *
 * Parameters:
 * 	data_in : the answer received by the module
 * 	end : the end of the frame
 * 	start : the start of the frame
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::txZBStatusResponse()
{
	// create reception buffer
	uint8_t ByteIN[MAX_PARSE];
    unsigned long previous=millis();

    // set number of bytes that TX Status frame (0x8B) has
    uint16_t numberBytes=11;
    uint8_t end=0;
    uint16_t counter3=0;
    uint8_t undesired=0;
    uint8_t status=0;
    uint16_t num_TX=0;
    uint8_t num_esc=0;
    uint16_t interval=5000;
    uint8_t num_mes=0;
    uint16_t i=1;
    uint16_t length_mes=0;
    uint16_t length_prev=0;
    uint8_t maxFrame=110;

    error_TX=2;

    memset(ByteIN, 0x00, sizeof(ByteIN));

	// If a frame was truncated before, we set the first byte as 0x7E
	// and we add a new packet to 'num_mes' counter
    if( frameNext )
    {
        ByteIN[0]=0x7E;
        counter3=1;
        num_mes=1;
        frameNext=0;
    }

	// Read data from XBee while the following conditions are true:
	// - TX status is not received
	// - The maximum number of bytes are not received
	// - There is enough memory to store a whole new packet when a start
	//	 delimeter (0x7E) is received
	// - Timeout is not exceeded
    while( end==0 && !frameNext )
    {
		// check available data
		if( serialAvailable(uart)>0 )
       	{
			// read byte from correspondent uart
       		ByteIN[counter3] = serialRead(uart);
            counter3++;
            previous=millis();

            // check if a new frame is received
            if(ByteIN[counter3-1]==0x7E)
			{
				// if there is no memory available for a whole new packet
				// then we escape and select frameNext=1 in order to get it
				// the next time we read from XBee
           		if( (MAX_PARSE-counter3) < maxFrame )
           		{
					frameNext=1;
				}
                else num_mes++;
            }

            // If some corrupted frame has appeared, it is discarded,
            // counter3 is set to zero again
            if( (counter3==1) && (ByteIN[counter3-1]!=0x7E) )
            {
				counter3=0;
			}

			// if counter3 reaches the maximum data to parse, then finish
           	if( counter3>=MAX_PARSE )
           	{
				end=1;
			}

			// Discard any non-TX status frame which are determined by a frame
			// type which may be 0x8B(TX Status) or 0x8A(Modem Status)
           	if( (counter3==4+(uint16_t)status*6+undesired) && (undesired!=1) )
            {
            	if( (ByteIN[counter3-1]!= 0x8B) && (ByteIN[counter3-1]!=0x8A) )
				{
					// increment undesired counter
                	undesired=1;

                	// sum 3 new bytes corresponding to
	                // start delimiter (1Byte) + length (2Bytes)
                	numberBytes+=3;
                }
            }

            // if undesired counter is active, increment 'numberBytes'
            if( undesired==1 )
            {
				numberBytes++;
			}

            // If a escape character (0x7D) is found increment 'numberBytes'
            if( (ByteIN[counter3-1]==0x7D) && (!undesired) )
            {
            	numberBytes++;
            }

            /* If a modem status frame (0x8A)
             *  ____________________________________________________
             * |      |     |     |            |         |          |
             * | 0x7E | MSB | LSB | Frame Type | cmdData | checksum |
             * |______|_____|_____|____________|_________|__________|
             *    0      1     2        3          4          5
             */
            if( (ByteIN[counter3-1]==0x8A) && (counter3==(4+(uint16_t)status*6)) )
            {
				// increment in 6Bytes 'numberBytes'
            	numberBytes+=6;

            	// increment 'status' in order to add a new 'modem status frame'
            	status++;
            }

            // If a new frame is read after reading any undesired frame,
        	// decrement 'numberBytes' and set undesired
            if( (ByteIN[counter3-1]==0x7E) && (undesired==1) )
            {
            	numberBytes--;
				undesired=numberBytes-7;
            }

            // if 'counter3' is the same as 'numberBytes' we finish
        	// This means that TX status has been found
            if(counter3==numberBytes)
            {
            	end=1;
           	}
       	}

       	// avoid millis overflow problem
		if( millis() < previous ) previous=millis();

		// check if time is out
        if( (millis()-previous) > interval )
       	{
        	end=1;
        	serialFlush(uart);
        }
    }

    // Store number of read bytes
    num_TX=counter3;
    counter3=0;

    #if DEBUG_XBEE > 0
	PRINT_XBEE(F("RX:"));
    for(uint16_t i = 0; i < num_TX ; i++)
	{
		USB.printHex(ByteIN[i]);
	}
	USB.println();
	#endif

    // If some corrupted frame has appeared we jump it
    if( ByteIN[0]!=0x7E )
    {
		// jump until a new frame start delimiter is found
		while( ByteIN[i]!=0x7E && i<num_TX )
        {
			i++;
		}
	}

    // Parse the received messages from the XBee
    while( num_mes>0 )
    {
		// get length of the packet until another start delimiter
		// is found or the end of read bytes is reached
        while( ByteIN[i]!=0x7E && i<num_TX )
        {
			i++;
		}
        length_mes=i-length_prev;

		// If any byte has been escaped, it must be converted before parsing it
		// So first count number of escaped bytes and then make conversion
        for( it=0;it<length_mes;it++)
        {
            if( ByteIN[it+length_prev]==0x7D ) num_esc++;
        }

        // if there are escaped bytes, make conversion
        if( num_esc )
        {
			des_esc(ByteIN,length_mes,i-length_mes);
		}


		/* Call parsing function depending on the Frame Type
		 *  _______________________________________________
		 * |      |     |     |            |               |
		 * | 0x7E | MSB | LSB | Frame Type |    ......     |
		 * |______|_____|_____|____________|_______________|
		 *    0      1     2        3          variable
		 */
        switch( ByteIN[(i-length_mes)+3] )
        {
            case 0x8A :	//Modem Status
						modemStatusResponse( ByteIN,
											 length_mes-num_esc+length_prev,
											 i-length_mes);
						break;

            case 0x90 :	// Receive Packet (AO=0)
            case 0x91 :	// Explicit Rx Indicator (AO=1)
						error_RX=rxData( ByteIN,
										 length_mes-num_esc+length_prev,
										 i-length_mes);
						break;

            case 0x8B :	// Transmit Status
						true_naD[0]=ByteIN[i-length_mes+5];
						true_naD[1]=ByteIN[i-length_mes+6];
						retries_sending=ByteIN[i-length_mes+7];
						discovery_status=ByteIN[i-length_mes+9];
						delivery_status=ByteIN[i-length_mes+8];
						if( delivery_status==0 )
						{
							error_TX=0;
						}
						else
						{
							error_TX=1;
						}
						break;

            default   :	break;
        }

		// decrement number of pending packets to be treated
        num_mes--;

        // update previous index in input buffer in order to carry on with the
        // following message stored in 'memory'
        length_prev=i;
        i++;
        num_esc=0;
    }

    return error_TX;
}


/*
 * Function: Parses the RX Data message received by the XBee module
 *
 * Parameters:
 * 	data_in : the answer received by the module
 * 	end : the end of the frame
 * start : the start of the frame
 *
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 *
 *  Call parsing function depending on the Frame Type
 *  ____________________________________________________
 * |      |     |     |                      |          |
 * | 0x7E | MSB | LSB |      Frame Data      | checksum |
 * |______|_____|_____|______________________|__________|
 *   1B     1B    1B          variable            1B
 *
 * Frame Data is split into the FrameType and cmdData
 *  ____________________________________________________
 * |      |     |     |           |          |          |
 * | 0x7E | MSB | LSB | FrameType |  cmdData | checksum |
 * |______|_____|_____|___________|__________|__________|
 *   1B     1B    1B       1B       variable     1B
 */
int8_t WaspXBeeCore::rxData(uint8_t* data_in, uint16_t end, uint16_t start)
{
    if(freeMemory()<150) return -1;
    uint8_t byteIN[120];
    int8_t error=2;

	// Check the checksum
    if(checkChecksum( data_in, end, start))
	{
		// clean input buffer before returning error
		flush();
        return 1;
    }

	// Copy 'cmdData' to byteIN and calculate
	// 'cmdData' length storing it in 'data_length' attribute
	data_length=0;
    for( uint16_t j = 4+start ; j < end-1 ; j++ )
    {
        byteIN[j-4-start] = data_in[j];
        data_length++;
    }

	// Set correspondent mode depending on the frame type
    switch( data_in[start+3] )
    {
        case 0x80 :	// XBee802 - RX (Receive) Packet: 64-bit Address
					rxFrameType=_64B;
					break;

        case 0x81 :	// XBee802 - RX (Receive) Packet: 16-bit Address
					rxFrameType=_16B;
					break;

        case 0x90 :	// XBee Receive Packet (AO=0)
					rxFrameType=NORMAL_RX;
					break;

        case 0x91 :	// XBee Explicit Rx Indicator (AO=1)
					rxFrameType=EXPLICIT_RX;
					break;
    }

	////////////////////////////////////////////////////////////////////////////
	// call parsing function for the packet which
	// has been stored in byteIN.
	////////////////////////////////////////////////////////////////////////////
    error=readXBee(byteIN);

    return error;
}




/*
 Function: Parses the ND message received by the XBee module
 Values: Stores in 'scannedBrothers' variable the data extracted from the answer
*/
void WaspXBeeCore::treatScan()
{
    uint8_t cont2=0;
    uint8_t length_NI=0;


    cont2=totalScannedBrothers-1;

    // store MY Address
    scannedBrothers[cont2].MY[0]=data[0];
    scannedBrothers[cont2].MY[1]=data[1];

    // store High MAC Address
    scannedBrothers[cont2].SH[0]=data[2];
    scannedBrothers[cont2].SH[1]=data[3];
    scannedBrothers[cont2].SH[2]=data[4];
    scannedBrothers[cont2].SH[3]=data[5];

    // store Low MAC Address
    scannedBrothers[cont2].SL[0]=data[6];
    scannedBrothers[cont2].SL[1]=data[7];
    scannedBrothers[cont2].SL[2]=data[8];
    scannedBrothers[cont2].SL[3]=data[9];

    // clean NI buffer
    memset(scannedBrothers[cont2].NI,0x00,sizeof(scannedBrothers[cont2].NI));

	if(protocol==XBEE_802_15_4)
    {
		// store RSSI
		scannedBrothers[cont2].RSSI=data[10];

		// store NI
		if (data_length>12)
		{
			length_NI = data_length-12;
			if (length_NI>20)
			{
				length_NI = 20;
			}
			memcpy(scannedBrothers[cont2].NI, &data[11], length_NI);
		}
	}
    else if( protocol == ZIGBEE 	||
			 protocol == DIGIMESH 	||
			 protocol == XBEE_900 	||
			 protocol == XBEE_868	||
			 protocol == XBEE_868LP	||
			 protocol == XBEE_900HP	 )
    {
		if (data_length>19)
		{
			length_NI = data_length-19;
			if (length_NI>20)
			{
				length_NI = 20;
			}
			memcpy(scannedBrothers[cont2].NI, &data[10], length_NI);

			// in the case the following protocols, store more available information
			scannedBrothers[cont2].PMY[0]=data[length_NI+11];
			scannedBrothers[cont2].PMY[1]=data[length_NI+12];

			scannedBrothers[cont2].DT=data[length_NI+13];
			scannedBrothers[cont2].ST=data[length_NI+14];

			scannedBrothers[cont2].PID[0]=data[length_NI+15];
			scannedBrothers[cont2].PID[1]=data[length_NI+16];

			scannedBrothers[cont2].MID[0]=data[length_NI+17];
			scannedBrothers[cont2].MID[1]=data[length_NI+18];
		}
    }
}

/*
 * Function: Checks the checksum is good
 * Parameters:
 * 	data_in : the answer received by the module
 * 	end : the end of the frame
 * 	start : the start of the frame
 * Returns: Integer that determines if there has been any error
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeCore::checkChecksum(uint8_t* data_in, uint16_t end, uint16_t start)
{
    uint16_t checksum=0;

    for(it=3+start;it<end;it++)
    {
        checksum=checksum+data_in[it];
    }
    if( (checksum==255) ) return 0;
    checksum%=256;
    if( checksum!=255 ) return 1;
    return 0;
}


/*
 * Function: Calculates the checksum for a TX frame
 * Parameters:
 * 	TX : pointer to the frame whose checksum has to be calculated
 * Returns: the calculated checksum for the frame
*/
uint8_t WaspXBeeCore::getChecksum(uint8_t* TX)
{
	uint8_t checksum=0;
	uint16_t length_field = (uint16_t)((TX[1]<<8)&0xFF00) + (uint16_t)(TX[2]&0x00FF);

	 // calculate checksum
    for( uint16_t i=0 ; i < length_field;i++)
    {
		checksum = (checksum + TX[i+3])&0xFF;
	}

	while( checksum > 255 )
	{
		checksum = checksum - 256;
	}
	checksum = 255 - checksum;

	return checksum;

}

/*
 Function: Clears the variable 'command'
*/
void WaspXBeeCore::clearCommand()
{
    memset(command,0x00,sizeof(command));
}


/*
 Function: It gets the next index where store the finished packet
*/
uint8_t WaspXBeeCore::getFinishIndex()
{
    for( it=0 ; it < MAX_FINISH_PACKETS ; it++ )
    {
        if( packet_finished[it] == NULL ) break;
    }
    return it;
}

/*
 Function: It clears the finished packets array
*/
void WaspXBeeCore::clearFinishArray()
{
    for( it=0 ; it < MAX_FINISH_PACKETS ; it++ )
    {
        free(packet_finished[it]);
        packet_finished[it]=NULL;
    }
}

/*
 Function: It gets the index in 'packet_finished' where store the new packet, according to a FIFO policy
*/
uint8_t WaspXBeeCore::getIndexFIFO()
{
    uint8_t position=0;
    uint16_t counter1=0;

    while( counter1 < MAX_FINISH_PACKETS )
    {
        for( it = counter1 ; it < (MAX_FINISH_PACKETS-1) ; it++ )
        {
            if( packet_finished[counter1]->time < packet_finished[it+1]->time ) position++;
            else break;
        }
        if( position==(MAX_FINISH_PACKETS-1) )
        {
            position=counter1;
            counter1=MAX_FINISH_PACKETS;
        }
        else position=counter1+1;
        counter1++;
    }
    free(packet_finished[position]);
    packet_finished[position]=NULL;
    return position;
}

/*
 Function: It gets the index in 'packet_finished' where store the new packet, according to a LIFO policy
*/
uint8_t WaspXBeeCore::getIndexLIFO()
{
    uint8_t position=0;
    uint16_t counter1=0;

    while( counter1<MAX_FINISH_PACKETS )
    {
        for(it=counter1;it<(MAX_FINISH_PACKETS-1);it++)
        {
            if( packet_finished[counter1]->time > packet_finished[it+1]->time ) position++;
            else break;
        }
        if( position==(MAX_FINISH_PACKETS-1) ){
            position=counter1;
            counter1=MAX_FINISH_PACKETS;
        }
        else position=counter1+1;
        counter1++;
    }
    free(packet_finished[position]);
    packet_finished[position]=NULL;
    return position;
}




/*
 *  Function: It receives the first packet of a new firmware
 *
 * Returns: Integer that determines if there has been any error
 * 	error=1 --> There has been an error while executing the function
 * 	error=0 --> The function has been executed with no errors
 */
uint8_t WaspXBeeCore::new_firmware_received()
{
	bool startSequence = true;
	uint8_t channel_to_set = 0;
	bool error_sd = false;
	char buffer[33];
	new_firm_received_t* packet;

	// cast the data field to a new_firm_received_t
	packet = (new_firm_received_t*)packet_finished[pos-1]->data;

	// Check 'KEY_ACCESS'
	for (int j = 0; j < 8; j++)
	{
		if(packet->authkey[j] != Utils.readEEPROM(j+107))
		{
			startSequence = false;
			break;
		}
	}

	// set default multicast type
	// firm_info.multi_type=3 means --> No multicast mode
	firm_info.multi_type=3;

	if( startSequence && !firm_info.already_init )
	{
		if(freeMemory()<450) return 1;
		char asteriscos[449];

		// Set OTA Flag and set last time a OTA packet was received
		programming_ON=1;
		firm_info.time_arrived = millis();

		// get pid from packet and set the PID as a 32-Byte array formatted as:
		// PID (7B) +  asterisks (25B)
		for(it=0; it<32; it++)
		{
			if( it>=7)
			{
				firm_info.ID[it]='*';
			}
			else
			{
				firm_info.ID[it]=packet->pid[it];
			}
		}
		firm_info.ID[it]='\0';

		// get date from packet
		for(it=0; it<12 ; it++)
		{
			firm_info.DATE[it]=packet->date[it];
		}
		firm_info.DATE[it]='\0';

		/*** OTA NEW PARAMETER SETTING CASES ***/

		/// 802.15.4 Multicast or Direct access with setting of new channel
		if( (packet_finished[pos-1]->data_length==32) && (protocol==XBEE_802_15_4) )
		{
			// get channel to set from packets
			channel_to_set = packet->channel;

			// get actual channel used by XBee module
			getChannel();
			firm_info.channel=channel;

			// set new channel if there is no error
			if( !error_AT )
			{
				setChannel(channel_to_set);
			}
			writeValues();

			// set multicast configuration mode
			firm_info.multi_type=0;
		}

		/// DigiMesh or ZigBee Multicast or Unicast with new Auth key setting
		if( packet_finished[pos-1]->data_length==39 && (protocol==ZIGBEE || protocol==DIGIMESH) )
		{
			// Copy 'Auth key'
			for (it = 0; it < 8;it++)
			{
				firm_info.authkey[it] = Utils.readEEPROM(it+107);
			}

			// Set new 'Auth key'
			for (it = 0; it < 8;it++)
			{
				// write EEPROM
				eeprom_write_byte((unsigned char *) it+107, packet->new_authkey[it]);
			}

			// set multicast configuration mode
			firm_info.multi_type=1;
		}

		/// 868 or 900 Multicast or Unicast with new encryption key setting
		if( (packet_finished[pos-1]->data_length==63) && (protocol==XBEE_868 || protocol==XBEE_900 || protocol==XBEE_868LP))
		{
			// Copy 'Encryption key' from packet
			for (it = 0; it < 16;it++)
			{
				firm_info.encryptionkey[it] = packet->encryptionkey[it];
			}

			// get new encryption key to set from packet
			char auxkey[16];
			for (it = 0; it < 16;it++)
			{
				auxkey[it] = packet->new_encryptionkey[it];
			}

			// get actual encryption mode
			getEncryptionMode();
			firm_info.encryptionMode = encryptMode;

			// enable encryption
			setEncryptionMode(1);

			// set new encryption key to XBee module
			setLinkKey(auxkey);
			writeValues();

			// set multicast configuration mode
			firm_info.multi_type=2;
		}

		// store mac address from received packet
		firm_info.mac_programming[0] = packet_finished[pos-1]->macSH[0];
		firm_info.mac_programming[1] = packet_finished[pos-1]->macSH[1];
		firm_info.mac_programming[2] = packet_finished[pos-1]->macSH[2];
		firm_info.mac_programming[3] = packet_finished[pos-1]->macSH[3];
		firm_info.mac_programming[4] = packet_finished[pos-1]->macSL[0];
		firm_info.mac_programming[5] = packet_finished[pos-1]->macSL[1];
		firm_info.mac_programming[6] = packet_finished[pos-1]->macSL[2];
		firm_info.mac_programming[7] = packet_finished[pos-1]->macSL[3];

		// copy program id
		for(it=0; it<7; it++)
		{
			firm_info.name_file[it] = firm_info.ID[it];
		}
		firm_info.name_file[it]='\0';

		// initialize variables
		firm_info.packets_received = 0;
		firm_info.data_count_packet = 0;
		firm_info.data_count_packet_ant = 0;
		firm_info.paq_disordered = 0;
		firm_info.already_init = 1;

		// close SD files
		boot_file.close();
		firm_file.close();
		SD.root.close();

		// init SD card	and local flag
		if(SD.ON())
		{
			sd_on=1;
			error_sd=false;
		}
		else
		{
			sd_on=0;
			error_sd=true;
		}

		// Create the first sector
		for (int j=0 ; j<448 ; j++)
		{
			asteriscos[j]='*';
		}
		asteriscos[448] = '\0';

		if( !error_sd )
		{
			// create firmware file: 2 trials
			if( !firm_file.open(&SD.root, firm_info.name_file, O_WRITE | O_CREAT | O_EXCL | O_SYNC | O_APPEND) )
			{
				// in the case it failed in first place, try it again
				firm_file.remove(&SD.root,firm_info.name_file);
				if(!firm_file.open(&SD.root, firm_info.name_file, O_WRITE | O_CREAT | O_EXCL | O_SYNC | O_APPEND))
				{
					error_sd=true;
				}
			}

			// once the firmware file is created write first sector (512 Bytes)
			// formatted OTA file: START_SECTOR(32B) + PID(32B) + asterisks(448B)
			if( !error_sd )
			{
				// START_SECTOR
				strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[10])));
				if(buffer==NULL) return 1;

				// Write START_SECTOR string into firmware file
				if( (uint16_t)firm_file.write(buffer,strlen(buffer)) != strlen(buffer) )
				{
					error_sd=true;
				}

				// Write program ID into firmware file
				if( (uint16_t)firm_file.write(firm_info.ID,strlen(firm_info.ID)) != strlen(firm_info.ID))
				{
					error_sd=true;
				}

				// Write asterisks into firmware file
				if( (uint16_t)firm_file.write(asteriscos,strlen(asteriscos)) != strlen(asteriscos))
				{
					error_sd=true;
				}
			}
		}

		if( error_sd )
		{
			programming_ON=0;
			setMulticastConf();
			return 1;
		}

	}
	// Error mismatch --> Delete the packet
	else
	{
		if(!programming_ON)
		{
			programming_ON=0;
			setMulticastConf();
			return 1;
		}
	}
	return 0;
}


/*
 Function: It receives the data packets of a new firmware
 Returns: Nothing
*/
void WaspXBeeCore::new_firmware_packets()
{
	uint8_t data_bin[92];
	uint16_t sd_index=0;
	bool true_mac = true;
	bool error_sd = false;
	new_firm_packet_t* packet;

	// cast the data field to a new_firm_received_t
	packet = (new_firm_packet_t*)packet_finished[pos-1]->data;

	it=0;

	// process the packet only when the programming mode is ON
	if( programming_ON )
	{
		// check if HIGH source mac address is correct
		for(int j=0 ; j<4 ; j++)
		{
			if( packet_finished[pos-1]->macSH[j] != firm_info.mac_programming[j] )
			{
				true_mac=false;
				break;
			}
		}
		// check if LOW source mac address is correct
		for(int j=0 ; j<4 ; j++)
		{
			if( packet_finished[pos-1]->macSL[j] != firm_info.mac_programming[j+4] )
			{
				true_mac=false;
				break;
			}
		}

		// if MAC address is OK, then proceed to write the SD file
		if( true_mac )
		{
			// get packet counter from received packet
			firm_info.data_count_packet = packet->counter;

			// successful cases to validate the packet:
			// -> It is the first packet received
			// -> This is the packet that follows the last one
			// -> The packet counter (1Byte) overflows and restarts from zero
			if(	((firm_info.data_count_packet == 0) && (firm_info.packets_received==0))
				||	((firm_info.data_count_packet - firm_info.data_count_packet_ant) == 1 )
				||	((firm_info.data_count_packet == 0)&&(firm_info.data_count_packet_ant == 255) ) )
            {
               	// Copy binary data and calculate length of this field
				for( sd_index=0 ; sd_index<(packet_finished[pos-1]->data_length)-sizeof(header_t)-1 ; sd_index++ )
				{
                   	data_bin[sd_index] = packet_finished[pos-1]->data[sd_index+sizeof(header_t)+1];
               	}

				// Write binary data string into firmware file
				if( (uint16_t)firm_file.write(data_bin,sd_index) != sd_index )
				{
					error_sd = true;
				}

				// set init flag to zero
				firm_info.already_init = 0;

				// Set new OTA previous packet arrival time
				firm_info.time_arrived=millis();

				if(error_sd)
				{
					// skip programming mode:
					programming_ON=0;
					firm_file.remove(&SD.root,firm_info.name_file);
					firm_info.packets_received=0;
					firm_info.paq_disordered=0;
					setMulticastConf();
				}
				else
				{
					// validate packet:
					firm_info.packets_received++;
					firm_info.data_count_packet_ant = firm_info.data_count_packet;
					firm_info.paq_disordered=0;
					sd_index=0;
				}
			}
			else if( !(firm_info.data_count_packet == firm_info.data_count_packet_ant) )
			{
				if( (firm_info.data_count_packet - firm_info.data_count_packet_ant) == 2 )
				{
					// re-order one packet lost
					firm_info.paq_disordered=1;
				}
				else
				{
					// if more than one packet is lost, then stop OTA process
					programming_ON=0;
					firm_file.remove(&SD.root,firm_info.name_file);
					firm_info.packets_received=0;
					firm_info.paq_disordered=0;
					setMulticastConf();

					// flush uart
					serialFlush(uart);
				}
			}
		}
		else
		{
			programming_ON=0;
			setMulticastConf();
		}
	}
	else
	{
		if(programming_ON)
		{
			programming_ON=0;
			setMulticastConf();
		}
	}
}


/*
 * Function: It receives the last packet of a new firmware which carries the
 * number of packets that must have been received
 *
 *
 *
 */
void WaspXBeeCore::new_firmware_end()
{
	if(freeMemory()<400) return (void)-1;
	bool true_mac = true;
	char num_packets_char[5];
	uint16_t num_packets=0;
	packetXBee* paq_sent;
	uint8_t destination[8];
	bool send_ok = true;
	bool error_sd = false;
	char buffer[33];
	char data[100];

	// process the packet only when the programming mode is ON
	if( programming_ON )
	{
		// check the MAC address
		for(int i=0 ; i<4 ; i++)
		{
			if( packet_finished[pos-1]->macSH[i] != firm_info.mac_programming[i] )
			{
				true_mac=false;
				break;
			}
		}
		for(int i=0 ; i<4 ; i++)
		{
			if( packet_finished[pos-1]->macSL[i] != firm_info.mac_programming[i+4] )
			{
				true_mac=false;
				break;
			}
		}

		// process the packet when the mac address is correct
		if( true_mac )
		{
			// get the payload which contains the number of packets sent
			for( it=0 ; it<(packet_finished[pos-1]->data_length)-sizeof(header_t) ; it++ )
			{
				// check iterator
				if( it == sizeof(num_packets_char))
				{
					break;
				}

				// copy data
				num_packets_char[it] = packet_finished[pos-1]->data[sizeof(header_t)+it];
			}
			num_packets_char[it]='\0';

			// convert from string to integer
			num_packets = atoi(num_packets_char);

			// check the number of packets received
			if( num_packets != firm_info.packets_received )
			{
				send_ok = false;
			}
			else
			{
				send_ok = true;
			}

			// if number of packets matches to the infor received
			// then close and open the file to check it works
			if( send_ok )
			{
				firm_file.close();
				delay(10);

				if(!firm_file.open(&SD.root, firm_info.name_file, O_READ))
				{
					send_ok = false;
				}
			}
		}
		else
		{
			// false MAC address
			send_ok = false;
		}
	}
	else
	{
		// not in programming mode
		send_ok = false;
	}

	// if OTA worked then copy the information to BOOT.TXT
	if( send_ok == true )
	{
		programming_ON=0;
		firm_info.packets_received=0;

		// open BOOT.TXT
		if(!boot_file.open(&SD.root, BOOT_LIST, O_WRITE | O_CREAT | O_EXCL | O_SYNC | O_APPEND) )
		{
			if(!boot_file.open(&SD.root, BOOT_LIST, O_WRITE | O_SYNC | O_APPEND)) error_sd=true;
		}

		// write program ID into file
		if( (uint16_t)boot_file.write(firm_info.ID, strlen(firm_info.ID)) != strlen(firm_info.ID))
		{
			error_sd=true;
		}

		// write program date into file
		if( (uint16_t)boot_file.write(firm_info.DATE, strlen(firm_info.DATE)) != strlen(firm_info.DATE))
		{
			error_sd=true;
		}

		// write "\r\n" into file
		if( (uint16_t)boot_file.write("\r\n",strlen("\r\n")) != strlen("\r\n") )
		{
			error_sd=true;
		}
	}


	// send OTA packet to inform the result
	if( (send_ok == true) && (error_sd == false) )
	{
		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=UNICAST;

		// copy destination address from received packet
		destination[0] = packet_finished[pos-1]->macSH[0];
		destination[1] = packet_finished[pos-1]->macSH[1];
		destination[2] = packet_finished[pos-1]->macSH[2];
		destination[3] = packet_finished[pos-1]->macSH[3];
		destination[4] = packet_finished[pos-1]->macSL[0];
		destination[5] = packet_finished[pos-1]->macSL[1];
		destination[6] = packet_finished[pos-1]->macSL[2];
		destination[7] = packet_finished[pos-1]->macSL[3];

		//NEW_FIRMWARE_MESSAGE_OK
		strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[0])));
		if(buffer==NULL) return void(-1);

		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=NEW_FIRM_END_FRAME;
		data[4]='\0';
		strcat(data,buffer);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );
		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;

		setMulticastConf();
	}
	else
	{
		firm_file.remove(&SD.root,firm_info.name_file);
		programming_ON=0;
		firm_info.packets_received=0;

		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=UNICAST;

		// copy destination address from received packet
		destination[0] = packet_finished[pos-1]->macSH[0];
		destination[1] = packet_finished[pos-1]->macSH[1];
		destination[2] = packet_finished[pos-1]->macSH[2];
		destination[3] = packet_finished[pos-1]->macSH[3];
		destination[4] = packet_finished[pos-1]->macSL[0];
		destination[5] = packet_finished[pos-1]->macSL[1];
		destination[6] = packet_finished[pos-1]->macSL[2];
		destination[7] = packet_finished[pos-1]->macSL[3];

		//NEW_FIRMWARE_MESSAGE_ERROR
		strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[1])));
		if(buffer==NULL) return void(-1);


		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=NEW_FIRM_END_FRAME;
		data[4]='\0';
		strcat(data,buffer);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );
		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;

		setMulticastConf();
	}

	// close SD files
	boot_file.close();
	firm_file.close();
	SD.root.close();

	sd_on=0;
}


/*
 * Function: It uploads the new firmware
 *
 * This function seeks the program ID requested in the received "upload firmware"
 * packet. If it does not exist, return an error packet. In the case it exists,
 * rebot Waspmote in order to upload the new firmware to Flash memory
*/
void WaspXBeeCore::upload_firmware()
{
	if(freeMemory()<400) return (void)-1;

	bool id_exist = true;
	packetXBee* paq_sent;
	uint8_t destination[8];
	unsigned long previous=0;
	uint8_t buf_sd[46];
	bool end_file=false;
	uint8_t num_bytes = 0;
	bool reset = false;
	bool startSequence = true;
	bool error_sd = false;
	char buffer[49];
	char data[70];
	upload_firm_t* packet;

	// cast the data field to a upload_firm_t
	packet = (upload_firm_t*)packet_finished[pos-1]->data;

	// Check 'KEY_ACCESS'
	for( int i = 0; i < 8; i++)
	{
		if(packet->authkey[i] != Utils.readEEPROM(i+107))
		{
			startSequence = false;
			break;
		}
	}

	// if authentication key is correct, then process the packet
	if( startSequence )
	{
		if( !sd_on )
		{
			sd_on=1;

			// init SD card
			SD.ON();

			if(boot_file.open(&SD.root, BOOT_LIST, O_READ))
			{
				sd_on=1;
				error_sd=false;
				boot_file.close();
			}
		}

		if( !error_sd )
		{
			if(boot_file.open(&SD.root, BOOT_LIST, O_READ))
			{
				// get the pid from the received packet
				for(it=0;it<32;it++)
				{
					if( it>=7)
					{
						firm_info.ID[it]='*';
					}
					else
					{
						firm_info.ID[it]=packet->pid[it];
					}
				}
				firm_info.ID[it]='\0';

				previous=millis();
				/*	while( num_lines>0 && (millis()-previous<5000) )*/
				while( millis()-previous<5000 && !end_file)
				{
					// read a new BOOT.TXT line
					if( (num_bytes=boot_file.read(buf_sd,sizeof(buf_sd))) == 0)
					{
						end_file=true;
					}

					// compare read line to pid previously stored
					for(it=0;it<32;it++)
					{
						if( buf_sd[it] != firm_info.ID[it] )
						{
							id_exist=false;
							break;
						}
					}
					if(!id_exist && !end_file )
					{
						id_exist=true;
					}
					else if(id_exist) break;

					//avoid millis overflow problem
					if( millis() < previous ) previous=millis();
				}
			}
			else
			{
				id_exist=false;
			}

			if(id_exist)
			{
				// store the filename to be uploaded
				for(it=0; it<7; it++)
				{
					if( firm_info.ID[it] == '*' ) break;
					firm_info.name_file[it]=firm_info.ID[it];
				}
				firm_info.name_file[it]='\0';

				if(!firm_file.open(&SD.root, firm_info.name_file, O_READ))
				{
					id_exist=false;
				}
			}
		}
		else
		{
			id_exist=false;
		}

		// If everything is correct proceed to set up the EEPROM memory, send a
		// packet to inform the status and jump to the bootloader
		if( id_exist)
		{
			// update the name of the firmware in EEPROM memory
			for( int i=0 ; i<32 ; i++)
			{
				// write EEPROM
				eeprom_write_byte((unsigned char *) i+2, firm_info.ID[i]);
			}

			paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
			paq_sent->mode=UNICAST;

			// copy destination address from received packet
			destination[0] = packet_finished[pos-1]->macSH[0];
			destination[1] = packet_finished[pos-1]->macSH[1];
			destination[2] = packet_finished[pos-1]->macSH[2];
			destination[3] = packet_finished[pos-1]->macSH[3];
			destination[4] = packet_finished[pos-1]->macSL[0];
			destination[5] = packet_finished[pos-1]->macSL[1];
			destination[6] = packet_finished[pos-1]->macSL[2];
			destination[7] = packet_finished[pos-1]->macSL[3];

			//UPLOAD_FIRWARE_MESSAGE_OK
			strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[2])));
			if(buffer==NULL) return void(-1);

			// generate frame to send
			data[0]='<';
			data[1]='=';
			data[2]='>';
			data[3]=UPLOAD_FIRM_FRAME;
			data[4]='\0';
			strcat(data,buffer);

			// set destination parameters
			setDestinationParams(paq_sent, destination, data);

			// delay random time
			delay( (rand()%delay_end + delay_start) );
			// Try to send the answer for several times
		        for(int k=0; k<MAX_OTA_RETRIES; k++)
			{
			   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
			   else delay(rand()%delay_end + delay_start);
			}
			free(paq_sent);
			paq_sent=NULL;

			// close SD files
			boot_file.close();
			firm_file.close();
			SD.root.close();

			sd_on=0;

			free(packet_finished[pos-1]);
			packet_finished[pos-1]=NULL;

			// Save the transmitter MAC to answer later
			for( int i=0 ; i<8 ; i++)
			{
				// write EEPROM
				eeprom_write_byte((unsigned char *) 99+i, destination[i]);
			}

			previous=millis();
			while( !reset && millis()-previous<5000 )
			{
				// set OTA flag in EEPROM to '1'
				eeprom_write_byte((unsigned char *) 0x01, 0x01);

				if( Utils.readEEPROM(0x01)!=0x01 )
				{
					eeprom_write_byte((unsigned char *) 0x01, 0x01);
				}
				else reset=true;
				delay(10);
				if( millis() < previous ) previous=millis(); //avoid millis overflow problem
			}

			// Jump to bootloader
			__asm__("jmp 0x1E000");
		}
		else
		{
			paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
			paq_sent->mode=UNICAST;

			// copy destination address from received packet
			destination[0] = packet_finished[pos-1]->macSH[0];
			destination[1] = packet_finished[pos-1]->macSH[1];
			destination[2] = packet_finished[pos-1]->macSH[2];
			destination[3] = packet_finished[pos-1]->macSH[3];
			destination[4] = packet_finished[pos-1]->macSL[0];
			destination[5] = packet_finished[pos-1]->macSL[1];
			destination[6] = packet_finished[pos-1]->macSL[2];
			destination[7] = packet_finished[pos-1]->macSL[3];

			//UPLOAD_FIRWARE_MESSAGE_ERROR
			strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[3])));
			if(buffer==NULL) return void(-1);

			// generate frame to send
			data[0]='<';
			data[1]='=';
			data[2]='>';
			data[3]=UPLOAD_FIRM_FRAME;
			data[4]='\0';
			strcat(data,buffer);

			// set destination parameters
			setDestinationParams(paq_sent, destination, data);

			// delay random time
			delay( (rand()%delay_end + delay_start) );
			// Try to send the answer for several times
		        for(int k=0; k<MAX_OTA_RETRIES; k++)
			{
			   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
			   else delay(rand()%delay_end + delay_start);
			}
			free(paq_sent);
			paq_sent=NULL;

			// close SD files
			boot_file.close();
			firm_file.close();
			SD.root.close();

			sd_on = 0;

			free(packet_finished[pos-1]);
			packet_finished[pos-1]=NULL;
		}
	}
}


/*
 * Function: It answers the ID requested
 *
 *
 *
 */
void WaspXBeeCore::request_ID()
{
	if(freeMemory()<400) return (void)-1;
	char PID_aux[33];
	packetXBee* paq_sent;
	uint8_t destination[8];
	char ID_aux[17];
	bool startSequence = true;
	char data[70];
	request_id_t* packet;

	// cast the data field to a upload_firm_t
	packet = (request_id_t*)packet_finished[pos-1]->data;


	// Check 'KEY_ACCESS'
	for( int i = 0; i < 8; i++)
	{
		if(packet->authkey[i] != Utils.readEEPROM(i+107))
		{
			startSequence = false;
			break;
		}
	}

	if( startSequence )
	{
		// get PID from EEPROM memory
		for( int i=0 ; i<32 ; i++)
		{
			PID_aux[i] = Utils.readEEPROM(i+34);
		}
		PID_aux[32]='\0';

		// get Mote ID from EEPROM memory
		for( int i=0 ; i<16; i++)
		{
			ID_aux[i] = Utils.readEEPROM(i+147);
		}
		ID_aux[16]='\0';

		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=UNICAST;

		// store source MAC address
		destination[0] = packet_finished[pos-1]->macSH[0];
		destination[1] = packet_finished[pos-1]->macSH[1];
		destination[2] = packet_finished[pos-1]->macSH[2];
		destination[3] = packet_finished[pos-1]->macSH[3];
		destination[4] = packet_finished[pos-1]->macSL[0];
		destination[5] = packet_finished[pos-1]->macSL[1];
		destination[6] = packet_finished[pos-1]->macSL[2];
		destination[7] = packet_finished[pos-1]->macSL[3];

		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=REQUEST_ID_FRAME;
		data[4]='\0';
		strcat(data,PID_aux);
		strcat(data,ID_aux);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );
		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;
	}
	else
	{
	}
}


/*
 * Function: It answers the boot list file
 *
 * This function seeks the program IDs written in BOOT.TXT
*/
void WaspXBeeCore::request_bootlist()
{
	packetXBee* paq_sent;
	uint8_t destination[8];
	unsigned long previous=0;
	uint8_t buf_sd[46];
	char buf_sd_aux[47];
	bool end_file=false;
	uint8_t num_bytes = 0;
	bool startSequence = true;
	uint8_t errors_tx = 0;
	char buffer[31];
	char data[70];
	request_boot_t* packet;

	// cast the data field to a upload_firm_t
	packet = (request_boot_t*)packet_finished[pos-1]->data;


	// Check 'KEY_ACCESS'
	for (it = 0; it < 8;it++)
	{
		if(packet->authkey[it] != Utils.readEEPROM(it+107))
		{
			startSequence = false;
			break;
		}
	}

	if( startSequence )
	{
		if( !sd_on )
		{
			sd_on=1;

			// init SD card
			SD.ON();
		}

		if( sd_on )
		{
			if(boot_file.open(&SD.root, BOOT_LIST, O_READ))
			{
				previous=millis();

				// send a packet for each BOOT.TXT line:
				while( millis()-previous<30000 && !end_file)
				{
					if( (num_bytes=boot_file.read(buf_sd,sizeof(buf_sd))) <= 3)
					{
						end_file=true;
					}

					if( !end_file )
					{
						for(it=0;it<(sizeof(buf_sd));it++)
						{
							buf_sd_aux[it]=buf_sd[it];
						}
						buf_sd_aux[it]='\0';

						paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
						paq_sent->mode=UNICAST;

						// store source MAC address
						destination[0] = packet_finished[pos-1]->macSH[0];
						destination[1] = packet_finished[pos-1]->macSH[1];
						destination[2] = packet_finished[pos-1]->macSH[2];
						destination[3] = packet_finished[pos-1]->macSH[3];
						destination[4] = packet_finished[pos-1]->macSL[0];
						destination[5] = packet_finished[pos-1]->macSL[1];
						destination[6] = packet_finished[pos-1]->macSL[2];
						destination[7] = packet_finished[pos-1]->macSL[3];

						// generate frame to send
						data[0]='<';
						data[1]='=';
						data[2]='>';
						data[3]=REQUEST_BOOT_FRAME;
						data[4]='\0';
						strcat(data,buf_sd_aux);

						setDestinationParams(paq_sent, destination, data);

						// delay random time
						delay( (rand()%delay_end + delay_start) );
						// Try to send the answer for several times
					        for(int k=0; k<MAX_OTA_RETRIES; k++)
						{
						   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
						   else delay(rand()%delay_end + delay_start);
						}
						if( error_TX ) errors_tx++;
						free(paq_sent);
						paq_sent=NULL;
					}

					// avoid millis overflow problem
					if( millis() < previous ) previous=millis();

				}

				// close SD files
				boot_file.close();
				firm_file.close();
				SD.root.close();

				sd_on=0;

				// send a packet to inform the result
				if( errors_tx )
				{
					paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
					paq_sent->mode=UNICAST;

					// store source MAC address
					destination[0] = packet_finished[pos-1]->macSH[0];
					destination[1] = packet_finished[pos-1]->macSH[1];
					destination[2] = packet_finished[pos-1]->macSH[2];
					destination[3] = packet_finished[pos-1]->macSH[3];
					destination[4] = packet_finished[pos-1]->macSL[0];
					destination[5] = packet_finished[pos-1]->macSL[1];
					destination[6] = packet_finished[pos-1]->macSL[2];
					destination[7] = packet_finished[pos-1]->macSL[3];

					//REQUEST_BOOTLIST_MESSAGE
					strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[4])));
					if(buffer==NULL) return void(-1);

					// generate frame to send
					data[0]='<';
					data[1]='=';
					data[2]='>';
					data[3]=REQUEST_BOOT_FRAME;
					data[4]='\0';
					strcat(data,buffer);
					strcat(data,"ER");

					// set destination parameters
					setDestinationParams(paq_sent, destination, data);

					// delay random time
					delay( (rand()%delay_end + delay_start) );
					// Try to send the answer for several times
		        	for(int k=0; k<MAX_OTA_RETRIES; k++)
					{
					   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
					   else delay(rand()%delay_end + delay_start);
					}
					free(paq_sent);
					paq_sent=NULL;
				}
				else
				{
					paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
					paq_sent->mode=UNICAST;

					// store source MAC address
					destination[0] = packet_finished[pos-1]->macSH[0];
					destination[1] = packet_finished[pos-1]->macSH[1];
					destination[2] = packet_finished[pos-1]->macSH[2];
					destination[3] = packet_finished[pos-1]->macSH[3];
					destination[4] = packet_finished[pos-1]->macSL[0];
					destination[5] = packet_finished[pos-1]->macSL[1];
					destination[6] = packet_finished[pos-1]->macSL[2];
					destination[7] = packet_finished[pos-1]->macSL[3];

					//REQUEST_BOOTLIST_MESSAGE
					strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[4])));
					if(buffer==NULL) return void(-1);

					// generate frame to send
					data[0]='<';
					data[1]='=';
					data[2]='>';
					data[3]=REQUEST_BOOT_FRAME;
					data[4]='\0';
					strcat(data,buffer);
					strcat(data,"OK");

					// set destination parameters
					setDestinationParams(paq_sent, destination, data);

					// delay random time
					delay( (rand()%delay_end + delay_start) );
					// Try to send the answer for several times
		        	for(int k=0; k<MAX_OTA_RETRIES; k++)
					{
					   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
					   else delay(rand()%delay_end + delay_start);
					}
					free(paq_sent);
					paq_sent=NULL;
				}
			}
			else
			{
			}
		}
		else
		{
		}
	}
	else
	{
	}
}


/*
 * checkNewProgram() - It checks the new firmware upgrade
 *
 * This function checks if there is any OTA process has been performed. This
 * function should be called at the beginning of any OTA-supporting code, just
 * after switching the XBee module ON
 *
 */
void WaspXBeeCore::checkNewProgram()
{

	if(freeMemory()<400) return (void)-1;
	uint8_t current_ID[32];
	char MID[17];
	bool reprogrammingOK = true;
	uint8_t byte_aux[32];
	packetXBee* paq_sent;
	uint8_t destination[8];
	char buffer[33];
	char data[70];

	pinMode(SD_SCK, INPUT);
	for(it=0;it<32;it++)
	{
		current_ID[it]= Utils.readEEPROM(it+34);
		eeprom_write_byte((unsigned char *) it+66, current_ID[it]);
	}

	for(it=0;it<16;it++)
	{
		MID[it]=Utils.readEEPROM(it+147);
	}
	MID[16]='\0';

	if( WaspRegister & REG_OTA)
	{
		// Checking if programID and currentID are the same --> the program has been changed properly
		for(it = 0;it<32;it++)
		{
			byte_aux[it] = eeprom_read_byte((unsigned char *) it+2);
		}

		for(it = 0;it<32;it++)
		{
			if (byte_aux[it] != eeprom_read_byte((unsigned char *) it+34))
			{
				reprogrammingOK = false;
			}
		}

		// unset OTA Flag in Waspmote Control Register
		WaspRegister &= ~(REG_OTA);

		// If both IDs are equal a confirmation message is sent to the trasmitter
		if (reprogrammingOK)
		{
			paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
			paq_sent->mode=UNICAST;

			for(it=0;it<8;it++)
			{
				destination[it]=Utils.readEEPROM(99+it);
			}

			// ANSWER_START_WITH_FIRMWARE_OK
			strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[5])));
			if(buffer==NULL) return void(-1);

			// generate frame to send
			data[0]='<';
			data[1]='=';
			data[2]='>';
			data[3]=CHECK_NEW_PROG_FRAME;
			data[4]='\0';
			strcat(data,MID);
			strcat(data,buffer);

			// set destination parameters
			setDestinationParams(paq_sent, destination, data);

			// delay random time
			delay( (rand()%delay_end + delay_start) );
			// Try to send the answer for several times
		        for(int k=0; k<MAX_OTA_RETRIES; k++)
			{
			   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
			   else delay(rand()%delay_end + delay_start);
			}
			free(paq_sent);
			paq_sent=NULL;
		}
		// If the IDs are different an error message is sent to the transmitter
		else
		{
			paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
			paq_sent->mode=UNICAST;

			for(it=0;it<8;it++) destination[it]=Utils.readEEPROM(99+it);

			// ANSWER_START_WITH_FIRMWARE_ERR
			strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[6])));
			if(buffer==NULL) return void(-1);

			// generate frame to send
			data[0]='<';
			data[1]='=';
			data[2]='>';
			data[3]=CHECK_NEW_PROG_FRAME;
			data[4]='\0';
			strcat(data,MID);
			strcat(data,buffer);

			// set destination parameters
			setDestinationParams(paq_sent, destination, data);

			// delay random time
			delay( (rand()%delay_end + delay_start) );
			// Try to send the answer for several times
		        for(int k=0; k<MAX_OTA_RETRIES; k++)
			{
			   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
			   else delay(rand()%delay_end + delay_start);
			}
			free(paq_sent);
			paq_sent=NULL;
		}
	}
	else
	{
		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=BROADCAST;

		// RESET_MESSAGE
		strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[7])));
		if(buffer==NULL) return void(-1);

		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=CHECK_NEW_PROG_FRAME;
		data[4]='\0';
		strcat(data,MID);
		strcat(data,buffer);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );
		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;
	}

	// close SD card
	SD.OFF();

	// Clear reception struct after restarting the program.
	// This allows to delete other restarting packets sent by other nodes.
	clearFinishArray();
	pos=0;
}


/*
 * This function seeks the program ID requested to be deleted. in the case it is
 * found, then it is deleted and a confirmation packet is sent. In the case it
 * is not found an error packet is sent
 *
 */
void WaspXBeeCore::delete_firmware()
{

	if(freeMemory()<400) return (void)-1;
	packetXBee* paq_sent;
	uint8_t destination[8];
	unsigned long previous=0;
	char buf_sd[46];
	char buf_sd_aux[47];
	bool end_file=false;
	uint8_t num_bytes = 0;
	bool startSequence = true;
	char file_to_delete[8];
	bool error=false;
	bool match_id = true;
	char buffer[33];
	char data[70];
	delete_firm_t* packet;

	// file_aux <-- "FILEAUX"
	char file_aux[10];
	strcpy_P(file_aux, (char*)pgm_read_word(&(table_OTA[11])));

	// cast to the pointer where the frame starts
	packet = (delete_firm_t*)packet_finished[pos-1]->data;

	// Check 'KEY_ACCESS'
	for( int i = 0; i < 8; i++)
	{
		if( packet->authkey[i] != Utils.readEEPROM(i+107))
		{
			startSequence = false;
			break;
		}
	}

	if( startSequence )
	{
		if( !sd_on )
		{
			sd_on=1;

			// init SD card
			SD.ON();
		}

		if( sd_on )
		{
			// Store the file to delete
			for(int i=0; i<7; i++)
			{
				file_to_delete[i]=packet->pid[i];
			}
			file_to_delete[7]='\0';

			// Open boot list
			if(boot_file.open(&SD.root, BOOT_LIST, O_READ))
			{
				// Delete firmware file from SD
				if(!firm_file.remove(&SD.root, file_to_delete))
				{
					error=true;
				}
				firm_file.close();

				// Create auxiliary file called FILEAUX using the firm_file object
				if(!firm_file.open(&SD.root, file_aux, O_WRITE | O_CREAT | O_EXCL | O_SYNC | O_APPEND))
				{
					error=true;
				}

				// Algorithm to copy boot_list but the line we want to delete
				previous=millis();
				while( millis()-previous<60000 && !end_file)
				{
					// read 46 bytes from boot file and check the end of file
					if( (num_bytes=boot_file.read(buf_sd,sizeof(buf_sd))) <= 3)
					{
						end_file=true;
					}

					if( !end_file )
					{
						// copy boot line to auxiliar variable
						for(it=0;it<(sizeof(buf_sd));it++)
						{
							buf_sd_aux[it]=buf_sd[it];
						}
						buf_sd_aux[it]='\0';

						// check filename to be deleted and
						// mark lack of coincidence in that case
						for(int i=0; i<7; i++)
						{
							if(buf_sd_aux[i]!=file_to_delete[i])
							{
								match_id=false;
								break;
							}
						}
						if(!match_id)
						{
							// Write string to Auxiliar file: FILEAUX
							if( (uint16_t)firm_file.write(buf_sd_aux,strlen(buf_sd_aux))!=strlen(buf_sd_aux))
							{
								error=true;
							}
							else match_id = true;
						}
					}

					// avoid millis overflow problem
					if( millis() < previous ) previous=millis();
				}
				end_file=false;
				firm_file.close();
				boot_file.close();

				// Delete previous boot_list
				if(!boot_file.remove(&SD.root,BOOT_LIST)) error=true;

				// Create a new boot_list file and copy the content of auxiliary file
				if(!boot_file.open(&SD.root, BOOT_LIST, O_WRITE | O_CREAT | O_EXCL | O_SYNC | O_APPEND) )
				{
					error=true;
				}

				if(firm_file.open(&SD.root, file_aux, O_READ))
				{
					previous=millis();
					while( millis()-previous<60000 && !end_file)
					{
						if( (num_bytes=firm_file.read(buf_sd,sizeof(buf_sd))) <= 3)
						{
							end_file=true;
						}

						if( !end_file )
						{
							for(it=0;it<(sizeof(buf_sd));it++)
							{
								buf_sd_aux[it]=buf_sd[it];
							}
							buf_sd_aux[it]='\0';

							// Write string to file
							if( (uint16_t)boot_file.write(buf_sd_aux,strlen(buf_sd_aux))!=strlen(buf_sd_aux))
							{
								error=true;
							}
						}

						// avoid millis overflow problem
						if( millis() < previous ) previous=millis();
					}
					firm_file.close();
					firm_file.remove(&SD.root,file_aux);
				}
				else error=true;
			}
			else error=true;
		}
		else error=true;
	}
	else error=true;

	if(!error)
	{
		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=UNICAST;

		// copy destination mac address from received packet
		destination[0] = packet_finished[pos-1]->macSH[0];
		destination[1] = packet_finished[pos-1]->macSH[1];
		destination[2] = packet_finished[pos-1]->macSH[2];
		destination[3] = packet_finished[pos-1]->macSH[3];
		destination[4] = packet_finished[pos-1]->macSL[0];
		destination[5] = packet_finished[pos-1]->macSL[1];
		destination[6] = packet_finished[pos-1]->macSL[2];
		destination[7] = packet_finished[pos-1]->macSL[3];

		// DELETE_MESSAGE_OK
		strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[8])));
		if(buffer==NULL) return void(-1);

		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=DELETE_FRAME;
		data[4]='\0';
		strcat(data, buffer);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );

		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;
	}
	else
	{
		paq_sent=(packetXBee*) calloc(1,sizeof(packetXBee));
		paq_sent->mode=UNICAST;

		// copy destination mac address from received packet
		destination[0] = packet_finished[pos-1]->macSH[0];
		destination[1] = packet_finished[pos-1]->macSH[1];
		destination[2] = packet_finished[pos-1]->macSH[2];
		destination[3] = packet_finished[pos-1]->macSH[3];
		destination[4] = packet_finished[pos-1]->macSL[0];
		destination[5] = packet_finished[pos-1]->macSL[1];
		destination[6] = packet_finished[pos-1]->macSL[2];
		destination[7] = packet_finished[pos-1]->macSL[3];

		// DELETE_MESSAGE_ERROR
		strcpy_P(buffer, (char*)pgm_read_word(&(table_OTA[9])));
		if(buffer==NULL)return void(-1);

		// generate frame to send
		data[0]='<';
		data[1]='=';
		data[2]='>';
		data[3]=DELETE_FRAME;
		data[4]='\0';
		strcat(data, buffer);

		// set destination parameters
		setDestinationParams(paq_sent, destination, data);

		// delay random time
		delay( (rand()%delay_end + delay_start) );

		// Try to send the answer for several times
		for(int k=0; k<MAX_OTA_RETRIES; k++)
		{
		   if(!sendXBee(paq_sent)) k=MAX_OTA_RETRIES;
		   else delay(rand()%delay_end + delay_start);
		}
		free(paq_sent);
		paq_sent=NULL;
	}

	// close SD files
	boot_file.close();
	firm_file.close();
	SD.root.close();

	sd_on=0;
}


/*
 * Function: setMulticastConf
 *
 * set XBee configuration before OTA process using MULTICAST addressing.
 * Depending on the protocol case, it will be necessary to re-set one parameter
 * or another different.
 *
 */
void WaspXBeeCore::setMulticastConf()
{
	switch( firm_info.multi_type )
	{
		case 0	:	setChannel(firm_info.channel);
					writeValues();
					break;

		case 1	: 	// Set previous 'Auth key'
					for ( int i = 0; i < 8; i++)
					{
						eeprom_write_byte((unsigned char *) i+107, firm_info.authkey[i]);

					}
					break;

		case 2	: 	// set initial encryption mode
					setEncryptionMode(firm_info.encryptionMode);

					// set initial encryption key
					setLinkKey(firm_info.encryptionkey);
					writeValues();
					break;
	}
}


/*
 Function: Checks if timeout is up while sending program packets
 Returns: Integer that determines if there has been any error
   1 --> Timeout is up
   0 --> The function has been executed with no errors
*/
uint8_t WaspXBeeCore::checkOtapTimeout()
{
	long total_time;

	if( programming_ON )
   	{
		// Check millis crossing through zero. Don't count time till zero
		if( (millis() < firm_info.time_arrived) )
		{
			//restart counter
			total_time=millis();
		}
		else
		{
			total_time=millis()-firm_info.time_arrived;
		}

		// compare elapsed time to 'OTA_TIMEOUT'
		if( OTA_TIMEOUT < total_time )
		{
			// Reach Timeout
			programming_ON=0;
			firm_file.remove(&SD.root,firm_info.name_file);
			firm_info.packets_received=0;
			firm_info.paq_disordered=0;
			firm_info.already_init = 0;
			setMulticastConf();

			// flush uart
			serialFlush(uart);
			return 1;
	   }
   	}
	return 0;
}


/*
 * available ( void ) - Checks if there is available data in the correspondent
 * uart
 *
 * Returns: number of bytes available in the correspondent uart
 */
uint8_t WaspXBeeCore::available()
{
  	return serialAvailable(uart);
}


/*
 * flush ( void ) - clears the correspondent UART buffer
 *
 */
void WaspXBeeCore::flush()
{
  serialFlush(uart);
}




/*
 * gen_escaped_frame( TX, data, final_length) - It generates the correct API
 * frame from a non-eschaped one. This function is used by gen_send function
 * which sends the correct escaped frame to the XBee module.
 *
 * Parameters:
 * 	TX : pointer to the array where the correct escaped frame is stored
 * 	data : pointer to the actual non-escaped frame
 * 	final_length : pointer where the final frame length is stored
 *
 * Returns: void
 *
 * StartDelimiter(1B) + Length(2B) +  Frame Data(variable) + Checksum(1B)
 *  ______________     ___________     __________________     __________
 * |              |   |     |     |   |                  |   |          |
 * |     0x7E     | + | MSB | LSB | + |    Frame Data    | + |  1 Byte  |
 * |______________|   |_____|_____|   |__________________|   |__________|
 *
 */
void WaspXBeeCore::gen_escaped_frame(	uint8_t* TX,
										uint8_t* data,
										int* final_length)
{
	// Local variables
    int length=0;
    int escaped=0;

    // get 'Frame Data' length in 'Length' field
    length=data[1]*256+data[2];

    // increase length variable in: startDelimiter field (1B)+ length field (2B)
    // + checksum field (1B)
    length=length+1+2+1;

    // copy the start delimiter byte (0x7E)
    TX[0]=data[0];

    for(int i=1; i < length ; i++)
    {

		// check if character must be escaped
        if( data[i]==0x11 ||
			data[i]==0x13 ||
			data[i]==0x7D ||
			data[i]==0x7E   )
        {
			// set the escaped character mark: 0x7D
			TX[i+escaped]=0x7D;

			// increase number of escaped characters
            escaped++;

			switch (data[i])
			{
				case 0x11:	TX[i+escaped]=0x31;
							break;
				case 0x13:	TX[i+escaped]=0x33;
							break;
				case 0x7D:	TX[i+escaped]=0x5D;
							break;
				case 0x7E:	TX[i+escaped]=0x5E;
							break;
				default:	break;
			}
		}
		else
		{
			// it is not necessary to escape the character
			TX[i+escaped]=data[i];

		}

	}

	// once the conversion is made, set the final length of the frame adding
	// the number of extra bytes due to escaped characters
	*final_length=length+escaped;
}




/*
 * Function: receive a new xbee data packet
 *
 * Parameters:
 * 	timeout : milliseconds to wait until time-out before a packet arrives
 *
 * Returns: Integer that determines if there has been any error
 * 	'7' --> ERROR: Buffer full. not enough memory space
 * 	'6' --> ERROR: Error escaping character within payload bytes
 * 	'5' --> ERROR: Error escaping character in checksum byte
 * 	'4' --> ERROR: Checksum is not correct
 * 	'3' --> ERROR: Checksum byte is not available
 * 	'2' --> ERROR: Frame Type is not valid
 * 	'1' --> ERROR: timeout when receiving answer
 * 	'0' --> OK: The command has been executed with no errors
*/
int8_t WaspXBeeCore::receivePacketTimeout( uint32_t timeout)
{
	uint32_t previous;
	uint16_t frame_length = 0;
	uint16_t packet_length = 0; // Packet length with escaped bytes converted
	uint16_t i = 0;
	uint8_t c;
	bool escape_pending = false;
	bool packet_completed = false;
	uint8_t frameType = 0;
	uint8_t buffer[MAX_DATA] = {0};

	// clear packet structure
	memset( _payload, 0x00, sizeof(_payload) );
	memset( buffer, 0x00, sizeof(buffer) );

	// init previous
	previous = millis();

	// Perform the different steps within a given timeout
	while( (millis()-previous) < timeout )
	{
		// Read char
		if( available() )
		{
			c = serialRead(uart);

			// Frame init detected
			if( c == 0x7E )
			{
				i = 0;
				escape_pending = false;
			}
			else if ( c == 0x7D )
			{
				escape_pending = true;
				continue;
			}
			else
			{
				if (escape_pending == true)
				{
					c = c xor 0x20;
					escape_pending = false;
				}
			}
			buffer[i++] = c;

			// Compute length
			if (i == 3) frame_length = (uint16_t)(buffer[1] << 8) + (uint16_t)c;

			// Check if we have a complete packet
			else if (i == (frame_length + 4))
			{
				packet_completed = true;
				packet_length = i;
				break;
			}
			// Check if there is still room
			else if (i >= sizeof(buffer)) return 7;
		}
	}

	// Check if we got a complete packet
	if (!packet_completed)  return 1;

	// We have a complete packet
	// Verify checksum
	if (getChecksum(buffer) != buffer[packet_length-1])  return 4;

	// Depending on frame type extract payload and
	frameType = buffer[3];

	// calculate paylaod length
	if( frameType == 0x80 )
	{
		rxPacket80_t* received = (rxPacket80_t*) buffer;

		// substract header size
		_length = packet_length - 15 ;

		// copy payload
		memcpy( _payload, received->data, _length);

		// copy source mac address
		memcpy( _srcMAC, received->macS, sizeof(_srcMAC));

		// get rssi level
		_rssi = (int)received->rssi*(-1);
	}
	else if (frameType == 0x81)
	{
		rxPacket81_t* received = (rxPacket81_t*) buffer;

		// substract header size
		_length = packet_length - 9 ;

		// copy payload
		memcpy( _payload, received->data, _length);

		// copy source Network Address (MY)
		memcpy( _srcNA, received->naS, sizeof(_srcNA));

		// get rssi level
		_rssi = (int)received->rssi*(-1);
	}
	else if (frameType == 0x90)
	{
		rxPacket90_t* received = (rxPacket90_t*) buffer;

		// substract header size
		_length = packet_length - 16 ;

		// copy payload
		memcpy( _payload, received->data, _length);

		// copy source mac address
		memcpy( _srcMAC, received->macS, sizeof(_srcMAC));
	}
	else if (frameType == 0x91)
	{
		rxPacket91_t* received = (rxPacket91_t*) buffer;

		// substract header size
		_length = packet_length - 22 ;

		// copy payload
		memcpy( _payload, received->data, _length);

		// copy source mac address
		memcpy( _srcMAC, received->macS, sizeof(_srcMAC));
	}
	else
	{
		// ERROR: frameType not valid
		return 2;
	}

	return 0;
}









/*
 * Function: It sets the RTC settings with Meshlium timestamp configuration
 * This function sends a special Frame to Meshlium (Meshlium's MAC address must
 * be indicated as input), and then Meshlium returns an answer with the
 * timestamp. This function parses the info and sets the RTC Time and Date.
 *
 * Returns: Integer that determines if there has been any error
 * state = 2  --> ERROR: error receiving timestamp info
 * state = 1  --> ERROR: error sending timestamp request
 * state = 0  --> OK: The command has been executed with no errors
 */
uint8_t WaspXBeeCore::setRTCfromMeshlium(char* address)
{
	bool status = false;
	uint8_t error = 0;
	int result;
	char buffer[100];
	uint16_t year, yearH;
	uint16_t month;
	uint16_t date;
	uint16_t hour;
	uint16_t minute;
	uint16_t second;
	char sign;
	uint16_t	gmtHour;
	uint16_t	gmtMinute;
	packetXBee packet;
	int retries;

	// define the correct response length
	//(19B for something like "20150203144622+0000")
	uint16_t PATTERN_LENGTH = 19;

	// clear buffers
	memset( buffer, 0x00, sizeof(buffer) );
	memset( &packet, 0x00, sizeof(packet) );

	// Create frame to send
	uint8_t request[] = { 	0x3C, 0x3D, 0x3E, 0x9B, 0x00, 0x23, 0x33, 0x38, 0x37,
							0x32, 0x36, 0x34, 0x35, 0x33, 0x39, 0x23, 0x6E, 0x6F,
							0x64, 0x65, 0x31, 0x23, 0x30, 0x23};
	uint16_t requestLen = sizeof(request);

	// Choose transmission mode: UNICAST or BROADCAST
	packet.mode = UNICAST;

	// set destination XBee parameters to packet
	setDestinationParams( &packet, address, request, requestLen, MAC_TYPE);

	// flush rx buffer
	flush();

	// set retries to '3' attempts
	retries = 3;

	while( (retries > 0) && (status==false) )
	{

		/// SEND /////////////////////////////////////////////////

		// sending function
		sendXBee( &packet );

		// check tx flag
		if( error_TX == 0 )
		{
			status = true;
		}

		/// RECEIVE ///////////////////////////////////////////////

		if( status == true )
		{
			// wait for response
			int rx_error = receivePacketTimeout( 5000 );

			if( rx_error == 0 )
			{
				if( _length == PATTERN_LENGTH )
				{
					status = true;
					memcpy( buffer, _payload, _length);
				}
				else
				{
					status = false;
				}
			}
			else
			{
				status = false;
			}

			/// PARSE RESPONSE IF SUCCESS //////////////////////////////

			// check rx status
			if( status == true )
			{
				char question[100];

				// "%2u%2u%2u%2u%2u%2u%2u%c%2u%2u"
				strcpy_P(question, (char*)pgm_read_word(&(table_CORE[47])));
				if( question == NULL ) return 1;

				// get all data fields: "YYYYMMDDHHMMSS+0000"
				result = sscanf(buffer,
								question,
								&yearH,
								&year,
								&month,
								&date,
								&hour,
								&minute,
								&second,
								&sign,
								&gmtHour,
								&gmtMinute );

				if (result != 10)
				{
					return 1;
				}

				// check if valid date and time:
				if( (year > 0) 	&&
					(month > 0) &&
					(month < 13) &&
					(date > 0) 	&&
					(date < 32) &&
					(hour >= 0) &&
					(hour < 24) &&
					(minute >= 0) &&
					(minute < 60) &&
					(second >= 0) &&
					(second < 60) )
				{
					status = true;
				}
				else
				{
					status = false;
				}

				if( status == true)
				{
					// set new timestamp
					if (RTC.isON == 0)
					{
						RTC.ON();
					}
					error = RTC.setTime(year,
										month,
										date,
										RTC.dow(year, month, date),
										hour,
										minute,
										second	);

					if (error == 0) status = true;
					else status = false;
				}
			}
		}

		if( status == false )
		{
			// if error, wait for another retry
			retries--;
			delay(1000);
		}
	}


	if( status == false )
	{
		return 1;
	}

	return 0;
}





/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * This function performs application-level retries.
 * This function is only used for 64-bit addressing.
 *
 * return:
 * 	'0' OK
 * 	'1' error
 */
uint8_t WaspXBeeCore::send( uint8_t* macAddress, char* data )
{
	return send( 	(uint8_t*)macAddress,
					(uint8_t*)data,
					(uint16_t)strlen(data) );
}


/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * This function performs application-level retries.
 * This function is only used for 64-bit addressing.
 *
 * return:
 * 	'0' OK
 * 	'1' error
 */
uint8_t WaspXBeeCore::send( uint8_t* macAddress, uint8_t* pointer, uint16_t length )
{
	// define buffer to translate from hex array to string
	char macAddress_str[20]={};

	Utils.hex2str( (uint8_t*)macAddress, (char*)macAddress_str, 8);

	return send( macAddress_str, pointer, length );
}



/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * This function performs application-level retries.
 * This function is only used for 64-bit addressing.
 *
 * return:
 * 	'0' OK
 * 	'1' error
 */
uint8_t WaspXBeeCore::send( char* macAddress, char* data )
{
	return send( macAddress, (uint8_t*)data, (uint16_t)strlen(data) );
}

/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * This function performs application-level retries.
 * This function is only used for 64-bit addressing.
 *
 *
 * Return:
 * 	'0' OK
 * 	'1' error
 */
uint8_t WaspXBeeCore::send( char* macAddress, uint8_t* pointer, uint16_t length )
{
	// counter for retries
	uint8_t counter = 0;
	const uint8_t MAX_RETRIES = _send_retries;

	// Pointer to an XBee packet structure
	packetXBee packet;

	// clear buffer
	memset( &packet, 0x00, sizeof(packet) );

	// Choose transmission mode: UNICAST or BROADCAST
	packet.mode = UNICAST;

	if( strlen(macAddress) == 4 )
	{
		// XBee802 16-bit addressing
		// Set destination XBee parameters to packet
		setDestinationParams( &packet, macAddress, pointer, length, MY_TYPE);
	}
	else
	{
		// Set destination XBee parameters to packet
		setDestinationParams( &packet, macAddress, pointer, length);
	}

	// Send the packet until reach a successful transmision or reach
	// the specified number of retries
	while( counter <= MAX_RETRIES )
	{
		// Send XBee packet
		sendXBee( &packet );

		// Check TX flag
		if( error_TX == 0 )
		{
			// Send successful, exit the while loop
			return 0;
		}
		else
		{
			// Error transmitting the packet
			// wait for a random delay between 100 and 500 ms
			delay( (unsigned long)rand()%400LU + 100LU);
		}

		// increment counter
		counter++;
	}

	return 1;

}




/*
 * setSendingRetries
 *
 * Set the maximum number of Application-Level packet delivery attempts
 *
 * Parameters:
 * 	_send_retries: number of retries ( From 0 to 10)
*/
void WaspXBeeCore::setSendingRetries(uint8_t num)
{
    if( num > 10 )
    {
        _send_retries = 10;
    }
    else
    {
        _send_retries = num;
    }
}
