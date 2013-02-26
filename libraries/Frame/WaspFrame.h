/*! \file WaspFrame.h
    \brief Library for creating formated frames
    
    Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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


/// Smart meetering sensor measurements

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
#define ASCII 		1
#define BINARY		0


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
    uint8_t _maxSize;
    
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
    void createFrame(void);   
  
    //! Function : creates a new frame
    /*! This function creates a new frame.
	\param uint8_t mode specifies the frame mode: BINARY or ASCII
	\return const char* moteID defines the mote Identifier
     */
    void createFrame(uint8_t mode, const char* moteID);
    
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
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3);
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3, int val4);
    int8_t addSensor(uint8_t type, int val1,int val2,int val3);
    int8_t addSensor(uint8_t type, double val1,double val2,double val3);

    int8_t checkFields(uint8_t type, uint8_t typeVal, uint8_t fields);

    void setID(char* moteID);
    void getID(char* moteID);
    
    // Sends Waspmote unique ID with the frame
    void setCloudCompatibility(void);
    
    //! Variable : buffer where the frame is created in
    /*!
     */ 
    uint8_t buffer[MAX_FRAME+1];
    
    //! Variable : length of the frame
    /*!
     */ 
    uint16_t length;
    
};

extern WaspFrame frame;

#endif

