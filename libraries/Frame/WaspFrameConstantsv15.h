/*! \file WaspFrameConstantsv15.h
    \brief Header file for Waspmote v15 Frame Constants

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

    Version:		3.3
    Design:			David Gascón
    Implementation:	Yuri Carmona, Javier Siscart, Joaquín Ruiz, Alejandro Gallego

*/


#ifndef WaspFrameconstantsv15_h
#define WaspFrameconstantsv15_h


#include <avr/pgmspace.h>



////////////////////////////////////////////////////////////////////////////////
// Waspmote v15 FRAME definitions
////////////////////////////////////////////////////////////////////////////////


// Gases v30
#define SENSOR_GASES_CO					0
#define SENSOR_GASES_CO2    			1
#define SENSOR_GASES_O2     			2
#define SENSOR_GASES_CH4    			3
#define SENSOR_GASES_O3     			4
#define SENSOR_GASES_NH3    			5
#define SENSOR_GASES_NO2    			6
#define SENSOR_GASES_LPG    			7
#define SENSOR_GASES_AP1    			8
#define SENSOR_GASES_AP2    			9
#define SENSOR_GASES_SV     			10
#define SENSOR_GASES_VOC    			11
#define SENSOR_GASES_TC     			74
#define SENSOR_GASES_TF     			75
#define SENSOR_GASES_HUM    			76
#define SENSOR_GASES_PRES   			77
#define SENSOR_GASES_LUXES  			78
#define SENSOR_GASES_US     			79

// Gases PRO v30
#define SENSOR_GASES_PRO_CO				0
#define SENSOR_GASES_PRO_CO2            1
#define SENSOR_GASES_PRO_O2             2
#define SENSOR_GASES_PRO_CH4            3
#define SENSOR_GASES_PRO_O3             4
#define SENSOR_GASES_PRO_NH3            5
#define SENSOR_GASES_PRO_NO2            6
#define SENSOR_GASES_PRO_NO             12
#define SENSOR_GASES_PRO_CL2            13
#define SENSOR_GASES_PRO_ETO            14
#define SENSOR_GASES_PRO_H2             15
#define SENSOR_GASES_PRO_H2S            16
#define SENSOR_GASES_PRO_HCL            17
#define SENSOR_GASES_PRO_HCN            18
#define SENSOR_GASES_PRO_PH3            19
#define SENSOR_GASES_PRO_SO2            20
#define SENSOR_GASES_PRO_SOCKET_A       30
#define SENSOR_GASES_PRO_SOCKET_B       31
#define SENSOR_GASES_PRO_SOCKET_C       32
#define SENSOR_GASES_PRO_SOCKET_F       35
#define SENSOR_GASES_PRO_PM1            70
#define SENSOR_GASES_PRO_PM2_5          71
#define SENSOR_GASES_PRO_PM10           72
#define SENSOR_GASES_PRO_PART           73
#define SENSOR_GASES_PRO_PM_BIN   		  190
#define SENSOR_GASES_PRO_PM_BINL	     	191
#define SENSOR_GASES_PRO_PM_BINH	     	192
#define SENSOR_GASES_PRO_TC             74
#define SENSOR_GASES_PRO_TF             75
#define SENSOR_GASES_PRO_HUM            76
#define SENSOR_GASES_PRO_PRES           77
#define SENSOR_GASES_PRO_LUXES          78
#define SENSOR_GASES_PRO_US			    79

// Events v30
#define SENSOR_EVENTS_WF				40
#define SENSOR_EVENTS_PIR           	41
#define SENSOR_EVENTS_LP            	42
#define SENSOR_EVENTS_LL            	43
#define SENSOR_EVENTS_HALL          	44
#define SENSOR_EVENTS_RELAY_IN      	45
#define SENSOR_EVENTS_RELAY_OUT     	46
#define SENSOR_EVENTS_SOCKET_A      	47
#define SENSOR_EVENTS_SOCKET_C      	48
#define SENSOR_EVENTS_SOCKET_D      	49
#define SENSOR_EVENTS_SOCKET_E      	50
#define SENSOR_EVENTS_TC            	74
#define SENSOR_EVENTS_TF            	75
#define SENSOR_EVENTS_HUM           	76
#define SENSOR_EVENTS_PRES          	77
#define SENSOR_EVENTS_LUXES         	78
#define SENSOR_EVENTS_US            	79


// Cities PRO v30
#define SENSOR_CITIES_PRO_CO			0
#define SENSOR_CITIES_PRO_CO2			1
#define SENSOR_CITIES_PRO_O2			2
#define SENSOR_CITIES_PRO_CH4			3
#define SENSOR_CITIES_PRO_O3 			4
#define SENSOR_CITIES_PRO_NH3			5
#define SENSOR_CITIES_PRO_NO2			6
#define SENSOR_CITIES_PRO_NO 			12
#define SENSOR_CITIES_PRO_CL2			13
#define SENSOR_CITIES_PRO_ETO			14
#define SENSOR_CITIES_PRO_H2 			15
#define SENSOR_CITIES_PRO_H2S			16
#define SENSOR_CITIES_PRO_HCL			17
#define SENSOR_CITIES_PRO_HCN			18
#define SENSOR_CITIES_PRO_PH3			19
#define SENSOR_CITIES_PRO_SO2			20
#define SENSOR_CITIES_PRO_NOISE			21
#define SENSOR_CITIES_PRO_SOCKET_A		30
#define SENSOR_CITIES_PRO_SOCKET_B		31
#define SENSOR_CITIES_PRO_SOCKET_C		32
#define SENSOR_CITIES_PRO_SOCKET_F		35
#define SENSOR_CITIES_PRO_PM1			70
#define SENSOR_CITIES_PRO_PM2_5			71
#define SENSOR_CITIES_PRO_PM10			72
#define SENSOR_CITIES_PRO_PART			73
#define SENSOR_CITIES_PRO_PM_BIN     190
#define SENSOR_CITIES_PRO_PM_BINL     191
#define SENSOR_CITIES_PRO_PM_BINH     192
#define SENSOR_CITIES_PRO_TC			74
#define SENSOR_CITIES_PRO_TF			75
#define SENSOR_CITIES_PRO_HUM			76
#define SENSOR_CITIES_PRO_PRES			77
#define SENSOR_CITIES_PRO_LUXES			78
#define SENSOR_CITIES_PRO_US			79


