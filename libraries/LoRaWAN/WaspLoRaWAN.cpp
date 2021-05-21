/*
 *  Library for managing managing the LoRaWAN module
 *
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
 *  Version:		4.4
 *  Design:		David Gascón
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
 const char command_45[]	PROGMEM	= 	"radio set pwr %i\r\n";
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
 const char command_78[]	PROGMEM	= 	"mac set rx2 %u %lu\r\n";
 const char command_79[]	PROGMEM	= 	"mac set rxdelay1 %u\r\n";
 const char command_80[]	PROGMEM	= 	"mac reset\r\n";
 const char command_81[]	PROGMEM	= 	"mac get status\r\n";
 const char command_82[]	PROGMEM	= 	"mac tx cnf %u ";
 const char command_83[]	PROGMEM	= 	"mac tx uncnf %u ";
 const char command_84[]	PROGMEM	= 	"sys sleep %lu\r\n";
 const char command_85[]	PROGMEM	= 	"mac set ar %s\r\n";
 const char command_86[]	PROGMEM	= 	"mac get ar\r\n";
 const char command_87[]	PROGMEM	= 	"mac get rxdelay1\r\n";
 const char command_88[]	PROGMEM	= 	"mac get rxdelay2\r\n";
 const char command_89[]	PROGMEM	= 	"mac get rx2 %s\r\n";
 const char command_90[]	PROGMEM	= 	"mac get rx2\r\n";
 const char command_91[]	PROGMEM	= 	"mac set sync %x\r\n";
 const char command_92[]	PROGMEM	= 	"mac get sync\r\n";
 const char command_93[]	PROGMEM	= 	"radio tx ";
 const char command_94[]	PROGMEM	= 	"mac set bat %u\r\n";
 const char command_95[]	PROGMEM	= 	"mac get rx2 ISM_AS923_BRUNEI\r\n";

 const char command_96[]	PROGMEM	= 	"at+reboot\r";
 const char command_97[]	PROGMEM	= 	"at+dev?\r";
 const char command_98[]	PROGMEM	= 	"at+ver?\r";
 const char command_99[]	PROGMEM	= 	"at\r";
 const char command_100[]	PROGMEM	= 	"at+facnew\r";
 const char command_101[]	PROGMEM	= 	"at+deveui?\r";
 const char command_102[]	PROGMEM	= 	"at+deveui=%s\r";
 const char command_103[]	PROGMEM	= 	"at+rfparam?\r";
 const char command_104[]	PROGMEM	= 	"at+mode=%u\r";
 const char command_105[]	PROGMEM	= 	"at+join\r";
 const char command_106[]	PROGMEM	= 	"at+pctx %u,%u\r%s";
 const char command_107[]	PROGMEM	= 	"at+dformat=%u\r";
 const char command_108[]	PROGMEM	= 	"at+band=%u\r";
 const char command_109[]	PROGMEM	= 	"at+devaddr?\r";
 const char command_110[]	PROGMEM	= 	"at+appeui?\r";
 const char command_111[]	PROGMEM	= 	"at+nwkskey?\r";
 const char command_112[]	PROGMEM	= 	"at+appskey?\r";
 const char command_113[]	PROGMEM	= 	"at+appkey?\r";
 const char command_114[]	PROGMEM	= 	"at+devaddr=%s\r";
 const char command_115[]	PROGMEM	= 	"at+appeui=%s\r";
 const char command_116[]	PROGMEM	= 	"at+nwkskey=%s\r";
 const char command_117[]	PROGMEM	= 	"at+appskey=%s\r";
 const char command_118[]	PROGMEM	= 	"at+appkey=%s\r";
 const char command_119[]	PROGMEM	= 	"at+rfparam=%u,%lu,%u,%u\r";
 const char command_120[]	PROGMEM	= 	"at+dr=%u\r";
 const char command_121[]	PROGMEM	= 	"at+band?\r";
 const char command_122[]	PROGMEM	= 	"at+dr?\r";
 const char command_123[]	PROGMEM	= 	"at+dwell=0,0\r";
 const char command_124[]	PROGMEM	= 	"at+rfpower=%u,%u\r";
 const char command_125[]	PROGMEM	= 	"at+rfpower?\r";
 const char command_126[]	PROGMEM	= 	"at+putx %u,%u\r%s";
 const char command_127[]	PROGMEM	= 	"at+adr?\r";
 const char command_128[]	PROGMEM	= 	"at+adr=%u\r";
 const char command_129[]	PROGMEM	= 	"at+rtynum?\r";
 const char command_130[]	PROGMEM	= 	"at+rtynum=%u\r";
 const char command_131[]	PROGMEM	= 	"at+lncheck=0\r";
 const char command_132[]	PROGMEM	= 	"at+frmcnt?\r";
 const char command_133[]	PROGMEM	= 	"at+frmcnt=%lu,%lu\r";
 const char command_134[]	PROGMEM	= 	"at+rx2=%lu,%u\r";
 const char command_135[]	PROGMEM	= 	"at+rx2?\r";
 const char command_136[]	PROGMEM	= 	"at+delay=5000,6000,%d,%d\r";
 const char command_137[]	PROGMEM	= 	"at+delay?\r";
 const char command_138[]	PROGMEM	= 	"at+dformat?\r";
 const char command_139[]	PROGMEM	= 	"at+msize?\r";
 const char command_140[]	PROGMEM	= 	"at+chmask?\r";

 const char command_141[]	PROGMEM	= 	"radio get rssi\r\n";

 const char command_142[]	PROGMEM	= 	"at+dutycycle?\r";
 const char command_143[]	PROGMEM	= 	"at+dutycycle=%u\r";
 const char command_144[]	PROGMEM	= 	"at+cst?\r";
 const char command_145[]	PROGMEM	= 	"at+cst=%u\r";
 const char command_146[]	PROGMEM	= 	"at+rssith?\r";
 const char command_147[]	PROGMEM	= 	"at+rssith=%d\r";





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
	command_77,
	command_78,
	command_79,
	command_80,
	command_81,
	command_82,
	command_83,
	command_84,
	command_85,
	command_86,
	command_87,
	command_88,
	command_89,
	command_90,
	command_91,
	command_92,
	command_93,
	command_94,
	command_95,

	command_96,
	command_97,
	command_98,
	command_99,
	command_100,
	command_101,
	command_102,
	command_103,
	command_104,
	command_105,
	command_106,
	command_107,
	command_108,
	command_109,
	command_110,
	command_111,
	command_112,
	command_113,
	command_114,
	command_115,
	command_116,
	command_117,
	command_118,
	command_119,
	command_120,
	command_121,
	command_122,
	command_123,
	command_124,
	command_125,
	command_126,
	command_127,
	command_128,
	command_129,
	command_130,
	command_131,
	command_132,
	command_133,
	command_134,
	command_135,
	command_136,
	command_137,
    command_138,
	command_139,
	command_140,

	command_141,

	command_142,
	command_143,
    command_144,
    command_145,
    command_146,
    command_147,

};

/******************************************************************************
 * FLASH DEFINITIONS ANSWERS
 ******************************************************************************/
 const char answer_00[]	PROGMEM	=	"ok";
 const char answer_01[]	PROGMEM	=	"invalid_param";
 const char answer_02[]	PROGMEM	=	"no_free_ch";
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
 const char answer_19[]	PROGMEM	=	"denied";
 const char answer_20[]	PROGMEM	=	"RN2903";
 const char answer_21[]	PROGMEM	=	"India";
 const char answer_22[]	PROGMEM	=	"radio_rx "; // for india purpose only
 const char answer_23[]	PROGMEM	=	"AS923"; // for ASIA-PAC / LATAM purpose only

 const char answer_24[]	PROGMEM	=	"+EVENT=0,0";
 const char answer_25[]	PROGMEM	=	"ABZ-093";
 const char answer_26[]	PROGMEM	=	"+ERR=-1";
 const char answer_27[]	PROGMEM	=	"+ERR=-2";
 const char answer_28[]	PROGMEM	=	"+ERR=-3";
 const char answer_29[]	PROGMEM	=	"+ERR=-4";
 const char answer_30[]	PROGMEM	=	"+ERR=-5";
 const char answer_31[]	PROGMEM	=	"+ERR=-6";
 const char answer_32[]	PROGMEM	=	"+ERR=-7";
 const char answer_33[]	PROGMEM	=	"+ERR=-8";
 const char answer_34[]	PROGMEM	=	"+ERR=-9";
 const char answer_35[]	PROGMEM	=	"+ERR=-10";
 const char answer_36[]	PROGMEM	=	"+ERR=-11";
 const char answer_37[]	PROGMEM	=	"+ERR=-12";
 const char answer_38[]	PROGMEM	=	"+ERR=-13";
 const char answer_39[]	PROGMEM	=	"+ERR=-14";
 const char answer_40[]	PROGMEM	=	"+ERR=-14";
 const char answer_41[]	PROGMEM	=	"+ERR=-16";
 const char answer_42[]	PROGMEM	=	"+ERR=-17";
 const char answer_43[]	PROGMEM	=	"+ERR=-18";
 const char answer_44[]	PROGMEM	=	"+ERR=-19";
 const char answer_45[]	PROGMEM	=	"+ERR=-20";
 const char answer_46[]	PROGMEM	=	"+ERR=";
 const char answer_47[]	PROGMEM	=	"+OK";
 const char answer_48[]	PROGMEM	=	"+EVENT=0,1";
 const char answer_49[]	PROGMEM	=	"+OK=";
 const char answer_50[]	PROGMEM	=	"+EVENT=1,1";
 const char answer_51[]	PROGMEM	=	"+ACK";
 const char answer_52[]	PROGMEM	=	"+RECV=";
 const char answer_53[]	PROGMEM	=	";%u,";
 const char answer_54[]	PROGMEM	=	"+EVENT=2,";
 const char answer_55[]	PROGMEM	=	"+ANS=2,";
 const char answer_56[]	PROGMEM	=	"+EVENT=1,0";




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
	answer_19,
	answer_20,
	answer_21,
	answer_22,
	answer_23,

	answer_24,
	answer_25,
	answer_26,
	answer_27,
	answer_28,
	answer_29,
	answer_30,
	answer_31,
	answer_32,
	answer_33,
	answer_34,
	answer_35,
	answer_36,
	answer_37,
	answer_38,
	answer_39,
	answer_40,
	answer_41,
	answer_42,
	answer_43,
	answer_44,
	answer_45,
	answer_46,
	answer_47,
	answer_48,
	answer_49,
	answer_50,
	answer_51,
	answer_52,
	answer_53,
	answer_54,
	answer_55,
	answer_56,

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

	// select multiplexer
    if (_uart == SOCKET0) 	Utils.setMuxSocket0();
    if (_uart == SOCKET1) 	Utils.setMuxSocket1();

	// Open UART
	beginUART();

    // power on the socket
    PWR.powerSocket(_uart, HIGH);

	delay(500);
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
	_uart = socket;

	// close uart
	closeUART();

	// unselect multiplexer
    if (_uart == SOCKET0) Utils.setMuxUSB();
    if (_uart == SOCKET1) Utils.muxOFF1();

	// switch module OFF
	PWR.powerSocket(_uart, LOW);

	return LORAWAN_ANSWER_OK;
}




