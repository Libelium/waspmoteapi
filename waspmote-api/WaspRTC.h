/*! \file WaspRTC.h
    \brief Library for managing the RTC
    
    Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
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
  
    Version:		1.0
    Design:			David Gascón
    Implementation:	Alberto Bielsa, David Cuartielles, Marcos Yarza

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
#define	RTC_SECONDS_ADDRESS		0x00	
#define	RTC_MINUTES_ADDRESS		0x01
#define	RTC_HOURS_ADDRESS		0x02
#define	RTC_DAYS_ADDRESS		0x03
#define	RTC_DATE_ADDRESS		0x04
#define	RTC_MONTH_ADDRESS		0x05
#define	RTC_YEAR_ADDRESS		0x06
#define	RTC_ALM1_START_ADDRESS		0x07
#define	RTC_ALM1_SECONDS_ADDRESS	0x07
#define	RTC_ALM1_MINUTES_ADDRESS	0x08
#define	RTC_ALM1_HOURS_ADDRESS		0x09
#define	RTC_ALM1_DAYS_ADDRESS		0x0A
#define	RTC_ALM2_START_ADDRESS		0x0B
#define	RTC_ALM2_MINUTES_ADDRESS	0x0B
#define	RTC_ALM2_HOURS_ADDRESS		0x0C
#define	RTC_ALM2_DAYS_ADDRESS		0x0D
#define	RTC_CONTROL_ADDRESS			0x0E
#define	RTC_STATUS_ADDRESS			0x0F
#define	RTC_MSB_TEMP_ADDRESS		0x11
#define	RTC_LSB_TEMP_ADDRESS		0x12


/*! \def RTC_START_ADDRESS
    \brief RTC Addresses constants. Start address
 */
/*! \def RTC_ADDRESS
    \brief RTC Addresses constants. I2C RTC Address
 */
/*! \def RTC_DATA_SIZE
    \brief RTC Addresses constants. RTC Data size
 */
#define	RTC_START_ADDRESS		0x00
#define RTC_ADDRESS 			0x68
#define RTC_DATA_SIZE 			0x12


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
   	void writeRTC();
	
	//! It reads from the RTC the date,time and optionally alarm1 and alarm2, 
	//! setting the corresponding variables
    /*!
	\param uint8_t endAddress : specifies the last RTC register we want to read
	\return void
	\sa writeRTC()
	 */
	void readRTC(uint8_t endAddress);
	
	//! It writes to the RTC the selected registers stored in 'registersRTC'
    /*!
	\param uint8_t theAddress : specifies the RTC register address where we 
		want to start writing
	\return void
	\sa readRTCregister(uint8_t theAddress)
	 */
    void writeRTCregister(uint8_t theAddress);
	
	//! It reads from the RTC the selected register, and stores it in 'registersRTC' variable
    /*!
	\param uint8_t theAddress : specifies the RTC register address where we want to read from
	\return void
	\sa writeRTCregister(uint8_t theAddress)
	 */
    void readRTCregister(uint8_t theAddress);
	
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
	void writeRTCalarm1();
	
	//! It writes Alarm2 to the RTC 
    /*!
	\param void
	\return void
	\sa writeRTCalarm1()
	 */
	void writeRTCalarm2();
	
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
	
	//! It opens I2C bus and powers the RTC
    /*!
	\param void
	\return void
	\sa close(), begin()
    */ 
	void ON();
	
	//! It closes I2C and powers off the RTC module
    /*!
	\param void
	\return void
	\sa close(), begin()
    */ 
	void OFF();
	
	//! It inits the I2C bus and the variables reading them from the RTC
    /*!
	\param void
	\return void
	 */
	void begin();
	
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
	\return void
	\sa setTime(uint8_t year, uint8_t month, uint8_t date, uint8_t day_week, 
	uint8_t hour, uint8_t minute, uint8_t second), getTime()
	 */
	void setTime(const char* time);
	
	//! It sets in the RTC the specified date and time
    /*!
	\param uint8_t year : the year to set in the RTC
	\param uint8_t month : the month to set in the RTC
	\param uint8_t date : the date to set in the RTC
	\param uint8_t day_week : the day of the week to set in the RTC
	\param uint8_t hour : the hours to set in the RTC
	\param uint8_t minute : the minutes to set in the RTC
	\param uint8_t second : the seconds to set in the RTC
	\return void
	\sa setTime(const char* time), getTime()
	 */
	void setTime(	uint8_t year, 
					uint8_t month,
					uint8_t date, 
					uint8_t day_week, 
					uint8_t hour, 
					uint8_t minute, 
					uint8_t second	);
	
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
	void setAlarm1(const char* time, uint8_t offset, uint8_t mode);
	
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
	void setAlarm1(	uint8_t day_date, 
					uint8_t hour, 
					uint8_t minute, 
					uint8_t second, 
					uint8_t offset, 
					uint8_t mode	);
	
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
	void setAlarm2(const char* time, uint8_t offset, uint8_t mode);
	
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
	void setAlarm2(	uint8_t day_date, 
					uint8_t hour, 
					uint8_t minute, 
					uint8_t offset, 
					uint8_t mode	);
	
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
};

extern WaspRTC RTC;

#endif