// Smart Water Ions v30
#define SENSOR_IONS_CA					100
#define SENSOR_IONS_FL					101
#define SENSOR_IONS_FB					102
#define SENSOR_IONS_NO3					103
#define SENSOR_IONS_BR					104
#define SENSOR_IONS_CL					105
#define SENSOR_IONS_CU					106
#define SENSOR_IONS_IO					107
#define SENSOR_IONS_NH4					108
#define SENSOR_IONS_AG					109
#define SENSOR_IONS_PH					110
#define SENSOR_IONS_LI					111
#define SENSOR_IONS_MG					112
#define SENSOR_IONS_NO2					113
#define SENSOR_IONS_CLO4				114
#define SENSOR_IONS_K					115
#define SENSOR_IONS_NA					116
#define SENSOR_IONS_SOCKET_A			117
#define SENSOR_IONS_SOCKET_B			118
#define SENSOR_IONS_SOCKET_C			119
#define SENSOR_IONS_SOCKET_D			120
#define SENSOR_IONS_WT					134

// Parking
#define SENSOR_PARKING					128

// Radiation
#define SENSOR_RADIATION				129


// Smart Water v30
#define SENSOR_WATER_PH					130
#define SENSOR_WATER_ORP				131
#define SENSOR_WATER_DO					132
#define SENSOR_WATER_COND				133
#define SENSOR_WATER_WT					134
#define SENSOR_WATER_TURB				135
#define SENSOR_WATER_PH_A				136
#define SENSOR_WATER_PH_E				137
#define SENSOR_WATER_ORP_A				138
#define SENSOR_WATER_ORP_E				139


// Smart Agriculture v30
#define SENSOR_AGR_SOIL1				150
#define SENSOR_AGR_SOIL2				151
#define SENSOR_AGR_SOIL3				152
#define SENSOR_AGR_SOILTC				153
#define SENSOR_AGR_SOILTF				154
#define SENSOR_AGR_LW					155
#define SENSOR_AGR_ANE					156
#define SENSOR_AGR_WV					157
#define SENSOR_AGR_PLV1					158
#define SENSOR_AGR_PLV2					159
#define SENSOR_AGR_PLV3					160
#define SENSOR_AGR_PAR					161
#define SENSOR_AGR_UV					162
#define SENSOR_AGR_TD					163
#define SENSOR_AGR_SD					164
#define SENSOR_AGR_FD					165
#define SENSOR_AGR_SOIL_B				166
#define SENSOR_AGR_SOIL_C				167
#define SENSOR_AGR_SOIL_E				168
#define SENSOR_AGR_TC					74
#define SENSOR_AGR_TF					75
#define SENSOR_AGR_HUM					76
#define SENSOR_AGR_PRES					77
#define SENSOR_AGR_LUXES				78
#define SENSOR_AGR_US					79


// Ambient Control v30
#define SENSOR_AMBIENT_TCB				170
#define SENSOR_AMBIENT_HUMB				171
#define SENSOR_AMBIENT_LUM				172
#define SENSOR_AMBIENT_TC				74
#define SENSOR_AMBIENT_TF				75
#define SENSOR_AMBIENT_HUM				76
#define SENSOR_AMBIENT_PRES				77
#define SENSOR_AMBIENT_LUXES			78

// 4-20 mA
#define SENSOR_4_20_CURRENT_SOCKET_A	175
#define SENSOR_4_20_CURRENT_SOCKET_B	176
#define SENSOR_4_20_CURRENT_SOCKET_C	177
#define SENSOR_4_20_CURRENT_SOCKET_D	178

// Industrial protocols (ModBus & CAN bus)
#define SENSOR_MODBUS_COILS				180
#define SENSOR_MODBUS_DISCRETE_INPUT	181
#define SENSOR_MODBUS_HOLDING_REGS		182
#define SENSOR_MODBUS_INPUT_REGS		183
#define SENSOR_CANBUS_RPM				184
#define SENSOR_CANBUS_VS				185
#define SENSOR_CANBUS_FR				186
#define SENSOR_CANBUS_FL				187
#define SENSOR_CANBUS_TP				188
#define SENSOR_CANBUS_FP				189


// Common sensors
#define SENSOR_DUST_PM1					70
#define SENSOR_DUST_PM2_5				71
#define SENSOR_DUST_PM10				72
#define SENSOR_DUST_PART				73
#define SENSOR_BME_TC					74
#define SENSOR_BME_TF					75
#define SENSOR_BME_HUM					76
#define SENSOR_BME_PRES					77
#define SENSOR_LUXES					78
#define SENSOR_ULTRASOUND				79
#define SENSOR_PM_BIN    190
#define SENSOR_PM_BINL    191
#define SENSOR_PM_BINH    192