/*!
 * @brief	This function resets and restart the stored internal configurations
 * 			will be loaded upon reboot and saves modules version.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *
 */
uint8_t WaspLoRaWAN::reset()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "sys reset" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[0])));
		// create "RN2483" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
		// create "RN2903" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[20])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,600);

		if (status == 1)
		{
			_version = RN2483_MODULE;
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			_version = RN2903_MODULE;

			// create "India" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[21])));
			// create "ASIA-PAC / LATAM" answer
			memset(ans2,0x00,sizeof(ans2));
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[23])));

			status = waitFor(ans1,ans2);

			if(status == 1)
			{
				_version = RN2903_IN_MODULE;
			}
			else if (status == 2)
			{
				_version = RN2903_AS_MODULE;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			_version = 0;
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+reboot" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[96])));
		// create "+EVENT=0,0" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[24])));
		// create "+ERR=-1" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[26])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 1000);
		if (status == 1)
		{
			_version = ABZ_MODULE;
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			_version = ABZ_MODULE;
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			_version = 0;
			return LORAWAN_NO_ANSWER;
		}
	}
}


/*!
 * @brief	This function resets the module's configuration data and user
 * 			EEPROM to factory default values, restarts the module and saves
 * 			modules version.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *
 */
uint8_t WaspLoRaWAN::factoryReset()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "sys factoryRESET" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[1])));
		// create "RN2483" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
		// create "RN2903" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[20])));


		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,5000);

		if (status == 1)
		{
			_version = RN2483_MODULE;
			delay(100);
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			_version = RN2903_MODULE;

			// create "India" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[21])));
			// create "ASIA-PAC / LATAM" answer
			memset(ans2,0x00,sizeof(ans2));
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[23])));

			status = waitFor(ans1,ans2);

			if(status == 1)
			{
				_version = RN2903_IN_MODULE;
			}
			else if (status == 2)
			{
				_version = RN2903_AS_MODULE;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+facnew" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[100])));
		// create "+EVENT=0,0" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[24])));
		// create "+ERR=-1" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[26])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 5000);

		if (status == 1)
		{
			_version = ABZ_MODULE;
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			_version = ABZ_MODULE;
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			_version = 0;
			return LORAWAN_NO_ANSWER;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "sys get hweui" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[2])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			char* pch = strtok((char*)_buffer,ans1);
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
	else
	{
		// create "at+deveui?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[101])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			status = waitFor("\r\n", ans2, 500);

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
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "sys get hweui" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[2])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			char* pch = strtok((char*)_buffer,ans1);
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
	else
	{
		// create "at+devaddr?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[109])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			status = waitFor("\r\n", ans2, 500);

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
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "sys get vdd" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[3])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 * @brief	Checks if module is ready to use and saves which kind of
 * 			module has been plugged to Waspmote, either RN2483 or RN2903
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
	char ans3[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));

	// create "sys get ver" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[68])));
	// create "RN2483" command
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	// create "RN2903" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[20])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3, 2000);

	if (status == 1)
	{
		_version = RN2483_MODULE;
		return LORAWAN_ANSWER_OK;
	}
	if (status == 2)
	{
		_version = RN2903_MODULE;

		// create "India" answer
		memset(ans1,0x00,sizeof(ans1));
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[21])));
		// create "ASIA-PAC / LATAM" answer
		memset(ans2,0x00,sizeof(ans2));
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[23])));

		status = waitFor(ans1,ans2,100);

		if(status == 1)
		{
			_version = RN2903_IN_MODULE;
		}
		else if (status == 2)
		{
			_version = RN2903_AS_MODULE;
		}

		return LORAWAN_ANSWER_OK;
	}
	else if (status == 3)
	{
		return LORAWAN_ANSWER_ERROR;
	}
	else
	{
		_baudrate = 19200;

		OFF(_uart);
		delay(500);

		//pinMode(47, OUTPUT);
		//digitalWrite(47,HIGH);

		// select multiplexer
		  if (_uart == SOCKET0) 	Utils.setMuxSocket0();
		  if (_uart == SOCKET1) 	Utils.setMuxSocket1();

		// power on the socket
		PWR.powerSocket(_uart, HIGH);
		delay(1000);

        // Open UART
        beginUART();
        delay(100);

        serialFlush(_uart);

		memset(_command,0x00,sizeof(_command));
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));

		// create "at+dev?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[97])));
		// create "ABZ-093" command
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[25])));
		// create "+ERR=-1" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[26])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2, 1000);

		if (status == 1)
		{
			_version = ABZ_MODULE;
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
}



/*!
 * @brief	Displays the module's firmware version via USB port
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *
 */
void WaspLoRaWAN::showFirmwareVersion()
{
    uint8_t status;
	char ans1[5];
    char ans2[5];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
    memset(ans2,0x00,sizeof(ans2));

    if (_version != ABZ_MODULE)
	{
        // create "sys get ver" command
        sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[68])));
        // create "\r\n" answer
        sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

        //send command and wait for ans
        status = sendCommand(_command,ans1,1000);

        USB.print(F("Firmware version: "));
        USB.print((char*)_buffer);
    }
    else
    {
        // create "at+ver?" command
        sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[98])));
        // create "+OK=" answer
        sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
        // create "+ERR" answer
        sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

        //send command and wait for ans
        status = sendCommand(_command,ans1,ans2,500);

        if (status == 1)
        {
            waitFor("OK=", 500);
            waitFor("\r\n", 500);
            USB.print(F("Firmware version: "));
            USB.print((char*)_buffer);
        }
    }
}






////////////////////////////////////////////////////////////////////////////////
// LoRaWAN functions
////////////////////////////////////////////////////////////////////////////////



