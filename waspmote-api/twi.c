/*
 *  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
 *  Revised for Waspmote by Libelium, 2014-2018
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
 *  Version:		3.2
 *  Implementation:	N. Zambetti, A. Bielsa, Y. Carmona
 */
 

#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <string.h>

#include "WaspVariables.h"
#ifndef __WASPCONSTANTS_H__
  #include "WaspConstants.h"
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#include "twi.h"

static volatile uint8_t twi_state;
static volatile uint8_t twi_slarw;

static void (*twi_onSlaveTransmit)(void);
static void (*twi_onSlaveReceive)(uint8_t*, int);

static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_masterBufferIndex;
static uint8_t twi_masterBufferLength;

static uint8_t twi_txBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_txBufferIndex;
static volatile uint8_t twi_txBufferLength;

static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_rxBufferIndex;

static volatile uint8_t twi_error;

/* 
 * Function twi_init
 * Desc     readys twi pins and sets twi bitrate
 * Input    none
 * Output   none
 */
void twi_init(void)
{	
	// initialize state
	twi_state = TWI_READY;
	
	// re initialize TWI
	cbi(PRR0,PRTWI);

  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)
    // activate internal pull-ups for twi
    // as per note from atmega8 manual pg167
    sbi(PORTC, 4);
    sbi(PORTC, 5);
  #else
    // activate internal pull-ups for twi
    // as per note from atmega128 manual pg204
    // this also applies to mega1281
    sbi(PORTD, 0);
    sbi(PORTD, 1);
  #endif

	// initialize twi prescaler and bit rate
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2; 

	/* twi bit rate formula from atmega128 manual pg 204
	SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
	note: TWBR should be 10 or higher for master mode
	It is 72 for a 16mhz Wiring board with 100kHz TWI */

	// enable twi module, acks, and twi interrupt
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);	
	
	// clear buffers
	memset(twi_masterBuffer, 0x00, sizeof(twi_masterBuffer) );
	memset(twi_txBuffer, 0x00, sizeof(twi_txBuffer) );
	memset(twi_rxBuffer, 0x00, sizeof(twi_rxBuffer) );
}

/* 
 * Function twi_slaveInit
 * Desc     sets slave address and enables interrupt
 * Input    none
 * Output   none
 */
void twi_setAddress(uint8_t address)
{
  // set twi slave address (skip over TWGCE bit)
  TWAR = address << 1;
}

/* 
 * Function twi_readFrom
 * Desc     attempts to become twi bus master and read a
 *          series of bytes from a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes to read into array
 * Output   byte: 0 ok, 1 length too long for buffer
 */
uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length)
{
	uint8_t i;	

	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < length)
	{
		return 1;
	}
	
	// init timeout counter
	twi_tout(1);

	// wait until twi is ready, become master receiver
	while( TWI_READY != twi_state )
	{
		if (twi_tout(0)) break;
		continue;
	}
	twi_state = TWI_MRX;  
	
	// reset error state (0xFF: no error)
	twi_error = 0xFF;

	// initialize buffer iteration vars
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length;

	// build sla+w, slave device address + w bit
	twi_slarw = TW_READ;
	twi_slarw |= address << 1;

	// send start condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);

	// init timeout counter
	twi_tout(1);
	
	// wait for read operation to complete
	while( TWI_MRX == twi_state )
	{
		if (twi_tout(0)) break;
		continue;
	}

	// copy twi buffer to data
	for(i = 0; i < length; ++i)
	{
		data[i] = twi_masterBuffer[i];
	}
	
	return 0;
}

/* 
 * Function twi_writeTo
 * Desc     attempts to become twi bus master and write a
 *          series of bytes to a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes in array
 *          wait: boolean indicating to wait for write or not
 * Output   0 .. success
 *          1 .. length to long for buffer
 *          2 .. address send, NACK received
 *          3 .. data send, NACK received
 *          4 .. other twi error (lost bus arbitration, bus error, ..)
 */
uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait)
{
	uint8_t i;

	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < length)
	{
		return 1;
	}

	// init timeout counter
	twi_tout(1);

	// wait until twi is ready, become master transmitter
	while( TWI_READY != twi_state )
	{
		if (twi_tout(0)) break;
		continue;
	}
	twi_state = TWI_MTX;
	
	// reset error state (0xFF: no error)
	twi_error = 0xFF;
	
	// initialize buffer iteration vars
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length;
  
	// copy data to twi buffer
	for(i = 0; i < length; ++i)
	{
		twi_masterBuffer[i] = data[i];
	}
  
	// build sla+w, slave device address + w bit
	twi_slarw = TW_WRITE;
	twi_slarw |= address << 1;
  
	// send start condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);

	// init timeout counter
	twi_tout(1);
	
	// wait for write operation to complete
	while( wait && (TWI_MTX == twi_state) )
	{
		if (twi_tout(0)) return 5;
		continue;
	}
	
	if (twi_error == 0xFF)
		return 0;	// success
	else if (twi_error == TW_MT_SLA_NACK)
		return 2;	// error: address send, nack received
	else if (twi_error == TW_MT_DATA_NACK)
		return 3;	// error: data send, nack received
	else
		return 4;	// other twi error
}

