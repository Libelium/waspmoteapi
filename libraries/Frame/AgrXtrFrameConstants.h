/*! \file AgrXtrFrameconstants.h
    \brief Header file for Agriculture Xtreme Frame Constants

    Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		1.5
    Design:			David Gascón
    Implementation:	Javier Siscart, Víctor Boria

*/

#ifndef AgrXtrFrameConstants_h
#define AgrXtrFrameConstants_h

#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////////////////////////
// Agricuture Xtreme FRAME definitions
////////////////////////////////////////////////////////////////////////////////

#define AGRX_TC_A						0
#define AGRX_TF_A						1
#define AGRX_HUM_A						2
#define AGRX_PRES_A						3
#define AGRX_TC_D						4
#define AGRX_TF_D						5
#define AGRX_HUM_D						6
#define AGRX_PRES_D						7
#define AGRX_LUXES_A					8
#define AGRX_LUXES_D					9
#define AGRX_US_A						10
#define AGRX_US_D						11
#define AGRX_LW							12
#define AGRX_SR_B						13
#define AGRX_SR_C						14
#define AGRX_SR_E						15
#define AGRX_SR_F						16
#define AGRX_PAR_B						17
#define AGRX_PAR_C						18
#define AGRX_PAR_E						19
#define AGRX_PAR_F						20
#define AGRX_UV_B						21
#define AGRX_UV_C						22
#define AGRX_UV_E						23
#define AGRX_UV_F						24
#define AGRX_TD							25
#define AGRX_SD							26
#define AGRX_FD							27
#define AGRX_CURRENT_SOCKET_F			28
#define AGRX_CURRENT_SOCKET_B			29
#define AGRX_SI411_TC1_A				30
#define AGRX_SI411_TC1_B				31
#define AGRX_SI411_TC1_C				32
#define AGRX_SI411_TC1_D				33
#define AGRX_SI411_MV1_A				34
#define AGRX_SI411_MV1_B				35
#define AGRX_SI411_MV1_C				36
#define AGRX_SI411_MV1_D				37
#define AGRX_SI411_BT1_A				38
#define AGRX_SI411_BT1_B				39
#define AGRX_SI411_BT1_C				40
#define AGRX_SI411_BT1_D				41

// Industrial protocols (ModBus)
#define AGRX_MODBUS_COILS				42
#define AGRX_MODBUS_DISCRETE_INPUT		43
#define AGRX_MODBUS_HOLDING_REGS		44
#define AGRX_MODBUS_INPUT_REGS			45

// Teros11/12
#define AGRX_TEROS11_VWC1_A				46
#define AGRX_TEROS11_VWC1_B				47
#define AGRX_TEROS11_VWC1_C				48
#define AGRX_TEROS11_VWC1_D				49
#define AGRX_TEROS11_DP4_A				50
#define AGRX_TEROS11_DP4_B				51

#define AGRX_DATASOL_RAD				95
#define AGRX_DATASOL_SC1_RAD			96
#define AGRX_DATASOL_SC2_RAD			97
#define AGRX_DATASOL_ETC				98
#define AGRX_DATASOL_PTC				99
#define AGRX_DATASOL_WSP				100
#define AGRX_DATASOL_PSH				101
#define AGRX_DATASOL_NCN				102

// Teros11/12
#define AGRX_TEROS11_DP4_C				103
#define AGRX_TEROS11_DP4_D				104
#define AGRX_TEROS11_TC7_A				105
#define AGRX_TEROS11_TC7_B				106
#define AGRX_TEROS11_TC7_C				107
#define AGRX_TEROS11_TC7_D				108
#define AGRX_TEROS12_VWC2_A				109
#define AGRX_TEROS12_VWC2_B				110
#define AGRX_TEROS12_VWC2_C				111
#define AGRX_TEROS12_VWC2_D				112
#define AGRX_TEROS12_DP5_A				113
#define AGRX_TEROS12_DP5_B				114
#define AGRX_TEROS12_DP5_C				115
#define AGRX_TEROS12_DP5_D				116
#define AGRX_TEROS12_EC3_A				117
#define AGRX_TEROS12_EC3_B				118
#define AGRX_TEROS12_EC3_C				119
#define AGRX_TEROS12_EC3_D				120
#define AGRX_TEROS12_TC8_A				121
#define AGRX_TEROS12_TC8_B				122
#define AGRX_TEROS12_TC8_C				129
#define AGRX_TEROS12_TC8_D				130