/*!
 * @brief	This function is used to reset LoRaWAN configuration and set working band.
 *
 * @param	char* band: working LoRaWAN band: "433", EU or US
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::resetMacConfig(char* band)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if ((strcmp(band, "433")) && (strcmp(band, "868")) && (strcmp(band, "900")))
	{
		return LORAWAN_INPUT_ERROR;
	}

	if (!strcmp(band, "433") && (_version == RN2903_IN_MODULE))
	{
		return LORAWAN_INPUT_ERROR;
	}

	if (_version == RN2903_MODULE)
	{
		// create "mac reset" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[80])));
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}

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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setDeviceEUI(char* eui)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check eui length
	if (strlen(eui)!=16) return LORAWAN_INPUT_ERROR;

	// check if eui is a hexadecimal string
	for (uint8_t i=0;i<16;i++)
	{
		if (((eui[i] < '0') || (eui[i] > '9')) &&
			((eui[i] < 'A') || (eui[i] > 'F')) &&
			((eui[i] < 'a') || (eui[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

    if (_version == ABZ_MODULE)
    {
        // Get Device EUI
        status = getDeviceEUI();
        if( status == 0 )
        {
            USB.println(F("[LoRaWAN] LoRaWAN JP/KR module does not support setDeviceEUI() function."));
            USB.print(F("[LoRaWAN] It is mandatory to use the hardware Device EUI: "));
            USB.println(_devEUI);
            return LORAWAN_ANSWER_OK;
        }
        else
        {
            USB.println(F("[LoRaWAN] LoRaWAN JP/KR module does not support setDeviceEUI() function."));
            USB.println(F("[LoRaWAN] It is mandatory to use the hardware Device EUI: "));
            USB.print(F("[LoRaWAN] Get Device EUI error = "));
            USB.println(status, DEC);
            return LORAWAN_ANSWER_ERROR;
        }

    }
	else
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
}

/*!
 * @brief	This function sets  hardware MAC devEUI
 *
 * @param	char* EUI: EUI to be set
 *
 * @remarks	EUI is a sequence of digit representing the value of devEUI
 * 			expressed in hexadecimal value (i.e. EUI = 0004A30B001A836D
 * 			– address is composed by the following byte stream:
 * 			0x00, 0x04, 0xA3, 0x0B, 0x00, 0x1A, 0x83, 0x6D - 16 digit
 * 			converted in 8 bytes).
 *
 *          Device EUI is hard coded in production line. End customer
 *          should NOT modify device EUI. Device EUI will be not be
 *          restored in factoryReset() function
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setEUI(char* eui)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check eui length
	if (strlen(eui)!=16) return LORAWAN_INPUT_ERROR;

	// check if eui is a hexadecimal string
	for (uint8_t i=0;i<16;i++)
	{
		if (((eui[i] < '0') || (eui[i] > '9')) &&
			((eui[i] < 'A') || (eui[i] > 'F')) &&
			((eui[i] < 'a') || (eui[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
        USB.println(F("[LoRaWAN] setEUI() function overwrites the hardware Device EUI and"));
        USB.println(F("[LoRaWAN] it cannot be recovered using the factoryReset() function"));
        delay(500);

		// create "at+deveui=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[102])), eui);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_devEUI,0x00,sizeof(_devEUI));
			strncpy(_devEUI,eui,sizeof(_devEUI));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get deveui" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[25])));
		// create "invalid_param" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			char* pch = strtok((char*)_buffer,ans1);
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
	else
	{
		// create "at+deveui?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[101])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			status = waitFor("\r\n", ans2, 500);

			char* pch = strtok((char*)_buffer,"\r\n");
			if (pch != NULL)
			{
				memset(_devEUI,0x00,sizeof(_devEUI));
				strncpy(_devEUI, pch, sizeof(_devEUI));
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				//print error
				//~ waitFor("\r");
				//~ USB.print(F("Error: "));
				//~ USB.println((char*)_buffer);
				return LORAWAN_ANSWER_ERROR;
			}
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setDeviceAddr(char* addr)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check addr length
	if (strlen(addr)!=8) return LORAWAN_INPUT_ERROR;

	// check if addr is a hexadecimal string
	for (uint8_t i=0;i<8;i++)
	{
		if (((addr[i] < '0') || (addr[i] > '9')) &&
			((addr[i] < 'A') || (addr[i] > 'F')) &&
			((addr[i] < 'a') || (addr[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+devaddr=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[114])), addr);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_devAddr,0x00,sizeof(_devAddr));
			strncpy(_devAddr,addr,sizeof(_devAddr));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get devaddr" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[24])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			char* pch = strtok((char*)_buffer,ans1);
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
	else
	{
		// create "at+devaddr?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[109])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			status = waitFor("\r\n", ans2, 500);

			char* pch = strtok((char*)_buffer,"\r\n");
			if (pch != NULL)
			{
				memset(_devAddr,0x00,sizeof(_devAddr));
				strncpy(_devAddr, pch, sizeof(_devAddr));
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				//print error
				//~ waitFor("\r");
				//~ USB.print(F("Error: "));
				//~ USB.println((char*)_buffer);
				return LORAWAN_ANSWER_ERROR;
			}
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setNwkSessionKey(char* key)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check key length
	if (strlen(key)!=32) return LORAWAN_INPUT_ERROR;

	// check if key is a hexadecimal string
	for (uint8_t i=0;i<32;i++)
	{
		if (((key[i] < '0') || (key[i] > '9')) &&
			((key[i] < 'A') || (key[i] > 'F')) &&
			((key[i] < 'a') || (key[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+nwkskey=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[116])), key);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_nwkSKey,0x00,sizeof(_nwkSKey));
			strncpy(_nwkSKey,key,sizeof(_nwkSKey));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setAppEUI(char* eui)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check eui length
	if (strlen(eui)!=16) return LORAWAN_INPUT_ERROR;

	//check if eui is a hexadecimal string
	for (uint8_t i=0;i<16;i++)
	{
		if (((eui[i] < '0') || (eui[i] > '9')) &&
			((eui[i] < 'A') || (eui[i] > 'F')) &&
			((eui[i] < 'a') || (eui[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+appeui=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[115])), eui);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_appEUI,0x00,sizeof(_appEUI));
			strncpy(_appEUI,eui,sizeof(_appEUI));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get appeui" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[26])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			char* pch = strtok((char*)_buffer,ans1);
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
	else
	{
		// create "at+appeui?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[110])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			status = waitFor("\r\n", ans2, 500);

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
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setAppKey(char* key)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check key length
	if (strlen(key)!=32) return LORAWAN_INPUT_ERROR;

	//check if key is a hexadecimal string
	for (uint8_t i=0;i<32;i++)
	{
		if (((key[i] < '0') || (key[i] > '9')) &&
			((key[i] < 'A') || (key[i] > 'F')) &&
			((key[i] < 'a') || (key[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+appkey=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[118])), key);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_appKey,0x00,sizeof(_appKey));
			strncpy(_appKey,key,sizeof(_appKey));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setAppSessionKey(char* key)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check key length
	if (strlen(key)!=32) return LORAWAN_INPUT_ERROR;

	// check if key is a hexadecimal string
	for (uint8_t i=0;i<32;i++)
	{
		if (((key[i] < '0') || (key[i] > '9')) &&
			((key[i] < 'A') || (key[i] > 'F')) &&
			((key[i] < 'a') || (key[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+appskey=" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[117])), key);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_appSKey,0x00,sizeof(_appSKey));
			strncpy(_appSKey,key,sizeof(_appSKey));
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
	}
}




/*!
 * @brief	This function is used to configure the LoRaWAN RF power level
 *
 * @param	uint8_t index: power level to be set [0..5] for 433 MHz,
 * 			[1..5] for EU and [5..10] for US
 *
 *  @arg	0 -> 20 dBm (if supported)
 * 	@arg	1 -> 14 dBm
 * 	@arg	2 -> 11 dBm
 * 	@arg	3 -> 8 dBm
 * 	@arg	4 -> 5 dBm
 * 	@arg	5 -> 2 dBm
 *
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'7' if input parameter error
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setPower(uint8_t index)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
				getBand();

				switch (atol(_band))
				{
					case 868:
							if ((index > 5) || (index < 1)) return LORAWAN_INPUT_ERROR;
							else break;

					case 433:
							if (index > 5) return LORAWAN_INPUT_ERROR;
							else break;

					default:
							return LORAWAN_VERSION_ERROR;
				}
				break;

		case RN2903_MODULE:
				if ( index > 10 || index < 5 || index == 6) return LORAWAN_INPUT_ERROR;
				else break;

		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
				if ( index > 5 || index < 0) return LORAWAN_INPUT_ERROR;
				else break;

		case ABZ_MODULE:
				if ( index > 7 || index < 0) return LORAWAN_INPUT_ERROR;
				else break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac set pwrindx" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[17])), index);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);
	}
	else
	{
        if (index == 0 && _bandABZ == 0)
        {
            // create "at+rfpower=1,%u\r" command
            sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[124])), 1, index);
            // create "+OK" answer
            sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
            // create "+ERR=" answer
            sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

            //send command and wait for ans
            status = sendCommand(_command,ans1,ans2,100);
        }
        else
        {
            // create "at+rfpower=0,%u\r" command
            sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[124])), 0, index);
            // create "+OK" answer
            sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
            // create "+ERR=" answer
            sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

            //send command and wait for ans
            status = sendCommand(_command,ans1,ans2,100);
        }

	}

	if (status == 1)
	{
		_powerIndex = index;
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get pwrindx" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[29])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);
	}
	else
	{
		// create "at+rfpower?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[125])));
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);
		if (status == 1)
		{
			waitFor(",",100);
			waitFor("\r",100);
		}
	}

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
 * @param	uint8_t index: data rate to be set [0..7] (RN2483)(ABZ_MODULE)
 * 	@arg	0 -> Lora: SF 12 / 125 kHz		Bit/s: 250
 * 	@arg	1 -> Lora: SF 11 / 125 kHz		Bit/s: 440
 * 	@arg	2 -> Lora: SF 10 / 125 kHz		Bit/s: 980
 * 	@arg	3 -> Lora: SF 9 / 125 kHz		Bit/s: 1760
 * 	@arg	4 -> Lora: SF 8 / 125 kHz		Bit/s: 3125
 * 	@arg	5 -> Lora: SF 7 / 125 kHz		Bit/s: 5470
 * 	@arg	6 -> Lora: SF 7 / 250 kHz		Bit/s: 11000
 * 	@arg	7 -> 	FSK: 50kbps
 *
 * 			uint8_t index: data rate to be set [0..4] (RN2903)
 * 	@arg	0 -> Lora: SF 10 / 125 kHz		Bit/s: 980
 * 	@arg	1 -> Lora: SF 9 / 125 kHz		Bit/s: 1760
 * 	@arg	2 -> Lora: SF 8 / 125 kHz		Bit/s: 3125
 * 	@arg	3 -> Lora: SF 7 / 125 kHz		Bit/s: 5470
 * 	@arg	4 -> Lora: SF 8 / 500 kHz		Bit/s: 12500
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'7' if input parameter error
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setDataRate(uint8_t datarate)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
		case ABZ_MODULE:
				if (datarate > 7) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_MODULE:
				if (datarate > 4) return LORAWAN_INPUT_ERROR;
				break;
		default:
				return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac set dr" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[18])), datarate);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,200);

		if (status == 1)
		{
			_dataRate = datarate;
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
	else
	{
		// create "at+dr=%u\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[120])),datarate);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 1)
		{
			_dataRate = datarate;
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_NO_ANSWER;
		}
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
	char ans1[5];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get dr" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[27])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);

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
	else
	{
		// create "at+dr?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[122])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_dataRate = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
	}
}



/*!
 * @brief	This function saves config set into module's EEPROM
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if module does not support function
 */
uint8_t WaspLoRaWAN::saveConfig()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

  if (_version == ABZ_MODULE)
  {
    // Function not available for Murata mudule
    return LORAWAN_ANSWER_OK;
  }

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version == ABZ_MODULE) return LORAWAN_ANSWER_OK;

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
		status = LoRaWAN.getUpCounter();
		if (status == 0)
		{
			status = LoRaWAN.getDownCounter();
			if (status == 0)
			{
				return LORAWAN_ANSWER_OK;
			}

			return LORAWAN_ANSWER_ERROR;
		}

		return LORAWAN_ANSWER_ERROR;
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
	if(_OTAAError<=1)
	{
		uint8_t status;
		char ans1[15];
		char ans2[15];
		char ans3[15];

		memset(_command,0x00,sizeof(_command));
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));
		memset(ans3,0x00,sizeof(ans3));
	
		if (_version != ABZ_MODULE)
		{
			if (_syncWord != 0) setSyncWord(_syncWord);
			
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
					setUpCounter(_upCounter);
					setDownCounter(_downCounter);
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
		else
		{
			// create "at+mode=0" command
			sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[104])),0);
			// create "+OK" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
			// create "+ERR" answer
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

			//send command and wait for ans
			status = sendCommand(_command,ans1, ans2, 500);

			if (status == 0)
			{
				return LORAWAN_NO_ANSWER;
			}
			else if (status == 1)
			{
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				//print error
				//~ waitFor("\r");
				//~ USB.print(F("Error: "));
				//~ USB.println((char*)_buffer);
				return LORAWAN_ANSWER_ERROR;
			}
		}
	}
	else
	{
		USB.println(F("--------------------------------------------------------------------"));
		USB.println(F("---LoRaWAN: Conection not allowed. The OTAA previous attempt failed."));
		USB.println(F("---LoRaWAN: Check OTAA parameters and restart the code."));
		USB.println(F("--------------------------------------------------------------------"));
		return LORAWAN_NOT_JOINED;
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
    char ans4[15];
	uint8_t dev_addr[] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00};
	uint8_t nwk_s_key[] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00};
	uint8_t app_s_key[] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00};

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));


	if (_version != ABZ_MODULE)
	{
		
		if (_syncWord != 0) setSyncWord(_syncWord);

		//initialize devAddr so field is not empty
		status = setDeviceAddr((char*)dev_addr);
		if ( status != 0)
		{
			return LORAWAN_ANSWER_ERROR;
		}

		//initialize NwkSKey so field is not empty
		status = setNwkSessionKey((char*)nwk_s_key);
		if ( status != 0)
		{
			return LORAWAN_ANSWER_ERROR;
		}

		//initialize AppSKey so field is not empty
		status = setAppSessionKey((char*)app_s_key);
		if ( status != 0)
		{
			return LORAWAN_ANSWER_ERROR;
		}


		// try to join via OTAA
		int retries = 3;
		do
		{
			// create "mac join otaa" command
			sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[76])));
			// create "ok" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
			// create "invalid_param" answer
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
			// create "keys_not_init" answer
			sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[17])));

			//send command and wait for ans
			status = sendCommand(_command,ans1,ans2,ans3,10000);

			if (status == 1)
			{
				// create "accepted" answer
				memset(ans1,0x00,sizeof(ans1));
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[6])));
				// create "denied" answer
				memset(ans2,0x00,sizeof(ans2));
				sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[19])));

				//wait for response
				if (waitFor(ans1,ans2,30000) == 1)
				{
					status = saveConfig();
					if (status == 0)
					{
						_OTAAError=0;
						return LORAWAN_ANSWER_OK;
					}
					else
					{
						return LORAWAN_ANSWER_ERROR;
					}
				}
				else
				{
					status = 2;
					// continue with next attempt
					//return LORAWAN_ANSWER_ERROR;
				}
			}

			retries--;

		} while (retries > 0);

		if (status == 1)
		{
			_OTAAError=2;
			return LORAWAN_ANSWER_ERROR;
		}
		else if (status == 2)
		{
			_OTAAError=3;
			return LORAWAN_ANSWER_ERROR;
		}
		else if (status == 3)
		{
			_OTAAError=4;
			return LORAWAN_INIT_ERROR;
		}
		else
		{
			_OTAAError=5;
			return LORAWAN_NO_ANSWER;
		}

	}
	else
	{
		// create "at+mode=1" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[104])),1);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 1000);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(_command,0x00,sizeof(_command));
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			memset(ans3,0x00,sizeof(ans3));

			// create "at+join" command
			sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[105])));
			// create "+EVENT=1,1" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[50])));
            // create "+EVENT=1,0" answer
            sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[56])));
			// create "+ERR" answer
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

			//send command and wait for ans
			status = sendCommand(_command,ans1, ans2, ans3, 15000);

			if (status == 0)
			{
				return LORAWAN_NO_ANSWER;
			}
			else if (status == 1)
			{
                delay(1000);
				return LORAWAN_ANSWER_OK;
			}
            else if (status == 3)
            {
                return LORAWAN_NOT_JOINED;
            }
			else
			{
				//print error
				//~ waitFor("\r");
				//~ USB.print(F("Error: "));
				//~ USB.println((char*)_buffer);
				return LORAWAN_ANSWER_ERROR;
			}
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes).
 * 			User can check _datareceived to know if a downlink was performed
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'4' if data length error
 * 	@arg	'5' if error when sending data
 * 	@arg	'6' if module hasn't joined to a network
 *  @arg	'7' if input port parameter error
 */
