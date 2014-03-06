/*
 *  Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.1
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles, Marcos Yarza, Yuri Carmona
 */
 

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif




/// table_RTC /////////////////////////////////////////////////////////////////

const char rtc_string_00[] 	PROGMEM	= 	"Alarm Mode matches "; 	
const char rtc_string_01[] 	PROGMEM	= 	"[Day : hours : minutes : seconds] -> "; 	
const char rtc_string_02[] 	PROGMEM = 	"[Date : hours : minutes : seconds] -> ";	
const char rtc_string_03[] 	PROGMEM = 	"[Hours : minutes : seconds] -> ";		
const char rtc_string_04[] 	PROGMEM = 	"[Minutes : seconds] -> ";		
const char rtc_string_05[] 	PROGMEM = 	"[Seconds] -> ";		
const char rtc_string_06[] 	PROGMEM = 	"Once per second";	
const char rtc_string_07[] 	PROGMEM = 	"Incorrect alarm mode";	
const char rtc_string_08[] 	PROGMEM = 	"[%02u:%02u:%02u:%02u]";	
const char rtc_string_09[] 	PROGMEM = 	"[%02u:%02u:%02u]";	
const char rtc_string_10[] 	PROGMEM = 	"[%02u:%02u]";
const char rtc_string_11[] 	PROGMEM = 	"[%02u]";
const char rtc_string_12[] 	PROGMEM = 	"[Day : hours : minutes ] -> ";
const char rtc_string_13[] 	PROGMEM = 	"[Date : hours : minutes ] -> ";
const char rtc_string_14[] 	PROGMEM = 	"[Hours : minutes] -> ";
const char rtc_string_15[] 	PROGMEM = 	"[Minutes] -> ";	
const char rtc_string_16[] 	PROGMEM = 	"Once per minute";	
const char rtc_string_17[] 	PROGMEM = 	"%s, %02u/%02u/%02u, %02u:%02u:%02u";	


const char* const table_RTC[] PROGMEM = 	  
{
	rtc_string_00, 		// 0
	rtc_string_01,		// 1
	rtc_string_02,		// 2
	rtc_string_03, 		// 3
	rtc_string_04,		// 4
	rtc_string_05,		// 5
	rtc_string_06, 		// 6
	rtc_string_07,		// 7
	rtc_string_08,		// 8
	rtc_string_09, 		// 9
	rtc_string_10,		// 10
	rtc_string_11,		// 11
	rtc_string_12,		// 12
	rtc_string_13,		// 13
	rtc_string_14, 		// 14
	rtc_string_15,		// 15
	rtc_string_16,		// 16
	rtc_string_17,		// 16
};



// Constructors ////////////////////////////////////////////////////////////////

WaspRTC::WaspRTC()
{
  // nothing to do when constructing
}

// Public Methods //////////////////////////////////////////////////////////////

/*
 * ON (void) - It opens I2C bus and powers the RTC
 *
 *  It opens I2C bus and powers the RTC
 */
void WaspRTC::ON(void)
{
	begin();
}


/*
 * OFF (void) - It closes I2C bus and powers off the RTC
 *
 *  It closes I2C bus and powers off the RTC
 */
void WaspRTC::OFF(void)
{
	close();
	setMode(RTC_OFF, RTC_NORMAL_MODE);
}


/* begin() - inits I2C bus and used pins
 *
 * It enables internal pull-up resistor for the RTC interrupt pin, so as this
 * pin is set to HIGH when init
 * It inits I2C bus for communicating with RTC
 * It reads from RTC time,date and alarms, setting the corresponding variables
 *
 * Returns nothing
 */ 
void WaspRTC::begin()
{
	// Powers RTC UP
	setMode(RTC_ON, RTC_NORMAL_MODE);
	// Inits I2C bus
	if( !Wire.I2C_ON ) Wire.begin();
 
	// clear the alarm flags
	clearAlarmFlag();
  
	// initialize the variables used to store the data from the RTC
	resetVars();
  
	// read all registers related to the Time and Date and Alarms 
	readRTC(RTC_ALARM2_ADDRESS);
}


/* close() - closes I2C bus and used pins
 *
 * It enables internal pull-up resistor for the RTC interrupt pin, so as this
 * pin is set to HIGH when init
 * It inits I2C bus for communicating with RTC
 * It reads from RTC time,date and alarms, setting the corresponding variables
 *
 * Returns nothing
 */
void WaspRTC::close()
{
	if( Wire.I2C_ON && !ACC.isON) PWR.closeI2C();
}


/* setMode(mode) - set power mode
 *
 * It sets the power mode on the RTC. It has two possibilities: ON or OFF
 */
void WaspRTC::setMode(uint8_t mode, uint8_t I2C_mode)
{
	_pwrMode=mode;
	pinMode(RTC_PW,OUTPUT);
	switch(_pwrMode)
	{
		case RTC_ON 	: digitalWrite(RTC_PW,HIGH);
				  if( I2C_mode==RTC_I2C_MODE ) isON = 2;
				  else if( I2C_mode==RTC_NORMAL_MODE ) isON = 1;
			      	  break;
		case RTC_OFF 	: digitalWrite(RTC_PW,LOW);
				  isON = 0;
				  break;
	}
}


/* getMode() - gets power mode
 *
 * It gets the power mode of the RTC.
 */
 uint8_t WaspRTC::getMode()
{
	return _pwrMode;
}


/* resetVars() - resets variables to zero
 *
 * It resets all the used variables to default value
 */ 
void WaspRTC::resetVars()
{
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
    date = 0;
	second_alarm1 = 0;
	minute_alarm1 = 0;
	hour_alarm1 = 0;
	day_alarm1 = 0;
	minute_alarm2 = 0;
	hour_alarm2 = 0;
	day_alarm2 = 0;
	alarm1Mode = 0;
	alarm2Mode = 0;
	temp=0;
}




/* getTimestamp() - returns a string containing variables related with time 
 * and date.
 *
 * It returns a string containing variables related with time and date. These 
 * values are the last taken from RTC
 */
