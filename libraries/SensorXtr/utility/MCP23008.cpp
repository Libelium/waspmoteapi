/*! \file MCP23008.cpp
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

#include "MCP23008.h"

//! class constructor
MCP23008::MCP23008()
{
    // init variables
}

// Private Methods /////////////////////////////////////////////////////////////

/*!
* \brief Reads ony byte
* \param addr address to be read
* \return returns byte read
*/
uint8_t MCP23008::read8(uint8_t addr)
{
    uint8_t data;
    uint8_t error;
    I2C.begin();
    error = I2C.read(MCP23008_ADDRESS | i2caddr, addr, &data, 1);

    if (error != 0 )
    {
        #if DEBUG_AGR_XTR == 1
        PRINT_AGR_XTR("MCP Error:");
        USB.println(error,DEC);
        #endif
    }

    return data;

}

/*!
* \brief Writes one byte on pin expansor
* \param address address to write
* \param data data to write
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::write8(uint8_t addr, uint8_t data)
{
    uint8_t error;
    I2C.begin();
    error = I2C.write(MCP23008_ADDRESS | i2caddr, addr, data);

    if (error != 0 )
    {
        #if DEBUG_AGR_XTR == 1
        PRINT_AGR_XTR("MCP Error:");
        USB.println(error,DEC);
        #endif
    }
    return error;
}


// Public Methods //////////////////////////////////////////////////////////////

/*!
* \brief Used to change GPIO to input or output
* \param p pin to change state
* \param d desired state
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::pinMode(uint8_t p, uint8_t d)
{
    uint8_t iodir;

    // only 8 bits!
    if (p > 7)
    {
        return 1;
    }

    iodir = read8(MCP23008_IODIR);

    // set the pin and direction
    if (d == INPUT)
    {
        iodir |= 1 << p;
    }
    else
    {
        iodir &= ~(1 << p);
    }

    // write the new IODIR
    return write8(MCP23008_IODIR, iodir);
}

/*!
* \brief Reads state of a GPIO
* \param void
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::readGPIO(void)
{
    // read the current GPIO input
    return read8(MCP23008_GPIO);
}

/*!
* \brief Write into a GPIO
* \param GPIO to be written
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::writeGPIO(uint8_t gpio)
{
    return write8(MCP23008_GPIO, gpio);
}

/*!
* \brief Writes logic state on a GPIO
* \param p address to be written
* \param d state for the GPIO
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::digitalWrite(uint8_t p, uint8_t d)
{
    uint8_t gpio;

    // only 8 bits!
    if (p > 7)
    {
        return 1;
    }

    // read the current GPIO output latches
    gpio = readGPIO();

    // set the pin and direction
    if (d == HIGH)
    {
        gpio |= 1 << p;
    }
    else
    {
        gpio &= ~(1 << p);
    }

    // write the new GPIO
    return writeGPIO(gpio);
}

/*!
* \brief Set a GPIO as PULLUP
* \param p address to be written
* \param d state for the GPIO
* \return 0 if OK, error code otherwise
*/
uint8_t MCP23008::pullUp(uint8_t p, uint8_t d)
{
    uint8_t gppu;

    // only 8 bits!
    if (p > 7)
    {
        return 1;
    }

    gppu = read8(MCP23008_GPPU);
    // set the pin and direction
    if (d == HIGH)
    {
        gppu |= 1 << p;
    }
    else
    {
        gppu &= ~(1 << p);
    }
    // write the new GPIO
    return write8(MCP23008_GPPU, gppu);
}

/*!
* \brief Reads logic state of a GPIO
* \param p pin to be read
* \return Logic state of the GPIO
*/
uint8_t MCP23008::digitalRead(uint8_t p)
{
    // only 8 bits!
    if (p > 7)
    {
        return 1;   //FIX:
    }

    // read the current GPIO
    return (readGPIO() >> p) & 0x1;
}
