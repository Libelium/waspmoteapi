/*
 *  Library for managing managing the LoRaWAN module
 * 
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
 *  Version:		0.2
 *  Design:			David Gascón
 *  Implementation:	Luis Miguel Martí
 */
#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspLoRaWAN.h"

/******************************************************************************
 * FLASH DEFINITIONS COMMANDS
 ******************************************************************************/
 const char command_00[]	PROGMEM	= 	"sys reset\r\n";
 const char command_01[]	PROGMEM	= 	"sys factoryRESET\r\n";
 const char command_02[]	PROGMEM	= 	"sys get hweui\r\n";
 const char command_03[]	PROGMEM	= 	"sys get vdd\r\n";
 const char command_04[]	PROGMEM	= 	"mac reset %s\r\n";
 const char command_05[]	PROGMEM	= 	"mac tx cnf %u %s\r\n";
 const char command_06[]	PROGMEM	= 	"mac tx uncnf %u %s\r\n";
 const char command_07[]	PROGMEM	= 	"mac join abp\r\n";
 const char command_08[]	PROGMEM	= 	"mac save\r\n";
 const char command_09[]	PROGMEM	= 	"mac pause\r\n";
 const char command_10[]	PROGMEM	= 	"mac resume\r\n";
 const char command_11[]	PROGMEM	= 	"mac set devaddr %s\r\n";
 const char command_12[]	PROGMEM	= 	"mac set deveui %s\r\n";
 const char command_13[]	PROGMEM	= 	"mac set appeui %s\r\n";
 const char command_14[]	PROGMEM	= 	"mac set nwkskey %s\r\n";
 const char command_15[]	PROGMEM	= 	"mac set appskey %s\r\n";
 const char command_16[]	PROGMEM	= 	"mac set appkey %s\r\n";
 const char command_17[]	PROGMEM	= 	"mac set pwridx %u\r\n";
 const char command_18[]	PROGMEM	= 	"mac set dr %u\r\n";
 const char command_19[]	PROGMEM	= 	"mac set adr %s\r\n";
 const char command_20[]	PROGMEM	= 	"mac set ch freq %u %lu\r\n";
 const char command_21[]	PROGMEM	= 	"mac set ch dcycle %u %u\r\n";
 const char command_22[]	PROGMEM	= 	"mac set ch drrange %u %u %u\r\n";
 const char command_23[]	PROGMEM	= 	"mac set ch status %u %s\r\n";
 const char command_24[]	PROGMEM	= 	"mac get devaddr\r\n";
 const char command_25[]	PROGMEM	= 	"mac get deveui\r\n";
 const char command_26[]	PROGMEM	= 	"mac get appeui\r\n";
 const char command_27[]	PROGMEM	= 	"mac get dr\r\n";
 const char command_28[]	PROGMEM	= 	"mac get band\r\n";
 const char command_29[]	PROGMEM	= 	"mac get pwridx\r\n";
 const char command_30[]	PROGMEM	= 	"mac get adr\r\n";
 const char command_31[]	PROGMEM	= 	"mac get dcycleps\r\n";
 const char command_32[]	PROGMEM	= 	"mac get mrgn\r\n";
 const char command_33[]	PROGMEM	= 	"mac get gwnb\r\n";
 const char command_34[]	PROGMEM	= 	"mac get status\r\n";
 const char command_35[]	PROGMEM	= 	"mac get ch freq %u\r\n";
 const char command_36[]	PROGMEM	= 	"mac get ch dcycle %u\r\n";
 const char command_37[]	PROGMEM	= 	"mac get ch drrange %u\r\n";
 const char command_38[]	PROGMEM	= 	"mac get ch status %u\r\n";
 const char command_39[]	PROGMEM	= 	"radio rx 0\r\n";
 const char command_40[]	PROGMEM	= 	"radio tx %s\r\n";
 const char command_41[]	PROGMEM	= 	"radio cw on\r\n";
 const char command_42[]	PROGMEM	= 	"radio cw off\r\n";
 const char command_43[]	PROGMEM	= 	"radio set mod %s\r\n";
 const char command_44[]	PROGMEM	= 	"radio set freq %lu\r\n";
 const char command_45[]	PROGMEM	= 	"radio set pwr %u\r\n";
 const char command_46[]	PROGMEM	= 	"radio set sf %s\r\n";
 const char command_47[]	PROGMEM	= 	"radio set rxbw %s\r\n";
 const char command_48[]	PROGMEM	= 	"radio set rxbw %s.%s\r\n";
 const char command_49[]	PROGMEM	= 	"radio set bitrate %u\r\n";
 const char command_50[]	PROGMEM	= 	"radio set fdev %u\r\n";
 const char command_51[]	PROGMEM	= 	"radio set prlen %u\r\n";
 const char command_52[]	PROGMEM	= 	"radio set crc %s\r\n";
 const char command_53[]	PROGMEM	= 	"radio set cr %s\r\n";
 const char command_54[]	PROGMEM	= 	"radio set wdt %lu\r\n";
 const char command_55[]	PROGMEM	= 	"radio set bw %u\r\n";
 const char command_56[]	PROGMEM	= 	"radio get mod\r\n";
 const char command_57[]	PROGMEM	= 	"radio get freq\r\n";
 const char command_58[]	PROGMEM	= 	"radio get pwr\r\n";
 const char command_59[]	PROGMEM	= 	"radio get sf\r\n";
 const char command_60[]	PROGMEM	= 	"radio get rxbw\r\n";
 const char command_61[]	PROGMEM	= 	"radio get bitrate\r\n";
 const char command_62[]	PROGMEM	= 	"radio get cr\r\n";
 const char command_63[]	PROGMEM	= 	"radio get wdt\r\n";
 const char command_64[]	PROGMEM	= 	"radio get bw\r\n";
 const char command_65[]	PROGMEM	= 	"radio get snr\r\n";
 const char command_66[]	PROGMEM	= 	"radio get crc\r\n";
 const char command_67[]	PROGMEM	= 	"radio get prlen\r\n";
 const char command_68[]	PROGMEM	= 	"sys get ver\r\n";
 const char command_69[]	PROGMEM	= 	"mac set retx %u\r\n";
 const char command_70[]	PROGMEM	= 	"mac get retx\r\n";
 const char command_71[]	PROGMEM	= 	"radio get fdev\r\n";
 const char command_72[]	PROGMEM	= 	"mac set upctr %lu\r\n";
 const char command_73[]	PROGMEM	= 	"mac get upctr\r\n";
 const char command_74[]	PROGMEM	= 	"mac set dnctr %lu\r\n";
 const char command_75[]	PROGMEM	= 	"mac get dnctr\r\n";
 const char command_76[]	PROGMEM	= 	"mac join otaa\r\n";
 const char command_77[]	PROGMEM	= 	"mac set linkchk %u\r\n";


