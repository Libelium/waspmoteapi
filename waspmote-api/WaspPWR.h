/*! \file WaspPWR.h
    \brief Library for managing Waspmote Power & Energy Modes
    
    Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.2
    Design:			David Gascón
    Implementation:	Alberto Bielsa, David Cuartielles, Yuri Carmona

*/

 /*! \def WaspPWR_h
    \brief The library flag
    
  */
#ifndef WaspPWR_h
#define WaspPWR_h


/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def WTD_ON
 \brief Watchdog possible states. ON in this case
 */
/*! \def WTD_OFF
 \brief Watchdog possible states. OFF in this case
 */
#define	WTD_ON	1
#define	WTD_OFF	2


/*******************************************************************************
 * WATCHDOG POSSIBLE TIMERS
 ******************************************************************************/
/*! \def WTD_16MS
    \brief Watchdog possible timers. 16 miliseconds in this case
 */
/*! \def WTD_32MS
    \brief Watchdog possible timers. 32 miliseconds in this case
 */
/*! \def WTD_64MS
    \brief Watchdog possible timers. 64 miliseconds in this case
 */
/*! \def WTD_128MS
    \brief Watchdog possible timers. 128 miliseconds in this case
 */
/*! \def WTD_250MS
    \brief Watchdog possible timers. 250 miliseconds in this case
 */
/*! \def WTD_500MS
    \brief Watchdog possible timers. 500 miliseconds in this case
 */
/*! \def WTD_1S
    \brief Watchdog possible timers. 1 second in this case
 */
/*! \def WTD_2S
    \brief Watchdog possible timers. 2 seconds in this case
 */
/*! \def WTD_4S
    \brief Watchdog possible timers. 4 seconds in this case
 */
/*! \def WTD_8S
    \brief Watchdog possible timers. 8 seconds in this case
 */
#define	WTD_16MS	0
#define	WTD_32MS	1
#define	WTD_64MS	2
#define	WTD_128MS	3
#define	WTD_250MS	4
#define	WTD_500MS	5
#define	WTD_1S		6
#define	WTD_2S		7
#define	WTD_4S		8
#define	WTD_8S		9



/*******************************************************************************
 * SLEEP OPTIONS
 ******************************************************************************/
/*! \def SENS_OFF
    \brief Sleep Options. Set sensor power supply OFF (5V and 3V3)
 */
/*! \def SOCKET0_OFF
    \brief Sleep Options. Switch related with SOCKET0 power supply is set OFF
 */
/*! \def ALL_OFF
    \brief Sleep Options. All options are switched off
 */
/*! \def ALL_ON
    \brief Sleep Options. Do not switch off anything
 */
#define	SENS_OFF		1
#define	SOCKET0_OFF		2
#define	ALL_OFF			SENS_OFF | SOCKET0_OFF
#define	ALL_ON			0

//! DEPRECATED definitions. *** FIXME: To be deleted
#define BAT_OFF 		ALL_ON
//#define RTC_OFF 		ALL_ON //! It was redefined
#define UART0_OFF 		SOCKET0_OFF
#define UART1_OFF 		ALL_ON


/*! \def HIB_ADDR
    \brief EEPROM Address for hibernating
 */
/*! \def HIB_VALUE
    \brief EEPROM Value for hibernating
 */
#define	HIB_ADDR	0
#define	HIB_VALUE	10

extern volatile uint16_t	intFlag;
extern volatile uint16_t 	intConf;
extern volatile uint8_t		intCounter;
extern volatile uint8_t		intArray[8];
extern volatile unsigned long 	WaspRegister;


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspPWR Class
/*!
	WaspPWR Class defines all the variables and functions used for managing 
	Waspmote Energy and Power Modes
 */
class WaspPWR
{
  private:
	  
	//! It sets a certain internal peripheral on 
    /*!
	\param uint8_t peripheral : the peripheral to set on
	\return void
	\sa resetIPF(uint8_t peripheral), getIPF()
	*/ 
	void setIPF(uint8_t peripheral);
	
	//! It sets a certain internal peripheral off 
    /*!
	\param uint8_t peripheral : the peripheral to set off
	\return void
	\sa setIPF(uint8_t peripheral), getIPF()
	 */ 
	void resetIPF(uint8_t peripheral);
	