// Now some index are reserved for additional fields, already defined
#define AGRX_SO411_CO_A					134
#define AGRX_SO411_CO_B					135
#define AGRX_SO411_CO_C					136
#define AGRX_SO411_CO_D					137
#define AGRX_SO411_TC2_A				138
#define AGRX_SO411_TC2_B				139
#define AGRX_SO411_TC2_C				140
#define AGRX_SO411_TC2_D				141
#define AGRX_SO411_MV2_A				142
#define AGRX_SO411_MV2_B				143
#define AGRX_SO411_MV2_C				144
#define AGRX_SO411_MV2_D				145
#define AGRX_GS3_DP1_A					146
#define AGRX_GS3_DP1_B					147
#define AGRX_GS3_DP1_C					148
#define AGRX_GS3_DP1_D					149
#define AGRX_GS3_EC1_A					150
#define AGRX_GS3_EC1_B					151
#define AGRX_GS3_EC1_C					152
#define AGRX_GS3_EC1_D					153
#define AGRX_GS3_TC3_A					154
#define AGRX_GS3_TC3_B					155
#define AGRX_GS3_TC3_C					156
#define AGRX_GS3_TC3_D					157
#define AGRX_5TE_DP2_A					158
#define AGRX_5TE_DP2_B					159
#define AGRX_5TE_DP2_C					160
#define AGRX_5TE_DP2_D					161
#define AGRX_5TE_EC2_A					162
#define AGRX_5TE_EC2_B					163
#define AGRX_5TE_EC2_C					164
#define AGRX_5TE_EC2_D					165
#define AGRX_5TE_TC4_A					166
#define AGRX_5TE_TC4_B					167
#define AGRX_5TE_TC4_C					168
#define AGRX_5TE_TC4_D					169
#define AGRX_VP4_VP_A					170
#define AGRX_VP4_VP_B					171
#define AGRX_VP4_VP_C					172
#define AGRX_VP4_VP_D					173
#define AGRX_VP4_TC5_A					174
#define AGRX_VP4_TC5_B					175
#define AGRX_VP4_TC5_C					176
#define AGRX_VP4_TC5_D					177
#define AGRX_VP4_RH_A					178
#define AGRX_VP4_RH_B					179
#define AGRX_VP4_RH_C					180
#define AGRX_VP4_RH_D					181
#define AGRX_VP4_AP_A					182
#define AGRX_VP4_AP_B					183
#define AGRX_VP4_AP_C					184
#define AGRX_VP4_AP_D					185
#define AGRX_MPS6_WP_A					186
#define AGRX_MPS6_WP_B					187
#define AGRX_MPS6_WP_C					188
#define AGRX_MPS6_WP_D					189
#define AGRX_MPS6_TC6_A					190
#define AGRX_MPS6_TC6_B					191
#define AGRX_MPS6_TC6_C					192
#define AGRX_MPS6_TC6_D					193
#define AGRX_SF421_BT2_A				194
#define AGRX_SF421_BT2_B				195
#define AGRX_SF421_BT2_C				196
#define AGRX_SF421_BT2_D				197
#define AGRX_SF421_LT_A					198
#define AGRX_SF421_LT_B					199
#define AGRX_SF421_LT_C					200
#define AGRX_SF421_LT_D					201
#define AGRX_5TM_DP3_A					202
#define AGRX_5TM_DP3_B					203
#define AGRX_5TM_DP3_C					204
#define AGRX_5TM_DP3_D					205
#define AGRX_5TM_TC7_A					206
#define AGRX_5TM_TC7_B					207
#define AGRX_5TM_TC7_C					208
#define AGRX_5TM_TC7_D					209
#define AGRX_GMX_WD						210
#define AGRX_GMX_AWD					211
#define AGRX_GMX_WS						212
#define AGRX_GMX_AWS					213
#define AGRX_GMX_AWGD					214
#define AGRX_GMX_AWGS					215
#define AGRX_GMX_WSS					216
#define AGRX_GMX_PT						217
#define AGRX_GMX_PI						218
#define AGRX_GMX_PST					219
#define AGRX_GMX_CWD					220
#define AGRX_GMX_ACWD					221
#define AGRX_GMX_CMPS					222
#define AGRX_GMX_XT						223
#define AGRX_GMX_YT						224
#define AGRX_GMX_ZO						225
#define AGRX_GMX_SVO					226
#define AGRX_GMX_ST						227

#define AGRX_GMX_SR						228
#define AGRX_GMX_SUNSHINE				229
#define AGRX_GMX_SUNRISE				230
#define AGRX_GMX_SOLAR_NOON				231
#define AGRX_GMX_SUNSET					232
#define AGRX_GMX_POS_SUN				233
#define AGRX_GMX_TW_CIV					234
#define AGRX_GMX_TW_NAU					235
#define AGRX_GMX_TW_AST					236
#define AGRX_GMX_PRES					237
#define AGRX_GMX_PRES_SEA				238
#define AGRX_GMX_PRES_STA				239
#define AGRX_GMX_RH						240
#define AGRX_GMX_TEMP					241
#define AGRX_GMX_DEWP					242
#define AGRX_GMX_AH						243
#define AGRX_GMX_AD						244
#define AGRX_GMX_WBT					245
#define AGRX_GMX_WC						246
#define AGRX_GMX_HI						247
#define AGRX_GMX_GPS_CSP				248
#define AGRX_GMX_GPS_ACS				249
#define AGRX_GMX_GPS_CGS				250
#define AGRX_GMX_GPS_CGD				251
#define AGRX_GMX_GPS_LOC				252
#define AGRX_GMX_GPS_HEA				253
#define AGRX_GMX_GPS_SPEED				254
#define AGRX_GMX_GPS_STATUS				255


/// Flash defines //////////////////////////////////////////////////////////////


/*******************************************************************************
 * The following Flash strings define the tags for Agriculture Xtreme sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 ******************************************************************************/

const char	agr_xtr_00[] 	PROGMEM	= "TC_A";
const char 	agr_xtr_01[] 	PROGMEM	= "TF_A";
const char	agr_xtr_02[] 	PROGMEM	= "HUM_A";
const char 	agr_xtr_03[] 	PROGMEM	= "PRES_A";
const char	agr_xtr_04[] 	PROGMEM	= "TC_D";
const char 	agr_xtr_05[] 	PROGMEM	= "TF_D";
const char	agr_xtr_06[] 	PROGMEM	= "HUM_D";
const char 	agr_xtr_07[] 	PROGMEM	= "PRES_D";
const char	agr_xtr_08[] 	PROGMEM	= "LUX_A";
const char 	agr_xtr_09[] 	PROGMEM	= "LUX_D";
const char	agr_xtr_10[] 	PROGMEM	= "US_A";
const char	agr_xtr_11[] 	PROGMEM	= "US_D";
const char 	agr_xtr_12[] 	PROGMEM	= "LW";
const char 	agr_xtr_13[] 	PROGMEM	= "SR_B";
const char 	agr_xtr_14[] 	PROGMEM	= "SR_C";
const char 	agr_xtr_15[] 	PROGMEM	= "SR_E";
const char 	agr_xtr_16[] 	PROGMEM	= "SR_F";
const char 	agr_xtr_17[] 	PROGMEM	= "PAR_B";
const char 	agr_xtr_18[] 	PROGMEM	= "PAR_C";
const char 	agr_xtr_19[] 	PROGMEM	= "PAR_E";
const char 	agr_xtr_20[] 	PROGMEM	= "PAR_F";
const char 	agr_xtr_21[] 	PROGMEM	= "UV_B";
const char 	agr_xtr_22[] 	PROGMEM	= "UV_C";
const char 	agr_xtr_23[] 	PROGMEM	= "UV_E";
const char 	agr_xtr_24[] 	PROGMEM	= "UV_F";
const char 	agr_xtr_25[] 	PROGMEM	= "TD";
const char 	agr_xtr_26[] 	PROGMEM	= "SD";
const char 	agr_xtr_27[] 	PROGMEM	= "FD";
const char 	agr_xtr_28[] 	PROGMEM	= "CUR_F";
const char 	agr_xtr_29[] 	PROGMEM	= "CUR_B";
const char 	agr_xtr_30[] 	PROGMEM	= "TC1_A";
const char 	agr_xtr_31[] 	PROGMEM	= "TC1_B";
const char 	agr_xtr_32[] 	PROGMEM	= "TC1_C";
const char 	agr_xtr_33[] 	PROGMEM	= "TC1_D";
const char 	agr_xtr_34[] 	PROGMEM	= "MV1_A";
const char 	agr_xtr_35[] 	PROGMEM	= "MV1_B";
const char 	agr_xtr_36[] 	PROGMEM	= "MV1_C";
const char 	agr_xtr_37[] 	PROGMEM	= "MV1_D";
const char 	agr_xtr_38[] 	PROGMEM	= "BT1_A";
const char 	agr_xtr_39[] 	PROGMEM	= "BT1_B";
const char 	agr_xtr_40[] 	PROGMEM	= "BT1_C";
const char 	agr_xtr_41[] 	PROGMEM	= "BT1_D";