const char* const table_LoRaWAN_COMMANDS[] PROGMEM= 	  
{   
	command_00, 
	command_01,
	command_02,
	command_03,
	command_04,
	command_05,
	command_06,
	command_07,
	command_08,
	command_09,
	command_10,
	command_11,
	command_12,
	command_13,
	command_14,
	command_15,
	command_16,
	command_17,
	command_18,
	command_19,
	command_20,
	command_21,
	command_22,
	command_23,
	command_24,
	command_25,
	command_26,
	command_27,
	command_28,
	command_29,
	command_30,
	command_31,
	command_32,
	command_33,
	command_34,
	command_35,
	command_36,
	command_37,
	command_38,
	command_39,
	command_40,
	command_41,
	command_42,
	command_43,
	command_44,
	command_45, 
	command_46,
	command_47,
	command_48,
	command_49,
	command_50,
	command_51,
	command_52,
	command_53,
	command_54,
	command_55,
	command_56,
	command_57,
	command_58,
	command_59,
	command_60,
	command_61,
	command_62,
	command_63,
	command_64,
	command_65,
	command_66,
	command_67,     
	command_68,
	command_69,
	command_70,
	command_71,
	command_72,
	command_73,
	command_74,
	command_75,
	command_76,
	command_77
};

/******************************************************************************
 * FLASH DEFINITIONS ANSWERS
 ******************************************************************************/
 const char answer_00[]	PROGMEM	=	"ok";
 const char answer_01[]	PROGMEM	=	"invalid_param";
 const char answer_02[]	PROGMEM	=	"channel_busy";
 const char answer_03[]	PROGMEM	=	"mac_rx";
 const char answer_04[]	PROGMEM	=	"radio_tx_ok";
 const char answer_05[]	PROGMEM	=	"RN2483";
 const char answer_06[]	PROGMEM	=	"accepted";
 const char answer_07[]	PROGMEM	=	"radio_rx  ";
 const char answer_08[]	PROGMEM	=	"mac_tx_ok";
 const char answer_09[]	PROGMEM	=	"on";
 const char answer_10[]	PROGMEM	=	"off";
 const char answer_11[]	PROGMEM	=	"mac_paused";
 const char answer_12[]	PROGMEM	=	"radio_err";
 const char answer_13[]	PROGMEM	=	"\r\n";
 const char answer_14[]	PROGMEM	=	"4294967245";
 const char answer_15[]	PROGMEM	=	"mac_err";
 const char answer_16[]	PROGMEM	=	"invalid_data_len";
 const char answer_17[]	PROGMEM	=	"keys_not_init";
 const char answer_18[]	PROGMEM	=	"not_joined";
 


const char* const table_LoRaWAN_ANSWERS[] PROGMEM= 	  
{   
	answer_00, 
	answer_01,
	answer_02,
	answer_03,
	answer_04,
	answer_05,
	answer_06,
	answer_07,
	answer_08,
	answer_09,
	answer_10,
	answer_11,
	answer_12,
	answer_13,
	answer_14,
	answer_15,
	answer_16,
	answer_17,
	answer_18,
};


/******************************************************************************
 * User API
 ******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// System functions
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief	This function powers on the module
 * 
 * @param 	uint8_t	socket: socket to be used: SOCKET0 or SOCKET1
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::ON(uint8_t socket)
{
	uint8_t error;
	_baudrate = 57600;
	_uart = socket;

	OFF(socket);
	delay(200);

	if (socket == SOCKET0)
	{  
		_uart = SOCKET0;
		
		// Set multiplexer
		Utils.setMuxSocket0(); 

		// Open UART
		beginUART();
		
		// power up
		pinMode(XBEE_PW,OUTPUT);
		digitalWrite(XBEE_PW,HIGH);	
	}
	else
	{	
		// check RTC int pin to disable line in order to communicate
		if (digitalRead(RTC_INT_PIN_MON) == HIGH)
		{
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
		}
		
		_uart = SOCKET1;
		
		// Set multiplexer
		Utils.setMuxSocket1(); 
		
		// Open UART
		beginUART();
		
		// power up
		pinMode(DIGITAL6,OUTPUT);
		digitalWrite(DIGITAL6,HIGH);			
	}
	delay(300);
	error = check();
	return error;
}

/*!
 * @brief	This function powers down the module
 * 
 * @param 	uint8_t	socket: socket to be used: SOCKET0 or SOCKET1
 * 
 * @return	
 * 	@arg	'0' if OK
 */