char* WaspRTC::getTimestamp() 
{
	// define local buffer
	char buffer[40];
	
	// buffer <-- "%s, %02u/%02u/%02u, %02u:%02u:%02u"
	strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[17])));		
	
	switch (day) 
	{
	case 1:	sprintf (timeStamp, buffer, DAY_1, year, month, date, hour, minute, second);
			break;
	case 2:	sprintf (timeStamp, buffer, DAY_2, year, month, date, hour, minute, second);
			break;
	case 3:	sprintf (timeStamp, buffer, DAY_3, year, month, date, hour, minute, second);
			break;
	case 4:	sprintf (timeStamp, buffer, DAY_4, year, month, date, hour, minute, second);
			break;
	case 5:	sprintf (timeStamp, buffer, DAY_5, year, month, date, hour, minute, second);
			break;
	case 6:	sprintf (timeStamp, buffer, DAY_6, year, month, date, hour, minute, second);
			break;
	case 7:	sprintf (timeStamp, buffer, DAY_7, year, month, date, hour, minute, second);
			break;
	default:sprintf (timeStamp, "error");
			break;
  }
  return timeStamp;
}


/* readRTC(endAddress) - reads from RTC the specified addresses
 *
 * It reads from RTC the specified addresses by 'endAddress'. This input
 * specifies the last address wants to be read.
 *
 * 'endAddress' may be any address, but it is recommended to use one of the
 * following:
 *
 * --> RTC_DATE_ADDRESS: to read time and date
 * --> RTC_ALARM1_ADDRESS: to read time, date and alarm1
 * --> RTC_ALARM2_ADDRESS: to read time, date, alarm1 and alarm2
 *
 * It stores in corresponding variables the read values up to alarm2 values
 * and stores then in 'registersRTC' array too.
 */
void WaspRTC::readRTC(uint8_t endAddress) 
{
	uint16_t timecount = 0;
	uint16_t timeout = 0;
	// ADDRESSING FROM MEMORY POSITION ZERO
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104    
	// transmit to device #104 (0x68)
	Wire.beginTransmission(RTC_ADDRESS);
  
	Wire.send(RTC_START_ADDRESS);  // start from address zero
	Wire.endTransmission();
  
	// START READING
	Wire.requestFrom(RTC_ADDRESS, RTC_DATA_SIZE);  

	// slave may send less than requested
	while((timecount <= endAddress) && (timeout < 10))
	{ 
		if (Wire.available())
		{
			uint8_t c = Wire.receive(); // receive a byte as character
			registersRTC[timecount] = c;
			switch (timecount)
			{
				case 0:	second = BCD2byte(c>>4, c&B00001111);
						break;
				case 1:	minute = BCD2byte(c>>4, c&B00001111);
						break;
				case 2:	hour = BCD2byte(c>>4, c&B00001111);
						break;
				case 3:	day = c;
						break;
				case 4:	date = BCD2byte(c>>4, c&B00001111);
						break;
				case 5:	month = BCD2byte(c>>4, c&B00001111);
						break;
				case 6:	year = BCD2byte(c>>4, c&B00001111);
						break;
				case 7:	second_alarm1 = BCD2byte((c>>4)&B00000111, c&B00001111);
						break;
				case 8:	minute_alarm1 = BCD2byte((c>>4)&B00000111, c&B00001111);
						break;
				case 9:	hour_alarm1 = BCD2byte((c>>4)&B00000011, c&B00001111);
						break;
				case 10:day_alarm1 = BCD2byte((c>>4)&B00000011, c&B00001111);
						break;
				case 11:minute_alarm2 = BCD2byte((c>>4)&B00000111, c&B00001111);
						break;
				case 12:hour_alarm2 = BCD2byte((c>>4)&B00000011, c&B00001111);
						break;
				case 13:day_alarm2 = BCD2byte((c>>4)&B00000011, c&B00001111);
						break;
			}
			timecount++;
		}
		// No data on I2C bus
		else
		{
			timeout++;
		}
	}
	
	timecount = 0;
}


/* writeRTC() - writes the stored variables to the RTC
 *
 * It writes the stored variables corresponding to time and date to the RTC.
 * It loads the variables into 'registersRTC'
 * array and then, this array is sent to the RTC
 */
void WaspRTC::writeRTC() 
{
	int timecount = 0;
	Wire.beginTransmission(RTC_ADDRESS); // transmit to device #104 (0x4A)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104
	Wire.send(RTC_START_ADDRESS);  // start from address zero

	registersRTC[RTC_SECONDS_ADDRESS] = byte2BCD(second);
	registersRTC[RTC_MINUTES_ADDRESS] = byte2BCD(minute);
	registersRTC[RTC_HOURS_ADDRESS] = byte2BCD(hour);
	registersRTC[RTC_DAYS_ADDRESS] = day;
	registersRTC[RTC_DATE_ADDRESS] = byte2BCD(date);
	registersRTC[RTC_MONTH_ADDRESS] = byte2BCD(month);
	registersRTC[RTC_YEAR_ADDRESS] = byte2BCD(year);

	for(timecount = 0; timecount <= 0x06; timecount++)
	{
		Wire.send(registersRTC[timecount]);
	}

	Wire.endTransmission();
}


/* writeRTCalarm1() - writes stored alarm1 to the RTC
 *
 * It writes stored time in corresponding alarm1 variables to the RTC.
 * It loads these values to 'registersRTC' array
 * and then is sent to the RTC
 */
void WaspRTC::writeRTCalarm1() 
{
	byte timecount = 0;
	Wire.beginTransmission(RTC_ADDRESS); // transmit to device #104 (0x4A)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104
	Wire.send(RTC_ALM1_START_ADDRESS);

	registersRTC[RTC_ALM1_SECONDS_ADDRESS] 	= 0x7F & byte2BCD(second_alarm1);
	registersRTC[RTC_ALM1_MINUTES_ADDRESS] 	= 0x7F & byte2BCD(minute_alarm1);
	registersRTC[RTC_ALM1_HOURS_ADDRESS] 	= 0x7F & byte2BCD(hour_alarm1);
	registersRTC[RTC_ALM1_DAYS_ADDRESS] 	= 0x3F & byte2BCD(day_alarm1);

	for(timecount = 7; timecount <= 0x0A; timecount++)
	{
		Wire.send(registersRTC[timecount]);
	}

	Wire.endTransmission();
}


