/*! \file WaspRTC.h
    \brief Library for managing the RTC

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com

 	Functions getEpochTime(), breakTimeAbsolute(), breakTimeOffset() and
 	constants related to them are based on the library 'time' developed by
 	Michael Margolis 2009-2014: https://www.pjrc.com/teensy/td_libs_Time.html

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version:		3.2
    Design:			David Gascón
    Implementation:	A. Bielsa, D. Cuartielles, M. Yarza, Y. Carmona

*/

 /*! \def WaspRTC_h
    \brief The library flag

  */
#ifndef WaspRTC_h
#define WaspRTC_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

//! DEBUG_RTC
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_RTC 	0
#define PRINT_RTC(str)	USB.print(F("[RTC] ")); USB.print(str);


// RTC ADDRESSES CONSTANTS
/*! \def RTC_SECONDS_ADDRESS
    \brief RTC Addresses constants. Seconds register in this case
 */
/*! \def RTC_MINUTES_ADDRESS
    \brief RTC Addresses constants. Minutes register in this case
 */
/*! \def RTC_HOURS_ADDRESS
    \brief RTC Addresses constants. Hours register in this case
 */
/*! \def RTC_DAYS_ADDRESS
    \brief RTC Addresses constants. Days register in this case
 */
/*! \def RTC_DATE_ADDRESS
    \brief RTC Addresses constants. Date register in this case
 */
/*! \def RTC_MONTH_ADDRESS
    \brief RTC Addresses constants. Month register in this case
 */
/*! \def RTC_YEAR_ADDRESS
    \brief RTC Addresses constants. Year register in this case
 */
/*! \def RTC_ALM1_START_ADDRESS
    \brief RTC Addresses constants. Alarm1 start address in this case
 */
/*! \def RTC_ALM1_SECONDS_ADDRESS
    \brief RTC Addresses constants. Alarm1 seconds register in this case
 */
/*! \def RTC_ALM1_MINUTES_ADDRESS
    \brief RTC Addresses constants. Alarm1 minutes register in this case
 */
/*! \def RTC_ALM1_HOURS_ADDRESS
    \brief RTC Addresses constants. Alarm1 hours register in this case
 */
/*! \def RTC_ALM1_DAYS_ADDRESS
    \brief RTC Addresses constants. Alarm1 days register in this case
 */
/*! \def RTC_ALM2_START_ADDRESS
    \brief RTC Addresses constants. Alarm2 start address in this case
 */
/*! \def RTC_ALM2_MINUTES_ADDRESS
    \brief RTC Addresses constants. Alarm2 minutes register in this case
 */
/*! \def RTC_ALM2_HOURS_ADDRESS
    \brief RTC Addresses constants. Alarm2 hours register in this case
 */
/*! \def RTC_ALM2_DAYS_ADDRESS
    \brief RTC Addresses constants. Alarm2 days register in this case
 */
/*! \def RTC_CONTROL_ADDRESS
    \brief RTC Addresses constants. Control register in this case
 */
/*! \def RTC_STATUS_ADDRESS
    \brief RTC Addresses constants. Status register in this case
 */
/*! \def RTC_MSB_TEMP_ADDRESS
    \brief RTC Addresses constants. MSB Temperature register in this case
 */
/*! \def RTC_LSB_TEMP_ADDRESS
    \brief RTC Addresses constants. LSB Temperature register in this case
 */
