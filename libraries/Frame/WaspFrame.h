/*! \file WaspFrame.h
    \brief Library for creating formated frames
    
    Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.9
    Design:			David Gascón
    Implementation:	Yuri Carmona, Javier Siscart, Joaquín Ruiz

*/
  
 
/*! \def WaspFrame_h        
 */
#ifndef WaspFrame_h
#define WaspFrame_h



/******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <WConstants.h>
#include "../WaspAES/WaspAES.h"


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/



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

 
// Gases
#define SENSOR_CO	 	0
#define SENSOR_CO2 		1
#define SENSOR_O2		2
#define SENSOR_CH4		3
#define SENSOR_LPG		4
#define SENSOR_NH3		5
#define SENSOR_AP1		6
#define SENSOR_AP2		7
#define SENSOR_SV		8
#define SENSOR_NO2		9
#define SENSOR_O3		10
#define SENSOR_VOC		11
#define SENSOR_TCA		12
#define SENSOR_TFA		13
#define SENSOR_HUMA		14
#define SENSOR_PA		15

// Events
#define SENSOR_PW  		16
#define SENSOR_BEND 	17
#define SENSOR_VBR  	18
#define SENSOR_HALL 	19
#define SENSOR_LP  		20
#define SENSOR_LL  		21
#define SENSOR_LUM  	22
#define SENSOR_PIR  	23
#define SENSOR_ST  		24

// Smart Cities	
#define SENSOR_MCP  	25
#define SENSOR_CDG  	26
#define SENSOR_CPG  	27
#define SENSOR_LD  		28
#define SENSOR_DUST		29
#define SENSOR_US  		30	

// Smart parking
#define SENSOR_MF		31
#define SENSOR_PS		32

// Agriculture
#define SENSOR_TCB		33
#define SENSOR_TFB		34
#define SENSOR_HUMB		35
#define SENSOR_SOILT 	36
#define SENSOR_SOIL 	37
#define SENSOR_LW  		38
#define SENSOR_PAR  	39
#define SENSOR_UV  		40
#define SENSOR_TD  		41	
#define SENSOR_SD  		42
#define SENSOR_FD  		43
#define SENSOR_ANE  	44
#define SENSOR_WV  		45
#define SENSOR_PLV  	46

// Radiation	
#define SENSOR_RAD  	47

// Smart meetering
#define SENSOR_CU  		48
#define SENSOR_WF  		49
#define SENSOR_LC  		50
#define SENSOR_DF  		51

// Additional
#define SENSOR_BAT  	52
#define SENSOR_GPS  	53
#define SENSOR_RSSI  	54
#define SENSOR_MAC  	55
#define SENSOR_NA  		56
#define SENSOR_NID  	57
#define SENSOR_DATE 	58
#define SENSOR_TIME 	59
#define SENSOR_GMT  	60
#define SENSOR_RAM		61
#define SENSOR_IN_TEMP	62
#define SENSOR_ACC		63
#define SENSOR_MILLIS	64

// Special
#define SENSOR_STR	 	65

// Meshlium
#define SENSOR_MBT	 	66
#define SENSOR_MWIFI 	67

// RFID
#define SENSOR_UID		68
#define SENSOR_RB	 	69

// Smart Water
#define SENSOR_PH		70
#define SENSOR_ORP	 	71
#define SENSOR_DO	 	72
#define SENSOR_COND	 	73
#define SENSOR_WT	 	74
#define SENSOR_DINA	 	75
#define SENSOR_DICA	 	76
#define SENSOR_DIF	 	77
#define SENSOR_DICL	 	78
#define SENSOR_DIBR	 	79
#define SENSOR_DII	 	80
#define SENSOR_DICU2	81
#define SENSOR_DIK	 	82
#define SENSOR_DIMG2	83
#define SENSOR_DINO3	84

// Smart Libelium
#define SENSOR_TX_PWR	85
#define SENSOR_DM_ST	86
#define SENSOR_DM_SP	87
#define SENSOR_LUX		88

// GPS
#define SENSOR_SPEED	89
#define SENSOR_COURSE	90
#define SENSOR_ALTITUDE	91
#define SENSOR_HDOP		92
#define SENSOR_VDOP		93
#define SENSOR_PDOP		94

// Finite State Machine status
#define SENSOR_FSM		95

// New pluviometer values
#define SENSOR_PLV1  	96
#define SENSOR_PLV2  	97
#define SENSOR_PLV3  	98

// P&S watermark sensors (Smart Agriculture)
#define SENSOR_SOIL_C  	99
#define SENSOR_SOIL_D  	100
#define SENSOR_SOIL_E  	101
#define SENSOR_SOIL_F  	102

// Waspmote OEM watermark sensors
#define SENSOR_SOIL1  	103
#define SENSOR_SOIL2  	104
#define SENSOR_SOIL3  	105

// DS18B20
#define SENSOR_TCC  	106

// P&S Ultrasound depending on socket voltage ref (Smart Cities & Smart Metering)
#define SENSOR_US_3V3  	107
#define SENSOR_US_5V  	108

// P&S Security sensors depending on socket (Smart Security)
#define SENSOR_LUM_D	109
#define SENSOR_LUM_E	110
#define SENSOR_LUM_F	111
#define SENSOR_LP_D		112
#define SENSOR_LP_E		113
#define SENSOR_LP_F		114
#define SENSOR_LL_D		115
#define SENSOR_LL_E		116
#define SENSOR_LL_F		117
#define SENSOR_HALL_D	118
#define SENSOR_HALL_E	119
#define SENSOR_HALL_F	120

// P&S liquid flow sensor depending on socket (Smart Metering)
#define SENSOR_WF_C		121
#define SENSOR_WF_E		122
	
// Unix/Epoch timestamp
#define SENSOR_TST		123
	
// Turbidity sensor
#define SENSOR_TURB		124

// Version parameters
#define SENSOR_VAPI		125
#define SENSOR_VPROG	126
#define SENSOR_VBOOT	127


// Gases PRO
#define SENSOR_GP_CL2	128
#define SENSOR_GP_CO	129
#define SENSOR_GP_ETO	130
#define SENSOR_GP_H2	131
#define SENSOR_GP_H2S	132
#define SENSOR_GP_HCL	133
#define SENSOR_GP_HCN	134
#define SENSOR_GP_NH3	135
#define SENSOR_GP_NO	136
#define SENSOR_GP_NO2	137
#define SENSOR_GP_O2	138
#define SENSOR_GP_PH3	139
#define SENSOR_GP_SO2	140
#define SENSOR_GP_CH4	141
#define SENSOR_GP_O3	142
#define SENSOR_GP_CO2	143
#define SENSOR_GP_TC	144
#define SENSOR_GP_TF	145
#define SENSOR_GP_HUM	146
#define SENSOR_GP_PRES	147

// OPCN2 Dust Sensor
#define SENSOR_OPC_TC		148
#define SENSOR_OPC_TF		149
#define SENSOR_OPC_P		150
#define SENSOR_OPC_PM1		151
#define SENSOR_OPC_PM2_5	152
#define SENSOR_OPC_PM10		153
#define SENSOR_OPC_PART		154

// Smart Water Ions
#define SENSOR_SWI_CA	155
#define SENSOR_SWI_FL	156
#define SENSOR_SWI_FB	157
#define SENSOR_SWI_NO	158
#define SENSOR_SWI_BR	159
#define SENSOR_SWI_CL	160
#define SENSOR_SWI_CU	161
#define SENSOR_SWI_IO	162
#define SENSOR_SWI_PB	163
#define SENSOR_SWI_AG	164
#define SENSOR_SWI_PH	165

// P&S Smart Water sensors depending on socket (Smart Water)
#define SENSOR_PH_A		166
#define SENSOR_PH_B		167
#define SENSOR_PH_C		168
#define SENSOR_ORP_A	169
#define SENSOR_ORP_B	170
#define SENSOR_ORP_C	171

// define MACROS in order to manage bits inside Bytes
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


/*! \def MAX_FRAME
    \brief maximum size in bytes of the frame 
 */
