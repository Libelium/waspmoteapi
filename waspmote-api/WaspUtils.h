/*! \file WaspUtils.h
    \brief Library containing useful general functions
    
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
    Design:			David Gascon
    Implementation:	Alberto Bielsa, David Cuartielles

*/
  
  
/*! \def Wasputils_h
    \brief The library flag
    
 */
#ifndef Wasputils_h
#define Wasputils_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>
#include <avr/eeprom.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def LED_ON
    \brief sets LED ON
 */
/*! \def LED_OFF
    \brief sets LED OFF
 */
#define	LED_ON	1
#define	LED_OFF	0


/*! \def EEPROM_OTA_AUTHKEY
    \brief Authentication key EEPROM address
 */
/*! \def EEPROM_FRAME_MOTEID
    \brief MOTEID EEPROM address
 */
/*! \def EEPROM_FRAME_SEQUENCE
    \brief Sequence EEPROM address
 */ 
/*! \def EEPROM_PROG_VERSION
    \brief EEPROM address for program version
 */ 
/*! \def EEPROM_SERIALID_START
    \brief Starting address for the backup of Serial ID of Waspmote (4B)
 */
/*! \def EEPROM_START
    \brief First EEPROM's writable address. There is a 1kB reserved area from 
    address 0 to address 1023.
 */
#define EEPROM_OTA_FLAG				1
#define EEPROM_OTA_RETRIES			98
#define EEPROM_OTA_AUTHKEY			107
#define EEPROM_FRAME_MOTEID			147
#define EEPROM_FRAME_SEQUENCE		163
#define EEPROM_PROG_VERSION 		225
#define EEPROM_PROG_VERSION_BACKUP 	226
#define EEPROM_SERIALID_START 		227
#define EEPROM_START 				1024





//! Variable :  Waspmote bootloader version
extern volatile uint8_t _boot_version;

//! Variable :  Waspmote serial id
extern volatile uint8_t _serial_id[8];


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspUtils Class
/*!
	WaspUtils Class defines all the variables and functions used to set LEDs, 
	multiplexor and useful general functions
 */
class WaspUtils
{
  private:
  
  public:

  //! class constructor
  /*!
  It does nothing
  \param void
  \return void
  */
  WaspUtils(void);


  //! It sets the specified LED to the specified state(ON or OFF)
  /*!
  \param uint8_t led : the LED to set ON/OFF
  \param uint8_t state : the state to set the LED
  \return void
  \sa getLED(uint8_t led), blinkLEDs(uint16_t time)
   */
  void	setLED(uint8_t led, uint8_t state);
  
  
   //! It sets external LED to the specified state(ON or OFF)
  /*!
   \param uint8_t state : the state to set the LED
  \return void
  */
  void	setExternalLED(uint8_t state);
  
  
  //! It gets the state of the specified LED
  /*!
  \param uint8_t led : the LED to get the state
  \return the state of the LED
  \sa setLED(uint8_t led, uint8_t state), blinkLEDs(uint16_t time)
   */
  uint8_t getLED(uint8_t led);
  
  //! It gets the state of external LED
  /*!
  
  \return the state of the LED
  \sa setLED(uint8_t led, uint8_t state), blinkLEDs(uint16_t time)
   */
  uint8_t getExternalLED();
  
  
  
  
  //! It blinks LEDs, with the specified time for blinking
  /*!
  \param uint16_t time : time for blinking
  \return void
  \sa setLED(uint8_t led, uint8_t state), getLED(uint8_t led)
   */
  void blinkLEDs(uint16_t time);
  
	//! It blinks the red LED once during 200ms
	void blinkRedLED();
	
	//! It blinks the red LED once during 'time' milliseconds
	/*!
	\param uint16_t time : time for blinking
	\return void
	*/
	void blinkRedLED( uint16_t time );
	
	//! It blinks the red LED for 'num' times, and during 'time' milliseconds
	/*!
	\param uint16_t time : time for blinking
	\param uint8_t num : number of blink actions
	\return void
	*/
	void blinkRedLED( uint16_t time, uint8_t num );
	
	//! It blinks the green LED once during 200ms
	void blinkGreenLED();
	
	//! It blinks the green LED once during 'time' milliseconds
	/*!
	\param uint16_t time : time for blinking
	\return void
	*/
	void blinkGreenLED( uint16_t time );
	
