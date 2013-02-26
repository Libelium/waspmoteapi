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
 *  Version:		0.1
 *  Design:		David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa
 */
 

#include <inttypes.h>
#ifndef __WASPCONSTANTS_H__
#include "WaspConstants.h"
#endif 

/* EPR - Existing Peripheral Registers
 * contain information about which peripherals are
 * installed in the Wasp, the information should be
 * stored in the EEPROM coming from the factory
 */

// EPRA contains LSB - PGPS|PSD|PACC|PXBEE|PRTC|PUSB|PSID|PSLOW_CLK - MSB
uint8_t EPRA = 0;

// EPRB contains LSB - PGPRS|XX|XX|XX|XX|XX|XX|XX - MSB
uint8_t EPRB = 0;

// Functions to read and test peripherals

// readEPRA copies the values from the EEPROM into the EEPRA register
// answers 0 for normal operation
uint8_t readEPRA() {
}

// readEPRB copies the values from the EEPROM into the EEPRB register
// answers 0 for normal operation
uint8_t readEPRB() {
}

// testPeripherals checks whether the information in the EEPROM corresponds
// to the peripherals on the board through running a test on each one of them
// the different test functions will print directly to the USB and one LED will
// show through quick blinking if there was an error
uint8_t testPeripherals() {
}