// fever kit
#define FEVER_USER_TEMP    				193
#define FEVER_AIR_TEMP    				194
#define FEVER_SI4B1_TEMP    			195
#define FEVER_MEASUREMENTS_COUNTER    	196
#define FEVER_POSITIVE_FEVER_COUNTER    197
#define FEVER_THRESHOLD    				198
#define FEVER_RESULT    				199


/// Flash defines //////////////////////////////////////////////////////////////


/*******************************************************************************
 * The following Flash strings, define the tags for all Waspmote sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 *
 ******************************************************************************/

// Gases v30
const char	str_frame_00[] 	PROGMEM	= "CO";
const char 	str_frame_01[] 	PROGMEM	= "CO2";
const char 	str_frame_02[] 	PROGMEM	= "O2";
const char 	str_frame_03[] 	PROGMEM	= "CH4";
const char 	str_frame_04[] 	PROGMEM	= "O3";
const char 	str_frame_05[] 	PROGMEM	= "NH3";
const char 	str_frame_06[] 	PROGMEM	= "NO2";
const char 	str_frame_07[] 	PROGMEM	= "LPG";
const char 	str_frame_08[] 	PROGMEM	= "AP1";
const char 	str_frame_09[] 	PROGMEM	= "AP2";
const char 	str_frame_10[] 	PROGMEM	= "SV";
const char 	str_frame_11[] 	PROGMEM	= "VOC";


// Gases PRO v30
const char 	str_frame_12[] 	PROGMEM	= "NO";
const char 	str_frame_13[] 	PROGMEM	= "CL2";
const char 	str_frame_14[] 	PROGMEM	= "ETO";
const char 	str_frame_15[] 	PROGMEM	= "H2";
const char 	str_frame_16[] 	PROGMEM	= "H2S";
const char 	str_frame_17[] 	PROGMEM	= "HCL";
const char 	str_frame_18[] 	PROGMEM	= "HCN";
const char 	str_frame_19[] 	PROGMEM	= "PH3";
const char 	str_frame_20[] 	PROGMEM	= "SO2";


// Cities PRO v30
const char 	str_frame_21[] 	PROGMEM	= "NOISE";


// Reserved
const char 	str_frame_22[] 	PROGMEM	= "";
const char 	str_frame_23[] 	PROGMEM	= "";
const char 	str_frame_24[] 	PROGMEM	= "";
const char 	str_frame_25[] 	PROGMEM	= "";
const char 	str_frame_26[] 	PROGMEM	= "";
const char 	str_frame_27[] 	PROGMEM	= "";
const char 	str_frame_28[] 	PROGMEM	= "";
const char 	str_frame_29[] 	PROGMEM	= "";

// Gases PRO v30 (P&S)
const char 	str_frame_30[] 	PROGMEM	= "GP_A";
const char 	str_frame_31[] 	PROGMEM	= "GP_B";
const char 	str_frame_32[] 	PROGMEM	= "GP_C";
const char 	str_frame_33[] 	PROGMEM	= "";		//reserved
const char 	str_frame_34[] 	PROGMEM	= "";		//reserved
const char 	str_frame_35[] 	PROGMEM	= "GP_F";
const char 	str_frame_36[] 	PROGMEM	= "";		//reserved
const char 	str_frame_37[] 	PROGMEM	= "";		//reserved
const char 	str_frame_38[] 	PROGMEM	= "";		//reserved
const char 	str_frame_39[] 	PROGMEM	= "";		//reserved


// Events v30
const char 	str_frame_40[] 	PROGMEM	= "WF";
const char 	str_frame_41[] 	PROGMEM	= "PIR";
const char 	str_frame_42[] 	PROGMEM	= "LP";
const char 	str_frame_43[] 	PROGMEM	= "LL";
const char 	str_frame_44[] 	PROGMEM	= "HALL";
const char 	str_frame_45[] 	PROGMEM	= "RIN";
const char 	str_frame_46[] 	PROGMEM	= "ROUT";
const char 	str_frame_47[] 	PROGMEM	= "EV_A";
const char 	str_frame_48[] 	PROGMEM	= "EV_C";
const char 	str_frame_49[] 	PROGMEM	= "EV_D";
const char 	str_frame_50[] 	PROGMEM	= "EV_E";
const char 	str_frame_51[] 	PROGMEM	= "";		// reserved


