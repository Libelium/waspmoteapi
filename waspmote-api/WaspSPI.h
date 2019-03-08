/*! \file WaspSPI.h
    \brief Library for managing the SPI bus

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

    Version:		3.1
    Design:			David Gascón
    Implementation:	Alberto Bielsa, David Cuartielles

*/


/*! \def WaspSPI_h
    \brief The library flag
 */
#ifndef WaspSPI_h
#define WaspSPI_h

/******************************************************************************
 * Includes
 ******************************************************************************/



/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def SPI_CLOCK_DIV4
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/4
 */
/*! \def SPI_CLOCK_DIV16
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/16
 */
/*! \def SPI_CLOCK_DIV64
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/64
 */
/*! \def SPI_CLOCK_DIV128
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/128
 */
/*! \def SPI_CLOCK_DIV2
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/2
 */
/*! \def SPI_CLOCK_DIV8
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/8
 */
/*! \def SPI_CLOCK_DIV32
 \brief Constant to control the SCK rate of the device. SCK freq = fosc/32
 */
#define SPI_CLOCK_DIV4 		0x00
#define SPI_CLOCK_DIV16 	0x01
#define SPI_CLOCK_DIV64 	0x02
#define SPI_CLOCK_DIV128 	0x03
#define SPI_CLOCK_DIV2 		0x04
#define SPI_CLOCK_DIV8 		0x05
#define SPI_CLOCK_DIV32 	0x06


/*! SPI DATA MODES: There are four combinations of SCK phase and polarity with
respect to serial data, which are determined by control bits CPHA and CPOL. Data
bits are shifted out and latched in on opposite edges of the SCK signal,
ensuring sufficient time for data signals to stabilize.
*/
/*! \def SPI_MODE0
 \brief CPOL=0, CPHA=0
 */
/*! \def SPI_MODE1
 \brief CPOL=0, CPHA=1
 */
/*! \def SPI_MODE2
 \brief CPOL=1, CPHA=0
 */
/*! \def SPI_MODE3
 \brief CPOL=1, CPHA=1
 */
#define SPI_MODE0 			0x00
#define SPI_MODE1 			0x04
#define SPI_MODE2 			0x08
#define SPI_MODE3 			0x0C


#define SPI_MODE_MASK 		0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 		0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 	0x01  // SPI2X = bit 0 on SPSR

#define DUST_SENSOR_CS DIGITAL2
#define DUST_SENSOR_POWER DIGITAL1


/*! \def SD_SELECT
    \brief select SD on SPI bus
 */
/*! \def SOCKET0_SELECT
    \brief select SOCKET 0 on SPI bus
 */
/*! \def SOCKET1_SELECT
    \brief select SOCKET 1 on SPI bus
 */
/*! \def DUST_SENSOR_SELECT
    \brief select Particle sensor on SPI bus
 */
/*! \def SMART_WATER
    \brief select Smart Water Sensor Board on SPI bus
 */
/*! \def SMART_WATER_IONS
    \brief select Smart Water Ions Sensor Board on SPI bus
 */
 /*! \def SMART_AGR_XTR
     \brief select Smart AGR XTR Sensor Board on SPI bus
  */
/*! \def ALL_DESELECTED
    \brief deselect all devides on SPI bus
 */
enum spi_selection {
	SD_SELECT,
	SOCKET0_SELECT,
	SOCKET1_SELECT,
	DUST_SENSOR_SELECT,
	SMART_WATER_SELECT,
	SMART_IONS_SELECT,
	SMART_XTR_SELECT,
	ALL_DESELECTED,
};

/******************************************************************************
 * Class
 ******************************************************************************/


class WaspSPI
{

public:

	WaspSPI()
	{
		isSD = false;
		isSocket0 = false;
		isDustSensor = false;
		isSmartWater = false;
		isSmartWaterIons = false;
    isSmartAgrXtr = false;
	};

	static byte transfer(uint8_t _data);
	void transfer(const uint8_t* buf , size_t n);
	// SPI Configuration methods

	inline static void attachInterrupt();
	inline static void detachInterrupt(); // Default

	static void begin(); // Default
	static void end();
	void close();

	static void setBitOrder(uint8_t);
	static void setDataMode(uint8_t);
	static void setClockDivider(uint8_t);
	uint8_t receive();
	uint8_t receive(uint8_t* buf, size_t n);

	//! It selects the slave on SPI bus to use
	/*! Possibilities:
		SD_SELECT
		SRAM_SELECT
		SOCKET0_SELECT
		SOCKET1_SELECT
		ALL_DESELECTED
	\param uint8_t SELECTION : the selection
	\return void
	*/
	void setSPISlave(uint8_t SELECTION);

	void secureBegin();
	void secureEnd();

	//! Variable : indicates when SOCKET0 module is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean 	isSocket0;

	//! Variable : indicates when SD module is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean 	isSD;

	//! Variable : indicates when Dust Sensor is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean		isDustSensor;

	//! Variable : indicates when Smart Water is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean		isSmartWater;

	//! Variable : indicates when Smart Water Ions is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean		isSmartWaterIons;

  //! Variable : indicates when Smart Agriculture Xtreme is being powered on
  	/*! true: ON; false: OFF
   	*/
	boolean		isSmartAgrXtr;



};

extern WaspSPI SPI;

/*
 * attachInterrupt
 * When the SPE bit is written to one, the SPI is enabled.
 */
void WaspSPI::attachInterrupt()
{
  SPCR |= _BV(SPIE);
}


/*
 * detachInterrupt
 * Disable the SPI operations
 */
void WaspSPI::detachInterrupt()
{
  SPCR &= ~_BV(SPIE);
}


#endif