#define	RTC_SECONDS_ADDRESS			(uint8_t)0x00
#define	RTC_MINUTES_ADDRESS			(uint8_t)0x01
#define	RTC_HOURS_ADDRESS			(uint8_t)0x02
#define	RTC_DAYS_ADDRESS			(uint8_t)0x03
#define	RTC_DATE_ADDRESS			(uint8_t)0x04
#define	RTC_MONTH_ADDRESS			(uint8_t)0x05
#define	RTC_YEAR_ADDRESS			(uint8_t)0x06
#define	RTC_ALM1_START_ADDRESS		(uint8_t)0x07
#define	RTC_ALM1_SECONDS_ADDRESS	(uint8_t)0x07
#define	RTC_ALM1_MINUTES_ADDRESS	(uint8_t)0x08
#define	RTC_ALM1_HOURS_ADDRESS		(uint8_t)0x09
#define	RTC_ALM1_DAYS_ADDRESS		(uint8_t)0x0A
#define	RTC_ALM2_START_ADDRESS		(uint8_t)0x0B
#define	RTC_ALM2_MINUTES_ADDRESS	(uint8_t)0x0B
#define	RTC_ALM2_HOURS_ADDRESS		(uint8_t)0x0C
#define	RTC_ALM2_DAYS_ADDRESS		(uint8_t)0x0D
#define	RTC_CONTROL_ADDRESS			(uint8_t)0x0E
#define	RTC_STATUS_ADDRESS			(uint8_t)0x0F
#define	RTC_MSB_TEMP_ADDRESS		(uint8_t)0x11
#define	RTC_LSB_TEMP_ADDRESS		(uint8_t)0x12


/*! \def RTC_START_ADDRESS
    \brief RTC Addresses constants. Start address
 */
/*! \def RTC_DATA_SIZE
    \brief RTC Addresses constants. Number of Timekeeping Registers within RTC
 */
#define	RTC_START_ADDRESS		(uint8_t)0x00
#define RTC_DATA_SIZE 			0x13


/*! \def RTC_DATE_ADDRESS_2
    \brief RTC Addresses constants to use in function 'readRTC'. Use when only
    time and date wants to be read from the RTC
 */
/*! \def RTC_ALARM1_ADDRESS
    \brief RTC Addresses constants to use in function 'readRTC'. Use when time,
    date and alarm1 wants to be read from the RTC
 */
/*! \def RTC_ALARM2_ADDRESS
    \brief RTC Addresses constants to use in function 'readRTC'. Use when time,
    date, alarm1 and alarm2 wants to be read from the RTC
 */
#define	RTC_DATE_ADDRESS_2		6
#define	RTC_ALARM1_ADDRESS		10
#define	RTC_ALARM2_ADDRESS		13

/*! \def RTC_ALM1_MODE1
    \brief RTC Alarm Modes. Day of the week,hours,minutes and seconds match
 */
/*! \def RTC_ALM1_MODE2
    \brief RTC Alarm Modes. Date,hours,minutes and seconds match
 */
/*! \def RTC_ALM1_MODE3
    \brief RTC Alarm Modes. Hours,minutes and seconds match
 */
/*! \def RTC_ALM1_MODE4
    \brief RTC Alarm Modes. Minutes and seconds match
 */
/*! \def RTC_ALM1_MODE5
    \brief RTC Alarm Modes. Seconds match
 */
/*! \def RTC_ALM1_MODE6
    \brief RTC Alarm Modes. Once per second
 */
/*! \def RTC_ALM2_MODE1
    \brief RTC Alarm Modes. Day of the week,hours and minutes match
 */
/*! \def RTC_ALM2_MODE2
    \brief RTC Alarm Modes. Date,hours and minutes match
 */
/*! \def RTC_ALM2_MODE3
    \brief RTC Alarm Modes. Hours and minutes
 */
/*! \def RTC_ALM2_MODE4
    \brief RTC Alarm Modes. Minutes match
 */
/*! \def RTC_ALM2_MODE5
    \brief RTC Alarm Modes. Once per minute
 */
#define	RTC_ALM1_MODE1			0
#define	RTC_ALM1_MODE2			1
#define	RTC_ALM1_MODE3			2
#define	RTC_ALM1_MODE4			3
#define	RTC_ALM1_MODE5			4
#define	RTC_ALM1_MODE6			5

#define	RTC_ALM2_MODE1			0
#define	RTC_ALM2_MODE2			1
#define	RTC_ALM2_MODE3			2
#define	RTC_ALM2_MODE4			3
#define	RTC_ALM2_MODE5			4


