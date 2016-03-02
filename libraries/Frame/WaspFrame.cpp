/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
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
 *
 *  Version:		1.9
 *  Design:			David Gascón
 *  Implementation:	Yuri Carmona, Javier Siscart, Joaquín Ruiz
 */
  

#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspFrame.h"
#include "WaspFrameConstants.h"




/// Constructors ///////////////////////////////////////////////////////////////

WaspFrame::WaspFrame()
{	
    // store number zero to EEPROM in roder to start 
    // with this first frame sequence number
    storeSequence(0);
	
	//! This code should be used when Hibernate feature is used instead of the 
	//! previous storeSequence(0) calling
    //~ if( !( digitalRead(RTC_INT_PIN_MON) && (Utils.readEEPROM(HIB_ADDR)==HIB_VALUE) ))
	//~ {
		//~ storeSequence(0);
	//~ }
    
    // set default maximum frame size. It might be changed using 'setFrameSize' 
    // function when using an XBee module
    _maxSize=MAX_FRAME;    
    
    // init waspmote ID attribute
    frame.getID(_waspmoteID);  
}



/// Public Methods /////////////////////////////////////////////////////////////


/*
 * setFrameSize( size ) - set maximum frame size
 * 
 * This function sets the class attribute to the parameter given to this 
 * function always it doesn't exceed the constant predefined in WaspFrame.h 
 * called MAX_FRAME
 * 
 */
void WaspFrame::setFrameSize( uint8_t size )
{
	if( size < MAX_FRAME)
	{		
		// set new maximum size
		_maxSize = size;
	}
	else
	{
		// input parameter exceeds the predefined constant
		_maxSize = MAX_FRAME;
	}
	
	
			
	
}


/*
 * setFrameSize( protocol, linkEncryption, AESEncryption)
 * 
 * This function MUST only be used when using an XBee module. This is the unique
 * module which has size restrictions depending on the protocol, addressing, link
 * encryption and AES encryption use. 
 * 
 * The possible values for protocol are:
 * 	XBEE_802_15_4 
 * 	ZIGBEE 
 * 	DIGIMESH 	
 * 	XBEE_900 		
 * 	XBEE_868 	
 * 
 * The possible values for linkEncryption are:
 *  ENABLED = 1
 * 	DISABLED = 0
 * 
 * The possible values for AESEncryption are:
 *  ENABLED = 1
 * 	DISABLED = 0
 * 
 */
void WaspFrame::setFrameSize(	uint8_t protocol, 
								uint8_t linkEncryption, 
								uint8_t AESEncryption)
{
	// call function prototype using a 64-bit addressing (the unique unicast
	// possible for all XBee modules but the XBee-802.15.4)
	return setFrameSize( protocol, UNICAST_64B, linkEncryption, AESEncryption);	
}

/*
 * setFrameSize( protocol, addressing, linkEncryption, AESEncryption)
 * 
 * This function MUST only be used when using an XBee module. This is the unique
 * module which has size restrictions depending on the protocol, addressing, link
 * encryption and AES encryption use. 
 * 
 * The possible values for protocol are:
 * 	XBEE_802_15_4 
 * 	ZIGBEE 
 * 	DIGIMESH 	
 * 	XBEE_900 		
 * 	XBEE_868 	
 * 
 * The possible values for addressgin are: 
 * 	UNICAST_16B ---> for Unicast 16-bit addressing (only for XBee-802.15.4)
 * 	UNICAST_64B ---> for Unicast 64-bit addressing 
 * 	BROADCAST_MODE 	---> for Broadcast addressing 	
 * 
 * The possible values for linkEncryption are:
 *  ENABLED = 1
 * 	DISABLED = 0
 * 
 * The possible values for AESEncryption are:
 *  ENABLED = 1
 * 	DISABLED = 0
 * 
 */
