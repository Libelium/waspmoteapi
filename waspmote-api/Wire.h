/*!
 *  @file 		Wire.h 
 *  @version	3.1
 *
 *  Modified for Waspmote by Libelium, 2009-2016
 *  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
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
 */
 

#ifndef TwoWire_h
#define TwoWire_h

#include <inttypes.h>

#define BUFFER_LENGTH 32

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled
 * 	2: verbose debug mode enabled
 */
#define DEBUG_I2C 0
// #define DEBUG_I2C 1
// #define DEBUG_I2C 2


// define print MACRO
#define PRINT_I2C(str)		USB.print(F("[I2C] ")); USB.print(str);


#define I2C_TIMEOUT		250			// timeout for I2C reads in milliseconds

//I2c addresses
#define I2C_ADDRESS_WASP_ACC			0x19
#define I2C_ADDRESS_WASP_RTC			0x68
#define I2C_ADDRESS_EVENTS_DIGIPOT1		0x28
#define I2C_ADDRESS_EVENTS_DIGIPOT2		0x2C
#define I2C_ADDRESS_EVENTS_DIGIPOT3		0x2A
#define I2C_ADDRESS_AGR_DENDROMETER		0x16
#define I2C_ADDRESS_AGR_PT1000			0x16
#define I2C_ADDRESS_AGR_RADIATION		0x14
#define I2C_ADDRESS_GASES_DIGIPOT1		0x2C
#define I2C_ADDRESS_GASES_DIGIPOT2		0x28
#define I2C_ADDRESS_GASES_DIGIPOT3		0x2E
#define I2C_ADDRESS_SENS_CITIES_DUST	0X2A
#define I2C_ADDRESS_CITIES_LD			0X28
#define I2C_ADDRESS_CITIES_AUDIO		0X2A
#define I2C_ADDRESS_CITIES_AUDIO_GAIN	0X2E
#define I2C_ADDRESS_CITIES_HUMIDITY		0X2F
#define I2C_ADDRESS_CITIES_TEMPERATURE	0X2C
#define I2C_ADDRESS_CITIES_ULTRA_5V		0X2F
#define I2C_ADDRESS_CITIES_ULTRA_3V3	0X2C
#define I2C_ADDRESS_CITIES_LDR			0X2C
#define I2C_ADDRESS_CITIES_CD			0X2C
#define I2C_ADDRESS_CITIES_CP			0X2C
#define I2C_ADDRESS_GASPRO_BME280		0x77
#define I2C_ADDRESS_GASPRO_LMP91000 	0x48
#define I2C_ADDRESS_GASPRO_MCP3421_A1	0x69
#define I2C_ADDRESS_GASPRO_MCP3421_A2	0x6A
#define I2C_ADDRESS_GASPRO_E2PROM		0x50
#define I2C_ADDRESS_GASPRO_MCP4146		0x2A
#define I2C_ADDRESS_EEPROM				0x55
#define I2C_ADDRESS_EEPROM_DEFAULT 		0x50
#define I2C_ADDRESS_TSL2561	 			0x39
#define I2C_ADDRESS_MB7040_MB1202		0x70
#define I2C_ADDRESS_GASES_SOCKET_1A_1B	0x28
#define I2C_ADDRESS_GASES_SOCKET_4		0x2A
#define I2C_ADDRESS_GASES_SOCKET_2A_2B	0x2C
#define I2C_ADDRESS_GASES_SOCKET_3_3B	0x2E

class TwoWire
{
  private:
  	bool _5V_ON;
	bool _3V3_ON;
	
    static uint8_t rxBuffer[BUFFER_LENGTH];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[BUFFER_LENGTH];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);
  
	unsigned long readTimeout;	// I2C timeout
  
  public:
    TwoWire();
    
    //! Variable : indicates when I2C bus is ON (1) or OFF (0)
    uint8_t isON;
    
    //! Variable : indicates when Sensor Board is being powered on
  	/*! true: ON; false: OFF
   	*/
	bool isBoard;
	
    void begin();
    void begin(uint8_t);
    void begin(int);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);    
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    void send(uint8_t);
    void send(uint8_t*, uint8_t);
    void send(int);
    void send(char*);
    uint8_t available(void);
    uint8_t receive(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );
    void close();

	
    void secureBegin();
    void secureEnd();
	
	
	//! This function writes a bit via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: data to send
	\param uint8_t pos: position of the bit to write [7|6|5|4|3|2|1|0]
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos);
	
	//! This function writes some bits via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: data to send
	\param uint8_t pos: first position of the bits to write starting by the LSb [7|6|5|4|3|2|1|0]
	\param uint8_t length: number of bits to write
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos, uint8_t length);

	//! This function writes byte via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: data to send
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
	
	//! This function writes bytes via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t *data: data to send
	\param uint8_t length: number of bytes to write
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length);
	
	//! This function reads a bit via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t *data: buffer to store the data
	\param uint8_t pos: position of the bit to read [7|6|5|4|3|2|1|0]
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos);
	
	//! This function reads some bits via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: buffer to store the data
	\param uint8_t pos: first position of the bits to read starting by the LSb [7|6|5|4|3|2|1|0]
	\param uint8_t length: number of bits to read
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos, uint8_t length);
	
	//! This function reads a byte via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: buffer to store the data
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
	
	//! This function reads bytes via I2C
	/*!
	\param uint8_t devAddr: I2C address of the device
	\param uint8_t regAddr: I2C register
	\param uint8_t data: buffer to store the data
	\param uint8_t length: number of bytes to read
	\return		0 if OK
				1 if length to long for buffer
				2 if address send, NACK received
				3 if data send, NACK received
				4 if other twi error (lost bus arbitration, bus error, ..)
 				5 if timeout
	*/
	int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length);

	
};

extern TwoWire Wire;

#endif

