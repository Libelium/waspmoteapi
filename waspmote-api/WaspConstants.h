/*
    Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
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
  
    Version:		1.9
    Design:			David Gascón
    Implementation:	David Cuartielles, Alberto Bielsa, Yuri Carmona
*/
 
  


#ifndef __WASPCONSTANTS_H__
#define __WASPCONSTANTS_H__

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include	"pins_waspmote.h"

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def WASPMOTE_API_VERSION
    \brief Waspmote API version number
 */
#define WASPMOTE_API_VERSION 20
 
 
 

// internal peripherals flag (IPF) register
// it just re-arranges the PRR0 and PRR1 registers from the MCU:
// MSB	-	7	6	5	4	3	2	1	  0
// ----------------------------------------------------------------------------- 
// PRR0	-	PRTWI	PRTIM2 	PRTIM0	– 	PRTIM1	PRSPI	PRUSART0  PRADC
// PRR1	-	– 	– 	– 	– 	PRTIM3 	– 	–  	  PRUSART1

// IPRA register
// has the three MSB positions empty
#define IPADC 1
#define IPTWI 2
#define IPSPI 4
#define IPUSART0 8
#define IPUSART1 16

// IPRB register
// has the four MSB positions empty
#define IPTIM0 1
#define IPTIM1 2
#define IPTIM2 4
#define IPTIM3 8

// external peripherals flag (EPF) register and constants
// '1' marks should be present, '0' marks not installed
// the EPF should be hardcoded in EEPROM on manufacturing
// a function will then check through the flags if the peripheral is
// installed on a certain WASP device, there is room for others
// that could come on the possible add-on boards

// EPRA register
#define PGPS 1
#define PSD 2
#define PACC 4
#define PXBEE 8
#define PRTC 16
#define PUSB 32
#define PSID 64
#define PSLOW_CLK 128

// EPRB register - for GPRS and add-on boards
#define PGPRS 1


/***************************************************
 * ANALOG PINS
 ***************************************************/
#define	ANALOG0	0
#define	ANALOG1	1
#define	ANALOG2	2
#define	ANALOG3	3
#define	ANALOG4	4
#define	ANALOG5	5
#define	ANALOG6	6
#define	ANALOG7	7



/***************************************************
 * INTERRUPTION BITMAP: 'intFlag' and 'intConf'
 * 
 * Waspmote interrupt vector definitions for 'intFlag' and 
 * 'intConf' bit-map vectors. These are 16-bit interrupt 
 * vectors to contain the flags for the different HW/SW
 * interrupts '0' will denote not-active, '1' will denote 
 * active the HW interrupts and default callback functions
 * are stored inside WInterrupts.c
 *  __________________________________________________________
 * |        |      |     |     |     |      |     |     |     |    
 * | PIR_3G | XBEE | RAD | HIB | PLV | SENS | WTD | RTC | ACC |
 * |________|______|_____|_____|_____|______|_____|_____|_____|
 *      8      7      6     5     4      3     2     1     0
 *  
 ***************************************************/
/*! \def ACC_INT
    \brief Accelerometer interruption bit within intFlag and intConf
 */
/*! \def RTC_INT
    \brief RTC interruption bit within intFlag and intConf
 */
/*! \def WTD_INT
    \brief Watchdog interruption bit within intFlag and intConf
 */
/*! \def SENS_INT
    \brief Sensor Boards interruption bit within intFlag and intConf
 */
/*! \def PLV_INT
    \brief Pluviometer sensor interruption bit within intFlag and intConf
 */
/*! \def HIB_INT
    \brief Hibernate interruption bit within intFlag and intConf
 */
/*! \def RAD_INT
    \brief Radiation sensor interruption bit within intFlag and intConf
 */
/*! \def XBEE_INT
    \brief XBee module interruption bit within intFlag and intConf
 */