#define MAX_FRAME 150



/*! \def UNICAST_16B
    \brief 
 */
/*! \def UNICAST_64B
    \brief 
 */
/*! \def BROADCAST_MODE
    \brief 
 */
#define UNICAST_16B 	0
#define UNICAST_64B 	1
#define BROADCAST_MODE 	2



/*! \def EXAMPLE_FRAME
    \brief 
 */
/*! \def TIMEOUT_FRAME
    \brief 
 */
/*! \def EVENT_FRAME
    \brief 
 */
/*! \def ALARM_FRAME
    \brief 
 */
/*! \def SERVICE1_FRAME
    \brief 
 */
/*! \def SERVICE2_FRAME
    \brief 
 */
#define EXAMPLE_FRAME 	0
#define TIMEOUT_FRAME 	1
#define EVENT_FRAME 	2
#define ALARM_FRAME 	3
#define SERVICE1_FRAME 	4
#define SERVICE2_FRAME 	5
#define SET_TIME_FRAME 	6

/*! \def AES128_ECB_FRAME
    \brief Encrypted frame using AES-128 key size and ECB mode
 */
/*! \def AES192_ECB_FRAME
    \brief Encrypted frame using AES-192 key size and ECB mode
 */
/*! \def AES256_ECB_FRAME
    \brief Encrypted frame using AES-256 key size and ECB mode
 */