// Industrial protocols: Modbus
const char	agr_xtr_42[]  PROGMEM = "MB_COILS"; 
const char	agr_xtr_43[]  PROGMEM = "MB_DI"; 
const char	agr_xtr_44[]  PROGMEM = "MB_HR"; 
const char	agr_xtr_45[]  PROGMEM = "MB_IR"; 

// Teros11/12
const char	agr_xtr_46[]  PROGMEM = "VWC1_A"; 
const char	agr_xtr_47[]  PROGMEM = "VWC1_B"; 
const char	agr_xtr_48[]  PROGMEM = "VWC1_C"; 
const char	agr_xtr_49[]  PROGMEM = "VWC1_D"; 
const char	agr_xtr_50[]  PROGMEM = "DP4_A"; 
const char	agr_xtr_51[]  PROGMEM = "DP4_B"; 

// Additional
const char	agr_xtr_52[] 	PROGMEM	= "BAT";
const char	agr_xtr_53[] 	PROGMEM	= "GPS";
const char	agr_xtr_54[] 	PROGMEM	= "RSSI";
const char	agr_xtr_55[] 	PROGMEM	= "MAC";
const char	agr_xtr_56[] 	PROGMEM	= "NA";
const char	agr_xtr_57[] 	PROGMEM	= "NID";
const char	agr_xtr_58[] 	PROGMEM	= "DATE";
const char	agr_xtr_59[] 	PROGMEM	= "TIME";
const char	agr_xtr_60[] 	PROGMEM	= "GMT";
const char	agr_xtr_61[] 	PROGMEM	= "RAM";
const char	agr_xtr_62[] 	PROGMEM	= "IN_TEMP"; // (deprecated for Waspv15)
const char	agr_xtr_63[]	PROGMEM = "ACC";
const char	agr_xtr_64[]  	PROGMEM = "MILLIS";
const char	agr_xtr_65[] 	PROGMEM = "STR";
const char	agr_xtr_66[]  	PROGMEM = "";
const char	agr_xtr_67[]	PROGMEM = "";
const char	agr_xtr_68[]  	PROGMEM = "UID";
const char	agr_xtr_69[]  	PROGMEM = "RB";
const char	agr_xtr_70[]  	PROGMEM = "PM1";
const char	agr_xtr_71[]  	PROGMEM = "PM2_5";
const char	agr_xtr_72[]  	PROGMEM = "PM10";
const char	agr_xtr_73[]  	PROGMEM = "PART";
const char	agr_xtr_74[]  	PROGMEM = "TC";
const char	agr_xtr_75[]  	PROGMEM = "TF";
const char	agr_xtr_76[]  	PROGMEM = "HUM";
const char	agr_xtr_77[]  	PROGMEM = "PRES";
const char	agr_xtr_78[]  	PROGMEM = "LUX";
const char	agr_xtr_79[]  	PROGMEM = "US";
const char	agr_xtr_80[]  	PROGMEM = "";
const char	agr_xtr_81[]  	PROGMEM = "";
const char	agr_xtr_82[]  	PROGMEM = "";
const char	agr_xtr_83[]  	PROGMEM = "";
const char	agr_xtr_84[]  	PROGMEM = "";
const char	agr_xtr_85[]  	PROGMEM = "";
const char	agr_xtr_86[]  	PROGMEM = "";
const char	agr_xtr_87[]  	PROGMEM = "";
const char	agr_xtr_88[]  	PROGMEM = "";
const char	agr_xtr_89[]  	PROGMEM = "SPEED_OG";
const char	agr_xtr_90[]  	PROGMEM = "COURSE_OG";
const char	agr_xtr_91[]  	PROGMEM = "ALT";
const char	agr_xtr_92[]  	PROGMEM = "HDOP";
const char	agr_xtr_93[]  	PROGMEM = "VDOP";
const char	agr_xtr_94[]  	PROGMEM = "PDOP";
const char	agr_xtr_95[]  	PROGMEM = "RAD";
const char	agr_xtr_96[]  	PROGMEM = "SC1_RAD";
const char	agr_xtr_97[]  	PROGMEM = "SC2_RAD";
const char	agr_xtr_98[]  	PROGMEM = "ETC";
const char	agr_xtr_99[]  	PROGMEM = "PTC";
const char	agr_xtr_100[]  	PROGMEM = "WSP";
const char	agr_xtr_101[]  	PROGMEM = "PSH";
const char	agr_xtr_102[]  	PROGMEM = "NCN";