/*! \def PIR_3G_INT
    \brief PIR sensor (Video Camera board) interruption bit within intFlag and intConf
 */
#define ACC_INT   	1		// bit 0
#define RTC_INT   	2		// bit 1
#define WTD_INT   	4		// bit 2
#define SENS_INT	8		// bit 3
#define PLV_INT		16		// bit 4
#define HIB_INT		32		// bit 5
#define RAD_INT		64		// bit 6
#define XBEE_INT 	128		// bit 7
#define PIR_3G_INT	256		// bit 8


/*******************************************************************************
 * INTERRUPTION POSTITION BITMAP 
 * 
 * Waspmote definitions for 'intArray' bit-map interruption 
 * counter vector. This is a 16-Byte interrupt array to 
 * contain the number of interruption generated per each 
 * interruption source
 *  ____________________________________________________
 * |        |      |     |     |      |     |     |     |    
 * | PIR_3G | XBEE | RAD | PLV | SENS | WTD | RTC | ACC |
 * |________|______|_____|_____|______|_____|_____|_____|
 *      7       6     5     4      3     2     1     0
 *  
 ******************************************************************************/
 /*! \def ACC_POS
    \brief Accelerometer interruption counter index within 'intArray'
 */
 /*! \def RTC_POS
    \brief RTC interruption counter index within 'intArray'
 */
 /*! \def WTD_POS
    \brief Watchdog interruption counter index within 'intArray'
 */
 /*! \def SENS_POS
    \brief Sensor interruption counter index within 'intArray'
 */
 /*! \def PLV_POS
    \brief Pluviometer interruption counter index within 'intArray'
 */
 /*! \def RAD_POS
    \brief Radiation board interruption counter index within 'intArray'
 */
 /*! \def XBEE_POS
    \brief XBee module interruption counter index within 'intArray'
 */
 /*! \def PIR_3G_POS
    \brief PIR sensor interruption counter index within 'intArray'
 */
#define	ACC_POS		0
#define	RTC_POS		1
#define	WTD_POS		2
#define	SENS_POS	3
#define	PLV_POS		4
#define RAD_POS		5
#define XBEE_POS	6
#define PIR_3G_POS	7


/*******************************************************************************
 * INTERRUPTION PINS used to generate interruptions in Waspmote
 ******************************************************************************/
/*! \def RXD1_PIN
    \brief Interruption pin used for ACC, RTC, SENS and XBEE
    \remarks This pin is also the UART1's RX pin
 */
 /*! \def TXD1_PIN
    \brief Interruption pin used for BAT critical level
    \remarks This pin is also the UART1's TX pin
 */
 /*! \def INT4_PIN
    \brief Interruption pin used for Watchdog timer
 */
#define RXD1_PIN	2	// INT2 pin
#define TXD1_PIN	3	// INT3 pin
#define INT4_PIN	4	// INT4 pin
 

/*******************************************************************************
 * Interruption monitorization pins
 ******************************************************************************/
/*! \def ACC_INT_PIN_MON
    \brief Monitorization pin used for ACC interruptions
 */
 /*! \def BAT_INT_PIN_MON
    \brief Monitorization pin used for BAT interruptions
 */ 
 /*! \def RTC_INT_PIN_MON
    \brief Monitorization pin used for RTC interruptions
 */ 
 /*! \def WTD_INT_PIN_MON
    \brief Monitorization pin used for Watchdog interruptions
 */ 
 /*! \def XBEE_INT_PIN_MON
    \brief Monitorization pin used for XBee interruptions
 */ 
 /*! \def RAD_INT_PIN_MON
    \brief Monitorization pin used for Radiation sensor board interruptions
 */ 
 /*! \def PIR_3G_PIN_MON
    \brief Monitorization pin used for PIR sensor interruptions (in videocamera
    sensor board) 
 */ 
 /*! \def PLV_INT_PIN_MON
    \brief Monitorization pin used for Pluviometer sensor interruptions
 */ 