uint8_t WaspLoRaWAN::OFF(uint8_t socket)
{
	if (socket == SOCKET0)
	{  
		_uart = SOCKET0;
		
		// Set multiplexer
		Utils.setMuxUSB(); 
		
		// close UART0
		closeUART();		
		
		// power down
		pinMode(XBEE_PW,OUTPUT);	
		digitalWrite(XBEE_PW, LOW);
	}
	else
	{	
		_uart = SOCKET1;
		
		// close UART1
		closeUART();
		
		// power down
		pinMode(DIGITAL6,OUTPUT);
		digitalWrite(DIGITAL6,LOW);			
	}
	
	return LORAWAN_ANSWER_OK;	
}
 
 
 

/*!
 * @brief	This function resets and restart the. Stored internal configurations
 * 			will be loaded upon reboot.
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'2' if no answer  
 * 
 */
uint8_t WaspLoRaWAN::reset()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "sys reset" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[0])));
	// create "RN2483" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,600);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function resets the module's configuration data and user
 * 			EEPROM to factory default values and restarts the module.
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'2' if no answer  
 * 
 */
uint8_t WaspLoRaWAN::factoryReset()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "sys factoryRESET" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[1])));
	// create "RN2483" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,5000);
	
	if (status == 1)
	{
		waitFor("\r\n",1000);
		return LORAWAN_ANSWER_OK;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets hardware EUI from the module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getEUI()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "sys get hweui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[2])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 0)
	{
		return LORAWAN_NO_ANSWER;
	}
	else if (status == 1)
	{		
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_eui,0x00,sizeof(_eui));
			strncpy(_eui, pch, sizeof(_eui));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}

/*!
 * @brief	This function gets hardware EUI from the module nad stores
 * 			last 4 byte as devAddres
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getAddr()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "sys get hweui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[2])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 0)
	{
		return LORAWAN_NO_ANSWER;
	}
	else if (status == 1)
	{		
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_devAddr,0x00,sizeof(_devAddr));
			strncpy(_devAddr, pch+8, sizeof(_devAddr));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}




/*!
 * @brief	This functions gets supply power from the module
 *
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getSupplyPower()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "sys get vdd" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[3])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{	
		_supplyPower = parseIntValue();
		if (_supplyPower == 0)
		{			
			return LORAWAN_ANSWER_ERROR;
		}		

		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	Checks if RN2483 module is ready
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 * 
 */ 
uint8_t WaspLoRaWAN::check()
{	
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "sys get ver" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[68])));
	// create "RN2483" command
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,1000);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




////////////////////////////////////////////////////////////////////////////////
// LoRaWAN functions
////////////////////////////////////////////////////////////////////////////////



