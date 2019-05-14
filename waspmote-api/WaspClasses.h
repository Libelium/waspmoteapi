/*
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
 *  Version:		3.2
 *  Design:			David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa, Yuri Carmona
 */
   
  
// strings and math
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// interrupts and sleep
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <alloca.h>

#include "pins_waspmote.h"
#include "WaspConstants.h"
#include "wiring.h"


#ifdef __cplusplus

#include "WaspUtils.h"
#include "WaspUSB.h"
#include "WaspRTC.h"
#include "WaspACC.h"
#include "WaspSD.h"
#include "WaspPWR.h"
#include "WaspXBeeCore.h"
#include "MemoryFree.h"
#include "WaspEEPROM.h"
#include "WaspOneWire.h"

// I2C library
#include "WaspI2C.h"


// SPI library
#include "WaspSPI.h"


// One wire library
#include "WaspOneWire.h"


#endif