// Additional
const char	str_frame_52[] 	PROGMEM	= "BAT";
const char	str_frame_53[] 	PROGMEM	= "GPS";
const char	str_frame_54[] 	PROGMEM	= "RSSI";
const char	str_frame_55[] 	PROGMEM	= "MAC";
const char	str_frame_56[] 	PROGMEM	= "NA";
const char	str_frame_57[] 	PROGMEM	= "NID";
const char	str_frame_58[] 	PROGMEM	= "DATE";
const char	str_frame_59[] 	PROGMEM	= "TIME";
const char	str_frame_60[] 	PROGMEM	= "GMT";
const char	str_frame_61[] 	PROGMEM	= "RAM";
const char	str_frame_62[] 	PROGMEM	= "IN_TEMP"; // (deprecated for Waspv15)
const char	str_frame_63[]	PROGMEM = "ACC";
const char	str_frame_64[]  PROGMEM = "MILLIS";
const char	str_frame_65[]  PROGMEM = "STR";
const char	str_frame_66[]  PROGMEM = ""; 		// reserved
const char	str_frame_67[]  PROGMEM = ""; 		// reserved
const char	str_frame_68[]  PROGMEM = "UID";
const char	str_frame_69[]  PROGMEM = "RB";
const char	str_frame_70[]  PROGMEM = "PM1";
const char	str_frame_71[]  PROGMEM = "PM2_5";
const char	str_frame_72[]  PROGMEM = "PM10";
const char	str_frame_73[]  PROGMEM = "PART";
const char	str_frame_74[]  PROGMEM = "TC";
const char	str_frame_75[]  PROGMEM = "TF";
const char	str_frame_76[]  PROGMEM = "HUM";
const char	str_frame_77[]  PROGMEM = "PRES";
const char	str_frame_78[]  PROGMEM = "LUX";
const char	str_frame_79[]  PROGMEM = "US";
const char	str_frame_80[]  PROGMEM = ""; 		// reserved
const char	str_frame_81[]  PROGMEM = "";       // reserved
const char	str_frame_82[]  PROGMEM = "";       // reserved
const char	str_frame_83[]  PROGMEM = "";       // reserved
const char	str_frame_84[]  PROGMEM = "";       // reserved
const char	str_frame_85[]  PROGMEM = "";       // reserved
const char	str_frame_86[]  PROGMEM = "";       // reserved
const char	str_frame_87[]  PROGMEM = "";       // reserved
const char	str_frame_88[]  PROGMEM = "";       // reserved
const char	str_frame_89[]  PROGMEM = "SPEED_OG";
const char	str_frame_90[]  PROGMEM = "COURSE_OG";
const char	str_frame_91[]  PROGMEM = "ALT";
const char	str_frame_92[]  PROGMEM = "HDOP";
const char	str_frame_93[]  PROGMEM = "VDOP";
const char	str_frame_94[]  PROGMEM = "PDOP";
const char	str_frame_95[]  PROGMEM = "";      	// reserved
const char	str_frame_96[]  PROGMEM = "";      	// reserved
const char	str_frame_97[]  PROGMEM = "";      	// reserved
const char	str_frame_98[]  PROGMEM = "";      	// reserved
const char	str_frame_99[]  PROGMEM = "";      	// reserved


// Smart Water Ions v30
const char	str_frame_100[]  PROGMEM = "SWICA";
const char	str_frame_101[]  PROGMEM = "SWIFL";
const char	str_frame_102[]  PROGMEM = "SWIFB";
const char	str_frame_103[]  PROGMEM = "SWINO3";
const char	str_frame_104[]  PROGMEM = "SWIBR";
const char	str_frame_105[]  PROGMEM = "SWICL";
const char	str_frame_106[]  PROGMEM = "SWICU";
const char	str_frame_107[]  PROGMEM = "SWIIO";
const char	str_frame_108[]  PROGMEM = "SWINH4";
const char	str_frame_109[]  PROGMEM = "SWIAG";
const char	str_frame_110[]  PROGMEM = "SWIPH";
const char	str_frame_111[]  PROGMEM = "SWILI";
const char	str_frame_112[]  PROGMEM = "SWIMG";
const char	str_frame_113[]  PROGMEM = "SWINO2";
const char	str_frame_114[]  PROGMEM = "SWICLO4";
const char	str_frame_115[]  PROGMEM = "SWIK";
const char	str_frame_116[]  PROGMEM = "SWINA";
const char	str_frame_117[]  PROGMEM = "SWI_A";
const char	str_frame_118[]  PROGMEM = "SWI_B";
const char	str_frame_119[]  PROGMEM = "SWI_C";
const char	str_frame_120[]  PROGMEM = "SWI_D";
const char	str_frame_121[]  PROGMEM = "";      	// reserved
const char	str_frame_122[]  PROGMEM = "";      	// reserved


// Additional
const char	str_frame_123[]  PROGMEM = "TST";
const char	str_frame_124[]  PROGMEM = "";     		// reserved
const char	str_frame_125[]  PROGMEM = "VAPI";
const char	str_frame_126[]  PROGMEM = "VPROG";
const char	str_frame_127[]  PROGMEM = "VBOOT";
const char	str_frame_128[]  PROGMEM = "PS";

// Radiation
const char	str_frame_129[]  PROGMEM = "RAD";


// Smart Water v30
const char	str_frame_130[]  PROGMEM = "PH";
const char	str_frame_131[]  PROGMEM = "ORP";
const char	str_frame_132[]  PROGMEM = "DO";
const char	str_frame_133[]  PROGMEM = "COND";
const char	str_frame_134[]  PROGMEM = "WT";
const char	str_frame_135[]  PROGMEM = "TURB";
const char	str_frame_136[]  PROGMEM = "PH_A";
const char	str_frame_137[]  PROGMEM = "PH_E";
const char	str_frame_138[]  PROGMEM = "ORP_A";
const char	str_frame_139[]  PROGMEM = "ORP_E";
const char	str_frame_140[]  PROGMEM = "";      		// reserved
const char	str_frame_141[]  PROGMEM = "";      		// reserved
const char	str_frame_142[]  PROGMEM = "";      		// reserved
const char	str_frame_143[]  PROGMEM = "";      		// reserved
const char	str_frame_144[]  PROGMEM = "";      		// reserved
const char	str_frame_145[]  PROGMEM = "";      		// reserved
const char	str_frame_146[]  PROGMEM = "";      		// reserved
const char	str_frame_147[]  PROGMEM = "";      		// reserved
const char	str_frame_148[]  PROGMEM = "";      		// reserved
const char	str_frame_149[]  PROGMEM = "";      		// reserved


