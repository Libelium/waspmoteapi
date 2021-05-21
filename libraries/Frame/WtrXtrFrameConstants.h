/*! \file WtrXtrFrameconstants.h
    \brief Header file for Water Xtreme Frame Constants

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		1.0
    Design:			David Gascón
    Implementation:	Javier Siscart, Víctor Boria

*/

#ifndef WtrXtrFrameConstants_h
#define WtrXtrFrameConstants_h

#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////////////////////////
// Water Xtreme FRAME definitions
////////////////////////////////////////////////////////////////////////////////

#define WTRX_TC_A						0
#define WTRX_TF_A						1
#define WTRX_HUM_A						2
#define WTRX_PRES_A						3
#define WTRX_TC_D						4
#define WTRX_TF_D						5
#define WTRX_HUM_D						6
#define WTRX_PRES_D						7
#define WTRX_LUXES_A					8
#define WTRX_LUXES_D					9
#define WTRX_US_A						10
#define WTRX_US_D						11
#define WTRX_OPTOD_TC1_A				12
#define WTRX_OPTOD_TC1_B				13
#define WTRX_OPTOD_TC1_C				14
#define WTRX_OPTOD_TC1_D				15
#define WTRX_OPTOD_TC1_E				16
#define WTRX_OPTOD_OS_A					17
#define WTRX_OPTOD_OS_B					18
#define WTRX_OPTOD_OS_C					19
#define WTRX_OPTOD_OS_D					20
#define WTRX_OPTOD_OS_E					21
#define WTRX_OPTOD_OM_A					22
#define WTRX_OPTOD_OM_B					23
#define WTRX_OPTOD_OM_C					24
#define WTRX_OPTOD_OM_D					25
#define WTRX_OPTOD_OM_E					26
#define WTRX_OPTOD_OP_A					27
#define WTRX_OPTOD_OP_B					28
#define WTRX_OPTOD_OP_C					29
#define WTRX_OPTOD_OP_D					30
#define WTRX_OPTOD_OP_E					31

// Eureka Manta
#define WTRX_MANTA_PH_F					32
#define WTRX_MANTA_ORP_F				33
#define WTRX_MANTA_DEPTH_F				34
#define WTRX_MANTA_COND_F				35
#define WTRX_MANTA_CHL_F				36
#define WTRX_MANTA_NH4_F				37
#define WTRX_MANTA_NO3_F				38
#define WTRX_MANTA_CL_F					39
#define WTRX_MANTA_HDO_F				40
#define WTRX_MANTA_TC_F					41		// manta continues on 237


// Industrial protocols (ModBus & CAN bus)
#define WTRX_MODBUS_COILS				42
#define WTRX_MODBUS_DISCRETE_INPUT		43
#define WTRX_MODBUS_HOLDING_REGS		44
#define WTRX_MODBUS_INPUT_REGS			45
#define WTRX_CANBUS_RPM					46
#define WTRX_CANBUS_VS					47
#define WTRX_CANBUS_FR					48
#define WTRX_CANBUS_FL					49
#define WTRX_CANBUS_TP					50
#define WTRX_CANBUS_FP					51