/*! \def RTC_OFFSET
	\brief RTC Alarm Values. This option adds the time specified by the user to
	the actual time
 */
/*! \def RTC_ABSOLUTE
	\brief RTC Alarm Values. This option establishes the time specified by the
	user as the alarm time
 */
#define	RTC_OFFSET			0
#define	RTC_ABSOLUTE		1


/*! \def RTC_ALM1
    \brief RTC Alarm Values. Specifies Alarm1
 */
/*! \def RTC_ALM2
    \brief RTC Alarm Values. Specifies Alarm2
 */
#define	RTC_ALM1			1
#define	RTC_ALM2			2


/*! \def DAY_1
    \brief Days of the Week. Sunday in this case
 */
/*! \def DAY_2
    \brief Days of the Week. Monday in this case
 */
/*! \def DAY_3
    \brief Days of the Week. Tuesday in this case
 */
/*! \def DAY_4
    \brief Days of the Week. Wednesday in this case
 */
/*! \def DAY_5
    \brief Days of the Week. Thursday in this case
 */
/*! \def DAY_6
    \brief Days of the Week. Friday in this case
 */
/*! \def DAY_7
    \brief Days of the Week. Saturday in this case
 */
#define DAY_1 "Sun"
#define DAY_2 "Mon"
#define DAY_3 "Tue"
#define DAY_4 "Wed"
#define DAY_5 "Thu"
#define DAY_6 "Fri"
#define DAY_7 "Sat"

/*! \def RTC_ON
    \brief RTC Power Modes. ON in this case
 */
/*! \def RTC_OFF
    \brief RTC Power Modes. OFF in this case
 */
#define	RTC_ON	1
#define	RTC_OFF	0

/*! \def RTC_I2C_MODE
    \brief Used to set RTC.isON value
 */
/*! \def RTC_NORMAL_MODE
    \brief Used to set RTC.isON value
 */
#define	RTC_I2C_MODE	1
#define	RTC_NORMAL_MODE	0

/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)
#define DAYS_PER_WEEK (7UL)
#define SECS_PER_WEEK (SECS_PER_DAY * DAYS_PER_WEEK)
#define SECS_PER_YEAR (SECS_PER_WEEK * 52UL)
#define SECS_YR_2000  (946684800UL) // the time at the start of y2k

// leap year calulator expects year argument as years offset from 2000
#define LEAP_YEAR(Y)     ( ((2000+Y)>0) && !((2000+Y)%4) && ( ((2000+Y)%100) || !((2000+Y)%400) ) )


// API starts months from 1, this array starts from 0
static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

// Struct for storing time structures: YYMMDDHHMMS
typedef struct
{
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t day;   // day of week, sunday is day 1
  uint8_t date;
  uint8_t month;
  uint8_t year;
} 	timestamp_t;

/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspRTC Class
/*!
	WaspRTC Class defines all the variables and functions used for managing the RTC
 */
class WaspRTC
{
  private:
  public:
	//! class constructor
    /*!
	It does nothing
	\param void
	\return void
	*/
    WaspRTC();

	//! It converts a number from BCD to byte
    /*!
	\param uint8_t number : number to convert
	\return the number converted
	\sa BCD2byte(uint8_t high, uint8_t low), byte2BCD(uint8_t theNumber)
	 */
    uint8_t BCD2byte(uint8_t number);

	//! It converts a number from BCD to byte
    /*!
	\param uint8_t high : higher part of the number to convert
	\param uint8_t low : lower part of the number to convert
	\return the number converted
	\sa BCD2byte(uint8_t number), byte2BCD(uint8_t theNumber)
	 */
    uint8_t BCD2byte(uint8_t high, uint8_t low);

	//! It converts a number from int to BCD
    /*!
	\param uint8_t theNumber : number to convert
	\return the number converted
	\sa BCD2byte(uint8_t number), BCD2byte(uint8_t high, uint8_t low)
	 */
    uint8_t byte2BCD(uint8_t theNumber);