	//! It blinks the green LED for 'num' times, and during 'time' milliseconds
	/*!
	\param uint16_t time : time for blinking
	\param uint8_t num : number of blink actions
	\return void
	*/
	void blinkGreenLED( uint16_t time, uint8_t num );
  
  
  //! It blinks LED, with the specified time for blinking
  /*!
  \param uint16_t time : time for blinking
  \return void
  \sa setLED(uint8_t led, uint8_t state), getLED(uint8_t led)
   */
  void externalLEDBlink(uint16_t time);
  
  
  //! It maps 'x' from the read range to the specified range
  /*!
  \param long x : value to map
  \param long in_min : minimum input value for 'x'
  \param long in_max : maximum input value for 'x'
  \param long out_min : minimum output value for 'x'
  \param long out_max : maximum output value for 'x'
  \return the value 'x' mapped to the [out_min,out_max] range
   */
  long map(long x, long in_min, long in_max, long out_min, long out_max);

  //! It sets multiplexer on UART_1 to the desired combination
  /*! It sets multiplexer on UART_1 to the desired combination. 
    Possible combinations are:  
  	MUX_LOW = 0 & MUX_HIGH = 1 ---> GPS MODULE
  	MUX_LOW = 1 & MUX_HIGH = 1 ---> SOCKET1
  	MUX_LOW = 1 & MUX_HIGH = 0 ---> AUX1 MODULE
  	MUX_LOW = 0 & MUX_HIGH = 0 ---> AUX2 MODULE
  
  \param uint8_t MUX_LOW : low combination part
  \param uint8_t MUX_HIGH : high combination part
  \return void
  \sa setMuxGPS(), setMuxSocket1(), setMuxAux1(), setMuxAux2()
   */
  void setMux(uint8_t MUX_LOW, uint8_t MUX_HIGH);
  
  //! It sets multiplexer on UART_1 to GPS module
  /*!  
  \return void
   */
  void setMuxGPS();
  
  //! It sets multiplexer on UART_1 to SOCKET1
  /*!  
  \return void
   */
  void setMuxSocket1();
  
  //! It sets multiplexer on UART_1 to enable AUX1 module
  /*!  
  \return void
   */
  void setMuxAux1();
  
  //! It sets multiplexer on UART_1 to enable AUX2 module
  /*!  
  \return void
   */
  void setMuxAux2();  
   
  //! It sets multiplexer on UART_0 to USB
  /*!
  \return void
   */
  void setMuxUSB();  

   
  //! It switches off the multiplexer on UART0 and UART1
  /*!
  \return void
   */
  void muxOFF();  
    
  //! It switches off the multiplexer on UART0
  /*!
  \return void
   */
  void muxOFF0(); 
  
  //! It switches off the multiplexer on UART1
  /*!
  \return void
   */
  void muxOFF1(); 
  
  //! set multiplexer on UART_0 to SOCKET0
  /*!
  \return void
   */
  void setMuxSocket0();

  //! It reads a value from the specified EEPROM address
  /*!
  \param int address : EEPROM address to read from
  \return the value read from EEPROM address
  \sa writeEEPROM(int address, uint8_t value)
   */
  uint8_t readEEPROM(int address);
  
  //! It writes the specified value to the specified EEPROM address
  /*!
  \param int address : EEPROM address to write to
  \param uint8_t value: value to write to the EEPROM
  \return void
  \sa readEEPROM(int address)
   */
  void writeEEPROM(int address, uint8_t value);
   
  //! It writes the mote identifier to the EEPROM[147-162]
  /*!
  \param char* moteID: identifier to write to the EEPROM
  \return void 
   */
  void setID(char* moteID);
   
  //! It writes the authentication key to the EEPROM[107-114]
  /*!
  \param char* authkey: authentication key to write to the EEPROM
  \return void 
   */
  void setAuthKey(char* authkey);
   
  //! It reads the Waspmote unique serial identifier
  /*!
  \return unsigned long: Waspmote unique serial identifier
   */
  unsigned long readSerialChip();
   
  //! It reads the Waspmote unique serial identifier
  /*! If fails, we try to read from EEPROM
  \return unsigned long: Waspmote unique serial identifier
   */
  unsigned long readSerialID();  
  
  //! It sets the Waspmote unique serial identifier to eeprom
  /*!
  \return bool: 'true' if OK; 'false' otherwise
   */
  bool setSerialEEPROM( unsigned long serial );
  
  //! It gets the Waspmote unique serial identifier from eeprom
  /*!
  \return unsigned long: the serial read from eeprom memory
   */
  unsigned long getSerialEEPROM();
  
  //! It reads the DS1820 temperature sensor
  /*!
  \param  uint8_t pin: digital MCU pin used for one wire comm
  \return float: Temperature of DS1820 sensor
   */
  float readTempDS1820( uint8_t pin );  
  
  //! It reads the DS1820 temperature sensor
  /*!
  \param  uint8_t pin: digital MCU pin used for one wire comm
  \param  bool is3v3: indicates if 3v3 power supply is needed for powering sensor
  \return float: Temperature of DS1820 sensor
   */
  float readTempDS1820( uint8_t pin, bool is3v3 );
  