// Now some index are reserved for additional fieLds, already defined
#define WTRX_PHEHT_TC2_A				134
#define WTRX_PHEHT_TC2_B				135
#define WTRX_PHEHT_TC2_C				136
#define WTRX_PHEHT_TC2_D				137
#define WTRX_PHEHT_TC2_E				138
#define WTRX_PHEHT_PH_A					139
#define WTRX_PHEHT_PH_B					140
#define WTRX_PHEHT_PH_C					141
#define WTRX_PHEHT_PH_D					142
#define WTRX_PHEHT_PH_E					143
#define WTRX_PHEHT_RX_A					144
#define WTRX_PHEHT_RX_B					145
#define WTRX_PHEHT_RX_C					146
#define WTRX_PHEHT_RX_D					147
#define WTRX_PHEHT_RX_E					148
#define WTRX_PHEHT_PM_A					149
#define WTRX_PHEHT_PM_B					150
#define WTRX_PHEHT_PM_C					151
#define WTRX_PHEHT_PM_D					152
#define WTRX_PHEHT_PM_E					153
#define WTRX_C4E_TC3_A					154
#define WTRX_C4E_TC3_B					155
#define WTRX_C4E_TC3_C					156
#define WTRX_C4E_TC3_D					157
#define WTRX_C4E_TC3_E					158
#define WTRX_C4E_CN_A					159
#define WTRX_C4E_CN_B					160
#define WTRX_C4E_CN_C					161
#define WTRX_C4E_CN_D					162
#define WTRX_C4E_CN_E					163
#define WTRX_C4E_SA_A					164
#define WTRX_C4E_SA_B					165
#define WTRX_C4E_SA_C					166
#define WTRX_C4E_SA_D					167
#define WTRX_C4E_SA_E					168
#define WTRX_C4E_TD_A					169
#define WTRX_C4E_TD_B					170
#define WTRX_C4E_TD_C					171
#define WTRX_C4E_TD_D					172
#define WTRX_C4E_TD_E					173
#define WTRX_NTU_TC4_A					174
#define WTRX_NTU_TC4_B					175
#define WTRX_NTU_TC4_C					176
#define WTRX_NTU_TC4_D					177
#define WTRX_NTU_TC4_E					178
#define WTRX_NTU_TN_A					179
#define WTRX_NTU_TN_B					180
#define WTRX_NTU_TN_C					181
#define WTRX_NTU_TN_D					182
#define WTRX_NTU_TN_E					183
#define WTRX_NTU_TM_A					184
#define WTRX_NTU_TM_B					185
#define WTRX_NTU_TM_C					186
#define WTRX_NTU_TM_D					187
#define WTRX_NTU_TM_E					188
#define WTRX_CTZN_TC5_A					189
#define WTRX_CTZN_TC5_B					190
#define WTRX_CTZN_TC5_C					191
#define WTRX_CTZN_TC5_D					192
#define WTRX_CTZN_TC5_E					193
#define WTRX_CTZN_CN1_A					194
#define WTRX_CTZN_CN1_B					195
#define WTRX_CTZN_CN1_C					196
#define WTRX_CTZN_CN1_D					197
#define WTRX_CTZN_CN1_E					198
#define WTRX_CTZN_SA1_A					199
#define WTRX_CTZN_SA1_B					200
#define WTRX_CTZN_SA1_C					201
#define WTRX_CTZN_SA1_D					202
#define WTRX_CTZN_SA1_E					203
#define WTRX_CTZN_CU_A					204
#define WTRX_CTZN_CU_B					205
#define WTRX_CTZN_CU_C					206
#define WTRX_CTZN_CU_D					207
#define WTRX_CTZN_CU_E					208
#define WTRX_MES5_TC6_A					209
#define WTRX_MES5_TC6_B					210
#define WTRX_MES5_TC6_C					211
#define WTRX_MES5_TC6_D					212
#define WTRX_MES5_TC6_E					213
#define WTRX_MES5_SB_A					214
#define WTRX_MES5_SB_B					215
#define WTRX_MES5_SB_C					216
#define WTRX_MES5_SB_D					217
#define WTRX_MES5_SB_E					218
#define WTRX_MES5_SS_A					219
#define WTRX_MES5_SS_B					220
#define WTRX_MES5_SS_C					221
#define WTRX_MES5_SS_D					222
#define WTRX_MES5_SS_E					223
#define WTRX_MES5_TF_A					224
#define WTRX_MES5_TF_B					225
#define WTRX_MES5_TF_C					226
#define WTRX_MES5_TF_D					227
#define WTRX_MES5_TF_E					228
#define WTRX_C21_DIS_A					229
#define WTRX_C21_DIS_B					230
#define WTRX_C21_DIS_C					231
#define WTRX_C21_DIS_D					232
#define WTRX_C21_TC7_A					233
#define WTRX_C21_TC7_B					234
#define WTRX_C21_TC7_C					235
#define WTRX_C21_TC7_D					236

#define WTRX_MANTA_TURB_F					237
#define WTRX_MANTA_BGA_F					238
/// Flash defines //////////////////////////////////////////////////////////////


/*******************************************************************************
 * The following Flash strings define the tags for Water Xtreme sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 ******************************************************************************/

