/*! \file ADC.h
 *  \brief Library for managing the ADC of Smart Agriculture Extreme sensor board
 *
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Design:			Ahmad Saad, Javier Siscart.
 */

#ifndef ADC_h
#define ADC_h

//!*************************************************************************************
//! Includes
//!*************************************************************************************
#include <inttypes.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
#define XTR_ADC_CS 		DIGITAL3

//!*************************************************************************************
//! Class declaration
//!*************************************************************************************
class LTC
{

	public:

		LTC();
		void begin();
		float readADC(uint8_t channel);
};

#endif
