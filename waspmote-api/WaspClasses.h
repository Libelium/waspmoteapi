/*
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.0
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
#include <avr/signal.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <alloca.h>

// HASH
#include "hash/md5.h"
#include "hash/md5_sbox.h"
#include "hash/sha1.h"
#include "hash/sha224.h"
#include "hash/sha256.h"
#include "hash/sha384.h"
#include "hash/sha512.h"
#include "hash/sha2_small_common.h"
#include "hash/sha2_large_common.h"

// AES
#include "aes/aes.h"

// RSA
#include "rsa/bignum.h"

// I2C libraries
#include "Wire.h"
#include "twi.h"

#include "pins_waspmote.h"
#include "WaspConstants.h"
#include "wiring.h"


#ifdef __cplusplus

#include "WaspUtils.h"
#include "HardwareSerial.h"
#include "WaspUSB.h"
#include "Wire.h"
#include "WaspRTC.h"
#include "WaspACC.h"
#include "WaspSD.h"
#include "WaspPWR.h"
#include "WaspXBeeCore.h"
#include "MemoryFree.h"
#include "WaspHash.h"
#include "WaspRSA.h"
#include "WaspAES.h"

// SPI library
#include "WaspSPI.h"


// Usb host library
#include "usbhost.h"
#include "max3421e.h"
#include "usb_ch9.h"
#include "Usb.h"
#include "usbhub.h"

#include "address.h"
#include "pgmstrings.h"

#include "parsetools.h"
#include "confdescparser.h"
#include "hidusagestr.h"
#include "hid.h"
#include "hidboot.h"
#include "message.h"

// Usb device library
#include "enum_data.h"

// One wire library
#include "WaspOneWire.h"

// random prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);

#endif