#define AES128_ECB_FRAME	97
#define AES192_ECB_FRAME	98
#define AES256_ECB_FRAME	99



/*! \def TYPE_UINT8
    \brief TYPE_UINT8 defines the constant for uint8_t variables types (1 Byte)
 */
/*! \def TYPE_INT
    \brief TYPE_INT defines the constant for int (int16_t) variables types (2 Bytes)
 */
/*! \def TYPE_FLOAT
    \brief TYPE_FLOAT defines the constant for double/float variables types (4 Bytes)
 */
/*! \def TYPE_CHAR
    \brief TYPE_CHAR defines the constant for char* (strings) variables types (variable Bytes)
 */
/*! \def TYPE_ULONG
    \brief TYPE_ULONG defines the constant for unsigned long int variables types (4 Bytes)
 */
#define TYPE_UINT8 		0
#define TYPE_INT 		1
#define TYPE_FLOAT 		2
#define TYPE_CHAR 		3
#define TYPE_ULONG 	 	4



/*! \def ASCII
    \brief ASCII frame mode
 */
/*! \def BINARY
    \brief BINARY frame mode
 */
#define BINARY		0
#define ASCII 		1
#define ENCRYPTED_FRAME	2


//! Variable :  Waspmote serial id
/*!
*/ 
extern volatile unsigned long _serial_id;


/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspFrame Class
/*!
	WaspFrame Class defines all the variables and functions used to create the
	sensor frames in Waspmote
 */
class WaspFrame
{
 
private:  

    //! Function : store the sequence number in EEPROM
    /*! This function stores the sequence number in the EEPROM address specified 
     * by the SEQUENCE_ADDR address.
     */ 
    void storeSequence(uint8_t seqNumber);
    
    //! Function : read the sequence number from EEPROM
    /*! This function reads the sequence number from the EEPROM address specified 
     * by the SEQUENCE_ADDR address.
     */ 
    uint8_t readSequence(void);
    
    //! Function : check if maximum length is reached
    /*! Check if maximum length is reached when introducing a new frame field
     */ 
    uint8_t checkLength(int sum);

    //! Variable : sequence number
    /*!
	This is the frame sequence number in order to control if any packet is lost
     */ 
    uint8_t sequence;
    
    //! Variable : number of sensor values within the frame
    /*!
     */ 
    uint8_t numFields;     
    
    //! Variable : frame format: ASCII (0) or BINARY (1)
    /*!
     */ 
    uint8_t _mode;   
    
    //! Variable : maximum frame size 
    /*!
     */ 
    uint16_t _maxSize;
    
    //! Variable : buffer for Waspmote ID. 16B maximum
    /*!
     */ 
    char _waspmoteID[17];	
    
public:

    //! class constructor
    /*!
	Initialize the class attributes
	\param void
	\return void
    */ 
    WaspFrame();      
    
