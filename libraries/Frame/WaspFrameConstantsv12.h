/*! \file WaspFrameConstants.h
    \brief Header file for Waspmote v12 Frame Constants

    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		3.0
    Design:			David Gascón
    Implementation:	Yuri Carmona, Javier Siscart, Joaquín Ruiz, Alejandro Gallego

*/


#ifndef WaspFrameconstants_h
#define WaspFrameconstants_h


#include <avr/pgmspace.h>


////////////////////////////////////////////////////////////////////////////////
// Waspmote v12 FRAME definitions
////////////////////////////////////////////////////////////////////////////////


/// Gases Board sensor measurements

/*! \def SENSOR_CO
    \brief Carbon Monoxide measurement type
 */
/*! \def SENSOR_CO2
    \brief Carbon Dioxide measurement type
 */
/*! \def SENSOR_O2
    \brief Oxygen measurement type
 */
/*! \def SENSOR_CH4
    \brief Methane measurement type
 */
/*! \def SENSOR_LPG
    \brief Liquefied Pretoleum Gases measurement type
 */
/*! \def SENSOR_NH3
    \brief Ammonia measurement type
 */
/*! \def SENSOR_AP1
    \brief Air Pollutans 1 measurement type
 */
/*! \def SENSOR_AP2
    \brief Air Pollutans 2 measurement type
 */
/*! \def SENSOR_SV
    \brief Solvent Vapors measurement type
 */
/*! \def SENSOR_NO2
    \brief Nitrogen Dioxide measurement type
 */
/*! \def SENSOR_O3
    \brief Ozone measurement type
 */
/*! \def SENSOR_VOC
    \brief Hydrocarbons measurement type
 */
/*! \def SENSOR_TC
    \brief Temperature Celsius measurement type
 */
/*! \def SENSOR_TF
    \brief Temperature Fahrenheit measurement type
 */
/*! \def SENSOR_HUM
    \brief Humidity measurement type
 */
/*! \def SENSOR_PA
    \brief Pressure atmospheric measurement type
 */


/// Events Board Sensor measurements

/*! \def SENSOR_PW
    \brief Pressure/Weight measurement type
 */
/*! \def SENSOR_BEND
    \brief Bend measurement type
 */
/*! \def SENSOR_VBR
    \brief Vibration measurement type
 */
/*! \def SENSOR_HALL
    \brief Hall Effect measurement type
 */
/*! \def SENSOR_LP
    \brief Liquid Presence measurement type
 */
/*! \def SENSOR_LL
    \brief Liquid Level measurement type
 */
/*! \def SENSOR_LUM
    \brief Luminosity measurement type
 */
/*! \def SENSOR_PIR
    \brief Presence measurement type
 */
/*! \def SENSOR_ST
    \brief Stretch measurement type
 */


/// Smart cities sensor measurements

/*! \def SENSOR_MCP
    \brief Microphone measurement type
 */
/*! \def SENSOR_CDG
    \brief Crack detection gauge measurement type
 */
/*! \def SENSOR_CPG
    \brief Crack propagation gauge measurement type
 */
/*! \def SENSOR_LD
    \brief Linear Displacement measurement type
 */
/*! \def SENSOR_DUST
    \brief Dust measurement type
 */
/*! \def SENSOR_US
    \brief Ultrasound measurement type
 */


/// Smart parking sensor measurements

/*! \def SENSOR_MF
    \brief Magnetic Field measurement type
 */
/*! \def SENSOR_PS
    \brief Parking Spot Status measurement type
 */

/// Agriculture sensor measurements

/*! \def SENSOR_AIR
    \brief Air Temperature / Humidity measurement type
 */
/*! \def SENSOR_SOIL
    \brief Soil Temperature / Moisture measurement type
 */
/*! \def SENSOR_LW
    \brief Leaf Wetness measurement type
 */
/*! \def SENSOR_PAR
    \brief Solar Radiation measurement type
 */
/*! \def SENSOR_UV
    \brief Ultraviolet Radiation measurement type
 */
/*! \def SENSOR_TD
    \brief Trunk Diameter measurement type
 */
/*! \def SENSOR_SD
    \brief Stem Diameter measurement type
 */
/*! \def SENSOR_FD
    \brief Fruit Diameter measurement type
 */
/*! \def SENSOR_ANE
    \brief Anemometer measurement type
 */
/*! \def SENSOR_WV
    \brief Wind Vane measurement type
 */
/*! \def SENSOR_PLV
    \brief Pluviometer measurement type
 */


/// Radiation sensor measurements

/*! \def SENSOR_RAD
    \brief Geiger tube measurement type
 */


/// Smart Metering sensor measurements

/*! \def SENSOR_CU
    \brief Current measurement type
 */
/*! \def SENSOR_WF
    \brief Water flow measurement type
 */
/*! \def SENSOR_LC
    \brief Load cell measurement type
 */
/*! \def SENSOR_DF
    \brief Distance foil measurement type
 */


/// Additional sensor measurements

/*! \def SENSOR_BAT
    \brief Battery measurement type
 */
/*! \def SENSOR_GPS
    \brief Global Positioning System measurement type
 */
/*! \def SENSOR_RSSI
    \brief RSSI measurement type
 */
/*! \def SENSOR_MAC
    \brief MAC Address measurement type
 */
/*! \def SENSOR_NA
    \brief Network Address measurement type
 */
/*! \def SENSOR_NID
    \brief Network Identifier origin measurement type
 */
/*! \def SENSOR_DATE
    \brief Date measurement type
 */
/*! \def SENSOR_TIME
    \brief Time measurement type
 */
/*! \def SENSOR_GMT
    \brief GMT measurement type
 */
/*! \def SENSOR_RAM
    \brief RAM measurement type
 */
/*! \def SENSOR_IN_TEMP
    \brief Internal temperature measurement type
 */
/*! \def SENSOR_MILLIS
    \brief Millis measurement type
 */

/// Special sensor measurements

/*! \def SENSOR_STR
    \brief String type
 */

/// Smart Water

/*! \def SENSOR_PH
    \brief pH measurement type
 */
/*! \def SENSOR_ORP
    \brief Oxidation Reduction Potential measurement type
 */
/*! \def SENSOR_DI
    \brief Disolved Ion measurement type
 */
/*! \def SENSOR_DO
    \brief Disolved Oxygen measurement type
 */
/*! \def SENSOR_COND
    \brief Conductivity measurement type
 */
/*! \def SENSOR_WT
    \brief Water Temperature measurement type
 */


/// Smart Libelium
/*! \def SENSOR_DM_ST
    \brief XBee Digimesh awake time for cyclic sleep mode
 */
/*! \def SENSOR_DM_SP
    \brief XBee Digimesh asleep time for cyclic sleep mode
 */
/*! \def SENSOR_TX_PWR
    \brief XBee transmision power
 */
/*! \def SENSOR_LUX
    \brief Luxes measurement type
 */


/// GPS
/*! \def SENSOR_SPEED
    \brief GPS speed over the ground measurement type
 */