const char	wtr_xtr_00[] 	PROGMEM	= "TC_A";
const char 	wtr_xtr_01[] 	PROGMEM	= "TF_A";
const char	wtr_xtr_02[] 	PROGMEM	= "HUM_A";
const char 	wtr_xtr_03[] 	PROGMEM	= "PRES_A";
const char	wtr_xtr_04[] 	PROGMEM	= "TC_D";
const char 	wtr_xtr_05[] 	PROGMEM	= "TF_D";
const char	wtr_xtr_06[] 	PROGMEM	= "HUM_D";
const char 	wtr_xtr_07[] 	PROGMEM	= "PRES_D";
const char	wtr_xtr_08[] 	PROGMEM	= "LUX_A";
const char 	wtr_xtr_09[] 	PROGMEM	= "LUX_D";
const char	wtr_xtr_10[] 	PROGMEM	= "US_A";
const char	wtr_xtr_11[] 	PROGMEM	= "US_D";
const char 	wtr_xtr_12[] 	PROGMEM	= "TC1_A";
const char 	wtr_xtr_13[] 	PROGMEM	= "TC1_B";
const char 	wtr_xtr_14[] 	PROGMEM	= "TC1_C";
const char 	wtr_xtr_15[] 	PROGMEM	= "TC1_D";
const char 	wtr_xtr_16[] 	PROGMEM	= "TC1_E";
const char 	wtr_xtr_17[] 	PROGMEM	= "OS_A";
const char 	wtr_xtr_18[] 	PROGMEM	= "OS_B";
const char 	wtr_xtr_19[] 	PROGMEM	= "OS_C";
const char 	wtr_xtr_20[] 	PROGMEM	= "OS_D";
const char 	wtr_xtr_21[] 	PROGMEM	= "OS_E";
const char 	wtr_xtr_22[] 	PROGMEM	= "OM_A";
const char 	wtr_xtr_23[] 	PROGMEM	= "OM_B";
const char 	wtr_xtr_24[] 	PROGMEM	= "OM_C";
const char 	wtr_xtr_25[] 	PROGMEM	= "OM_D";
const char 	wtr_xtr_26[] 	PROGMEM	= "OM_E";
const char 	wtr_xtr_27[] 	PROGMEM	= "OP_A";
const char 	wtr_xtr_28[] 	PROGMEM	= "OP_B";
const char 	wtr_xtr_29[] 	PROGMEM	= "OP_C";
const char 	wtr_xtr_30[] 	PROGMEM	= "OP_D";
const char 	wtr_xtr_31[] 	PROGMEM	= "OP_E";
const char 	wtr_xtr_32[] 	PROGMEM	= "EM_PH";
const char 	wtr_xtr_33[] 	PROGMEM	= "EM_ORP";
const char 	wtr_xtr_34[] 	PROGMEM	= "EM_DEPTH";
const char 	wtr_xtr_35[] 	PROGMEM	= "EM_COND";
const char 	wtr_xtr_36[] 	PROGMEM	= "EM_CHL";
const char 	wtr_xtr_37[] 	PROGMEM	= "EM_NH4";
const char 	wtr_xtr_38[] 	PROGMEM	= "EM_NO3";
const char 	wtr_xtr_39[] 	PROGMEM	= "EM_CL";
const char 	wtr_xtr_40[] 	PROGMEM	= "EM_HDO";
const char 	wtr_xtr_41[] 	PROGMEM	= "EM_TC";


// Industrial protocols: Modbus & CAN bus
const char	wtr_xtr_42[]  PROGMEM = "MB_COILS";
const char	wtr_xtr_43[]  PROGMEM = "MB_DI";
const char	wtr_xtr_44[]  PROGMEM = "MB_HR";
const char	wtr_xtr_45[]  PROGMEM = "MB_IR";
const char	wtr_xtr_46[]  PROGMEM = "CB_RPM";
const char	wtr_xtr_47[]  PROGMEM = "CB_VS";
const char	wtr_xtr_48[]  PROGMEM = "CB_FR";
const char	wtr_xtr_49[]  PROGMEM = "CB_FL";
const char	wtr_xtr_50[]  PROGMEM = "CB_TP";
const char	wtr_xtr_51[]  PROGMEM = "CB_FP";


