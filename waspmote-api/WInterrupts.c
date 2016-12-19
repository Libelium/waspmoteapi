/*
 *  Part of the Wiring project - http://wiring.uniandes.edu.co
 *
 *  Copyright (c) 2004-05 Hernando Barragan
 *  Modified 24 November 2006 by David A. Mellis
 * 	Revised for Waspmote by Libelium, 2016
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
 *  Design:			David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa, David A. Mellis, Hernando Barragan, Manuel Calahorra
 */


#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
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
extern volatile uint8_t _boot_version;


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
 * Observe that, if enabled, the interrupts will trigger even if the INT7:0 or 
 * PCINT23:0 pins are configured as outputs
 * 
 * The External Interrupts can be triggered by a falling or rising edge or a low 
 * level. This is set up as indicated in the specification for the External 
 * Interrupt Control Registers – EICRA (INT3:0) and EICRB (INT7:4).
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
			
			case 0:	// INT0 connects to I2C_SCL (not used as interrupt pin in Waspmote)
					// Configure the interrupt mode (trigger on low input, any 
					// change, rising edge, or falling edge).  The mode constants 
					// were chosen to correspond to the configuration bits in the 
					// hardware register, so we simply shift the mode into place.
					EIMSK &= ~(1 << INT0);
					EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
					EIFR  |= (1 << INT0);
					EIMSK |= (1 << INT0);
					break;
			
			case 1:	// INT1 connects to I2C_SDA (not used as interrupt pin in Waspmote)
					EIMSK &= ~(1 << INT1);
					EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
					EIFR  |= (1 << INT1);
					EIMSK |= (1 << INT1);
					break;
			
			case 2:	// INT2 is assigned to MUX_RX
					// This means the interruption pin is shared with the UART1
					// RX pin
					EIMSK &= ~(1 << INT2);					
					EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
					EIFR  |= (1 << INT2);
					EIMSK |= (1 << INT2);
					break;
        
			case 3:	// INT3 is assigned to MUX_TX
					// This means the interruption pin is shared with the UART1
					// TX pin
					EIMSK &= ~(1 << INT3);	
					EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
					EIFR  |= (1 << INT3);
					EIMSK |= (1 << INT3);
					break;
        
			case 4:	// INT4 pin is connected to DIGITAL0 pin (RESERVED pin!!) 
					// DIGITAL0 pin is used by the Watchdog timer to simulate a 
					// hardware interruption. So when the Watchdog interrupts, 
					// the inner subroutine sets this pin to high level to 
					// indicate this interrption arrived and this is the way to
					// distinguish this interruption from others.
					EIMSK &= ~(1 << INT4);	
					EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
					EIFR  |= (1 << INT4);
					EIMSK |= (1 << INT4);
					break;
        
			case 5:	// INT5 pin is used to enable the 5v power supply
					// Therefore it will not be used as interruption pin, 
					// since it has a completely different use it is commented 
					// to avoid conflicts
					//EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
					//EIMSK |= (1 << INT5);
					break;
			
			case 6:	// INT6 pin is used as the ACC_INT monitorization pin
					// Corresponds to the accelerometer's RDY_ACC pin
					// Therefore it will not be used as interruption pin, 
					// since it has a completely different use it is commented 
					// to avoid conflicts
					//EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
					//EIMSK |= (1 << INT6);
					break;
			
			case 7:	// INT7 pin is used as the RTC_INT monitorization pin
					// Therefore it will not be used as interruption pin, 
					// since it has a completely different use it is commented 
					// to avoid conflicts					
					//EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
					//EIMSK |= (1 << INT7);
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


ISR(INT0_vect) 
{
  if(intFunc[EXTERNAL_INT_0])
    intFunc[EXTERNAL_INT_0]();
}


ISR(INT1_vect)
{
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}


ISR(INT2_vect) 
{
	sleep_disable();
  if(intFunc[EXTERNAL_INT_2])
    intFunc[EXTERNAL_INT_2]();
}


ISR(INT3_vect) 
{
	sleep_disable();
  if(intFunc[EXTERNAL_INT_3])
    intFunc[EXTERNAL_INT_3]();
}