/* writeRTCalarm2() - writes stored alarm2 to the RTC
 *
 * It writes stored time in corresponding alarm2 variables to the RTC.
 * It loads these values to 'registersRTC' array
 * and then is sent to the RTC
 */
void WaspRTC::writeRTCalarm2() 
{
	byte timecount = 0;
	Wire.beginTransmission(RTC_ADDRESS); // transmit to device #104 (0x4A)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104
	Wire.send(RTC_ALM2_START_ADDRESS);

	registersRTC[RTC_ALM2_MINUTES_ADDRESS] 	= 0x7F & byte2BCD(minute_alarm2);
	registersRTC[RTC_ALM2_HOURS_ADDRESS] 	= 0x7F & byte2BCD(hour_alarm2);
	registersRTC[RTC_ALM2_DAYS_ADDRESS] 	= 0x3F & byte2BCD(day_alarm2);


	for(timecount = 0X0B; timecount <= 0x0D; timecount++)
	{
		Wire.send(registersRTC[timecount]);
	}

	Wire.endTransmission();
}


/* configureAlarmMode(alarmNum, alarmMode) - configures alarmMode and
 * enables interrupt
 *
 * It configures the mode for the alarm and enables interrupt.
 * After calling this function, the alarm is set in the RTC.
 * Prior to this, time and date should be set.
 *
 * 'alarNum' specifies if the selected alarm is 1 or 2
 * 'alarMode' specifies the selected mode. The different modes are:
 *
 * -->  RTC_ALM1_MODE1	0	// Day,hours,minutes and seconds match
 * -->	RTC_ALM1_MODE2	1	// Date,hours,minutes and seconds match
 * -->	RTC_ALM1_MODE3	2	// Hours,minutes and seconds match
 * -->	RTC_ALM1_MODE4	3	// Minutes and seconds match
 * -->	RTC_ALM1_MODE5	4	// Seconds match
 * -->	RTC_ALM1_MODE6	5	// Once per second 
 * 
 * -->	RTC_ALM2_MODE1	0	// Day,hours and minutes match
 * -->	RTC_ALM2_MODE2	1	// Date,hours and minutes match
 * -->	RTC_ALM2_MODE3	2	// Hours and minutes
 * -->	RTC_ALM2_MODE4	3	// Minutes match
 * -->	RTC_ALM2_MODE5	4	// Once per minute
 */
