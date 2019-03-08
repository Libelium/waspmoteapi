/*! \file WaspPWR.h
    \brief Library for managing Waspmote Power & Energy Modes
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		3.0
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
#include <WaspUART.h>


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
#define	ALL_ON			0
#define	SENS_OFF		1		// redefined
#define	SOCKET0_OFF		2
#define	ALL_OFF			3		//SENS_OFF | SOCKET0_OFF
#define SOCKET0_ON		5
#define	SENSOR_ON		6


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
extern volatile uint16_t 	WaspRegister;
extern volatile uint16_t 	WaspRegisterSensor;


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
	  
    /*!
    \brief	It sets a certain internal peripheral on 
	\param 	uint8_t peripheral : the peripheral to set on
	\return void
	*/ 
	void setIPF(uint8_t peripheral);
	
    /*!
    \brief	It sets a certain internal peripheral off 
	\param 	uint8_t peripheral : the peripheral to set off
	\return void
	 */ 
	void resetIPF(uint8_t peripheral);
	
    /*!
    \brief 	It gets the whole IPR 
	\param 	void
	\return the IPRA flag
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
	
    /*!
    \brief	It sets ON/OFF 3V3 or 5V switches
	\param 	uint8_t type:
		\arg SENS_3V3
		\arg SENS_5V
	\param 	uint8_t mode: 
		\arg SENS_ON
		\arg SENS_OFF
	\return void
	 */ 
	void setSensorPower(uint8_t type, uint8_t mode);
	
    /*!
    \brief It enables or disables watchdog interruption
	\param uint8_t mode: 
		\arg WTD_ON 
		\arg WTD_OFF		
	\param uint8_t timer: 
		\arg WTD_16MS
		\arg WTD_32MS
		\arg WTD_64MS
		\arg WTD_128MS
		\arg WTD_250MS
		\arg WTD_500MS
		\arg WTD_1S
		\arg WTD_2S
		\arg WTD_4S
		\arg WTD_8S
	\return void
	 */ 
	void setWatchdog(uint8_t mode, uint8_t timer);
	
	/*!
    \brief It switches off the specified Waspmote switches
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	 */ 
	void switchesOFF(uint8_t option);
	
    /*!
    \brief It switches on the specified Waspmote switches
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	 */
	void switchesON(uint8_t option);

    /*!
    \brief It sets the microcontroller to the lowest consumption sleep mode
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	 */
	void sleep(uint8_t option);
	
    /*!
    \brief It sets the microcontroller to the lowest consumption sleep mode 
		enabling the watchdog
	\param uint8_t timer : WTD_16MS, WTD_32MS, WTD_64MS, WTD_128MS, WTD_250MS, 
	WTD_500MS, WTD_1S, WTD_2S, WTD_4S or WTD_8S
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF
	\return void
	 */
	void sleep(uint8_t timer, uint8_t option);
	

    /*!
    \brief It sets the microcontroller to the lowest consumption sleep mode 
		enabling RTC interruption
	\param const char* time2wake : string that indicates the time to wake up. 
		It looks like "dd:hh:mm:ss"
	\param uint8_t offset: 	
		\arg RTC_OFFSET 
		\arg RTC_ABSOLUTE
	\param uint8_t mode: 
		\arg RTC_ALM1_MODE1 
		\arg RTC_ALM1_MODE2
		\arg RTC_ALM1_MODE3 
		\arg RTC_ALM1_MODE4 
		\arg RTC_ALM1_MODE5
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF, SOCKET0_OFF, SENSOR_ON
	\return void
	 */
	void deepSleep(const char* time2wake, uint8_t offset, uint8_t mode);
	void deepSleep(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option);
	
	
    /*!
    \brief It switches off the general switch enabling RTC interruption
	\param const char* time2wake : string that indicates the time to wake up. 
		It looks like "dd:hh:mm:ss"
	\param uint8_t offset: 	
		\arg RTC_OFFSET 
		\arg RTC_ABSOLUTE
	\param uint8_t mode : 		
		\arg RTC_ALM1_MODE1 
		\arg RTC_ALM1_MODE2
		\arg RTC_ALM1_MODE3 
		\arg RTC_ALM1_MODE4 
		\arg RTC_ALM1_MODE5
	\return void
	 */
	void hibernate(const char* time2wake, uint8_t offset, uint8_t mode); 
	
	
	/*!
    \brief  It gets the remaining battery %
	\return the remaining battery in % unit
	 */
	uint8_t	getBatteryLevel(); 
	

    /*!
    \brief  It gets the remaining battery in volts
	\return the remaining battery in volts
	 */
	float getBatteryVolts();
	

    /*!
    \brief  It gets the current charging the battery
	\return the current charging the battery in mA
	 */
	uint16_t getBatteryCurrent();
	
	
    /*!
    \brief 	It gets the state of the battery charger 
	\return the he state of the battery charger (1 Battery is being charged, 0 battery is not being charged)
	 */
	bool getChargingState();

    /*!
    \brief  It closes I2C bus
	\return void
	 */
	void closeI2C();

    /*!
    \brief  It checks if Hibernate has generated the reset
	\return void
	 */
	void ifHibernate();
        
    /*!
    \brief  It restarts Waspmote
    \return void
    */
    void reboot();
    
    /*!
    \brief  It cleans the interruption signal
    \return void
    */  
    void clearInterruptionPin();
        
    /*!
    \brief  It prints the 'intFlag' bitmap
    \return void
    */      
    void printIntFlag();
    
    /*!
    \brief  Manage SOCKET0 or SOCKET1 to set them to ON/OFF state
    \return void
    */ 
    void powerSocket(uint8_t socket, uint8_t state);
    
    /*!
    \brief  Check if XBee modules are connected to SOCKET0
    \return void
    */ 
    void checkPeripherals();
    
};

extern WaspPWR PWR;

#endif