uint8_t WaspLoRaWAN::sendConfirmed(uint8_t port, char* payload)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	char carr[5];

	// clear data received flag
	_dataReceived = false;

	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	memset(ans4,0x00,sizeof(ans4));

	// check port
	if (port > 223) return LORAWAN_INPUT_ERROR;

	// check if payload is a hexadecimal string
	for (uint8_t i=0;i<strlen(payload);i++)
	{
		if (((payload[i] < '0') || (payload[i] > '9')) &&
			((payload[i] < 'A') || (payload[i] > 'F')) &&
			((payload[i] < 'a') || (payload[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac tx cnf <port> <data>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[5])),port,payload);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		// create "not_joined" answer
		sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
		// invalid_data_len
		strcpy_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,ans3,ans4,1000);

		if (status == 1)
		{
			// clear buffer
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			memset(ans3,0x00,sizeof(ans3));
			memset(carr,0x00,sizeof(carr));

			// mac_rx
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
			// mac_tx_ok
			strcpy_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
			// mac_err
			strcpy_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));
			// \r\n
			strcpy_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			//wait for response
			status = waitFor(ans1, ans2, ans3, 60000);

			if (status == 1)
			{
				waitFor(carr,500);
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
	else
	{
		// create "at+pctx <port>,<length>\r<payload>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[106])),port,strlen(payload)/2,payload);
		// create "+ACK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[51])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 20000);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));

			// create "+RECV=" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[52])));

			status = waitFor(ans1,2000);

			if(status == 1)
			{
				waitFor("\r\n\r\n",500);

				char* pch = strtok((char*) _buffer,",");
				_port = atoi(pch);

				pch = strtok(NULL,"\r\n\r\n");
				int packetLength = atoi(pch);

				delay(100);
				readBuffer(packetLength*2);

				memset(_data,0x00,sizeof(_data));
				memcpy(_data, (char*) _buffer, sizeof(_data)-1);

				_dataReceived = true;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
	}
}


/*!
 *
 * @brief	This function sends a LoRaWAN packet and waits for ACK
 *
 * @param 	char* data:	data to be sent
 * 			uint8_t port: port number to send data
 * 			uint16_t length: length of data array
 *
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: payload =12A435 – the payload
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes).
 * 			User can check _datareceived to know if a downlink was performed
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'4' if data length error
 * 	@arg	'5' if error when sending data
 * 	@arg	'6' if module hasn't joined to a network
 *  @arg	'7' if input port parameter error
 */
uint8_t WaspLoRaWAN::sendConfirmed(uint8_t port, uint8_t* payload, uint16_t length)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	char byte2send[3];
	char carr[5];

	// clear data received flag
	_dataReceived = false;

	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	memset(ans4,0x00,sizeof(ans4));
	memset(byte2send,0x00,sizeof(byte2send));
	memset(carr,0x00,sizeof(carr));

	// check port
	if (port > 223) return LORAWAN_INPUT_ERROR;

	if (_version != ABZ_MODULE)
	{
		// create "mac tx cnf <port> " command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[82])),port);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		// create "not_joined" answer
		sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
		// invalid_data_len
		strcpy_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));
		// create "\r\n" answer
		sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

		//send command and wait for ans
		printString(_command,_uart);
		for (uint16_t i=0; i<length;i++)
		{
		Utils.hex2str((uint8_t*)&payload[i], byte2send, 1);
		printByte(byte2send[0],_uart);
		printByte(byte2send[1],_uart);
		}
		printString(carr,_uart);
		status = waitFor(ans1,ans2,ans3,ans4,500);

		if (status == 1)
		{
			// clear buffer
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			memset(ans3,0x00,sizeof(ans3));

			// mac_rx
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
			// mac_tx_ok
			strcpy_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
			// mac_err
			strcpy_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));

			//wait for response
			status = waitFor(ans1, ans2, ans3, 20000);

			if (status == 1)
			{
				waitFor(carr,500);
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
	else
	{
		// create "at+pctx <port>,<length>\r<payload>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[106])),port,length*2,NULL);
		// create "+ACK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[51])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

        //send command and wait for ans
        printString(_command,_uart);
        for (uint16_t i=0; i<length;i++)
        {
            Utils.hex2str((uint8_t*)&payload[i], byte2send, 1);
            printByte(byte2send[0],_uart);
            printByte(byte2send[1],_uart);
        }
        status = waitFor(ans1, ans2, 20000);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));

			// create "+RECV=" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[52])));

			status = waitFor(ans1,4000);

			if(status == 1)
			{
				waitFor("\r\n\r\n",500);

				char* pch = strtok((char*) _buffer,",");
				_port = atoi(pch);

				pch = strtok(NULL,"\r\n\r\n");
				int packetLength = atoi(pch);

				delay(100);
				readBuffer(packetLength*2);

				memset(_data,0x00,sizeof(_data));
				memcpy(_data, (char*) _buffer, sizeof(_data)-1);

				_dataReceived = true;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes).
 * 			User can check _datareceived to know if a downlink was performed
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'4' if data length error
 * 	@arg	'5' if error when sending data
 * 	@arg	'6' if module hasn't joined to a network
 *  @arg	'7' if input port parameter error
 */