	//! Variable : Array for storing the value of the different RTC registers
    /*!
	Its size is defined by 'RTC_DATA_SIZE' constant
    */
    uint8_t registersRTC[RTC_DATA_SIZE];

	//! Variable : It stores if the RTC is ON(1) or OFF(0)
    /*!
	 */
	uint8_t isON;

	//! Variable : It stores the value of the year
    /*!
	 */
    uint8_t year;

	//! Variable : It stores the value of the month
    /*!
	 */
    uint8_t month;

	//! Variable : It stores the value of the day of the week
    /*!
	 */
    uint8_t day;

	//! Variable : It stores the value of the hours
    /*!
	 */
    uint8_t hour;

	//! Variable : It stores the value of the minutes
    /*!
	 */
    uint8_t minute;

	//! Variable : It stores the value of the seconds
    /*!
	 */
   	uint8_t second;

	//! Variable : It stores the value of the date(day of the week)
    /*!
	 */
    uint8_t date;

	//! Variable : It stores the value of the seconds for Alarm1
    /*!
	 */
	uint8_t second_alarm1;

	//! Variable : It stores the value of the minutes for Alarm1
   	/*!
	 */
	uint8_t minute_alarm1;

	//! Variable : It stores the value of the hours for Alarm1
    /*!
	 */
	uint8_t hour_alarm1;

	//! Variable : It stores the value of the day of the week/date for Alarm1
    	/*!
	 */
	uint8_t day_alarm1;

	//! Variable : It stores the value of the minutes for Alarm2
    /*!
	 */
	uint8_t minute_alarm2;

	//! Variable : It stores the value of the hours for Alarm2
    /*!
	 */
	uint8_t hour_alarm2;

	//! Variable : It stores the value of the day of the week/date for Alarm2
   	/*!
	 */
	uint8_t day_alarm2;

	//! Variable : It stores the alarm mode for the Alarm 1
   	/*!
	 */
	uint8_t alarm1Mode;

	//! Variable : It stores the alarm mode for the Alarm 2
    /*!
	 */
	uint8_t alarm2Mode;

	//! Variable : It stores the value of the temperature
    /*!
	*/
	float temp;

	//! Variable : It stores the RTC power mode
    /*!
	*/
	uint8_t _pwrMode;

	//! Variable : It stores the timeStamp in "dow, YY/MM/DD - HH:MM.SS"  format
    /*!
	 */
	char timeStamp[100];

	//! Variable : It stores the epoch time when getUnixTime() is called
    /*!
	 */
	unsigned long epoch;

	//! Variable : It stores the GMT
    /*!
	 */
	int8_t _gmt;

	//! Variable : It stores the alarm which generated the last RTC Alarm
    /*! Possible values are:
     * 	'1': Alarm1 triggered
     * 	'2': Alarm2 triggered
     * 	'3': Both alarms triggered
	 */
	uint8_t alarmTriggered;


	// RTC Internal Functions
	//! It resets the variables used through the library
    /*!
	\param void
	\return void
	 */
    void resetVars();

	//! It gets date and time
    /*!
	\param void
	\return a string containing date and time. These values are got from the
	library variables
	 */
    char* getTimestamp();

	//! It writes the date and time set in the corresponding variables to the RTC
    /*!
	\param void
	\return void
	\sa readRTC(uint8_t endAddress)
	 */
   	int writeRTC();

	//! It reads from the RTC the date,time and optionally alarm1 and alarm2,
	//! setting the corresponding variables
    /*!
	\param uint8_t endAddress : specifies the last RTC register we want to read
	\return void
	\sa writeRTC()
	 */
	int readRTC(uint8_t endAddress);

	//! It writes to the RTC the selected registers stored in 'registersRTC'
    /*!
	\param uint8_t theAddress : specifies the RTC register address where we
		want to start writing
	\return void
	\sa readRTCregister(uint8_t theAddress)
	 */
    int writeRTCregister(uint8_t theAddress);

