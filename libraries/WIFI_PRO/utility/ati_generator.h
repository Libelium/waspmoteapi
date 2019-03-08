/*! \file ati_generator.h
    \brief Library for generating AT+I commands

    Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version:		3.1
    Design:			David Gascon
    Implementation:	Yuri Carmona

 */

/*! \def ati_generator
    \brief The library flag

 */

#ifndef ati_generator_h
#define ati_generator_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <avr/pgmspace.h>
#include "ati_error_codes.h"



/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! GLOBAL commands

static char I_OK[] 		= "I/OK";
static char I_ERROR[] 	= "I/ERROR";
static char I_ONLINE[] 	= "I/ONLINE";
static char	AT[] 		= "AT+i\r";
static char	AT_I[]		= "AT+i"; 		// at commands header
static char AT_OK[]  	= "OK"; 		// OK response
static char AT_OK2[]	= "I/("; 		// OK with contents
static char AT_ERROR[]	= "ERROR"; 		// ERROR response
static char AT_ONLINE[]	= "I/ONLINE"; 	//
static char I_OK_EOL[] 	= "I/OK\r\n";
static char OTA_ver_file[]	= "UPGRADE.TXT";	// Server's file
static char NO_OTA[] = "NO_FILE";	// No file in server pattern indicator
static char WIFI_PRO_SCANFILE[] = "SCANFILE.TXT";	// file to store scaning results
static char WIFI_PRO_LISTFILE[] = "LISTFILE.TXT";	// file to store listing results
static char I_SLASH[] 	= "I/";
static char EOL_CR_LF[] = "\r\n";