void WaspFrame::setFrameSize(	uint8_t protocol, 
								uint8_t addressing, 
								uint8_t linkEncryption, 
								uint8_t AESEncryption)
{
	
	/// AES disabled 
	if( AESEncryption == DISABLED )
	{		
		switch (protocol)
		{				
			/// XBEE_802_15_4 ////////////////	
			case XBEE_802_15_4:
			
				if( linkEncryption == DISABLED)
				{									
					// XBEE_802 & Link Disabled & AES Disabled 
					_maxSize = 100;		
				}
				else if( linkEncryption == ENABLED)
				{
					if( addressing == UNICAST_16B )
					{
						// XBEE_802 & Unicast 16B  & Link Enabled & AES Disabled 
						_maxSize = 98;	
					}
					else if( addressing == UNICAST_64B )
					{
						// XBEE_802 & Unicast 64B & Link Enabled & AES Disabled 
						_maxSize = 94;	
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// XBEE_802 & Broadcast & Link Enabled & AES Disabled 						
						_maxSize = 95;	
					}					
				} 		
				break;
			
			/// ZIGBEE /////////////////////
			case ZIGBEE:
			
				if( linkEncryption == DISABLED)
				{
					if( addressing == UNICAST_64B )
					{
						// ZIGBEE & Unicast & Link Disabled & AES Disabled 
						_maxSize = 74;	
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// ZIGBEE & Broadcast & Link Disabled & AES Disabled 						
						_maxSize = 92;	
					}							
				}
				else if( linkEncryption == ENABLED)
				{
					if( addressing == UNICAST_64B )
					{
						// ZIGBEE & Unicast 64B & Link Enabled & AES Disabled 
						_maxSize = 66;	
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// ZIGBEE & Broadcast & Link Enabled & AES Disabled 						
						_maxSize = 84;	
					}					
				} 		
				break;
			
			/// DIGIMESH /////////////////////					
			case DIGIMESH:
				
				_maxSize = 73;	
				break;
			
			/// XBEE_900 /////////////////////					
			case XBEE_900:
			
				if( linkEncryption == DISABLED)
				{							
					_maxSize = 100;								
				}
				else if( linkEncryption == ENABLED)
				{
					_maxSize = 80;						
				} 
					
				break;
			
			/// XBEE_868 /////////////////////					
			case XBEE_868:
				
				_maxSize = 100;								
				break;
				
			default :
				// No limit
				_maxSize = MAX_FRAME;
				break;
		}			
	}		
	/// AES enabled 
	else if( AESEncryption == ENABLED ) 
	{		
		switch (protocol)
		{				
			/// XBEE_802_15_4 ////////////////	
			case XBEE_802_15_4:
			
				if( linkEncryption == DISABLED)
				{									
					// XBEE_802 & Link Disabled & AES Enabled 
					_maxSize = ((100-10-strlen(_waspmoteID))/16)*16;	
				}
				else if( linkEncryption == ENABLED)
				{
					if( addressing == UNICAST_16B )
					{
						// XBEE_802 & Unicast 16B  & Link Enabled & AES Enabled 
						_maxSize = ((98-10-strlen(_waspmoteID))/16)*16;	
					}
					else if( addressing == UNICAST_64B )
					{
						// XBEE_802 & Unicast 64B & Link Enabled & AES Enabled 
						_maxSize = ((94-10-strlen(_waspmoteID))/16)*16;
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// XBEE_802 & Broadcast & Link Enabled & AES Enabled 						
						_maxSize = ((95-10-strlen(_waspmoteID))/16)*16;	
					}					
				} 		
				break;
			
			/// ZIGBEE /////////////////////
			case ZIGBEE:
			
				if( linkEncryption == DISABLED)
				{
					if( addressing == UNICAST_64B )
					{
						// ZIGBEE & Unicast & Link Disabled & AES Enabled 
						_maxSize = ((74-10-strlen(_waspmoteID))/16)*16;	
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// ZIGBEE & Broadcast & Link Disabled & AES Enabled 						
						_maxSize = ((92-10-strlen(_waspmoteID))/16)*16;	
					}							
				}
				else if( linkEncryption == ENABLED)
				{
					if( addressing == UNICAST_64B )
					{
						// ZIGBEE & Unicast 64B & Link Enabled & AES Enabled 
						_maxSize = ((66-10-strlen(_waspmoteID))/16)*16;	
					}
					else if( addressing == BROADCAST_MODE )
					{	
						// ZIGBEE & Broadcast & Link Enabled & AES Enabled 						
						_maxSize = ((84-10-strlen(_waspmoteID))/16)*16;	
					}					
				} 		
				break;
			
			/// DIGIMESH /////////////////////					
			case DIGIMESH:
				
				_maxSize = ((73-10-strlen(_waspmoteID))/16)*16;	
				break;
			
			/// XBEE_900 /////////////////////					
			case XBEE_900:
			
				if( linkEncryption == DISABLED)
				{							
					_maxSize = ((100-10-strlen(_waspmoteID))/16)*16;								
				}
				else if( linkEncryption == ENABLED)
				{
					_maxSize = ((80-10-strlen(_waspmoteID))/16)*16;						
				} 
					
				break;
			
			/// XBEE_868 /////////////////////					
			case XBEE_868:
				
				_maxSize = ((100-10-strlen(_waspmoteID))/16)*16;							
				break;
				
			default :
				// No limit
				_maxSize = MAX_FRAME;
				break;
		}	
		
	}
	/// No limit	
	else
	{ 
		_maxSize = MAX_FRAME;
	}
	
}




/*
 * getFrameSize( ) - returns the maximum frame size previously set
 * 
 *   
 */
uint8_t WaspFrame::getFrameSize( void )
{
	return _maxSize;
}



/* 
 * createFrame () - Initialize frame buffer
 * 
 * Also, frame header bytes are initiliazed with default values
 * 
 */
void WaspFrame::createFrame(uint8_t mode, char* moteID)
{
	// set waspmote ID 
	frame.setID( moteID );
	
	// create new frame
	frame.createFrame( mode );	
}



/* 
 * createFrame () - Initialize frame buffer
 * 
 * Also, frame header bytes are initiliazed with default values
 * 
 */
void WaspFrame::createFrame(uint8_t mode)
{	
	// local variables
	uint8_t sequence;	
	char str[16];	
	
	// store mode: ASCII or BINARY
	_mode = mode;	
	
	// init buffer
	memset( buffer, 0x00, sizeof(buffer) );
	
	// init counter
	numFields = 0;	
	
	// set frame delimiter
	buffer[0] = '<';
	buffer[1] = '=';
	buffer[2] = '>';
		
	uint8_t type;

	// set type of frame depending on the frame mode
	if( _mode == ASCII )
	{
		/** ASCII FRAME **/
		type=B10000000;
		buffer[3]= type;		
	
		// initialize 'number of fields' byte
		buffer[4] = 0x00;
		
		// set the '#' separator
		buffer[5]='#';
		
		// set serial ID
		length = 6;	
		
		// _serial_id is read in main.cpp
		snprintf(str, sizeof(str), "%lu", _serial_id);
		
		for( uint16_t i=0 ; i<strlen(str) ; i++ )
		{
			// break if end of string
			if( str[i] == '\0') 
			{
				break;
			}
			else
			{
				buffer[length] = str[i];
				length++;
			}
		}

		// set separator '#'
		buffer[length] = '#';	
		length++;

		// set identifier
		for( int i=0 ; i<16 ; i++ )
		{
			// break if end of string
			if( _waspmoteID[i] == '\0') 
			{
				break;
			}
			else
			{
				// if '#' character appears -> change it for '_'
				if( _waspmoteID[i] == '#' )
				{
					buffer[length] = '_';
				}
				else
				{
					buffer[length] = _waspmoteID[i];
				}
				length++;
			}
		}

		// set separator '#'
		buffer[length] = '#';	
		length++;

		// read sequence number from EEPROM
		sequence = readSequence();

		// convert from integer to string
		char seqStr[4];
		itoa(sequence, seqStr, 10);
		
		// add sequence number	
		memcpy( &buffer[length], seqStr, strlen(seqStr));
		length += strlen(seqStr);
		
		// add separator '#'
		buffer[length] = '#';		
		length++;

		// increment and store the frame sequence number
		sequence++;
		storeSequence(sequence);
		
		// now the frame is ready to be filled with new sensor values!		
	}
	else 
	{		
		if (_mode == BINARY)
		{
			/** BINARY FRAME **/
			type=B00000000;
			buffer[3] = type;
		}
				
		// set serial ID
		// _serial_id is read in main.cpp			
		char val[4]; 
		memcpy(val, (const void*)&_serial_id, 4);
		
		/*union {
		  unsigned long f;
		  char b[4];
		} u;
		u.b[3] = val[3];
		u.b[2] = val[2];
		u.b[1] = val[1];
		u.b[0] = val[0];

		USB.println(u.f);	*/

		// concatenate sensor name to frame string
        buffer[5] = val[0];
		buffer[6] = val[1];
        buffer[7] = val[2];
		buffer[8] = val[3];
		length = 9;		

		// set identifier
		for( int i=0 ; i<16 ; i++ )
		{
			// break if end of string
			if( _waspmoteID[i] == '\0') 
			{
				break;
			}
			else
			{
				// if '#' character appears -> change it for '_'
				if( _waspmoteID[i] == '#' )
				{
					buffer[length] = '_';
				}
				else
				{
					buffer[length]=_waspmoteID[i];
				}
				length++;
			}
		}

		// set separator '#'
		buffer[length] = '#';	
		length++;

		// read and set the sequence number to the frame   
		sequence=readSequence();
		buffer[length]=sequence;
		length++;
		
		// initialize 'number of bytes' field
		buffer[4] = length - 5;	

		sequence++;
		storeSequence(sequence);

	}
}