void WaspRTC::configureAlarmMode (uint8_t alarmNum, uint8_t alarmMode)
{
	if (alarmNum == 1)
	{
		// activate the INT/SQW output on alarm match
		registersRTC[RTC_CONTROL_ADDRESS] &= B11111110; 
		registersRTC[RTC_CONTROL_ADDRESS] |= B00000101;
		writeRTCregister(RTC_CONTROL_ADDRESS);
		// reset the alarm flags
		registersRTC[RTC_STATUS_ADDRESS] &= B11111100;  
		writeRTCregister(RTC_STATUS_ADDRESS);

		switch (alarmMode)
		{
			// when day, hours, minutes and seconds match
			case 0:	// set A1M1 bit to 0
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);
					
					// set A1M2 bit to 0
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] &= B01111111; 
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 0
					registersRTC[RTC_ALM1_HOURS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 0
					registersRTC[RTC_ALM1_DAYS_ADDRESS] &= B01111111;
					// set DY/DT bit to 1
					registersRTC[RTC_ALM1_DAYS_ADDRESS] |= B01000000; 
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);

					break;
			
			// when date, hours, minutes and seconds match				
			case 1: // set A1M1 bit to 0
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);
					
					// set A1M2 bit to 0
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 0
					registersRTC[RTC_ALM1_HOURS_ADDRESS] &= B01111111; 
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 0 and DY/DT to 0
					registersRTC[RTC_ALM1_DAYS_ADDRESS] &= B00111111; 
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);

					break;
					
			// when hours, minutes and seconds match
			case 2:	// set A1M1 bit to 0
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);

					// set A1M2 bit to 0
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 0
					registersRTC[RTC_ALM1_HOURS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 1
					registersRTC[RTC_ALM1_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);

					break;
					
			// when minutes and seconds match
			case 3: // set A1M1 bit to 0
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);

					// set A1M2 bit to 0
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 1
					registersRTC[RTC_ALM1_HOURS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 1
					registersRTC[RTC_ALM1_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);
					break;
			
			// when seconds match
			case 4:	// set A1M1 bit to 0
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);

					// set A1M2 bit to 1
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 1
					registersRTC[RTC_ALM1_HOURS_ADDRESS] |= B10000000; 
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 1
					registersRTC[RTC_ALM1_DAYS_ADDRESS] |= B10000000; 
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);
					break;
			
			// once per second
			case 5:	// set A1M1 bit to 1
					registersRTC[RTC_ALM1_SECONDS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_SECONDS_ADDRESS);

					// set A1M2 bit to 1
					registersRTC[RTC_ALM1_MINUTES_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_MINUTES_ADDRESS);

					// set A1M3 bit to 1
					registersRTC[RTC_ALM1_HOURS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_HOURS_ADDRESS);

					// set A1M4 bit to 1
					registersRTC[RTC_ALM1_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM1_DAYS_ADDRESS);
					break;
			
			// alarm1 OFF
			case 6:	// de-activate the INT/SQW output on alarm match
					registersRTC[RTC_CONTROL_ADDRESS] &= B11111000;
					writeRTCregister(RTC_CONTROL_ADDRESS);
					detachInt();
					break;
		}

	}

	if (alarmNum == 2)
	{
		// activate the INT/SQW output on alarm match
		registersRTC[RTC_CONTROL_ADDRESS] &= B11111101;
		registersRTC[RTC_CONTROL_ADDRESS] |= B00000110;
		writeRTCregister(RTC_CONTROL_ADDRESS);
		// reset the alarm flags
		registersRTC[RTC_STATUS_ADDRESS] &= B11111100;
		writeRTCregister(RTC_STATUS_ADDRESS);

		switch (alarmMode)
		{
			// when day, hours and minutes match
			case 0:	// set A2M2 bit to 0
					registersRTC[RTC_ALM2_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_MINUTES_ADDRESS);

					// set A2M3 bit to 0
					registersRTC[RTC_ALM2_HOURS_ADDRESS] &= B01111111; 
					writeRTCregister(RTC_ALM2_HOURS_ADDRESS);
					
					// set A2M4 bit to 0
					registersRTC[RTC_ALM2_DAYS_ADDRESS] &= B01111111;
					// set DY/DT bit to 1 
					registersRTC[RTC_ALM2_DAYS_ADDRESS] |= B01000000;
					writeRTCregister(RTC_ALM2_DAYS_ADDRESS);
					break;

			// when date,hours and minutes match
			case 1:	// set A2M2 bit to 0
					registersRTC[RTC_ALM2_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_MINUTES_ADDRESS);

					// set A2M3 bit to 0
					registersRTC[RTC_ALM2_HOURS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_HOURS_ADDRESS);

					// set A2M4 bit to 0 and DY/DT to 0
					registersRTC[RTC_ALM2_DAYS_ADDRESS] &= B00111111; 
					writeRTCregister(RTC_ALM2_DAYS_ADDRESS);
					break;
			
			// when hours and minutes match
			case 2:	// set A2M2 bit to 0
					registersRTC[RTC_ALM2_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_MINUTES_ADDRESS);
					   
					// set A2M3 bit to 0
					registersRTC[RTC_ALM2_HOURS_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_HOURS_ADDRESS);

					//set A2M4 bit to 1
					registersRTC[RTC_ALM2_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM2_DAYS_ADDRESS);
					break;
			
			// when minutes match
			case 3:	// set A2M2 bit to 0
					registersRTC[RTC_ALM2_MINUTES_ADDRESS] &= B01111111;
					writeRTCregister(RTC_ALM2_MINUTES_ADDRESS);

					// set A2M3 bit to 1
					registersRTC[RTC_ALM2_HOURS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM2_HOURS_ADDRESS);

					// set A2M4 bit to 1
					registersRTC[RTC_ALM2_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM2_DAYS_ADDRESS);
					break;
			
			// Once per minute
			case 4:	// set A2M2 bit to 1
					registersRTC[RTC_ALM2_MINUTES_ADDRESS] |= B10000000; 
					writeRTCregister(RTC_ALM2_MINUTES_ADDRESS);

					// set A2M3 bit to 1
					registersRTC[RTC_ALM2_HOURS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM2_HOURS_ADDRESS);

					// set A2M4 bit to 1
					registersRTC[RTC_ALM2_DAYS_ADDRESS] |= B10000000;
					writeRTCregister(RTC_ALM2_DAYS_ADDRESS);
					break;
			
			// alarm 2 OFF
			case 5:	// de-activate the INT/SQW output on alarm match
					registersRTC[RTC_CONTROL_ADDRESS] &= B11111000;
					writeRTCregister(RTC_CONTROL_ADDRESS);
					detachInt();
					break;
		}

	}

	attachInt();
}


/* writeRTCregister(theaddress) - writes the specified register into the RTC
 *
 * It writes the specified register into the RTC. It takes the data from
 * 'registersRTC' array.
 *
 * - FIXME: modify it to write to EEPROM
 */
void WaspRTC::writeRTCregister(uint8_t theAddress) 
{
	// ADDRESSING FROM MEMORY POSITION RECEIVED AS PARAMETER
	Wire.beginTransmission(RTC_ADDRESS); // transmit to device #104 (0x68)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104    
	Wire.send(theAddress);  // start from address theAddress

	// START SENDING
	Wire.send(registersRTC[theAddress]);
	Wire.endTransmission();
}


/* readRTCregister(theaddress) - reads from RTC the specified register
 *
 * It reads from RTC the specified register and stores into 'registersRTC'
 * array in corresponding position
 *
 * - FIXME: modify it to read from EEPROM
 */
void WaspRTC::readRTCregister(uint8_t theAddress) 
{
	uint16_t timeout = 0;
	
	// ADDRESSING FROM MEMORY POSITION RECEIVED AS PARAMETER
	Wire.beginTransmission(RTC_ADDRESS); // transmit to device #104 (0x68)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104    
	Wire.send(theAddress);  // start from address theAddress
	Wire.endTransmission();
  
	// START READING
	Wire.requestFrom(RTC_ADDRESS, 0x01); // transmit to device #104 (0x68)
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104    
	while(!Wire.available() && (timeout < 10))
	{
		timeout++;
	}
	registersRTC[theAddress] = Wire.receive();
	Wire.endTransmission();
}


/* dow(y,m,d) - calculate the day of the week based on the year,month and day
 * 
 * Sakamoto’s algorithm is used in this function. Valid for any date in the 
 * range [September 14, 1752] – [December 31, 9999]
 * 
 * Parameters
 * 	y: year
 * 	m: month (1-12)
 * 	d: day of the month (1-31). 
 * 
 * Returns
 * 	The function returns 1 = Sunday, 2 = Monday, ..., 7 =Saturday.
 *
 */
int WaspRTC::dow(int y, int m, int d)
{	
	// invalid day of month 
	if( (d>31)|| (d<1) )
	{
		return 1;
	}
	
	// invalid month 
	if( (m>12)||(m<1) )
	{
		return 1;
	}
	
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7 + 1;
}