// Additional
const char	wtr_xtr_52[] 	PROGMEM	= "BAT";
const char	wtr_xtr_53[] 	PROGMEM	= "GPS";
const char	wtr_xtr_54[] 	PROGMEM	= "RSSI";
const char	wtr_xtr_55[] 	PROGMEM	= "MAC";
const char	wtr_xtr_56[] 	PROGMEM	= "NA";
const char	wtr_xtr_57[] 	PROGMEM	= "NID";
const char	wtr_xtr_58[] 	PROGMEM	= "DATE";
const char	wtr_xtr_59[] 	PROGMEM	= "TIME";
const char	wtr_xtr_60[] 	PROGMEM	= "GMT";
const char	wtr_xtr_61[] 	PROGMEM	= "RAM";
const char	wtr_xtr_62[] 	PROGMEM	= "IN_TEMP"; // (deprecated for Waspv15)
const char	wtr_xtr_63[]	PROGMEM = "ACC";
const char	wtr_xtr_64[]  	PROGMEM = "MILLIS";
const char	wtr_xtr_65[] 	PROGMEM = "STR";
const char	wtr_xtr_66[]  	PROGMEM = "";
const char	wtr_xtr_67[]	PROGMEM = "";
const char	wtr_xtr_68[]  	PROGMEM = "UID";
const char	wtr_xtr_69[]  	PROGMEM = "RB";
const char	wtr_xtr_70[]  	PROGMEM = "PM1";
const char	wtr_xtr_71[]  	PROGMEM = "PM2_5";
const char	wtr_xtr_72[]  	PROGMEM = "PM10";
const char	wtr_xtr_73[]  	PROGMEM = "PART";
const char	wtr_xtr_74[]  	PROGMEM = "TC";
const char	wtr_xtr_75[]  	PROGMEM = "TF";
const char	wtr_xtr_76[]  	PROGMEM = "HUM";
const char	wtr_xtr_77[]  	PROGMEM = "PRES";
const char	wtr_xtr_78[]  	PROGMEM = "LUX";
const char	wtr_xtr_79[]  	PROGMEM = "US";
const char	wtr_xtr_80[]  	PROGMEM = "";
const char	wtr_xtr_81[]  	PROGMEM = "";
const char	wtr_xtr_82[]  	PROGMEM = "";
const char	wtr_xtr_83[]  	PROGMEM = "";
const char	wtr_xtr_84[]  	PROGMEM = "";
const char	wtr_xtr_85[]  	PROGMEM = "";
const char	wtr_xtr_86[]  	PROGMEM = "";
const char	wtr_xtr_87[]  	PROGMEM = "";
const char	wtr_xtr_88[]  	PROGMEM = "";
const char	wtr_xtr_89[]  	PROGMEM = "SPEED_OG";
const char	wtr_xtr_90[]  	PROGMEM = "COURSE_OG";
const char	wtr_xtr_91[]  	PROGMEM = "ALT";
const char	wtr_xtr_92[]  	PROGMEM = "HDOP";
const char	wtr_xtr_93[]  	PROGMEM = "VDOP";
const char	wtr_xtr_94[]  	PROGMEM = "PDOP";
const char	wtr_xtr_95[]  	PROGMEM = "";
const char	wtr_xtr_96[]  	PROGMEM = "";
const char	wtr_xtr_97[]  	PROGMEM = "";
const char	wtr_xtr_98[]  	PROGMEM = "";
const char	wtr_xtr_99[]  	PROGMEM = "";
const char	wtr_xtr_100[]  	PROGMEM = "";
const char	wtr_xtr_101[]  	PROGMEM = "";
const char	wtr_xtr_102[]  	PROGMEM = "";
const char	wtr_xtr_103[]  	PROGMEM = "";
const char	wtr_xtr_104[]  	PROGMEM = "";
const char	wtr_xtr_105[]  	PROGMEM = "";
const char	wtr_xtr_106[]  	PROGMEM = "";
const char	wtr_xtr_107[]  	PROGMEM = "";
const char	wtr_xtr_108[]  	PROGMEM = "";
const char	wtr_xtr_109[]  	PROGMEM = "";
const char	wtr_xtr_110[]  	PROGMEM = "";
const char	wtr_xtr_111[]  	PROGMEM = "";
const char	wtr_xtr_112[]  	PROGMEM = "";
const char	wtr_xtr_113[]  	PROGMEM = "";
const char	wtr_xtr_114[]  	PROGMEM = "";
const char	wtr_xtr_115[]  	PROGMEM = "";
const char	wtr_xtr_116[]  	PROGMEM = "";
const char	wtr_xtr_117[]  	PROGMEM = "";
const char	wtr_xtr_118[]  	PROGMEM = "";
const char	wtr_xtr_119[]  	PROGMEM = "";
const char	wtr_xtr_120[]  	PROGMEM = "";
const char	wtr_xtr_121[]  	PROGMEM = "";
const char	wtr_xtr_122[]  	PROGMEM = "";
const char	wtr_xtr_123[]  	PROGMEM = "TST";
const char	wtr_xtr_124[]  	PROGMEM = "";
const char	wtr_xtr_125[]  	PROGMEM = "VAPI";
const char	wtr_xtr_126[]  	PROGMEM = "VPROG";
const char	wtr_xtr_127[]  	PROGMEM = "VBOOT";
const char	wtr_xtr_128[]  	PROGMEM = "PS";