#ifdef WaspAES_h
/* 
 * createEncryptedFrame () - Create encrypted frame from previous created frame
 * The inner 'frame.buffer' is used for encapsulating the new Waspmote frame. 
 * The structure of the encrypted frames is: 
 *  ___________________________________________________________________________
 * |     |            |           |           |          |   |                 | 
 * | <=> | Frame Type | Num Bytes | ID secret |  Wasp ID | # | Encrypted Frame |
 * |_____|____________|___________|___________|__________|___|_________________| 
 * 
 * Where 'Encrypted Frame' is the original 'frame.buffer' which is encrypted 
 * using the specifications of this function: AES key size qand pasword. ECB 
 * mode and ZEROS padding are always used. The resulting encrypted frame is 
 * stored in the same 'frame.buffer'
 */
uint8_t WaspFrame::encryptFrame( uint16_t keySize, char* password )
{	
	// Variable for encrypted message's length	
	uint16_t encrypted_length;
  
	// calculate encrypted length
	encrypted_length = AES.sizeOfBlocks(frame.length); 
	
	if( encrypted_length > frame._maxSize )
	{
		return 0;
	}
	
	// Buffer for the encrypted message with enough memory space
	uint8_t encrypted_message[encrypted_length]; 
	
	// create Encrypted message
	AES.encrypt(  keySize
				, password
				, frame.buffer
				, frame.length
				, encrypted_message
				, ECB
				, ZEROS); 
	
	/// Create new frame with the correct structure
	/***
	 __________________________________________________________________________
	|     |            |           |          |          |   |                 | 
	| <=> | Frame Type | Num Bytes | secretID |  Wasp ID | # | Encrypted Frame |
	|_____|____________|___________|__________|__________|___|_________________| 
	*/
	
	// define the frame type depending on the 
	// key size. ECB mode is always used for Meshlium. 
	uint8_t	frame_type;
	
	if( keySize == AES_128 )
	{
		frame_type = AES128_ECB_FRAME;
	}
	else if( keySize == AES_192 )
	{
		frame_type = AES192_ECB_FRAME;		
	}
	else if( keySize == AES_256 )
	{
		frame_type = AES256_ECB_FRAME;		
	}
	else
	{
		return 0;
	}
		
	// set serial ID
	char val[4]; 
	memcpy(val, (const void*)&_serial_id, 4);
	
	// set frame delimiter
	frame.buffer[0] = '<';
	frame.buffer[1] = '=';
	frame.buffer[2] = '>';
	frame.buffer[3] = frame_type;
	frame.buffer[4] = encrypted_length + 5 + strlen(frame._waspmoteID); // length
	frame.buffer[5] = val[0]; // serial ID
	frame.buffer[6] = val[1]; // serial ID
	frame.buffer[7] = val[2]; // serial ID
	frame.buffer[8] = val[3]; // serial ID
	
	// temporal length of frame
	uint16_t temp_length = 9;
	
	// waspmote ID
	for(uint16_t i = 0; i < strlen(frame._waspmoteID) ; i++)
	{
		frame.buffer[temp_length+i] = frame._waspmoteID[i];
	}	
	temp_length += strlen(frame._waspmoteID);
	
	// separator
	frame.buffer[temp_length] = '#';
	temp_length++;
	
	// copy payload: encrypted message
	for( uint16_t j = 0 ; j < encrypted_length; j++)
	{
		frame.buffer[temp_length+j] = encrypted_message[j];		
	}
	temp_length += encrypted_length;
	
	// set frame.length attribute
	frame.length = temp_length;
	
	// update attribute with the special frame type
	_mode = ENCRYPTED_FRAME;
	
	return 1;
}
#endif





/* 
 * setFrameType () - Set Frame Type
 * 
 * The possible frame types to be selected are:
 * 	EXAMPLE_FRAME
 * 	TIMEOUT_FRAME 	
 * 	EVENT_FRAME 	
 * 	ALARM_FRAME 	
 * 	SERVICE1_FRAME 
 * 	SERVICE2_FRAME 
 * 
 */
void WaspFrame::setFrameType(uint8_t type)
{			
	// set Frame Type in bits b5-b0 of correspondent field
	buffer[3] |= type & B00111111;
}



/*
 * showFrame (void) - Show current frame buffer
 * 
 */