// Teros11/12
const char	agr_xtr_103[]  	PROGMEM = "DP4_C";
const char	agr_xtr_104[]  	PROGMEM = "DP4_D";
const char	agr_xtr_105[]  	PROGMEM = "TC7_A";
const char	agr_xtr_106[]  	PROGMEM = "TC7_B";
const char	agr_xtr_107[]  	PROGMEM = "TC7_C";
const char	agr_xtr_108[]  	PROGMEM = "TC7_D";
const char	agr_xtr_109[]  	PROGMEM = "VWC2_A";
const char	agr_xtr_110[]  	PROGMEM = "VWC2_B";
const char	agr_xtr_111[]  	PROGMEM = "VWC2_C";
const char	agr_xtr_112[]  	PROGMEM = "VWC2_D";
const char	agr_xtr_113[]  	PROGMEM = "DP5_A";
const char	agr_xtr_114[]  	PROGMEM = "DP5_B";
const char	agr_xtr_115[]  	PROGMEM = "DP5_C";
const char	agr_xtr_116[]  	PROGMEM = "DP5_D";
const char	agr_xtr_117[]  	PROGMEM = "EC3_A";
const char	agr_xtr_118[]  	PROGMEM = "EC3_B";
const char	agr_xtr_119[]  	PROGMEM = "EC3_C";
const char	agr_xtr_120[]  	PROGMEM = "EC3_D";
const char	agr_xtr_121[]  	PROGMEM = "TC8_A";
const char	agr_xtr_122[]  	PROGMEM = "TC8_B";

const char	agr_xtr_123[]  	PROGMEM = "TST";
const char	agr_xtr_124[]  	PROGMEM = "";
const char	agr_xtr_125[]  	PROGMEM = "VAPI";
const char	agr_xtr_126[]  	PROGMEM = "VPROG";
const char	agr_xtr_127[]  	PROGMEM = "VBOOT";
const char	agr_xtr_128[]  	PROGMEM = "PS";

const char	agr_xtr_129[]  	PROGMEM = "TC8_C";
const char	agr_xtr_130[]  	PROGMEM = "TC8_D";

const char	agr_xtr_131[]  	PROGMEM = "";
const char	agr_xtr_132[]  	PROGMEM = "";
const char	agr_xtr_133[]  	PROGMEM = "";
const char	agr_xtr_134[]  	PROGMEM = "CO_A";
const char	agr_xtr_135[]  	PROGMEM = "CO_B";
const char	agr_xtr_136[]  	PROGMEM = "CO_C";
const char	agr_xtr_137[]  	PROGMEM = "CO_D";
const char	agr_xtr_138[]  	PROGMEM = "TC2_A";
const char	agr_xtr_139[]  	PROGMEM = "TC2_B";
const char	agr_xtr_140[]  	PROGMEM = "TC2_C";
const char	agr_xtr_141[]  	PROGMEM = "TC2_D";
const char	agr_xtr_142[]  	PROGMEM = "MV2_A";
const char	agr_xtr_143[]  	PROGMEM = "MV2_B";
const char	agr_xtr_144[]  	PROGMEM = "MV2_C";
const char	agr_xtr_145[]  	PROGMEM = "MV2_D";
const char	agr_xtr_146[]  	PROGMEM = "DP1_A";
const char	agr_xtr_147[]  	PROGMEM = "DP1_B";
const char	agr_xtr_148[]  	PROGMEM = "DP1_C";
const char	agr_xtr_149[]  	PROGMEM = "DP1_D";
const char	agr_xtr_150[]  	PROGMEM = "EC1_A";
const char	agr_xtr_151[]  	PROGMEM = "EC1_B";
const char	agr_xtr_152[]  	PROGMEM = "EC1_C";
const char	agr_xtr_153[]  	PROGMEM = "EC1_D";
const char	agr_xtr_154[]  	PROGMEM = "TC3_A";
const char	agr_xtr_155[]  	PROGMEM = "TC3_B";
const char	agr_xtr_156[]  	PROGMEM = "TC3_C";
const char	agr_xtr_157[]  	PROGMEM = "TC3_D";
const char	agr_xtr_158[]  	PROGMEM = "DP2_A";
const char	agr_xtr_159[]  	PROGMEM = "DP2_B";
const char	agr_xtr_160[]  	PROGMEM = "DP2_C";
const char	agr_xtr_161[]  	PROGMEM = "DP2_D";
const char	agr_xtr_162[]  	PROGMEM = "EC2_A";
const char	agr_xtr_163[]  	PROGMEM = "EC2_B";
const char	agr_xtr_164[]  	PROGMEM = "EC2_C";
const char	agr_xtr_165[]  	PROGMEM = "EC2_D";
const char	agr_xtr_166[]  	PROGMEM = "TC4_A";
const char	agr_xtr_167[]  	PROGMEM = "TC4_B";
const char	agr_xtr_168[]  	PROGMEM = "TC4_C";
const char	agr_xtr_169[]  	PROGMEM = "TC4_D";
const char	agr_xtr_170[]  	PROGMEM = "VP_A";
const char	agr_xtr_171[]  	PROGMEM = "VP_B";
const char	agr_xtr_172[]  	PROGMEM = "VP_C";
const char	agr_xtr_173[]  	PROGMEM = "VP_D";
const char	agr_xtr_174[]  	PROGMEM = "TC5_A";
const char	agr_xtr_175[]  	PROGMEM = "TC5_B";
const char	agr_xtr_176[]  	PROGMEM = "TC5_C";
const char	agr_xtr_177[]  	PROGMEM = "TC5_D";
const char	agr_xtr_178[]  	PROGMEM = "RH_A";
const char	agr_xtr_179[]  	PROGMEM = "RH_B";
const char	agr_xtr_180[]  	PROGMEM = "RH_C";
const char	agr_xtr_181[]  	PROGMEM = "RH_D";
const char	agr_xtr_182[]  	PROGMEM = "AP_A";
const char	agr_xtr_183[]  	PROGMEM = "AP_B";
const char	agr_xtr_184[]  	PROGMEM = "AP_C";
const char	agr_xtr_185[]  	PROGMEM = "AP_D";
const char	agr_xtr_186[]  	PROGMEM = "WP_A";
const char	agr_xtr_187[]  	PROGMEM = "WP_B";
const char	agr_xtr_188[]  	PROGMEM = "WP_C";
const char	agr_xtr_189[]  	PROGMEM = "WP_D";
const char	agr_xtr_190[]  	PROGMEM = "TC6_A";
const char	agr_xtr_191[]  	PROGMEM = "TC6_B";
const char	agr_xtr_192[]  	PROGMEM = "TC6_C";
const char	agr_xtr_193[]  	PROGMEM = "TC6_D";
const char	agr_xtr_194[]  	PROGMEM = "BT2_A";
const char	agr_xtr_195[]  	PROGMEM = "BT2_B";
const char	agr_xtr_196[]  	PROGMEM = "BT2_C";
const char	agr_xtr_197[]  	PROGMEM = "BT2_D";
const char	agr_xtr_198[]  	PROGMEM = "LT_A";
const char	agr_xtr_199[]  	PROGMEM = "LT_B";
const char	agr_xtr_200[]  	PROGMEM = "LT_C";
const char	agr_xtr_201[]  	PROGMEM = "LT_D";
const char	agr_xtr_202[]  	PROGMEM = "DP3_A";
const char	agr_xtr_203[]  	PROGMEM = "DP3_B";
const char	agr_xtr_204[]  	PROGMEM = "DP3_C";
const char	agr_xtr_205[]  	PROGMEM = "DP3_D";
const char	agr_xtr_206[]  	PROGMEM = "TC7_A";
const char	agr_xtr_207[]  	PROGMEM = "TC7_B";
const char	agr_xtr_208[]  	PROGMEM = "TC7_C";
const char	agr_xtr_209[]  	PROGMEM = "TC7_D";
const char	agr_xtr_210[]  	PROGMEM = "WD";
const char	agr_xtr_211[]  	PROGMEM = "AWD";
const char	agr_xtr_212[]  	PROGMEM = "WS";
const char	agr_xtr_213[]  	PROGMEM = "AWS";
const char	agr_xtr_214[]  	PROGMEM = "AWGD";
const char	agr_xtr_215[]  	PROGMEM = "AWGS";
const char	agr_xtr_216[]  	PROGMEM = "WSS";
const char	agr_xtr_217[]  	PROGMEM = "PT";
const char	agr_xtr_218[]  	PROGMEM = "PI";
const char	agr_xtr_219[]  	PROGMEM = "PST";
const char	agr_xtr_220[]  	PROGMEM = "CWD";
const char	agr_xtr_221[]  	PROGMEM = "ACWD";
const char	agr_xtr_222[]  	PROGMEM = "CMPS";
const char	agr_xtr_223[]  	PROGMEM = "XT";
const char	agr_xtr_224[]  	PROGMEM = "YT";
const char	agr_xtr_225[]  	PROGMEM = "ZO";
const char	agr_xtr_226[]  	PROGMEM = "SVO";
const char	agr_xtr_227[]  	PROGMEM = "ST";

