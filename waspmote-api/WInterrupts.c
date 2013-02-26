/*
 *  Part of the Wiring project - http://wiring.uniandes.edu.co
 *
 *  Copyright (c) 2004-05 Hernando Barragan
 * 
 *  Modified 24 November 2006 by David A. Mellis
 * 
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
 *  Version:		1.0
 *  Design:			David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa, David A. Mellis, Hernando Barragan, Manuel Calahorra
 */


#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "WConstants.h"
#include "WaspVariables.h"
#ifndef __WASPCONSTANTS_H__
  #include "WaspConstants.h"
#endif
#include "wiring_private.h"

// definition of interrupt vectors
volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];
volatile static voidFuncPtr twiIntFunc;


#if defined(__AVR_ATmega168__)
#define MCUCR EICRA
#define GICR EIMSK
#endif

/* attachInterrupt( interruptNum, userFunc, mode ) - attaches the interruption 
 * to the corresponding pin and subrutine
 *
 * It attaches the interruption to the corresponding microcontroller pin and 
 * subrutine associated to it.
 *
 * It returns nothing
 */
void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) 
{
  
	if(interruptNum < EXTERNAL_NUM_INTERRUPTS) 
	{
		intFunc[interruptNum] = userFunc;
    
		switch (interruptNum) 
		{
			
			case 0:	// INT0 connects to I2C_SCL
					// Configure the interrupt mode (trigger on low input, any 
					// change, rising edge, or falling edge).  The mode constants 
					// were chosen to correspond to the configuration bits in the 
					// hardware register, so we simply shift the mode into place.
					EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      
					// Enable the interrupt.
					EIMSK |= (1 << INT0);
					break;
			
			case 1:	// INT1 connects to I2C_SDA
					EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
					EIMSK |= (1 << INT1);
					break;
			
			case 2:	// INT2 is assigned to GPRS_RX in Wasp v5, this will allow 
					// waking up the processor on serial event from the GPRS
					EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
					EIMSK |= (1 << INT2);
					break;
        
			case 3:	// INT3 corresponds to GPRS_TX in Wasp v5, it could 
					// eventually be used in a configuration where we were not 
					// using the GPRS board
					EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
					EIMSK |= (1 << INT3);
					break;
        
			case 4:	// INT4 is connected to PE4 which is also PWM2 in Wasp v5, 
					// it could be used as a source for an external interrupt, 
					// since it is connected to the analog sensor port
					EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
					EIMSK |= (1 << INT4);
					break;
        
			case 5:	// this hardware interrupt is connected to EN_5V_PW in 
					// Wasp v5, therefore it will not be used as interrupt, 
					// since it has a completely different use it is commented 
					// away to avoid conflicts
					//EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
					//EIMSK |= (1 << INT5);
					break;
			
			case 6:	// INT6 is the interrupt at PE6 which in Wasp v5 corresponds 
					// to the accelerometer's RDY_ACC pin, we should activate it 
					// when willing to get signals from it
					EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
					EIMSK |= (1 << INT6);
					break;
			
			case 7:	// INT7 is the interrupt at PE7 which in Wasp v5 is 
					// connected to RST_RTC, or the watchdog from the RTC, 
					// therefore we will have to connect this pin when working 
					// with the external RTC
					EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
					EIMSK |= (1 << INT7);
					break;
		}
	}
}


/* detachInterrupt(interruptNum) - detaches the interruption from the corresponding pin
 *
 * It detaches the interruption from the corresponding microcontroller pin.
 *
 * It returns nothing
 */