//  Smart Agriculture v30
const char	str_frame_150[]  PROGMEM = "SOIL1";
const char	str_frame_151[]  PROGMEM = "SOIL2";
const char	str_frame_152[]  PROGMEM = "SOIL3";
const char	str_frame_153[]  PROGMEM = "SOILTC";
const char	str_frame_154[]  PROGMEM = "SOILTF";
const char	str_frame_155[]  PROGMEM = "LW";
const char	str_frame_156[]  PROGMEM = "ANE";
const char	str_frame_157[]  PROGMEM = "WV";
const char	str_frame_158[]  PROGMEM = "PLV1";
const char	str_frame_159[]  PROGMEM = "PLV2";
const char	str_frame_160[]  PROGMEM = "PLV3";
const char	str_frame_161[]  PROGMEM = "PAR";
const char	str_frame_162[]  PROGMEM = "UV";
const char	str_frame_163[]  PROGMEM = "TD";
const char	str_frame_164[]  PROGMEM = "SD";
const char	str_frame_165[]  PROGMEM = "FD";
const char	str_frame_166[]  PROGMEM = "SOIL_B";
const char	str_frame_167[]  PROGMEM = "SOIL_C";
const char	str_frame_168[]  PROGMEM = "SOIL_E";
const char	str_frame_169[]  PROGMEM = "";    			// reserved

// Ambient Control
const char	str_frame_170[]  PROGMEM = "TCB";
const char	str_frame_171[]  PROGMEM = "HUMB";
const char	str_frame_172[]  PROGMEM = "LUM";
const char	str_frame_173[]  PROGMEM = "";
const char	str_frame_174[]  PROGMEM = "";

// 4-20 mA
const char	str_frame_175[]  PROGMEM = "CUR_A";
const char	str_frame_176[]  PROGMEM = "CUR_B";
const char	str_frame_177[]  PROGMEM = "CUR_C";
const char	str_frame_178[]  PROGMEM = "CUR_D";
const char	str_frame_179[]  PROGMEM = "";

// Industrial protocols: Modbus & CAN bus
const char	str_frame_180[]  PROGMEM = "MB_COILS";
const char	str_frame_181[]  PROGMEM = "MB_DI";
const char	str_frame_182[]  PROGMEM = "MB_HR";
const char	str_frame_183[]  PROGMEM = "MB_IR";
const char	str_frame_184[]  PROGMEM = "CB_RPM";
const char	str_frame_185[]  PROGMEM = "CB_VS";
const char	str_frame_186[]  PROGMEM = "CB_FR";
const char	str_frame_187[]  PROGMEM = "CB_FL";
const char	str_frame_188[]  PROGMEM = "CB_TP";
const char	str_frame_189[]  PROGMEM = "CB_FP";

// OPC N3 sensor
const char	str_frame_190[]  PROGMEM = "PM_BIN";
const char	str_frame_191[]  PROGMEM = "PM_BINL";
const char	str_frame_192[]  PROGMEM = "PM_BINH";

// fever kit
const char	str_frame_193[]  PROGMEM = "USER_TC";
const char	str_frame_194[]  PROGMEM = "AIR_TC";
const char	str_frame_195[]  PROGMEM = "SI4B1_TC";
const char	str_frame_196[]  PROGMEM = "COUNTER";
const char	str_frame_197[]  PROGMEM = "FEVER_COUNTER";
const char	str_frame_198[]  PROGMEM = "THRESHOLD";
const char	str_frame_199[]  PROGMEM = "RESULT";



/*******************************************************************************
 * SENSOR_TABLE - Sensor label table
 *
 * This table specifies the tag for each sensor. Every tag has been previously
 * defined in Flash memory
 ******************************************************************************/