/*! 
 * @brief	This function is used to reset LoRaWAN configuration and set working band.
 * 
 * @param	char* band: working LoRaWAN band: "433" or "868"
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::resetMacConfig(char* band)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac reset" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[4])), band);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,1000);

	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function gets hardware EUI and sets MAC devEUI
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDeviceEUI()
{
	uint8_t error = getEUI();
	
	if (error != 0)
	{
		return error;
	}	
	
	return setDeviceEUI(_eui);
}


/*! 
 * @brief	This function sets  MAC devEUI
 * 
 * @param	char* EUI: EUI to be set
 * 
 * @remarks	EUI is a sequence of digit representing the value of devEUI
 * 			expressed in hexadecimal value (i.e. EUI = 0004A30B001A836D 
 * 			– address is composed by the following byte stream: 
 * 			0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1A, 0x83, 0x6D - 16 digit 
 * 			converted in 8 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDeviceEUI(char* eui)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set deveui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[12])), eui);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);
	
	if (status == 1)
	{
		memset(_devEUI,0x00,sizeof(_devEUI));
		strncpy(_devEUI,eui,sizeof(_devEUI));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function gets the MAC device EUI from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getDeviceEUI()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get deveui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[25])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 0)
	{
		return LORAWAN_NO_ANSWER;
	}
	else if (status == 1)
	{		
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_devEUI,0x00,sizeof(_devEUI));
			strncpy(_devEUI, pch, sizeof(_devEUI));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}



/*! 
 * @brief	This function gets hardware EUI and sets MAC devAddress
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDeviceAddr()
{
	getAddr();
	return setDeviceAddr(_devAddr);
}



/*! 
 * @brief	This function sets  MAC devAddress
 * 
 * @param	char* addr: addr to be set
 * 
 * @remarks	addr is a sequence of digit representing the value of addres
 * 			expressed in hexadecimal value (i.e. addr = 001A836D – address
 * 			is composed by the following byte stream: 0x00, 0x1A, 0x83, 0x6D 
 * 			– 8 digit converted in 4 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDeviceAddr(char* addr)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set devaddr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[11])), addr);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		memset(_devAddr,0x00,sizeof(_devAddr));
		strncpy(_devAddr,addr,sizeof(_devAddr));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the MAC device Address from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getDeviceAddr()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get devaddr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[24])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 0)
	{
		return LORAWAN_NO_ANSWER;
	}
	else if (status == 1)
	{		
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_devAddr,0x00,sizeof(_devAddr));
			strncpy(_devAddr, pch, sizeof(_devAddr));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}



/*! 
 * @brief	This function sets  MAC Network Session Key
 * 
 * @param	char* key: key to be set
 * 
 * @remarks	key is a sequence of digit representing the value of NwkSKey
 * 			expressed in hexadecimal value (i.e. key = 000102030405060708091011121314
 *			32 digit converted in 16 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setNwkSessionKey(char* key)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set nwkskey" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[14])), key);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		memset(_nwkSKey,0x00,sizeof(_nwkSKey));
		strncpy(_nwkSKey,key,sizeof(_nwkSKey));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function sets  MAC appEUI
 * 
 * @param	char* EUI: EUI to be set
 * 
 * @remarks	EUI is a sequence of digit representing the value of appEUI
 * 			expressed in hexadecimal value (i.e.: EUI = 0001020304050607
 *			16 digit converted in 8 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setAppEUI(char* eui)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set appeui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[13])), eui);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		memset(_appEUI,0x00,sizeof(_appEUI));
		strncpy(_appEUI,eui,sizeof(_appEUI));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the MAC AppEUI from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getAppEUI()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get appeui" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[26])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 0)
	{
		return LORAWAN_NO_ANSWER;
	}
	else if (status == 1)
	{		
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_appEUI,0x00,sizeof(_appEUI));
			strncpy(_appEUI, pch, sizeof(_appEUI));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}


/*! 
 * @brief	This function sets  MAC App Key
 * 
 * @param	char* key: key to be set
 * 
 * @remarks	key is a sequence of digit representing the value of AppKey
 * 			expressed in hexadecimal value (i.e.: key = 000102030405060708091011121314
 *			32 digit converted in 16 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setAppKey(char* key)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set appkey" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[16])), key);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		memset(_appKey,0x00,sizeof(_appKey));
		strncpy(_appKey,key,sizeof(_appKey));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*! 
 * @brief	This function sets  MAC App Session Key
 * 
 * @param	char* key: key to be set
 * 
 * @remarks	key is a sequence of digit representing the value of AppSKey
 * 			expressed in hexadecimal value (i.e.: key = 000102030405060708091011121314
 *			32 digit converted in 16 bytes).
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setAppSessionKey(char* key)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set appskey" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[15])), key);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		memset(_appSKey,0x00,sizeof(_appSKey));
		strncpy(_appSKey,key,sizeof(_appSKey));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function is used to configure the LoRaWAN RF power level 
 * 
 * @param	uint8_t index: power level to be set [0..5] for 433 MHz
 * 			and [1..5] for 868 MHz	
 * 	@arg	0 -> 20 dBm (if supported)
 * 	@arg	1 -> 14 dBm
 * 	@arg	2 -> 11 dBm
 * 	@arg	3 -> 8 dBm
 * 	@arg	4 -> 5 dBm
 * 	@arg	5 -> 2 dBm
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setPower(uint8_t index)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set pwrindx" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[17])), index);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		_powerIndex = index;
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function is used to read the power index from module
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getPower()
{
	uint8_t status;	
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get pwrindx" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[29])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);

	if (status == 1)
	{
		_powerIndex = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*! 
 * @brief	This function is used to configure the LoRaWAN RF data rate
 * 
 * @param	uint8_t index: data rate to be set [0..7]	
 * 	@arg	0 -> Lora: SF 12 / 125 kHz		Bit/s: 250
 * 	@arg	1 -> Lora: SF 11 / 125 kHz		Bit/s: 440
 * 	@arg	2 -> Lora: SF 10 / 125 kHz		Bit/s: 980
 * 	@arg	3 -> Lora: SF 9 / 125 kHz		Bit/s: 1760
 * 	@arg	4 -> Lora: SF 8 / 125 kHz		Bit/s: 3125
 * 	@arg	5 -> Lora: SF 7 / 125 kHz		Bit/s: 5470
 * 	@arg	6 -> Lora: SF 7 / 250 kHz		Bit/s: 11000
 * 	@arg	7 -> 	FSK: 50kbps
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDataRate(uint8_t datarate)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set dr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[18])), datarate);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		_dataRate = datarate;
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function is used to read the data rate from module
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getDataRate()
{
	uint8_t status;	
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get dr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[27])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);

	if (status == 1)
	{
		_dataRate = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function saves config set into module's EEPROM
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::saveConfig()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac save" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[8])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,4000);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function joins module to a network
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 * 	@arg	'3' if keys were not initiated
 */