void detachInterrupt(uint8_t interruptNum) 
{
	// Disable all interrupts by clearing the global interrupt mask. 
	cli();
	
	if(interruptNum < EXTERNAL_NUM_INTERRUPTS) 
	{
		switch (interruptNum) 
		{
			case 0:	// Disable the interrupt.
					EIMSK &= ~(1 << INT0);
					break;
					
			case 1:	EIMSK &= ~(1 << INT1);
					break;
					
			case 2:	EIMSK &= ~(1 << INT2);
					break;
			
			case 3: EIMSK &= ~(1 << INT3);
					break;
			
			case 4: EIMSK &= ~(1 << INT4);
					break;
			
			case 5: // this hardware interrupt is connected to EN_5V_PW in Wasp v5, therefore
					// it will not be used as interrupt, since it has a completely different use
					// it is commented away to avoid conflicts
					//EIMSK &= ~(1 << INT5);
					break;
        
			case 6:	EIMSK &= ~(1 << INT6);
					break;
        
			case 7:	EIMSK &= ~(1 << INT7);
					break;
		}
      
		intFunc[interruptNum] = 0;
	}
	
	// Enable interrupts by setting the global interrupt mask
	sei();
}

void attachInterruptTwi(void (*userFunc)(void) ) {
  twiIntFunc = userFunc;
}


SIGNAL(SIG_INTERRUPT0) {
  if(intFunc[EXTERNAL_INT_0])
    intFunc[EXTERNAL_INT_0]();
}

SIGNAL(SIG_INTERRUPT1) {
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}

SIGNAL(SIG_INTERRUPT2) {
  if(intFunc[EXTERNAL_INT_2])
    intFunc[EXTERNAL_INT_2]();
}

SIGNAL(SIG_INTERRUPT3) {
  if(intFunc[EXTERNAL_INT_3])
    intFunc[EXTERNAL_INT_3]();
}

SIGNAL(SIG_INTERRUPT4) {
  if(intFunc[EXTERNAL_INT_4])
    intFunc[EXTERNAL_INT_4]();
}

SIGNAL(SIG_INTERRUPT5) {
  if(intFunc[EXTERNAL_INT_5])
    intFunc[EXTERNAL_INT_5]();
}

SIGNAL(SIG_INTERRUPT6) {
  if(intFunc[EXTERNAL_INT_6])
    intFunc[EXTERNAL_INT_6]();
}

SIGNAL(SIG_INTERRUPT7) {
  if(intFunc[EXTERNAL_INT_7])
    intFunc[EXTERNAL_INT_7]();
}

/*SIGNAL(SIG_2WIRE_SERIAL) {
  if(twiIntFunc)
    twiIntFunc();
}*/


/* onHAIwakeUP(void) - setup the default interrupt for the High Activate Interrupts
 * 
 * It setups the default interrupt for the High Activate Interrupts. There are some modules that activates interruptions
 * on HIGH. These modules are Accelerometer, UART1 (GPRS) and other additional modules like sensors.
 *
 * This subrutine is executed when the interruption is detected on the corresponding microcontroller pin.
 *
 * We have to check 'intConf' flag and the monitorization pin, to know what module has activated the interruption, due to
 * more than one module is multiplexed on the same microcontroller pin. When the two conditions match, 'intFlag' is activated
 * on the correct position to show the module that has activated the interruption. 
 * A counter called 'intCounter' is incremented each time an interruption is detected. 
 * A counter array called 'intArray' is incremented in the correct position to know how many times a module has activated
 * the interruption.
 */
