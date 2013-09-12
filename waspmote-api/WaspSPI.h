/*! \file WaspUtils.h
    \brief Library containing useful general functions
    
    Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
    Implementation:	Alberto Bielsa, David Cuartielles

*/
  
  
/*! \def Wasputils_h
    \brief The library flag
    
 */
#ifndef WaspSPI_h
#define WaspSPI_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
//#include <stdio.h>
//#include <WProgram.h>
//#include <avr/pgmspace.h>
//#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

/******************************************************************************
 * Class
 ******************************************************************************/
 

class WaspSPI
{
 public:

WaspSPI(){};
 
 inline static byte transfer(byte _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin(); // Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);

};

extern WaspSPI SPI;

byte WaspSPI::transfer(byte _data) {
  SPDR = _data;
  while (!(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}

void WaspSPI::attachInterrupt() {
  SPCR |= _BV(SPIE);
}

void WaspSPI::detachInterrupt() {
  SPCR &= ~_BV(SPIE);
}


#endif
