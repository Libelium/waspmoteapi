/*
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		0.12
 *  Design:		David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles
 */
  

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif


/*
 * Constructor
 */


void WaspSPI::begin() {
  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).

  pinMode(SD_SCK, OUTPUT);
  pinMode(SD_MOSI, OUTPUT);
  pinMode(SD_SS, OUTPUT);

  digitalWrite(SD_SCK, LOW);
  digitalWrite(SD_MOSI, LOW);
  digitalWrite(SD_SS, HIGH);

  // Warning: if the SS pin ever becomes a LOW INPUT then SPI 
  // automatically switches to Slave, so the data direction of 
  // the SS pin MUST be kept as OUTPUT.
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}

void WaspSPI::end() {
  SPCR &= ~_BV(SPE);
}

void WaspSPI::setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == LSBFIRST) {
    SPCR |= _BV(DORD);
  } else {
    SPCR &= ~(_BV(DORD));
  }
}

void WaspSPI::setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

void WaspSPI::setClockDivider(uint8_t rate)
{
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | (rate & SPI_2XCLOCK_MASK);
}

WaspSPI SPI = WaspSPI();