const char	wtr_xtr_129[]  	PROGMEM = "";
const char	wtr_xtr_130[]  	PROGMEM = "";
const char	wtr_xtr_131[]  	PROGMEM = "";
const char	wtr_xtr_132[]  	PROGMEM = "";
const char	wtr_xtr_133[]  	PROGMEM = "";
const char	wtr_xtr_134[]  	PROGMEM = "TC2_A";
const char	wtr_xtr_135[]  	PROGMEM = "TC2_B";
const char	wtr_xtr_136[]  	PROGMEM = "TC2_C";
const char	wtr_xtr_137[]  	PROGMEM = "TC2_D";
const char	wtr_xtr_138[]  	PROGMEM = "TC2_E";
const char	wtr_xtr_139[]  	PROGMEM = "PH_A";
const char	wtr_xtr_140[]  	PROGMEM = "PH_B";
const char	wtr_xtr_141[]  	PROGMEM = "PH_C";
const char	wtr_xtr_142[]  	PROGMEM = "PH_D";
const char	wtr_xtr_143[]  	PROGMEM = "PH_E";
const char	wtr_xtr_144[]  	PROGMEM = "RX_A";
const char	wtr_xtr_145[]  	PROGMEM = "RX_B";
const char	wtr_xtr_146[]  	PROGMEM = "RX_C";
const char	wtr_xtr_147[]  	PROGMEM = "RX_D";
const char	wtr_xtr_148[]  	PROGMEM = "RX_E";
const char	wtr_xtr_149[]  	PROGMEM = "PM_A";
const char	wtr_xtr_150[]  	PROGMEM = "PM_B";
const char	wtr_xtr_151[]  	PROGMEM = "PM_C";
const char	wtr_xtr_152[]  	PROGMEM = "PM_D";
const char	wtr_xtr_153[]  	PROGMEM = "PM_E";
const char	wtr_xtr_154[]  	PROGMEM = "TC3_A";
const char	wtr_xtr_155[]  	PROGMEM = "TC3_B";
const char	wtr_xtr_156[]  	PROGMEM = "TC3_C";
const char	wtr_xtr_157[]  	PROGMEM = "TC3_D";
const char	wtr_xtr_158[]  	PROGMEM = "TC3_E";
const char	wtr_xtr_159[]  	PROGMEM = "CN_A";
const char	wtr_xtr_160[]  	PROGMEM = "CN_B";
const char	wtr_xtr_161[]  	PROGMEM = "CN_C";
const char	wtr_xtr_162[]  	PROGMEM = "CN_D";
const char	wtr_xtr_163[]  	PROGMEM = "CN_E";
const char	wtr_xtr_164[]  	PROGMEM = "SA_A";
const char	wtr_xtr_165[]  	PROGMEM = "SA_B";
const char	wtr_xtr_166[]  	PROGMEM = "SA_C";
const char	wtr_xtr_167[]  	PROGMEM = "SA_D";
const char	wtr_xtr_168[]  	PROGMEM = "SA_E";
const char	wtr_xtr_169[]  	PROGMEM = "TD_A";
const char	wtr_xtr_170[]  	PROGMEM = "TD_B";
const char	wtr_xtr_171[]  	PROGMEM = "TD_C";
const char	wtr_xtr_172[]  	PROGMEM = "TD_D";
const char	wtr_xtr_173[]  	PROGMEM = "TD_E";
const char	wtr_xtr_174[]  	PROGMEM = "TC4_A";
const char	wtr_xtr_175[]  	PROGMEM = "TC4_B";
const char	wtr_xtr_176[]  	PROGMEM = "TC4_C";
const char	wtr_xtr_177[]  	PROGMEM = "TC4_D";
const char	wtr_xtr_178[]  	PROGMEM = "TC4_E";
const char	wtr_xtr_179[]  	PROGMEM = "TN_A";
const char	wtr_xtr_180[]  	PROGMEM = "TN_B";
const char	wtr_xtr_181[]  	PROGMEM = "TN_C";
const char	wtr_xtr_182[]  	PROGMEM = "TN_D";
const char	wtr_xtr_183[]  	PROGMEM = "TN_E";
const char	wtr_xtr_184[]  	PROGMEM = "TM_A";
const char	wtr_xtr_185[]  	PROGMEM = "TM_B";
const char	wtr_xtr_186[]  	PROGMEM = "TM_C";
const char	wtr_xtr_187[]  	PROGMEM = "TM_D";
const char	wtr_xtr_188[]  	PROGMEM = "TM_E";
const char	wtr_xtr_189[]  	PROGMEM = "TC5_A";
const char	wtr_xtr_190[]  	PROGMEM = "TC5_B";
const char	wtr_xtr_191[]  	PROGMEM = "TC5_C";
const char	wtr_xtr_192[]  	PROGMEM = "TC5_D";
const char	wtr_xtr_193[]  	PROGMEM = "TC5_E";
const char	wtr_xtr_194[]  	PROGMEM = "CN1_A";
const char	wtr_xtr_195[]  	PROGMEM = "CN1_B";
const char	wtr_xtr_196[]  	PROGMEM = "CN1_C";
const char	wtr_xtr_197[]  	PROGMEM = "CN1_D";
const char	wtr_xtr_198[]  	PROGMEM = "CN1_E";
const char	wtr_xtr_199[]  	PROGMEM = "SA1_A";
const char	wtr_xtr_200[]  	PROGMEM = "SA1_B";
const char	wtr_xtr_201[]  	PROGMEM = "SA1_C";
const char	wtr_xtr_202[]  	PROGMEM = "SA1_D";
const char	wtr_xtr_203[]  	PROGMEM = "SA1_E";
const char	wtr_xtr_204[]  	PROGMEM = "CU_A";
const char	wtr_xtr_205[]  	PROGMEM = "CU_B";
const char	wtr_xtr_206[]  	PROGMEM = "CU_C";
const char	wtr_xtr_207[]  	PROGMEM = "CU_D";
const char	wtr_xtr_208[]  	PROGMEM = "CU_E";
const char	wtr_xtr_209[]  	PROGMEM = "TC6_A";
const char	wtr_xtr_210[]  	PROGMEM = "TC6_B";
const char	wtr_xtr_211[]  	PROGMEM = "TC6_C";
const char	wtr_xtr_212[]  	PROGMEM = "TC6_D";
const char	wtr_xtr_213[]  	PROGMEM = "TC6_E";
const char	wtr_xtr_214[]  	PROGMEM = "SB_A";
const char	wtr_xtr_215[]  	PROGMEM = "SB_B";
const char	wtr_xtr_216[]  	PROGMEM = "SB_C";
const char	wtr_xtr_217[]  	PROGMEM = "SB_D";
const char	wtr_xtr_218[]  	PROGMEM = "SB_E";
const char	wtr_xtr_219[]  	PROGMEM = "SS_A";
const char	wtr_xtr_220[]  	PROGMEM = "SS_B";
const char	wtr_xtr_221[]  	PROGMEM = "SS_C";
const char	wtr_xtr_222[]  	PROGMEM = "SS_D";
const char	wtr_xtr_223[]  	PROGMEM = "SS_E";
const char	wtr_xtr_224[]  	PROGMEM = "TFA_A";
const char	wtr_xtr_225[]  	PROGMEM = "TFA_B";
const char	wtr_xtr_226[]  	PROGMEM = "TFA_C";
const char	wtr_xtr_227[]  	PROGMEM = "TFA_D";
const char	wtr_xtr_228[]  	PROGMEM = "TFA_E";
const char	wtr_xtr_229[]  	PROGMEM = "DIS_A";
const char	wtr_xtr_230[]  	PROGMEM = "DIS_B";
const char	wtr_xtr_231[]  	PROGMEM = "DIS_C";
const char	wtr_xtr_232[]  	PROGMEM = "DIS_D";
const char	wtr_xtr_233[]  	PROGMEM = "TC7_A";
const char	wtr_xtr_234[]  	PROGMEM = "TC7_B";
const char	wtr_xtr_235[]  	PROGMEM = "TC7_C";
const char	wtr_xtr_236[]  	PROGMEM = "TC7_D";

