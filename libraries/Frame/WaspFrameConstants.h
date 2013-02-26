

#ifndef WaspFrameconstants_h
#define WaspFrameconstants_h


#include <avr/pgmspace.h>



/// Flash defines //////////////////////////////////////////////////////////////


/******************************************************************************* 
 * The following Flash strings, define the tags for all Waspmote sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 * 
 ******************************************************************************/

// Gases
prog_char	str_CO[] 	PROGMEM	= "CO";		// 0	
prog_char 	str_CO2[] 	PROGMEM	= "CO2";	// 1
prog_char 	str_O2[] 	PROGMEM	= "O2";		// 2	
prog_char 	str_CH4[] 	PROGMEM	= "CH4";	// 3	
prog_char 	str_LPG[] 	PROGMEM	= "LPG";	// 4	
prog_char 	str_NH3[] 	PROGMEM	= "NH3";	// 5	
prog_char 	str_AP1[] 	PROGMEM	= "AP1";	// 6	
prog_char 	str_AP2[] 	PROGMEM	= "AP2";	// 7	
prog_char 	str_SV[] 	PROGMEM	= "SV";		// 8	
prog_char 	str_NO2[] 	PROGMEM	= "NO2";	// 9	
prog_char 	str_O3[] 	PROGMEM	= "O3";		// 10	
prog_char 	str_VOC[] 	PROGMEM	= "VOC";	// 11	
prog_char 	str_TCA[] 	PROGMEM	= "TCA";	// 12	
prog_char 	str_TFA[] 	PROGMEM	= "TFA";	// 13	
prog_char 	str_HUMA[] 	PROGMEM	= "HUMA";	// 14	
prog_char 	str_PA[] 	PROGMEM	= "PA";		// 15	

// Events
prog_char	str_PW[] 	PROGMEM	= "PW";		// 16
prog_char	str_BEND[] 	PROGMEM	= "BEND";	// 17
prog_char	str_VBR[] 	PROGMEM	= "VBR";	// 18
prog_char	str_HALL[] 	PROGMEM	= "HALL";	// 19
prog_char	str_LP[] 	PROGMEM	= "LP";		// 20
prog_char	str_LL[] 	PROGMEM	= "LL";		// 21
prog_char	str_LUM[] 	PROGMEM	= "LUM";	// 22
prog_char	str_PIR[] 	PROGMEM	= "PIR";	// 23
prog_char	str_ST[] 	PROGMEM	= "ST";		// 24

// Smart cities
prog_char	str_MCP[] 	PROGMEM	= "MCP";	// 25
prog_char	str_CDG[] 	PROGMEM	= "CDG";	// 26
prog_char	str_CPG[] 	PROGMEM	= "CPG";	// 27
prog_char	str_LD[] 	PROGMEM	= "LD";		// 28
prog_char	str_DUST[] 	PROGMEM	= "DUST";	// 29
prog_char	str_US[] 	PROGMEM	= "US";		// 30

// Smart parking
prog_char	str_MF[] 	PROGMEM	= "MF";		// 31
prog_char	str_PS[] 	PROGMEM	= "PS";		// 32

// Agriculture
prog_char	str_TCB[] 	PROGMEM	= "TCB";	// 33
prog_char	str_TFB[]	PROGMEM = "TFB";	// 34
prog_char	str_HUMB[]	PROGMEM = "HUMB";	// 35
prog_char	str_SOILT[] PROGMEM	= "SOILT";	// 36
prog_char	str_SOIL[] 	PROGMEM	= "SOIL";	// 37
prog_char	str_LW[] 	PROGMEM	= "LW";		// 38
prog_char	str_PAR[] 	PROGMEM	= "PAR";	// 39
prog_char	str_UV[] 	PROGMEM	= "UV";		// 40
prog_char	str_TD[] 	PROGMEM	= "TD";		// 41
prog_char	str_SD[] 	PROGMEM	= "SD";		// 42
prog_char	str_FD[] 	PROGMEM	= "FD";		// 43
prog_char	str_ANE[] 	PROGMEM	= "ANE";	// 44
prog_char	str_WV[] 	PROGMEM	= "WV";		// 45
prog_char	str_PLV[] 	PROGMEM	= "PLV";	// 46

// Radiation
prog_char	str_RAD[] 	PROGMEM	= "RAD";	// 47

// Smart meetering
prog_char	str_CU[] 	PROGMEM	= "CU";		// 48
prog_char	str_WF[] 	PROGMEM	= "WF";		// 49
prog_char	str_LC[] 	PROGMEM	= "LC";		// 50
prog_char	str_DF[] 	PROGMEM	= "DF";		// 51

