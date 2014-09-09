/*
 *  Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		1.1
 *  Design:			David Gascón
 *  Implementation:	Jim Studt, Alberto Bielsa, Yuri Carmona
 */
 

#ifndef __WPROGRAM_H__
//#include <WProgram.h>
#include <WaspClasses.h>
#endif

#include "WaspOneWire.h"


WaspOneWire::WaspOneWire( uint8_t pinArg)
{
    pin = pinArg;
    port = digitalPinToPort(pin);
    bitmask =  digitalPinToBitMask(pin);
    outputReg = portOutputRegister(port);
    inputReg = portInputRegister(port);
    modeReg = portModeRegister(port);
#if ONEWIRE_SEARCH
    reset_search();
#endif
}

//
// Perform the onewire reset function.  We will wait up to 250uS for
// the bus to come high, if it doesn't then it is broken or shorted
// and we return a 0;
//
// Returns 1 if a device asserted a presence pulse, 0 otherwise.
//
uint8_t WaspOneWire::reset() {
    uint8_t r;
    uint8_t retries = 125;
    unsigned long a = 0;

    // wait until the wire is high... just in case
    pinMode(pin,INPUT);
    a = millis();
    do {
		if ( retries-- == 0) return 0;
		delayMicroseconds(2); 
		if ( a > millis() )
		{
			a = millis();
		}
    } while( !digitalRead( pin) && ( (millis() - a) < 500 ) );
    
    pinMode(pin,OUTPUT);
    digitalWrite(pin,0);   // pull low for 500uS
    delayMicroseconds(500);
    pinMode(pin,INPUT);
    delayMicroseconds(65);
    r = !digitalRead(pin);
    delayMicroseconds(490);
    a = millis();
    while((r!=1) && ( (millis() - a) < 500 ) )
    {
		 r = !digitalRead(pin);
		 delayMicroseconds(10);
		if ( a > millis() )
		{
			a = millis();
		}
    }
    return r;
}

//
// Perform the onewire reset function.  We will wait up to 250uS for
// the bus to come high, if it doesn't then it is broken or shorted
// and we return a 0;
//
// Returns 1 if a device asserted a presence pulse, 0 otherwise.
//
uint8_t WaspOneWire::resetSerialID() {
    uint8_t r;
    uint8_t retries = 125;
    unsigned long a = 0;

    // wait until the wire is high... just in case
    pinMode(pin,INPUT);
    a = millis();
    do {
		if ( retries-- == 0) return 0;
		delayMicroseconds(2); 
		if ( a > millis() )
		{
			a = millis();
		}		
    } while( !digitalRead( pin) && ( (millis() - a) < 500 ) );
    
    pinMode(pin,OUTPUT);
    digitalWrite(pin,0);   // pull low for 500uS
    delayMicroseconds(400);
    a = millis();
    r = !digitalRead(pin);
    while( (r!=1) && ( (millis() - a) < 500 ) )
    {
		 r = !digitalRead(pin);
		 delayMicroseconds(10);
		if ( a > millis() )
		{
			a = millis();
		}
    }
    return r;
}

//
// Write a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
void WaspOneWire::write_bit(uint8_t v) {
    static uint8_t lowTime[] = { 55, 5 };
    static uint8_t highTime[] = { 5, 55};
    
    v = (v&1);
    *modeReg |= bitmask;  // make pin an output, do first since we
                          // expect to be at 1
    *outputReg &= ~bitmask; // zero
    delayMicroseconds(lowTime[v]);
    *outputReg |= bitmask; // one, push pin up - important for
                           // parasites, they might start in here
    delayMicroseconds(highTime[v]);
}

//
// Read a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
uint8_t WaspOneWire::read_bit() {
    uint8_t r;
    
    *modeReg |= bitmask;    // make pin an output, do first since we expect to be at 1
    *outputReg &= ~bitmask; // zero
    delayMicroseconds(1);
    *modeReg &= ~bitmask;     // let pin float, pull up will raise
    pinMode(pin,INPUT);
    digitalWrite(pin,1);
    delayMicroseconds(5-2);          // A "read slot" is when 1mcs > t > 2mcs
    r = ( *inputReg & bitmask) ? 1 : 0; // check the bit
    delayMicroseconds(50);        // whole bit slot is 60-120uS, need to give some time
    
    return r;
}

//
// Write a byte. The writing code uses the active drivers to raise the
// pin high, if you need power after the write (e.g. DS18S20 in
// parasite power mode) then set 'power' to 1, otherwise the pin will
// go tri-state at the end of the write to avoid heating in a short or
// other mishap.
//
void WaspOneWire::write(uint8_t v, uint8_t power) {
    uint8_t bitMask;
    
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {
	WaspOneWire::write_bit( (bitMask & v)?1:0);
    }
    if ( !power) {
	pinMode(pin,INPUT);
	digitalWrite(pin,0);
    }
}

//
// Read a byte
//
uint8_t WaspOneWire::read() {
    uint8_t bitMask;
    uint8_t r = 0;
    
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {
	if ( WaspOneWire::read_bit()) r |= bitMask;
    }
    return r;
}

