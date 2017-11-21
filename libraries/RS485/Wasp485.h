/*! \file Wasp485.h
    \brief Library for managing RS-485 module.
    
    Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		3.1
    Design:			David Gascón
    Implementation:	Ahmad Saad

 */
 
#ifndef Wasp485_h
#define Wasp485_h


/*******************************************************************************
 * Definitions 
 ******************************************************************************/

/*! 
 * \def DEBUG_RS485 
 * \brief Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_RS485	0
#define PRINT_RS485(str)	USB.print(F("[RS485] ")); USB.print(str);
#define PRINTLN_RS485(str)	USB.print(F("[RS485] ")); USB.println(str);



/******************************************************************************
* Register access masks in MAX3107
******************************************************************************/
#define RHR_REG				(0x00) /* RX FIFO */
#define THR_REG				(0x00) /* TX FIFO */
#define IRQEN_REG			(0x01) /* IRQ enable */
#define IRQSTS_REG			(0x02) /* IRQ status */
#define LSR_IRQEN_REG		(0x03) /* LSR IRQ enable */
#define LSR_IRQSTS_REG		(0x04) /* LSR IRQ status */
#define SPCHR_IRQEN_REG		(0x05) /* Special char IRQ enable */
#define SPCHR_IRQSTS_REG	(0x06) /* Special char IRQ status */
#define STS_IRQEN_REG		(0x07) /* Status IRQ enable */
#define STS_IRQSTS_REG		(0x08) /* Status IRQ status */
#define MODE1_REG			(0x09) /* MODE1 */
#define MODE2_REG			(0x0A) /* MODE2 */
#define LCR_REG				(0x0B) /* LCR */
#define RXTO_REG			(0x0C) /* RX timeout */
#define HDPIXDELAY_REG		(0x0D) /* Auto transceiver delays */
#define IRDA_REG			(0x0E) /* IRDA settings */
#define FLOWLVL_REG			(0x0F) /* Flow control levels */
#define FIFOTRIGLVL_REG		(0x10) /* FIFO IRQ trigger levels */
#define TXFIFOLVL_REG		(0x11) /* TX FIFO level */
#define RXFIFOLVL_REG		(0x12) /* RX FIFO level */
#define FLOWCTRL_REG		(0x13) /* Flow control */
#define XON1_REG			(0x14) /* XON1 character */
#define XON2_REG			(0x15) /* XON2 character */
#define XOFF1_REG			(0x16) /* XOFF1 character */
#define XOFF2_REG			(0x17) /* XOFF2 character */
#define GPIOCFG_REG			(0x18) /* GPIO config */
#define GPIODATA_REG		(0x19) /* GPIO data */
#define PLLCFG_REG			(0x1A) /* PLL config */
#define BRGCFG_REG			(0x1B) /* Baud rate generator conf */
#define BRGDIVLSB_REG		(0x1C) /* Baud rate divisor LSB */
#define BRGDIVMSB_REG		(0x1D) /* Baud rate divisor MSB */
#define CLKSRC_REG			(0x1E) /* Clock source */
#define REVID_REG			(0x1F) /* Revision identification */
						
						
/******************************************************************************
* Configuration Selection
******************************************************************************/

#define ENABLE  1
#define DISABLE 0
#define ONE_STOP_BIT 1
#define TWO_STOP_BITS 2


/******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef inttypes_h
	#include <inttypes.h>
#endif 

/******************************************************************************
 * Class
 ******************************************************************************/

class Wasp485
{
//**********************************************************************
// Public functions. 
//**********************************************************************
	
	public:

		//! Class Constructors
		Wasp485();

		//! Baud-Rate configuration. It sets the speed of communication.
		uint8_t baudRateConfig(unsigned long speed);
		 
		//!Enables or disables the parity bit.
		void parityBit(bool state);	 
		 
		//! Selects the number of stop bits.  
		void stopBitConfig(uint8_t numStopBits);
		
		//! Powers the 485 module and opens the SPI
		uint8_t  ON();

		//! Powers OFF the 485 module and closes the SPI
		void OFF(void);
		
		//! Receives data through the SPI.
		uint8_t read(void);

		//! Sends data n through the SPI.
		void send(uint8_t n);
		void send(int n);
		void send(unsigned int n);
		void send( long n);
		void send( unsigned long n);
		void send(long n, uint8_t base);
		
		//! Sends data through the SPI. It sends a string s.
		void send (const char *s);
		
		//! All register bits are reset to their reset state and all FIFOs are cleared.
		bool reset(void);
		 
		 //! Clear both the receive and transmit FIFOs of all data contents.
		void flush(void);
	
		//! Returns true when the buffer is empty.
		uint8_t available(void);
		
		//! Disable/Enable transmission.
		void transmission(bool state);
		 
		 //! Disable/Enable the receiver.
		void reception(bool state);

	private:

		//! Write data in the MAX3107 adress.
		void maxWrite(char address , char data);

		//! Read a data from the MAX3107.
		uint8_t maxRead(char address);	

		//! It prints an integer in a given base ( HEX,DEC,OCT,BYTE,BIN)
		void printIntegerInBase(unsigned long n , uint8_t base); 

};

extern Wasp485 W485;


#endif