/* 
 * Function twi_transmit
 * Desc     fills slave tx buffer with data
 *          must be called in slave tx event callback
 * Input    data: pointer to byte array
 *          length: number of bytes in array
 * Output   1 length too long for buffer
 *          2 not slave transmitter
 *          0 ok
 */
uint8_t twi_transmit(uint8_t* data, uint8_t length)
{
  uint8_t i;

  // ensure data will fit into buffer
  if(TWI_BUFFER_LENGTH < length){
    return 1;
  }
  
  // ensure we are currently a slave transmitter
  if(TWI_STX != twi_state){
    return 2;
  }
  
  // set length and copy data into tx buffer
  twi_txBufferLength = length;
  for(i = 0; i < length; ++i){
    twi_txBuffer[i] = data[i];
  }
  
  return 0;
}

/* 
 * Function twi_attachSlaveRxEvent
 * Desc     sets function called before a slave read operation
 * Input    function: callback function to use
 * Output   none
 */
void twi_attachSlaveRxEvent( void (*function)(uint8_t*, int) )
{
  twi_onSlaveReceive = function;
}

/* 
 * Function twi_attachSlaveTxEvent
 * Desc     sets function called before a slave write operation
 * Input    function: callback function to use
 * Output   none
 */
void twi_attachSlaveTxEvent( void (*function)(void) )
{
  twi_onSlaveTransmit = function;
}

/* 
 * Function twi_reply
 * Desc     sends byte or readys receive line
 * Input    ack: byte indicating to ack or to nack
 * Output   none
 */
void twi_reply(uint8_t ack)
{
	// transmit master read ready signal, with or without ack
	if(ack){
	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
  }else{
	  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
  }
}

/* 
 * Function twi_stop
 * Desc     relinquishes bus master status
 * Input    none
 * Output   none
 */
void twi_stop(void)
{
	// send stop condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

	// init timeout counter
	twi_tout(1);

	// wait for stop condition to be exectued on bus
	// TWINT is not set after a stop condition!
	while( TWCR & _BV(TWSTO) )
	{
		if (twi_tout(0)) break;
		continue;
	}

	// update twi state
	twi_state = TWI_READY;
}

/* 
 * Function twi_releaseBus
 * Desc     releases bus control
 * Input    none
 * Output   none
 */
void twi_releaseBus(void)
{
  // release bus
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);

  // update twi state
  twi_state = TWI_READY;
}

void twi_close()
{	
	// de-activate internal pull-up resistors: SDA and SCL pins set to '0'
	cbi(PORTD, 0); 
	cbi(PORTD, 1);	
	
	// set pre-scaler bits to 64 prescaler value
	sbi(TWSR, TWPS0);
	sbi(TWSR, TWPS1);
	
	// disable twi module, acks, and twi interrupt
	sbi(TWCR,TWINT);
	sbi(TWCR,TWSTO);
	cbi(TWCR,TWEA);
	cbi(TWCR,TWSTA);
	cbi(TWCR,TWWC);
	// switch off TWI depending on wether a sensor board is plugged or not
	if(		(WaspRegisterSensor & REG_GASES) 
		||	(WaspRegisterSensor & REG_CITIES_V14) 
		||	(WaspRegisterSensor & REG_PROTOTYPING) )
	{
		cbi(TWCR,TWEN);
	}
	else
	{
		sbi(TWCR,TWEN);
	}
	cbi(TWCR,TWIE);
	sbi(PRR0,PRTWI);
}


/* 
 * Function twi_tout
 * Desc     timeout function
 * Input    init: '1' for initializing. '0' for normal operation
 * Output   '1'-> timeout;  '0'-> OK
 */
static volatile uint32_t twi_toutc;
uint8_t twi_tout(uint8_t ini)
{
	if (ini) twi_toutc=0; else twi_toutc++;	
	if (twi_toutc>=100000UL) {
		twi_toutc=0;
		twi_init();
		return 1;
	}
  return 0;  
}


