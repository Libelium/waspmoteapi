/*! \file MCP23008.h
    \brief Library for managing library for the MCP23008 i2c port expander

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    These displays use I2C to communicate, 2 pins are required to
    interface. Adafruit invests time and resources providing this open
    source code, please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    Written by Limor Fried/Ladyada for Adafruit Industries.
    BSD license, all text above must be included in any redistribution

    Version:		3.0
    Design:			David Gascón
    Implementation: Javier Siscart, Víctor Boria

 */

 #ifndef MCP23008_H
 #define MCP23008_H

 /*******************************************************************************
  * Includes
  ******************************************************************************/
  #ifndef __WPROGRAM_H__
    #include <WaspClasses.h>
  #endif

  /*******************************************************************************
   * Definitions
   ******************************************************************************/

 #define MCP23008_ADDRESS 0x20

 // registers
 #define MCP23008_IODIR 0x00
 #define MCP23008_IPOL 0x01
 #define MCP23008_GPINTEN 0x02
 #define MCP23008_DEFVAL 0x03
 #define MCP23008_INTCON 0x04
 #define MCP23008_IOCON 0x05
 #define MCP23008_GPPU 0x06
 #define MCP23008_INTF 0x07
 #define MCP23008_INTCAP 0x08
 #define MCP23008_GPIO 0x09
 #define MCP23008_OLAT 0x0A


/*******************************************************************************
 * Class
 ******************************************************************************/

/*!
 * \class MCP23008
 * \brief class for Pin expansor
 */
class MCP23008
{
  private:
    uint8_t i2caddr;
    uint8_t read8(uint8_t addr);
    uint8_t write8(uint8_t addr, uint8_t data);

  public:

    MCP23008();                                 // Constructor

    uint8_t pinMode(uint8_t p, uint8_t d);
    uint8_t digitalWrite(uint8_t p, uint8_t d);
    uint8_t pullUp(uint8_t p, uint8_t d);
    uint8_t digitalRead(uint8_t p);
    uint8_t readGPIO(void);
    uint8_t writeGPIO(uint8_t);
};

#endif