/*! \def SENSOR_COURSE
    \brief GPS course over the ground measurement type
 */
/*! \def SENSOR_ALTITUDE
    \brief GPS altitude over the ground measurement type
 */
/*! \def SENSOR_HDOP
    \brief GPS HDOP over the ground measurement type
 */
/*! \def SENSOR_VDOP
    \brief GPS VDOP over the ground measurement type
 */
/*! \def SENSOR_PDOP
    \brief GPS PDOP over the ground measurement type
 */


/// State Machine
/*! \def SENSOR_FSM
    \brief Finite State Machine (FSM) value
 */


/// New pluviometer values
/*! \def SENSOR_PLV1
    \brief pluviomter value for current hour
 */
 /*! \def SENSOR_PLV2
    \brief pluviomter value for previous hour
 */
 /*! \def SENSOR_PLV3
    \brief pluviomter value for last 24h
 */

/// P&S watermarks
/*! \def SENSOR_SOIL_C
    \brief watermark value for P&S connector C
 */
 /*! \def SENSOR_SOIL_D
    \brief watermark value for P&S connector D
 */
 /*! \def SENSOR_SOIL_E
    \brief watermark value for P&S connector E
 */
 /*! \def SENSOR_SOIL_F
    \brief watermark value for P&S connector F
 */

/// Waspmote OEM watermarks
/*! \def SENSOR_SOIL1
    \brief Agriculture Board watermark1
 */
 /*! \def SENSOR_SOIL2
    \brief Agriculture Board watermark2
 */
 /*! \def SENSOR_SOIL3
    \brief Agriculture Board watermark3
 */

 /// DS18B20
 /*! \def SENSOR_TCC
    \brief DS18B20 temperature sensor
 */

 /// P&S Ultrasound depending on socket voltage ref
 /*! \def SENSOR_US_3V3
    \brief WRA1 Ultrasound sensor powered at 3V3
 */
/*! \def SENSOR_US_5V
    \brief WRA1 Ultrasound sensor powered at 5V
 */


/// P&S Security sensors depending on socket (Security - Events board)
 /*! \def SENSOR_LUM_D
    \brief LDR sensor in socket D
 */
/*! \def SENSOR_LUM_E
    \brief LDR sensor in socket E
 */
 /*! \def SENSOR_LUM_F
    \brief LDR sensor in socket F
 */
 /*! \def SENSOR_LP_D
    \brief Liquid Presence sensor in socket D
 */
 /*! \def SENSOR_LP_E
    \brief Liquid Presence sensor in socket E
 */
 /*! \def SENSOR_LP_F
    \brief Liquid Presence sensor in socket F
 */
 /*! \def SENSOR_LL_D
    \brief Liquid Level sensor in socketD
 */
 /*! \def SENSOR_LL_E
    \brief Liquid Level sensor in socketE
 */
 /*! \def SENSOR_LL_F
    \brief Liquid Level sensor in socketF
 */
 /*! \def SENSOR_HALL_D
    \brief Hall Effect sensor in socket D
 */
 /*! \def SENSOR_HALL_E
    \brief Hall Effect sensor in socket E
 */
 /*! \def SENSOR_HALL_F
    \brief Hall Effect sensor in socket F
 */

/// P&S liquid flow sensor depending on socket (Smart Metering)
/*! \def SENSOR_WF_C
    \brief Liquid Flow sensor in socket C
 */
/*! \def SENSOR_WF_E
    \brief Liquid Flow sensor in socket E
 */

/// Unix/Epoch timestamp
/*! \def SENSOR_TST
    \brief Unix (aka Epoch) timestamp value
 */

/// Turbidity sensor
/*! \def SENSOR_TURB
    \brief Turbidity sensor
 */


/// Version parameters
/*! \def SENSOR_VAPI
    \brief API version
 */
/*! \def SENSOR_VPROG
    \brief Program version
 */
/*! \def SENSOR_VBOOT
    \brief Bootloader version
 */


/// Gases PRO
/*! \def SENSOR_GP_CL2
    \brief Chlorine measurement type
 */
/*! \def SENSOR_GP_CO
    \brief Carbon Monoxide measurement type
 */
/*! \def SENSOR_GP_ETO
    \brief Ethylene Oxide measurement type
 */
/*! \def SENSOR_GP_H2
    \brief Hydrogen measurement type
 */
/*! \def SENSOR_GP_H2S
    \brief Hydrogen Sulphide measurement type
 */
/*! \def SENSOR_GP_HCL
    \brief Hydrogen Chloride measurement type
 */
/*! \def SENSOR_GP_HCN
    \brief Hydrogen Cyanide measurement type
 */
/*! \def SENSOR_GP_NH3
    \brief Ammonia measurement type
 */
/*! \def SENSOR_GP_NO
    \brief Nitrogen Monoxide measurement type
 */
/*! \def SENSOR_GP_NO2
    \brief Nitrogen Dioxide measurement type
 */
/*! \def SENSOR_GP_O2
    \brief Oxygen measurement type
 */
/*! \def SENSOR_GP_PH3
    \brief Phospine measurement type
 */
/*! \def SENSOR_GP_SO2
    \brief Sulfur Dioxide measurement type
 */
/*! \def SENSOR_GP_CH4
    \brief Methane and other combustible gases measurement type
 */
/*! \def SENSOR_GP_O3
    \brief Ozone measurement type
 */
/*! \def SENSOR_GP_CO2
    \brief Carbon Dioxide measurement type
 */
/*! \def SENSOR_GP_TC
    \brief Temperature Celsius measurement type
 */
/*! \def SENSOR_GP_TF
    \brief Temperature Fahrenheit measurement type
 */
/*! \def SENSOR_GP_HUM
    \brief Humidity measurement type
 */
/*! \def SENSOR_GP_PRES
    \brief Pressure measurement type
 */
/*! \def SENSOR_OPC_TC
    \brief Temperature Celsius measurement type
 */
/*! \def SENSOR_OPC_TF
    \brief Temperature Fahrenheit measurement type
 */
/*! \def SENSOR_OPC_PM1
    \brief PM1 measurement type
 */
/*! \def SENSOR_OPC_PM2_5
    \brief PM2.5 measurement type
 */
/*! \def SENSOR_OPC_PM10
    \brief PM10 measurement type
 */
/*! \def SENSOR_OPC_PART
    \brief Particle bin counter measurement type
 */
/*! \def SENSOR_SWI_CA
    \brief Calcium ion measurement type
 */
/*! \def SENSOR_SWI_FL
    \brief Fluoride ion measurement type
 */
/*! \def SENSOR_SWI_BF
    \brief Tetrafluoroborate ion measurement type
 */
/*! \def SENSOR_SWI_NO
    \brief Nitrates ion measurement type
 */
/*! \def SENSOR_SWI_BR
    \brief Bromide ion measurement type
 */
/*! \def SENSOR_SWI_CL
    \brief Chlorideion measurement type
 */
/*! \def SENSOR_SWI_CU
    \brief Cupric ion measurement type
 */