void onHAIwakeUP(void) 
{
	// Disable all interrupts by clearing the global interrupt mask. 
	cli();
	
	// used to update the interrupt flag
	if( intConf & ACC_INT )
	{	
		if( digitalRead(ACC_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= ACC_INT;
			intArray[ACC_POS]++;
		}
	}
	
	if( intConf & RTC_INT )
	{
		if( digitalRead(RTC_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= RTC_INT;
			intArray[RTC_POS]++;
		}
	}
	
	if( intConf & HAI_INT )
	{
		if( digitalRead(HAI_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= HAI_INT;
			intArray[HAI_POS]++;
		}
	}
	
	if( intConf & SENS_INT )
	{	
		if( digitalRead(SENS_INT_PIN_MON) )
		{
			intCounter++;
			digitalWrite(SENS_INT_ENABLE,LOW);
			intFlag |= SENS_INT;
			intArray[SENS_POS]++;
		}
	}
	if( intConf & XBEE_INT )
	{
		if( digitalRead(XBEE_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= XBEE_INT;
			intArray[XBEE_POS]++;
		}
	}
	
	if( intConf & PIR_3G_INT )
	{
		if( digitalRead(PIR_3G_PIN_MON) )
		{
			intCounter++;
			intFlag |= PIR_3G_INT;
			intArray[PIR_3G_POS]++;
		}
	}
	
	if( intConf & PLV_INT )
	{
		if( ( !(intConf & ACC_INT) || !digitalRead(ACC_INT_PIN_MON) ) && 
			( !(intConf & RTC_INT) || !digitalRead(RTC_INT_PIN_MON) ) && 
			( !(intConf & UART1_INT) || !digitalRead(UART1_INT_PIN_MON) )	)
		{
			intCounter++;
			intFlag |= PLV_INT;
			intArray[PLV_POS]++;
		}
	}
	
	// Enable interrupts by setting the global interrupt mask
	sei();
}

/* onLAIwakeUP(void) - setup the default interrupt for the Low Activate Interrupts
 * 
 * It setups the default interrupt for the Low Activate Interrupts. There are some modules that activates interruptions
 * on LOW. These modules are RTC, Low Battery, internal Watchdog and other additional modules like sensors.
 *
 * This subrutine is executed when the interruption is detected on the corresponding microcontroller pin.
 *
 * We have to check 'intConf' flag and the monitorization pin, to know what module has activated the interruption, due to
 * more than one module is multiplexed on the same microcontroller pin. When the two conditions match, 'intFlag' is activated
 * on the correct position to show the module that has activated the interruption. 
 * A counter called 'intCounter' is incremented each time an interruption is detected. 
 * A counter array called 'intArray' is incremented in the correct position to know how many times a module has activated
 * the interruption.
 */

void onLAIwakeUP(void) 
{
	// Disable all interrupts by clearing the global interrupt mask. 
	cli();
	
	// used to update the interrupt flag
	
	if( intConf & BAT_INT )
	{
		if( !digitalRead(BAT_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= BAT_INT;
			intArray[BAT_POS]++;
			disableInterrupts(BAT_INT);
		}
	}
	
	if( intConf & RAD_INT )
    {
        if( !digitalRead(RAD_INT_PIN_MON) )
        {
			
            intCounter++;
            intFlag |= RAD_INT;
            intArray[RAD_POS]++;
            disableInterrupts(RAD_INT);
        }
    }

	if( intConf & WTD_INT )
	{
		if( !digitalRead(WTD_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= WTD_INT;
			intArray[WTD_POS]++;
			digitalWrite(WTD_INT_PIN_MON,HIGH);
		}
	}
	
	if( intConf & UART1_INT )
	{
		if( digitalRead(UART1_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= UART1_INT;
			intArray[UART1_POS]++;
		}
	}

	if( intConf & LAI_INT )
	{
		if( !digitalRead(LAI_INT_PIN_MON) )
		{
			intCounter++;
			intFlag |= LAI_INT;
			intArray[LAI_POS]++;
		}
	}


	// Enable interrupts by setting the global interrupt mask
	sei();
}

/* clearIntFlag() - clears 'intFlag' global variable
 *
 */
void	clearIntFlag()
{
	intFlag=0;
}


/* enableInterrupts( conf ) - enables the specified interruption
 *
 * It enables the specified interruption by 'conf' input.
 *
 * When this function is called, 'intConf' flag is updated with the new active 
 * interruption. After that, it is attached to
 * the corresponding microcontroller pin and associated subrutine.
 */
void enableInterrupts(uint32_t conf)
{
	intConf |= conf;
		
	if( conf & HAI_INT )
	{
		pinMode(MUX_RX,INPUT);
		attachInterrupt(HAI_INT_ACT, onHAIwakeUP, HIGH);
	}
	if( conf & LAI_INT )
	{
		pinMode(MUX_TX, INPUT);
		attachInterrupt(LAI_INT_ACT, onLAIwakeUP, LOW);
	}
	if( conf & ACC_INT )
	{
		pinMode(MUX_RX,INPUT);
		pinMode(ACC_INT_PIN_MON, INPUT);
		attachInterrupt(ACC_INT_ACT, onHAIwakeUP, HIGH);
	}
	if( conf & BAT_INT )
	{
		pinMode(MUX_TX, INPUT);
		pinMode(BAT_INT_PIN_MON,INPUT);
		digitalWrite(MUX_TX, HIGH);
		attachInterrupt(BAT_INT_ACT, onLAIwakeUP, LOW);
	}	
	if( conf & RTC_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(RTC_INT_PIN_MON,INPUT);
		attachInterrupt(RTC_INT_ACT, onHAIwakeUP, HIGH);
	}
	if( conf & WTD_INT )
	{
		pinMode(WTD_INT_PIN_MON,OUTPUT);
		digitalWrite(WTD_INT_PIN_MON,HIGH);
		attachInterrupt(WTD_INT_ACT, onLAIwakeUP, LOW);
	}
	if( conf & UART1_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(UART1_INT_PIN_MON,INPUT);
		attachInterrupt(UART1_INT_ACT, onLAIwakeUP, LOW);
	}
	if( conf & SENS_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(SENS_INT_PIN_MON,INPUT);
		attachInterrupt(SENS_INT_ACT, onHAIwakeUP, HIGH);
	}
	if( conf & PLV_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(MUX_TX, INPUT);
		pinMode(SENS2_INT_PIN_MON,INPUT);
		pinMode(SENS2_INT_PIN2_MON,INPUT);
		attachInterrupt(PLV_INT_ACT, onLAIwakeUP, LOW);
	}
	
	if( conf & RAD_INT )
	{
		pinMode(RAD_INT_PIN_MON,INPUT);
        pinMode(MUX_TX, INPUT);
        attachInterrupt(RAD_INT_ACT, onLAIwakeUP, LOW);
	}
	
	if( conf & XBEE_INT )
	{
		pinMode(XBEE_INT_PIN_MON,INPUT);
        pinMode(MUX_RX, INPUT);
        attachInterrupt(XBEE_INT_ACT, onHAIwakeUP, HIGH);
	}
	
	if( conf & PIR_3G_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(PIR_3G_PIN_MON,INPUT);
		attachInterrupt(PIR_3G_INT_ACT, onHAIwakeUP, HIGH);
	}
}


/* disableInterrupts( conf ) - disables the specified interruption
 *
 * It disables the specified interruption by 'conf' input.
 *
 * When this function is called, 'intConf' flag is updated with the interruption that has been detached. After that, it is
 * deatached from the corresponding microcontroller pin and associated subrutine.
 */
void disableInterrupts(uint32_t conf)
{
	// Disable all interrupts by clearing the global interrupt mask. 
	cli();
	
	if( conf & HAI_INT )
	{
		detachInterrupt(HAI_INT_ACT);
	}
	if( conf & LAI_INT )
	{
		detachInterrupt(LAI_INT_ACT);
	}
	if( conf & ACC_INT )
	{
		detachInterrupt(ACC_INT_ACT);
	}
	if( conf & BAT_INT )
	{
		detachInterrupt(BAT_INT_ACT);
	}	
	if( conf & RTC_INT )
	{
		detachInterrupt(RTC_INT_ACT);
	}
	if( conf & UART1_INT )
	{
		detachInterrupt(UART1_INT_ACT);
	}
	if( conf & WTD_INT )
	{
		detachInterrupt(WTD_INT_ACT);
	}
	if( conf & SENS_INT )
	{
		detachInterrupt(SENS_INT_ACT);
	}
	if( conf & PLV_INT )
	{
		detachInterrupt(PLV_INT_ACT);
	}
	if( conf & XBEE_INT )
	{
		detachInterrupt(XBEE_INT_ACT);
	}
	if( conf & PIR_3G_INT )
	{
		detachInterrupt(PIR_3G_INT_ACT);
	}
	intConf &= ~(conf);
	
	// Enable interrupts by setting the global interrupt mask
	sei();
}