#define	ACC_INT_PIN_MON		RDY_ACC 	// PE6
#define	BAT_INT_PIN_MON		LOW_BAT_MON	// PG0
#define	RTC_INT_PIN_MON		RST_RTC		// PE7
#define	WTD_INT_PIN_MON		DIGITAL0	// PE4
#define XBEE_INT_PIN_MON	XBEE_MON	// PA7
#define RAD_INT_PIN_MON   	DIGITAL7	// PC4
#define PIR_3G_PIN_MON    	ANA4		// PF5 (ANALOG5)
#define	PLV_INT_PIN_MON		DIGITAL4
#define	UART1_INT_PIN_MON	GPRS_PIN 	// PC2

// Event Sensor Board
#define	SENS_INT_PIN_MON 	DIGITAL2  	// PA2
#define	SENS_INT_CLK_REG	DIGITAL7	// PC4
#define	SENS_INT_DO			DIGITAL1	// PE3
#define	SENS_INT_ENABLE		DIGITAL8	// PC5
#define	SENS_INT_CLK_INH	DIGITAL3	// PA4


// Smart Cities Sensor Board
#define	SENS_INT_CITIES_PIN_MON 	DIGITAL2	// PA2
#define	SENS_INT_CITIES_CLK_REG		DIGITAL7	// PC4
#define	SENS_INT_CITIES_DO			DIGITAL3	// PA4
#define	SENS_INT_CITIES_ENABLE		DIGITAL5	// PC7
#define	SENS_INT_CITIES_CLK_INH		DIGITAL8	// PC5



/*******************************************************************************
 * WASPMOTE CONTROL REGISTER FOR POWER SUPPLIES AND MODULES 
   _________________________________________________
  |     |     |     |     |     |     |     |       |   
  |     |     |     |     |     |     |     |  SD   | 
  |_____|_____|_____|_____|_____|_____|_____|_______|
    23     22   21    20    19    18    17     16
   _______________________________________________________________________
  |     |       |       |         |       |     |            |            |
  | OTA | Water | Video | Parking | Proto | Rad | Cities v15 | Cities v14 |
  |_____|_______|_______|_________|_______|_____|____________|____________|
    15     14      13        12      11     10         9            8
   ________________________________________________________________________
  |        |       |             |          |         |         |     |    |
  | Events | Gases | Agriculture | Metering | Socket1 | Socket0 | 3V3 | 5V |
  |________|_______|_____________|__________|_________|_________|_____|____|
      7        6          5            4         3         2       1     0  

 ******************************************************************************/

/*! \def REG_5V
    \brief Bit dedicated to the 5V power supply
 */
/*! \def REG_3V3
    \brief Bit dedicated to the 3V3 power supply
 */
/*! \def REG_SOCKET0
    \brief Bit dedicated to the SOCKET0 power supply
 */
/*! \def REG_SOCKET1
    \brief Bit dedicated to the SOCKET1 power supply
 */
/*! \def REG_METERING
    \brief Bit dedicated to the presence of the Smart Metering Board
 */
/*! \def REG_AGRICULTURE
    \brief Bit dedicated to the presence of the Agriculture Board
 */
/*! \def REG_GASES
    \brief Bit dedicated to the presence of the Gases Board
 */
/*! \def REG_CITIES_V14
    \brief Bit dedicated to the presence of the Smart Cities Board v1.4
 */
/*! \def REG_CITIES_V15
    \brief Bit dedicated to the presence of the Smart Cities Board v1.5
 */
/*! \def REG_RADIATION
    \brief Bit dedicated to the presence of the Radiation Board
 */
/*! \def REG_PROTOTYPING
    \brief Bit dedicated to the presence of the Prototyping Board
 */
/*! \def REG_PARKING
    \brief Bit dedicated to the presence of the Parking Board
 */
/*! \def REG_VIDEO_CAMERA
    \brief Bit dedicated to the presence of the Video Camera Board
 */