ISR(TWI_vect)
{
	/* http://www.nongnu.org/avr-libc/user-manual/group__util__twi.html
	 * #define TW_STATUS   (TWSR & TW_STATUS_MASK)
	 * #define TW_STATUS_MASK (_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|_BV(TWS3))
	 */
	
	switch(TW_STATUS)
	{
		/// All Master
		case TW_START:     // start condition transmitted
		case TW_REP_START: // repeated start condition transmitted
			// copy device address and r/w bit to output register and ack
			TWDR = twi_slarw;
			twi_reply(1);
			break;

		/// Master Transmitter - TW_MT_xxx 
		case TW_MT_SLA_ACK:  // slave receiver acked address
		case TW_MT_DATA_ACK: // slave receiver acked data
			// if there is data to send, send it, otherwise stop 
			if(twi_masterBufferIndex < twi_masterBufferLength)
			{
				// copy data to output register and ack
				TWDR = twi_masterBuffer[twi_masterBufferIndex++];
				twi_reply(1);
			}
			else
			{
				twi_stop();
			}
			break;
		case TW_MT_SLA_NACK:  // address sent, nack received
			twi_stop();
			twi_error = TW_MT_SLA_NACK;
			break;
		case TW_MT_DATA_NACK: // data sent, nack received
			twi_error = TW_MT_DATA_NACK;
			twi_stop();
			break;
		case TW_MT_ARB_LOST: // lost bus arbitration
			twi_error = TW_MT_ARB_LOST;
			twi_releaseBus();
			break;

		/// Master Receiver - TW_MR_xxx
		case TW_MR_DATA_ACK: // data received, ack sent
			// put byte into buffer
			twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
		case TW_MR_SLA_ACK:  // address sent, ack received
			// ack if more bytes are expected, otherwise nack
			if(twi_masterBufferIndex < twi_masterBufferLength)
			{
				twi_reply(1);
			}
			else
			{
				twi_reply(0);
			}
			break;
		case TW_MR_DATA_NACK: // data received, nack sent
			// put final byte into buffer
			twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
		case TW_MR_SLA_NACK: // address sent, nack received
			twi_stop();
			break;
		// TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

		/// Slave Receiver - TW_SR_xxx
		case TW_SR_SLA_ACK:   // addressed, returned ack
		case TW_SR_GCALL_ACK: // addressed generally, returned ack
		case TW_SR_ARB_LOST_SLA_ACK:   // lost arbitration, returned ack
		case TW_SR_ARB_LOST_GCALL_ACK: // lost arbitration, returned ack
			// enter slave receiver mode
			twi_state = TWI_SRX;
			// indicate that rx buffer can be overwritten and ack
			twi_rxBufferIndex = 0;
			twi_reply(1);
			break;
		case TW_SR_DATA_ACK:       // data received, returned ack
		case TW_SR_GCALL_DATA_ACK: // data received generally, returned ack
			// if there is still room in the rx buffer
			if(twi_rxBufferIndex < TWI_BUFFER_LENGTH)
			{
				// put byte in buffer and ack
				twi_rxBuffer[twi_rxBufferIndex++] = TWDR;
				twi_reply(1);
			}
			else
			{
				// otherwise nack
				twi_reply(0);
			}
			break;
		case TW_SR_STOP: // stop or repeated start condition received
			// put a null char after data if there's room
			if(twi_rxBufferIndex < TWI_BUFFER_LENGTH)
			{
				twi_rxBuffer[twi_rxBufferIndex] = '\0';
			}
			// callback to user defined callback
			twi_onSlaveReceive(twi_rxBuffer, twi_rxBufferIndex);
			// ack future responses
			twi_reply(1);
			// leave slave receiver state
			twi_state = TWI_READY;
			break;
		case TW_SR_DATA_NACK:       // data received, returned nack
		case TW_SR_GCALL_DATA_NACK: // data received generally, returned nack
			// nack back at master
			twi_reply(0);
			break;
    
		/// Slave Transmitter - TW_ST_xxx
		case TW_ST_SLA_ACK:          // addressed, returned ack
		case TW_ST_ARB_LOST_SLA_ACK: // arbitration lost, returned ack
			// enter slave transmitter mode
			twi_state = TWI_STX;
			// ready the tx buffer index for iteration
			twi_txBufferIndex = 0;
			// set tx buffer length to be zero, to verify if user changes it
			twi_txBufferLength = 0;
			// request for txBuffer to be filled and length to be set
			// note: user must call twi_transmit(bytes, length) to do this
			twi_onSlaveTransmit();
			// if they didn't change buffer & length, initialize it
			if(0 == twi_txBufferLength)
			{
				twi_txBufferLength = 1;
				twi_txBuffer[0] = 0x00;
			}
			// transmit first byte from buffer, fall
		case TW_ST_DATA_ACK: // byte sent, ack returned
			// copy data to output register
			TWDR = twi_txBuffer[twi_txBufferIndex++];
			// if there is more to send, ack, otherwise nack
			if(twi_txBufferIndex < twi_txBufferLength)
			{
				twi_reply(1);
			}else{
				twi_reply(0);
			}
			break;
		case TW_ST_DATA_NACK: // received nack, we are done 
		case TW_ST_LAST_DATA: // received ack, but we are done already!
			// ack future responses
			twi_reply(1);
			// leave slave receiver state
			twi_state = TWI_READY;
			break;

		/// All
		case TW_NO_INFO:   // no state information
			break;
		case TW_BUS_ERROR: // bus error, illegal stop/start
			twi_error = TW_BUS_ERROR;
			twi_stop();
			break;
	}
}
