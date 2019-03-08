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
 *  Version:		3.0
 *  Design:			Ahmad Saad
 */

#ifndef ADC_h
#define ADC_h

//!*************************************************************************************
//! Includes
//!*************************************************************************************
#include <inttypes.h>


//!*************************************************************************************
//! Defines
//!*************************************************************************************
// Comm. Register Codes to set up a read from data reg on second channel:
// spi_transfer(READ|DATA_REG|CH1)
#define DRDY_BIT	(7)
#define COMM_REG	(0x00)
#define SETUP_REG	(0x10)
#define CLOCK_REG	(0x20)
#define DATA_REG	(0x30)
#define OFFSET_REG	(0x60)
#define GAIN_REG	(0x70)
#define READ		(0x08)
#define WRITE	 	(0x00)
#define STBY		(0x04)
#define AIN1		(0x00)
#define AIN2		(0x01)

// Setup Reg. Codes
#define OP_NORMAL	(0x00)
#define OP_SELF_CAL	(0x40)
#define OP_ZS_CAL	(0x80)
#define OP_FS_CAL	(0xC0)
#define GAIN_1		(0x00)
#define GAIN_2		(0x08)
#define GAIN_4		(0x10)
#define GAIN_8		(0x18)
#define GAIN_16		(0x20)
#define GAIN_32		(0x28)
#define GAIN_64		(0x30)
#define GAIN_128	(0x38)
#define BIPOLAR		(0x00)
#define UNIPOLAR	(0x04)
#define BUF_ON		(0x02)
#define BUF_OFF		(0x00)
#define FSYNC		(0x01)
#define FSYNC_CLR	(0x00)

// Clock Reg. Codes
// These settings let it update at about 20hz
#define CLKDIS (0x00) // 00010000
#define CLKDIV (0x08) // 00001000
#define CLK    (0x04) // 00000100
#define FILTER (0x00) // 00000000

// Pin setup
#define CS_AD7705 DIGITAL1
#define DRDY DIGITAL6

#define timeOut 100


//!*************************************************************************************
//! Class declaration
//!*************************************************************************************
class adcClass
{
	
	public:

		adcClass();
		void begin();
		void configure(uint8_t CHANNEL);
		float readADC(uint8_t channel);
};

extern adcClass myADC;

#endif