  //! It reads the temperature sensor
  /*!
  \return float: Temperature of the sensor
   */
  float readTemperature();
  
  //! It reads the humidity sensor
  /*!
  \return uint8_t: Value of the humidity sensor
   */
  uint8_t readHumidity();
  
  //! It reads the light sensor
  /*!
  \return uint8_t: Value of the light sensor
   */
  uint8_t readLight();
  
 
    
  //! It converts a decimal number into a string
  /*!
  \param long num : number to convert
  \param char* numb : string where store the converted number
  \return the number of digits of the number
  \sa  str2hex(char* str), str2hex(uint8_t* str)
   */
  uint8_t long2array(long num, char* numb);
  
  //! It converts a number stored in a string into a hexadecimal number
  /*!
  \param char* str : string where the number is stored
  \return the converted number
  \sa long2array(long num, char* numb), str2hex(uint8_t* str)
   */
  uint8_t str2hex(char* str);  
  
  //! It converts an array of bytes expressed in ASCII to hexadecimal values
  /*!
  \param char* str : string where the array is defined in ASCII format
  \param uint8_t* array : array of bytes where the converted array is stored
  \return length of the converted array; '0' if error
   */
  uint16_t str2hex(char* str, uint8_t* array);
  uint16_t str2hex(char* str, uint8_t* array, uint16_t size);
  
  //! It converts a number stored in a string into a hexadecimal number
  /*!
  \param char* str : string where the number is stored
  \return the converted number
  \sa long2array(long num, char* numb), str2hex(char* str)
   */
  uint8_t str2hex(uint8_t* str);  
  
  //! It converts a hexadecimal number stored in an array to a string (8 Byte numbers)
  /*!
  \param uint8_t* number : hexadecimal array to conver to a string
  \param const char* macDest : char array where the converted number is stored
  \return void
  \sa long2array(long num, char* numb), str2hex(char* str), str2hex(uint8_t* str)
   */
  void hex2str(uint8_t* number, char* macDest);
  
   //! It converts a hexadecimal number stored in an array to a string (8 Byte numbers)
  /*!
  \param uint8_t* number : hexadecimal array to conver to a string
  \param const char* macDest : char array where the converted number is stored
  \param uint8_t length : length to copy
  \return void
  \sa long2array(long num, char* numb), str2hex(char* str), str2hex(uint8_t* str)
   */
  void hex2str(uint8_t* number, char* macDest, uint8_t length);
  
  //! It clears the arguments[][] data matrix
  /*!
  \param void
  \return void
   */
  void clearArguments(void);  

  
  //! It breaks a string into its arguments separated by "separators". The pieces are stored in 'arguments' array
  /*!
  \param const char* str : string to separate
  \param char separator : the separator used to separate the string in pieces
  \return void
  \sa clearArguments(),clearBuffer()
   */
  void strExplode(const char* str, char separator);
  
  //! It generates a decimal number from two ASCII characters which were numbers
  /*!
  \param uint8_t conv1 : the ASCII number first digit to convert
  \param uint8_t conv2 : the ASCII number second digit to convert
  \return the converted number
  */
  uint8_t converter(uint8_t conv1, uint8_t conv2);
  
  //! It converts a float into a string
  /*!
  \param float fl : the float to convert
  \param char str[] : the string where store the float converted
  \param int N : the number of decimals
  \return void
   */
  void float2String(float fl, char str[], int N);
  
  //! It writes into the EEPROM the name of the OTA file
  /*!
  \return void
  */
  void loadOTA(const char* filename, uint8_t version);
  
  //! It reads the EEPROM from position 2 to 34 and shows it by USB
  /*!
  \return void
  */
  void readEEPROM();
  
  //! It checks the new firmware upgrade
  /*!
  \return '0' if reprogramming error, '1' if reprogramming OK and '2' for normal restart
  */
  int8_t checkNewProgram();
  
  //! It reads program ID (PID) from EEPROM
  /*!
  \param char* program_ID : string pointer to store the PID
  \return void
  */
  void getProgramID(char* program_ID);
  
  //! It reads mote ID from EEPROM
  /*!
  \param char* moteID : string pointer to store the mote ID
  \return void
  */
  void getID(char* moteID);
  
  //! It stores the version of the program to EEPROM
  /*!
  \param uint8_t version : version of te program. Values from 0 to 255
  \return void
  */
  void setProgramVersion(uint8_t version);
  
  //! It reads the version of the program from EEPROM
  /*!
  \return the version of the actual program
  */
  uint8_t getProgramVersion();   
  
  //! It reads the version of the bootloader from EEPROM
  /*!
  \return the version of the actual bootloader
  */
  uint8_t getBootVersion();
  
  //! It displays the Waspmote's version
  void showVersion();
  
};

extern WaspUtils Utils;

#endif