	//! It reads from the RTC the selected register, and stores it in 'registersRTC' variable
    /*!
	\param uint8_t theAddress : specifies the RTC register address where we want to read from
	\return void
	\sa writeRTCregister(uint8_t theAddress)
	 */
    int readRTCregister(uint8_t theAddress);

	//! It configures the alarm mode and attaches the interruption
    /*!
	\param uint8_t alarmNum : specifies the alarm we want to use
	\param uint8_t alarmMode : specifies the alarm mode we want to use
	\return void
	 */
	void configureAlarmMode (uint8_t alarmNum, uint8_t alarmMode);

	//! It writes Alarm1 to the RTC
    /*!
	\param void
	\return void
	\sa writeRTCalarm2()
	 */
	int writeRTCalarm1();

	//! It writes Alarm2 to the RTC
    /*!
	\param void
	\return void
	\sa writeRTCalarm1()
	 */
	int writeRTCalarm2();

	//! It attaches the interruption to the defined pin
    /*!
	\param void
	\return void
	\sa detachInt()
	 */
	void attachInt(void);

	//! It detaches the interruption from the defined pin
    /*!
	\param void
	\return void
	\sa attachInt()
	 */
	void detachInt(void);

	// RTC User Functions

	//! It powers the RTC and initializes variables
    /*!
	\param void
	\return void
    */
	void ON();

	//! It closes I2C and powers off the RTC module
    /*!
	\param void
	\return void
	\sa close(),
    */
	void OFF();

	//! It closes I2C bus
    /*!
	\param void
	\return void
	 */
	void close();

	//! It sets Power Mode
    /*!
	\param uint8_t mode : RTC_ON or RTC_OFF
	\param uint8_t I2C_mode : RTC_I2C_MODE or RTC_NORMAL_MODE
	\return void
	\sa getMode()
	 */
	void setMode(uint8_t mode, uint8_t I2C_mode);

	//! It gets Power Mode
    /*!
	\param void
	\return the variable '_pwrMode' that contains the RTC power mode
	\sa setMode(uint8_t mode)
	 */
	uint8_t getMode();

	//! It calculates the day of the week based on the complete date
    /*!
	\param int y : year
	\param int m: month
	\param int d: day of the month
	\return int the day of the week (range from 1-7)
	 */
	int dow(int y, int m, int d);

	//! It sets in the RTC the specified date and time
    /*!
	\param const char* time : the time and date to set in the RTC. It looks
		like "YY:MM:DD:dow:hh:mm:ss"
	\return '0' if OK; '1' if error
	 */
	uint8_t setTime(const char* time);

	//! It sets in the RTC the specified date and time
    /*!
	\param uint8_t year : the year to set in the RTC
	\param uint8_t month : the month to set in the RTC
	\param uint8_t date : the date to set in the RTC
	\param uint8_t day_week : the day of the week to set in the RTC
	\param uint8_t hour : the hours to set in the RTC
	\param uint8_t minute : the minutes to set in the RTC
	\param uint8_t second : the seconds to set in the RTC
	\return '0' if OK; '1' if error
	 */
	uint8_t setTime(uint8_t year,
					uint8_t month,
					uint8_t date,
					uint8_t day_week,
					uint8_t hour,
					uint8_t minute,
					uint8_t second);

	//! It gets from the RTC the date and time, storing them in the
	//! corresponding variables
    /*!
	\param void
	\return a string containing the date and the time
	\sa setTime(const char* time), setTime(uint8_t year, uint8_t month, uint8_t
	date, uint8_t day_week, uint8_t hour, uint8_t minute, uint8_t second)
	 */
	char* getTime();