/*! \def SENSOR_SWI_IO
    \brief Iodide ion measurement type
 */
/*! \def SENSOR_SWI_PB
    \brief Lead ion measurement type
 */
/*! \def SENSOR_SWI_AG
    \brief Silver ion measurement type
 */
/*! \def SENSOR_SWI_PH
    \brief pH (for Smart Water Ions) measurement type
 */


// Gases v20
#define SENSOR_CO	 		0
#define SENSOR_CO2 			1
#define SENSOR_O2			2
#define SENSOR_CH4			3
#define SENSOR_LPG			4
#define SENSOR_NH3			5
#define SENSOR_AP1			6
#define SENSOR_AP2			7
#define SENSOR_SV			8
#define SENSOR_NO2			9
#define SENSOR_O3			10
#define SENSOR_VOC			11
#define SENSOR_TCA			12
#define SENSOR_TFA			13
#define SENSOR_HUMA			14
#define SENSOR_PA			15

// Events v20
#define SENSOR_PW  			16
#define SENSOR_BEND 		17
#define SENSOR_VBR  		18
#define SENSOR_HALL 		19
#define SENSOR_LP  			20
#define SENSOR_LL  			21
#define SENSOR_LUM  		22
#define SENSOR_PIR  		23
#define SENSOR_ST  			24

// Smart Cities
#define SENSOR_MCP  		25
#define SENSOR_CDG  		26
#define SENSOR_CPG  		27
#define SENSOR_LD  			28
#define SENSOR_DUST			29
#define SENSOR_US  			30

// Smart parking
#define SENSOR_MF			31
#define SENSOR_PS			32

// Agriculture
#define SENSOR_TCB			33
#define SENSOR_TFB			34
#define SENSOR_HUMB			35
#define SENSOR_SOILT 		36
#define SENSOR_SOIL 		37
#define SENSOR_LW  			38
#define SENSOR_PAR  		39
#define SENSOR_UV  			40
#define SENSOR_TD  			41
#define SENSOR_SD  			42
#define SENSOR_FD  			43
#define SENSOR_ANE  		44
#define SENSOR_WV  			45
#define SENSOR_PLV  		46

// Radiation
#define SENSOR_RAD  		47

// Smart metering
#define SENSOR_CU  			48
#define SENSOR_WF  			49
#define SENSOR_LC  			50
#define SENSOR_DF  			51

// Additional
#define SENSOR_BAT  		52
#define SENSOR_GPS  		53
#define SENSOR_RSSI  		54
#define SENSOR_MAC  		55
#define SENSOR_NA  			56
#define SENSOR_NID  		57
#define SENSOR_DATE 		58
#define SENSOR_TIME 		59
#define SENSOR_GMT  		60
#define SENSOR_RAM			61
#define SENSOR_IN_TEMP		62
#define SENSOR_ACC			63
#define SENSOR_MILLIS		64

// Special
#define SENSOR_STR	 		65

// Meshlium
#define SENSOR_MBT	 		66
#define SENSOR_MWIFI 		67

// RFID
#define SENSOR_UID			68
#define SENSOR_RB	 		69

// Smart Water
#define SENSOR_PH			70
#define SENSOR_ORP	 		71
#define SENSOR_DO	 		72
#define SENSOR_COND	 		73
#define SENSOR_WT	 		74
#define SENSOR_DINA	 		75
#define SENSOR_DICA	 		76
#define SENSOR_DIF	 		77
#define SENSOR_DICL	 		78
#define SENSOR_DIBR	 		79
#define SENSOR_DII	 		80
#define SENSOR_DICU2		81
#define SENSOR_DIK	 		82
#define SENSOR_DIMG2		83
#define SENSOR_DINO3		84

// Smart Libelium
#define SENSOR_TX_PWR		85
#define SENSOR_DM_ST		86
#define SENSOR_DM_SP		87
#define SENSOR_LUX			88

// GPS
#define SENSOR_SPEED		89
#define SENSOR_COURSE		90
#define SENSOR_ALTITUDE		91
#define SENSOR_HDOP			92
#define SENSOR_VDOP			93
#define SENSOR_PDOP			94

// Finite State Machine status
#define SENSOR_FSM			95

// New pluviometer values
#define SENSOR_PLV1  		96
#define SENSOR_PLV2  		97
#define SENSOR_PLV3  		98

// P&S watermark sensors (Smart Agriculture)
#define SENSOR_SOIL_C  		99
#define SENSOR_SOIL_D  		100
#define SENSOR_SOIL_E  		101
#define SENSOR_SOIL_F  		102

// Waspmote OEM watermark sensors
#define SENSOR_SOIL1  		103
#define SENSOR_SOIL2  		104
#define SENSOR_SOIL3  		105

// DS18B20
#define SENSOR_TCC  		106

// P&S Ultrasound depending on socket voltage ref (Smart Cities & Smart Metering)
#define SENSOR_US_3V3  		107
#define SENSOR_US_5V  		108

// P&S Security sensors depending on socket (Smart Security)
#define SENSOR_LUM_D		109
#define SENSOR_LUM_E		110
#define SENSOR_LUM_F		111
#define SENSOR_LP_D			112
#define SENSOR_LP_E			113
#define SENSOR_LP_F			114
#define SENSOR_LL_D			115
#define SENSOR_LL_E			116
#define SENSOR_LL_F			117
#define SENSOR_HALL_D		118
#define SENSOR_HALL_E		119
#define SENSOR_HALL_F		120

// P&S liquid flow sensor depending on socket (Smart Metering)
#define SENSOR_WF_C			121
#define SENSOR_WF_E			122

// Unix/Epoch timestamp
#define SENSOR_TST			123

// Turbidity sensor
#define SENSOR_TURB			124

// Version parameters
#define SENSOR_VAPI			125
#define SENSOR_VPROG		126
#define SENSOR_VBOOT		127


// Gases PRO
#define SENSOR_GP_CL2		128
#define SENSOR_GP_CO		129
#define SENSOR_GP_ETO		130
#define SENSOR_GP_H2		131
#define SENSOR_GP_H2S		132
#define SENSOR_GP_HCL		133
#define SENSOR_GP_HCN		134
#define SENSOR_GP_NH3		135
#define SENSOR_GP_NO		136
#define SENSOR_GP_NO2		137
#define SENSOR_GP_O2		138
#define SENSOR_GP_PH3		139
#define SENSOR_GP_SO2		140
#define SENSOR_GP_CH4		141
#define SENSOR_GP_O3		142
#define SENSOR_GP_CO2		143
#define SENSOR_GP_TC		144
#define SENSOR_GP_TF		145
#define SENSOR_GP_HUM		146
#define SENSOR_GP_PRES		147

// OPCN2 Dust Sensor
#define SENSOR_OPC_TC		148
#define SENSOR_OPC_TF		149
#define SENSOR_OPC_P		150
#define SENSOR_OPC_PM1		151
#define SENSOR_OPC_PM2_5	152
#define SENSOR_OPC_PM10		153
#define SENSOR_OPC_PART		154