// Additional
prog_char	str_BAT[] 	PROGMEM	= "BAT";	// 52
prog_char	str_GPS[] 	PROGMEM	= "GPS";	// 53
prog_char	str_RSSI[] 	PROGMEM	= "RSSI";	// 54
prog_char	str_MAC[] 	PROGMEM	= "MAC";	// 55
prog_char	str_NA[] 	PROGMEM	= "NA";		// 56
prog_char	str_NID[] 	PROGMEM	= "NID";	// 57
prog_char	str_DATE[] 	PROGMEM	= "DATE";	// 58
prog_char	str_TIME[] 	PROGMEM	= "TIME";	// 59
prog_char	str_GMT[] 	PROGMEM	= "GMT";	// 60
prog_char	str_RAM[] 	PROGMEM	= "RAM";	// 61
prog_char	str_IN_TEMP[] 	PROGMEM	= "IN_TEMP";	// 62
prog_char	str_ACC[]	PROGMEM = "ACC";	// 63
prog_char	str_MILLIS[] PROGMEM = "MILLIS"; // 64

// Special
prog_char	str_STR[] 	PROGMEM	= "STR";	// 65

// Meshlium
prog_char	str_MBT[] 	PROGMEM	= "MBT";	// 66
prog_char	str_MWIFI[] PROGMEM	= "MWIFI";	// 67

// RFID
prog_char	str_UID[] 	PROGMEM	= "UID";	// 68
prog_char	str_RB[] 	PROGMEM	= "RB";		// 69


/******************************************************************************* 
 * SENSOR_TABLE - Sensor label table
 * 
 * This table specifies the tag for each sensor. Every tag has been previously 
 * defined in Flash memory
 ******************************************************************************/
PROGMEM const char* SENSOR_TABLE[] = 	  
{   
	// Gases
	str_CO,			// 0	
 	str_CO2,		// 1
 	str_O2,			// 2	
 	str_CH4,		// 3	
 	str_LPG,		// 4	
 	str_NH3,		// 5	
 	str_AP1,		// 6	
 	str_AP2,		// 7	
 	str_SV,			// 8	
 	str_NO2,		// 9	
 	str_O3,			// 10	
 	str_VOC,		// 11	
 	str_TCA,		// 12	
 	str_TFA,		// 13	
 	str_HUMA,		// 14	
 	str_PA,			// 15	

	// Events
	str_PW,			// 16
	str_BEND,		// 17
	str_VBR,		// 18
	str_HALL,		// 19
	str_LP,			// 20
	str_LL,			// 21
	str_LUM,		// 22
	str_PIR,		// 23
	str_ST,			// 24

// Smart cities
	str_MCP,		// 25
	str_CDG,		// 26
	str_CPG,		// 27
	str_LD,			// 28
	str_DUST,		// 29
	str_US,			// 30

// Smart parking
	str_MF,			// 31
	str_PS,			// 32

// Agriculture
	str_TCB,		// 33
	str_TFB,		// 34
	str_HUMB,		// 35
	str_SOILT,		// 36
	str_SOIL,		// 37
	str_LW,			// 38
	str_PAR,		// 39
	str_UV,			// 40
	str_TD,			// 41
	str_SD,			// 42
	str_FD,			// 43
	str_ANE,		// 44
	str_WV,			// 45
	str_PLV,		// 46

	// Radiation
	str_RAD,		// 47

	// Smart meetering
	str_CU,			// 48
	str_WF,			// 49
	str_LC,			// 50
	str_DF,			// 51

	// Additional
	str_BAT,		// 52
	str_GPS,		// 53
	str_RSSI,		// 54
	str_MAC,		// 55
	str_NA,			// 56
	str_NID,		// 57
	str_DATE,		// 58
	str_TIME,		// 59
	str_GMT,		// 60
	str_RAM,		// 61
	str_IN_TEMP,	// 62
	str_ACC,		// 63
	str_MILLIS,		// 64

	// Special
	str_STR,		// 65

	// Meshlium
	str_MBT,		// 66
	str_MWIFI,		// 67

	// RFID
	str_UID,		// 68
	str_RB			// 69
	
};


/*******************************************************************************  
 * SENSOR_TYPE_TABLE - Binary frames sensor types
 * 
 * This table specifies the type of sensor depending on the type of value the
 * user must put as input. These are the possibilities:
 *	
 * 	0: uint8_t
 *	1: int (the same as int16_t)  
 *	2: double 
 *	3: char* 
 *  4: unsigned long
 *  5: uint8_t*
 ******************************************************************************/
