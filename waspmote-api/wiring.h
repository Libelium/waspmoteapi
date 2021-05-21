/*
 *  Modified for Waspmote by D. Cuartielles & A. Bielsa, 2009
 *	Modified for Waspmote, 2018
 * 
 *  Copyright (c) 2005-2006 David A. Mellis
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
 * 	Version:	3.1 
 */
 

#ifndef Wiring_h
#define Wiring_h

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "binary.h"

#ifdef __cplusplus
extern "C"{
#endif

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define PI 3.14159265
#define HALF_PI 1.57079
#define TWO_PI 6.283185

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )


// define MACROS in order to manage bits inside Bytes
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


typedef uint8_t boolean;
typedef uint8_t byte;

void init(void);

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);
void analogReference(uint8_t mode);
int analogRead(uint8_t);
void analogWrite(uint8_t, int);

void beginSerial(long, uint8_t);
void closeSerial(uint8_t);
void serialWrite(unsigned char, uint8_t);
int serialAvailable(uint8_t);
int serialRead(uint8_t);
void serialFlush(uint8_t);
void printMode(int, uint8_t);
void printByte(unsigned char c, uint8_t);
void printNewline(uint8_t);
void printString(const char *s, uint8_t);
void printInteger(long n, uint8_t);
void printHex(unsigned long n, uint8_t);
void printOctal(unsigned long n, uint8_t);
void printBinary(unsigned long n, uint8_t);
void printIntegerInBase(unsigned long n, unsigned long base, uint8_t);
void puthex(char ch, uint8_t portNum);

unsigned long millis(void);
unsigned long millisTim2(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
//void wait(unsigned long);
void wait(uint8_t);
void waitFor (uint8_t, uint8_t);
float pulseIn(uint8_t pin, uint8_t state);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val);

//////////////////////

// definition of interrupt vectors

//volatile uint16_t intFlag;

// main definition of interrupt functions

void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);
void enableInterrupts(uint32_t);
void disableInterrupts(uint32_t);

// default interrupt functions

void onHAIwakeUP(void);
void onLAIwakeUP(void);
void clearIntFlag();

//////////////////////

void wakeUpNowDefault(void);

void setup_watchdog(uint8_t);
void off_watchdog(void);

void setIPF_(uint8_t peripheral);
void resetIPF_(uint8_t peripheral); 

void setup(void);
void loop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
