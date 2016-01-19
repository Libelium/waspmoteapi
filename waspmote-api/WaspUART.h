/*! \file WaspUART.h
    \brief Library for managing UART bus
    
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
  
    Version:		1.1
    Design:			David Gascón
    Implementation:	Yuri Carmona

*/
 
  
#ifndef WaspUART_h
#define WaspUART_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
 

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

#define UART_DEBUG 0


/*! \def UART0
    \brief UART0 of the MCU
 */
/*! \def UART1
    \brief UART1 of the MCU
 */
#define UART0	0
#define UART1	1
 
 
/*! \def DEF_COMMAND_TIMEOUT
    \brief default timeout for command operations
 */
#define DEF_COMMAND_TIMEOUT	 5000

/*! \def DEF_COMMAND_DELAY
    \brief default time to wait after sending command
 */
#define DEF_COMMAND_DELAY	 100
 
/*! \def DEF_BAUD_RATE
    \brief default baudrate
 */
#define DEF_BAUD_RATE	 115200

/******************************************************************************
 * Class
 ******************************************************************************/
 

class WaspUART
{

protected:

	uint8_t 	_uart;
	uint32_t 	_baudrate;
	uint32_t 	_def_timeout;
	uint32_t 	_def_delay;
	bool 		_flush_mode;

public:

	WaspUART()
	{		
		_baudrate 	= DEF_BAUD_RATE;
		_def_timeout= DEF_COMMAND_TIMEOUT;
		_def_delay 	= DEF_COMMAND_DELAY;
		_flush_mode = true;
	};
	
	//! buffer for rx data
	uint8_t	_buffer[512];
	
	//! length of the contents in '_buffer'
	uint16_t _length;
	
	//! It open the corresponding uart
	void beginUART();
	
	//! It closes the corresponding uart
	void closeUART();
	
	//! It sets the time to wait for command responses
	void setTimeout(uint32_t newTimeout);
	
	//! It gets the time to wait for command responses
	uint32_t getTimeout();
	
	//! It sets the time to wait after sending the command
	void setDelay( uint32_t newDelay );
	
	//! It gets the time to wait after sending the command
	uint32_t getDelay();
	
	//! It sends a command through the selected uart expecting a specific answer
    /*!
	\param char* command : string to send to the module
	\param char* ans1 : string expected to be answered by the module
	\return '0' if timeout error, 
			'1' if ans1
	*/
	uint8_t sendCommand(char* command, 
						char* ans1);
						
	uint8_t sendCommand(char* command, 
						char* ans1, 
						uint32_t timeout);
	
	//! It sends a command through the selected uart expecting specific answers
    /*!
	\param char* command : string to send to the module
	\param char* ans1 : string expected to be answered by the module
	\param char* ans2 : string expected to be answered by the module
	\param uint32_t timeout : time to wait for responses before exit with error
	\return '0' if timeout error, 
			'1' if ans1
			'2' if ans2
	 */	
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2);
						
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2, 
						uint32_t timeout);
	
	//! It sends a command through the selected uart expecting specific answers
    /*!
	\param char* command : string to send to the module
	\param char* ans1 : string expected to be answered by the module
	\param char* ans2 : string expected to be answered by the module
	\param char* ans3 : string expected to be answered by the module
	\param uint32_t timeout : time to wait for responses before exit with error
	\return '0' if timeout error, 
			'1' if ans1
			'2' if ans2
			'3' if ans3
	 */	
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2, 
						char* ans3 );
						
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2,
						char* ans3,  
						uint32_t timeout);
	
	//! It sends a command through the selected uart expecting specific answers
    /*!
	\param char* command : string to send to the module
	\param char* ans1 : string expected to be answered by the module
	\param char* ans2 : string expected to be answered by the module
	\param char* ans3 : string expected to be answered by the module
	\param char* ans4 : string expected to be answered by the module
	\param uint32_t timeout : time to wait for responses before exit with error
	\return '0' if timeout error, 
			'1' if ans1
			'2' if ans2
			'3' if ans3
			'4' if ans4
	 */	
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2, 
						char* ans3, 
						char* ans4);
						
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2, 
						char* ans3, 
						char* ans4, 
						uint32_t timeout);
						
	//! It seeks 'pattern' inside the 'buffer' array
	bool find(uint8_t* buffer, uint16_t length, char* pattern);	
	
	//! It sends a command without waiting answer (only send)
	void sendCommand(uint8_t* command, uint16_t length);

	/*!
	\brief	This function waits for one of the answers during a certain period 
			of time. The result is stored in '_buffer'.
	\param	char* command: command to be sent
	\param	char* ans1: expected answer
	\param	char* ans2: expected answer
	\param	char* ans3: expected answer
	\param	char* ans4: expected answer
	\param  uint32_t timeout : time to wait for responses before exit with error
	\return '0' if timeout error, 
			'1' if ans1
			'2' if ans2
			'3' if ans3
			'4' if ans4
	*/
	uint8_t waitFor( char* ans1);
	uint8_t waitFor( char* ans1, uint32_t timeout);
	uint8_t waitFor( char* ans1, char* ans2);			
	uint8_t waitFor( char* ans1, char* ans2, uint32_t timeout);
	uint8_t waitFor( char* ans1, char* ans2, char* ans3 );	
	uint8_t waitFor( char* ans1, char* ans2, char* ans3, uint32_t timeout);
	uint8_t waitFor( char* ans1, char* ans2, char* ans3, char* ans4);
	uint8_t waitFor( char* ans1, char* ans2, char* ans3, char* ans4, uint32_t timeout);
	
	//! Read the contents of the rx buffer
	uint16_t readBuffer(uint16_t requestBytes);
	uint16_t readBuffer(uint16_t requestBytes, bool clearBuffer);
	
	//! It waits depending on the baudrate used
	void latencyDelay();

protected:
	
	//! It parses the contents of _buffer and copies the string to the pointer
	uint8_t parseString(char* str, uint16_t size, char* delimiters);
	
	//! It parses the contents of _buffer and converts it to a float type
	uint8_t parseFloat(float* value, char* delimiters);
	
	//! It parses the contents of _buffer and converts it to a uint32_t type
	uint8_t parseUint32(uint32_t* value, char* delimiters);

	//! It parses the contents of _buffer and converts it to a int type
	uint8_t parseInt(int* value, char* delimiters);
	
	//! It parses the contents of _buffer and converts it to a uint16_t type
	uint8_t parseUint8(uint8_t* value, char* delimiters);
	
	//! It parses the contents of _buffer and converts it to a uint16_t type
	uint8_t parseHex(uint8_t* value, char* delimiters);
};


#endif