const char	wtr_xtr_237[]  	PROGMEM = "EM_TURB";
const char	wtr_xtr_238[]  	PROGMEM = "EM_BGA";

/*******************************************************************************
 * SENSOR_TABLE - Sensor label table
 *
 * This table specifies the tag for each sensor. Every tag has been previously
 * defined in Flash memory
 ******************************************************************************/
const char* const WTR_XTR_TABLE[] PROGMEM=
{
	wtr_xtr_00,
	wtr_xtr_01,
	wtr_xtr_02,
	wtr_xtr_03,
	wtr_xtr_04,
	wtr_xtr_05,
	wtr_xtr_06,
	wtr_xtr_07,
	wtr_xtr_08,
	wtr_xtr_09,
	wtr_xtr_10,
	wtr_xtr_11,
 	wtr_xtr_12,
 	wtr_xtr_13,
 	wtr_xtr_14,
 	wtr_xtr_15,
 	wtr_xtr_16,
 	wtr_xtr_17,
 	wtr_xtr_18,
	wtr_xtr_19,
	wtr_xtr_20,
	wtr_xtr_21,
	wtr_xtr_22,
	wtr_xtr_23,
	wtr_xtr_24,
	wtr_xtr_25,
	wtr_xtr_26,
	wtr_xtr_27,
	wtr_xtr_28,
	wtr_xtr_29,
	wtr_xtr_30,
	wtr_xtr_31,
	wtr_xtr_32,
	wtr_xtr_33,
	wtr_xtr_34,
	wtr_xtr_35,
	wtr_xtr_36,
	wtr_xtr_37,
	wtr_xtr_38,
	wtr_xtr_39,
	wtr_xtr_40,
	wtr_xtr_41,
	wtr_xtr_42,
	wtr_xtr_43,
	wtr_xtr_44,
	wtr_xtr_45,
	wtr_xtr_46,
	wtr_xtr_47,
	wtr_xtr_48,
	wtr_xtr_49,
	wtr_xtr_50,
	wtr_xtr_51,
	wtr_xtr_52,
	wtr_xtr_53,
	wtr_xtr_54,
	wtr_xtr_55,
	wtr_xtr_56,
	wtr_xtr_57,
	wtr_xtr_58,
	wtr_xtr_59,
	wtr_xtr_60,
	wtr_xtr_61,
	wtr_xtr_62,
	wtr_xtr_63,
	wtr_xtr_64,
	wtr_xtr_65,
	wtr_xtr_66,
	wtr_xtr_67,
	wtr_xtr_68,
	wtr_xtr_69,
	wtr_xtr_70,
	wtr_xtr_71,
	wtr_xtr_72,
	wtr_xtr_73,
	wtr_xtr_74,
	wtr_xtr_75,
	wtr_xtr_76,
	wtr_xtr_77,
	wtr_xtr_78,
	wtr_xtr_79,
	wtr_xtr_80,
	wtr_xtr_81,
	wtr_xtr_82,
	wtr_xtr_83,
	wtr_xtr_84,
	wtr_xtr_85,
	wtr_xtr_86,
	wtr_xtr_87,
	wtr_xtr_88,
	wtr_xtr_89,
	wtr_xtr_90,
	wtr_xtr_91,
	wtr_xtr_92,
	wtr_xtr_93,
	wtr_xtr_94,
	wtr_xtr_95,
	wtr_xtr_96,
	wtr_xtr_97,
	wtr_xtr_98,
	wtr_xtr_99,
	wtr_xtr_100,
	wtr_xtr_101,
	wtr_xtr_102,
	wtr_xtr_103,
	wtr_xtr_104,
	wtr_xtr_105,
	wtr_xtr_106,
	wtr_xtr_107,
	wtr_xtr_108,
	wtr_xtr_109,
	wtr_xtr_110,
	wtr_xtr_111,
	wtr_xtr_112,
	wtr_xtr_113,
	wtr_xtr_114,
	wtr_xtr_115,
	wtr_xtr_116,
	wtr_xtr_117,
	wtr_xtr_118,
	wtr_xtr_119,
	wtr_xtr_120,
	wtr_xtr_121,
	wtr_xtr_122,
	wtr_xtr_123,
	wtr_xtr_124,
	wtr_xtr_125,
	wtr_xtr_126,
	wtr_xtr_127,
	wtr_xtr_128,
	wtr_xtr_129,
	wtr_xtr_130,
	wtr_xtr_131,
	wtr_xtr_132,
	wtr_xtr_133,
	wtr_xtr_134,
	wtr_xtr_135,
	wtr_xtr_136,
	wtr_xtr_137,
	wtr_xtr_138,
	wtr_xtr_139,
	wtr_xtr_140,
	wtr_xtr_141,
	wtr_xtr_142,
	wtr_xtr_143,
	wtr_xtr_144,
	wtr_xtr_145,
	wtr_xtr_146,
	wtr_xtr_147,
	wtr_xtr_148,
	wtr_xtr_149,
	wtr_xtr_150,
	wtr_xtr_151,
	wtr_xtr_152,
	wtr_xtr_153,
	wtr_xtr_154,
	wtr_xtr_155,
	wtr_xtr_156,
	wtr_xtr_157,
	wtr_xtr_158,
	wtr_xtr_159,
	wtr_xtr_160,
	wtr_xtr_161,
	wtr_xtr_162,
	wtr_xtr_163,
	wtr_xtr_164,
	wtr_xtr_165,
	wtr_xtr_166,
	wtr_xtr_167,
	wtr_xtr_168,
	wtr_xtr_169,
	wtr_xtr_170,
	wtr_xtr_171,
	wtr_xtr_172,
	wtr_xtr_173,
	wtr_xtr_174,
	wtr_xtr_175,
	wtr_xtr_176,
	wtr_xtr_177,
	wtr_xtr_178,
	wtr_xtr_179,
	wtr_xtr_180,
	wtr_xtr_181,
	wtr_xtr_182,
	wtr_xtr_183,
	wtr_xtr_184,
	wtr_xtr_185,
	wtr_xtr_186,
	wtr_xtr_187,
	wtr_xtr_188,
	wtr_xtr_189,
	wtr_xtr_190,
	wtr_xtr_191,
	wtr_xtr_192,
	wtr_xtr_193,
	wtr_xtr_194,
	wtr_xtr_195,
	wtr_xtr_196,
	wtr_xtr_197,
	wtr_xtr_198,
	wtr_xtr_199,
	wtr_xtr_200,
	wtr_xtr_201,
	wtr_xtr_202,
	wtr_xtr_203,
	wtr_xtr_204,
	wtr_xtr_205,
	wtr_xtr_206,
	wtr_xtr_207,
	wtr_xtr_208,
	wtr_xtr_209,
	wtr_xtr_210,
	wtr_xtr_211,
	wtr_xtr_212,
	wtr_xtr_213,
	wtr_xtr_214,
	wtr_xtr_215,
	wtr_xtr_216,
	wtr_xtr_217,
	wtr_xtr_218,
	wtr_xtr_219,
	wtr_xtr_220,
	wtr_xtr_221,
	wtr_xtr_222,
	wtr_xtr_223,
	wtr_xtr_224,
	wtr_xtr_225,
	wtr_xtr_226,
	wtr_xtr_227,
	wtr_xtr_228,
	wtr_xtr_229,
	wtr_xtr_230,
	wtr_xtr_231,
	wtr_xtr_232,
	wtr_xtr_233,
	wtr_xtr_234,
	wtr_xtr_235,
	wtr_xtr_236,
	wtr_xtr_237,
	wtr_xtr_238
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
const uint8_t WTR_XTR_TYPE_TABLE[] PROGMEM=
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

	//// Industrial protocols (ModBus & CAN bus)
	1,		// 42
	1,		// 43
	1,		// 44
	1,		// 45
	1,		// 46
	1,		// 47
	1,		// 48
	0,		// 49
	0,		// 50
	1,		// 51

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

	0,		// 95
	0,		// 96
	0,		// 97
	0,		// 98
	0,		// 99
	0,		// 100
	0,		// 101
	0,		// 102
	0,		// 103
	0,		// 104
	0,		// 105
	0,		// 106
	0,		// 107
	0,		// 108
	0,		// 109
	0,		// 110
	0,		// 111
	0,		// 112
	0,		// 113
	0,		// 114
	0,		// 115
	0,		// 116
	0,		// 117
	0,		// 118
	0,		// 119
	0,		// 120
	0,		// 121
	0,		// 122

	4,		// 123
	0,		// 124
	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128
	0,		// 129
	0,		// 130
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
	2,		// 210
	2,		// 211
	2,		// 212
	2,		// 213
	2,		// 214
	2,		// 215
	2,		// 216
	2,		// 217
	2,		// 218
	2,		// 219
	2,		// 220
	2,		// 221
	2,		// 222
	2,		// 223
	2,		// 224
	2,		// 225
	2,		// 226
	2,		// 227
	2,		// 228
	2,		// 229
	2,		// 230
	2,		// 231
	2,		// 232
	2,		// 233
	2,		// 234
	2,		// 235
	2,		// 236
	2,		// 237
	2			// 238
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
const uint8_t WTR_XTR_FIELD_TABLE[] PROGMEM=
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
	1			// 238
};



