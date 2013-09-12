/*
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.0
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
    
    // set default maximum frame size. It might be changed using 'setFrameSize' 
    // function when using an XBee module
    _maxSize=MAX_FRAME;      
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
		_maxSize=size;
	}
	else
	{
		// input parameter exceeds the predefined constant
		_maxSize=MAX_FRAME;
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
	switch (AESEncryption)
	{
		case DISABLED: /// AES disabled //////////////////////////////////////////////
		
			switch (protocol)
			{				
				/// XBEE_802_15_4 ////////////////	
				case XBEE_802_15_4:
				
					if( linkEncryption == DISABLED)
					{						
						_maxSize = 100;		
					}
					else if( linkEncryption == ENABLED)
					{
						if( addressing == UNICAST_16B )
						{
							_maxSize = 98;	
						}
						else if( addressing == UNICAST_64B )
						{
							_maxSize = 94;	
						}
						else if( addressing == BROADCAST_MODE )
						{							
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
							_maxSize = 74;	
						}
						else if( addressing == BROADCAST_MODE )
						{							
							_maxSize = 92;	
						}							
					}
					else if( linkEncryption == ENABLED)
					{
						if( addressing == UNICAST_64B )
						{
							_maxSize = 66;	
						}
						else if( addressing == BROADCAST_MODE )
						{							
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
					_maxSize=MAX_FRAME;
					break;
			}
			break;
			
		case ENABLED: /// AES enabled //////////////////////////////////////////////
		
			switch (protocol)
			{				
				/// XBEE_802_15_4 ////////////////	
				case XBEE_802_15_4:
				
					if( linkEncryption == DISABLED)
					{						
						_maxSize = 93;		
					}
					else if( linkEncryption == ENABLED)
					{
						if( addressing == UNICAST_16B )
						{
							_maxSize = 93;	
						}
						else if( (addressing == UNICAST_64B) ||
								 (addressing == BROADCAST_MODE ) 	)
						{
							_maxSize = 77;	
						}				
					} 		
					break;
				
				/// ZIGBEE /////////////////////
				case ZIGBEE:
					
					if( addressing == UNICAST_64B )
					{
						_maxSize = 61;	
					}
					else if( addressing == BROADCAST_MODE )
					{							
						_maxSize = 77;	
					}							
						
					break;
				
				/// DIGIMESH /////////////////////					
				case DIGIMESH:
					
					_maxSize = 61;	
					break;
				
				/// XBEE_900 /////////////////////					
				case XBEE_900:
				
					if( linkEncryption == DISABLED)
					{							
						_maxSize = 93;								
					}
					else if( linkEncryption == ENABLED)
					{
						_maxSize = 77;						
					} 
						
					break;
				
				/// XBEE_868 /////////////////////					
				case XBEE_868:
					
					_maxSize = 93;								
					break;
					
				default :
					// No limit
					_maxSize=MAX_FRAME;
					break;
			}	
		
			break;
			
		default: // No limit
			_maxSize=MAX_FRAME;
			
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
 * createFrame (void) - Initialize frame buffer
 * 
 * Also, frame header bytes are initiliazed with deafult values
 * 
 */
void WaspFrame::createFrame(void)
{	
	// variable
	char MID[17];
	
	// get mote Identifier from EEPROM
	getID(MID);	
	
	// create default frame: ASCII mode, 
	createFrame(ASCII, MID);
	
}



/* 
 * createFrame () - Initialize frame buffer
 * 
 * Also, frame header bytes are initiliazed with default values
 * 
 */
