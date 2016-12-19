/*
 *  Copyright (c) 2005-2006 David A. Mellis
 *  Modified for Waspmote by Libelium, 2016
 
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
 *
 *
 */
 

#include "wiring_private.h"
#include "pins_waspmote.h"


uint8_t analog_reference = DEFAULT;


/*! 
 * @brief	This function sets the analog_reference for ADC conversion
 * @param 	uint8_t mode: Select the voltage reference selections for ADC
 * 	@arg	EXTERNAL: AREF, Internal VREF turned off
 * 	@arg	DEFAULT: AVCC with external capacitor at AREF pin
 * 	@arg	INTERNAL1V1: Internal 1V1 reference with capacitor at AREF pin
 * 	@arg	INTERNAL2V56: Internal 2V56 reference with capacitor at AREF pin
 * @return	void
 * 
 */
void analogReference(uint8_t mode)
{
	analog_reference = mode;
	
	// set Reference Selection bits
	if (analog_reference == INTERNAL2V56)
	{
		sbi(ADMUX, REFS1);
		sbi(ADMUX, REFS0);
	}
	else if (analog_reference == INTERNAL1V1)
	{		
		sbi(ADMUX, REFS1);
		cbi(ADMUX, REFS0);
	}
	else if (analog_reference == EXTERNAL)
	{		
		cbi(ADMUX, REFS1);
		cbi(ADMUX, REFS0);
	}
	else
	{	
		// DEFAULT	
		cbi(ADMUX, REFS1);
		sbi(ADMUX, REFS0);
	}
	
	// stabilization time
	delay(10);
}


/*! 
 * @brief	This function reads the analog pin
 * @param 	uint8_t pin: input analog pin to read from
 * 	@arg	ANALOG1
 * 	@arg	ANALOG2
 * 	@arg	ANALOG3
 * 	@arg	ANALOG4
 *	@arg	ANALOG5
 *	@arg	ANALOG6
 *	@arg	ANALOG7
 * @return	analog value in bits (from 0 to 1023) as it is using a 10-bit ADC
 * 
 */
int analogRead(uint8_t pin)
{
	uint8_t low, high, ch = analogInPinToBit(pin);

	// store channel previously set
	uint8_t channel = (ADMUX & (unsigned int) 0x0f);
	
	// enables the ADC
	sbi(ADCSRA, ADEN);
	
	// check if there is need to change the channel and wait for stabilization
	if( channel != ch )
	{
		// the low 4 bits of ADMUX select the ADC channel
		ADMUX = (ADMUX & (unsigned int) 0xf0) | (ch & (unsigned int) 0x0f);

		// without a delay, we seem to read from the wrong channel
		delay(1);		
	}

	// start the conversion. 
	sbi(ADCSRA, ADSC);

	// When the conversion is complete, ADSC bit 
	// (inside ADCSRA register) returns to zero.
	while (bit_is_set(ADCSRA, ADSC));

	// we have to read ADCL first; doing so locks both ADCL
	// and ADCH until ADCH is read.  reading ADCL second would
	// cause the results of each conversion to be discarded,
	// as ADCL and ADCH would be locked when it completed.
	low = ADCL;
	high = ADCH;

	// combine the two bytes
	return (high << 8) | low;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint8_t pin, int val)
{
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	
	if (digitalPinToTimer(pin) == TIMER1A) {
		// connect pwm to pin on timer 1, channel A
		sbi(TCCR1A, COM1A1);
		// set pwm duty
		OCR1A = val;
	} else if (digitalPinToTimer(pin) == TIMER1B) {
		// connect pwm to pin on timer 1, channel B
		sbi(TCCR1A, COM1B1);
		// set pwm duty
		OCR1B = val;
#if defined(__AVR_ATmega168__)
	} else if (digitalPinToTimer(pin) == TIMER0A) {
		// connect pwm to pin on timer 0, channel A
		sbi(TCCR0A, COM0A1);
		// set pwm duty
		OCR0A = val;	
	} else if (digitalPinToTimer(pin) == TIMER0B) {
		// connect pwm to pin on timer 0, channel B
		sbi(TCCR0A, COM0B1);
		// set pwm duty
		OCR0B = val;
	} else if (digitalPinToTimer(pin) == TIMER2A) {
		// connect pwm to pin on timer 2, channel A
		sbi(TCCR2A, COM2A1);
		// set pwm duty
		OCR2A = val;	
	} else if (digitalPinToTimer(pin) == TIMER2B) {
		// connect pwm to pin on timer 2, channel B
		sbi(TCCR2A, COM2B1);
		// set pwm duty
		OCR2B = val;
#elif defined(__AVR_ATmega1281__)
	} else if (digitalPinToTimer(pin) == TIMER0A) {
		// connect pwm to pin on timer 0, channel A
		sbi(TCCR0A, COM0A1);
		// set pwm duty
		OCR0A = val;	
	} else if (digitalPinToTimer(pin) == TIMER0B) {
		// connect pwm to pin on timer 0, channel B
		sbi(TCCR0A, COM0B1);
		// set pwm duty
		OCR0B = val;
	} else if (digitalPinToTimer(pin) == TIMER2A) {
		// connect pwm to pin on timer 2, channel A
		sbi(TCCR2A, COM2A1);
		// set pwm duty
		OCR2A = val;	
	} else if (digitalPinToTimer(pin) == TIMER2B) {
		// connect pwm to pin on timer 2, channel B
		sbi(TCCR2A, COM2B1);
		// set pwm duty
		OCR2B = val;
	} else if (digitalPinToTimer(pin) == TIMER3A) {
		// connect pwm to pin on timer 3, channel A
		sbi(TCCR3A, COM3A1);
		// set pwm duty
		OCR3A = val;	
	} else if (digitalPinToTimer(pin) == TIMER3B) {
		// connect pwm to pin on timer 3, channel B
		sbi(TCCR3A, COM3B1);
		// set pwm duty
		OCR3B = val;
#else
	} else if (digitalPinToTimer(pin) == TIMER2) {
		// connect pwm to pin on timer 2, channel B
		sbi(TCCR2, COM21);
		// set pwm duty
		OCR2 = val;
#endif
	} else if (val < 128)
		digitalWrite(pin, LOW);
	else
		digitalWrite(pin, HIGH);
}