const char* const FRAME_SENSOR_TABLE[] PROGMEM=
{
	// Gases v30
	str_frame_00,
 	str_frame_01,
 	str_frame_02,
 	str_frame_03,
 	str_frame_04,
 	str_frame_05,
 	str_frame_06,
 	str_frame_07,
 	str_frame_08,
 	str_frame_09,
 	str_frame_10,
 	str_frame_11,
 	str_frame_12,
 	str_frame_13,
 	str_frame_14,
 	str_frame_15,
 	str_frame_16,
 	str_frame_17,
 	str_frame_18,
	str_frame_19,
	str_frame_20,
	str_frame_21,
	str_frame_22,
	str_frame_23,
	str_frame_24,
	str_frame_25,
	str_frame_26,
	str_frame_27,
	str_frame_28,
	str_frame_29,
	str_frame_30,
	str_frame_31,
	str_frame_32,
	str_frame_33,
	str_frame_34,
	str_frame_35,
	str_frame_36,
	str_frame_37,
	str_frame_38,
	str_frame_39,
	str_frame_40,
	str_frame_41,
	str_frame_42,
	str_frame_43,
	str_frame_44,
	str_frame_45,
	str_frame_46,
	str_frame_47,
	str_frame_48,
	str_frame_49,
	str_frame_50,
	str_frame_51,
	str_frame_52,
	str_frame_53,
	str_frame_54,
	str_frame_55,
	str_frame_56,
	str_frame_57,
	str_frame_58,
	str_frame_59,
	str_frame_60,
	str_frame_61,
	str_frame_62,
	str_frame_63,
	str_frame_64,
	str_frame_65,
	str_frame_66,
	str_frame_67,
	str_frame_68,
	str_frame_69,
	str_frame_70,
	str_frame_71,
	str_frame_72,
	str_frame_73,
	str_frame_74,
	str_frame_75,
	str_frame_76,
	str_frame_77,
	str_frame_78,
	str_frame_79,
	str_frame_80,
	str_frame_81,
	str_frame_82,
	str_frame_83,
	str_frame_84,
	str_frame_85,
	str_frame_86,
	str_frame_87,
	str_frame_88,
	str_frame_89,
	str_frame_90,
	str_frame_91,
	str_frame_92,
	str_frame_93,
	str_frame_94,
	str_frame_95,
	str_frame_96,
	str_frame_97,
	str_frame_98,
	str_frame_99,
	str_frame_100,
	str_frame_101,
	str_frame_102,
	str_frame_103,
	str_frame_104,
	str_frame_105,
	str_frame_106,
	str_frame_107,
	str_frame_108,
	str_frame_109,
	str_frame_110,
	str_frame_111,
	str_frame_112,
	str_frame_113,
	str_frame_114,
	str_frame_115,
	str_frame_116,
	str_frame_117,
	str_frame_118,
	str_frame_119,
	str_frame_120,
	str_frame_121,
	str_frame_122,
	str_frame_123,
	str_frame_124,
	str_frame_125,
	str_frame_126,
	str_frame_127,
	str_frame_128,
	str_frame_129,
	str_frame_130,
	str_frame_131,
	str_frame_132,
	str_frame_133,
	str_frame_134,
	str_frame_135,
	str_frame_136,
	str_frame_137,
	str_frame_138,
	str_frame_139,
	str_frame_140,
	str_frame_141,
	str_frame_142,
	str_frame_143,
	str_frame_144,
	str_frame_145,
	str_frame_146,
	str_frame_147,
	str_frame_148,
	str_frame_149,
	str_frame_150,
	str_frame_151,
	str_frame_152,
	str_frame_153,
	str_frame_154,
	str_frame_155,
	str_frame_156,
	str_frame_157,
	str_frame_158,
	str_frame_159,
	str_frame_160,
	str_frame_161,
	str_frame_162,
	str_frame_163,
	str_frame_164,
	str_frame_165,
	str_frame_166,
	str_frame_167,
	str_frame_168,
	str_frame_169,
	str_frame_170,
	str_frame_171,
	str_frame_172,
	str_frame_173,
	str_frame_174,
	str_frame_175,
	str_frame_176,
	str_frame_177,
	str_frame_178,
	str_frame_179,
	str_frame_180,
	str_frame_181,
	str_frame_182,
	str_frame_183,
	str_frame_184,
	str_frame_185,
	str_frame_186,
	str_frame_187,
	str_frame_188,
	str_frame_189,
  	str_frame_190,
	str_frame_191,
	str_frame_192,
	str_frame_193,
	str_frame_194,
	str_frame_195,
	str_frame_196,
	str_frame_197,
	str_frame_198,
	str_frame_199,

};