// Smart Water Ions
#define SENSOR_SWI_CA		155
#define SENSOR_SWI_FL		156
#define SENSOR_SWI_FB		157
#define SENSOR_SWI_NO		158
#define SENSOR_SWI_BR		159
#define SENSOR_SWI_CL		160
#define SENSOR_SWI_CU		161
#define SENSOR_SWI_IO		162
#define SENSOR_SWI_PB		163
#define SENSOR_SWI_AG		164
#define SENSOR_SWI_PH		165

// P&S Smart Water sensors depending on socket (Smart Water)
#define SENSOR_PH_A			166
#define SENSOR_PH_B			167
#define SENSOR_PH_C			168
#define SENSOR_ORP_A		169
#define SENSOR_ORP_B		170
#define SENSOR_ORP_C		171

#define SENSOR_OPCN3_BIN		172
#define SENSOR_OPCN2_BIN		173




/// Flash defines //////////////////////////////////////////////////////////////


/*******************************************************************************
 * The following Flash strings, define the tags for all Waspmote sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 *
 ******************************************************************************/

// Gases
const char	str_CO[] 	PROGMEM	= "CO";		// 0
const char 	str_CO2[] 	PROGMEM	= "CO2";	// 1
const char 	str_O2[] 	PROGMEM	= "O2";		// 2
const char 	str_CH4[] 	PROGMEM	= "CH4";	// 3
const char 	str_LPG[] 	PROGMEM	= "LPG";	// 4
const char 	str_NH3[] 	PROGMEM	= "NH3";	// 5
const char 	str_AP1[] 	PROGMEM	= "AP1";	// 6
const char 	str_AP2[] 	PROGMEM	= "AP2";	// 7
const char 	str_SV[] 	PROGMEM	= "SV";		// 8
const char 	str_NO2[] 	PROGMEM	= "NO2";	// 9
const char 	str_O3[] 	PROGMEM	= "O3";		// 10
const char 	str_VOC[] 	PROGMEM	= "VOC";	// 11
const char 	str_TCA[] 	PROGMEM	= "TCA";	// 12
const char 	str_TFA[] 	PROGMEM	= "TFA";	// 13
const char 	str_HUMA[] 	PROGMEM	= "HUMA";	// 14
const char 	str_PA[] 	PROGMEM	= "PA";		// 15

// Events
const char	str_PW[] 	PROGMEM	= "PW";		// 16
const char	str_BEND[] 	PROGMEM	= "BEND";	// 17
const char	str_VBR[] 	PROGMEM	= "VBR";	// 18
const char	str_HALL[] 	PROGMEM	= "HALL";	// 19
const char	str_LP[] 	PROGMEM	= "LP";		// 20
const char	str_LL[] 	PROGMEM	= "LL";		// 21
const char	str_LUM[] 	PROGMEM	= "LUM";	// 22
const char	str_PIR[] 	PROGMEM	= "PIR";	// 23
const char	str_ST[] 	PROGMEM	= "ST";		// 24

// Smart cities
const char	str_MCP[] 	PROGMEM	= "MCP";	// 25
const char	str_CDG[] 	PROGMEM	= "CDG";	// 26
const char	str_CPG[] 	PROGMEM	= "CPG";	// 27
const char	str_LD[] 	PROGMEM	= "LD";		// 28
const char	str_DUST[] 	PROGMEM	= "DUST";	// 29
const char	str_US[] 	PROGMEM	= "US";		// 30

// Smart parking
const char	str_MF[] 	PROGMEM	= "MF";		// 31
const char	str_PS[] 	PROGMEM	= "PS";		// 32

// Agriculture
const char	str_TCB[] 	PROGMEM	= "TCB";	// 33
const char	str_TFB[]	PROGMEM = "TFB";	// 34
const char	str_HUMB[]	PROGMEM = "HUMB";	// 35
const char	str_SOILT[] PROGMEM	= "SOILT";	// 36
const char	str_SOIL[] 	PROGMEM	= "SOIL";	// 37
const char	str_LW[] 	PROGMEM	= "LW";		// 38
const char	str_PAR[] 	PROGMEM	= "PAR";	// 39
const char	str_UV[] 	PROGMEM	= "UV";		// 40
const char	str_TD[] 	PROGMEM	= "TD";		// 41
const char	str_SD[] 	PROGMEM	= "SD";		// 42
const char	str_FD[] 	PROGMEM	= "FD";		// 43
const char	str_ANE[] 	PROGMEM	= "ANE";	// 44
const char	str_WV[] 	PROGMEM	= "WV";		// 45
const char	str_PLV[] 	PROGMEM	= "PLV";	// 46

// Radiation
const char	str_RAD[] 	PROGMEM	= "RAD";	// 47

// Smart meetering
const char	str_CU[] 	PROGMEM	= "CU";		// 48
const char	str_WF[] 	PROGMEM	= "WF";		// 49
const char	str_LC[] 	PROGMEM	= "LC";		// 50
const char	str_DF[] 	PROGMEM	= "DF";		// 51

// Additional
const char	str_BAT[] 	PROGMEM	= "BAT";	// 52
const char	str_GPS[] 	PROGMEM	= "GPS";	// 53
const char	str_RSSI[] 	PROGMEM	= "RSSI";	// 54
const char	str_MAC[] 	PROGMEM	= "MAC";	// 55
const char	str_NA[] 	PROGMEM	= "NA";		// 56
const char	str_NID[] 	PROGMEM	= "NID";	// 57
const char	str_DATE[] 	PROGMEM	= "DATE";	// 58
const char	str_TIME[] 	PROGMEM	= "TIME";	// 59
const char	str_GMT[] 	PROGMEM	= "GMT";	// 60
const char	str_RAM[] 	PROGMEM	= "RAM";	// 61
const char	str_IN_TEMP[] 	PROGMEM	= "IN_TEMP";	// 62
const char	str_ACC[]	PROGMEM = "ACC";	// 63
const char	str_MILLIS[] PROGMEM = "MILLIS"; // 64

// Special
const char	str_STR[] 	PROGMEM	= "STR";	// 65

// Meshlium
const char	str_MBT[] 	PROGMEM	= "MBT";	// 66
const char	str_MWIFI[] PROGMEM	= "MWIFI";	// 67

// RFID
const char	str_UID[] 	PROGMEM	= "UID";	// 68
const char	str_RB[] 	PROGMEM	= "RB";		// 69

// Smart Water
const char	str_PH[] 	PROGMEM	= "PH";		// 70
const char	str_ORP[] 	PROGMEM	= "ORP";	// 71
const char	str_DO[] 	PROGMEM	= "DO";		// 72
const char	str_COND[] 	PROGMEM	= "COND";	// 73
const char	str_WT[] 	PROGMEM	= "WT";		// 74
const char	str_DINA[] 	PROGMEM	= "DINA";	// 75
const char	str_DICA[] 	PROGMEM	= "DICA";	// 76
const char	str_DIF[] 	PROGMEM	= "DIF";	// 77
const char	str_DICL[] 	PROGMEM	= "DICL";	// 78
const char	str_DIBR[] 	PROGMEM	= "DIBR";	// 79
const char	str_DII[] 	PROGMEM	= "DII";	// 80
const char	str_DICU2[] PROGMEM	= "DICU2";	// 81
const char	str_DIK[] 	PROGMEM	= "DIK";	// 82
const char	str_DIMG2[] PROGMEM	= "DIMG2";	// 83
const char	str_DINO3[] PROGMEM	= "DINO3";	// 84