PROGMEM const uint8_t SENSOR_TYPE_TABLE[] = 	  
{   
	// Gases
	2, // str_CO,		// 0	
	2, // str_CO2,		// 1
	2, // str_O2,		// 2			
	2, // str_CH4,		// 3
	2, // str_LPG,		// 4		
	2, // str_NH3,		// 5	
	2, // str_AP1,		// 6	
	2, // str_AP2,		// 7	
	2, // str_SV,		// 8		
	2, // str_NO2,		// 9		
	2, // str_O3,		// 10
	2, // str_VOC,		// 11	
	2, // str_TCA,		// 12	
	2, // str_TFA,		// 13	
	2, // str_HUMA,		// 14
	2, // str_PA,		// 15	
	
	// Events
	2, // str_PW,		// 16	
	2, // str_BEND,		// 17
	0, // str_VBR,		// 18
	0, // str_HALL,		// 19	
	0, // str_LP,		// 20	
	0, // str_LL,		// 21	
	2, // str_LUM,		// 22	
	0, // str_PIR,		// 23	
	2, // str_ST,		// 24	
	
	// Smart cities
	0, // str_MCP,		// 25
	0, // str_CDG,		// 26
	2, // str_CPG,		// 27
	2, // str_LD,		// 28
	2, // str_DUST,		// 29
	2, // str_US,		// 30
	
	// Smart parking
	1, //str_MF,		// 31
	0, //str_PS,		// 32
	
	// Agriculture
	2, // str_TCB,		// 33
	2, // str_TFB,		// 34
	2, // str_HUMB,		// 35
	2, // str_SOILT,	// 36
	2, // str_SOIL,		// 37
	0, // str_LW,		// 38
	2, // str_PAR,		// 39	
	2, // str_UV,		// 40		
	2, // str_TD,		// 41		
	2, // str_SD,		// 42		
	2, // str_FD,		// 43		
	2, // str_ANE,		// 44	
	0, // str_WV,		// 45	
	2, // str_PLV,		// 46
	
	// Radiation
	2, // str_RAD,		// 47
	
	// Smart meetering	
	2, // str_CU,		// 48
	2, // str_WF,		// 49
	2, // str_LC,		// 50
	2, // str_DF,		// 51
	
	// Additional
	0, // str_BAT,		// 52
	2, // str_GPS,		// 53
	1, // str_RSSI,		// 54
	3, // str_MAC,		// 55
	3, // str_NA,		// 56
	3, // str_NID,		// 57
	0, // str_DATE,		// 58
	0, // str_TIME,		// 59
	1, // str_GMT,		// 60
	1, // str_RAM,		// 61
	2, // str_IN_TEMP,	// 62
	1, // str_ACC,		// 63
	4, // str_MILLIS,	// 64
	
	
	// Special
	3, // str_STR		// 65

	// Meshlium
	3,	// str_MBT		// 66
	3,	//str_MWIFI		// 67

	// RFID
	3,	//str_UID		// 68
	3	//str_RB		// 69
	
};


/*******************************************************************************  
 * SENSOR_FIELD_TABLE - Sensor fields
 * 
 * This table specifies the number of fields per sensor. 
 * 
 * For example, a temperature sensor indicates the temperature in a single field. 
 * On the other hand, the GPS module indicates the position with two fields: 
 * latitude and longitude
 ******************************************************************************/