uint8_t WaspLoRaWAN::sendUnconfirmed(uint8_t port, char* payload)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	char carr[5];

	// clear data received flag
	_dataReceived = false;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	memset(ans4,0x00,sizeof(ans4));

	// check port
	if (port > 223) return LORAWAN_INPUT_ERROR;

	// check if payload is a hexadecimal string
	for (uint8_t i=0;i<strlen(payload);i++)
	{
		if (((payload[i] < '0') || (payload[i] > '9')) &&
			((payload[i] < 'A') || (payload[i] > 'F')) &&
			((payload[i] < 'a') || (payload[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac tx uncnf <port> <data>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[6])),port,payload);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		// create "not_joined" answer
		sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
		// invalid_data_len
		sprintf_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,ans3,ans4,500);

		if (status == 1)
		{
			// clear buffer
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			memset(ans3,0x00,sizeof(ans3));
			memset(ans4,0x00,sizeof(ans4));
			memset(carr,0x00,sizeof(carr));

			// mac_rx <port>
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
			// mac_tx_ok
			sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
			// mac_err
			sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));
			// \r\n
			sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			//wait for response
			status = waitFor(ans1, ans2, ans3, 20000);

			if (status == 1)
			{
				waitFor(carr,500);

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
	else
	{
		// create "at+putx <port>,<length>\r<payload>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[126])),port,strlen(payload)/2,payload);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 20000);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));

			// create "+RECV=" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[52])));

			status = waitFor(ans1,4000);

			if(status == 1)
			{
				waitFor("\r\n\r\n",500);

				char* pch = strtok((char*) _buffer,",");
				_port = atoi(pch);

				pch = strtok(NULL,"\r\n\r\n");
				int packetLength = atoi(pch);

				delay(100);
				readBuffer(packetLength*2);

				memset(_data,0x00,sizeof(_data));
				memcpy(_data, (char*) _buffer, sizeof(_data)-1);

				_dataReceived = true;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
	}
}


/*!
 *
 * @brief	This function sends a LoRaWAN packet and waits for ACK
 *
 * @param 	char* data:	data to be sent
 * 			uint8_t port: port number to send data
 * 			uint16_t length: length of data array
 *
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: payload =12A435 – the payload
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 584 digit (292 Bytes).
 * 			User can check _datareceived to know if a downlink was performed
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'4' if data length error
 * 	@arg	'5' if error when sending data
 * 	@arg	'6' if module hasn't joined to a network
 *  @arg	'7' if input port parameter error
 */
uint8_t WaspLoRaWAN::sendUnconfirmed(uint8_t port, uint8_t* payload, uint16_t length)
{
	uint8_t status;
	char ans1[20];
	char ans2[20];
	char ans3[20];
	char ans4[20];
	char byte2send[3];
	char carr[5];

	// clear data received flag
	_dataReceived = false;

	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));
	memset(ans4,0x00,sizeof(ans4));
	memset(carr,0x00,sizeof(carr));
	memset(byte2send,0x00,sizeof(byte2send));

	// check port
	if (port > 223) return LORAWAN_INPUT_ERROR;

	if (_version != ABZ_MODULE)
	{
		// create "mac tx uncnf <port> " command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[83])),port);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
		// create "not_joined" answer
		sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[18])));
		// invalid_data_len
		strcpy_P(ans4,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[16])));
		// create "\r\n" answer
		sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

		//send command and wait for ans
		printString(_command,_uart);
		for (uint16_t i=0; i<length;i++)
		{
			Utils.hex2str((uint8_t*)&payload[i], byte2send, 1);
			printByte(byte2send[0],_uart);
			printByte(byte2send[1],_uart);
		}
		printString(carr,_uart);
		status = waitFor(ans1,ans2,ans3,ans4,500);

		if (status == 1)
		{
			// clear buffer
			memset(ans1,0x00,sizeof(ans1));
			memset(ans2,0x00,sizeof(ans2));
			memset(ans3,0x00,sizeof(ans3));
			memset(carr,0x00,sizeof(carr));

			// mac_rx
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[3])));
			// mac_tx_ok
			strcpy_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[8])));
			// mac_err
			strcpy_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[15])));
			// create "\r\n" answer
			sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			//wait for response
			status = waitFor(ans1, ans2, ans3, 20000);

			if (status == 1)
			{
				waitFor(carr,500);
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
	else
	{
		// create "at+putx <port>,<length>\r<payload>" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[126])),port,length*2,NULL);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

        //send command and wait for ans
        printString(_command,_uart);
        for (uint16_t i=0; i<length;i++)
        {
            Utils.hex2str((uint8_t*)&payload[i], byte2send, 1);
            printByte(byte2send[0],_uart);
            printByte(byte2send[1],_uart);
        }
        status = waitFor(ans1, ans2, 20000);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));

			// create "+RECV=" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[52])));

			status = waitFor(ans1,4000);

			if(status == 1)
			{
				waitFor("\r\n\r\n",500);

				char* pch = strtok((char*) _buffer,",");
				_port = atoi(pch);

				pch = strtok(NULL,"\r\n\r\n");
				int packetLength = atoi(pch);

				delay(100);
				readBuffer(packetLength*2);

				memset(_data,0x00,sizeof(_data));
				memcpy(_data, (char*) _buffer, sizeof(_data)-1);

				_dataReceived = true;
			}

			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setADR(char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
  uint8_t adr_state;

	// check state
	if ((strcmp(state, "on")) && (strcmp(state, "off"))) return LORAWAN_INPUT_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

  if (strcmp(state, "on")  == 0) adr_state = true;
  if (strcmp(state, "off") == 0) adr_state = false;

  if (_version != ABZ_MODULE)
  {
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
  		_adr = adr_state;
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
  else
  {
    // create "at+adr=<adr>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[128])),adr_state);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      _adr = adr_state;
      return LORAWAN_ANSWER_OK;
    }
    else
    {
      //print error
      waitFor("\r");
      USB.print(F("Error: "));
      USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
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

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 3)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+adr?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[127])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_adr = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// create "mac get dcycle" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[31])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// create "mac pause" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[9])));
	// create "4294967245" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[14])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
 * @brief	This function sets the frequency on the given channel ID
 *
 * @param	uint32_t freq: frequency to be set [863250000..869750000]
 * 											   [433250000..434550000]
 * 			uint8_t channel: channel to be set [3..15]
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 * 	@arg	'8' if module does not support function
 */
uint8_t WaspLoRaWAN::setChannelFreq(uint8_t channel, uint32_t freq)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	//check module (this function is only available for RN2483)
	if (_version == RN2903_MODULE)
	{
		return LORAWAN_VERSION_ERROR;
	}

	// check frequency settings
	if (_version == ABZ_MODULE && _bandABZ == 0)
	{
		if (freq > 928000000) return LORAWAN_INPUT_ERROR;
		if (freq < 920600000) return LORAWAN_INPUT_ERROR;
	}

	// check frequency settings
	if (_version == ABZ_MODULE && _bandABZ == 6)
	{
		if (freq > 923500000) return LORAWAN_INPUT_ERROR;
		if (freq < 917000000) return LORAWAN_INPUT_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// check channel
		if ((channel > 15 || channel <3) && !(_version == RN2903_AS_MODULE)) return LORAWAN_INPUT_ERROR;
		else if (channel > 15 || channel <2) return LORAWAN_INPUT_ERROR;

		// check frequency settings
		if (_version == RN2903_IN_MODULE || _version == RN2483_MODULE)
		{
			if (freq < 433250000) return LORAWAN_INPUT_ERROR;
			if ((freq > 434550000)&&(freq < 863250000)) return LORAWAN_INPUT_ERROR;
			if (freq > 869750000) return LORAWAN_INPUT_ERROR;
			if ((freq < 863250000) && (_version == RN2903_IN_MODULE)) return LORAWAN_INPUT_ERROR;
		}

		// check frequency settings
		if (_version == RN2903_AS_MODULE)
		{
			if (freq > 928000000) return LORAWAN_INPUT_ERROR;
			if (freq < 915250000) return LORAWAN_INPUT_ERROR;
		}


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
	else
	{
		// create "at+rfparam=%u,%lu,%u,%u\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[119])),channel,freq,_drrMin[channel],_drrMax[channel]);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

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
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_NO_ANSWER;
		}
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
 * 	@arg	'7' if input parameter error
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::getChannelFreq(uint8_t channel)
{
	uint8_t status;
	char ans2[15];
	char ans1[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
		case ABZ_MODULE:
				if (channel > 15)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case RN2903_MODULE:
				if (channel > 71)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac get ch freq" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[35])),channel);
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 1)
		{
			_freq[channel] = parseValue(10);
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
	else
	{
		// create "at+rfparam?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[103])));
		// create ";%u," answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[53])),channel);
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,"\r",10000);

		if (status == 1)
		{
			waitFor(",",100);

			_freq[channel] = parseValue(10);
			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_NO_ANSWER;
		}
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
 *  @arg	'7' if input channel parameter error
 *	@arg	'8' module does not support function
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

	//check module (this function is only available for RN2483)
	if (_version == RN2903_MODULE || _version == ABZ_MODULE)
	{
		return LORAWAN_VERSION_ERROR;
	}

	// check channel
	if (channel > 15) return LORAWAN_INPUT_ERROR;

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
 *	@arg	'8' module does not support function
 */
uint8_t WaspLoRaWAN::getChannelDutyCycle(uint8_t channel)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	//check module (this function is only available for RN2483)
	if (_version == RN2903_MODULE || _version == ABZ_MODULE)
	{
		return LORAWAN_VERSION_ERROR;
	}

	// check channel
	if (channel > 15) return LORAWAN_INPUT_ERROR;

	// create "mac get ch dcycle" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[36])),channel);
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,300);

	if (status == 1)
	{
		_dCycle[channel] = parseValue(10);
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
 * @brief	This function sets the data rate range on the given channel ID
 *
 * @param	uint8_t minDR: datarate to be set
 * 			uint8_t maxDR: datarate to be set
 * 			uint8_t channel: channel to be set
 * @remarks
 * 			For RN2483:
 * 						minDR [0..5]
 *  	                maxDR [0..5]
 *						channel [0..15]
 * 			For RN2903:
 * 						minDR [0..3]
 *  	                maxDR [0..3]
 *						channel [0..63]
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::setChannelDRRange(uint8_t channel, uint8_t minDR, uint8_t maxDR)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
		case ABZ_MODULE:
				if ((channel > 15) || (minDR > 5) || (maxDR > 5))
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case RN2903_MODULE:
				if ((channel > 63) || (minDR > 3) || (maxDR > 3))
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
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
	else
	{
		// create "at+rfparam=%u,%lu,%u,%u\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[119])),channel,_freq[channel],minDR,maxDR);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

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
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_NO_ANSWER;
		}
	}
}


/*!
 * @brief	This function gets the data rate range on the given channel
 *
 * @param	uint8_t channel
 * 			For RN2483: channel [0..15]
 * 			For RN2903: channel [0..71]
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::getChannelDRRange(uint8_t channel)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
		case ABZ_MODULE:
				if (channel > 15)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case RN2903_MODULE:
				if (channel > 71)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac get ch drrange" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[37])),channel);
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+rfparam?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[103])));
		// create ";%u," answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[53])),channel);
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,"\r",3000);

		if (status == 1)
		{
			waitFor(",",100);
			// channel freq
			waitFor(",",100);
			_drrMin[channel] = parseValue(10);
			waitFor(",",100);
			_drrMax[channel] = parseValue(10);

			return LORAWAN_ANSWER_OK;
		}
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_NO_ANSWER;
		}
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
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::setChannelStatus(uint8_t channel, char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "on" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
	// create "off" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));

	// check state
	if ((strcmp(state, ans1)) && (strcmp(state, ans2))) return LORAWAN_INPUT_ERROR;

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
				if (channel > 15)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case RN2903_MODULE:
				if (channel > 71)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case ABZ_MODULE:
		default:
				return LORAWAN_VERSION_ERROR;
	}

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
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));

		// create "on" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
		// create "off" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));

		// Store the status of the channel into _status[channel]
		if (!strcmp(state,ans1)) _status[channel] = true;
		if (!strcmp(state,ans2)) _status[channel] = false;

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
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
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

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
				if (channel > 15)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;

		case RN2903_MODULE:
				if (channel > 71)
				{
					return LORAWAN_INPUT_ERROR;
				}
				break;
		case ABZ_MODULE:
                if (channel > 15)
                {
                    return LORAWAN_INPUT_ERROR;
                }
                break;
		default:
				return LORAWAN_VERSION_ERROR;
	}


    if (_version != ABZ_MODULE)
    {
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
    	else if (status == 3)
    	{
    		return LORAWAN_ANSWER_ERROR;
    	}
    	else
    	{
    		return LORAWAN_NO_ANSWER;
    	}
    }
    else
    {
        // create "at+chmask?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[140])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
            waitFor("\r\n", 500);
            char* pch = strtok((char*)_buffer," \r\n");
            if (pch != NULL)
			{
                unsigned long int chmask_hex = strtoul(pch, NULL, 16);

                uint8_t lsb_mask = uint8_t (chmask_hex >> 8);
                uint8_t msb_mask = uint8_t (chmask_hex);

                chmask_hex = ((unsigned long int) msb_mask << 8) + lsb_mask;

                unsigned long int mask = 0x0001 << channel;

                if ((chmask_hex & mask) != 0)
                {
                    _status[channel] = true;
                    return LORAWAN_ANSWER_OK;
                }
                else
                {
                    _status[channel] = false;
            		return LORAWAN_ANSWER_OK;
                }
			}
            else
            {
                //print error
                //~ waitFor("\r");
                //~ USB.print(F("Error: "));
                //~ USB.println((char*)_buffer);
                return LORAWAN_ANSWER_ERROR;
            }
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+rtynum=%u\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[130])), retries);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
		  return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			_retries = retries;
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get retx" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[70])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);

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
	else
	{
		// create "at+rtynum?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[129])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_retries = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
	}
}




/*!
 * @brief	This function gets current band of operation
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *	@arg	'8' module does not support function
 */
uint8_t WaspLoRaWAN::getBand()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	//check module (this function is only available for RN2483)
	if (_version != RN2483_MODULE && _version != ABZ_MODULE)
	{
		return LORAWAN_VERSION_ERROR;
	}

	if (_version != ABZ_MODULE)
	{
		// create "mac get band" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[28])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 1)
		{
			memset(_band, 0x00, sizeof(_band));
			strncpy(_band,(char*)_buffer, sizeof(_band));
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
	else
	{
		// create "at+band?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[121])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_bandABZ = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get mrgn" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[32])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

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
	else
	{
		// create "at+lncheck=0\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[131])));
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));
			// create "+EVENT=2," answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[54])));

			waitFor(ans1,5000);
			waitFor("\r",5000);

			if (parseValue(10) == 0)
			{
				_gwNumber = 0;
				_margin = 0;
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				memset(ans1,0x00,sizeof(ans1));
				// create "+ANS=2," answer
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[55])));
				waitFor(ans1,5000);
				waitFor(",",100);
				_margin = parseValue(10);
				waitFor("\r",100);
				_gwNumber = parseValue(10);
				return LORAWAN_ANSWER_OK;
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
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get gwnb" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[33])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

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
	else
	{
		// create "at+lncheck=0\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[131])));
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,300);

		if (status == 1)
		{
			memset(ans1,0x00,sizeof(ans1));
			// create "+EVENT=2," answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[54])));

			waitFor(ans1,5000);
			waitFor("\r",100);

			if (parseValue(10) == 0)
			{
				_gwNumber = 0;
				_margin = 0;
				return LORAWAN_ANSWER_OK;
			}
			else
			{
				memset(ans1,0x00,sizeof(ans1));
				// create "+ANS=2," answer
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[55])));

				waitFor(ans1,5000);
				//get the margin
				waitFor(",",100);
				_margin = parseValue(10);

				//get the gateway number
				waitFor("\r",100);
				_gwNumber = parseValue(10);

				return LORAWAN_ANSWER_OK;
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

	if (_version != ABZ_MODULE)
	{
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
		else if(status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+frmcnt=%lu,%lu\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[133])), counter, _downCounter);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
		  return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			_upCounter = counter;
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get upctr" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[73])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);

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
	else
	{
		// create "at+frmcnt?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[132])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			waitFor(",",100);
			_upCounter = parseIntValue();

			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_downCounter = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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

	if (_version != ABZ_MODULE)
	{
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
		else if (status == 2)
		{
			return LORAWAN_ANSWER_ERROR;
		}
		else
		{
			return LORAWAN_NO_ANSWER;
		}
	}
	else
	{
		// create "at+frmcnt=%lu,%lu\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[133])), _upCounter, counter);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			_upCounter = counter;
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// create "mac set linkchk %u" command
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
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get dnctr" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[75])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,100);

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
	else
	{
		// create "at+frmcnt?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[132])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			waitFor(",",100);
			_upCounter = parseIntValue();
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_downCounter = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
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
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::sendRadio(char * message)
{
	char ans1[15];
	char ans2[15];
	uint8_t status;

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// check if payload is a hexadecimal string
	for (uint8_t i=0;i<strlen(message);i++)
	{
		if (((message[i] < '0') || (message[i] > '9')) &&
			((message[i] < 'A') || (message[i] > 'F')) &&
			((message[i] < 'a') || (message[i] > 'f')))
		{
			return LORAWAN_INPUT_ERROR;
		}
	}

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
 * @brief	Send a packet via radio
 *
 * @param	uint8_t* data: byte array that will be send
 * 			uint16_t length: length of data array
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if there was an error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::sendRadio(uint8_t * payload, uint16_t length)
{
	char ans1[15];
	char ans2[15];
	char carr[5];
	char byte2send[3];
	uint8_t status;

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// clear buffers
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(byte2send,0x00,sizeof(byte2send));
	memset(carr,0x00,sizeof(carr));

	// create "radio tx " command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[93])));
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "\r\n" answer
	sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

	//send command and wait for ans
	printString(_command,_uart);
	for (uint16_t i=0; i<length;i++)
	{
		Utils.hex2str((uint8_t*)&payload[i], byte2send, 1);
		printByte(byte2send[0],_uart);
		printByte(byte2send[1],_uart);
	}
	printString(carr,_uart);

	status = waitFor(ans1,ans2,600);

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
 * 	@arg	'2' it no answer
 *
 */
uint8_t WaspLoRaWAN::receiveRadio(uint32_t timeout)
{
	uint8_t error;
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	//set watch dog radio to timeout
	error = setRadioWDT(timeout);
	if (error == 0)
	{
		//start radio receiving
		memset(_command,0x00,sizeof(_command));
		memset(ans1,0x00,sizeof(ans1));
		memset(ans2,0x00,sizeof(ans2));

		// create "radio rx" command
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
			if (_version == RN2903_IN_MODULE)
			{
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[22])));
			}
			else
			{
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[7])));
			}

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
 *  @arg	'2' it no answer
 */
uint8_t WaspLoRaWAN::test_ON()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
 * @brief	Stops the continuous wave mode, this function works with module
 * 			identical to "reset()"
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 *  @arg	'2' it no answer
 *
 */
uint8_t WaspLoRaWAN::test_OFF()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans3,0x00,sizeof(ans3));

	// create "radio cw off" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[42])));
	// create "RN2483" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[5])));
	// create "RN2903" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[20])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3);

	if (status == 1)
	{
		_version = RN2483_MODULE;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		_version = RN2903_MODULE;

		// create "India" answer
		memset(ans1,0x00,sizeof(ans1));
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[21])));
		// create "ASIA-PAC / LATAM" answer
		memset(ans2,0x00,sizeof(ans2));
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[23])));

		status = waitFor(ans1,ans2);

		if(status == 1)
		{
			_version = RN2903_IN_MODULE;
		}
		else if (status == 2)
		{
			_version = RN2903_AS_MODULE;
		}

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get snr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[65])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get sf" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[59])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::setRadioPower(int8_t pwr)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// create "radio set pwr" command
	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
				if ((pwr < -3) || (pwr > 15)) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_MODULE:
				if ((pwr < 2) || (pwr > 20)) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_AS_MODULE:
				if ((pwr < -3) || (pwr > 16)) return LORAWAN_INPUT_ERROR;
				break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[45])),pwr);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

	if (status == 1)
	{
		_radioPower = pwr;
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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get pwr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[58])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get mod" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[56])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 * @param	uint32_t freq: operating frequency [863250000..869750000] (RN2483)
 * 											   [433250000..434550000]
 * 			uint32_t freq: operating frequency [923550000..927250000] (RN2903)
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::setRadioFreq(uint32_t freq)
{
	uint8_t status;
	char ans1[50];
	char ans2[50];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
				if (freq < 433250000) return LORAWAN_INPUT_ERROR;
				if ((freq > 434550000)&&(freq < 863250000)) return LORAWAN_INPUT_ERROR;
				if (freq > 869750000) return LORAWAN_INPUT_ERROR;
				if ((freq < 863250000) && (_version == RN2903_IN_MODULE)) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_MODULE:
				if ((freq < 902250000)||(freq > 927750000)) return LORAWAN_INPUT_ERROR;
				break;
		case RN2903_AS_MODULE:
				if ((freq < 915250000)||(freq > 927750000)) return LORAWAN_INPUT_ERROR;
				break;
		default:
				return LORAWAN_VERSION_ERROR;
	}

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));

	// create "radio get freq" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[57])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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

	if (strcmp(decimal,"0") == 0)
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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get rxbw" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[60])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 * 	@arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setRadioBitRateFSK(uint32_t bitrate)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	//check bit rate
	if ((bitrate > 300000)&&(bitrate < 1)) return LORAWAN_INPUT_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get bitrate" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[61])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 * 	@arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setRadioFreqDeviation(uint32_t freqdeviation)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	//check freqdeviation
	if (freqdeviation > 200000) return LORAWAN_INPUT_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get fdev" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[71])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
		// create "on" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));

		if (!strcmp(state,ans1)) _crcStatus = true;
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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get prlen" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[67])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get cr" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[62])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		char* pch = strtok((char*)_buffer,ans1);
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

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get wdt" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[63])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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
 * @brief	This function gets the RSSI of the last radio received packet
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getRadioRSSI()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get rssi" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[141])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,1000);

	if (status == 1)
	{
		char * pch;

		pch = strtok((char*) _buffer,ans1);
		if (pch != NULL)
		{
			_radioRSSI = atoi(pch);
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
 * @brief	This function sets the bandwidth for transceiver use
 *
 * @param	uint16_t bandwitdh: 125,250,500
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg 	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::setRadioBW(uint16_t bandwidth)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	//check bandwidth
	if ((bandwidth == 125) || (bandwidth == 250) || (bandwidth == 500)){}
	else return LORAWAN_INPUT_ERROR;

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
	char ans2[15];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "radio get bw" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[64])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

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


/*!
 * @brief	This function sets data rate and frequency used for the
 * 			second receive window.
 *
 * @remarks	The configuration of the receive window parameters should
 * 			be in concordance with the server configuration
 *
 * @param	uint8_t datarate: datarate to be set [0..5]
 * 			uint32_t frequency: frequency to be set [863000000..870000000]
 * 													[433050000..434790000]
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *	@arg	'7' if input parameter error
 *	@arg	'8' unrecognized module
 */
uint8_t WaspLoRaWAN::setRX2Parameters(uint8_t datarate, uint32_t frequency)
{
	uint8_t status;
	float dutycycle;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
				if (datarate > 7) return LORAWAN_INPUT_ERROR;
				if (frequency < 433250000) return LORAWAN_INPUT_ERROR;
				if ((frequency > 434550000)&&(frequency < 863250000)) return LORAWAN_INPUT_ERROR;
				if (frequency > 869750000) return LORAWAN_INPUT_ERROR;
				if ((frequency < 863250000) && (_version == RN2903_IN_MODULE)) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_MODULE:
				if ((datarate > 13) || (datarate < 8))
				{
					return LORAWAN_INPUT_ERROR;
				}
				if ((frequency < 923550000) || (frequency > 927250000)) return LORAWAN_INPUT_ERROR;
				break;

		case RN2903_AS_MODULE:
				if (datarate > 7)
				{
					return LORAWAN_INPUT_ERROR;
				}
				if ((frequency < 915250000) || (frequency > 927250000)) return LORAWAN_INPUT_ERROR;
				break;

		case ABZ_MODULE:
                getBand();
				if (_bandABZ == 0)
				{
					if (frequency > 928000000 || frequency < 920600000) return LORAWAN_INPUT_ERROR;
				}
				if (_bandABZ == 6)
				{
					if (frequency < 920900000 || frequency > 923300000) return LORAWAN_INPUT_ERROR;
				}
				break;

		default:
				return LORAWAN_VERSION_ERROR;
	}

	if(_version != ABZ_MODULE)
	{
		// create "mac set rx2" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[78])),datarate,frequency);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2);

		if (status == 1)
		{
			_rx2DataRate = datarate;
			_rx2Frequency = frequency;
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
	else
	{
		// create "at+rx2=%lu,%u\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[134])),frequency,datarate);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2);

		if (status == 1)
		{
			_rx2DataRate = datarate;
			_rx2Frequency = frequency;
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
}


/*!
 * @brief	This function sets the delay used for the first receive window
 *
 * @param	uint16_t delay: delay to be set [0..65535]
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
uint8_t WaspLoRaWAN::setRX1Delay(uint16_t delay)
{
	uint8_t status;
	float dutycycle;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac set rx1delay" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[79])),delay);
		// create "ok" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2);

		if (status == 1)
		{
			_rx1Delay = delay;
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
	else
	{
		// create "at+delay=5000,6000,%d,%d\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[136])),delay,delay+1000);
		// create "+OK" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
		// create "+ERRR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2);

		if (status == 1)
		{
			_rx1Delay = delay;
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
}



/*!
 * @brief	This function gets MAC status from the module
 *
 * @remarks This functino is necessary before showing MAC status with
 * 			showMACStatus() function
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::getMACStatus()
{
	uint8_t status;
	char ans1[15];
	char carr[5];

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(carr,0x00,sizeof(carr));

	// create "mac get status" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[81])));
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));
	// create "\r\n" answer
	sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

	//send command and wait for ans
	status = sendCommand(_command,"000",ans1);

	if (status == 1)
	{
		status = waitFor(carr,ans1);
		char* pointer = strtok((char*)_buffer,carr);
		memset(ans1,0x00,sizeof(ans1));
		memcpy(ans1,pointer,sizeof(ans1));
		uint8_t aux[5];
		for (uint8_t i=0; i<5; i++)
		{
			if (ans1[i]>='0' && ans1[i]<='9')
			{
				aux[4-i] = ans1[i] - '0';
			}
			else if (ans1[i]>='A' && ans1[i]<='F')
			{
				aux[4-i] = ans1[i] - 'A' + 10;
			}
			else
			{
				return LORAWAN_ANSWER_ERROR;
			}
		}

		_macStatus = (aux[4]*(16^4))+(aux[3]*(16^3))+(aux[2]*(16^2))+(aux[1]*16)+aux[0];
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
 * @brief	This function returns MAC status verbose
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::showMACStatus()
{
	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	if (_macStatus&0x01) USB.println(F("Module joined to a network"));
	else USB.println(F("Module not joined to a network"));

	if (_macStatus&0x10) USB.println(F("Automatic reply status enabled"));
	else USB.println(F("Automatic reply status disabled"));

	if (_macStatus&0x20) USB.println(F("ADR status enabled"));
	else USB.println(F("ADR status disabled"));

	if (_macStatus&0x40) USB.println(F("Silent inmediately status enabled"));
	else USB.println(F("Silent inmediately status disabled"));

	if (_macStatus&0x80) USB.println(F("MAC paused"));
	else USB.println(F("MAC not paused"));

	if (_macStatus&0x200) USB.println(F("Link check status enabled"));
	else USB.println(F("Link check status disabled"));

	if (_macStatus&0x400) USB.println(F("Channels updated via NewChannelReq or CFList"));
	else USB.println(F("Channels not updated"));

	if (_macStatus&0x800) USB.println(F("Output power updated"));
	else USB.println(F("Output power not updated"));

	if (_macStatus&0x1000) USB.println(F("Number of repetitions updated"));
	else USB.println(F("Number of repetitions not updated"));

	if (_macStatus&=0x2000) USB.println(F("Prescaler updated"));
	else USB.println(F("Prescaler not updated"));

	if (_macStatus&=0x4000) USB.println(F("RX2 window parameter updated"));
	else USB.println(F("RX2 window not updated"));

	if (_macStatus&=0x8000) USB.println(F("TX timing updated"));
	else USB.println(F("TX timing not updated"));

	if (_macStatus&=0x10000) USB.println(F("Rejoin needed"));
	else USB.println(F("End device functional"));

}


/*!
 * @brief	This function returns all channel status
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
void WaspLoRaWAN::showChannelStatus()
{
	switch (_version)
	{
		case RN2483_MODULE:
		case RN2903_IN_MODULE:
		case RN2903_AS_MODULE:
				for (int i = 0; i < 16; i++) showChannelStatus(i);
				break;

		case RN2903_MODULE:
				for (int i = 0; i < 64; i++) showChannelStatus(i);
				break;
		default:
				break;
	}

}


/*!
 * @brief	This function returns all channel status
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
void WaspLoRaWAN::showChannelStatus(uint8_t channel)
{
	if (_version != ABZ_MODULE)
	{
		getChannelStatus(channel);
		USB.print(F("Channel number: "));
		USB.print(channel,DEC);
		USB.print(F(" status is "));
		if (_status[channel] == true) USB.println(F("on"));
		else USB.println(F("off"));
	}
}


void WaspLoRaWAN::convertString(char* string2convert, char* outputString)
{
	Utils.hex2str((uint8_t*)string2convert, outputString, strlen(string2convert));
}

void WaspLoRaWAN::convertString(uint8_t* string2convert, char* outputString)
{
	Utils.hex2str(string2convert, outputString, strlen((char*)string2convert));
}

/*!
 * @brief	This function puts the module to sleep
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::sleep()
{
	return sleep(4294967295);
}

/*!
 * @brief	This function puts the module to sleep
 *
 * @param	uint32_t time: 100..4294967295
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::sleep(uint32_t time)
{
	uint8_t status;
	char ans1[25];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// create "mac get status" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[84])),time);
	// create "invalid_param" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,1000);

	if (status == 1)
	{
		return 1;
	}
	return 0;
}

/*!
 * @brief	This function force the module to wake up
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 */
uint8_t WaspLoRaWAN::wakeUp()
{
	uint8_t status;
	char ans1[25];

	memset(ans1,0x00,sizeof(ans1));

	beginUART();

	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));

	printByte(0x00,_uart);
	printByte(0x55,_uart);

	delay(500);

	sleep(100);
	status = waitFor(ans1,500);

	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
	}
	else
	{
		return LORAWAN_ANSWER_ERROR;
	}
}


/*!
 * @brief	This function is used to set the automatic reply status from module
 *
 * @param	char* state: "on"/"off"
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 * 	@arg	'8' if module does not support function
 */
uint8_t WaspLoRaWAN::setAR(char* state)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

  if (_version == ABZ_MODULE)
  {
    // Function not available for Murata mudule
    return LORAWAN_VERSION_ERROR;
  }

	// check state
	if ((strcmp(state, "on")) && (strcmp(state, "off"))) return LORAWAN_INPUT_ERROR;

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "mac set ar" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[85])),state);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,500);

	if (status == 1)
	{
		if (strcmp(state, "on")  == 0) _ar = true;
		if (strcmp(state, "off") == 0) _ar = false;
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
 * @brief	This function is used to get the automatic reply status from module
 *
 * @param	char* state: "on"/"off"
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 * 	@arg	'8' if module does not support function
 */
uint8_t WaspLoRaWAN::getAR()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];
	char ans3[15];

  if (_version == ABZ_MODULE)
  {
    // Function not available for Murata mudule
    return LORAWAN_VERSION_ERROR;
  }

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));
	memset(ans2,0x00,sizeof(ans3));

	// create "mac get ar" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[86])));
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[9])));
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[10])));
	// create "invalid_param" answer
	sprintf_P(ans3,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,ans3,500);

	if (status == 1)
	{
		_ar = true;
		return LORAWAN_ANSWER_OK;
	}
	else if (status == 2)
	{
		_ar = false;
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
 * @brief	This function is used to get the first receive window delay
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::getRX1Delay()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version != ABZ_MODULE)
	{
		// create "mac get rxdelay1" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[87])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			_rx1Delay = parseIntValue();
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
	else
	{
		// create "at+delay?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[137])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			waitFor(",",100);
			waitFor(",",100);
			waitFor(",",100);
			_rx1Delay = parseIntValue();

			waitFor(",",100);
			_rx2Delay = parseIntValue();
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
}


/*!
 * @brief	This function is used to get the second receive window delay
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::getRX2Delay()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if(_version != ABZ_MODULE)
	{
		// create "mac get rxdelay2" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[88])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			_rx2Delay = parseIntValue();
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
	else
	{
		getRX1Delay();
	}
}


/*!
 * @brief	This function is used to set second receiving window
 * 			parameters depending on the working band
 *
 * @param	char* band: "868", "433" or "900"
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 *  @arg	'7' if input parameter error
 */
uint8_t WaspLoRaWAN::getRX2Parameters(char* band)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version == ABZ_MODULE) return LORAWAN_VERSION_ERROR;

	// check state
	if ((strcmp(band, "868")) && (strcmp(band, "433")) && (strcmp(band, "900")) && (strcmp(band, "923"))) return LORAWAN_INPUT_ERROR;
	if (!(strcmp(band, "433")) && _version == RN2903_IN_MODULE) return LORAWAN_INPUT_ERROR;

	if (_version == RN2483_MODULE || _version == RN2903_IN_MODULE)
	{
		// create "mac get rx2" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[89])),band);
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			char * pch;
			pch = strtok((char*) _buffer," \r\n");
			if (pch != NULL)
			{
				_rx2DataRate = strtoul(pch,NULL, 10);
				pch = strtok(NULL,"\r\n");
				if (pch != NULL)
				{
					_rx2Frequency = strtoul(pch,NULL, 10);
					return LORAWAN_ANSWER_OK;
				}
				return LORAWAN_ANSWER_ERROR;
			}
			return LORAWAN_ANSWER_ERROR;
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
	else if (_version == RN2903_MODULE)
	{
		// create "mac get rx2" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[90])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			char * pch;
			pch = strtok((char*) _buffer," \r\n");
			if (pch != NULL)
			{
				_rx2DataRate = strtoul(pch,NULL, 10);
				pch = strtok(NULL,"\r\n");
				if (pch != NULL)
				{
					_rx2Frequency = strtoul(pch,NULL, 10);
					return LORAWAN_ANSWER_OK;
				}
				return LORAWAN_ANSWER_ERROR;
			}
			return LORAWAN_ANSWER_ERROR;
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
	else if (_version == RN2903_AS_MODULE)
	{
		// create "mac get rx2" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[95])));
		// create "\r\n" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
		// create "invalid_param" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2,500);

		if (status == 1)
		{
			char * pch;
			pch = strtok((char*) _buffer," \r\n");
			if (pch != NULL)
			{
				_rx2DataRate = strtoul(pch,NULL, 10);
				pch = strtok(NULL,"\r\n");
				if (pch != NULL)
				{
					_rx2Frequency = strtoul(pch,NULL, 10);
					return LORAWAN_ANSWER_OK;
				}
				return LORAWAN_ANSWER_ERROR;
			}
			return LORAWAN_ANSWER_ERROR;
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
}


uint8_t WaspLoRaWAN::getRX2Parameters()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	if (_version == ABZ_MODULE)
	{
		// create "at+rx2?\r" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[135])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR=" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1,ans2);

		if (status == 1)
		{
			waitFor(",",100);
			_rx2Frequency = parseIntValue();


			memset(ans1,0x00,sizeof(ans1));
			// create "\r\n" answer
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
			waitFor(ans1,100);
			_rx2DataRate = parseIntValue();

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
	else
	{
		return LORAWAN_VERSION_ERROR;
	}
}


/*!
 * @brief	This function calculates the maximum payload for current settings
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 */
uint8_t WaspLoRaWAN::getMaxPayload()
{
	uint8_t error;
	_maxPayload = 0;

    if (_version != ABZ_MODULE)
	{
    	// get current data rate
    	error = getDataRate();

    	if (error == 0)
    	{
    		if (_version == RN2483_MODULE)
    		{
    			switch (_dataRate)
    			{
    				case 0:
    				case 1:
    				case 2:	_maxPayload = 51;
    						break;
    				case 3: _maxPayload = 115;
    						break;
    				case 4:
    				case 5:
    				case 6:
    				case 7: _maxPayload = 222;
    						break;
    				default:_maxPayload = 0;
    						return 1;
    						break;
    			}
    		}
    		else if (_version == RN2903_MODULE)
    		{
    			switch (_dataRate)
    			{
    				case 0:	_maxPayload = 11;
    						break;
    				case 1:	_maxPayload = 53;
    						break;
    				case 2:	_maxPayload = 129;
    						break;
    				case 3:
    				case 4: _maxPayload = 242;
    						break;
    				default:_maxPayload = 0;
    						return 1;
    						break;
    			}
    		}
    		else if (_version == RN2903_IN_MODULE)
    		{
    			switch (_dataRate)
    			{
    				case 0:
    				case 1:
    				case 2:	_maxPayload = 51;
    						break;
    				case 3: _maxPayload = 115;
    						break;
    				case 4:
    				case 5: _maxPayload = 222;
    						break;
    				default:_maxPayload = 0;
    						return 1;
    						break;
    			}
    		}
    		else if (_version == RN2903_AS_MODULE)
    		{
    			switch (_dataRate)
    			{
    				case 0:
    				case 1:
    				case 2:	_maxPayload = 51;
    						break;
    				case 3: _maxPayload = 123;
    						break;
    				case 4:
    				case 5: _maxPayload = 230;
    						break;
    				default:_maxPayload = 0;
    						return 1;
    						break;
    			}
    		}
    		else
    		{
    			return 1;
    		}
    	}
    	else
    	{
    		return 1;
    	}

    	return 0;
    }
    else
    {
        uint8_t status;
        char ans1[5];
        char ans2[15];

        memset(_command,0x00,sizeof(_command));
        memset(ans1,0x00,sizeof(ans1));
        memset(ans2,0x00,sizeof(ans2));

        // create "at+msize?" command
		sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[139])));
		// create "+OK=" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		//send command and wait for ans
		status = sendCommand(_command,ans1, ans2, 500);

		if (status == 0)
		{
			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			// create "\r\n" answer
			memset(ans1,0x00,sizeof(ans1));
			sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

			waitFor(ans1,100);

			_maxPayload = parseIntValue();
			return LORAWAN_ANSWER_OK;
		}
		else
		{
			//print error
			//~ waitFor("\r");
			//~ USB.print(F("Error: "));
			//~ USB.println((char*)_buffer);
			return LORAWAN_ANSWER_ERROR;
		}
    }
}

/*!
 * @brief	This function is used to configure the synchronization word
 *			for the LoRaWAN communication.
 *
 * @param	uint8_t sync: one byte long hexadecimal number that represents
 * 			the synchronization word
 */
uint8_t WaspLoRaWAN::setSyncWord(uint8_t sync)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "mac set sync" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[91])), sync);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		_syncWord = sync;
		return LORAWAN_ANSWER_OK;
	}
	else
	{
		return LORAWAN_NO_ANSWER;
	}
}