/* setTime(time) - sets time and date in the RTC
 *
 * It sets time and date in the RTC.
 *
 * After setting the variables, function 'writeRTC' is called to write to RTC
 * the values
 *
 * 'time' must be set in a specify format: YY:MM:DD:dow:hh:mm:ss
 */
void WaspRTC::setTime(const char* time)
{
	uint8_t aux=0, aux2=0;
	
	aux=(uint8_t) time[0] - 48;
	aux2=(uint8_t) time[1] - 48;
	year = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[3] - 48;
	aux2=(uint8_t) time[4] - 48;
	month = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[6] - 48;
	aux2=(uint8_t) time[7] - 48;
	date = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[9] - 48;
	aux2=(uint8_t) time[10] - 48;
	day = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[12] - 48;
	aux2=(uint8_t) time[13] - 48;
	hour = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[15] - 48;
	aux2=(uint8_t) time[16] - 48;
	minute = RTC.BCD2byte(aux, aux2);
	aux=(uint8_t) time[18] - 48;
	aux2=(uint8_t) time[19] - 48;
	second = RTC.BCD2byte(aux, aux2);
	writeRTC();
}

/* setTime(_year,_month,_date,day_week,_hour,_minute,_second) - sets time and
 * date in the RTC
 *
 * It sets time and date in the RTC.
 *
 * After setting the variables, function 'writeRTC' is called to write to RTC
 * the values
 *
 * Each input corresponds to the relayed part of time and date.
 */
void WaspRTC::setTime(	uint8_t _year, 
						uint8_t _month, 
						uint8_t _date,
						uint8_t day_week, 
						uint8_t _hour, 
						uint8_t _minute,
						uint8_t _second	)
{
	uint8_t aux=0, aux2=0;
	if(_year<10)
	{
		aux=0;
		aux2=_year;
		year = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_year>=10)
			{
				aux2=_year%10;
				aux=_year/10;
				year = RTC.BCD2byte(aux, aux2);
			}
	if(_month<10)
	{
		aux=0;
		aux2=_month;
		month = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_month>=10)
			{
				aux2=_month%10;
				aux=_month/10;
				month = RTC.BCD2byte(aux, aux2);
			}
	if(_date<10)
	{
		aux=0;
		aux2=_date;
		date = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_date>=10)
			{
				aux2=_date%10;
				aux=_date/10;
				date = RTC.BCD2byte(aux, aux2);
			}
	if(day_week<10)
	{
		aux=0;
		aux2=day_week;
		day = RTC.BCD2byte(aux, aux2);
	}
	else 	if(day_week>=10)
			{
				aux2=day_week%10;
				aux=day_week/10;
				day = RTC.BCD2byte(aux, aux2);
			}
	if(_hour<10)
	{
		aux=0;
		aux2=_hour;
		hour = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_hour>=10)
			{
				aux2=_hour%10;
				aux=_hour/10;
				hour = RTC.BCD2byte(aux, aux2);
			}
	if(_minute<10)
	{
		aux=0;
		aux2=_minute;
		minute = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_minute>=10)
			{
				aux2=_minute%10;
				aux=_minute/10;
				minute = RTC.BCD2byte(aux, aux2);
			}
	if(_second<10)
	{
		aux=0;
		aux2=_second;
		second = RTC.BCD2byte(aux, aux2);
	}
	else 	if(_second>=10)
			{
				aux2=_second%10;
				aux=_second/10;
				second = RTC.BCD2byte(aux, aux2);
			}
	writeRTC();
}


/* getTime() - gets time and date
 *
 * It gets time and date, storing them in 'registersRTC' array.
 *
 * It returns a string containing time and data in the following format:
 * "YY:MM:DD:dw:hh:mm:ss"
 */
char* WaspRTC::getTime()
{
	readRTC(RTC_DATE_ADDRESS_2);
	return getTimestamp();
}


/* getTemperature() - gets temperature
 *
 * It gets temperature from RTC. It reads associated registers to 
 * temperature and stores the temperature in a variable called 'temp'.
 * The temperature is encoded in two's complement format. 
 * The upper 8 bits, the integer portion, are at RTC's register 11h and 
 * the lower 2 bits, the fractional portion,  are in the upper nibble at 
 * register 12h.
 *
 * It returns temperature value.
 */
float WaspRTC::getTemperature()
{
	// Local variables
	int8_t high; // store upper byte
	uint8_t low; // store lower byte
	int16_t aux; 
	
	// Read RTC temperature registers 
	readRTCregister(RTC_MSB_TEMP_ADDRESS); // Upper byte
	readRTCregister(RTC_LSB_TEMP_ADDRESS); // Lower byte	
	high=registersRTC[RTC_MSB_TEMP_ADDRESS];
	low=registersRTC[RTC_LSB_TEMP_ADDRESS];
	
	// Compose temperature value 
	aux=((int16_t)high<<2)+((uint16_t)low>>6);
	  
	// The temperature is encoded in two's complement format. Check sign bit:
	if (registersRTC[RTC_MSB_TEMP_ADDRESS]>>7 == 1)	
	{
		// Negative temperature
		aux=~(aux); 
		aux++;
		temp=(float)aux;
		temp*=-1;
		temp=temp/4; 
	}
	else
	{
		// Positive temperature
		temp=(float)aux;
		temp=temp/4; 
	}
    
	return temp;
}


/* setAlarm1(time,offset,mode) - sets Alarm1 to the specified time, offset
 * and mode
 *
 * It sets Alarm1 to the specified time, offset and mode.
 *
 * 'time' --> has the following format : "dd:hh:mm:ss"
 * 'offset' --> possible values are:
 *		RTC_OFFSET--> 'time' is added to the actual time read from RTC
 *		RTC_ABSOLUTE--> 'time' is set as the time for Alarm1
 * 'mode' --> specifies the mode for Alarm1. Possible values are the same
 * as specified in 'configureAlarmMode'
 *
 * This function specifies the time for alarm, sets alarm in RTC
 * and enables interrupt.
 */