/*! \def REG_WATER
    \brief Bit dedicated to the presence of the Smart Water Board
 */
/*! \def REG_OTA
    \brief Bit dedicated to the marking of the OTA process
 */
/*! \def REG_SD
    \brief Bit dedicated to the marking of the SD module 
 */
/*! \def REG_SX
    \brief Bit dedicated to the marking of the Semtech module 
 */
/*! \def REG_DUST_GASES_PRO
    \brief Bit dedicated to the marking of the Dust sensor in Gases PRO Board
 */
#define	REG_5V				1		// bit 0
#define	REG_3V3				2 		// bit 1
#define	REG_SOCKET0			4 		// bit 2
#define	REG_SOCKET1			8 		// bit 3
#define	REG_METERING		16 		// bit 4
#define	REG_AGRICULTURE		32 		// bit 5
#define	REG_GASES			64 		// bit 6
#define	REG_EVENTS			128		// bit 7
#define	REG_CITIES_V14		256		// bit 8	
#define	REG_CITIES_V15		512		// bit 9
#define	REG_RADIATION		1024	// bit 10
#define	REG_PROTOTYPING		2048	// bit 11
#define	REG_PARKING			4096	// bit 12
#define	REG_VIDEO_CAMERA	8192	// bit 13
#define	REG_WATER			16384	// bit 14
#define	REG_OTA				32768	// bit 15
#define	REG_SD				65536	// bit 16
#define	REG_SX				131072	// bit 17
#define	REG_DUST_GASES_PRO	262144	// bit 18
#define	REG_WATER_IONS		524288	// bit 19
#define REG_RS485			1048576	// bit 20


/*******************************************************************************
 * SOCKETS
 ******************************************************************************/

/*! \def SOCKET0
    \brief socket where UART0 is used
*/
/*! \def SOCKET1
    \brief socket where UART1 is used   
 */
#define SOCKET0	0  
#define SOCKET1	1


/*! \def XBEE_ON
    \brief XBee Power Mode. OFF in this case    
 */
/*! \def XBEE_HIBERNATE
    \brief XBee Power Mode. HIBERNATE in this case    
 */
/*! \def XBEE_OFF
    \brief XBee Power Mode. OFF in this case    
 */
#define	XBEE_ON			1
#define	XBEE_HIBERNATE	2
#define	XBEE_OFF		3


/*! \def XBEE_RATE
    \brief XBee Baud Rate    
 */
#define XBEE_RATE	115200


/*! \def SENS_ON
    \brief Sensor Board Power Modes. ON in this case    
 */
/*! \def SENS_OFF
    \brief Sensor Board Power Modes. OFF in this case    
 */
#define	SENS_ON		0
#define	SENS_OFF	1


/*! \def SENS_3V3
    \brief Sensor Board Types. 3V3 switch in this case    
 */
/*! \def SENS_5V
    \brief Sensor Board Types. 5V switch in this case    
 */
#define	SENS_3V3	0
#define	SENS_5V		1


/*! \def boolean
    \brief boolean is defined as a uint8_t  
 */
/*! \def byte
    \brief byte is defined as a uint8_t
 */
#define boolean	uint8_t
#define byte	uint8_t


/*! \def ENABLED
    \brief Constant to define a enabled state  
 */
/*! \def DISABLED
    \brief Constant to define a disabled state    
 */
#define	DISABLED	0
#define	ENABLED		1


// Used EEPROM addresses 
/*! \def AUTHKEY_ADDR
    \brief Authentication key EEPROM address
 */
/*! \def MOTEID_ADDR
    \brief MOTEID EEPROM address
 */
/*! \def SEQUENCE_ADDR
    \brief Sequence EEPROM address
 */
#define MOTEID_ADDR		147
#define SEQUENCE_ADDR	163
#define AUTHKEY_ADDR	107

#endif
