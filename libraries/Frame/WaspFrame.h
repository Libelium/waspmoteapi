/*! \file WaspFrame.h
    \brief Library for creating formated frames

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

    Version:		3.8
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
#include "WaspFrameConstantsv12.h"
#include "WaspFrameConstantsv15.h"
#include "AgrXtrFrameConstants.h"
#include "WtrXtrFrameConstants.h"

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

//! DEBUG_FRAME
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_FRAME 	0

// define print message
#define PRINT_FRAME(str)	USB.print(F("[FRAME] ")); USB.print(str);


/*! \def MAX_FRAME
    \brief maximum size in bytes of the frame
 */
#define MAX_FRAME 255



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



//Define Frame Types
#define INFORMATION_FRAME_V12 	     0
#define TIMEOUT_FRAME 			     1
#define EVENT_FRAME 			     2
#define ALARM_FRAME 			     3
#define SERVICE1_FRAME 			     4
#define SERVICE2_FRAME 			     5
#define INFORMATION_FRAME_V15	     6
#define INFORMATION_FRAME_AGR_XTR    7
#define INFORMATION_FRAME_WTR_XTR    8

// Define frame types for encrypted frames in different formats
#define AES_ECB_FRAME_V15			96
#define AES128_ECB_FRAME_V12		97
#define AES192_ECB_FRAME_V12		98
#define AES256_ECB_FRAME_V12		99
#define AES_ECB_END_TO_END_V15		100
#define AES_ECB_END_TO_END_V12		101
#define AES_LIBELIUM_CLOUD_SW_FRAME	102
#define AES_LIBELIUM_CLOUD_HW_FRAME	103

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
extern volatile uint8_t _serial_id[8];

const uint8_t max_fields = 30;


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

    //! Variable : frame format: ASCII (0) or BINARY (1)
    uint8_t _mode;

    //! Variable : maximum frame size
    uint16_t _maxSize;

    //! Variable : buffer for Waspmote ID. 16B maximum
    char _waspmoteID[17];

    //! Variable: encryption flag for End-to-End encryption from device to Cloud
    uint8_t _encryptionToCloud;

    //! Variable: Stores frame type
    uint8_t _frameType;

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
	void setFrameSize(uint16_t size);


	uint16_t getMaxSizeForXBee(	uint8_t protocol,
								uint8_t linkEncryption,
								uint8_t AESEncryption);

	uint16_t getMaxSizeForXBee(	uint8_t protocol,
								uint8_t addressing,
								uint8_t linkEncryption,
								uint8_t AESEncryption);

	uint16_t getMaxSizeForXBee(	uint8_t protocol,
								uint8_t addressing,
								uint8_t linkEncryption,
								uint8_t AESEncryption,
								uint8_t HwEncryption);

  uint16_t getMaxSizeFor4G(uint16_t maximumSize,
                uint8_t AESEncryption,
                uint8_t HwEncryption);


	//! Function : calculates the frame maximum size for WiFi PRO module
    /*! This function sets the frame maximum size depending on the protocol,
    host, port, aes_encryption.
	\param char* protocol: "http" or "https"
	\param char* host: IP or DNS
	\param char* port: remote port (default 80 for HTTP)
	\param uint8_t aes_encryption: defines if AES encryption is used or not
	\return maximum size
     */
	uint16_t getMaxSizeForWifi(	char* protocol,
								char* host,
								char* port,
								uint8_t aes_encryption);

	//! Function : calculates the frame maximum size for WiFi PRO module
    /*! This function sets the frame maximum size depending on the protocol,
    host, port, path, aes_encryption.
	\param char* protocol: "http" or "https"
	\param char* host: IP or DNS
	\param char* port: remote port (default 80 for HTTP)
	\param char* path: path of the http server
	\param uint8_t aes_encryption: defines if AES encryption is used or not
	\return maximum size
     */
	uint16_t getMaxSizeForWifi(	char* protocol,
								char* host,
								char* port,
								char* path,
								uint8_t aes_encryption);

    //! Function : get the frame maximum size
    /*! This function gets the frame maximum size
	\return uint8_t indicating the value of _maxSize
     */
	uint16_t getFrameSize( void );

    void createFrame(uint8_t mode);
    void createFrame(uint8_t mode, char* moteID);

    uint8_t encryptFrame(uint16_t keySize, char* password);
    uint8_t encryptFrameHw(uint8_t keyIndex);

    //! Function : creates a encrypted frame from a fragment
    /*! This function creates a new frame, encrypting the current contents of the
     * fragment stored in the library structs with the AES-key specified as input.
     * The encrypted message becomes the payload of the new encapsultad frame
	\param uint16_t keySize: specifies the AES key mode: AES_128, AES_192 or AES_256
	\param char* password: specifies the AES key as a string (16, 24 or 32 chars)
	\return '0' if OK; '1' otherwise
	 */
    uint8_t encryptFragment(uint16_t keySize, char* password);
    uint8_t encryptFragmentHw(uint8_t keyIndex);

    void encryptionToCloud(uint8_t flag);

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
    /*! This function prints the current frame
     */
    void showFrame(void);

    int8_t addSensor(uint8_t type, int value);
    int8_t addSensor(uint8_t type, uint16_t value);
    int8_t addSensor(uint8_t type, unsigned long value);
    int8_t addSensor(uint8_t type, double value);
    int8_t addSensor(uint8_t type, double value, int N);
    int8_t addSensor(uint8_t type, char* str);

    int8_t addSensor(uint8_t type, double val1, double val2);
    int8_t addSensor(uint8_t type, unsigned long val1, unsigned long val2);
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3);
    int8_t addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3, int val4);
    int8_t addSensor(uint8_t type, int val1,int val2);
    int8_t addSensor(uint8_t type, int val1,int val2,int val3);
    int8_t addSensor(uint8_t type, double val1,double val2,double val3);

    int8_t addSensor(uint8_t type, uint16_t val[]);

    int8_t checkFields(uint8_t type, uint8_t typeVal, uint8_t fields);

    void setID(char* moteID);
    void getID(char* moteID);

    void decrementSequence(void);

    //! Function: add special timestamp field
    int8_t addTimestamp(void);

    //! Variable : buffer where the frame is created in
    uint8_t buffer[MAX_FRAME+1];

    //! Variable : length of the frame
    uint16_t length;

    //! Variable : number of sensor values within the frame
    uint8_t numFields;

    //! Function: set new tiny frame max length
    void setTinyLength(uint8_t length);
    //! Function: generate new frame from internal strcutures
    uint8_t generateTinyFrame();

    //! Variable : buffer where the Tiny Frame is created
    uint8_t bufferTiny[100];
    uint8_t lengthTiny;
    uint8_t _maxTinyLength;

    //! Function: checks if fragmentation is needed given the input max size
    bool isFragmentationNeeded(uint16_t maxSize);
    //! Function: init structures for fragmenting the frame
    uint8_t createFragmentHeader(uint16_t fragmentSize);
    //! Function: generate frame with optimum capacity
    uint8_t generateFragment();

    //! Variable: maximum payload permitted to split frame
    uint8_t fragmentMaxSize;
    uint8_t fragmentHeaderLength;
    uint8_t fragmentIndex;

    //! Variable : buffer where the fragment frame is created
    uint8_t bufferFragment[101];
    uint16_t lengthFragment;

    //! Structure for storing all fields in binary frame
    struct
    {
		uint8_t flag;	// flag to indicate if data has been added ('0':not added; '1' added)
		uint8_t start;	// index of starting byte of field
		uint8_t size;	// total size of sensor field: id+data
	}field[max_fields];

};

extern WaspFrame frame;

#endif