uint8_t WaspLoRaWAN::joinABP()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac join abp" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[7])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "keys_not_init" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[17])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);

	if (status == 1)
	{
		memset(ans1,0x00,sizeof(ans1));
		// create "accepted" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[6])));
		
		//wait for response
		if (waitFor(ans1,800) == 1)
		{
			return LORAWAN_ANSWER_OK;
		}
		else 
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else if (status == 3)
	{
		return LORAWAN_INIT_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function joins module to a network
 * 
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 *	@arg	'3' if keys were not initiated
 */
uint8_t WaspLoRaWAN::joinOTAA()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac join otaa" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[76])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "keys_not_init" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[17])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);

	if (status == 1)
	{
		memset(ans1,0x00,sizeof(ans1));
		// create "accepted" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[6])));
		
		//wait for response
		if (waitFor(ans1,20000) == 1)
		{
			return LORAWAN_ANSWER_OK;
		}
		else 
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else if (status == 3)
	{
		return LORAWAN_INIT_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * 
 * @brief	This function sends a LoRaWAN packet and waits for ACK
 * 	
 * @param 	char* data:	data to be sent
 * 			uint8_t port: port number to send data
 * 
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: payload =12A435 – the payload 
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes)
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 * 	@arg	'4' if there is data from server
 */
uint8_t WaspLoRaWAN::sendConfirmed(uint8_t port, char* payload)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	
	// clear data received flag
	_dataReceived = false;
	
	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac tx cnf <port> <data>" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[5])),port,payload);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "not_joined" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,1000);
	
	if (status == 1)
	{
		// clear buffer
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));
		memset(ans3,0x00,sizeof(ans3));
		memset(ans4,0x00,sizeof(ans4));
		
		// mac_rx
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
		// mac_tx_ok
		strcpy_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
		// mac_err
		strcpy_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));		
		// invalid_data_len
		strcpy_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));
		
		//wait for response
		status = waitFor(ans1, ans2, ans3, ans4, 20000);
		
		if (status == 1)
		{
			waitFor("/r/n",500);
			if (_length > 0)
			{
				char* pch = strtok((char*) _buffer," \r\n");
				_port = atoi(pch);
				
				pch = strtok(NULL," \r\n");
								
				memset(_data,0x00,sizeof(_data));
				strncpy(_data, pch, sizeof(_data)-1);
			
				saveConfig();
				_dataReceived = true;
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				saveConfig();
				return LORAWAN_ANSWER_OK;
			}
		}
		else if (status == 2)
		{
			saveConfig();
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 3)
		{
			saveConfig();
			return LORAWAN_SENDING_ERROR;
		}
		else if (status == 4)
		{
			saveConfig();
			return LORAWAN_LENGTH_ERROR;
		}
		else
		{
			saveConfig();
			return LORAWAN_NO_ANSWER;
		}
	}
	else if (status == 2)
	{
		saveConfig();
		return LORAWAN_ANSWER_ERROR;
	}
	else if (status == 3)
	{
		saveConfig();
		return LORAWAN_NOT_JOINED;
	}
	else
	{
		saveConfig();
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * 
 * @brief	This function sends a LoRaWAN packet without ACK
 * 	
 * @param 	char* data:	data to be sent
 * 			uint8_t port: port number to send data
 * 
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: payload =12A435 – the payload 
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes)
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::sendUnconfirmed(uint8_t port, char* payload)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	
	// clear data received flag
	_dataReceived = false;
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac tx uncnf <port> <data>" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[6])),port,payload);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "not_joined" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);

	if (status == 1)
	{
		// clear buffer
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));
		memset(ans3,0x00,sizeof(ans3));
		memset(ans4,0x00,sizeof(ans4));
			
		// mac_rx <port>
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
		// mac_tx_ok
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
		// mac_err
		sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));
		// invalid_data_len
		sprintf_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));
		
		//wait for response
		status = waitFor(ans1, ans2, ans3, ans4, 20000);
		
		if (status == 1)
		{
			waitFor("/r/n",500);
			
			if (_length > 0)
			{
				char* pch = strtok((char*) _buffer," \r\n");
				_port = atoi(pch);
				
				pch = strtok(NULL," \r\n");
								
				memset(_data,0x00,sizeof(_data));
				strncpy(_data, pch, sizeof(_data)-1);
			
				saveConfig();
				_dataReceived = true;
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				saveConfig();
				return LORAWAN_ANSWER_OK;
			}
		}
		else if (status == 2)
		{
			saveConfig();
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 3)
		{
			saveConfig();
			return LORAWAN_SENDING_ERROR;
		}
		else if (status == 4)
		{
			saveConfig();
			return LORAWAN_LENGTH_ERROR;
		}
		else
		{
			saveConfig();
			return LORAWAN_NO_ANSWER;
		}
	}
	else if (status == 2)
	{
		saveConfig();
		return LORAWAN_ANSWER_ERROR;
	}
	else if (status == 3)
	{
		saveConfig();
		return LORAWAN_NOT_JOINED;
	}
	else
	{
		saveConfig();
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function is used to set the ADR status from module
 * 
 * @param	char* state: "on"/"off"
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setADR(char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set adr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[19])),state);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
		
	if (status == 1)
	{
		if (strcmp(state, "on")  == 0) _adr = true;
		if (strcmp(state, "off") == 0) _adr = false;		
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function is used to read the ADR status from module
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getADR()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac get adr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[30])));
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);
	
	if (status == 1)
	{
		_adr = true;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		_adr = false;
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function is used to read the duty cycle prescaler from module
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getDutyCyclePrescaler()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get dcycle" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[31])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_dCyclePS = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*! 
 * @brief	This function pauses MAC functionality so the module is able
 * 			to use radio functions.
 * 
 * @remarks	This function must be called before using radio RX and TX
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::macPause()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac pause" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[9])));
	// create "4294967245" command
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[14])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}

/*! 
 * @brief	This function resumes MAC functionality
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::macResume()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac resume" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[10])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the frequency on the given channel ID
 * 
 * @param	uint32_t freq: frequency to be set [863250000..869750000]
 * 											   [433250000..434550000]
 * 			uint8_t channel: channel to be set [3..15]
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer  
 */
