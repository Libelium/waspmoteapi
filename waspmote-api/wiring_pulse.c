/*
 *  Copyright (c) 2005-2006 David A. Mellis
 *  Modified for Waspmote, 2016.
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
 * 	Version:	3.0 
 */
 
 
#include "wiring_private.h"
#include "pins_waspmote.h"

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 10 microseconds
 * to 3 minutes in length, but must be called at least N microseconds before
 * the start of the pulse. */
float pulseIn(uint8_t pin, uint8_t state)
{
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t stateMask = (state ? bit : 0);
	unsigned long width = 0; // keep initialization out of time critical area
	
	// wait for the pulse to start
	while ((*portInputRegister(port) & bit) != stateMask)
		;
	
	// wait for the pulse to stop
	while ((*portInputRegister(port) & bit) == stateMask)
		width++;

	// convert the reading to microseconds. The loop has been determined
	// to be 10 clock cycles long and have about 12 clocks between the edge
	// and the start of the loop. There will be some error introduced by
	// the interrupt handlers.
	float clockCyclesPerMicrosecond = (float)F_CPU / (float)1000000;	
	return (width * 10 + 12)/clockCyclesPerMicrosecond;
	
}