/*!
 * @brief	This function is used to configure the synchronization word
 *			for the LoRaWAN communication.
 *
 * @param	uint8_t sync: one byte long hexadecimal number that represents
 * 			the synchronization word
 */
uint8_t WaspLoRaWAN::getSyncWord()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	// create "mac get sync" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[92])));
	// create "\r\n" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1) 
	{
		_syncWord = parseValue(16);
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
 * @brief	This function is used to set the battery level required for
 * 			Device Status Answer frame in use with the LoRaWAN Class A protocol.
 *
 * @param	uint8_t sync: one byte long hexadecimal number that represents
 * 			the synchronization word
 */
uint8_t WaspLoRaWAN::setBatteryLevel()
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	uint16_t battery = PWR.getBatteryLevel();

	battery = battery * 254/100;
	if (battery == 0) battery = 1;

	// create "mac set bat" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[94])), battery);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

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
 * @brief	This function is used to set the battery level required for
 * 			Device Status Answer frame in use with the LoRaWAN Class A protocol.
 *
 * @param	uint8_t sync: one byte long hexadecimal number that represents
 * 			the synchronization word
 */
uint8_t WaspLoRaWAN::setBatteryLevel(uint8_t bat)
{
	uint8_t status;
	char ans1[15];
	char ans2[15];

	memset(_command,0x00,sizeof(_command));
	memset(ans1,0x00,sizeof(ans1));
	memset(ans2,0x00,sizeof(ans2));

	uint16_t battery = bat;

	if (battery > 100) battery = 100;

	battery = battery * 254/100;
	if (battery == 0) battery = 1;

	// create "mac set bat" command
	sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[94])), battery);
	// create "ok" answer
	sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[0])));
	// create "invalid_param" answer
	sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[1])));

	//send command and wait for ans
	status = sendCommand(_command,ans1,ans2,100);

	if (status == 1)
	{
		return LORAWAN_ANSWER_OK;
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
	char carr[5];

	memset(carr,0x00,sizeof(carr));
	// create "\r\n" answer
	sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

	pch = strtok((char*) _buffer,carr);
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
	char carr[5];

	memset(carr,0x00,sizeof(carr));
	// create "\r\n" answer
	sprintf_P(carr,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

	pch = strtok((char*) _buffer,carr);
	if (pch != NULL)
	{
		return atof(pch);
	}
	return 0;
}


/*!
 * @brief	This function sets data format of sendings and receivin message.
 * Only for murata module.
 * 0: text ()default
 * 1: hex
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setDataFormat(uint8_t format)
{
  uint8_t status;
  char ans1[5];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+dformat=<format>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[107])),format);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      _dFormat = format;
      return LORAWAN_ANSWER_OK;

    }
    else
    {
		  //print error
		  waitFor("\r");
		  USB.print(F("Error: "));
		  USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function gets data format of sendings and receivin message.
 * Only for murata module.
 * 0: text ()default
 * 1: hex
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::getDataFormat()
{
  uint8_t status;
  char ans1[15];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+dformat?" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[138])));
    // create "+OK=" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      // create "\r\n" answer
      memset(ans1,0x00,sizeof(ans1));
      sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

      waitFor(ans1,100);

      _dFormat = parseIntValue();
      return LORAWAN_ANSWER_OK;
    }
    else
    {
      //print error
      waitFor("\r");
      USB.print(F("Error: "));
      USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function configure the radio band.
 * Only for murata module.
 * 0: AS923
 * 1: AU915
 * 2, 3, 4: RFU
 * 5: EU868 (default)
 * 6: KR920
 * 7: IN865
 * 8: US915
 * 9: US915-HYBRID
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setBand(uint8_t band)
{
  uint8_t status;
  char ans1[15];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Microchip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+band=<band>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[108])),band);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 1000);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {

		memset(ans1,0x00,sizeof(ans1));

		// create "+EVENT=0,0" answer
		sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[24])));
		// create "+ERR" answer
		sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

		status = waitFor(ans1,ans2,10000);

		if (status == 0)
		{
            uint8_t error = getBand();
            if (error == 0)
            {
                if (band == _bandABZ) return LORAWAN_ANSWER_OK;
            }

			return LORAWAN_NO_ANSWER;
		}
		else if (status == 1)
		{
			_bandABZ = band;

			if (_bandABZ == BAND_JP923)
			{
				// give some time to the module after the previous event
				delay(10);

				// create "at+dwell=0,0" command
				sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[123])));
				// create "+OK" answer
				sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
				// create "+ERR" answer
				sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

				//send command and wait for ans
				status = sendCommand(_command,ans1, ans2, 1000);
			}

			if (status == 0)
			{
			  return LORAWAN_NO_ANSWER;
			}
			else if (status == 1)
			{
			  return LORAWAN_ANSWER_OK;
			}
			else
			{
				//print error
				//~ waitFor("\r");
				//~ USB.print(F("Error: "));
				//~ USB.println((char*)_buffer);
			  return LORAWAN_ANSWER_ERROR;
			}
		}
		else
		{
			return LORAWAN_ANSWER_ERROR;
		}
    }
    else
    {
		//print error
		//~ waitFor("\r");
		//~ USB.print(F("Error: "));
		//~ USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function configure duty cycle for EU868 band.
 * Only for murata module.
 * 0: off
 * 1: on (default)
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setDutyCycle(uint8_t state)
{
  uint8_t status;
  char ans1[5];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+dutycycle=<state>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[143])),state);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      _dutyCycle = state;
      return LORAWAN_ANSWER_OK;

    }
    else
    {
		  //print error
		  waitFor("\r");
		  USB.print(F("Error: "));
		  USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function gets duty cycle state for EU868 band.
 * Only for murata module.
 * 0: off
 * 1: on (default)
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::getDutyCycle()
{
  uint8_t status;
  char ans1[15];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+dformat?" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[142])));
    // create "+OK=" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      // create "\r\n" answer
      memset(ans1,0x00,sizeof(ans1));
      sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

      waitFor(ans1,100);

      _dutyCycle = parseIntValue();
      return LORAWAN_ANSWER_OK;
    }
    else
    {
      //print error
      waitFor("\r");
      USB.print(F("Error: "));
      USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function sets carrier sensor time (CST) used by LBT
 * Only for murata module.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setCST(uint16_t cst)
{
  uint8_t status;
  char ans1[5];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+cst=<cst>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[145])), cst);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      _cst = cst;
      return LORAWAN_ANSWER_OK;

    }
    else
    {
		  //print error
		  waitFor("\r");
		  USB.print(F("Error: "));
		  USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function gets  carrier sensor time (CST) used by LBT
 * Only for murata module.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::getCST()
{
  uint8_t status;
  char ans1[15];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+cst?" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[144])));
    // create "+OK=" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      // create "\r\n" answer
      memset(ans1,0x00,sizeof(ans1));
      sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

      waitFor(ans1,100);

      _cst = parseIntValue();
      return LORAWAN_ANSWER_OK;
    }
    else
    {
      //print error
      waitFor("\r");
      USB.print(F("Error: "));
      USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function sets the threshold RSSI value used by LBT
 * Only for murata module.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::setThresholdRSSI(int rssi)
{
  uint8_t status;
  char ans1[5];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+rssith=<rssi>" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[147])), rssi);
    // create "+OK" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[47])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      _rssith = rssi;
      return LORAWAN_ANSWER_OK;

    }
    else
    {
		  //print error
		  waitFor("\r");
		  USB.print(F("Error: "));
		  USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}

/*!
 * @brief	This function gets the threshold RSSI value used by LBT
 * Only for murata module.
 *
 * @return
 * 	@arg	'0' if OK
 * 	@arg	'1' if error
 * 	@arg	'2' if no answer
 * 	@arg	'8' if unrecognized module
 */
uint8_t WaspLoRaWAN::getThresholdRSSI()
{
  uint8_t status;
  char ans1[15];
  char ans2[15];

  memset(_command,0x00,sizeof(_command));
  memset(ans1,0x00,sizeof(ans1));
  memset(ans2,0x00,sizeof(ans2));

  if (_version != ABZ_MODULE)
  {
    //Funtion not available for Micrichip modules
    return LORAWAN_VERSION_ERROR;
  }
  else
  {
    // create "at+rssith?" command
    sprintf_P(_command,(char*)pgm_read_word(&(table_LoRaWAN_COMMANDS[146])));
    // create "+OK=" answer
    sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[49])));
    // create "+ERR" answer
    sprintf_P(ans2,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[46])));

    //send command and wait for ans
    status = sendCommand(_command,ans1, ans2, 500);

    if (status == 0)
    {
      return LORAWAN_NO_ANSWER;
    }
    else if (status == 1)
    {
      // create "\r\n" answer
      memset(ans1,0x00,sizeof(ans1));
      sprintf_P(ans1,(char*)pgm_read_word(&(table_LoRaWAN_ANSWERS[13])));

      waitFor(ans1,100);

      _rssith = parseIntValue();
      return LORAWAN_ANSWER_OK;
    }
    else
    {
      //print error
      waitFor("\r");
      USB.print(F("Error: "));
      USB.println((char*)_buffer);
      return LORAWAN_ANSWER_ERROR;
    }
  }
}



// Preinstantiate Objects /////////////////////////////////////////////////////
WaspLoRaWAN LoRaWAN = WaspLoRaWAN();