uint8_t WaspLoRaWAN::setChannelFreq(uint8_t channel, uint32_t freq)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	// check frequency settings
	if (freq < 433250000) return LORAWAN_ANSWER_ERROR;
	if ((freq > 434550000)&&(freq < 863250000)) return LORAWAN_ANSWER_ERROR;
	if (freq > 869750000) return LORAWAN_ANSWER_ERROR;	
	
	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set ch freq" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[20])),channel,freq);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_freq[channel] = freq;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the operating frequency on the given channel
 * 	
 * @param	uint8_t channel
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getChannelFreq(uint8_t channel)
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get ch freq" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[35])),channel);
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		_freq[channel] = parseValue(10);
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the duty cycle on the given channel ID
 * 
 * @param	uint16_t dcycle: frequency to be set [0..65535]
 * 			uint8_t channel: channel to be set [0..15]
 * 
 * @remarks	The "dcycle" value that needs to be configured can be obtained 
 * 			from the actual duty cycle X (in percentage) using the following formula:
 * 			dcycle = (100/X) – 1
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setChannelDutyCycle(uint8_t channel, uint16_t dcycle)
{
	uint8_t status;
	float dutycycle;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set ch dcycle" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[21])),channel,dcycle);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2);
	
	if (status == 1)
	{
		_dCycle[channel] = dcycle;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function gets the operating duty channel on the given channel
 * 	
 * @param	uint8_t channel
 * 
 * @remarks	The "dcycle" value obtained from the module helps us to calculate
 * 			duty cycle percentage "X" using the following formula:
 * 			dcycle = (100/X) – 1
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getChannelDutyCycle(uint8_t channel)
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get ch dcycle" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[36])),channel);
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		_dCycle[channel] = parseValue(10);
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function sets the data rate range on the given channel ID
 * 
 * @param	uint8_t minDR: datarate to be set [0..6]
 * 			uint8_t maxDR: datarate to be set [0..6]
 * 			uint8_t channel: channel to be set [0..15]
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setChannelDRRange(uint8_t channel, uint8_t minDR, uint8_t maxDR)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set ch drrange" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[22])),channel,minDR,maxDR);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_drrMin[channel] = minDR;
		_drrMax[channel] = maxDR;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function gets the data rate range on the given channel
 * 	
 * @param	uint8_t channel
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getChannelDRRange(uint8_t channel)
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get ch drrange" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[37])),channel);
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		char * pch;	
		pch = strtok((char*) _buffer," \r\n");
		if (pch != NULL)
		{
			_drrMin[channel] = strtoul(pch,NULL, 10);
			pch = strtok(NULL," \r\n");
			if (pch != NULL)
			{
				_drrMax[channel] = strtoul(pch,NULL, 10);
				pch = strtok(pch," \r\n");
				return LORAWAN_ANSWER_OK;
			}
			return LORAWAN_ANSWER_ERROR;
		}		
		return LORAWAN_ANSWER_ERROR;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function sets the status on the given channel ID
 * 
 * @param	char* state: state "on"/"off"
 * 			uint8_t channel: channel to be set [0..15]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setChannelStatus(uint8_t channel, char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set ch state" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[23])),channel,state);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_status[channel] = state;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the status of the given channel
 * 	
 * @param	uint8_t channel
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getChannelStatus(uint8_t channel)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "mac get ch status" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[38])),channel);
	// create "on" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
	// create "off" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);
	
	if (status == 1)
	{
		_status[channel] = true;
		return LORAWAN_ANSWER_OK;
	}
	if (status == 2)
	{
		_status[channel] = false;
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 3)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}





/*!
 * @brief	This function is used to configure number of retransmisions
 * 				for an uplink confirmed packet
 * 
 * @param	uint8_t retries: number of retries [0..255]
 * 	
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setRetries(uint8_t retries)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set retx" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[69])),retries);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);
	
	if (status == 1)
	{
		_retries = retries;
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function is used to read the power index from module
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getRetries()
{
	uint8_t status;	
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get retx" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[70])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);
	
	if (status == 1)
	{
		_retries = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}






/*! 
 * @brief	This function gets current band of operation
 * 
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getBand()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get band" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[28])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		memset(_band, 0x00, sizeof(_band));
		strncpy(_band,(char*)_buffer, sizeof(_band));
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function gets the demodulation margin from the module
 * 	
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getMargin()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get mrgn" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[32])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		uint8_t value = parseValue(10);
		_margin = value;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}

/*!
 * @brief	This function gets the number of gateways that successfully 
 * 			received the last Linck Check Request from the module
 * 	
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getGatewayNumber()
{
	uint8_t status;
	char ans1[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get gwnb" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[33])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,300);
	
	if (status == 1)
	{
		_gwNumber = parseValue(10);
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function sets the value of the uplink frame counter that will 
 * 			be used for the next uplink transmission.
 * 
 * @param	uint8_t counter: 
 * 	
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setUpCounter(uint32_t counter)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set upctr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[72])),counter);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_upCounter = counter;
		saveConfig();
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function is used to get the value of the uplink frame counter 
 * 			that will be used for the next uplink transmission.
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getUpCounter()
{
	uint8_t status;	
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get upctr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[73])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);
	
	if (status == 1)
	{
		_upCounter = parseValue(10);
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}





/*!
 * @brief	This function sets the value of the downlink frame counter that will 
 * 			be used for the next downlink transmission.
 * 
 * @param	uint8_t counter: 
 * 	
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setDownCounter(uint32_t counter)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set dnctr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[74])),counter);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_downCounter = counter;
		saveConfig();
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}

/*!
 * @brief	This function sets the time interval for the link check 
 * 			process to be triggered periodically
 * 
 * @param	uint8_t counter: 
 * 	
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setLinkCheck(uint16_t time)
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "mac set dnctr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[77])),time);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*! 
 * @brief	This function is used to get the value of the downlink frame counter 
 * 			that will be used for the next downlink transmission.
 * 
 * @return		
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getDownCounter()
{
	uint8_t status;	
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "mac get dnctr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[75])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);
	
	if (status == 1)
	{
		_downCounter = parseValue(10);
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}





////////////////////////////////////////////////////////////////////////////////
// Radio P2P functions
////////////////////////////////////////////////////////////////////////////////


/*!
 * @brief	Send a packet via radio
 * 
 * @param	char* message: char array that will be send
 * 
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e. radio tx 12A435 – the payload 
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 510 digit (255 Bytes)
 * 			for LoRa modulation and 128 digit (64 bytes) FSK modulation
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if there was an error
 * 	@arg	'2' if timeout
 * 
 */
