/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 * 	Functions getEpochTime(), breakTimeAbsolute(), breakTimeOffset() and
 * 	constants related to them are based on the library 'time' developed by
 * 	Michael Margolis 2009-2014: https://www.pjrc.com/teensy/td_libs_Time.html
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
 *  Version:		3.3
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles, Marcos Yarza, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif




/// table_RTC /////////////////////////////////////////////////////////////////

const char rtc_string_00[] 	PROGMEM	= 	"Alarm matches ";
const char rtc_string_01[] 	PROGMEM	= 	"[Day, hh:mm:ss] --> ";
const char rtc_string_02[] 	PROGMEM = 	"[Date, hh:mm:ss] --> ";
const char rtc_string_03[] 	PROGMEM = 	"[hh:mm:ss] --> ";
const char rtc_string_04[] 	PROGMEM = 	"[mm:ss] --> ";
const char rtc_string_05[] 	PROGMEM = 	"[ss] --> ";
const char rtc_string_06[] 	PROGMEM = 	"Once per second";
const char rtc_string_07[] 	PROGMEM = 	"Incorrect alarm mode";
const char rtc_string_08[] 	PROGMEM = 	"[%02u, %02u:%02u:%02u]";
const char rtc_string_09[] 	PROGMEM = 	"[%02u, %02u:%02u]";
const char rtc_string_10[] 	PROGMEM = 	"[%02u:%02u]";
const char rtc_string_11[] 	PROGMEM = 	"[%02u]";
const char rtc_string_12[] 	PROGMEM = 	"[Day, hh:mm] --> ";
const char rtc_string_13[] 	PROGMEM = 	"[Date, hh:mm] --> ";
const char rtc_string_14[] 	PROGMEM = 	"[hh:mm] --> ";
const char rtc_string_15[] 	PROGMEM = 	"[mm] --> ";
const char rtc_string_16[] 	PROGMEM = 	"Once per minute";
const char rtc_string_17[] 	PROGMEM = 	"%s, %02u/%02u/%02u, %02u:%02u:%02u";
const char rtc_string_18[] 	PROGMEM = 	"error";
const char rtc_string_19[]	PROGMEM =	"%02u%c%02u%c%02u%c%02u%c%02u%c%02u%c%02u";
const char rtc_string_20[] 	PROGMEM = 	"[%02u:%02u:%02u]";


const char* const table_RTC[] PROGMEM =
{
	rtc_string_00,
	rtc_string_01,
	rtc_string_02,
	rtc_string_03,
	rtc_string_04,
	rtc_string_05,
	rtc_string_06,
	rtc_string_07,
	rtc_string_08,
	rtc_string_09,
	rtc_string_10,
	rtc_string_11,
	rtc_string_12,
	rtc_string_13,
	rtc_string_14,
	rtc_string_15,
	rtc_string_16,
	rtc_string_17,
	rtc_string_18,
	rtc_string_19,
	rtc_string_20,
};



// Constructors ////////////////////////////////////////////////////////////////

WaspRTC::WaspRTC()
{
	// init attributes
	_gmt = 0;
	isON = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

/*
 * ON (void) - It opens I2C bus and powers the RTC
 *
 *  It enables internal pull-up resistor for the RTC interrupt pin, so as this
 *  pin is set to HIGH when init
 *
 *  It reads from RTC time,date and alarms, setting the corresponding variables
 */
void WaspRTC::ON(void)
{
	// Powers RTC UP
	setMode(RTC_ON, RTC_NORMAL_MODE);

	// clear the alarm flags
	clearAlarmFlag();

	// initialize the variables used to store the data from the RTC
	resetVars();

	// read all registers related to the Time and Date and Alarms
	readRTC(RTC_ALARM2_ADDRESS);

	// set the interruption line down
	pinMode(MUX_RX, OUTPUT);
	digitalWrite(MUX_RX, LOW);
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
	I2C.close();
}


/* setMode(mode) - set power mode
 *
 * It sets the power mode on the RTC. It has two possibilities: ON or OFF
 */
void WaspRTC::setMode(uint8_t mode, uint8_t I2C_mode)
{
	// set power supply as 'mode'
	if (_boot_version < 'G')
	{
		pinMode(RTC_PW, OUTPUT);
		digitalWrite(RTC_PW, mode);
	}

	_pwrMode = mode;
	switch(_pwrMode)
	{
		case RTC_ON 	: 	if (I2C_mode==RTC_I2C_MODE) isON = 2;
							else if (I2C_mode==RTC_NORMAL_MODE) isON = 1;
							break;
		case RTC_OFF 	: 	isON = 0;
							break;
	}


	// stabilization time after switching on
	delay(10);
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
	char error_string[20];

	// buffer <-- "%s, %02u/%02u/%02u, %02u:%02u:%02u"
	strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[17])));
	// error_string <-- "error"
	strcpy_P(error_string,  (char*)pgm_read_word(&(table_RTC[18])));

	switch (day)
	{
	case 1:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_1, year, month, date, hour, minute, second);
			break;
	case 2:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_2, year, month, date, hour, minute, second);
			break;
	case 3:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_3, year, month, date, hour, minute, second);
			break;
	case 4:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_4, year, month, date, hour, minute, second);
			break;
	case 5:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_5, year, month, date, hour, minute, second);
			break;
	case 6:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_6, year, month, date, hour, minute, second);
			break;
	case 7:	snprintf(timeStamp, sizeof(timeStamp), buffer, DAY_7, year, month, date, hour, minute, second);
			break;
	default:snprintf(timeStamp, sizeof(timeStamp), error_string);
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
int WaspRTC::readRTC(uint8_t endAddress)
{
	uint8_t data[endAddress+1];
	int error;

	// init I2C bus
	I2C.begin();

	// ADDRESSING FROM MEMORY POSITION ZERO
	// the address specified in the datasheet is 208 (0xD0)
	// but i2c adressing uses the high 7 bits so it's 104
	// transmit to device #104 (0x68)
	error = I2C.read(I2C_ADDRESS_WASP_RTC, RTC_START_ADDRESS, data, endAddress+1);

	if (error == TWI_SUCCESS)
	{
		for (int i = 0; i <= endAddress; i++)
		{
			registersRTC[i] = data[i];
			switch (i)
			{
				case 0:	second = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 1:	minute = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 2:	hour = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 3:	day = data[i];
						break;
				case 4:	date = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 5:	month = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 6:	year = BCD2byte(data[i]>>4, data[i]&B00001111);
						break;
				case 7:	second_alarm1 = BCD2byte((data[i]>>4)&B00000111, data[i]&B00001111);
						break;
				case 8:	minute_alarm1 = BCD2byte((data[i]>>4)&B00000111, data[i]&B00001111);
						break;
				case 9:	hour_alarm1 = BCD2byte((data[i]>>4)&B00000011, data[i]&B00001111);
						break;
				case 10:day_alarm1 = BCD2byte((data[i]>>4)&B00000011, data[i]&B00001111);
						break;
				case 11:minute_alarm2 = BCD2byte((data[i]>>4)&B00000111, data[i]&B00001111);
						break;
				case 12:hour_alarm2 = BCD2byte((data[i]>>4)&B00000011, data[i]&B00001111);
						break;
				case 13:day_alarm2 = BCD2byte((data[i]>>4)&B00000011, data[i]&B00001111);
						break;
				default:
						break;
			}
		}
	}

	return error;
}