void WaspFrame::showFrame(void)
{
	USB.secureBegin();
	
	for(int i = 0; i <31 ; i++)
	{
		printByte( '=',  0);
	}
	printByte( '\r',  0);
	printByte( '\n',  0);
	
	
	if( _mode == ASCII )
	{
		printString( "Current ASCII",  0);		
	}
	else if( _mode == BINARY )
	{
		printString( "Current BINARY",  0);	
	}
	else if( _mode == ENCRYPTED_FRAME )
	{
		printString( "Current ENCRYPTED",  0);	
	}
	else return (void)0;
	
	printString( " Frame:\r\n",  0);
	
	printString( "Length: ",  0);
	printIntegerInBase(length, 10,  0);	
	printByte( '\r',  0);
	printByte( '\n',  0);
	
	printString( "Frame Type:  ",  0);	
	printIntegerInBase(buffer[3], 10,  0);	
	printByte( '\r',  0);
	printByte( '\n',  0);

	printString( "frame (HEX): ",  0);	
	for( uint16_t i= 0; i < length ; i++ )
	{		
		puthex((char)buffer[i],0);
	}
	
	printByte( '\r',  0);
	printByte( '\n',  0);

	printString( "frame (STR): ",  0);	
	for( uint16_t i= 0; i < length ; i++ )
	{
		printByte( buffer[i],  0);
	}
	
	printByte( '\r',  0);
	printByte( '\n',  0);
	
	for(int i = 0; i <31 ; i++)
	{
		printByte( '=',  0);
	}

	printByte( '\r',  0);
	printByte( '\n',  0);
	
	USB.secureEnd();	
}



/*
 * addSensor (type, value) - add sensor value to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	value : indicates the sensor value as a float 	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, int value)
{
	char str[10];
	
	if(_mode == ASCII)
	{
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		itoa( value, str, 10);	
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str)  +
						 strlen(":")  +
						 strlen("#") 	))
			{
				return -1;
			}
			
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value
		// 'index_4' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(str)-strlen(":")-strlen("#");
		int index_2 = length-strlen(str)-strlen(":")-strlen("#");
		int index_3 = length-strlen(str)-strlen("#");
		int index_4 = length-strlen("#");
		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str'
		memcpy ( &buffer[index_3], str, strlen(str) );	
	
		// add separator '#'
		memcpy ( &buffer[index_4], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor
		if (value<=255)
		{
			if( checkFields(type, TYPE_UINT8, 1) == -1 ) return -1;
		}
		else
		{
			if( checkFields(type, TYPE_INT, 1) == -1 ) return -1;
		}

		// set data bytes (in this case, int is two bytes)
		char val[2];
		memcpy(val,&value,2);

	    /*char val1 = value &0xFF;
    	char val2 = (value >> 8) &0xFF;  */

    	//Check again (1 byte or 2 bytes)
    	uint8_t config;
		config =(uint8_t)pgm_read_word(&(SENSOR_TYPE_TABLE[type])); 

		if (config == TYPE_INT)
		{
			// check if new sensor value fits
			if(!checkLength(3))
			{
				return -1;
			}

			// concatenate sensor name to frame string
	        buffer[length-3] = (char)type;
	        buffer[length-2] = val[0];
			buffer[length-1] = val[1];
			buffer[length] = '\0';
		}
		else
		{
			// check if new sensor value fits
			if(!checkLength(2))
			{
				return -1;
			}

			// concatenate sensor name to frame string
	        buffer[length-2] = (char)type;
			buffer[length-1] = val[0];
			buffer[length] = '\0';
		}

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}

	return length;
}



/*
 * addSensor (type, value) - add sensor value to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	value : indicates the sensor value as an unsigned long
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, unsigned long value)
{
	char str[20];
	
	if(_mode == ASCII)
	{
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		ultoa( value, str, 10);
	
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str)  +
						 strlen(":")  +
						 strlen("#") 	))
		{
			return -1;
		}
				
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value
		// 'index_4' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(str)-strlen(":")-strlen("#");
		int index_2 = length-strlen(str)-strlen(":")-strlen("#");
		int index_3 = length-strlen(str)-strlen("#");
		int index_4 = length-strlen("#");
		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str'
		memcpy ( &buffer[index_3], str, strlen(str) );	
	
		// add separator '#'
		memcpy ( &buffer[index_4], "#", strlen("#") );	
					
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor		
		if(checkFields(type, TYPE_ULONG, 1) == -1 ) return -1;
		
		// set data bytes (in this case, double is 4...)
		char val[4];
		memcpy(val,&value,4);
		
		/* Check correct copy
		union {
		  unsigned long f;
		  char b[4];
		} u;
		u.b[3] = val[3];
		u.b[2] = val[2];
		u.b[1] = val[1];
		u.b[0] = val[0];
		delay(1);
		USB.println(u.f);*/
		
		// check if new sensor value fits /1+4/
		if(!checkLength(5))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-5] = (char)type;
        buffer[length-4] = val[0];
		buffer[length-3] = val[1];
        buffer[length-2] = val[2];
		buffer[length-1] = val[3];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;
		
	}

	return length;
}




/*
 * addSensor (type, value) - add sensor value to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	value : indicates the sensor value as a float
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, double value)
{
	// get name of sensor from table
	char numDecimals;
	numDecimals =(uint8_t)pgm_read_word(&(DECIMAL_TABLE[type])); 
	
	return addSensor(type, value, numDecimals);
}



/*
 * addSensor (type, value, N) - add sensor value to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	value : indicates the sensor value as a float
 * 	N : number of decimals
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, double value, int N)
{
	char str[20];
		
	if(_mode == ASCII)
	{
		// convert from float to string		
		dtostrf( value,	N, N, str );
		
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str)  +
						 strlen(":")  +
						 strlen("#") 	))
		{
			return -1;
		}
	
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value
		// 'index_4' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(str)-strlen(":")-strlen("#");
		int index_2 = length-strlen(str)-strlen(":")-strlen("#");
		int index_3 = length-strlen(str)-strlen("#");
		int index_4 = length-strlen("#");
		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str'
		memcpy ( &buffer[index_3], str, strlen(str) );	
	
		// add separator '#'
		memcpy ( &buffer[index_4], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
	}
	else
	{	
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_FLOAT, 1) == -1 ) return -1;
		
		// set data bytes (in this case, double is 4...)
		char val[4];
		memcpy(val,&value,4);
		
		/* Check correct copy
		union {
		  float f;
		  char b[4];
		} u;
		u.b[3] = val[3];
		u.b[2] = val[2];
		u.b[1] = val[1];
		u.b[0] = val[0];
		delay(1);
		USB.println(u.f);*/
		
		// check if new sensor value fits /1+4/
		if(!checkLength(5))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-5] = (char)type;
        buffer[length-4] = val[0];
		buffer[length-3] = val[1];
        buffer[length-2] = val[2];
		buffer[length-1] = val[3];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}		

	return length;
}