uint8_t WaspLoRaWAN::sendRadio(char * message)
{	
	char ans1[15];
	char ans2[15];
	uint8_t status;
	
	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[40])), message);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,600);

	if (status == 1)
	{
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));
		
		// create "radio_tx_ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[4])));
		// create "radio_err" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[12])));
		
		//wait for response
		status = waitFor(ans1,ans2,3000);
		
		if (status == 1)
		{
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	Receive a packet via radio
 * 
 * @param	uint32_t timeout: time to wait for data
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if there was an error
 * 	@arg	'2' if timeout
 * 
 */
uint8_t WaspLoRaWAN::receiveRadio(uint32_t timeout)
{
	uint8_t error;	
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	char ans3[15];
		
	//set watch dog radio to timeout
	error = setRadioWDT(timeout);
	if (error == 0)
	{
		//start radio receiving
		memset(_command,0x00,sizeof(_command));
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));
		
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[39])));
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		
		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);
		
		if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			
			// create "radio_rx  " answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[7])));
			// create "\r\n" answer
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
			// create "radio_err" answer
			sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[12])));
			
			//wait for response
			status = waitFor(ans1,ans3,timeout);

			if (status == 1)
			{
				//wait for response
				status = waitFor(ans2,1000);
				
				_buffer[_length-1] = 0x00;
				_buffer[_length-2] = 0x00;
				_length -= 2;
				
				return LORAWAN_ANSWER_OK;
			}				
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	return LORAWAN_NO_ANSWER;
}
 
 
/*!
 * @brief	This function is used to radiate continuous wave without any modulation
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 
 */
uint8_t WaspLoRaWAN::test_ON()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[41])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	return LORAWAN_ANSWER_ERROR;
}


/*!
 * @brief	Stops the continuous wave mode, this function works with module 
 * 			identical to "reset()"
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 
 */
uint8_t WaspLoRaWAN::test_OFF()
{
	uint8_t status;	
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio cw off" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[42])));
	// create "RN2483" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	return LORAWAN_ANSWER_ERROR;
}



/*!
 * @brief	This function is used to read the SNR for the last receive packet
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::getRadioSNR()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get snr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[65])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);

	if (status == 1)
	{
		_radioSNR = parseValue(10);
		if (_radioSNR > 31)
		{
			_radioSNR = 64 - _radioSNR;
		}
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * 
 * @brief	This function sets spreading factor for radio mode
 * 	
 * @param 	char* sprfact:	spreading factor to be set [SF7..SF12]
 * 
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setRadioSF(char* sprfact)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set sf" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[46])),sprfact);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function gets the operating radio spreading factor from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioSF()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get sf" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[59])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		memset(_radioSF,0x00,sizeof(_radioSF));
		strncpy(_radioSF,(char*)_buffer,sizeof(_radioSF));
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * 
 * @brief	This function sets tx power for radio mode
 * 	
 * @param 	uint8_t pwr: power to be set [-3..15]
 * 	
 * @return		 
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer 
 */