//Smart Libelium
const char	str_TX_PWR[]	PROGMEM = "TX_PWR";	// 85
const char	str_DM_ST[]		PROGMEM = "DM_ST";	// 86
const char	str_DM_SP[]		PROGMEM = "DM_SP";	// 87
const char	str_LUX[]		PROGMEM = "LUX";	// 88

//GPS
const char	str_SPEED[]		PROGMEM = "SPEED_OG";	// 89
const char	str_COURSE[]	PROGMEM = "COURSE_OG";	// 90
const char	str_ALTITUDE[]	PROGMEM = "ALT";		// 91
const char	str_HDOP[]		PROGMEM = "HDOP";		// 92
const char	str_VDOP[]		PROGMEM = "VDOP";		// 93
const char	str_PDOP[]		PROGMEM = "PDOP";		// 94

// Finite State Machine status
const char	str_FSM[]	PROGMEM = "FSM";		// 95

// New Pluviometer values
const char	str_PLV1[]	PROGMEM = "PLV1";		// 96
const char	str_PLV2[]	PROGMEM = "PLV2";		// 97
const char	str_PLV3[]	PROGMEM = "PLV3";		// 98

// P&S Watermarks depending on P&S connector
const char	str_SOIL_C[]	PROGMEM = "SOIL_C";		// 99
const char	str_SOIL_D[]	PROGMEM = "SOIL_D";		// 100
const char	str_SOIL_E[]	PROGMEM = "SOIL_E";		// 101
const char	str_SOIL_F[]	PROGMEM = "SOIL_F";		// 102

// Waspmote OEM watermark sensors (same as library)
const char	str_SOIL1[]	PROGMEM = "SOIL1";		// 103
const char	str_SOIL2[]	PROGMEM = "SOIL2";		// 104
const char	str_SOIL3[]	PROGMEM = "SOIL3";		// 105

// DS18B20 (temperature: air, water, soil)
const char	str_TCC[]	PROGMEM = "TCC";		// 106

// P&S Ultrasound depending on socket voltage ref
const char	str_US_3V3[]	PROGMEM = "US_3V3";	// 107
const char	str_US_5V[]		PROGMEM = "US_5V";	// 108

// P&S Security sensors depending on socket (Events board)
const char	str_LUM_D[]		PROGMEM = "LUM_D";	// 109
const char	str_LUM_E[]		PROGMEM = "LUM_E";	// 110
const char	str_LUM_F[]		PROGMEM = "LUM_F";	// 111
const char	str_LP_D[]		PROGMEM = "LP_D";	// 112
const char	str_LP_E[]		PROGMEM = "LP_E";	// 113
const char	str_LP_F[]		PROGMEM = "LP_F";	// 114
const char	str_LL_D[]		PROGMEM = "LL_D";	// 115
const char	str_LL_E[]		PROGMEM = "LL_E";	// 116
const char	str_LL_F[]		PROGMEM = "LL_F";	// 117
const char	str_HALL_D[]	PROGMEM = "HALL_D";	// 118
const char	str_HALL_E[]	PROGMEM = "HALL_E";	// 119
const char	str_HALL_F[]	PROGMEM = "HALL_F";	// 120

// P&S liquid flow sensor depending on socket (Smart Metering)
const char	str_WF_C[]		PROGMEM = "WF_C";	// 121
const char	str_WF_E[]		PROGMEM = "WF_E";	// 122

// Unix Epoch timestamp
const char	str_TST[]		PROGMEM = "TST";	// 123

// Turbidity sensor
const char	str_TURB[]		PROGMEM = "TURB";	// 124

// Version parameters
const char	str_VAPI[]	PROGMEM = "VAPI";	// 125
const char	str_VPROG[]	PROGMEM = "VPROG";	// 126
const char	str_VBOOT[]	PROGMEM = "VBOOT";	// 127


// Gases PRO board
const char	str_GP_CL2[]	PROGMEM = "GP_CL2";		// 128
const char	str_GP_CO[]		PROGMEM = "GP_CO";		// 129
const char	str_GP_ETO[]	PROGMEM = "GP_ETO";		// 130
const char	str_GP_H2[]		PROGMEM = "GP_H2";		// 131
const char	str_GP_H2S[]	PROGMEM = "GP_H2S";		// 132
const char	str_GP_HCL[]	PROGMEM = "GP_HCL";		// 133
const char	str_GP_HCN[]	PROGMEM = "GP_HCN";		// 134
const char	str_GP_NH3[]	PROGMEM = "GP_NH3";		// 135
const char	str_GP_NO[]		PROGMEM = "GP_NO";		// 136
const char	str_GP_NO2[]	PROGMEM = "GP_NO2";		// 137
const char	str_GP_O2[]		PROGMEM = "GP_O2";		// 138
const char	str_GP_PH3[]	PROGMEM = "GP_PH3";		// 139
const char	str_GP_SO2[]	PROGMEM = "GP_SO2";		// 140
const char	str_GP_CH4[]	PROGMEM = "GP_CH4";		// 141
const char	str_GP_O3[]		PROGMEM = "GP_O3";		// 142
const char	str_GP_CO2[]	PROGMEM = "GP_CO2";		// 143
const char	str_GP_TC[]		PROGMEM = "GP_TC";		// 144
const char	str_GP_TF[]		PROGMEM = "GP_TF";		// 145
const char	str_GP_HUM[]	PROGMEM = "GP_HUM";		// 146
const char	str_GP_PRES[]	PROGMEM = "GP_PRES";	// 147

// OPCN2 Dust Sensor
const char	str_OPC_tc[]	PROGMEM = "OPC_TC";		// 148
const char	str_OPC_tf[]	PROGMEM = "OPC_TF";		// 149
const char	str_OPC_p[]		PROGMEM = "OPC_P";		// 150
const char	str_OPC_pm1[]	PROGMEM = "OPC_PM1";	// 151
const char	str_OPC_pm2_5[]	PROGMEM = "OPC_PM2_5";	// 152
const char	str_OPC_pm10[]	PROGMEM = "OPC_PM10";	// 153
const char	str_OPC_part[]	PROGMEM = "OPC_PART";	// 154