/* writeRTC() - writes the stored variables to the RTC
 *
 * It writes the stored variables corresponding to time and date to the RTC.
 * It loads the variables into 'registersRTC'
 * array and then, this array is sent to the RTC
 */
int WaspRTC::writeRTC()
{
	int error = 0;

	// init I2C bus
	I2C.begin();

	registersRTC[RTC_SECONDS_ADDRESS] = byte2BCD(second);
	registersRTC[RTC_MINUTES_ADDRESS] = byte2BCD(minute);
	registersRTC[RTC_HOURS_ADDRESS] = byte2BCD(hour);
	registersRTC[RTC_DAYS_ADDRESS] = day;
	registersRTC[RTC_DATE_ADDRESS] = byte2BCD(date);
	registersRTC[RTC_MONTH_ADDRESS] = byte2BCD(month);
	registersRTC[RTC_YEAR_ADDRESS] = byte2BCD(year);

	error = I2C.write(I2C_ADDRESS_WASP_RTC, RTC_START_ADDRESS, registersRTC, 7);

	return error;
}


/* writeRTCalarm1() - writes stored alarm1 to the RTC
 *
 * It writes stored time in corresponding alarm1 variables to the RTC.
 * It loads these values to 'registersRTC' array
 * and then is sent to the RTC
 */
int WaspRTC::writeRTCalarm1()
{
	int error = 0;

	// init I2C bus
	I2C.begin();

	registersRTC[RTC_ALM1_SECONDS_ADDRESS] 	= 0x7F & byte2BCD(second_alarm1);
	registersRTC[RTC_ALM1_MINUTES_ADDRESS] 	= 0x7F & byte2BCD(minute_alarm1);
	registersRTC[RTC_ALM1_HOURS_ADDRESS] 	= 0x7F & byte2BCD(hour_alarm1);
	registersRTC[RTC_ALM1_DAYS_ADDRESS] 	= 0x3F & byte2BCD(day_alarm1);

	error = I2C.write(I2C_ADDRESS_WASP_RTC, RTC_ALM1_START_ADDRESS, &registersRTC[RTC_ALM1_SECONDS_ADDRESS], 4);

	return error;
}


/* writeRTCalarm2() - writes stored alarm2 to the RTC
 *
 * It writes stored time in corresponding alarm2 variables to the RTC.
 * It loads these values to 'registersRTC' array
 * and then is sent to the RTC
 */