uint8_t WaspLoRaWAN::setRadioPower(uint8_t pwr)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	// create "radio set pwr" command
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[45])),pwr);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else if (status = 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function gets the operating radio power from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioPower()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get pwr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[58])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioPower = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function sets the operating mode for transceiver use
 * 	
 * @param	char* mode: "lora"/"fsk"
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioMode(char* mode)
{
	uint8_t status;
	char ans1[50];
	char ans2[50];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set mod" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[43])),mode);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,300);
	
	if (status == 1)
	{
		memset(_radioMode, 0x00, sizeof(_radioMode));
		strncpy(_radioMode,mode,sizeof(_radioMode));
		return LORAWAN_ANSWER_OK;		
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the operating radio mode from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioMode()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get mod" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[56])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		memset(_radioMode,0x00,sizeof(_radioMode));
		strncpy(_radioMode, (char*)_buffer, sizeof(_radioMode));
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function sets the operating frequency for transceiver use
 * 	
 * @param	uint32_t freq: operating frequency [863250000..869750000]
 * 											   [433250000..434550000]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioFreq(uint32_t freq)
{
	uint8_t status;
	char ans1[50];
	char ans2[50];
	
	// check frequency settings
	if (freq < 433250000) return LORAWAN_ANSWER_ERROR;
	if ((freq > 434550000)&&(freq < 863250000)) return LORAWAN_ANSWER_ERROR;
	if (freq > 869750000) return LORAWAN_ANSWER_ERROR;	
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set freq" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[44])),freq);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_radioFreq = freq;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function gets the operating radio frequency from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioFreq()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get freq" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[57])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioFreq = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function sets the signal bandwidth for receiver use
 * 	
 * @param	float bandwidth: [250,125,62.5,31.3,15.6,7.8,3.9,200,100,50,25,
 * 							  12.5,6.3,3.1,166.7,83.3,41.7,20.8,10.4,5.2,2.6]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioReceivingBW(float bandwidth)
{
	uint8_t status;
	char bandw[6];
	char ans1[15];
	char ans2[15];
	char integer[4];
	char decimal[4];

	memset(_command,0x00,sizeof(_command));
	memset(bandw,0x00,sizeof(bandw));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(integer,0x00,sizeof(integer));
	memset(decimal,0x00,sizeof(decimal));

	dtostrf (bandwidth,NULL,1,bandw);
	
	char* pch = strtok(bandw,".\r\n");
	snprintf(integer, sizeof(integer), "%s",pch);
	pch = strtok(NULL,"\r\n");
	snprintf(decimal, sizeof(decimal), "%s",pch);
	
	if (decimal == "0")
	{
		// create "radio set rxbw" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[47])),integer);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		
		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);
	}
	else
	{	
		// create "radio set rxbw" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[48])),integer,decimal);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		
		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);
	}
		
	if (status == 1)
	{
		_radioRxBW = bandwidth;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the operating receiving bandwidth from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioReceivingBW()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get rxbw" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[60])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioRxBW = parseFloatValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the FSK bit rate value for transceiver use
 * 	
 * @param	uint16_t bitrate: [0..65535]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioBitRateFSK(uint16_t bitrate)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set bitrate" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[49])),bitrate);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_radioBitRate = bitrate;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function gets the bit rate for FSK modulation from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioBitRateFSK()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get bitrate" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[61])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioBitRate = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function sets the frequency deviation for transceiver use
 * 	
 * @param	uint16_t freqdeviation: [0..65535]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioFreqDeviation(uint16_t freqdeviation)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set fdev" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[50])),freqdeviation);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_radioFreqDev = freqdeviation;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}

/*!
 * @brief	This function gets the frequency deviation from the module
 * 	
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioFreqDeviation()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get fdev" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[66])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioFreqDev = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the CRC header state for transceiver use
 * 	
 * @param	uint16_t state: "on"/"off"
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioCRC(char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set crc" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[52])),state);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		if (state == ans1) _crcStatus = true;
		else _crcStatus = false;
		
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2) 
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}

/*!
 * @brief	This function gets the CRC header state from module
 * 	
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioCRC()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	
	// create "radio get crc" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[66])));
	// create "on" anwser
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
	// create "off" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);
	
	if (status == 1)
	{
		_crcStatus = true;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		_crcStatus = false;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 3)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the preamble length for transceiver use
 * 	
 * @param	uint16_t length: preamble length [0..65535]
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioPreamble(uint16_t length)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set prlen" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[51])),length);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_preambleLength = length;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the preamble length from module
 * 	
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioPreamble()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get prlen" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[67])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_preambleLength = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function sets the coding rate for transceiver use
 * 	
 * @param	char* codingrate: "4/5","4/6","4/7","4/8"
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioCR(char* codingrate)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set cr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[53])),codingrate);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		memset(_radioCR, 0x00, sizeof(_radioCR));
		strncpy(_radioCR,codingrate,sizeof(_radioCR));
		return LORAWAN_ANSWER_OK;
	}
	else  if (status == 2)
	{
		return LORAWAN_NO_ANSWER;
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}



/*!
 * @brief	This function gets the operating coding rate from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioCR()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get cr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[62])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,100);
	
	if (status == 1)
	{
		char* pch = strtok((char*)_buffer,"\r\n");
		if (pch != NULL)
		{
			memset(_radioCR, 0x00, sizeof(_radioCR));
			strncpy(_radioCR, pch, sizeof(_radioCR));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the time for the radio watch dog timer
 * 	
 * @param	uint32_t time: [0..4294967295] time in milliseconds
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioWDT(uint32_t time)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set wdt" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[54])),time);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_radioWDT = time;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function gets the watch dog timer's time from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioWDT()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get wdt" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[63])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioWDT = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}



/*!
 * @brief	This function sets the bandwidth for transceiver use
 * 	
 * @param	uint16_t bandwitdh: 125,250,500
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::setRadioBW(uint16_t bandwidth)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	
	// create "radio set bw" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[55])),bandwidth);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);
	
	if (status == 1)
	{
		_radioBW = bandwidth;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}




/*!
 * @brief	This function gets the operating radio bandwidth from module
 * 
 * @return	
 * 	@arg	'0' if OK
 * 	@arg	'1' if error 
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioBW()
{
	uint8_t status;
	char ans1[15];
	
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	
	// create "radio get bw" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[64])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	
	//send command and wait for ans
	status = sendCommand(_command,"\r\n",ans1,500);
	
	if (status == 1)
	{
		_radioBW = parseIntValue();
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else 
	{
		return LORAWAN_NO_ANSWER;
	}
}





////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief	This function parses a value 
 * @return	parsed value. '0' if nothing to parse
 */
uint32_t WaspLoRaWAN::parseValue(uint8_t base)
{
	char * pch;	
	pch = strtok((char*) _buffer," \r\n");
	if (pch != NULL)
	{
		return strtoul(pch,NULL, base);
	}
	return 0;
}


/*! 
 * @brief	This function parses a int value 
 * @return	parsed value. '0' if nothing to parse
 */			
uint32_t WaspLoRaWAN::parseIntValue()
{
	char * pch;	
	pch = strtok((char*) _buffer,"\r\n");
	if (pch != NULL)
	{
		return atol(pch);
	}
	return 0;
}


/*! 
 * @brief	This function parses a float value
 * @return	parsed value. '0' if nothing to parse
 */
float WaspLoRaWAN::parseFloatValue()
{
	char * pch;	
	pch = strtok((char*) _buffer,"\r\n");
	if (pch != NULL)
	{
		return atof(pch);
	}
	return 0;
}




// Preinstantiate Objects /////////////////////////////////////////////////////
WaspLoRaWAN LoRaWAN = WaspLoRaWAN();