//
// Do a ROM select
//
void WaspOneWire::select( uint8_t rom[8])
{
    int i;

    write(0x55,0);         // Choose ROM

    for( i = 0; i < 8; i++) write(rom[i],0);
}

//
// Do a ROM skip
//
void WaspOneWire::skip()
{
    write(0xCC,0);         // Skip ROM
}

void WaspOneWire::depower()
{
    pinMode(pin,INPUT);
}

#if ONEWIRE_SEARCH

//
// You need to use this function to start a search again from the beginning.
// You do not need to do it for the first search, though you could.
//
void WaspOneWire::reset_search()
{
    uint8_t i;
    
    searchJunction = -1;
    searchExhausted = 0;
    for( i = 7; ; i--) {
	address[i] = 0;
	if ( i == 0) break;
    }
}

//
// Perform a search. If this function returns a '1' then it has
// enumerated the next device and you may retrieve the ROM from the
// OneWire::address variable. If there are no devices, no further
// devices, or something horrible happens in the middle of the
// enumeration then a 0 is returned.  If a new device is found then
// its address is copied to newAddr.  Use OneWire::reset_search() to
// start over.
// 
uint8_t WaspOneWire::search(uint8_t *newAddr)
{
    uint8_t i;
    char lastJunction = -1;
    uint8_t done = 1;
    
    if ( searchExhausted) return 0;
    
    if ( !reset()) return 0;
    write( 0xf0, 0);
    
    for( i = 0; i < 64; i++) {
	uint8_t a = read_bit( );
	uint8_t nota = read_bit( );
	uint8_t ibyte = i/8;
	uint8_t ibit = 1<<(i&7);
	
	if ( a && nota) return 0;  // I don't think this should happen, this means nothing responded, but maybe if
	// something vanishes during the search it will come up.
	if ( !a && !nota) {
	    if ( i == searchJunction) {   // this is our time to decide differently, we went zero last time, go one.
		a = 1;
		searchJunction = lastJunction;
	    } else if ( i < searchJunction) {   // take whatever we took last time, look in address
		if ( address[ ibyte]&ibit) a = 1;
		else {                            // Only 0s count as pending junctions, we've already exhasuted the 0 side of 1s
		    a = 0;
		    done = 0;
		    lastJunction = i;
		}
	    } else {                            // we are blazing new tree, take the 0
		a = 0;
		searchJunction = i;
		done = 0;
	    }
	    lastJunction = i;
	}
	if ( a) address[ ibyte] |= ibit;
	else address[ ibyte] &= ~ibit;
	
	write_bit( a);
    }
    if ( done) searchExhausted = 1;
    for ( i = 0; i < 8; i++) newAddr[i] = address[i];
    return 1;  
}
#endif

#if ONEWIRE_CRC
// The 1-Wire CRC scheme is described in Maxim Application Note 27:
// "Understanding and Using Cyclic Redundancy Checks with Maxim iButton Products"
//

#if ONEWIRE_CRC8_TABLE
// This table comes from Dallas sample code where it is freely reusable, 
// though Copyright (C) 2000 Dallas Semiconductor Corporation
static uint8_t dscrc_table[] = {
      0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
     35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
    190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
     70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
    219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
     17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
     50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
     87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};

//
// Compute a Dallas Semiconductor 8 bit CRC. These show up in the ROM
// and the registers.  (note: this might better be done without to
// table, it would probably be smaller and certainly fast enough
// compared to all those delayMicrosecond() calls.  But I got
// confused, so I use this table from the examples.)  
//
uint8_t WaspOneWire::crc8( uint8_t *addr, uint8_t len)
{
    uint8_t i;
    uint8_t crc = 0;
    
    for ( i = 0; i < len; i++) {
	crc  = dscrc_table[ crc ^ addr[i] ];
    }
    return crc;
}
#else
//
// Compute a Dallas Semiconductor 8 bit CRC directly. 
//
uint8_t WaspOneWire::crc8( uint8_t *addr, uint8_t len)
{
    uint8_t i, j;
    uint8_t crc = 0;
    
    for (i = 0; i < len; i++) {
        uint8_t inbyte = addr[i];
        for (j = 0; j < 8; j++) {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
#endif

#if ONEWIRE_CRC16
static short oddparity[16] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };

//
// Compute a Dallas Semiconductor 16 bit CRC. I have never seen one of
// these, but here it is.
//
unsigned short WaspOneWire::crc16(unsigned short *data, unsigned short len)
{
    unsigned short i;
    unsigned short crc = 0;
    
    for ( i = 0; i < len; i++) {
	unsigned short cdata = data[len];
	
	cdata = (cdata ^ (crc & 0xff)) & 0xff;
	crc >>= 8;
	
	if (oddparity[cdata & 0xf] ^ oddparity[cdata >> 4]) crc ^= 0xc001;
	
	cdata <<= 6;
	crc ^= cdata;
	cdata <<= 1;
	crc ^= cdata;
    }
    return crc;
}
#endif

#endif

WaspOneWire Onewire = WaspOneWire(LED1);