int WaspRTC::writeRTCalarm2()
{
	int error = 0;

	// init I2C bus
	I2C.begin();

	registersRTC[RTC_ALM2_MINUTES_ADDRESS] 	= 0x7F & byte2BCD(minute_alarm2);
	registersRTC[RTC_ALM2_HOURS_ADDRESS] 	= 0x7F & byte2BCD(hour_alarm2);
	registersRTC[RTC_ALM2_DAYS_ADDRESS] 	= 0x3F & byte2BCD(day_alarm2);

	error = I2C.write(I2C_ADDRESS_WASP_RTC, RTC_ALM2_START_ADDRESS, &registersRTC[RTC_ALM2_MINUTES_ADDRESS], 4);

	return error;
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
int WaspRTC::writeRTCregister(uint8_t theAddress)
{
	int error = 0;

	// init I2C bus
	I2C.begin();

	error = I2C.write(I2C_ADDRESS_WASP_RTC, theAddress, registersRTC[theAddress]);

	return error;
}


/* readRTCregister(theaddress) - reads from RTC the specified register
 *
 * It reads from RTC the specified register and stores into 'registersRTC'
 * array in corresponding position
 *
 * - FIXME: modify it to read from EEPROM
 */
int WaspRTC::readRTCregister(uint8_t theAddress)
{
	int error = 0;

	// init I2C bus
	I2C.begin();

	error = I2C.read(I2C_ADDRESS_WASP_RTC, theAddress, &registersRTC[theAddress], 1);

	return error;
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
uint8_t WaspRTC::setTime(const char* time)
{
	uint16_t _year;
	uint16_t _month;
	uint16_t _date;
	uint16_t _dow;
	uint16_t _hour;
	uint16_t _minute;
	uint16_t _second;
	char dots[7];
	char aux[40];

	// clear
	memset( dots, 0x00, sizeof(dots) );

	// "%02u%c%02u%c%02u%c%02u%c%02u%c%02u%c%02u"
	strcpy_P(aux, (char*)pgm_read_word(&(table_RTC[19])));

	// Check len
	if (strlen(time) != 20) return 1;

	// Split time
	sscanf (time,aux,	&_year,dots,
						&_month,dots+1,
						&_date,dots+2,
						&_dow,dots+3,
						&_hour,dots+4,
						&_minute,dots+5,
						&_second);

	//Check time format
	char* aux2 = strstr(dots,"::::::");
	if ( aux2 == NULL)
	{
		return 1;
	}

	// Check date
	if( _year <= 99 )
	{
		year = _year;
	}
	else return 1;

	if ( _month > 0 && _month <= 12 )
	{
		month = _month;

		// check correct maximum day depending on month
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		{
			// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
			if(_date>31) return 1;
		}
		else if(month==4||month==6||month==9||month==11)
		{
			// 30-Day months: Apr, June, Sep and Nov
			if( _date>30 ) return 1;
		}
		else if(month==2)
		{
			// Leap year condition for february
			if( LEAP_YEAR(year) )
			{
				if( _date>29 ) return 1;
			}
			else
			{
				if( _date>28 ) return 1;
			}
		}
	}
	else return 1;

	if ( _date > 0 && _date <= 31 )
	{
		date = _date;
	}
	else return 1;

	if ( _dow > 0 && _dow <= 7 )
	{
		day = _dow;
	}
	else return 1;

	if ( _hour <= 23 )
	{
		hour = _hour;
	}
	else return 1;

	if ( _minute <= 59 )
	{
		minute = _minute;
	}
	else return 1;

	if ( _second <= 59 )
	{
		second = _second;
	}
	else return 1;

	writeRTC();

	return 0;
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
uint8_t WaspRTC::setTime(	uint8_t _year,
						uint8_t _month,
						uint8_t _date,
						uint8_t day_week,
						uint8_t _hour,
						uint8_t _minute,
						uint8_t _second	)
{

	if( _year <= 99 )
	{
		year = _year;
	}
	else return 1;

	if ( _month > 0 && _month <= 12 )
	{
		month = _month;

		// check correct maximum day depending on month
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		{
			// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
			if(_date>31) return 1;
		}
		else if(month==4||month==6||month==9||month==11)
		{
			// 30-Day months: Apr, June, Sep and Nov
			if( _date>30 ) return 1;
		}
		else if(month==2)
		{
			// Leap year condition for february
			if( LEAP_YEAR(year) )
			{
				if( _date>29 ) return 1;
			}
			else
			{
				if( _date>28 ) return 1;
			}
		}
	}
	else return 1;

	if ( _date > 0 && _date <= 31 )
	{
		date = _date;
	}
	else return 1;

	if ( day_week > 0 && day_week <= 7 )
	{
		day = day_week;
	}
	else return 1;

	if ( _hour <= 23 )
	{
		hour = _hour;
	}
	else return 1;

	if ( _minute <= 59 )
	{
		minute = _minute;
	}
	else return 1;

	if ( _second <= 59 )
	{
		second = _second;
	}
	else return 1;

	writeRTC();

	return 0;

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
uint8_t WaspRTC::setAlarm1(const char* time, uint8_t offset, uint8_t mode)
{
	// Define variables
	uint8_t aux=0, aux2=0;

	// Check alarm-time string format: "dd:hh:mm:ss"
	if (strlen(time) != 11)
	{
		PRINT_RTC(F("Wrong time format. Must be \"dd:hh:mm:ss\"\n"));
	}

	// Parse string contents:
	// day field
	aux=(uint8_t) time[0] - 48;
	aux2=(uint8_t) time[1] - 48;
	day_alarm1 = BCD2byte(aux, aux2);
	// hour field
	aux=(uint8_t) time[3] - 48;
	aux2=(uint8_t) time[4] - 48;
	hour_alarm1 = BCD2byte(aux, aux2);
	// minutes field
	aux=(uint8_t) time[6] - 48;
	aux2=(uint8_t) time[7] - 48;
	minute_alarm1 = BCD2byte(aux, aux2);
	// seconds field
	aux=(uint8_t) time[9] - 48;
	aux2=(uint8_t) time[10] - 48;
	second_alarm1 = BCD2byte(aux, aux2);

	// if OFFSET mode then add the date to the actual date
	if (offset == RTC_OFFSET)
	{
		// get actual date
		readRTC(RTC_DATE_ADDRESS_2);

		// add 'seconds' offset
		second_alarm1 += second;
		if (second_alarm1 >= 60)
		{
			// check zero-crossing
			second_alarm1-=60;
			minute_alarm1++;
		}

		// add 'minutes' offset
		minute_alarm1+=minute;
		if (minute_alarm1 >= 60)
		{
			// check zero-crossing
			minute_alarm1-=60;
			hour_alarm1++;
		}

		// add 'hour' offset
		hour_alarm1+=hour;
		if (hour_alarm1 >= 24)
		{
			// check zero-crossing
			hour_alarm1 -= 24;
			day_alarm1++;
		}

		// add 'day' offset
		// RTC_ALM1_MODE1 indicates "dd" field as Day-Of-Week
		// Any other indicates "dd" field as Day of Month
		if (mode == RTC_ALM1_MODE1)
		{
			day_alarm1 += day;
			if (day_alarm1 > 7) day_alarm1 -= 7;
		}
		else
		{
			day_alarm1+=date;

			if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
			{
				// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
				if (day_alarm1 > 31) day_alarm1 -= 31;
			}
			else if (month==4||month==6||month==9||month==11 )
			{
				// 30-Day months: Apr, June, Sep and Nov
				if (day_alarm1 > 30) day_alarm1 -= 30;
			}
			else if (month==2)
			{
				// Leap year condition for february
				if (LEAP_YEAR(RTC.year))
				{
					if (day_alarm1>29) day_alarm1 -= 29;
				}
				else
				{
					if (day_alarm1 > 28) day_alarm1 -= 28;
				}
			}
		}
	}


	if ((day_alarm1 > 31) || (hour_alarm1 > 23) || (minute_alarm1 > 59) || (second_alarm1 > 59))
	{
		PRINT_RTC(F("Incorrect input parameters\n"));

		#if DEBUG_RTC > 0
		PRINT_RTC(F("day_alarm1:"));
		USB.println(day_alarm1, DEC);
		PRINT_RTC(F("hour_alarm1:"));
		USB.println(hour_alarm1, DEC);
		PRINT_RTC(F("minute_alarm1:"));
		USB.println(minute_alarm1, DEC);
		PRINT_RTC(F("second_alarm1:"));
		USB.println(second_alarm1, DEC);
		#endif
		return 1;
	}

	alarm1Mode = mode;
	RTC.writeRTCalarm1();
	RTC.configureAlarmMode(1,mode);
	return 0;
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
uint8_t WaspRTC::setAlarm1(uint8_t day_date,
							uint8_t _hour,
							uint8_t _minute,
							uint8_t _second,
							uint8_t offset,
							uint8_t mode)
{
	uint8_t aux=0, aux2=0;

	if (day_date<10)
	{
		aux=0;
		aux2=day_date;
		day_alarm1 = BCD2byte(aux, aux2);
	}
	else if (day_date>=10)
	{
		aux2=day_date%10;
		aux=day_date/10;
		day_alarm1 = BCD2byte(aux, aux2);
	}
	if (_hour<10)
	{
		aux=0;
		aux2=_hour;
		hour_alarm1 = BCD2byte(aux, aux2);
	}
	else if (_hour>=10)
	{
		aux2=_hour%10;
		aux=_hour/10;
		hour_alarm1 = BCD2byte(aux, aux2);
	}
	if (_minute<10)
	{
		aux=0;
		aux2=_minute;
		minute_alarm1 = BCD2byte(aux, aux2);
	}
	else if (_minute>=10)
	{
		aux2=_minute%10;
		aux=_minute/10;
		minute_alarm1 = BCD2byte(aux, aux2);
	}
	if (_second<10)
	{
		aux=0;
		aux2=_second;
		second_alarm1 = BCD2byte(aux, aux2);
	}
	else if (_second>=10)
	{
		aux2=_second%10;
		aux=_second/10;
		second_alarm1 = BCD2byte(aux, aux2);
	}

	if (offset == RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		second_alarm1+=second;
		if (second_alarm1 >= 60)
		{
			second_alarm1 -= 60;
			minute_alarm1++;
		}
		minute_alarm1+=minute;
		if (minute_alarm1 >= 60)
		{
			minute_alarm1 -= 60;
			hour_alarm1++;
		}
		hour_alarm1+=hour;
		if (hour_alarm1 >= 24)
		{
			hour_alarm1 -= 24;
			day_alarm1++;
		}
		if (mode == RTC_ALM1_MODE1)
		{
			day_alarm1+=day;
			if (day_alarm1 > 7) day_alarm1 -= 7;
		}
		else
		{
			day_alarm1+=date;

			if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
			{
				// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
				if( day_alarm1>31 ) day_alarm1-=31;
			}
			else if (month==4||month==6||month==9||month==11)
			{
				// 30-Day months: Apr, June, Sep and Nov
				if( day_alarm1>30 ) day_alarm1-=30;
			}
			else if (month==2)
			{
				// Leap year condition for february
				if (LEAP_YEAR(RTC.year))
				{
					if (day_alarm1 > 29) day_alarm1 -= 29;
				}
				else
				{
					if (day_alarm1 > 28) day_alarm1 -= 28;
				}
			}
		}
	}

	if ((day_alarm1 > 31) || (hour_alarm1 > 23) || (minute_alarm1 > 59) || (second_alarm1 > 59))
	{
		PRINT_RTC(F("Incorrect input parameters\n"));

		#if DEBUG_RTC > 0
		PRINT_RTC(F("day_alarm1:"));
		USB.println(day_alarm1, DEC);
		PRINT_RTC(F("hour_alarm1:"));
		USB.println(hour_alarm1, DEC);
		PRINT_RTC(F("minute_alarm1:"));
		USB.println(minute_alarm1, DEC);
		PRINT_RTC(F("second_alarm1:"));
		USB.println(second_alarm1, DEC);
		#endif
		return 1;
	}

	alarm1Mode = mode;
	RTC.writeRTCalarm1();
	RTC.configureAlarmMode(1,mode);

	return 0;
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

	// buffer: "Alarm matches "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_RTC[0])));
	strcat(timeStamp,buffer);

	switch(alarm1Mode)
	{
		case RTC_ALM1_MODE1:

			// buffer: "[Day, hh:mm:ss] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[1])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u, %02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[8])));

			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											day_alarm1,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM1_MODE2:

			// buffer: "[Date, hh:mm:ss] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[2])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u, %02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[8])));

			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											day_alarm1,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM1_MODE3:

			// buffer: "[hh:mm:ss] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[3])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u:%02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[20])));

			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											hour_alarm1,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM1_MODE4:

			// buffer: "[mm:ss] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[4])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u:%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[10])));

			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											minute_alarm1,
											second_alarm1);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM1_MODE5:

			// buffer: "[ss] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[5])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[11])));

			snprintf(auxiliar, sizeof(auxiliar), buffer_format,	second_alarm1);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM1_MODE6:

			// buffer: "Once per second"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[6])));
			strcat(timeStamp,buffer);
			break;

		default:
			// buffer: "Incorrect alarm mode"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[7])));
			snprintf(timeStamp, sizeof(timeStamp), buffer);
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
uint8_t WaspRTC::setAlarm2(const char* time, uint8_t offset, uint8_t mode)
{
	// Define variables
	uint8_t aux=0, aux2=0;

	// Check alarm-time string format: "dd:hh:mm"
	if (strlen(time) != 8)
	{
		PRINT_RTC(F("Wrong time format. Must be \"dd:hh:mm\"\n"));
	}

	// Parse string contents:
	// day field
	aux=(uint8_t) time[0] - 48;
	aux2=(uint8_t) time[1] - 48;
	day_alarm2 = BCD2byte(aux, aux2);
	// hour field
	aux=(uint8_t) time[3] - 48;
	aux2=(uint8_t) time[4] - 48;
	hour_alarm2 = BCD2byte(aux, aux2);
	// minute field
	aux=(uint8_t) time[6] - 48;
	aux2=(uint8_t) time[7] - 48;
	minute_alarm2 = BCD2byte(aux, aux2);

	// if OFFSET mode then add the date to the actual date
	if (offset == RTC_OFFSET)
	{
		// get actual date
		readRTC(RTC_DATE_ADDRESS_2);

		// add 'minutes' offset
		minute_alarm2+=minute;
		if (minute_alarm2 >= 60)
		{
			// check zero-crossing
			minute_alarm2 -= 60;
			hour_alarm2++;
		}

		// add 'hours' offset
		hour_alarm2+=hour;
		if (hour_alarm2 >= 24)
		{
			// check zero-crossing
			hour_alarm2-=24;
			day_alarm2++;
		}

		// add 'day' offset
		// RTC_ALM2_MODE1 indicates "dd" field as Day-Of-Week
		// Any other indicates "dd" field as Day of Month
		if (mode == RTC_ALM2_MODE1)
		{
			day_alarm2 += day;
			if (day_alarm2 > 7) day_alarm2 -= 7;
		}
		else
		{
			day_alarm2+=date;
			if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
			{
				// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
				if (day_alarm2 > 31) day_alarm2 -= 31;
			}
			else if (month==4||month==6||month==9||month==11)
			{
				// 30-Day months: Apr, Jun, Sep and Nov
				if (day_alarm2 > 30) day_alarm2 -= 30;
			}
			else if (month==2)
			{
				// Leap year condition for february
				if (LEAP_YEAR(RTC.year))
				{
					if (day_alarm2 > 29) day_alarm2 -= 29;
				}
				else
				{
					if (day_alarm2 > 28) day_alarm2 -= 28;
				}
			}
		}
	}

	if ((day_alarm2 > 31) || (hour_alarm2 > 23) || (minute_alarm2 > 59))
	{
		PRINT_RTC(F("Incorrect input parameters\n"));

		#if DEBUG_RTC > 0
		PRINT_RTC(F("day_alarm2:"));
		USB.println(day_alarm2, DEC);
		PRINT_RTC(F("hour_alarm2:"));
		USB.println(hour_alarm2, DEC);
		PRINT_RTC(F("minute_alarm2:"));
		USB.println(minute_alarm2, DEC);
		#endif
		return 1;
	}

	alarm2Mode = mode;
	RTC.writeRTCalarm2();
	RTC.configureAlarmMode(2,mode);

	return 0;
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
uint8_t WaspRTC::setAlarm2(uint8_t day_date,
							uint8_t _hour,
							uint8_t _minute,
							uint8_t offset,
							uint8_t mode)
{
	uint8_t aux=0, aux2=0;
	if (day_date < 10)
	{
		aux=0;
		aux2=day_date;
		day_alarm2 = BCD2byte(aux, aux2);
	}
	else if (day_date >= 10)
	{
		aux2=day_date%10;
		aux=day_date/10;
		day_alarm2 = BCD2byte(aux, aux2);
	}
	if (_hour < 10)
	{
		aux=0;
		aux2=_hour;
		hour_alarm2 = BCD2byte(aux, aux2);
	}
	else if (_hour >= 10)
	{
		aux2=_hour%10;
		aux=_hour/10;
		hour_alarm2 = BCD2byte(aux, aux2);
	}
	if (_minute < 10)
	{
		aux=0;
		aux2=_minute;
		minute_alarm2 = BCD2byte(aux, aux2);
	}
	else if (_minute >= 10)
	{
		aux2=_minute%10;
		aux=_minute/10;
		minute_alarm2 = BCD2byte(aux, aux2);
	}

	if (offset == RTC_OFFSET) // add the date to the actual date
	{
		readRTC(RTC_DATE_ADDRESS_2);
		minute_alarm2+=minute;
		if (minute_alarm2 >= 60)
		{
			minute_alarm2-=60;
			hour_alarm2++;
		}
		hour_alarm2+=hour;
		if (hour_alarm2 >= 24)
		{
			hour_alarm2-=24;
			day_alarm2++;
		}
		if (mode == RTC_ALM2_MODE1)
		{
			day_alarm2+=day;
			if (day_alarm2 > 7) day_alarm2 -= 7;
		}
		else
		{
			day_alarm2+=date;
			if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
			{
				// 31-Day months: Jan, Mar, May, Jul, Aug, Oct and Dec
				if (day_alarm2 > 31) day_alarm2 -= 31;
			}
			else if (month==4||month==6||month==9||month==11)
			{
				// 30-Day months: Apr, Jun, Sep and Nov
				if (day_alarm2 > 30) day_alarm2 -= 30;
			}
			else if (month==2)
			{
				// Leap year condition for february
				if (LEAP_YEAR(RTC.year))
				{
					if (day_alarm2 > 29) day_alarm2-=29;
				}
				else
				{
					if (day_alarm2 > 28) day_alarm2-=28;
				}
			}
		}
	}

	if ((day_alarm2 > 31) || (hour_alarm2 > 23) || (minute_alarm2 > 59))
	{
		PRINT_RTC(F("Incorrect input parameters\n"));

		#if DEBUG_RTC > 0
		PRINT_RTC(F("day_alarm2:"));
		USB.println(day_alarm2, DEC);
		PRINT_RTC(F("hour_alarm2:"));
		USB.println(hour_alarm2, DEC);
		PRINT_RTC(F("minute_alarm2:"));
		USB.println(minute_alarm2, DEC);
		#endif
		return 1;
	}

	alarm2Mode = mode;
	RTC.writeRTCalarm2();
	RTC.configureAlarmMode(2,mode);

	return 0;
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

	// buffer: "Alarm matches "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_RTC[0])));
	strcat(timeStamp,buffer);

	switch(alarm2Mode)
	{
		case RTC_ALM2_MODE1:

			// buffer: "[Day, hh:mm] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[12])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u, %02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[9])));
			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											day_alarm2,
											hour_alarm2,
											minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM2_MODE2:

			// buffer: "[Date, hh:mm] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[13])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u, %02u:%02u]"
			strcpy_P(buffer_format,  (char*)pgm_read_word(&(table_RTC[9])));
			snprintf(auxiliar, sizeof(auxiliar), buffer_format,
											day_alarm2,
											hour_alarm2,
											minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM2_MODE3:

			// buffer: "[hh:mm] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[14])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u:%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[10])));
			snprintf(auxiliar, sizeof(auxiliar), buffer_format, hour_alarm2, minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM2_MODE4:

			// buffer: "[mm] --> "
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[15])));
			strcat(timeStamp, buffer);

			// buffer_format: "[%02u]"
			strcpy_P(buffer_format, (char*)pgm_read_word(&(table_RTC[11])));
			snprintf(auxiliar, sizeof(auxiliar), buffer_format, minute_alarm2);
			strcat(timeStamp, auxiliar);
			break;

		case RTC_ALM2_MODE5:
			// buffer: "Once per minute"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[16])));
			strcat(timeStamp, buffer);
			break;

		default:
			// buffer: "Incorrect alarm mode"
			strcpy_P(buffer,  (char*)pgm_read_word(&(table_RTC[7])));
			snprintf(timeStamp, sizeof(timeStamp), buffer);
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
	// check hardware version
	if (_boot_version < 'G')
	{
		// get alarm which triggered last alarm
		uint8_t trig = getAlarmTriggered();

		// if a pending alarm is being generated then update attribute
		if( trig != 0 ) alarmTriggered = trig;
	}

	// reset the alarm flags in RTC
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


/* getEpochTime() - Get the epoch time based on RTC settings
 *
 * This function is based on library developed by Michael Margolis:
 * 	https://www.pjrc.com/teensy/td_libs_Time.html
 */
unsigned long WaspRTC::getEpochTime()
{
	// get actual time and date
	RTC.getTime();

	return getEpochTime(RTC.year,
						RTC.month,
						RTC.date,
						RTC.hour,
						RTC.minute,
						RTC.second);
}


/* getEpochTime() - Get the epoch time based on RTC settings
 *
 * This function is based on library developed by Michael Margolis:
 * 	https://www.pjrc.com/teensy/td_libs_Time.html
 */
unsigned long WaspRTC::getEpochTime(uint8_t Year,
									uint8_t Month,
									uint8_t Date,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second)
{

	// initialize variable
	epoch = SECS_YR_2000;

	// seconds from 1970 till 1 jan 00:00:00 of the given year
	epoch += Year * (SECS_PER_DAY * 365);

	// add extra days for leap years
	for( int i = 0; i < Year; i++)
	{
		if( LEAP_YEAR(i) )
		{
			epoch += SECS_PER_DAY;
		}
	}

	// add days for this year, months start from 1
	for( int i = 1; i < Month ; i++)
	{
		// check february if leap year
		if ( (i == 2) && LEAP_YEAR(Year))
		{
			epoch += SECS_PER_DAY * 29;
		}
		else
		{
			epoch += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
		}
	}

	epoch += (Date-1) * SECS_PER_DAY;
	epoch += Hour * SECS_PER_HOUR;
	epoch += Minute * SECS_PER_MIN;
	epoch += Second;

	return epoch;
}


/* getEpochTime() - Get the epoch time based on RTC settings
 *
 * This function is based on library developed by Michael Margolis:
 * 	https://www.pjrc.com/teensy/td_libs_Time.html
 */
unsigned long WaspRTC::getEpochTime(uint8_t Year,
									uint8_t Month,
									uint8_t Date,
									uint8_t Hour,
									uint8_t Minute,
									uint8_t Second,
                  uint8_t Timezone)
{

	// initialize variable
	epoch = SECS_YR_2000;

	// seconds from 1970 till 1 jan 00:00:00 of the given year
	epoch += Year * (SECS_PER_DAY * 365);

	// add extra days for leap years
	for( int i = 0; i < Year; i++)
	{
		if( LEAP_YEAR(i) )
		{
			epoch += SECS_PER_DAY;
		}
	}

	// add days for this year, months start from 1
	for( int i = 1; i < Month ; i++)
	{
		// check february if leap year
		if ( (i == 2) && LEAP_YEAR(Year))
		{
			epoch += SECS_PER_DAY * 29;
		}
		else
		{
			epoch += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
		}
	}

	epoch += (Date-1) * SECS_PER_DAY;
	epoch += Hour * SECS_PER_HOUR;
	epoch += Minute * SECS_PER_MIN;
	epoch += Second;

  epoch -= (Timezone*SECS_PER_HOUR);

	return epoch;
}


/*
 * breakTimeAbsolute()
 *
 * break the given time by 'timeInput' into time components: year, month, date,
 * day (week day), hour, minute and seconds. And store this info in the 'tmElements_t'
 * struct given as input parameter.
 *
 * This function calculates the structure as an ABSOLUTE time. For example,
 * if timeInput equals to 1416933867, this function stores the following
 * data within the structure: Tue, 25 Nov 2014 16:44:27 GMT
 *
 * 	tm->second = 27;
 * 	tm->minute = 44;
 * 	tm->hour = 16;
 * 	tm->date = 25;
 * 	tm->month = 11;
 * 	tm->year = 14;
 * 	tm->day = 14;
 *
 * This function is based on library developed by Michael Margolis:
 * 	https://www.pjrc.com/teensy/td_libs_Time.html
 *
 * Remarks: http://www.epochconverter.com/
 */

void WaspRTC::breakTimeAbsolute(unsigned long timeInput, timestamp_t *tm)
{
	uint8_t Year;
	uint8_t Month, monthLength;
	uint32_t time;
	unsigned long days;

	time = (uint32_t)timeInput;
	tm->second = time % 60;
	time /= 60; // now it is minutes
	tm->minute = time % 60;
	time /= 60; // now it is hours
	tm->hour = time % 24;
	time /= 24; // now it is days
	tm->day = ((time + 4) % 7) + 1;  // Sunday is day 1

	Year = 0;
	days = 0;
	// count number of 'days' from 1970 until now and number of 'year'
	while((unsigned)(days += (LEAP_YEAR(Year-30) ? 366 : 365)) <= time)
	{
		Year++;
	}
	tm->year = Year-30; // year is offset from 2000

	days -= LEAP_YEAR(Year-30) ? 366 : 365;
	time  -= days; // now it is days in this year, starting at 0

	days=0;
	Month=0;
	monthLength=0;
	for (Month=0; Month<12; Month++)
	{
		if (Month==1)
		{
			// february
			if (LEAP_YEAR(Year-30))
			{
				monthLength=29;
			}
			else
			{
				monthLength=28;
			}
		}
		else
		{
			monthLength = monthDays[Month];
		}

		if (time >= monthLength)
		{
			time -= monthLength;
		}
		else
		{
			break;
		}
	}
	tm->month = Month + 1;  // jan is month 1
	tm->date = time + 1;     // day of month
}



/*
 * breakTimeOffset()
 *
 * break the given time by 'timeInput' into time components: year, month, date,
 * day (week day), hour, minute and seconds. And store this info in the 'tmElements_t'
 * struct given as input parameter.
 *
 * This function calculates the structure as a relative OFFSET time. For
 * example, if timeInput equals to 411361, this function stores the following
 * data within the structure: 4 days, 18 hours, 16 minutes and 1 seconds.
 *
 * 	tm->second = 1;
 * 	tm->minute = 16;
 * 	tm->hour = 18;
 * 	tm->date = 4;
 * 	tm->month = 0;
 * 	tm->year = 0;
 *
 * This function is based on library developed by Michael Margolis:
 * 	https://www.pjrc.com/teensy/td_libs_Time.html
 *
 * Remarks: http://www.epochconverter.com/
 */
void WaspRTC::breakTimeOffset(unsigned long timeInput, timestamp_t *tm)
{
	uint32_t time;

	const unsigned long MAXIMUM_OFFSET = 2764799; // 31days 23h 59m 59s

	// trunc input time to maximum possible value
	if( timeInput > MAXIMUM_OFFSET )
	{
		timeInput = MAXIMUM_OFFSET;
	}

	// copy
	time = (uint32_t)timeInput;

	tm->second = time % 60;
	time /= 60; // now it is minutes
	tm->minute = time % 60;
	time /= 60; // now it is hours
	tm->hour = time % 24;
	time /= 24; // now it is days

	tm->date = time;	// days of month
	tm->month = 0;		// month
	tm->year = 0;		// year
	tm->day = 0; 		// week day
}


/*
 * getAlarmTriggered()
 *
 * This function reads registersRTC[RTC_STATUS_ADDRESS] flags and returns which
 * alarms have been triggered
 *
 * returns		1 -> alarm1 triggered
 * 				2 -> alarm2 triggered
 * 				3 -> both alarms triggered
 *
 */
uint8_t WaspRTC::getAlarmTriggered()
{
	readRTCregister(RTC_STATUS_ADDRESS);
	return registersRTC[RTC_STATUS_ADDRESS]&B00000011;
}


/*
 * setGMT()
 *
 * This function sets GMT to add the offset to the epoch time
 *
 * returns		0 -> correct GMT value
 * 				1 -> wrong GMT value (set to '0')
 */
uint8_t WaspRTC::setGMT(int8_t gmt)
{
	if (gmt>-12 && gmt < 14)
	{
		_gmt = gmt;
		return 0;
	}
	else
	{
		USB.println(F("Invalid GMT value"));
		_gmt = 0;
		return 1;
	}
}

/*
 * getGMT()
 *
 * This function get GMT value
 *
 * returns		GMT value stored or default
 */
int8_t WaspRTC::getGMT()
{

	return _gmt;

}


/*******************************************************************************
 * utilities functions
 *******************************************************************************/


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
	// note that binary operations have preference on the others
	return (theNumber%10 | ((theNumber-theNumber%10)/10)<<4);
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

/*
 * setWatchdog(uint16_t minutes) - Set Watchdog alarm to reset Waspmote
 *
 *
 */
void WaspRTC::setWatchdog(uint16_t minutesWatchdog)
{
	if (_boot_version < 'H')
	{
		PRINT_RTC(F("\n***************  WARNING *******************\n"));
		PRINT_RTC(F("This example is valid only for Waspmote v15.\n"));
		PRINT_RTC(F("Your Waspmote version is v12.\n"));
		PRINT_RTC(F("*******************************************\n"));
		return (void)0;
	}

	uint8_t days = 0;
	uint8_t hours = 0;
	uint8_t minutes = 0;

	// check correct input
	if (minutesWatchdog == 0) return (void)1;

	// If needed: Translate from 'minutes' to 'days, hours and minutes'
	if (minutesWatchdog < 60)
	{
		minutes = (uint8_t) minutesWatchdog;
	}
	else if (minutesWatchdog < 1440)
	{
		hours = (uint8_t)(minutesWatchdog/60);
		minutes = (uint8_t)(minutesWatchdog%60);
	}
	else if (minutesWatchdog < 43200)
	{
		days = (uint8_t)(minutesWatchdog/(24*60));
		hours = (uint8_t)(minutesWatchdog%24);
		minutes = (uint8_t)(minutesWatchdog%(24*60));
	}
	else
	{
		return (void)1;
	}

	// get RTC status
	uint8_t status = RTC.isON;

	// switch on RTC if needed
	if (!status)
	{
		RTC.ON();
	}

	// Set Alarm2 for specified time
	RTC.setAlarm2(days, hours, minutes, RTC_OFFSET, RTC_ALM2_MODE2);

    // switch off RTC if needed
    if (!status)
	{
		RTC.OFF();
	}
}

/*
 * getWatchdog() - return the Watchdog alarm settings
 *
 *
 */
char* WaspRTC::getWatchdog()
{
  return RTC.getAlarm2();
}



/*
 * unSetWatchdog() - Unset Watchdog alarm
 *
 *
 */
void WaspRTC::unSetWatchdog(void)
{
	// get RTC status
	uint8_t status = RTC.isON;

	// switch on RTC if needed
	if (!status)
	{
		RTC.ON();
	}

	// disable the RTC alarm2
	RTC.disableAlarm2();

	// switch off RTC if needed
    if (!status)
	{
		RTC.OFF();
	}
}


/*
 * disableSQW() - Disable SQW Square Wave Output on the SQW/INTB pin
 *
 *
 */
void WaspRTC::disableSQW(void)
{
	// set INTCN to '1'
	registersRTC[RTC_CONTROL_ADDRESS] &= B11111011;
	registersRTC[RTC_CONTROL_ADDRESS] |= B00000100;
	writeRTCregister(RTC_CONTROL_ADDRESS);
}


// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspRTC RTC = WaspRTC();