/*
 * addSensor (type, value) - add sensor value to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	value : indicates the sensor value as a float 	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, char* str)
{	
	// calculate the buffer length to be created 
	// depending on the input string to be copied to it
	uint16_t string_length = strlen(str)+1;
	const  uint16_t MAX_SIZE = 400;
	
	// limit the max string length to MAX_SIZE Bytes 
	// to avoid running out of memory
	if ( string_length >= MAX_SIZE)
	{
		string_length = MAX_SIZE;
	}	
	
	// create aux buffer
	char aux_str[string_length];
	
	// clear aux buffer	
	memset( aux_str, 0x00, sizeof(aux_str) );
	
	// copy string to aux buffer
	strncpy( aux_str, str, sizeof(aux_str)-1 );
	
	// avoid '#' characters inside the string
	for( uint16_t i = 0; i < strlen(aux_str) ; i++)
	{
		if( aux_str[i] == '#' )
		{			
			aux_str[i] = '_';
		}
	}	
	
	if(_mode == ASCII)
	{	
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(aux_str)  +
						 strlen(":")  +
						 strlen("#") 	))
		{
			return -1;
		}
		
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value
		// 'index_4' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(aux_str)-strlen("#");
		int index_2 = length-strlen(":")-strlen(aux_str)-strlen("#");
		int index_3 = length-strlen(aux_str)-strlen("#");
		int index_4 = length-strlen("#");
		
		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'aux_str'
		memcpy ( &buffer[index_3], aux_str, strlen(aux_str) );	
	
		// add separator '#'
		memcpy ( &buffer[index_4], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_CHAR, 1) == -1 ) return -1;

		// set data bytes (in this case, string, one byte per char) & length (1 byte)
		int8_t lng = strlen(aux_str);
		
		// check if new sensor value fits (id + nbytes + str)
		if(!checkLength(2+strlen(aux_str)))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        int len = length-2-strlen(aux_str);
        buffer[len] = (char)type;
        buffer[len+1] = lng;
		for (uint16_t j=len+2;j<length;j++)
		{
			buffer[j] = aux_str[j-2-len];
		}
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;
		
	}		

	return length;
}




/*
 * addSensor( type, val1, val2) - add sensor to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	val1 : indicates the sensor value as a float 	
 *  val2 : indicates the sensor value as a float 	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, double val1, double val2)
{

	char str1[20];
	char str2[20];

	if(_mode == ASCII)
	{
		// get name of sensor from table
		char numDecimals;
		numDecimals =(uint8_t)pgm_read_word(&(DECIMAL_TABLE[type])); 
				
		
		// convert from float to string		
		dtostrf( val1,	numDecimals, numDecimals, str1 );
		dtostrf( val2,	numDecimals, numDecimals, str2 );

		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str1) + strlen(str2) +
						 strlen(";") +
						 strlen(":")  +
						 strlen("#") 	))
		{
			return -1;
		}
		
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding ';'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_3 = length-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_4 = length-strlen(";")-strlen(str2)-strlen("#");
		int index_5 = length-strlen(str2)-strlen("#");
		int index_6 = length-strlen("#");

		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add ';'
		memcpy ( &buffer[index_4], ";", strlen(";") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );		
	
		// add separator '#'
		memcpy ( &buffer[index_6], "#", strlen("#") );		
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_FLOAT, 2) == -1 ) return -1;
		
		// set data bytes (in this case, double is 4...)
		char valB1[4]; char valB2[4];
		memcpy(valB1,&val1,4);
		memcpy(valB2,&val2,4);
		
		/*
		union{
		  float f;
		  char b[4];
		} u;
		u.b[3] = valB1[3];
		u.b[2] = valB1[2];
		u.b[1] = valB1[1];
		u.b[0] = valB1[0];

		USB.println(u.f);
		*/
		
		// check if new sensor value fits /1+4+4/
		if(!checkLength(9))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-9] = (char)type;
        buffer[length-8] = valB1[0];
		buffer[length-7] = valB1[1];
        buffer[length-6] = valB1[2];
		buffer[length-5] = valB1[3];
        buffer[length-4] = valB2[0];
		buffer[length-3] = valB2[1];
        buffer[length-2] = valB2[2];
		buffer[length-1] = valB2[3];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}		

	return length;
}