void WaspRTC::setAlarm1(const char* time, uint8_t offset, uint8_t mode)
{
	uint8_t aux=0, aux2=0;
	aux=(uint8_t) time[0] - 48;
	aux2=(uint8_t) time[1] - 48;
	day_alarm1 = BCD2byte(aux, aux2);
	aux=(uint8_t) time[3] - 48;
	aux2=(uint8_t) time[4] - 48;
	hour_alarm1 = BCD2byte(aux, aux2);
	aux=(uint8_t) time[6] - 48;
	aux2=(uint8_t) time[7] - 48;
	minute_alarm1 = BCD2byte(aux, aux2);
	aux=(uint8_t) time[9] - 48;
	aux2=(uint8_t) time[10] - 48;
	second_alarm1 = BCD2byte(aux, aux2);
	
	if(offset==RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		second_alarm1+=second;
		if(second_alarm1>=60)
		{
			second_alarm1-=60;
			minute_alarm1++;
		}
		minute_alarm1+=minute;
		if(minute_alarm1>=60)
		{
			minute_alarm1-=60;
			hour_alarm1++;
		}
		hour_alarm1+=hour;
		if(hour_alarm1>=24)
		{
			hour_alarm1-=24;
			day_alarm1++;
		}
		if(mode==RTC_ALM1_MODE1)
		{
			day_alarm1+=day;
			if( day_alarm1>7 ) day_alarm1-=7;
		}
		else
		{	
			day_alarm1+=date;
			if(month==1||month==3||month==5||month==7||month==8||month==12 )
			{
				if( day_alarm1>31 ) day_alarm1-=31;
			}
			if(month==4||month==6||month==9||month==10||month==11 )
			{
				if( day_alarm1>30 ) day_alarm1-=30;
			}
			if( month==2 )
			{
				if( day_alarm1>28 ) day_alarm1-=28;
			}			
		}
	}
	alarm1Mode=mode;
	RTC.writeRTCalarm1();
	RTC.configureAlarmMode(1,mode);
}

/* setAlarm1(day_date,_hour,_minute,_second,offset,mode) 
 *
 * It sets Alarm1 to the specified time, offset and mode.
 *
 * 'day_date,_hour,_minute,_second' --> specifies the time for Alarm1
 * 'offset' --> possible values are:
 *		RTC_OFFSET--> 'time' is added to the actual time read from RTC
 *		RTC_ABSOLUTE--> 'time' is set as the time for Alarm1
 * 'mode' --> specifies the mode for Alarm1. Possible values are the same
 * as specified in 'configureAlarmMode'
 *
 * This function specifies the time for alarm, sets alarm in RTC and
 * enables interrupt.
 */
void WaspRTC::setAlarm1(uint8_t day_date, uint8_t _hour, uint8_t _minute,
						uint8_t _second, uint8_t offset, uint8_t mode)
{
	uint8_t aux=0, aux2=0;

	if(day_date<10)
	{
		aux=0;
		aux2=day_date;
		day_alarm1 = BCD2byte(aux, aux2);
	}
	else if(day_date>=10)
	{
		aux2=day_date%10;
		aux=day_date/10;
		day_alarm1 = BCD2byte(aux, aux2);
	}
	if(_hour<10)
	{
		aux=0;
		aux2=_hour;
		hour_alarm1 = BCD2byte(aux, aux2);
	}
	else if(_hour>=10)
	{
		aux2=_hour%10;
		aux=_hour/10;
		hour_alarm1 = BCD2byte(aux, aux2);
	}
	if(_minute<10)
	{
		aux=0;
		aux2=_minute;
		minute_alarm1 = BCD2byte(aux, aux2);
	}
	else if(_minute>=10)
	{
		aux2=_minute%10;
		aux=_minute/10;
		minute_alarm1 = BCD2byte(aux, aux2);
	}
	if(_second<10)
	{
		aux=0;
		aux2=_second;
		second_alarm1 = BCD2byte(aux, aux2);
	}
	else if(_second>=10)
	{
		aux2=_second%10;
		aux=_second/10;
		second_alarm1 = BCD2byte(aux, aux2);
	}
	
	if(offset==RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		second_alarm1+=second;
		if(second_alarm1>=60)
		{
			second_alarm1-=60;
			minute_alarm1++;
		}
		minute_alarm1+=minute;
		if(minute_alarm1>=60)
		{
			minute_alarm1-=60;
			hour_alarm1++;
		}
		hour_alarm1+=hour;
		if(hour_alarm1>=24)
		{
			hour_alarm1-=24;
			day_alarm1++;
		}
		if(mode==RTC_ALM1_MODE1)
		{
			day_alarm1+=day;
			if( day_alarm1>7 ) day_alarm1-=7;
		}
		else
		{	
			day_alarm1+=date;
			if(month==1||month==3||month==5||month==7||month==8||month==12)
			{
				if( day_alarm1>31 ) day_alarm1-=31;
			}
			if(month==4||month==6||month==9||month==10||month==11)
			{
				if( day_alarm1>30 ) day_alarm1-=30;
			}
			if( month==2 )
			{
				if( day_alarm1>28 ) day_alarm1-=28;
			}			
		}
	}
	alarm1Mode=mode;
	RTC.writeRTCalarm1();
	RTC.configureAlarmMode(1,mode);
}


/* getAlarm1() - gets Alarm1 time
 *
 * It gets Alarm1 time from RTC. 
 *
 * It returns a string containing this time and date for Alarm1
 * Format: [dd - hh:mm:ss] where "dd" indicates day of alarm set in the RTC 
 * which might refer to day of month or day of week depending on the alarm mode
 * set to the RTC
 */