// Smart Water Ions
const char	str_SWI_CA[]	PROGMEM = "SWICA";	// 155
const char	str_SWI_FL[]	PROGMEM = "SWIFL";	// 156
const char	str_SWI_FB[]	PROGMEM = "SWIFB";	// 157
const char	str_SWI_NO[]	PROGMEM = "SWINO";	// 158
const char	str_SWI_BR[]	PROGMEM = "SWIBR";	// 159
const char	str_SWI_CL[]	PROGMEM = "SWICL";	// 160
const char	str_SWI_CU[]	PROGMEM = "SWICU";	// 161
const char	str_SWI_IO[]	PROGMEM = "SWIIO";	// 162
const char	str_SWI_PB[]	PROGMEM = "SWIPB";	// 163
const char	str_SWI_AG[]	PROGMEM = "SWIAG";	// 164
const char	str_SWI_PH[]	PROGMEM = "SWIPH";	// 165

// P&S Smart Water sensors depending on socket (Smart Water)
const char	str_PH_A[]		PROGMEM = "PH_A";	//	166
const char	str_PH_B[]		PROGMEM = "PH_B";	//	167
const char	str_PH_C[]		PROGMEM = "PH_C";	//	168
const char	str_ORP_A[]		PROGMEM = "ORP_A";	//	169
const char	str_ORP_B[]		PROGMEM = "ORP_B";	//	170
const char	str_ORP_C[]		PROGMEM = "ORP_C";	//	171

const char	str_OPCN3_bin[]		PROGMEM = "OPC_N3_BIN";	//	172
const char	str_OPCN2_bin[]		PROGMEM = "OPC_N2_BIN";	//	173

/*******************************************************************************
 * SENSOR_TABLE - Sensor label table
 *
 * This table specifies the tag for each sensor. Every tag has been previously
 * defined in Flash memory
 ******************************************************************************/