/*
 * addSensor( type, val1, val2) - add sensor to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	val1 : indicates the sensor value as a float 	
 *  val2 : indicates the sensor value as a float 	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, unsigned long val1, unsigned long val2)
{

	char str1[20];
	char str2[20];

	if(_mode == ASCII)
	{
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		ultoa( val1, str1, 10);
		ultoa( val2, str2, 10);
	
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str1) + strlen(str2) +
						 strlen(";") +
						 strlen(":")  +
						 strlen("#") 	))
		{
			return -1;
		}
		
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding ';'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_3 = length-strlen(str1)-strlen(";")-strlen(str2)-strlen("#");
		int index_4 = length-strlen(";")-strlen(str2)-strlen("#");
		int index_5 = length-strlen(str2)-strlen("#");
		int index_6 = length-strlen("#");

		
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add ';'
		memcpy ( &buffer[index_4], ";", strlen(";") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );		
	
		// add separator '#'
		memcpy ( &buffer[index_6], "#", strlen("#") );		
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_ULONG, 2) == -1 ) return -1;
		
		// set data bytes (in this case, double is 4...)
		char valB1[4]; char valB2[4];
		memcpy(valB1,&val1,4);
		memcpy(valB2,&val2,4);
		
		// check if new sensor value fits /1+4+4/
		if(!checkLength(9))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-9] = (char)type;
        buffer[length-8] = valB1[0];
		buffer[length-7] = valB1[1];
        buffer[length-6] = valB1[2];
		buffer[length-5] = valB1[3];
        buffer[length-4] = valB2[0];
		buffer[length-3] = valB2[1];
        buffer[length-2] = valB2[2];
		buffer[length-1] = valB2[3];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}		

	return length;
}




/*
 * addSensor( type, val1, val2, val3) - add sensor to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	val1 : indicates the sensor value as an uint8_t	
 *  val2 : indicates the sensor value as an uint8_t
 *  val2 : indicates the sensor value as an uint8_t	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached  
 * 
 * This function prototype is only thought for SENSOR_TIME and SENSOR_DATE fields
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3)
{
	char str1[10];
	char str2[10];
	char str3[10];
	
	if(_mode == ASCII)
	{
		/// ASCII
		
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		itoa( val1, str1, 10);
		itoa( val2, str2, 10);
		itoa( val3, str3, 10);
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(":")  +
						 strlen(str1)  +
						 strlen("-") +
						 strlen(str2) +
						 strlen("-") +
						 strlen(str3) +
						 strlen("#") 	))
		{
			return -1;
		}
			
			
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding '-'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding '-'
		// 'index_7' is needed for adding sensor value in str3
		// 'index_8' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("#");
		int index_3 = length-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("#");
		int index_4 = length-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("#");
		int index_5 = length-strlen(str2)-strlen("-")-strlen(str3)-strlen("#");
		int index_6 = length-strlen("-")-strlen(str3)-strlen("#");
		int index_7 = length-strlen(str3)-strlen("#");
		int index_8 = length-strlen("#");
				
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add '-'
		memcpy ( &buffer[index_4], "-", strlen("-") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );
		
		// add '-'
		memcpy ( &buffer[index_6], "-", strlen("-") );
	
		// add input string defined in 'str3'
		memcpy ( &buffer[index_7], str3, strlen(str3) );		
	
		// add separator '#'
		memcpy ( &buffer[index_8], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		/// BINARY
				
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_UINT8, 3) == -1 ) return -1;		
		
		// check if new sensor value fits 1+1+1+1
		if(!checkLength(4))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-4] = (char)type;
        buffer[length-3] = val1;
        buffer[length-2] = val2;
        buffer[length-1] = val3;
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}

	return length;
}





/*
 * addSensor( type, val1, val2, val3, val4) - add sensor to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	val1 : indicates the sensor value as an uint8_t	
 *  val2 : indicates the sensor value as an uint8_t
 *  val2 : indicates the sensor value as an uint8_t	
 *  val2 : indicates the sensor value as an int	
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached  
 * 
 * This function prototype is only thought for SENSOR_TIME field
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3, int val4)
{
	char str1[10];
	char str2[10];
	char str3[10];
	char str4[10];

	if(_mode == ASCII)
	{
		/// ASCII
		
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		itoa( val1, str1, 10);
		itoa( val2, str2, 10);
		itoa( val3, str3, 10);
		itoa( val4, str4, 10);
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(":")  +
						 strlen(str1)  +
						 strlen("-") +
						 strlen(str2) +
						 strlen("-") +
						 strlen(str3) +
						 strlen("+") +
						 strlen(str4) +
						 strlen("#") 	))
		{
			return -1;
		}
		
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding '-'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding '-'
		// 'index_7' is needed for adding sensor value in str3
		// 'index_8' is needed for adding '+'
		// 'index_9' is needed for adding sensor value in str4
		// 'index_10' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_3 = length-strlen(str1)-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_4 = length-strlen("-")-strlen(str2)-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_5 = length-strlen(str2)-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_6 = length-strlen("-")-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_7 = length-strlen(str3)-strlen("+")-strlen(str4)-strlen("#");
		int index_8 = length-strlen("+")-strlen(str4)-strlen("#");
		int index_9 = length-strlen(str4)-strlen("#");
		int index_10 = length-strlen("#");
	
				
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add '-'
		memcpy ( &buffer[index_4], "-", strlen("-") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );
		
		// add '-'
		memcpy ( &buffer[index_6], "-", strlen("-") );
	
		// add input string defined in 'str3'
		memcpy ( &buffer[index_7], str3, strlen(str3) );	
		
		if( val4>= 0 )
		{
			// add '+'
			memcpy ( &buffer[index_8], "+", strlen("+") );
		}
		else
		{		
			// if negative then index_8 is useless because character '-' is
			// implicit within the number, so it is necessary to delete 1 Byte
			index_9 -= 1;
			index_10 -= 1;
		}
		
		// add input string defined in 'str4'
		memcpy ( &buffer[index_9], str4, strlen(str4) );		
	
		// add separator '#'
		memcpy ( &buffer[index_10], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4] = numFields;
	}
	else
	{
		/// BINARY
		
		// As SENSOR_TIME is thought to be a 3-value field. This function permits to 
		// add teh GMT value at the end of the time. But "checkFields" function must
		// expect 3 values because it is the original composition.
		if(checkFields(type, TYPE_UINT8, 3) == -1 ) return -1;		
		
		// check if new sensor value fits 1+1+1+1
		if(!checkLength(4))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-4] = (char)type;
        buffer[length-3] = val1;
        buffer[length-2] = val2;
        buffer[length-1] = val3;
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}

	return length;
}





/*
 * addSensor( type, val1, val2, val3) - add sensor to frame
 * 
 * Parameters:
 * 	type : Refers to the type of sensor data
 * 	val1 : indicates the sensor value as an int (int16_t) 	
 *  val2 : indicates the sensor value as an int (int16_t) 	
 *  val2 : indicates the sensor value as an int (int16_t) 		
 * 
 * Returns: 
 * 	'length' of the composed frame when ok 
 * 	-1 when the maximum length of the frame is reached  
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, int val1,int val2,int val3)
{
	char str1[10];
	char str2[10];
	char str3[10];

	if(_mode == ASCII)
	{
		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// convert from integer to string
		itoa( val1, str1, 10);
		itoa( val2, str2, 10);
		itoa( val3, str3, 10);
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(":")  +
						 strlen(str1)  +
						 strlen(";") +
						 strlen(str2) +
						 strlen(";") +
						 strlen(str3) +
						 strlen("#") 	))
		{
			return -1;
		}
		
		
		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding ';'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding ';'
		// 'index_7' is needed for adding sensor value in str3
		// 'index_8' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_3 = length-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_4 = length-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_5 = length-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_6 = length-strlen(";")-strlen(str3)-strlen("#");
		int index_7 = length-strlen(str3)-strlen("#");
		int index_8 = length-strlen("#");
				
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add ';'
		memcpy ( &buffer[index_4], ";", strlen(";") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );
		
		// add ';'
		memcpy ( &buffer[index_6], ";", strlen(";") );
	
		// add input string defined in 'str3'
		memcpy ( &buffer[index_7], str3, strlen(str3) );		
	
		// add separator '#'
		memcpy ( &buffer[index_8], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if( checkFields(type, TYPE_INT, 3) == -1 ) return -1;

		// set data bytes (in this case, int is two bytes)
		char valC1[2];
		char valC2[2];
		char valC3[2];
		memcpy(valC1,&val1,2);
		memcpy(valC2,&val2,2);
		memcpy(valC3,&val3,2);

		// check if new sensor value fits 1+2+2+2
		if(!checkLength(7))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-7] = (char)type;
        buffer[length-6] = valC1[0];
		buffer[length-5] = valC1[1];
        buffer[length-4] = valC2[0];
		buffer[length-3] = valC2[1];
        buffer[length-2] = valC3[0];
		buffer[length-1] = valC3[1];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}

	return length;
}

/*
 * 
 * 
 * 
 * 
 * 
 */
