/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	Marcos Yarza, Javier Siscart
 */
 
 
#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspSensorRadiation.h"

// Constructors //

/*				
 Function: Constructor
 Returns: 
 Parameters: 	
 Values: 
*/
WaspRadiationBoard::WaspRadiationBoard()
{

	// Initializes some variables
	count = 0;
	timePrevious = 0;
	time = 0;
	timePreviousMeassure = 0;
	radiationValue = 0.0;
	//ledArray = {DIGITAL8,DIGITAL6,DIGITAL4,DIGITAL2,DIGITAL3};
	ledArray[0] = DIGITAL8;
	ledArray[1] = DIGITAL6;
	ledArray[2] = DIGITAL4;
	ledArray[3] = DIGITAL2;
	ledArray[4] = DIGITAL3;
	
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_RADIATION;

}

// public methods

/*
 Function: Turns on radiation board
 Returns: 
 Parameters: 
 Values: 
*/
void WaspRadiationBoard::ON()
{	
	// switch on the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	PWR.setSensorPower(SENS_5V, SENS_ON);
  	delay(1000);
  	
  	init();
}

/*
 Function: Turns off radiation board
 Returns: 
 Parameters: 
 Values: 
*/
void WaspRadiationBoard::OFF()
{	
	// switch off the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	disableInterrupts(RAD_INT);
}

/*
 Function: enable interrupts and blinks led bar.
 Returns: 
 Parameters: 
 Values: 
*/
void WaspRadiationBoard::init()
{

	// configure led bar pins
  	for (int i=0;i<5;i++){
    		pinMode(ledArray[i],OUTPUT);
  	}

	// Blink led bar one time
	ledBar(1000);
	delay(1000);
	ledBar(0);

}




/*
 Function: Measures actual radiation value during 10 seconds without interruptions.
 Returns: 
	radiationValue: Returns value of radiation in uSv/H
 Parameters: 
 Values: 
*/
float WaspRadiationBoard::getRadiation()
{
	count = 0;
	time = millis();
	
	while (millis()-time < 10000)
	{
		if(digitalRead(RAD_INT_PIN_MON) == 0)
		{
			count++;
			while(digitalRead(RAD_INT_PIN_MON) == 0); // do nothing until pin goes back to HIGH
		}
		if( millis() < time )
		{
			count = 0;
			time = millis();
		}
	}
	radiationValue = 6.0 * count * CONV_FACTOR;

	return radiationValue;

}


/*
 Function: Measures actual radiation value during 10 seconds.
 Returns: 
	radiationValue: Returns value of radiation in uSv/H
 Parameters: 
 Values: 
*/
float WaspRadiationBoard::getRadiationInt()
{

	unsigned long timeRepeat= 10000;        
	unsigned long previous=millis();

	enableInterrupts(RAD_INT);

	
	while( (millis()-previous<timeRepeat) )
	{
		if( intFlag & RAD_INT){
			disableInterrupts(RAD_INT);
			intFlag &= ~(RAD_INT);
			countPulse();

			while(!digitalRead(RAD_INT_PIN_MON));
				enableInterrupts(RAD_INT);
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous = millis();
	}

	radiationValue = 6.0 *count * CONV_FACTOR;
	timePreviousMeassure = millis();
	ledBar(6*count);  
	count = 0;

	return radiationValue;
}



/*
 Function: Measures actual radiation value during specified time. Maximum measure time is 60 seconds
 Returns: 
	radiationValue: Returns value of radiation in uSv/H
 Parameters: 
	time: time while radiation is measured. Time units must be milliseconds
 Values: 
*/
float WaspRadiationBoard::getRadiationInt(long time)
{

	float k=0;      //used to obtain CPM
	float minute = 60000;
	unsigned long previous=millis();

	enableInterrupts(RAD_INT);

	while( (millis()-previous<time) )
    {
		if( intFlag & RAD_INT){
			disableInterrupts(RAD_INT);
			intFlag &= ~(RAD_INT);
			countPulse();

			while(!digitalRead(RAD_INT_PIN_MON));
    			enableInterrupts(RAD_INT);
  		}
    
    		// Condition to avoid an overflow (DO NOT REMOVE)
    	if( millis() < previous ) previous = millis();
    }
     	
	k = (minute/time);
	radiationValueCPM = k*count;
   	radiationValue = k*count * CONV_FACTOR;
   	timePreviousMeassure = millis();
	ledBar(k*count);  
   	count = 0;

	return radiationValue;
}

/*
 Function: Measures actual radiation value during specified time. Maximum time is 60 seconds
 Returns: 
	RadiationValueCPM: radiation value in CPM
 Parameters: 
	time: time while radiation is measured. Time must be in milliseconds
 Values: 
*/
float WaspRadiationBoard::getCPM(long time)
{

	float k=0;
	float minute = 60000;
	unsigned long previous=millis();
	
	enableInterrupts(RAD_INT);
	while( (millis()-previous<time) )
    {
		if( intFlag & RAD_INT)
		{
			disableInterrupts(RAD_INT);
			intFlag &= ~(RAD_INT);
			countPulse();
    		enableInterrupts(RAD_INT);
			while(!digitalRead(RAD_INT_PIN_MON));
  		}
    
    	// Condition to avoid an overflow (DO NOT REMOVE)
    	if( millis() < previous ) previous=millis();
    }
	k = (minute/time);
   	radiationValueCPM = k*count  ;
   	timePreviousMeassure = millis();
	ledBar(k*count);  
   	count = 0;

	return radiationValueCPM;
}

/*
 Function: Refresh led bar value
 Returns: 
 Parameters: 
	value: counter value to set led bar 
 Values: 
*/
//resfresh led bar value.
void WaspRadiationBoard::ledBar(float value)
{

	int numberOfLed = 0;

	// First clear previous value
	for(int i=0;i<5;i++)	digitalWrite(ledArray[i],LOW);

	if (value<TH1) numberOfLed=0;
	if ((value>=TH1) && (value<TH2)) numberOfLed=1;
	if ((value>=TH2) && (value<TH3)) numberOfLed=2;
	if ((value>=TH3) && (value<TH4)) numberOfLed=3;
	if ((value>=TH4) && (value<TH5)) numberOfLed=4;
	if (value>=TH5) numberOfLed=5;

	// Set led Bar
	for(int i=0;i<numberOfLed;i++)	digitalWrite(ledArray[i],HIGH);
	
}

// Private methods

/*
 Function: Adds one pulse to cpm counter
 Returns: 
 Parameters: 
 Values: 
*/
void WaspRadiationBoard::countPulse()
{

 	count++;
  	
  	
}

WaspRadiationBoard RadiationBoard=WaspRadiationBoard();		//object
