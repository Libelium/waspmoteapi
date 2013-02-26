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
 
 
// EPRA contains LSB - PGPS|PSD|PACC|PXBEE|PRTC|PUSB|PSID|PSLOW_CLK - MSB
uint8_t EPRA;

// EPRB contains LSB - PGPRS|XX|XX|XX|XX|XX|XX|XX - MSB
uint8_t EPRB;

// Functions to read and test peripherals
uint8_t readEPRA() {};
uint8_t readEPRB() {};
uint8_t testPeripherals() {};