int8_t WaspFrame::addSensor(uint8_t type, double val1,double val2,double val3)
{
	
	char str1[20];
	char str2[20];
	char str3[20];

	if(_mode == ASCII)
	{
		// get name of sensor from table
		char numDecimals;
		numDecimals =(uint8_t)pgm_read_word(&(DECIMAL_TABLE[type])); 
		
		// convert from float to string		
		dtostrf( val1,	numDecimals, numDecimals, str1 );
		dtostrf( val2,	numDecimals, numDecimals, str2 );
		dtostrf( val3,	numDecimals, numDecimals, str3 );

		// get name of sensor from table
		char name[10];
		strcpy_P(name, (char*)pgm_read_word(&(SENSOR_TABLE[type]))); 
		
		// check if new sensor value fits in the frame or not
		// in the case the maximum length is reached, exit with error
		// if not, then add the new sensor length to the total length
		if(!checkLength( strlen(name) +
						 strlen(str1) + strlen(str2) + strlen(str3) +
						 strlen(";") + strlen(";") + strlen(":") +
						 strlen("#") 	))
		{
			return -1;
		}

		// create index for each element to be inserted in the sensor field
		// 'index_1' is needed for adding the sensor tag
		// 'index_2' is needed for adding ':'
		// 'index_3' is needed for adding sensor value in str1
		// 'index_4' is needed for adding ';'
		// 'index_5' is needed for adding sensor value in str2
		// 'index_6' is needed for adding ';'
		// 'index_7' is needed for adding sensor value in str3
		// 'index_8' is needed for adding the separator '#'
		int index_1 = length-strlen(name)-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_2 = length-strlen(":")-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_3 = length-strlen(str1)-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_4 = length-strlen(";")-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_5 = length-strlen(str2)-strlen(";")-strlen(str3)-strlen("#");
		int index_6 = length-strlen(";")-strlen(str3)-strlen("#");
		int index_7 = length-strlen(str3)-strlen("#");
		int index_8 = length-strlen("#");
				
		// add sensor tag	
		memcpy ( &buffer[index_1], name, strlen(name) );	

		// add ':'
		memcpy ( &buffer[index_2], ":", strlen(":") );	
	
		// add input string defined in 'str1'
		memcpy ( &buffer[index_3], str1, strlen(str1) );
		
		// add ';'
		memcpy ( &buffer[index_4], ";", strlen(";") );
	
		// add input string defined in 'str2'
		memcpy ( &buffer[index_5], str2, strlen(str2) );
		
		// add ';'
		memcpy ( &buffer[index_6], ";", strlen(";") );
	
		// add input string defined in 'str3'
		memcpy ( &buffer[index_7], str3, strlen(str3) );		
	
		// add separator '#'
		memcpy ( &buffer[index_8], "#", strlen("#") );	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if( checkFields(type, TYPE_FLOAT, 3) == -1 ) return -1;
		
		// set data bytes (in this case, double is 4...)
		char valB1[4]; char valB2[4]; char valB3[4];
		memcpy(valB1,&val1,4);
		memcpy(valB2,&val2,4);
		memcpy(valB3,&val3,4);
		/*
		union {
		  float f;
		  char b[4];
		} u;
		u.b[3] = val[3];
		u.b[2] = val[2];
		u.b[1] = val[1];
		u.b[0] = val[0];

		USB.println(u.f);
		*/
		// check if new sensor value fits /1+4+4+4/
		if(!checkLength(13))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        buffer[length-13] = (char)type;
        buffer[length-12] = valB1[0];
		buffer[length-11] = valB1[1];
        buffer[length-10] = valB1[2];
		buffer[length-9] = valB1[3];
        buffer[length-8] = valB2[0];
		buffer[length-7] = valB2[1];
        buffer[length-6] = valB2[2];
		buffer[length-5] = valB2[3];
        buffer[length-4] = valB3[0];
		buffer[length-3] = valB3[1];
        buffer[length-2] = valB3[2];
		buffer[length-1] = valB3[3];
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;

	}		

	return length;
}



/*
 * checkFields(type, typeVal, fields ) - check type of value given by the user
 * 
 * Parameters:
 * 	'type' is the index given to the sensor
 * 	'typeVal' is the type of variable given [0:uint8][1:int][2:double][3:char*]
 * 	'fields' is the number of fields the sensor must have
 * All parameters given are checked by this function in order to see if the 
 * inputs are OK 
 * 
 */