const char* const SENSOR_TABLE[] PROGMEM=
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
	str_RB,			// 69

	// Smart Water
	str_PH,			// 70
	str_ORP,		// 71
	str_DO,			// 72
	str_COND,		// 73
	str_WT, 		// 74
	str_DINA,		// 75
	str_DICA,		// 76
	str_DIF,		// 77
	str_DICL,		// 78
	str_DIBR,		// 79
	str_DII,		// 80
	str_DICU2,		// 81
	str_DIK,		// 82
	str_DIMG2,		// 83
	str_DINO3,		// 84

	//Smart Libelium
	str_TX_PWR,		// 85
	str_DM_ST,		// 86
	str_DM_SP,		// 87
	str_LUX,		// 88

	str_SPEED,		// 89
	str_COURSE,		// 90
	str_ALTITUDE,	// 91
	str_HDOP,		// 92
	str_VDOP,		// 93
	str_PDOP,		// 94

	// Finite State Machine
	str_FSM,		// 95

	// New Pluviometer values
	str_PLV1,		// 96
	str_PLV2,		// 97
	str_PLV3,		// 98

	// P&S watermarks
	str_SOIL_C,		// 99
	str_SOIL_D,		// 100
	str_SOIL_E,		// 101
	str_SOIL_F,		// 102

	// Waspmote OEM watermarks
	str_SOIL1,		// 103
	str_SOIL2,		// 104
	str_SOIL3,		// 105

	// DS18B20
	str_TCC, 		// 106

	// P&S ultrasound sensors depending on voltage ref
	str_US_3V3,		// 107
	str_US_5V,		// 108

	// P&S Security sensors depending on socket (Events board)
	str_LUM_D,	// 109
	str_LUM_E,	// 110
	str_LUM_F,	// 111
	str_LP_D,	// 112
	str_LP_E,	// 113
	str_LP_F,	// 114
	str_LL_D,	// 115
	str_LL_E,	// 116
	str_LL_F,	// 117
	str_HALL_D,	// 118
	str_HALL_E,	// 119
	str_HALL_F,	// 120

	// P&S liquid flow sensor depending on socket (Smart Metering)
	str_WF_C,	// 121
	str_WF_E,	// 122

	// Unix/Epoch timestamp
	str_TST,	// 123

	// Turbidity sensor
	str_TURB,	// 124

	// Version parameters
	str_VAPI,	// 125
	str_VPROG,	// 126
	str_VBOOT,	// 127

	// Gases PRO Board
	str_GP_CL2,		// 128
	str_GP_CO,		// 129
	str_GP_ETO,		// 130
	str_GP_H2,		// 131
	str_GP_H2S,		// 132
	str_GP_HCL,		// 133
	str_GP_HCN,		// 134
	str_GP_NH3,		// 135
	str_GP_NO,		// 136
	str_GP_NO2,		// 137
	str_GP_O2,		// 138
	str_GP_PH3,		// 139
	str_GP_SO2,		// 140
	str_GP_CH4,		// 141
	str_GP_O3,		// 142
	str_GP_CO2,		// 143
	str_GP_TC,		// 144
	str_GP_TF,		// 145
	str_GP_HUM,		// 146
	str_GP_PRES,	// 147

	// OPCN2 Dust Sensor
	str_OPC_tc,	// 148
	str_OPC_tf,	// 149
	str_OPC_p,	// 150
	str_OPC_pm1,	// 151
	str_OPC_pm2_5,	// 152
	str_OPC_pm10,	// 153
	str_OPC_part,	// 154

	// Smart Water Ions
	str_SWI_CA,	// 155
	str_SWI_FL,	// 156
	str_SWI_FB,	// 157
	str_SWI_NO,	// 158
	str_SWI_BR,	// 159
	str_SWI_CL,	// 160
	str_SWI_CU,	// 161
	str_SWI_IO,	// 162
	str_SWI_PB,	// 163
	str_SWI_AG,	// 164
	str_SWI_PH,	// 165

	// P&S Smart Water sensors depending on socket (Smart Water)
	str_PH_A,	//	166
	str_PH_B,	//	167
	str_PH_C,	//	168
	str_ORP_A,	//	169
	str_ORP_B,	//	170
	str_ORP_C,	//	171

  str_OPCN3_bin, // 172
  str_OPCN2_bin, // 173

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
const uint8_t SENSOR_TYPE_TABLE[] PROGMEM=
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
	2, // str_LW,		// 38
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
	3,	//str_RB		// 69

	// Smart Water
	2, // str_PH,		// 70
	2, // str_ORP,		// 71
	2, // str_DO,		// 72
	2, // str_COND,		// 73
	2, // str_WT, 		// 74
	2, // str_DINA,		// 75
	2, // str_DICA,		// 76
	2, // str_DIF,		// 77
	2, // str_DICL,		// 78
	2, // str_DIBR,		// 79
	2, // str_DII,		// 80
	2, // str_DICU2,	// 81
	2, // str_DIK,		// 82
	2, // str_DIMG2,	// 83
	2, // str_DINO3,	// 84


	//Smart Libelium
	0,	//str_TX_PWR	// 85
	0,	//str_DM_ST,	// 86
	0,	//str_DM_SP,	// 87
	4,	//str_LUX		// 88

	//GPS
	3,	//str_SPEED		// 89
	3,	//str_COURSE	// 90
	3,	//str_ALTITUDE	// 91
	3,	//str_HDOP		// 92
	3,	//str_VDOP		// 93
	3,	//str_PDOP		// 94

	// States Machine
	0,	//str_FSM		// 95

	// New Pluviometer values
	2, //str_PLV1		// 96
	2, //str_PLV2		// 97
	2, //str_PLV3		// 98

	// P&S watermarks
	2, // str_SOIL_C,	// 99
	2, // str_SOIL_D,	// 100
	2, // str_SOIL_E,	// 101
	2, // str_SOIL_F,	// 102

	// Waspmote OEM watermarks
	2, // str_SOIL1,	// 103
	2, // str_SOIL2,	// 104
	2, // str_SOIL3,	// 105

	// DS18B20
	2, // str_TCC,		// 106

	// P&S ultrasound sensor depending on voltage ref
	2, // str_US_3V3,	// 107
	2, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	2, // str_LUM_D,	// 109
	2, // str_LUM_E,	// 110
	2, // str_LUM_F,	// 111
	0, // str_LP_D,		// 112
	0, // str_LP_E,		// 113
	0, // str_LP_F,		// 114
	0, // str_LL_D,		// 115
	0, // str_LL_E,		// 116
	0, // str_LL_F,		// 117
	0, // str_HALL_D,	// 118
	0, // str_HALL_E,	// 119
	0, // str_HALL_F,	// 120

	// P&S liquid flow sensor depending on socket (Smart Metering)
	2, // str_WF_C,		// 121
	2, // str_WF_E,		// 122

	// Unix/Epoch timestamp
	4, // str_TST,		// 123

	// Turbidity sensor
	2, // str_TURB,		// 124

	// Version parameters
	0, // str_VAPI,		// 125
	0, // str_VPROG,	// 126
	0, // str_VBOOT,	// 127

	// Gases PRO Board
	2,	//str_GP_CL2,		// 128
	2,	//str_GP_CO,		// 129
	2,	//str_GP_ETO,		// 130
	2,	//str_GP_H2,		// 131
	2,	//str_GP_H2S,		// 132
	2,	//str_GP_HCL,		// 133
	2,	//str_GP_HCN,		// 134
	2,	//str_GP_NH3,		// 135
	2,	//str_GP_NO,		// 136
	2,	//str_GP_NO2,		// 137
	2,	//str_GP_O2,		// 138
	2,	//str_GP_PH3,		// 139
	2,	//str_GP_SO2,		// 140
	2,	//str_GP_CH4,		// 141
	2,	//str_GP_O3,		// 142
	2,	//str_GP_CO2,		// 143
	2,	//str_GP_TC			// 144
	2,	//str_GP_TF			// 145
	2,	//str_GP_HUM		// 146
	2,	//str_GP_PRES		// 147

	// OPCN2 Dust Sensor
	2,	//str_OPC_tc	// 148
	2,	//str_OPC_tf	// 149
	2,	//str_OPC_p		// 150
	2,	//str_OPC_pm1	// 151
	2,	//str_OPC_pm2_5	// 152
	2,	//str_OPC_pm10	// 153
	2,	//str_OPC_part	// 154

	// Smart Water Ions
	2,	//str_SWI_CA,	// 155
	2, 	//str_SWI_FL,	// 156
	2,	//str_SWI_FB,	// 157
	2,	//str_SWI_NO,	// 158
	2,	//str_SWI_BR,	// 159
	2,	//str_SWI_CL,	// 160
	2,	//str_SWI_CU,	// 161
	2,	//str_SWI_IO,	// 162
	2,	//str_SWI_PB,	// 163
	2,	//str_SWI_AG,	// 164
	2,	//str_SWI_PH,	// 165

	// P&S Smart Water sensors depending on socket (Smart Water)
	2, // str_PH_A,		// 166
	2, // str_PH_B,		// 167
	2, // str_PH_C,		// 168
	2, // str_ORP_A,	// 169
	2, // str_ORP_B,	// 170
	2, // str_ORP_C,	// 171

  1, //str_OPC_bin //172
  1, //str_OPC_bin //173

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
const uint8_t SENSOR_FIELD_TABLE[] PROGMEM=
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
	1,  //str_RB		// 69

	// Smart Water
	1, //str_PH,		// 70
	1, //str_ORP,		// 71
	1, //str_DO,		// 72
	1, //str_COND,		// 73
	1, //str_WT, 		// 74
	1, //str_DINA,		// 75
	1, //str_DICA,		// 76
	1, //str_DIF,		// 77
	1, //str_DICL,		// 78
	1, //str_DIBR,		// 79
	1, //str_DII,		// 80
	1, //str_DICU2,		// 81
	1, //str_DIK,		// 82
	1, //str_DIMG2,		// 83
	1, //str_DINO3,		// 84

	//Smart Libelium
	1,	//str_TX_PWR	// 85
	3,	//str_DM_ST,	// 86
	3,	//str_DM_SP,	// 87
	1,	//str_LUX		// 88

	//GPS
	1,	//str_SPEED		// 89
	1,	//str_COURSE	// 90
	1,	//str_ALTITUDE	// 91
	1,	//str_HDOP		// 92
	1,	//str_VDOP		// 93
	1,	//str_PDOP		// 94

	// States Machine
	1,	//str_FSM		// 95

	// New Pluviometer values
	1, //str_PLV1		// 96
	1, //str_PLV2		// 97
	1, //str_PLV3		// 98

	// P&S watermarks
	1, // str_SOIL_C,	// 99
	1, // str_SOIL_D,	// 100
	1, // str_SOIL_E,	// 101
	1, // str_SOIL_F,	// 102

	// Waspmote OEM watermarks
	1, // str_SOIL1,	// 103
	1, // str_SOIL2,	// 104
	1, // str_SOIL3,	// 105

	// DS18B20
	1, // str_TCC,		// 106

	// P&S ultrasound sensor depending on voltage ref
	1, // str_US_3V3,	// 107
	1, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	1, // str_LUM_D,	// 109
	1, // str_LUM_E,	// 110
	1, // str_LUM_F,	// 111
	1, // str_LP_D,		// 112
	1, // str_LP_E,		// 113
	1, // str_LP_F,		// 114
	1, // str_LL_D,		// 115
	1, // str_LL_E,		// 116
	1, // str_LL_F,		// 117
	1, // str_HALL_D,	// 118
	1, // str_HALL_E,	// 119
	1, // str_HALL_F,	// 120

	// P&S liquid flow sensor depending on socket (Smart Metering)
	1, // str_WF_C,		// 121
	1, // str_WF_E,		// 122

	// Unix/Epoch timestamp
	1, // str_TST,		// 123

	// Turbidity sensor
	1, // str_TURB,		// 124

	// Version parameters
	1, // str_VAPI,		// 125
	1, // str_VPROG,	// 126
	1, // str_VBOOT,	// 127

	// Gases PRO Board
	1,	//str_GP_CL2,		// 128
	1,	//str_GP_CO,		// 129
	1,	//str_GP_ETO,		// 130
	1,	//str_GP_H2,		// 131
	1,	//str_GP_H2S,		// 132
	1,	//str_GP_HCL,		// 133
	1,	//str_GP_HCN,		// 134
	1,	//str_GP_NH3,		// 135
	1,	//str_GP_NO,		// 136
	1,	//str_GP_NO2,		// 137
	1,	//str_GP_O2,		// 138
	1,	//str_GP_PH3,		// 139
	1,	//str_GP_SO2,		// 140
	1,	//str_GP_CH4,		// 141
	1,	//str_GP_O3,		// 142
	1,	//str_GP_CO2,		// 143
	1,	//str_GP_TC			// 144
	1,	//str_GP_TF			// 145
	1,	//str_GP_HUM		// 146
	1,	//str_GP_PRES		// 147

	// OPC_N2
	1,	//str_OPC_tc		// 148
	1,	//str_OPC_tf		// 149
	1,	//str_OPC_p			// 150
	1,	//str_OPC_pm1		// 151
	1,	//str_OPC_pm2_5		// 152
	1,	//str_OPC_pm10		// 153
	2,	//str_OPC_part		// 154

	// Smart Water Ions
	1,	//str_SWI_CA,	// 155
	1, 	//str_SWI_FL,	// 156
	1,	//str_SWI_FB,	// 157
	1,	//str_SWI_NO,	// 158
	1,	//str_SWI_BR,	// 159
	1,	//str_SWI_CL,	// 160
	1,	//str_SWI_CU,	// 161
	1,	//str_SWI_IO,	// 162
	1,	//str_SWI_PB,	// 163
	1,	//str_SWI_AG,	// 164
	1,	//str_SWI_PH,	// 165

	// P&S Smart Water sensors depending on socket (Smart Water)
	1, // str_PH_A,		// 166
	1, // str_PH_B,		// 167
	1, // str_PH_C,		// 168
	1, // str_ORP_A,	// 169
	1, // str_ORP_B,	// 170
	1, // str_ORP_C,	// 171

  24, //str_OPC_bin, // 172
  16, //str_OPC_bin, // 173
};