char* WaspRTC::getAlarm1()
{
	// read RTC registers
	readRTC(RTC_ALARM1_ADDRESS);
	
	// initialize variable
	memset(timeStamp, 0x00, sizeof(timeStamp) );
	
	// define local buffers
	char buffer[40];	
	char buffer_format[40];	
	char auxiliar[40];
			
	// buffer <-- "Alarm Mode matches "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_RTC[0]))); 	
	strcat(timeStamp,buffer);
		
	switch(alarm1Mode)
	{
		case RTC_ALM1_MODE1:	
		
			// buffer <-- [Day : hours : minutes : seconds]
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[1])));			
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[8])));
			
			sprintf(auxiliar, buffer_format,
											day_alarm1,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM1_MODE2:	
		
			// buffer <-- "[Date : hours : minutes : seconds]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[2])));
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[8])));
			
			sprintf(auxiliar,buffer_format,
											day_alarm1,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM1_MODE3:
		
			// buffer <-- "[Hours : minutes : seconds]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[3])));
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[9]))); 
			
			sprintf(auxiliar,buffer_format,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM1_MODE4:	
		
			// buffer <-- "[Minutes : seconds]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[4])));
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[10])));
	
			sprintf(auxiliar,buffer_format,												
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM1_MODE5:
		
			// buffer <-- "[Seconds]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[5]))); 
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[11]))); 
	
			sprintf(auxiliar,buffer_format,	second_alarm1);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM1_MODE6:
			
			// buffer <-- "Once per second"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[6])));
			strcat(timeStamp,buffer);	
			break;	
					
		default:
			// buffer <-- "Incorrect alarm mode"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[7])));
			sprintf(timeStamp, buffer);	
	}	
			
	return timeStamp;
}

/* setAlarm2(time,offset,mode) - sets Alarm2 to the specified time,
 * offset and mode
 *
 * It sets Alarm2 to the specified time, offset and mode.
 *
 * 'time' --> has the following format : "dd:hh:mm"
 * 'offset' --> possible values are:
 *		RTC_OFFSET--> 'time' is added to the actual time read from RTC
 *		RTC_ABSOLUTE--> 'time' is set as the time for Alarm2
 * 'mode' --> specifies the mode for Alarm2. Possible values are the same
 * as specified in 'configureAlarmMode'
 *
 * This function specifies the time for alarm, sets alarm in RTC and
 * enables interrupt.
 */
void WaspRTC::setAlarm2(const char* time, uint8_t offset, uint8_t mode)
{
	uint8_t aux=0, aux2=0;
	
	aux=(uint8_t) time[0] - 48;
	aux2=(uint8_t) time[1] - 48;
	day_alarm2 = BCD2byte(aux, aux2);
	aux=(uint8_t) time[3] - 48;
	aux2=(uint8_t) time[4] - 48;
	hour_alarm2 = BCD2byte(aux, aux2);
	aux=(uint8_t) time[6] - 48;
	aux2=(uint8_t) time[7] - 48;
	minute_alarm2 = BCD2byte(aux, aux2);
	
	if(offset==RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		minute_alarm2+=minute;
		if(minute_alarm2>=60)
		{
			minute_alarm2-=60;
			hour_alarm2++;
		}
		hour_alarm2+=hour;
		if(hour_alarm2>=24)
		{
			hour_alarm2-=24;
			day_alarm2++;
		}
		if(mode==RTC_ALM2_MODE1)
		{
			day_alarm2+=day;
			if( day_alarm2>7 ) day_alarm2-=7;
		}
		else
		{	
			day_alarm2+=date;
			if(month==1||month==3||month==5||month==7||month==8||month==12)
			{
				if( day_alarm2>31 ) day_alarm2-=31;
			}
			if(month==4||month==6||month==9||month==10||month==11)
			{
				if( day_alarm2>30 ) day_alarm2-=30;
			}
			if( month==2 )
			{
				if( day_alarm2>28 ) day_alarm2-=28;
			}			
		}
	}
	alarm2Mode=mode;
	RTC.writeRTCalarm2();
	RTC.configureAlarmMode(2,mode);
}

/* setAlarm2(day_date,_hour,_minute,offset,mode) - sets Alarm2 to the
 * specified time, offset and mode
 *
 * It sets Alarm2 to the specified time, offset and mode.
 *
 * 'day_date,_hour,_minute' --> specifies the time for Alarm2
 * 'offset' --> possible values are:
 *		RTC_OFFSET--> 'time' is added to the actual time read from RTC
 *		RTC_ABSOLUTE--> 'time' is set as the time for Alarm2
 * 'mode' --> specifies the mode for Alarm2. Possible values are the same
 * as specified in 'configureAlarmMode'
 *
 * This function specifies the time for alarm, sets alarm in RTC and
 * enables interrupt.
 */
void WaspRTC::setAlarm2(uint8_t day_date, uint8_t _hour, uint8_t _minute,
						uint8_t offset, uint8_t mode)
{
	uint8_t aux=0, aux2=0;
	if(day_date<10)
	{
		aux=0;
		aux2=day_date;
		day_alarm2 = BCD2byte(aux, aux2);
	}
	else if(day_date>=10)
	{
		aux2=day_date%10;
		aux=day_date/10;
		day_alarm2 = BCD2byte(aux, aux2);
	}
	if(_hour<10)
	{
		aux=0;
		aux2=_hour;
		hour_alarm2 = BCD2byte(aux, aux2);
	}
	else if(_hour>=10)
	{
		aux2=_hour%10;
		aux=_hour/10;
		hour_alarm2 = BCD2byte(aux, aux2);
	}
	if(_minute<10)
	{
		aux=0;
		aux2=_minute;
		minute_alarm2 = BCD2byte(aux, aux2);
	}
	else if(_minute>=10)
	{
		aux2=_minute%10;
		aux=_minute/10;
		minute_alarm2 = BCD2byte(aux, aux2);
	}
	
	if(offset==RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		minute_alarm2+=minute;
		if(minute_alarm2>=60)
		{
			minute_alarm2-=60;
			hour_alarm2++;
		}
		hour_alarm2+=hour;
		if(hour_alarm2>=24)
		{
			hour_alarm2-=24;
			day_alarm2++;
		}
		if(mode==RTC_ALM2_MODE1)
		{
			day_alarm2+=day;
			if( day_alarm2>7 ) day_alarm2-=7;
		}
		else
		{	
			day_alarm2+=date;
			if(month==1||month==3||month==5||month==7||month==8||month==12)
			{
				if( day_alarm2>31 ) day_alarm2-=31;
			}
			if(month==4||month==6||month==9||month==10||month==11)
			{
				if( day_alarm2>30 ) day_alarm2-=30;
			}
			if( month==2 )
			{
				if( day_alarm2>28 ) day_alarm2-=28;
			}			
		}
	}
	alarm2Mode=mode;
	RTC.writeRTCalarm2();
	RTC.configureAlarmMode(2,mode);
}