int8_t WaspFrame::checkFields(uint8_t type, uint8_t typeVal, uint8_t fields)
{
	uint8_t config;
	uint8_t nfields;

	// *1* check sensor typeVal
	
	config =(uint8_t)pgm_read_word(&(SENSOR_TYPE_TABLE[type])); 
		
	// special case (0 might be 1)
	if (config ==1)
	{
		if ((typeVal == 0)||(typeVal == 1))
		{
			//OK
		}
		else
		{
			USB.print(F("ERR sensor type & value mismatch, "));
			USB.print( config, DEC);
			USB.print(F(" vs "));			
			USB.println( typeVal, DEC);			
			return -1;
		}
	}
	else
	{
		if (config == typeVal)
		{
			//OK
		}
		else
		{
			USB.print(F("ERR sensor type & value mismatch, "));
			USB.print( config, DEC);
			USB.print(F(" vs "));			
			USB.println( typeVal, DEC);				
			return -1;
		}
	}

	// *2* check sensor number of fields

	nfields =(uint8_t)pgm_read_word(&(SENSOR_FIELD_TABLE[type]));
	if (nfields == fields)
	{
		//OK
	}
	else
	{
		USB.println(F("ERR sensor type & number of fields mismatch"));
		return -1;
	}

	return 1;
}




/// Private Methods ////////////////////////////////////////////////////////////

/*
 * checkLength (sum) - check if maximum length is reached
 *
 * 
 * Return:
 *  '1' : if new sensor value fits in the frame
 *  '0' : if new sensor value does not fit in the frame
 * 
 */
uint8_t WaspFrame::checkLength(int sum)
{
	if(	length + sum <= _maxSize )
	{
		// if OK, add new length to total length
		length = length + sum;
		return 1;
	}
	else
	{
		// error
		return 0;
	}
	
}



/*
 * setID (moteID) - store mote ID to EEPROM
 *
 * This function stores the mote Identifier in EEPROM[147-162] addresses
 */
void WaspFrame::setID(char* moteID)
{
	
	// set zeros in EEPROM addresses
	for( int i=0 ; i<16 ; i++ )
	{
		eeprom_write_byte((unsigned char *) i+MOTEID_ADDR, 0x00);
	}
	
	// clear the waspmote ID attribute
	memset( _waspmoteID, 0x00, sizeof(_waspmoteID) );
	
	// set the mote ID from EEPROM memory
	for( int i=0 ; i<16 ; i++ )
	{		
		if( moteID[i] != '#' )
		{
			eeprom_write_byte((unsigned char *) i+MOTEID_ADDR, moteID[i]);
			_waspmoteID[i] = moteID[i];
		}
		else
		{
			eeprom_write_byte((unsigned char *) i+MOTEID_ADDR, '_');
			_waspmoteID[i] = '_';
		}
		
		// break if end of string
		if( moteID[i] == '\0')
		{			
			break;
		}
	}

}


/*
 * getID (moteID) - read mote ID from EEPROM
 *
 * This function reads the moteID previously stored in EEPROM[147-162] addresses
 */
void WaspFrame::getID(char* moteID)
{
	// clear the waspmote ID attribute
	memset( _waspmoteID, 0x00, sizeof(_waspmoteID) );
	
	// read mote ID from EEPROM memory
	for(int i=0 ; i<16 ; i++ )
	{
		_waspmoteID[i] = Utils.readEEPROM(i+MOTEID_ADDR);
		moteID[i] = _waspmoteID[i];
	}	
	moteID[16]='\0';
		
}


/*
 * storeSequence (seqNumber) - store the sequence number to EEPROM[163] address
 * 
 */
void WaspFrame::storeSequence(uint8_t seqNumber)
{	
	// store frame sequence number to EEPROM[163]	
	eeprom_write_byte((unsigned char *) SEQUENCE_ADDR, seqNumber);


}



/*
 * readSequence (void) - read the sequence number from EEPROM[163] address
 * 
 */
uint8_t WaspFrame::readSequence(void)
{	
	// read frame sequence number from EEPROM[163]
	return Utils.readEEPROM(SEQUENCE_ADDR);

}




/*
 * decrementSequence (void) - decrement the sequence number
 * 
 * This function is useful for external function which only need to send a 
 * Frame with no sensor but some kind of feature. i.e. time sync frame
 */
void WaspFrame::decrementSequence(void)
{	
	uint8_t aux_sequence = readSequence();
	
	aux_sequence--;
	
	// store the new sequence number
	storeSequence(aux_sequence);
}

/*
 * addTimestamp () - add time stamp to the frame from RTC
 *
 * 
 * Return:
 *  '1' : if new sensor value does not fit in the frame
 *  '0' : if new sensor value fits in the frame
 * 
 */

int8_t WaspFrame::addTimestamp()
{	
	//ensure RTC is ON
	RTC.ON();
	unsigned long epochTime = RTC.getEpochTime();
	
	if (_mode == ASCII)
	{
		return addSensor(SENSOR_TST, epochTime);
	}
	else
	{
		// check if new sensor value fits /1+4/
		if(!checkLength(5))
		{
			return -1;
		}		
		
		// look for the separator
		uint8_t* pointer;
		pointer = (uint8_t*) memchr(&buffer[9],'#', length-5-9);
		
		if (pointer == NULL)
		{
			return -1;
		}
		
		// increment index to reach beginning of first payload byte
		pointer++;
		pointer++;
		
		// calculate total buffer size to move
		uint32_t size = length - 5 - (pointer-&buffer[0]);
		
		// move data to make room for timestamp
		memmove(pointer+5, pointer, size);
		
		// copy timestamp to buffer
		char type = SENSOR_TST;
		memcpy(pointer,&type,1);
		memcpy(pointer+1,&epochTime,4);
		
		// increment sensor fields counter 
		numFields++;
		// update number of bytes field
		buffer[4] = frame.length-5;		

		return length;
	}

}

/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspFrame frame = WaspFrame();