    //! Function : set the frame maximum size
    /*! This function sets the frame maximum size 
	\param uint8_t size size to set as maximum size. It can't exceed the 
		MAX_FRAME constant
	\return void
     */ 
	void setFrameSize(	uint8_t size);   
    
    //! Function : set the frame maximum size
    /*! This function sets the frame maximum size depending on the protocol, 
    addressing, linkEncryption mode, AESEncryption.
	\param uint8_t protocol defines the procotol used
	\param uint8_t linkEncryption defines if XBee encryption is enabled or not
	\param uint8_t AESEncryption defines if AES encryption is used or not
	\return void
     */ 
	void setFrameSize(	uint8_t protocol,
						uint8_t linkEncryption, 
						uint8_t AESEncryption);    
    
    //! Function : set the frame maximum size
    /*! This function sets the frame maximum size depending on the protocol, 
    addressing, linkEncryption mode, AESEncryption.
	\param uint8_t protocol defines the procotol used
	\param uint8_t addressing defines the addressing used
	\param uint8_t linkEncryption defines if XBee encryption is enabled or not
	\param uint8_t AESEncryption defines if AES encryption is used or not
	\return void
     */ 
	void setFrameSize(	uint8_t protocol,
						uint8_t addressing, 
						uint8_t linkEncryption, 
						uint8_t AESEncryption); 
    
    //! Function : get the frame maximum size
    /*! This function gets the frame maximum size 
	\return uint8_t indicating the value of _maxSize
     */ 
	uint8_t getFrameSize( void );
  
    //! Function : creates a new frame
    /*! This function creates a new ASCII frame getting the mote ID from the 
     * EEPROM memory.
     */ 
    void createFrame(uint8_t mode);   
  
    //! Function : creates a new frame
    /*! This function creates a new frame.
	\param uint8_t mode specifies the frame mode: BINARY or ASCII
	\return char* moteID defines the mote Identifier
     */
    void createFrame(uint8_t mode, char* moteID);
    
    //! Function : creates a encrypted frame
    /*! This function creates a new frame, encrypting the actual contents of the
     * Waspmote Frame with the AES-key specified as input. The encrypted message 
     * becomes the payload of the new encapsultad frame
	\param uint16_t AESmode: specifies the AES key mode: 128, 192 or 256
	\param char* password: specifies the AES key as a string
	\return '1' if OK; '0' otherwise
	 */
    uint8_t encryptFrame( uint16_t AESmode, char* password );
    
    
	//! Function : set the frame type
    /*! This function sets the frame type (fourth byte of the frame header)
	\param uint8_t type specifies the frame type:
		EXAMPLE_FRAME
		TIMEOUT_FRAME 	
		EVENT_FRAME 	
		ALARM_FRAME 	
		SERVICE1_FRAME 
		SERVICE2_FRAME 
	\return void
     */ 
	void setFrameType(uint8_t type);	
      
    //! Function : shows the frame
    /*! This function prints the actual frame
     */
    void showFrame(void);
    
    int8_t addSensor(uint8_t type, int value);
    int8_t addSensor(uint8_t type, unsigned long value);
    int8_t addSensor(uint8_t type, double value);
    int8_t addSensor(uint8_t type, double value, int N);
    int8_t addSensor(uint8_t type, char* str);

    int8_t addSensor(uint8_t type, double val1, double val2);
    int8_t addSensor(uint8_t type, unsigned long val1, unsigned long val2);
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3);
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3, int val4);
    int8_t addSensor(uint8_t type, int val1,int val2,int val3);
    int8_t addSensor(uint8_t type, double val1,double val2,double val3);

    int8_t checkFields(uint8_t type, uint8_t typeVal, uint8_t fields);

    void setID(char* moteID);
    void getID(char* moteID);
    
    void decrementSequence(void);
        
    //! Variable : buffer where the frame is created in
    /*!
     */ 
    uint8_t buffer[MAX_FRAME+1];
    
    //! Variable : length of the frame
    /*!
     */ 
    uint16_t length;
    
    int8_t addTimestamp(void);
};

extern WaspFrame frame;

#endif

