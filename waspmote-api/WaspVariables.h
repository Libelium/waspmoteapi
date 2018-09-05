/*! \file WaspVariables.h
    \brief General variables used through the libraries
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		3.0
    Design:			David Gascón
    Implementation:	Alberto Bielsa, David Cuartielles

 */
 
/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def intFlag
    \brief Flag used for storing the modules that have generated an interruption
 */
/*! \def intConf
    \brief Flag used for storing the modules that are enabled to generate an interruption
 */
/*! \def intCounter
    \brief Flag that stores the number of interruptions have been generated
 */
/*! \def intArray
    \brief Flag used for storing the number of times each different kind of interruption has been generated
 */

volatile	uint16_t 	intFlag;
volatile	uint16_t	intConf;

volatile 	uint8_t	intCounter;
volatile 	uint8_t	intArray[8];

/*! \def WaspRegister
    \brief Bitmap used for managing the different modules and power supplies 
    by different libraries
 */
volatile uint16_t WaspRegister;
volatile uint16_t WaspRegisterSensor;

/*! \def pwrGasRegister
    \brief Bitmap used for managing the power supply for Gases PRO board	
    0: dust sensor
	1: gas sensor on socket 1 or C
	2: gas sensor on socket 2
	3: gas sensor on socket 3 or F
	4: gas sensor on socket 4 or A
	5: gas sensor on socket 5 or B
	6: gas sensor on socket 6
 */
volatile uint8_t	pwrGasPRORegister;

volatile uint8_t	pwrCitiesPRORegister;