PROGMEM const uint8_t SENSOR_FIELD_TABLE[] = 	  
{   
	// Gases
	1, // str_CO,		// 0
	1, // str_CO2,		// 1
	1, // str_O2,		// 2
	1, // str_CH4,		// 3
	1, // str_LPG,		// 4
	1, // str_NH3,		// 5
	1, // str_AP1,		// 6
	1, // str_AP2,		// 7
	1, // str_SV,		// 8
	1, // str_NO2,		// 9	
	1, // str_O3,		// 10
	1, // str_VOC,		// 11
	1, // str_TCA,		// 12
	1, // str_TFA,		// 13	
	1, // str_HUMA,		// 14
	1, // str_PA,		// 15
	
	// Events
	1, // str_PW,		// 16
	1, // str_BEND,		// 17
	1, // str_VBR,		// 18
	1, // str_HALL,		// 19
	1, // str_LP,		// 20	
	1, // str_LL,		// 21	
	1, // str_LUM,		// 22	
	1, // str_PIR,		// 23	
	1, // str_ST,		// 24
	
	// Smart cities
	1, // str_MCP,		// 25
	1, // str_CDG,		// 26
	1, // str_CPG,		// 27
	1, // str_LD,		// 28
	1, // str_DUST,		// 29
	1, // str_US,		// 30
	
	// Smart parking
	3, //str_MF,		// 31
	1, //str_PS,		// 32
	
	// Agriculture
	1, // str_TCB,		// 33
	1, // str_TFB,		// 34
	1, // str_HUMB,		// 35
	1, // str_SOILT,	// 36
	1, // str_SOIL,		// 37
	1, // str_LW,		// 38	
	1, // str_PAR,		// 39
	1, // str_UV,		// 40	
	1, // str_TD,		// 41		
	1, // str_SD,		// 42	
	1, // str_FD,		// 43	
	1, // str_ANE,		// 44
	1, // str_WV,		// 45	
	1, // str_PLV,		// 46
	
	// Radiation
	1, // str_RAD,		// 47
	
	// Smart meetering
	1, // str_CU,		// 48
	1, // str_WF,		// 49
	1, // str_LC,		// 50
	1, // str_DF,		// 51
	
	// Additional
	1, // str_BAT,		// 52
	2, // str_GPS,		// 53
	1, // str_RSSI,		// 54
	1, // str_MAC,		// 55
	1, // str_NA,		// 56
	1, // str_NID,		// 57
	3, // str_DATE,		// 58
	3, // str_TIME,		// 59
	1, // str_GMT,		// 60	
	1, // str_RAM,		// 61
	1, // str_IN_TEMP,	// 62
	3, // str_ACC,		// 63
	1, // str_MILLIS,	// 64	
	
	// Special
	1, // str_STR		// 65

	// Meshlium
	1, // str_MBT		// 66
	1, //str_MWIFI		// 67

	// RFID
	1, //str_UID		// 68
	1  //str_RB			// 69
	
};



/******************************************************************************* 
 * DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
 * 
 * This table specifies the number of decimals for each sensor for ASCII frames
 ******************************************************************************/
PROGMEM const uint8_t DECIMAL_TABLE[] = 	  
{   
	// Gases
	3, // str_CO,		// 0
	3, // str_CO2,		// 1
	3, // str_O2,		// 2
	3, // str_CH4,		// 3
	3, // str_LPG,		// 4
	3, // str_NH3,		// 5
	3, // str_AP1,		// 6
	3, // str_AP2,		// 7
	3, // str_SV,		// 8	
	3, // str_NO2,		// 9	
	3, // str_O3,		// 10
	3, // str_VOC,		// 11
	2, // str_TCA,		// 12
	2, // str_TFA,		// 13	
	1, // str_HUMA,		// 14
	2, // str_PA,		// 15
	
	// Events
	3, // str_PW,		// 16	
	3, // str_BEND,		// 17
	0, // str_VBR,		// 18

	0, // str_HALL,		// 19
	0, // str_LP,		// 20	
	0, // str_LL,		// 21	
	3, // str_LUM,		// 22	
	0, // str_PIR,		// 23	
	3, // str_ST,		// 24
	
	// Smart cities
	0, // str_MCP,		// 25
	0, // str_CDG,		// 26
	3, // str_CPG,		// 27
	3, // str_LD,		// 28
	3, // str_DUST,		// 29
	2, // str_US,		// 30
	
	// Smart parking
	0, //str_MF,		// 31
	0, //str_PS,		// 32
	
	// Agriculture
	2, // str_TCB,		// 33
	2, // str_TFB,		// 34
	1, // str_HUMB,		// 35
	2, // str_SOILT,	// 36
	2, // str_SOIL,		// 37
	0, // str_LW,		// 38	
	2, // str_PAR,		// 39
	2, // str_UV,		// 40	
	3, // str_TD,		// 41		
	3, // str_SD,		// 42	
	3, // str_FD,		// 43	
	2, // str_ANE,		// 44
	0, // str_WV,		// 45	
	2, // str_PLV,		// 46
	
	// Radiation
	6, // str_RAD,		// 47
	
	// Smart meetering
	2, // str_CU,		// 48
	3, // str_WF,		// 49
	3, // str_LC,		// 50
	3, // str_DF,		// 51
	
	// Additional
	0, // str_BAT,		// 52	
	6, // str_GPS,		// 53
	0, // str_RSSI,		// 54
	0, // str_MAC,		// 55
	0, // str_NA,		// 56
	0, // str_NID,		// 57
	0, // str_DATE,		// 58
	0, // str_TIME,		// 59
	0, // str_GMT,		// 60	
	0, // str_RAM,		// 61
	2, // str_IN_TEMP,	// 62
	0, // str_ACC,		// 63
	0, // str_MILLIS,	// 64	
	
	// Special
	0, // str_STR		// 65

	// Meshlium
	0, // str_MBT		// 66
	0, //str_MWIFI		// 67

	// RFID
	0, //str_UID		// 68
	0  //str_RB			// 69
	
};

#endif