const char	agr_xtr_228[]  	PROGMEM = "SR_WS";
const char	agr_xtr_229[]  	PROGMEM = "SSH_WS";
const char	agr_xtr_230[]  	PROGMEM = "SRT_WS";
const char	agr_xtr_231[]  	PROGMEM = "SNT_WS";
const char	agr_xtr_232[]  	PROGMEM = "ST_WS";
const char	agr_xtr_233[]  	PROGMEM = "PS_WS";
const char	agr_xtr_234[]  	PROGMEM = "TC_WS";
const char	agr_xtr_235[]  	PROGMEM = "TN_WS";
const char	agr_xtr_236[]  	PROGMEM = "TA_WS";
const char	agr_xtr_237[]  	PROGMEM = "PRES_WS";
const char	agr_xtr_238[]  	PROGMEM = "PRESSL_WS";
const char	agr_xtr_239[]  	PROGMEM = "PRESS_WS";
const char	agr_xtr_240[]  	PROGMEM = "RH_WS";
const char	agr_xtr_241[]  	PROGMEM = "TEM_WS";
const char	agr_xtr_242[]  	PROGMEM = "DP_WS";
const char	agr_xtr_243[]  	PROGMEM = "AH_WS";
const char	agr_xtr_244[]  	PROGMEM = "AD_WS";
const char	agr_xtr_245[]  	PROGMEM = "WBT_WS";
const char	agr_xtr_246[]  	PROGMEM = "WC_WS";
const char	agr_xtr_247[]  	PROGMEM = "HI_WS";
const char	agr_xtr_248[]  	PROGMEM = "GPS_CSP";
const char	agr_xtr_249[]  	PROGMEM = "GPS_ACSP";
const char	agr_xtr_250[]  	PROGMEM = "GPS_GSP";
const char	agr_xtr_251[]  	PROGMEM = "GPS_GDIR";
const char	agr_xtr_252[]  	PROGMEM = "GPS_LOC";
const char	agr_xtr_253[]  	PROGMEM = "GPS_H";
const char	agr_xtr_254[]  	PROGMEM = "GPS_SP";
const char	agr_xtr_255[]  	PROGMEM = "GPS_ST";


/*******************************************************************************
 * SENSOR_TABLE - Sensor label table
 *
 * This table specifies the tag for each sensor. Every tag has been previously
 * defined in Flash memory
 ******************************************************************************/