/* getAlarm2() - gets Alarm2 time
 *
 * It gets Alarm2 time from RTC. 
 *
 * It returns a string containing this time and date for Alarm2
 * Format: [dd - hh:mm] where "dd" indicates day of alarm set in the RTC
 * which might refer to day of month or day of week depending on the alarm mode
 * set to the RTC
 */
char* WaspRTC::getAlarm2()
{
	// read RTC registers
	readRTC(RTC_ALARM2_ADDRESS);
	
	// initialize variable
	memset(timeStamp, 0x00, sizeof(timeStamp) );
	
	// define local buffers
	char buffer[40];	
	char buffer_format[40];	
	char auxiliar[40];
			
	// buffer <-- "Alarm Mode matches "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_RTC[0]))); 	
	strcat(timeStamp,buffer);
			
	switch(alarm2Mode)
	{		
		case RTC_ALM2_MODE1:				
			
			// buffer <-- "[Day : hours : minutes ]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[12])));			
			strcat(timeStamp, buffer);
						
			// buffer_format <-- "[%02u:%02u:%02u]"			
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[9]))); 
			sprintf(auxiliar, buffer_format,
											day_alarm2,
											hour_alarm2,
											minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM2_MODE2:
			
			// buffer <-- "[Date : hours : minutes ]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[13])));			
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u:%02u]"			
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[9]))); 
			sprintf(auxiliar, buffer_format,
											day_alarm2,
											hour_alarm2,
											minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM2_MODE3:
			
			// buffer <-- "[Hours : minutes ]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[14])));			
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u:%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[10])));			
			sprintf(auxiliar, buffer_format, hour_alarm2, minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM2_MODE4:
			
			// buffer <-- "[Minutes ]"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[15])));			
			strcat(timeStamp, buffer);
			
			// buffer_format <-- "[%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[11]))); 
			sprintf(auxiliar, buffer_format, minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;
			
		case RTC_ALM2_MODE5:		
			// buffer <-- "Once per minute"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[16])));			
			strcat(timeStamp, buffer);
			break;
			
		default:
			// buffer <-- "Incorrect alarm mode"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[7])));
			sprintf(timeStamp, buffer);	
	}	
	
	return timeStamp;
}


/* clearAlarmFlag() - clear alarm flags in RTC
 *
 * It clears alarm flags (A1F and A2F) in the RTC.
 * If these flags are not cleared after an interrupt is captured,
 * no more interrupts could be captured.
 */
void WaspRTC::clearAlarmFlag()
{
	// reset the alarm flags in RT
	RTC.registersRTC[RTC_STATUS_ADDRESS] &= B11111100;  
	RTC.writeRTCregister(RTC_STATUS_ADDRESS);
}


/* disableAlarm1() - disables Alarm1
 *
 * It clears (A1IE) in the RTC CONTROL REGISTER
 * Clearing this flag we disable the Alarm1 in RTC even if the Alarm1 matches 
 * the previously set time and date
 */
void WaspRTC::disableAlarm1()
{
	// read CONTROL REGISTER
	readRTCregister(RTC_CONTROL_ADDRESS);
	// set A1IE to '0'
	registersRTC[RTC_CONTROL_ADDRESS] &= B11111110; 
	writeRTCregister(RTC_CONTROL_ADDRESS);	
}

/* disableAlarm2() - disables Alarm2
 *
 * It clears (A2IE) in the RTC CONTROL REGISTER
 * Clearing this flag we disable the Alarm2 in RTC even if the Alarm2 matches 
 * the previously set time and date
 */
void WaspRTC::disableAlarm2()
{
	// read CONTROL REGISTER
	readRTCregister(RTC_CONTROL_ADDRESS);
	// set A2IE to '0'
	registersRTC[RTC_CONTROL_ADDRESS] &= B11111101; 
	writeRTCregister(RTC_CONTROL_ADDRESS);	
}



/* BCD2byte ( number ) - converts a BCD number to an integer
 * 
 */
uint8_t WaspRTC::BCD2byte(uint8_t number) 
{
  return (number>>4)*10 | (number & 0x0F);
}

/* BCD2byte ( high, low ) - converts a BCD number to an integer
 */
uint8_t WaspRTC::BCD2byte(uint8_t high, uint8_t low) 
{
  return high*10 + low;
}

/* byte2BCD ( number ) - converts an integer number to a BCD number
 */
uint8_t WaspRTC::byte2BCD(uint8_t theNumber) 
{
  return (theNumber%10 | ((theNumber-theNumber%10)/10)<<4);  // note that binary operations have preference on the others
}


/*******************************************************************************
 * HANDLING HARDWARE INTERRUPTS
 *******************************************************************************/

/*
 * attachInt(void) - configure the specific hardware interrupt for the RTC
 *
 * the default interrupt functions are defined inside WInterrupts.c
 */
void WaspRTC::attachInt(void)
{
	enableInterrupts(RTC_INT);
}

/*
 * detachInt(void) - unset the specific hardware interrupt for the RTC
 *
 * It also clear Alarm Flags so as to provide RTC the correct parameters for future alarms
 */
void WaspRTC::detachInt(void)
{
	// disable alarm not to provoke the interruption signal
	disableAlarm1();
	disableAlarm2();
	
	// disable the RXD1 interruption pin
	disableInterrupts(RTC_INT);
	
	// clear the Alarm signal
	clearAlarmFlag();
}


// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspRTC RTC = WaspRTC();