	//! It gets the whole IPR 
    /*!
	\param void
	\return the IPRA flag
	\sa setIPF(uint8_t peripheral), resetIPF(uint8_t peripheral)
	 */
	uint8_t getIPF();

  public:	
      	
	// VARIABLES
    uint8_t IPRA; //20090224 -- moved to wiring.c
    uint8_t IPRB;
	
	// CONSTRUCTOR
	//! class constructor
    /*!	It does nothing
	\param void
	\return void
	 */ 
    WaspPWR();
	
	//! It sets ON/OFF 3V3 or 5V switches
    	/*!
	\param uint8_t type : SENS_3V3 or SENS_5V
	\param uint8_t mode : SENS_ON or SENS_OFF
	\return void
	 */ 
	void 	setSensorPower(uint8_t type, uint8_t mode);
	
	//! It enables or disables watchdog interruption
    	/*!
	\param uint8_t mode : WTD_ON or WTD_OFF
	\param uint8_t timer : WTD_16MS, WTD_32MS, WTD_64MS, WTD_128MS, WTD_250MS, 
	WTD_500MS, WTD_1S, WTD_2S, WTD_4S or WTD_8S
	\return void
	 */ 
	void 	setWatchdog(uint8_t mode, uint8_t timer);
	
	//! It switches off the specified Waspmote switches
    	/*!
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	\sa switchesON(uint8_t option)
	 */ 
	void	switchesOFF(uint8_t option);
	
	//! It switches on the specified Waspmote switches
    	/*!
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	\sa switchesOFF(uint8_t option)
	 */
	void	switchesON(uint8_t option);
	
	//! It sets the microcontroller to the lowest consumption sleep mode
    /*!
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	\sa sleep(uint8_t timer, uint8_t option), deepSleep(const char* time2wake, 
	uint8_t offset, uint8_t mode, uint8_t option), 
	hibernate(const char* time2wake, uint8_t offset, uint8_t mode)
	 */
	void	sleep(uint8_t option);
	
	//! It sets the microcontroller to the lowest consumption sleep mode 
	//! enabling the watchdog
    /*!
	\param uint8_t timer : WTD_16MS, WTD_32MS, WTD_64MS, WTD_128MS, WTD_250MS, 
	WTD_500MS, WTD_1S, WTD_2S, WTD_4S or WTD_8S
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	\sa sleep(uint8_t option)
	\sa deepSleep(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option)
	\sa hibernate(const char* time2wake, uint8_t offset, uint8_t mode)
	 */
	void	sleep(uint8_t timer, uint8_t option);
	
	//! It sets the microcontroller to the lowest consumption sleep mode 
	//! enabling RTC interruption
    /*!
	\param const char* time2wake : string that indicates the time to wake up. 
	It looks like "dd:hh:mm:ss"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3, 
	RTC_ALM1_MODE4 or RTC_ALM1_MODE5
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	\sa sleep(uint8_t option)
	\sa sleep(uint8_t timer, uint8_t option)
	\sa hibernate(const char* time2wake, uint8_t offset, uint8_t mode)
	 */
	void	deepSleep(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option);
	
	//! It switches off the general switch enabling RTC interruption
    /*!
	\param const char* time2wake : string that indicates the time to wake up. 
	It looks like "dd:hh:mm:ss"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3, 
	RTC_ALM1_MODE4 or RTC_ALM1_MODE5
	\return void
	\sa sleep(uint8_t option)
	\sa sleep(uint8_t timer, uint8_t option)
	\sa deepSleep(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option)
	 */
	void 	hibernate(const char* time2wake, uint8_t offset, uint8_t mode); 
	
	//! It gets the remaining battery %
    /*!
	\return the remaining battery %
	 */
	uint8_t	getBatteryLevel(); 
	
	//! It gets the remaining battery in volts
    /*!
	\return the remaining battery in volts %
	 */
	float  getBatteryVolts();
	
	//! It closes I2C bus
    /*!
	\return void
	 */
	void 	closeI2C();
	
	//! It checks if Hibernate has generated the reset
    /*!
	\return void
	 */
	void	ifHibernate();
        
    //! It restarts Waspmote
    /*!
    \return void
    */
    void	reboot();
    
    //! It cleans the interruption signal
    /*!
    \return void
    */  
    void clearInterruptionPin();
        
    //! It prints the 'intFlag' bitmap
    /*!
    \return void
    */      
    void printIntFlag();
};

extern WaspPWR PWR;

#endif