	//! It sets Alarm1 to the specified time. It also enables the corresponding
	//! RTC interruption
    /*!
	\param const char* time : the time to set for the Alarm 1. It looks like "DD:hh:mm:ss"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3,
		RTC_ALM1_MODE4, RTC_ALM1_MODE5, RTC_ALM1_MODE6
	\return void
	\sa setAlarm1(uint8_t day_date, uint8_t hour, uint8_t minute, uint8_t second,
	uint8_t offset, uint8_t mode), getAlarm1()
	 */
	uint8_t setAlarm1(const char* time, uint8_t offset, uint8_t mode);

	//! It sets Alarm1 to the specified time. It also enables the corresponding
	//! RTC interruption
    /*!
	\param uint8_t day_date : specifies the date or the day of the week to set
		the Alarm1 to
	\param uint8_t hour : specifies the hour to set the Alarm1 to
	\param uint8_t minute : specifies the minute to set the Alarm1 to
	\param uint8_t second : specifies the second to set the Alarm1 to
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3,
		RTC_ALM1_MODE4, RTC_ALM1_MODE5, RTC_ALM1_MODE6
	\return void
	\sa setAlarm1(const char* time, uint8_t offset, uint8_t mode), getAlarm1()
	 */
	uint8_t setAlarm1(	uint8_t day_date,
						uint8_t hour,
						uint8_t minute,
						uint8_t second,
						uint8_t offset,
						uint8_t mode);

	//! It gets Alarm1 date and time from the RTC, storing them in the
	//! corresponding variables
    /*!
	\param void
	\return a string containing the Alarm1 date and the time
	 */
	char* getAlarm1();

	//! It sets Alarm2 to the specified time. It also enables the corresponding
	//! RTC interruption
    /*!
	\param const char* time : the time to set for the Alarm 1. It looks like "DD:hh:mm"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM2_MODE1, RTC_ALM2_MODE2, RTC_ALM2_MODE3,
		RTC_ALM2_MODE4, RTC_ALM2_MODE5
	\return void
	 */
	uint8_t setAlarm2(const char* time, uint8_t offset, uint8_t mode);

	//! It sets Alarm2 to the specified time. It also enables the corresponding
	//! RTC interruption
   	/*!
	\param uint8_t day_date : specifies the date or the day of the week to set the Alarm2 to
	\param uint8_t hour : specifies the hour to set the Alarm2 to
	\param uint8_t minute : specifies the minute to set the Alarm2 to
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM2_MODE1, RTC_ALM2_MODE2, RTC_ALM2_MODE3,
		RTC_ALM2_MODE4, RTC_ALM2_MODE5
	\return void
	\sa setAlarm2(const char* time, uint8_t offset, uint8_t mode), getAlarm2()
	 */
	uint8_t setAlarm2(	uint8_t day_date,
						uint8_t hour,
						uint8_t minute,
						uint8_t offset,
						uint8_t mode);

	//! It gets Alarm2 date and time from the RTC, storing them in the
	//! corresponding variables
   	/*!
	\param void
	\return a string containing the Alarm2 date and the time
	\sa setAlarm2(const char* time, uint8_t offset, uint8_t mode),
	setAlarm2(uint8_t day_date, uint8_t hour, uint8_t minute, uint8_t offset, uint8_t mode)
	 */
	char* getAlarm2();

	//! It clears bits A1F and A2F, necessary to be able to catch interrupts
	//! after previous interrupts
    /*!
	\param void
	\return void
	 */
	void clearAlarmFlag();

	//! It clears A1IE in control register to disable the Alarm1
    /*!
	\param void
	\return void
	 */
	void disableAlarm1();

	//! It clears A2IE in control register to disable the Alarm2
    /*!
	\param void
	\return void
	 */
	void disableAlarm2();

	//! It gets the temperature from the RTC temperature sensor
    /*!
	\param void
	\return temperature
	 */
	float getTemperature();

	//! It gets the timestamp (in seconds) from 1st January 1970
    /*! This function calls getTime() function to get actual values and then
     * calculate the epoch time from RTC time and date
	\param void
	\return timestamp
	 */
	unsigned long getEpochTime();