/******************************************************************************
 * COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_WiReach //////////////////////////////////////////////////////////////

const char str_wireach_00[] PROGMEM	= "RP10"; 			// 0
const char str_wireach_01[] PROGMEM	= "FD"; 			// 1
const char str_wireach_02[] PROGMEM	= "WLSI"; 			// 2
const char str_wireach_03[] PROGMEM	= "DOWN"; 			// 3
const char str_wireach_04[] PROGMEM	= "WST"; 			// 4
const char str_wireach_05[] PROGMEM	= "WKY"; 			// 5
const char str_wireach_06[] PROGMEM	= "WPP"; 			// 6
const char str_wireach_07[] PROGMEM	= "PING"; 			// 7
const char str_wireach_08[] PROGMEM	= "IPA"; 			// 8
const char str_wireach_09[] PROGMEM	= "RLNK"; 			// 9
const char str_wireach_10[] PROGMEM	= "\"%s://%s:%s/getpost_frame_parser.php?frame="; 	// 10
const char str_wireach_11[] PROGMEM	= "\"%s://%s:%s/%s\""; 	// 11
const char str_wireach_12[] PROGMEM	= "SLNK"; 			// 12
const char str_wireach_13[] PROGMEM	= "URL"; 			// 13
const char str_wireach_14[] PROGMEM	= "FOPN"; 			// 14
const char str_wireach_15[] PROGMEM	= "FSZ"; 			// 15
const char str_wireach_16[] PROGMEM	= "FRCV"; 			// 16
const char str_wireach_17[] PROGMEM	= "FCLS"; 			// 17
const char str_wireach_18[] PROGMEM	= "BDRA"; 			// 18
const char str_wireach_19[] PROGMEM	= "FSTO"; 			// 19
const char str_wireach_20[] PROGMEM	= "FAPN"; 			// 20
const char str_wireach_21[] PROGMEM	= "FSND"; 			// 21
const char str_wireach_22[] PROGMEM	= "FCLF"; 			// 22
const char str_wireach_23[] PROGMEM	= "STCP"; 			// 23
const char str_wireach_24[] PROGMEM	= "SUDP"; 			// 24
const char str_wireach_25[] PROGMEM	= "LTCP"; 			// 25
const char str_wireach_26[] PROGMEM	= "LSST"; 			// 26
const char str_wireach_27[] PROGMEM	= "SST"; 			// 27
const char str_wireach_28[] PROGMEM	= "SCS"; 			// 28
const char str_wireach_29[] PROGMEM	= "SSND%"; 			// 29
const char str_wireach_30[] PROGMEM	= "SRCV"; 			// 30
const char str_wireach_31[] PROGMEM	= "GPNM"; 			// 31
const char str_wireach_32[] PROGMEM	= "SDMP"; 			// 32
const char str_wireach_33[] PROGMEM	= "SFSH"; 			// 33
const char str_wireach_34[] PROGMEM	= "SCLS"; 			// 34
const char str_wireach_35[] PROGMEM	= "DIP"; 			// 35
const char str_wireach_36[] PROGMEM	= "DNS1"; 			// 36
const char str_wireach_37[] PROGMEM	= "DNS2"; 			// 37
const char str_wireach_38[] PROGMEM	= "IPG"; 			// 38
const char str_wireach_39[] PROGMEM	= "SNET"; 			// 39
const char str_wireach_40[] PROGMEM	= "NTS1"; 			// 40
const char str_wireach_41[] PROGMEM	= "NTS2"; 			// 41
const char str_wireach_42[] PROGMEM	= "NTOD"; 			// 42
const char str_wireach_43[] PROGMEM	= "GMTO"; 			// 43
const char str_wireach_44[] PROGMEM	= "RP8"; 			// 44
const char str_wireach_45[] PROGMEM	= "+++"; 			// 45
const char str_wireach_46[] PROGMEM	= "RP4"; 			// 46
const char str_wireach_47[] PROGMEM	= "!RP10"; 			// 47
const char str_wireach_48[] PROGMEM	= "WSI"; 			// 48
const char str_wireach_49[] PROGMEM	= "RP20"; 			// 49
const char str_wireach_50[] PROGMEM	= "WROM"; 			// 50
const char str_wireach_51[] PROGMEM	= "WLPW"; 			// 51
const char str_wireach_52[] PROGMEM	= "CA"; 			// 52
const char str_wireach_53[] PROGMEM	= "CTT"; 			// 53
const char str_wireach_54[] PROGMEM	= "FMKD"; 			// 54
const char str_wireach_55[] PROGMEM	= "FCWD"; 			// 55
const char str_wireach_56[] PROGMEM	= "FDL"; 			// 56
const char str_wireach_57[] PROGMEM	= "WSRL"; 			// 57
const char str_wireach_58[] PROGMEM	= "WSRH"; 			// 58
const char str_wireach_59[] PROGMEM	= "WPSI"; 			// 59
const char str_wireach_60[] PROGMEM	= "FOPS"; 			// 60
const char str_wireach_61[] PROGMEM	= "STAP"; 			// 61
const char str_wireach_62[] PROGMEM	= "DPSZ"; 			// 62
const char str_wireach_63[] PROGMEM	= "---"; 			// 63
const char str_wireach_64[] PROGMEM	= "RP1"; 			// 64
const char str_wireach_65[] PROGMEM	= "SSL"; 			// 65
const char str_wireach_66[] PROGMEM	= "MACA"; 			// 66


const char* const table_WiReach[] PROGMEM=
{
	str_wireach_00,
	str_wireach_01,
	str_wireach_02,
	str_wireach_03,
	str_wireach_04,
	str_wireach_05,
	str_wireach_06,
	str_wireach_07,
	str_wireach_08,
	str_wireach_09,
	str_wireach_10,
	str_wireach_11,
	str_wireach_12,
	str_wireach_13,
	str_wireach_14,
	str_wireach_15,
	str_wireach_16,
	str_wireach_17,
	str_wireach_18,
	str_wireach_19,
	str_wireach_20,
	str_wireach_21,
	str_wireach_22,
	str_wireach_23,
	str_wireach_24,
	str_wireach_25,
	str_wireach_26,
	str_wireach_27,
	str_wireach_28,
	str_wireach_29,
	str_wireach_30,
	str_wireach_31,
	str_wireach_32,
	str_wireach_33,
	str_wireach_34,
	str_wireach_35,
	str_wireach_36,
	str_wireach_37,
	str_wireach_38,
	str_wireach_39,
	str_wireach_40,
	str_wireach_41,
	str_wireach_42,
	str_wireach_43,
	str_wireach_44,
	str_wireach_45,
	str_wireach_46,
	str_wireach_47,
	str_wireach_48,
	str_wireach_49,
	str_wireach_50,
	str_wireach_51,
	str_wireach_52,
	str_wireach_53,
	str_wireach_54,
	str_wireach_55,
	str_wireach_56,
	str_wireach_57,
	str_wireach_58,
	str_wireach_59,
	str_wireach_60,
	str_wireach_61,
	str_wireach_62,
	str_wireach_63,
	str_wireach_64,
	str_wireach_65,
  str_wireach_66,
};




/// table_FORMAT //////////////////////////////////////////////////////////////

const char str_wireach_format_00[] PROGMEM	= " (%u)"; 						// 0
const char str_wireach_format_01[] PROGMEM	= "I/ERROR (%u)\r\n"; 			// 1
const char str_wireach_format_02[] PROGMEM	= "I/%lu\r\n"; 					// 2
const char str_wireach_format_03[] PROGMEM	= "\r\n"; 						// 3
const char str_wireach_format_04[] PROGMEM	= "ERROR ("; 					// 4
const char str_wireach_format_05[] PROGMEM	= "%lu\r\n"; 					// 5
const char str_wireach_format_06[] PROGMEM	= ")\r\n"; 						// 6
const char str_wireach_format_07[] PROGMEM	= "AT+iRP10\r\nI/(%u,%u,%u,%u)"; // 7
const char str_wireach_format_08[] PROGMEM	= "AT+iIPA?\r\n%s\r\n"; 		// 8
const char str_wireach_format_09[] PROGMEM	= "0.0.0.0"; 					// 9
const char str_wireach_format_10[] PROGMEM	= "\"%s://%s:%s/%s\""; 			// 10
const char str_wireach_format_11[] PROGMEM	= "%s%s:%s,%lu:"; 				// 11
const char str_wireach_format_12[] PROGMEM	= "%u)"; 						// 12
const char str_wireach_format_13[] PROGMEM	= "I/%u:"; 						// 13
const char str_wireach_format_14[] PROGMEM	= "%02u%02u-%02u-%02uT%02u:%02u:%02u+%02u:%02u"; 	// 14
const char str_wireach_format_15[] PROGMEM	= "AT+i!rp10\r\nI/OK"; 			// 15
const char str_wireach_format_16[] PROGMEM	= "%s%01u"; 					// 16
const char str_wireach_format_17[] PROGMEM	= " ,)"; 						// 17
const char str_wireach_format_18[] PROGMEM	= "I/0\r\n"; 					// 18
const char str_wireach_format_19[] PROGMEM	= "FILE:"; 						// 19
const char str_wireach_format_20[] PROGMEM	= "PATH:"; 						// 20
const char str_wireach_format_21[] PROGMEM	= "SIZE:"; 						// 21
const char str_wireach_format_22[] PROGMEM	= "VERSION:"; 					// 22
const char str_wireach_format_23[] PROGMEM	= " ,"; 						// 23
const char str_wireach_format_24[] PROGMEM	= "\r\n.\r\n"; 					// 24
const char str_wireach_format_25[] PROGMEM	= "%d)"; 						// 25
const char str_wireach_format_26[] PROGMEM	= "AT+iIPG?\r\n%s\r\n"; 		// 26
const char str_wireach_format_27[] PROGMEM	= "AT+iSNET?\r\n%s\r\n"; 		// 27
const char str_wireach_format_28[] PROGMEM	= "AT+iDNS1?\r\n%s\r\n"; 		// 28
const char str_wireach_format_29[] PROGMEM	= "AT+iDNS2?\r\n%s\r\n"; 		// 29
const char str_wireach_format_30[] PROGMEM	= "AT+iWLSI?\r\n%s\r\n"; 		// 30
const char str_wireach_format_31[] PROGMEM	= "AT+iMACA?\r\n%s\r\n"; 		// 31


const char* const table_WIFI_FORMAT[] PROGMEM=
{
	str_wireach_format_00,
	str_wireach_format_01,
	str_wireach_format_02,
	str_wireach_format_03,
	str_wireach_format_04,
	str_wireach_format_05,
	str_wireach_format_06,
	str_wireach_format_07,
	str_wireach_format_08,
	str_wireach_format_09,
	str_wireach_format_10,
	str_wireach_format_11,
	str_wireach_format_12,
	str_wireach_format_13,
	str_wireach_format_14,
	str_wireach_format_15,
	str_wireach_format_16,
	str_wireach_format_17,
	str_wireach_format_18,
	str_wireach_format_19,
	str_wireach_format_20,
	str_wireach_format_21,
	str_wireach_format_22,
	str_wireach_format_23,
	str_wireach_format_24,
	str_wireach_format_25,
	str_wireach_format_26,
	str_wireach_format_27,
	str_wireach_format_28,
	str_wireach_format_29,
	str_wireach_format_30,
  str_wireach_format_31,
};





#endif