/*******************************************************************************
* DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
*
* This table specifies the number of decimals for each sensor for ASCII frames
******************************************************************************/
const uint8_t WTR_XTR_DECIMAL_TABLE[] PROGMEM =
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

	//// Industrial protocols (ModBus & CAN bus)
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
	0,		// 98
	0,		// 99
	0,		// 100
	0,		// 101
	0,		// 102
	0,		// 103
	0,		// 104
	0,		// 105
	0,		// 106
	0,		// 107
	0,		// 108
	0,		// 109
	0,		// 110
	0,		// 111
	0,		// 112
	0,		// 113
	0,		// 114
	0,		// 115
	0,		// 116
	0,		// 117
	0,		// 118
	0,		// 119
	0,		// 120
	0,		// 121
	0,		// 122
	0,		// 123
	0,		// 124

	0,		// 125
	0,		// 126
	0,		// 127
	0,		// 128
	0,		// 129
	0,		// 130
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
	2,		// 210
	2,		// 211
	2,		// 212
	2,		// 213
	2,		// 214
	2,		// 215
	2,		// 216
	2,		// 217
	2,		// 218
	2,		// 219
	2,		// 220
	2,		// 221
	2,		// 222
	2,		// 223
	2,		// 224
	2,		// 225
	2,		// 226
	2,		// 227
	2,		// 228
	3,		// 229
	3,		// 230
	3,		// 231
	3,		// 232
	1,		// 233
	1,		// 234
	1,		// 235
	2,		// 236
	2,		// 237
	2			// 238

};

#endif