/*******************************************************************************
 * DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
 *
 * This table specifies the number of decimals for each sensor for ASCII frames
 ******************************************************************************/
const uint8_t DECIMAL_TABLE[] PROGMEM =
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
	3, // str_LW,		// 38
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
	0, //str_RB			// 69

	// Smart Water
	2, //str_PH,		// 70
	3, //str_ORP,		// 71
	1, //str_DO,		// 72
	1, //str_COND,		// 73
	2, //str_WT, 		// 74
	3, //str_DINA,		// 75
	3, //str_DICA,		// 76
	3, //str_DIF,		// 77
	3, //str_DICL,		// 78
	3, //str_DIBR,		// 79
	3, //str_DII,		// 80
	3, //str_DICU2,		// 81
	3, //str_DIK,		// 82
	3, //str_DIMG2,		// 83
	3, //str_DINO3,		// 84

	//Smart Libelium
	0,	//str_TX_PWR	// 85
	0,	//str_DM_ST,	// 86
	0,	//str_DM_SP,	// 87
	3,	//str_LUX		// 88

	//GPS
	2,	//str_SPEED		// 89
	2,	//str_COURSE	// 90
	2,	//str_ALTITUDE	// 91
	3,	//str_HDOP		// 92
	3,	//str_VDOP		// 93
	3,	//str_PDOP		// 94

	// States Machine
	0,	//str_FSM		// 95

	// New Pluviometer values
	2, //str_PLV1		// 96
	2, //str_PLV2		// 97
	2, //str_PLV3		// 98

	// P&S watermarks
	2, // str_SOIL_C,	// 99
	2, // str_SOIL_D,	// 100
	2, // str_SOIL_E,	// 101
	2, // str_SOIL_F,	// 102

	// Waspmote OEM watermarks
	2, // str_SOIL1,	// 103
	2, // str_SOIL2,	// 104
	2, // str_SOIL3,	// 105

	// DS18B20
	2, // str_TCC,		// 106

	// P&S ultrasound sensor depending on voltage ref
	2, // str_US_3V3,	// 107
	2, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	3, // str_LUM_D,	// 109
	3, // str_LUM_E,	// 110
	3, // str_LUM_F,	// 111
	0, // str_LP_D,		// 112
	0, // str_LP_E,		// 113
	0, // str_LP_F,		// 114
	0, // str_LL_D,		// 115
	0, // str_LL_E,		// 116
	0, // str_LL_F,		// 117
	0, // str_HALL_D,	// 118
	0, // str_HALL_E,	// 119
	0, // str_HALL_F,	// 120

	// P&S liquid flow sensor depending on socket (Smart Metering)
	3, // str_WF_C,		// 121
	3, // str_WF_E,		// 122

	// Unix/Epoch timestamp
	0, // str_TST,		// 123

	// Turbidity sensor
	1, // str_TURB,		// 124

	// Version parameters
	0, // str_VAPI,		// 125
	0, // str_VPROG,	// 126
	0, // str_VBOOT,	// 127

	// Gases PRO Board
	3,	//str_GP_CL2,		// 128
	3,	//str_GP_CO,		// 129
	3,	//str_GP_ETO,		// 130
	3,	//str_GP_H2,		// 131
	3,	//str_GP_H2S,		// 132
	3,	//str_GP_HCL,		// 133
	3,	//str_GP_HCN,		// 134
	3,	//str_GP_NH3,		// 135
	3,	//str_GP_NO,		// 136
	3,	//str_GP_NO2,		// 137
	3,	//str_GP_O2,		// 138
	3,	//str_GP_PH3,		// 139
	3,	//str_GP_SO2,		// 140
	3,	//str_GP_CH4,		// 141
	3,	//str_GP_O3,		// 142
	3,	//str_GP_CO2,		// 143
	3,	//str_GP_TC			// 144
	2,	//str_GP_TF			// 145
	2,	//str_GP_HUM		// 146
	0,	//str_GP_PRES		// 147

	// OPC_N2
	2,	//str_OPC_tc		// 148
	2,	//str_OPC_tf		// 149
	0,	//str_OPC_p			// 150
	4,	//str_OPC_pm1		// 151
	4,	//str_OPC_pm2_5		// 152
	4,	//str_OPC_pm10		// 153
	0,	//str_OPC_part		// 154

	// Smart Water Ions
	3,	//str_SWI_CA,	// 155
	3,	//str_SWI_FL,	// 156
	3,	//str_SWI_FB,	// 157
	3,	//str_SWI_NO,	// 158
	3,	//str_SWI_BR,	// 159
	3,	//str_SWI_CL,	// 160
	3,	//str_SWI_CU,	// 161
	3,	//str_SWI_IO,	// 162
	3,	//str_SWI_PB,	// 163
	3,	//str_SWI_AG,	// 164
	3,	//str_SWI_PH,	// 165

	// P&S Smart Water sensors depending on socket (Smart Water)
	2, // str_PH_A,		// 166
	2, // str_PH_B,		// 167
	2, // str_PH_C,		// 168
	3, // str_ORP_A,	// 169
	3, // str_ORP_B,	// 170
	3, // str_ORP_C,	// 171

  0, //str_OPC_bin  //172
  0, //str_OPC_bin  //173
};

#endif