	//! It gets the timestamp (in seconds) from 1st January 1970
    /*! This function uses the input date and time to calculate the epoch time.
     * It is necessary to indicate year, month, day, hour, minute and second
	\param 	uint8_t Year: It is specified as two ciphers. i.e. 2014 is 14
			uint8_t Month: month to be used.
			uint8_t Date: day of month to be used.
			uint8_t Hour: hour to be used.
			uint8_t Minute: minute to be used.
			uint8_t Second: second to be used.
	\return timestamp
	 */
	unsigned long getEpochTime(	uint8_t Year,
								uint8_t Month,
								uint8_t Date,
								uint8_t Hour,
								uint8_t Minute,
								uint8_t Second);

  //! It gets the timestamp (in seconds) from 1st January 1970
  /*! This function uses the input date and time to calculate the epoch time.
  * It is necessary to indicate year, month, day, hour, minute and second
  \param 	uint8_t Year: It is specified as two ciphers. i.e. 2014 is 14
    uint8_t Month: month to be used.
    uint8_t Date: day of month to be used.
    uint8_t Hour: hour to be used.
    uint8_t Minute: minute to be used.
    uint8_t Second: second to be used.
  \return timestamp
  */
  unsigned long getEpochTime(	uint8_t Year,
              	uint8_t Month,
              	uint8_t Date,
              	uint8_t Hour,
              	uint8_t Minute,
              	uint8_t Second,
                uint8_t Timezone);

	//! It gets the year, month, day, hour, minute and second values from input
	//! epoch time
    /*! This function calculates the structure as an ABSOLUTE time. For example,
	* if timeInput equals to 1416933867, this function stores the following
	* data within the structure: Tue, 25 Nov 2014 16:44:27 GMT
	\param 	unsigned long timeInput: input epoch time
	\param 	timestamp_t *tm: pointer to a structure where time and date is stored
	\return void
	 */
	void breakTimeAbsolute(unsigned long timeInput, timestamp_t *tm);

	//! It gets the offset time from input seconds time
    /*! This function calculates the structure as a relative OFFSET time. For
	* example, if timeInput equals to 411361, this function stores the following
	* data within the structure: 4 days, 18 hours, 16 minutes and 1 seconds.
	\param 	unsigned long timeInput: input seconds time
	\param 	timestamp_t *tm: pointer to a structure where time and date is stored
	\return void
	 */
	void breakTimeOffset(unsigned long timeInput, timestamp_t *tm);

	//! It sets the GMT
    /*! This function set the GMT variable and check if the param given is a
     * valid GMT value, if gmt is not a valid value it will save set GMT 0
	\param 	int8_t gmt: input gmt
	\return 	uint8_t 1 if not valid GMT, 0 otherwise
	 */
	uint8_t setGMT(int8_t gmt);

	//! It gets GMT value
    /*! This function get the GMT variable
	\param 	void
	\return int8_t _gmt
	 */
	int8_t getGMT();

	//! It gets alarm triggered from the RTC
    /*! This function gets the two last bit of the RTC status register and
     * returns the number of the alarm has been triggered
	\param 	void
	\return uint8_t 1 if alarm 1 has been triggered
					2 if alarm 2 has been triggered
					3 if both alarms have been triggered
	 */
	uint8_t getAlarmTriggered();

	/*! It sets the RTC alarm2 for generating a Waspmote reset
	\param uint16_t minutesWatchdog indicates the number of minute hand changes
		to perform before the reset is done
	\return void
	*/
	void setWatchdog(uint16_t minutesWatchdog);

	/*! It gets the RTC alarm2 settings for generating a Waspmote reset
	\return pointer to the buffer which stores the watchdog time settings
	*/
	char* getWatchdog();

	/*! It disables the RTC alarm2 so no reset will be done
	\return void
	*/
	void unSetWatchdog(void);

	/*! It disables the SQW output from the RTC
	\return void
	*/
	void disableSQW();
};

extern WaspRTC RTC;

#endif