const char* const AGR_XTR_TABLE[] PROGMEM=
{
	agr_xtr_00,
	agr_xtr_01,
	agr_xtr_02,
	agr_xtr_03,
	agr_xtr_04,
	agr_xtr_05,
	agr_xtr_06,
	agr_xtr_07,
	agr_xtr_08,
	agr_xtr_09,
	agr_xtr_10,
	agr_xtr_11,
 	agr_xtr_12,
 	agr_xtr_13,
 	agr_xtr_14,
 	agr_xtr_15,
 	agr_xtr_16,
 	agr_xtr_17,
 	agr_xtr_18,
	agr_xtr_19,
	agr_xtr_20,
	agr_xtr_21,
	agr_xtr_22,
	agr_xtr_23,
	agr_xtr_24,
	agr_xtr_25,
	agr_xtr_26,
	agr_xtr_27,
	agr_xtr_28,
	agr_xtr_29,
	agr_xtr_30,
	agr_xtr_31,
	agr_xtr_32,
	agr_xtr_33,
	agr_xtr_34,
	agr_xtr_35,
	agr_xtr_36,
	agr_xtr_37,
	agr_xtr_38,
	agr_xtr_39,
	agr_xtr_40,
	agr_xtr_41,
	agr_xtr_42,
	agr_xtr_43,
	agr_xtr_44,
	agr_xtr_45,
	agr_xtr_46,
	agr_xtr_47,
	agr_xtr_48,
	agr_xtr_49,
	agr_xtr_50,
	agr_xtr_51,
	agr_xtr_52,
	agr_xtr_53,
	agr_xtr_54,
	agr_xtr_55,
	agr_xtr_56,
	agr_xtr_57,
	agr_xtr_58,
	agr_xtr_59,
	agr_xtr_60,
	agr_xtr_61,
	agr_xtr_62,
	agr_xtr_63,
	agr_xtr_64,
	agr_xtr_65,
	agr_xtr_66,
	agr_xtr_67,
	agr_xtr_68,
	agr_xtr_69,
	agr_xtr_70,
	agr_xtr_71,
	agr_xtr_72,
	agr_xtr_73,
	agr_xtr_74,
	agr_xtr_75,
	agr_xtr_76,
	agr_xtr_77,
	agr_xtr_78,
	agr_xtr_79,
	agr_xtr_80,
	agr_xtr_81,
	agr_xtr_82,
	agr_xtr_83,
	agr_xtr_84,
	agr_xtr_85,
	agr_xtr_86,
	agr_xtr_87,
	agr_xtr_88,
	agr_xtr_89,
	agr_xtr_90,
	agr_xtr_91,
	agr_xtr_92,
	agr_xtr_93,
	agr_xtr_94,
	agr_xtr_95,
	agr_xtr_96,
	agr_xtr_97,
	agr_xtr_98,
	agr_xtr_99,
	agr_xtr_100,
	agr_xtr_101,
	agr_xtr_102,
	agr_xtr_103,
	agr_xtr_104,
	agr_xtr_105,
	agr_xtr_106,
	agr_xtr_107,
	agr_xtr_108,
	agr_xtr_109,
	agr_xtr_110,
	agr_xtr_111,
	agr_xtr_112,
	agr_xtr_113,
	agr_xtr_114,
	agr_xtr_115,
	agr_xtr_116,
	agr_xtr_117,
	agr_xtr_118,
	agr_xtr_119,
	agr_xtr_120,
	agr_xtr_121,
	agr_xtr_122,
	agr_xtr_123,
	agr_xtr_124,
	agr_xtr_125,
	agr_xtr_126,
	agr_xtr_127,
	agr_xtr_128,
	agr_xtr_129,
	agr_xtr_130,
	agr_xtr_131,
	agr_xtr_132,
	agr_xtr_133,
	agr_xtr_134,
	agr_xtr_135,
	agr_xtr_136,
	agr_xtr_137,
	agr_xtr_138,
	agr_xtr_139,
	agr_xtr_140,
	agr_xtr_141,
	agr_xtr_142,
	agr_xtr_143,
	agr_xtr_144,
	agr_xtr_145,
	agr_xtr_146,
	agr_xtr_147,
	agr_xtr_148,
	agr_xtr_149,
	agr_xtr_150,
	agr_xtr_151,
	agr_xtr_152,
	agr_xtr_153,
	agr_xtr_154,
	agr_xtr_155,
	agr_xtr_156,
	agr_xtr_157,
	agr_xtr_158,
	agr_xtr_159,
	agr_xtr_160,
	agr_xtr_161,
	agr_xtr_162,
	agr_xtr_163,
	agr_xtr_164,
	agr_xtr_165,
	agr_xtr_166,
	agr_xtr_167,
	agr_xtr_168,
	agr_xtr_169,
	agr_xtr_170,
	agr_xtr_171,
	agr_xtr_172,
	agr_xtr_173,
	agr_xtr_174,
	agr_xtr_175,
	agr_xtr_176,
	agr_xtr_177,
	agr_xtr_178,
	agr_xtr_179,
	agr_xtr_180,
	agr_xtr_181,
	agr_xtr_182,
	agr_xtr_183,
	agr_xtr_184,
	agr_xtr_185,
	agr_xtr_186,
	agr_xtr_187,
	agr_xtr_188,
	agr_xtr_189,
	agr_xtr_190,
	agr_xtr_191,
	agr_xtr_192,
	agr_xtr_193,
	agr_xtr_194,
	agr_xtr_195,
	agr_xtr_196,
	agr_xtr_197,
	agr_xtr_198,
	agr_xtr_199,
	agr_xtr_200,
	agr_xtr_201,
	agr_xtr_202,
	agr_xtr_203,
	agr_xtr_204,
	agr_xtr_205,
	agr_xtr_206,
	agr_xtr_207,
	agr_xtr_208,
	agr_xtr_209,
	agr_xtr_210,
	agr_xtr_211,
	agr_xtr_212,
	agr_xtr_213,
	agr_xtr_214,
	agr_xtr_215,
	agr_xtr_216,
	agr_xtr_217,
	agr_xtr_218,
	agr_xtr_219,
	agr_xtr_220,
	agr_xtr_221,
	agr_xtr_222,
	agr_xtr_223,
	agr_xtr_224,
	agr_xtr_225,
	agr_xtr_226,
	agr_xtr_227,
	agr_xtr_228,
	agr_xtr_229,
	agr_xtr_230,
	agr_xtr_231,
	agr_xtr_232,
	agr_xtr_233,
	agr_xtr_234,
	agr_xtr_235,
	agr_xtr_236,
	agr_xtr_237,
	agr_xtr_238,
	agr_xtr_239,
	agr_xtr_240,
	agr_xtr_241,
	agr_xtr_242,
	agr_xtr_243,
	agr_xtr_244,
	agr_xtr_245,
	agr_xtr_246,
	agr_xtr_247,
	agr_xtr_248,
	agr_xtr_249,
	agr_xtr_250,
	agr_xtr_251,
	agr_xtr_252,
	agr_xtr_253,
	agr_xtr_254,
	agr_xtr_255,

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
const uint8_t AGR_XTR_TYPE_TABLE[] PROGMEM=
{
	2,		// 0
	2, 		// 1
	2, 		// 2
	2, 		// 3
	2, 		// 4
	2, 		// 5
	2, 		// 6
	2, 		// 7
	4, 		// 8
	4, 		// 9
	1, 		// 10
	1, 		// 11
	2, 		// 12
	2, 		// 13
	2, 		// 14
	2, 		// 15
	2, 		// 16
	2, 		// 17
	2, 		// 18
	2, 		// 19
	2, 		// 20
	2, 		// 21
	2,		// 22
	2,		// 23
	2,		// 24
	2,		// 25
	2,		// 26
	2,		// 27
	2,		// 28
	2,		// 29
	2,		// 30
	2,		// 31
	2,		// 32
	2,		// 33
	2,		// 34
	2,		// 35
	2,		// 36
	2,		// 37
	2,		// 38
	2,		// 39
	2,		// 40
	2,		// 41

	//// Industrial protocols (ModBus)
	1,		// 42
	1,		// 43
	1,		// 44
	1,		// 45
	
	2,		// 46
	2,		// 47
	2,		// 48
	2,		// 49
	2,		// 50
	2,		// 51

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
	0, // 				// 66
	0, // 				// 67
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

	3,		// 89
	3,		// 90
	3,		// 91
	2,		// 92
	2,		// 93
	2,		// 94

	1,		// 95
	1,		// 96
	1,		// 97
	2,		// 98
	2,		// 99
	2,		// 100
	2,		// 101
	0,		// 102
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
	2,		// 121
	2,		// 122

	4,		// 123
	0,		// 124
	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128
	2,		// 129
	2,		// 130
	0,		// 131
	0,		// 132
	0,		// 133

	2,		// 134
	2,		// 135
	2,		// 136
	2,		// 137
	2,		// 138
	2,		// 139
	2,		// 140
	2,		// 141
	2,		// 142
	2,		// 143
	2,		// 144
	2,		// 145
	2,		// 146
	2,		// 147
	2,		// 148
	2,		// 149
	2,		// 150
	2,		// 151
	2,		// 152
	2,		// 153
	2,		// 154
	2,		// 155
	2,		// 156
	2,		// 157
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
	2,		// 169
	2,		// 170
	2,		// 171
	2,		// 172
	2,		// 173
	2,		// 174
	2,		// 175
	2,		// 176
	2,		// 177
	2,		// 178
	2,		// 179
	2,		// 180
	2,		// 181
	2,		// 182
	2,		// 183
	2,		// 184
	2,		// 185
	2,		// 186
	2,		// 187
	2,		// 188
	2,		// 189
	2,		// 190
	2,		// 191
	2,		// 192
	2,		// 193
	2,		// 194
	2,		// 195
	2,		// 196
	2,		// 197
	2,		// 198
	2,		// 199
	2,		// 200
	2,		// 201
	2,		// 202
	2,		// 203
	2,		// 204
	2,		// 205
	2,		// 206
	2,		// 207
	2,		// 208
	2,		// 209
	1,		// 210
	1,		// 211
	2,		// 212
	2,		// 213
	1,		// 214
	2,		// 215
	3,		// 216
	2,		// 217
	2,		// 218
	0,		// 219
	1,		// 220
	1,		// 221
	1,		// 222
	2,		// 223
	2,		// 224
	2,		// 225
	2,		// 226
	3,		// 227

	1,		// 228
	2,		// 229
	3,		// 230
	3,		// 231
	3,		// 232
	3,		// 233
	3,		// 234
	3,		// 235
	3,		// 236
	2,		// 237
	2,		// 238
	2,		// 239
	1,		// 240
	2,		// 241
	2,		// 242
	2,		// 243
	2,		// 244
	2,		// 245
	2,		// 246
	1,		// 247
	2,		// 248
	2,		// 249
	2,		// 250
	1,		// 251
	3,		// 252
	1,		// 253
	2,		// 254
	3,		// 255

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
const uint8_t AGR_XTR_FIELD_TABLE[] PROGMEM=
{
	1,		// 0
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
	1, 		// 12
	1, 		// 13
	1, 		// 14
	1, 		// 15
	1, 		// 16
	1, 		// 17
	1, 		// 18
	1, 		// 19
	1, 		// 20
	1, 		// 21
	1,		// 22
	1,		// 23
	1,		// 24
	1,		// 25
	1,		// 26
	1,		// 27
	1,		// 28
	1,		// 29
	1,		// 30
	1,		// 31
	1,		// 32
	1,		// 33
	1,		// 34
	1,		// 35
	1,		// 36
	1,		// 37
	1,		// 38
	1,		// 39
	1,		// 40
	1,		// 41

	//// Industrial protocols (ModBus & CAN bus)
	2,		// 42
	2,		// 43
	3,		// 44
	3,		// 45
	1,		// 46
	1,		// 47
	1,		// 48
	1,		// 49
	1,		// 50
	1,		// 51

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
	1, // str_STR		// 65
	1, // str_MBT		// 66
	1, // str_MWIFI		// 67
	1, // str_UID		// 68
	1, // str_RB		// 69
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

	1,		// 123
	1,		// 124
	1,		// 125
	1,		// 126
	1,		// 127
	1,		// 128
	1,		// 129
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
	1,		// 170
	1,		// 171
	1,		// 172
	1,		// 173
	1,		// 174
	1,		// 175
	1,		// 176
	1,		// 177
	1,		// 178
	1,		// 179
	1,		// 180
	1,		// 181
	1,		// 182
	1,		// 183
	1,		// 184
	1,		// 185
	1,		// 186
	1,		// 187
	1,		// 188
	1,		// 189
	1,		// 190
	1,		// 191
	1,		// 192
	1,		// 193
	1,		// 194
	1,		// 195
	1,		// 196
	1,		// 197
	1,		// 198
	1,		// 199
	1,		// 200
	1,		// 201
	1,		// 202
	1,		// 203
	1,		// 204
	1,		// 205
	1,		// 206
	1,		// 207
	1,		// 208
	1,		// 209
	1,		// 210
	1,		// 211
	1,		// 212
	1,		// 213
	1,		// 214
	1,		// 215
	1,		// 216
	1,		// 217
	1,		// 218
	1,		// 219
	1,		// 220
	1,		// 221
	1,		// 222
	1,		// 223
	1,		// 224
	1,		// 225
	1,		// 226
	1,		// 227

	1,		// 228
	1,		// 229
	1,		// 230
	1,		// 231
	1,		// 232
	1,		// 233
	1,		// 234
	1,		// 235
	1,		// 236
	1,		// 237
	1,		// 238
	1,		// 239
	1,		// 240
	1,		// 241
	1,		// 242
	1,		// 243
	1,		// 244
	1,		// 245
	1,		// 246
	1,		// 247
	1,		// 248
	1,		// 249
	1,		// 250
	1,		// 251
	1,		// 252
	1,		// 253
	1,		// 254
	1,		// 255

};



/*******************************************************************************
* DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
*
* This table specifies the number of decimals for each sensor for ASCII frames
******************************************************************************/
const uint8_t AGR_XTR_DECIMAL_TABLE[] PROGMEM =
{
	2,		// 0
	2, 		// 1
	1, 		// 2
	2, 		// 3
	2, 		// 4
	2, 		// 5
	1, 		// 6
	2, 		// 7
	0, 		// 8
	0, 		// 9
	0, 		// 10
	0, 		// 11
	4, 		// 12
	2, 		// 13
	2, 		// 14
	2, 		// 15
	2, 		// 16
	2, 		// 17
	2, 		// 18
	2, 		// 19
	2, 		// 20
	2, 		// 21
	2,		// 22
	2,		// 23
	2,		// 24
	3,		// 25
	3,		// 26
	3,		// 27
	3,		// 28
	3,		// 29
	4,		// 30
	4,		// 31
	4,		// 32
	4,		// 33
	3,		// 34
	3,		// 35
	3,		// 36
	3,		// 37
	3,		// 38
	3,		// 39
	3,		// 40
	3,		// 41

	//// Industrial protocols (ModBus & CAN bus)
	0,		// 42
	0,		// 43
	0,		// 44
	0,		// 45
	2,		// 46
	2,		// 47
	2,		// 48
	2,		// 49
	2,		// 50
	2,		// 51

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
	0, // str_MBT		// 66
	0, // str_MWIFI		// 67
	0, // str_UID		// 68
	0, // str_RB		// 69
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
	3,		// 92
	3,		// 93
	3,		// 94

	0,		// 95
	0,		// 96
	0,		// 97
	1,		// 98
	1,		// 99
	1,		// 100
	2,		// 101
	0,		// 102
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
	2,		// 121
	2,		// 122
	0,		// 123
	0,		// 124

	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128
	2,		// 129
	2,		// 130
	0,		// 131
	0,		// 132
	0,		// 133

	3,		// 134
	3,		// 135
	3,		// 136
	3,		// 137
	1,		// 138
	1,		// 139
	1,		// 140
	1,		// 141
	4,		// 142
	4,		// 143
	4,		// 144
	4,		// 145
	2,		// 146
	2,		// 147
	2,		// 148
	2,		// 149
	0,		// 150
	0,		// 151
	0,		// 152
	0,		// 153
	2,		// 154
	2,		// 155
	2,		// 156
	2,		// 157
	2,		// 158
	2,		// 159
	2,		// 160
	2,		// 161
	2,		// 162
	2,		// 163
	2,		// 164
	2,		// 165
	1,		// 166
	1,		// 167
	1,		// 168
	1,		// 169
	3,		// 170
	3,		// 171
	3,		// 172
	3,		// 173
	1,		// 174
	1,		// 175
	1,		// 176
	1,		// 177
	1,		// 178
	1,		// 179
	1,		// 180
	1,		// 181
	2,		// 182
	2,		// 183
	2,		// 184
	2,		// 185
	1,		// 186
	1,		// 187
	1,		// 188
	1,		// 189
	1,		// 190
	1,		// 191
	1,		// 192
	1,		// 193
	3,		// 194
	3,		// 195
	3,		// 196
	3,		// 197
	3,		// 198
	3,		// 199
	3,		// 200
	3,		// 201
	2,		// 202
	2,		// 203
	2,		// 204
	2,		// 205
	1,		// 206
	1,		// 207
	1,		// 208
	1,		// 209
	0,		// 210
	0,		// 211
	2,		// 212
	2,		// 213
	0,		// 214
	2,		// 215
	0,		// 216
	3,		// 217
	3,		// 218
	0,		// 219
	0,		// 220
	0,		// 221
	0,		// 222
	0,		// 223
	0,		// 224
	0,		// 225
	1,		// 226
	0,		// 227

	0,		// 228
	2,		// 229
	0,		// 230
	0,		// 231
	0,		// 232
	0,		// 233
	0,		// 234
	0,		// 235
	0,		// 236
	1,		// 237
	1,		// 238
	1,		// 239
	0,		// 240
	1,		// 241
	1,		// 242
	2,		// 243
	1,		// 244
	1,		// 245
	0,		// 246
	0,		// 247
	2,		// 248
	2,		// 249
	2,		// 250
	0,		// 251
	0,		// 252
	0,		// 253
	2,		// 254
	0,		// 255

};

#endif