void WaspFrame::createFrame(uint8_t mode, const char* moteID)
{	
	// local variables
	uint8_t sequence;
	
	// store mode: ASCII or BINARY
	_mode=mode;	
	
	// init buffer
	for( int i=0; i < MAX_DATA ; i++ )
	{
		buffer[i]='\0';
	}
	
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

		//! Queda tipo trama especial !//
	
		// set a "don't care" character in number of fields byte
		buffer[4]='?';
		
		// set the '#' separator
		buffer[5]='#';
		
		// set serial ID
		length=6;
		char str[16];		
		
		// _serial_id is read in main.cxx
		sprintf(str,"%lu",_serial_id);
		
		for( int i=0 ; i<strlen(str) ; i++ )
		{
			// break if end of string
			if( str[i] == '\0') 
			{
				break;
			}
			else
			{
				buffer[length]=str[i];
				length++;
			}
		}

		// set separator '#'
		buffer[length]='#';	
		length++;

		// set identifier
		for( int i=0 ; i<16 ; i++ )
		{
			// break if end of string
			if( moteID[i] == '\0') 
			{
				break;
			}
			else
			{
				buffer[length]=moteID[i];
				length++;
			}
		}

		// set separator '#'
		buffer[length]='#';	
		length++;

		// read and set the sequence number to the frame   
		sequence=readSequence();

		char seqStr[4];
		itoa(sequence, seqStr, 10);		
		strncat((char*)buffer, seqStr, strlen(seqStr));
		length += strlen(seqStr);
		buffer[length]='#';		
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
			buffer[3]= type;
		}
		
		// set a "don't care" character in number of fields byte
		buffer[4]='?';	
		
		// set serial ID
		// _serial_id is read in main.cxx				
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
		length=9;		

		// set identifier
		for( int i=0 ; i<16 ; i++ )
		{
			// break if end of string
			if( moteID[i] == '\0') 
			{
				break;
			}
			else
			{
				buffer[length]=moteID[i];
				length++;
			}
		}

		// set separator '#'
		buffer[length]='#';	
		length++;

		// read and set the sequence number to the frame   
		sequence=readSequence();
		buffer[length]=sequence;
		length++;

		sequence++;
		storeSequence(sequence);

	}
}


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
	USB.println(F("==============================="));
	if (_mode == ASCII)
	{
		USB.println(F("Current ASCII Frame: ")); 
	}
	else
	{
		USB.println(F("Current BINARY Frame: ")); 
	}
		
	USB.print(F("Length:  "));
	USB.println(length,DEC);	
	
	USB.print(F("Frame Type (decimal): "));	
	USB.println(buffer[3],DEC);
	

	USB.print(F("HEX:     "));
	for( int i= 0; i < length ; i++ )
	{
		USB.printHex(buffer[i]);
		USB.print(" ");
	}
	USB.println();

	USB.print(F("String:  "));
	for( int i= 0; i < length ; i++ )
	{
		USB.print(buffer[i]);
	}
	USB.println();	
	USB.println(F("==============================="));


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
				
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");		
		
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str, strlen(str));			
		strcat((char*)buffer, "#\0");
					
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
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
		// set sensor fields counter
		buffer[4]=numFields;

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
				
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");		
		
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str, strlen(str));			
		strcat((char*)buffer, "#\0");
					
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
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
		// set sensor fields counter
		buffer[4]=numFields;
		
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
		// convert from integer to string
		Utils.float2String(value, str, N);
		
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
	
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");	
	
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str, strlen(str));			
		strcat((char*)buffer, "#\0");	
		
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
		// set sensor fields counter
		buffer[4]=numFields;

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
	if(_mode == ASCII)
	{	
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
		
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");	
	
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str, strlen(str));			
		strcat((char*)buffer, "#\0");	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
	}
	else
	{
		// check if the data input type corresponds to the sensor	
		if(checkFields(type, TYPE_CHAR, 1) == -1 ) return -1;

		// set data bytes (in this case, string, one byte per char) & length (1 byte)
		int8_t lng = strlen(str);
		
		// check if new sensor value fits (id + nbytes + str)
		if(!checkLength(2+strlen(str)))
		{
			return -1;
		}

		// concatenate sensor name to frame string

        int len = length-2-strlen(str);
        buffer[len] = (char)type;
        buffer[len+1] = lng;
		for (int j=len+2;j<length;j++)
		{
			buffer[j] = str[j-2-len];
		}
		buffer[length] = '\0';

		// increment sensor fields counter 
		numFields++;
		// set sensor fields counter
		buffer[4]=numFields;
		
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
	int numDecimal=0;

	if(_mode == ASCII)
	{
		// get name of sensor from table
		char numDecimals;
		numDecimals =(uint8_t)pgm_read_word(&(DECIMAL_TABLE[type])); 
				
		// convert from integer to string
		Utils.float2String(val1, str1, numDecimals);
		Utils.float2String(val2, str2, numDecimals);

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
	
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");	
	
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str1, strlen(str1));	
		strcat((char *)buffer, ";");
		strncat((char*)buffer, str2, strlen(str2));	
		strcat((char*)buffer, "#\0");	
		
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
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
		// set sensor fields counter
		buffer[4]=numFields;

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
				
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");		
		
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str1, strlen(str1));
		strcat((char*)buffer, "-");				
		strncat((char*)buffer, str2, strlen(str2));
		strcat((char*)buffer, "-");		
		strncat((char*)buffer, str3, strlen(str3));
		strcat((char*)buffer, "#\0");
					
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
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
		// set sensor fields counter
		buffer[4]=numFields;

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
				
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");		
		
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str1, strlen(str1));
		strcat((char*)buffer, "-");				
		strncat((char*)buffer, str2, strlen(str2));
		strcat((char*)buffer, "-");		
		strncat((char*)buffer, str3, strlen(str3));
		if( val4>= 0 )
		{
			// if GMT is positive it is necessary to append a '+' character
			strcat((char*)buffer, "+");
		}
		strncat((char*)buffer, str4, strlen(str4));
		strcat((char*)buffer, "#\0");
					
		// increment sensor fields counter 
		numFields++;
		
		// set sensor fields counter
		buffer[4]=numFields;
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
		// set sensor fields counter
		buffer[4]=numFields;

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
				
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");		
		
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str1, strlen(str1));
		strcat((char*)buffer, ";");				
		strncat((char*)buffer, str2, strlen(str2));
		strcat((char*)buffer, ";");		
		strncat((char*)buffer, str3, strlen(str3));
		strcat((char*)buffer, "#\0");
					
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
		// set sensor fields counter
		buffer[4]=numFields;

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
		
		// convert from integer to string
		Utils.float2String(val1, str1, numDecimals);
		Utils.float2String(val2, str2, numDecimals);
		Utils.float2String(val3, str3, numDecimals);

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
	
		// concatenate sensor name to frame string		
		strncat((char*)buffer, name, strlen(name));		
		strcat((char*)buffer, ":");	
	
		// concatenate sensor value to frame string		
		strncat((char*)buffer, str1, strlen(str1));	
		strcat((char *)buffer, ";");
		strncat((char*)buffer, str2, strlen(str2));	
		strcat((char *)buffer, ";");
		strncat((char*)buffer, str3, strlen(str3));
		strcat((char*)buffer, "#\0");	
		
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
		// set sensor fields counter
		buffer[4]=numFields;

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
			USB.printf("ERR sensor type & value mismatch, %d vs %d \n",config, typeVal);
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
			USB.printf("ERR sensor type & value mismatch, %d vs %d \n",config, typeVal);
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





/*
 * setCloudCompatibility() - sends Waspmote unique ID with frame
 * 
 * Parameters:

 * 
 * Returns: 
 * 
 */
void WaspFrame::setCloudCompatibility()
{	
	// At the moment, this function only sends a dummy unique ID.
	// In the future will be more actions.
	
	
	// Waspmote Unique ID = 64 bit (6 Bytes)
	char uniqueID[7] =  "123456";
	
	// Here, unique ID should be read.
	// uniqueID = Utils.readSerial();
	
	
	// Now add it to frame
	
	// TO DO
	
	
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
	
	// set the mote ID from EEPROM memory
	for( int i=0 ; i<16 ; i++ )
	{		
		eeprom_write_byte((unsigned char *) i+MOTEID_ADDR, moteID[i]);
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
	
	// read mote ID from EEPROM memory
	for(int i=0 ; i<16 ; i++ )
	{
		moteID[i]=Utils.readEEPROM(i+MOTEID_ADDR);
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




/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspFrame frame = WaspFrame();