/*******************************************************************************
* SENSOR_TYPE_TABLE - Binary frames sensor types
*
* This table specifies the type of sensor depending on the type of value the
* user must put as input. These are the possibilities:
*
*	0: uint8_t
*	1: int (the same as int16_t)
*	2: double
*	3: char*
*  	4: uint32_t
*  	5: uint8_t*
******************************************************************************/
const uint8_t FRAME_SENSOR_TYPE_TABLE[] PROGMEM=
{
	// Gases v30
	2,		// 0
	2, 		// 1
	2, 		// 2
	2, 		// 3
	2, 		// 4
	2, 		// 5
	2, 		// 6
	2, 		// 7
	2, 		// 8
	2, 		// 9
	2, 		// 10
	2, 		// 11


	//// Gases PRO v30
	2, 		// 12
	2, 		// 13
	2, 		// 14
	2, 		// 15
	2, 		// 16
	2, 		// 17
	2, 		// 18
	2, 		// 19
	2, 		// 20

	//// Cities PRO v30
	2, 		// 21

	//// reserved
	0,		// 22
	0,		// 23
	0,		// 24
	0,		// 25
	0,		// 26
	0,		// 27
	0,		// 28
	0,		// 29

	//// Gases PRO v30
	2,		// 30
	2,		// 31
	2,		// 32
	2,		// 33
	2,		// 34
	2,		// 35

	//// reserved
	0,		// 36
	0,		// 37
	0,		// 38
	0,		// 39

	//// Events v30
	2,		// 40
	0,		// 41
	0,		// 42
	0,		// 43
	0,		// 44
	0,		// 45
	0,		// 46
	0,		// 47
	0,		// 48
	0,		// 49
	0,		// 50
	0,		// 51

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
	3, // str_STR		// 65
	3, // str_MBT		// 66
	3, // str_MWIFI		// 67
	3, // str_UID		// 68
	3, // str_RB		// 69
	2,		// 70
	2,		// 71
	2,		// 72
	4,		// 73
	2,		// 74
	2,		// 75
	2,		// 76
	2,		// 77
	4,		// 78
	1,		// 79
	0,		// 80
	0,		// 81
	0,		// 82
	0,		// 83
	0,		// 84
	0,		// 85
	0,		// 86
	0,		// 87
	0,		// 88
	2,		// 89
	2,		// 90
	2,		// 91
	2,		// 92
	2,		// 93
	2,		// 94
	0,		// 95
	0,		// 96
	0,		// 97
	0,		// 98
	0,		// 99

	//// Smart Water Ions
	2,		// 100
	2,		// 101
	2,		// 102
	2,		// 103
	2,		// 104
	2,		// 105
	2,		// 106
	2,		// 107
	2,		// 108
	2,		// 109
	2,		// 110
	2,		// 111
	2,		// 112
	2,		// 113
	2,		// 114
	2,		// 115
	2,		// 116
	2,		// 117
	2,		// 118
	2,		// 119
	2,		// 120
	0,		// 121
	0,		// 122

	//// Additional
	4,		// 123
	0,		// 124
	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128

	//// Radiation
	2,		// 129

	//// Smart Water
	2,		// 130
	2,		// 131
	2,		// 132
	2,		// 133
	2,		// 134
	2,		// 135
	2,		// 136
	2,		// 137
	2,		// 138
	2,		// 139
	0,		// 140
	0,		// 141
	0,		// 142
	0,		// 143
	0,		// 144
	0,		// 145
	0,		// 146
	0,		// 147
	0,		// 148
	0,		// 149

	//// Smart Agriculture
	2,		// 150
	2,		// 151
	2,		// 152
	2,		// 153
	2,		// 154
	2,		// 155
	2,		// 156
	0,		// 157
	2,		// 158
	2,		// 159
	2,		// 160
	2,		// 161
	2,		// 162
	2,		// 163
	2,		// 164
	2,		// 165
	2,		// 166
	2,		// 167
	2,		// 168
	0,		// 169

	//// Ambient Control
	2,		// 170
	2,		// 171
	2,		// 172
	0,		// 173
	0,		// 174

	//// 4-20 mA
	2,		// 175
	2,		// 176
	2,		// 177
	2,		// 178
	0,		// 179

	//// Industrial protocols (ModBus & CAN bus)
	1,		// 180
	1,		// 181
	1,		// 182
	1,		// 183
	1,		// 184
	1,		// 185
	1,		// 186
	0,		// 187
	0,		// 188
	1,		// 189

  	// OPC sensor
  	1,    // 190
	1,    // 191
	1,    // 192

	// fever
	2,	// 193
	2,	// 194
	2,	// 195
	4,	// 196
	4,	// 197
	2,	// 198
	0,	// 199

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
const uint8_t FRAME_SENSOR_FIELD_TABLE[] PROGMEM=
{
	//// Gases v30
	1, 		// 0
	1, 		// 1
	1, 		// 2
	1, 		// 3
	1, 		// 4
	1, 		// 5
	1, 		// 6
	1, 		// 7
	1, 		// 8
	1, 		// 9
	1, 		// 10
	1, 		// 11

	//// Gases PRO v30
	1, 		// 12
	1, 		// 13
	1, 		// 14
	1, 		// 15
	1, 		// 16
	1, 		// 17
	1, 		// 18
	1, 		// 19
	1, 		// 20

	//// Cities PRO v30
	1, 		// 21

	//// reserved
	1,		// 22
	1,		// 23
	1,		// 24
	1,		// 25
	1,		// 26
	1,		// 27
	1,		// 28
	1,		// 29

	//// Gases PRO v30
	1,		// 30
	1,		// 31
	1,		// 32
	1,		// 33
	1,		// 34
	1,		// 35

	//// reserved
	1,		// 36
	1,		// 37
	1,		// 38
	1,		// 39

	//// Events v30
	1,		// 40
	1,		// 41
	1,		// 42
	1,		// 43
	1,		// 44
	1,		// 45
	1,		// 46
	1,		// 47
	1,		// 48
	1,		// 49
	1,		// 50
	1,		// 51

	//// Additional
	1,		// 52
	2,		// 53
	1,		// 54
	1,		// 55
	1,		// 56
	1,		// 57
	3,		// 58
	3,		// 59
	1,		// 60
	1,		// 61
	1,		// 62
	3,		// 63
	1,		// 64
	1,		// 65
	1,		// 66
	1,		// 67
	1,		// 68
	1,		// 69
	1,		// 70
	1,		// 71
	1,		// 72
	2,		// 73
	1,		// 74
	1,		// 75
	1,		// 76
	1,		// 77
	1,		// 78
	1,		// 79
	1,		// 80
	1,		// 81
	1,		// 82
	1,		// 83
	1,		// 84
	1,		// 85
	1,		// 86
	1,		// 87
	1,		// 88
	1,		// 89
	1,		// 90
	1,		// 91
	1,		// 92
	1,		// 93
	1,		// 94
	1,		// 95
	1,		// 96
	1,		// 97
	1,		// 98
	1,		// 99

	//// Smart Water Ions
	1,		// 100
	1,		// 101
	1,		// 102
	1,		// 103
	1,		// 104
	1,		// 105
	1,		// 106
	1,		// 107
	1,		// 108
	1,		// 109
	1,		// 110
	1,		// 111
	1,		// 112
	1,		// 113
	1,		// 114
	1,		// 115
	1,		// 116
	1,		// 117
	1,		// 118
	1,		// 119
	1,		// 120
	1,		// 121
	1,		// 122

	//// Additional
	1,		// 123
	1,		// 124
	1,		// 125
	1,		// 126
	1,		// 127
	1,		// 128

	//// Radiation
	1,		// 129

	//// Smart Water
	1,		// 130
	1,		// 131
	1,		// 132
	1,		// 133
	1,		// 134
	1,		// 135
	1,		// 136
	1,		// 137
	1,		// 138
	1,		// 139
	1,		// 140
	1,		// 141
	1,		// 142
	1,		// 143
	1,		// 144
	1,		// 145
	1,		// 146
	1,		// 147
	1,		// 148
	1,		// 149

	//// Smart Agriculture
	1,		// 150
	1,		// 151
	1,		// 152
	1,		// 153
	1,		// 154
	1,		// 155
	1,		// 156
	1,		// 157
	1,		// 158
	1,		// 159
	1,		// 160
	1,		// 161
	1,		// 162
	1,		// 163
	1,		// 164
	1,		// 165
	1,		// 166
	1,		// 167
	1,		// 168
	1,		// 169

	//// Ambient Control
	1,		// 170
	1,		// 171
	1,		// 172
	1,		// 173
	1,		// 174

	//// 4-20 mA
	1,		// 175
	1,		// 176
	1,		// 177
	1,		// 178
	1,		// 179

	//// Industrial protocols (ModBus & CAN bus)
	2,		// 180
	2,		// 181
	3,		// 182
	3,		// 183
	1,		// 184
	1,		// 185
	1,		// 186
	1,		// 187
	1,		// 188
	1,		// 189

	// OPC sensor
	24,    // 190
	16,    // 191
	8,     // 192

	// fever
	1,	// 193
	1,	// 194
	1,	// 195
	1,	// 196
	1,	// 197
	1,	// 198
	1,	// 199
};



/*******************************************************************************
* DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
*
* This table specifies the number of decimals for each sensor for ASCII frames
******************************************************************************/
const uint8_t FRAME_DECIMAL_TABLE[] PROGMEM =
{
	// Gases
	3, 		// 0
	3, 		// 1
	3, 		// 2
	3, 		// 3
	3, 		// 4
	3, 		// 5
	3, 		// 6
	3, 		// 7
	3, 		// 8
	3, 		// 9
	3, 		// 10
	3, 		// 11

	//// Gases PRO v30
	3, 		// 12
	3, 		// 13
	3, 		// 14
	3, 		// 15
	3, 		// 16
	3, 		// 17
	3, 		// 18
	3, 		// 19
	3, 		// 20

	//// Cities PRO v30
	2, 		// 21

	//// reserved
	0,	// 22
	0,	// 23
	0,	// 24
	0,	// 25
	0,	// 26
	0,	// 27
	0,	// 28
	0,	// 29

	//// Gases PRO v30
	3,		// 30
	3,		// 31
	3,		// 32
	3,		// 33
	3,		// 34
	3,		// 35

	//// reserved
	0,	// 36
	0,	// 37
	0,	// 38
	0,	// 39

	//// Events v30
	3,		// 40
	0,		// 41
	0,		// 42
	0,		// 43
	0,		// 44
	0,		// 45
	0,		// 46
	0,		// 47
	0,		// 48
	0,		// 49
	0,		// 50
	0,		// 51

	//// Additional
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
	0, // str_STR		// 65
	0, 				// 66
	0, 				// 67
	0, //str_UID		// 68
	0, //str_RB			// 69
	4,		// 70
	4,		// 71
	4,		// 72
	0,		// 73
	2,		// 74
	2,		// 75
	1,		// 76
	2,		// 77
	0,		// 78
	0,		// 79
	0,	// 80
	0,	// 81
	0,	// 82
	0,	// 83
	0,	// 84
	0,	// 85
	0,	// 86
	0,	// 87
	0,	// 88
	2,		// 89
	2,		// 90
	2,		// 91
	3,		// 92
	3,		// 93
	3,		// 94
	0,		// 95
	0,		// 96
	0,		// 97
	0,		// 98
	0,		// 99

	//// Smart Water Ions
	3,		// 100
	3,		// 101
	3,		// 102
	3,		// 103
	3,		// 104
	3,		// 105
	3,		// 106
	3,		// 107
	3,		// 108
	3,		// 109
	3,		// 110
	3,		// 111
	3,		// 112
	3,		// 113
	3,		// 114
	3,		// 115
	3,		// 116
	3,		// 117
	3,		// 118
	3,		// 119
	3,		// 120
	3,		// 121
	3,		// 122

	//// Additional
	0,		// 123
	0,	// 124
	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128

	//// Radiation
	6,		// 129

	//// Smart Water
	2,		// 130
	3,		// 131
	1,		// 132
	1,		// 133
	2,		// 134
	1,		// 135
	2,		// 136
	2,		// 137
	3,		// 138
	3,		// 139
	0,	// 140
	0,	// 141
	0,	// 142
	0,	// 143
	0,	// 144
	0,	// 145
	0,	// 146
	0,	// 147
	0,	// 148
	0,	// 149

	//// Smart Agriculture
	2,		// 150
	2,		// 151
	2,		// 152
	2,		// 153
	2,		// 154
	3,		// 155
	2,		// 156
	0,		// 157
	2,		// 158
	2,		// 159
	2,		// 160
	2,		// 161
	2,		// 162
	3,		// 163
	3,		// 164
	3,		// 165
	2,		// 166
	2,		// 167
	2,		// 168
	0,		// 169

	//// Ambient Control
	2,		// 170
	1,		// 171
	3,		// 172
	0,		// 173
	0,		// 174

	//// 4-20 mA
	3,		// 175
	3,		// 176
	3,		// 177
	3,		// 178
	0,		// 179

	//// Industrial protocols (ModBus & CAN bus)
	0,		// 180
	0,		// 181
	0,		// 182
	0,		// 183
	0,		// 184
	0,		// 185
	0,		// 186
	0,		// 187
	0,		// 188
	0,		// 189

  	// OPC N3 sensor
  	0,    //190
	0,    //191
	0,    //192

	// fever
	2,	// 193
	2,	// 194
	2,	// 195
	0,	// 196
	0,	// 197
	2,	// 198
	0,	// 199

};

	#endif