ISR(INT4_vect) 
{
  if(intFunc[EXTERNAL_INT_4])
    intFunc[EXTERNAL_INT_4]();
}


ISR(INT5_vect) 
{
  if(intFunc[EXTERNAL_INT_5])
    intFunc[EXTERNAL_INT_5]();
}


ISR(INT6_vect) 
{
  if(intFunc[EXTERNAL_INT_6])
    intFunc[EXTERNAL_INT_6]();
}


ISR(INT7_vect) 
{
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
		if (_boot_version >= 'G')
		{		
			// check monitorization pin
			if( !(digitalRead(PLV_INT_PIN_MON_V30)))
			{				
				intCounter++;
				intFlag |= PLV_INT;
				intArray[PLV_POS]++;					
			}
		}
		else
		{
			if( !(digitalRead(PLV_INT_PIN_MON)))
			{				
				intCounter++;
				intFlag |= PLV_INT;
				intArray[PLV_POS]++;					
			}
			
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

	// Enable interrupts by setting the global interrupt mask
	sei();
}

/* clearIntFlag() - clears 'intFlag' global variable
 *
 */
void clearIntFlag()
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

	if( conf & ACC_INT )
	{
		pinMode(MUX_RX,INPUT);
		pinMode(ACC_INT_PIN_MON, INPUT);
		attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}	
	if( conf & RTC_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(RTC_INT_PIN_MON,INPUT);
		attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}
	if( conf & WTD_INT )
	{
		pinMode(WTD_INT_PIN_MON,OUTPUT);
		digitalWrite(WTD_INT_PIN_MON,HIGH);
		attachInterrupt(INT4_PIN, onLAIwakeUP, FALLING);
	}
	if( conf & SENS_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(SENS_INT_PIN_MON,INPUT);
		attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}
	if( conf & PLV_INT )
	{	
		pinMode(MUX_RX,INPUT);
		attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}
	
	if( conf & RAD_INT )
	{
		pinMode(RAD_INT_PIN_MON,INPUT);
        pinMode(MUX_TX, INPUT);
		digitalWrite(MUX_TX, HIGH);	
        attachInterrupt(TXD1_PIN, onLAIwakeUP, FALLING);
	}
	
	if( conf & XBEE_INT )
	{
		pinMode(XBEE_INT_PIN_MON,INPUT);
        pinMode(MUX_RX, INPUT);
        attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}
	
	if( conf & PIR_3G_INT )
	{
		pinMode(MUX_RX, INPUT);
		pinMode(PIR_3G_PIN_MON,INPUT);
		attachInterrupt(RXD1_PIN, onHAIwakeUP, RISING);
	}

}


/* disableInterrupts( conf ) - disables the specified interruption
 *
 * It disables the specified interruption by 'conf' input.
 *
 * When this function is called, 'intConf' flag is updated with the interruption 
 * that has been detached. After that, it is detached from the corresponding 
 * microcontroller pin and associated subrutine.
 */
void disableInterrupts(uint32_t conf)
{
	// Disable all interrupts by clearing the global interrupt mask. 
	cli();	

	if( conf & ACC_INT )
	{
		detachInterrupt(RXD1_PIN);
	}	
	if( conf & RTC_INT )
	{
		detachInterrupt(RXD1_PIN);
	}
	if( conf & WTD_INT )
	{
		detachInterrupt(INT4_PIN);
	}
	if( conf & SENS_INT )
	{
		detachInterrupt(RXD1_PIN);
	}
	if( conf & PLV_INT )
	{
		detachInterrupt(RXD1_PIN);
	}
	if( conf & XBEE_INT )
	{
		detachInterrupt(RXD1_PIN);
	}
	if( conf & PIR_3G_INT )
	{
		detachInterrupt(RXD1_PIN);
	}
	if( conf & RAD_INT )
	{
		detachInterrupt(TXD1_PIN);
	}
	intConf &= ~(conf);
	
	// Enable interrupts by setting the global interrupt mask
	sei();
}
