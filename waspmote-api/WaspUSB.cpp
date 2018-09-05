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
 *  Design:			David Gascon
 *  Implementation:	David Cuartielles, Alberto Bielsa, Marcos Yarza
 */
 

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

/*! \def DELAY_TIME
    \brief Delay time before switching the multiplexor back to its original 
    position in "print" kind functions. This avoids printing weird characters 
    through the serial port
 */
#define DELAY_TIME 3

/// Constructors ///////////////////////////////////////////////////////////////

WaspUSB::WaspUSB()
{
    _uart = 0;
}

/// Public Methods /////////////////////////////////////////////////////////////

/*
 * ON() - opens UART0 to be able to communicate with the FTDI conversor.
 * It also switches the multiplexor to USB   
 */
void WaspUSB::ON()
{
	// open UART0
	beginSerial(USB_RATE, _uart);
	
	// configure multiplexer to USB port. XBee disabled
	Utils.setMuxUSB();
	
	// unset XBee interruption line
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);	
	
}

/*
 * OFF() - closes the previously opened UART0
 *    
 */
void WaspUSB::OFF()
{
	if (!(WaspRegister & REG_SOCKET0))
	{	
		// close UART
		closeSerial(_uart);
		
		// switch off mux on uart0
		if (_boot_version >= 'G')
		{		
			Utils.muxOFF0();
		}
	}
	else
	{
		// configure mux to Socket0
		Utils.setMuxSocket0();
	}
	
	// unset XBee interruption line
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);	
}

/*
 * available() - checks if there is available data waiting to be read
 *  
 */
uint8_t WaspUSB::available()
{
	beginSerial(USB_RATE, _uart);

	// configure multiplexor to USB port
	Utils.setMuxUSB();
	
	return serialAvailable( _uart);
}

/*
 * read() - reads a byte from the UART
 * 
 */
int WaspUSB::read()
{
	beginSerial(USB_RATE, _uart);
	return serialRead( _uart);
}

/*
 * flush() - clears the UART buffer
 * 
 */
void WaspUSB::flush()
{
	beginSerial(USB_RATE, _uart);
	serialFlush( _uart);
}

/*
 * print( c ) - prints a character
 * 
 */
void WaspUSB::print(char c)
{
	secureBegin();
	printByte(c,  _uart);
	secureEnd();
}

/*
 * print( c ) - prints a string
 * 
 */
void WaspUSB::print(const char c[])
{
	secureBegin();
	printString(c,  _uart);	
	secureEnd();
}

/*
 * print( b ) - prints an unsigned 8-bit integer
 * 
 */
void WaspUSB::print(uint8_t b)
{
	secureBegin();
	printByte(b,  _uart);
	secureEnd();
}


/*
 * print() - prints an unsigned 16-bit integer
 * 
 */
void WaspUSB::print(uint16_t n)
{
	print((uint32_t) n);
}

/*
 * print( n ) - prints an integer
 * 
 */
void WaspUSB::print(int n)
{
	print((long) n);
}


/*
 * print( n ) - prints a long integer
 * 
 */
void WaspUSB::print(long n)
{
	secureBegin();
	if (n < 0) 
	{
		printByte('-',_uart);
		n = -n;
	}	
	printIntegerInBase((uint32_t)n, 10,  _uart);
	secureEnd();
}

/*
 * print( n ) - prints an unsigned long integer
 * 
 */
void WaspUSB::print(unsigned long n)
{
	secureBegin();
	printIntegerInBase(n, 10, _uart);
	secureEnd();
}

/*
 * print( n , base ) - prints a long number in the specified base
 * 
 */
void WaspUSB::print(long n, int base)
{
	secureBegin();
	if (base == 0)
	{		
		printByte((char) n, _uart);
	}
	else if (base == 10)
	{
		printInteger(n, _uart);
	}
	else
	{
		printIntegerInBase(n, base,  _uart);
	}
	secureEnd();
}

/*
 * printHex( n  ) - prints a byte as a hexadecimal (%2X) format 
 * 
 */
void WaspUSB::printHex(char n)
{
	secureBegin();	
	puthex((char)n,0);
	secureEnd();
}


/*
 * print( n  ) - prints a double number
 * 
 */
void WaspUSB::print(double n)
{	
	printFloat(n, 10);	
}

/*
 * print( n ) - prints an unsigned 64-bit number
 * 
 */
void WaspUSB::print(uint64_t n)
{
	secureBegin();
	printInteger(n,0);
	secureEnd();
}

/*
 * print( ) - prints an EOL and a carriage return
 * 
 */
void WaspUSB::println()
{
	secureBegin();
	printNewline(_uart);
	secureEnd();	
}

/*
 * print( c ) - prints a character adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(char c)
{
	secureBegin();
	printByte(c, _uart);
	printNewline(_uart);
	secureEnd();
}

/*
 * print( c ) - prints a string adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(const char c[])
{
	secureBegin();	
	printString(c,  _uart);	
	printNewline(_uart);
	secureEnd();
}

/*
 * print( b ) - prints an unsigned 8-bit integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(uint8_t b)
{
	secureBegin();	
	printByte(b,  _uart);
	printNewline(_uart);
	secureEnd();
}


/*
 * print() - prints an unsigned 16-bit integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(uint16_t n)
{
	secureBegin();	
	printIntegerInBase((uint32_t) n, 10, _uart);
	printNewline(_uart);
	secureEnd();
}



/*
 * print( n ) - prints an integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(int n)
{
	secureBegin();
	if (n < 0) 
	{
		printByte('-',_uart);
		n = -n;
	}	
	printIntegerInBase((uint32_t) n, 10,  _uart);
	printNewline(_uart);
	secureEnd();
}

/*
 * print( n ) - prints a long integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(long n)
{
	secureBegin();
	if (n < 0) 
	{
		printByte('-',_uart);
		n = -n;
	}	
	printIntegerInBase((uint32_t)n, 10,  _uart);
	printNewline(_uart);
	secureEnd();
}

/*
 * print( n ) - prints an unsigned long integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(unsigned long n)
{
	secureBegin();
	printIntegerInBase((uint32_t)n, 10,  _uart);
	printNewline(_uart);
	secureEnd();
}

/*
 * print( n , base ) - prints a long number in the specified base adding an EOL 
 * and a  carriage return
 * 
 */
void WaspUSB::println(long n, int base)
{
	secureBegin();
	if (base == 0)
	{		
		printByte((char) n, _uart);
	}
	else if (base == 10)
	{
		printInteger(n, _uart);
	}
	else
	{
		printIntegerInBase(n, base,  _uart);
	}
	printNewline(_uart);
	secureEnd();
}

/*
 * print( n ) - prints a double number adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(double n)
{	
	printFloat(n, 10);
	println();
}

/*
 * print( n ) - prints a 64-bit number adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(uint64_t n)
{
	secureBegin();
	printInteger(n,0);
	printNewline(_uart);
	secureEnd();
}

/// Private Methods ////////////////////////////////////////////////////////////


/*
 * printFloat( number , digits ) - prints a 'float' number
 * Parameters: 
 * 		number : the number to print
 * 		digits : the number of non-integer part digits
 * 
 */
void WaspUSB::printFloat(double number, uint8_t digits) 
{
	secureBegin();
	
	// Handle negative numbers
	if (number < 0.0)
	{
		printByte('-', _uart);
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
		rounding /= 10.0;
  
	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;	
	printIntegerInBase(int_part, 10, _uart);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
		printByte('.',_uart); 

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		int toPrint = int(remainder);
		printIntegerInBase( (long) toPrint, 10,  _uart);
		remainder -= toPrint; 
	}
	secureEnd();
}

/*
 * printFloat( ifsh ) - prints a string from Flash memory
 * Parameters: 
 * 		ifsh : FlashStringHelper defined in Flash memory  		
 * 
 */
uint32_t WaspUSB::print(const __FlashStringHelper *ifsh)
{
	unsigned char c;
	
	secureBegin();
	const char * __attribute__((progmem)) p = (const char * ) ifsh;
	uint32_t retries = 1000;
	while( retries > 0 ) 
	{
		retries--;
		c = pgm_read_byte(p++);
		if (c == 0) break;		
		printByte(c,  _uart);
	}
	secureEnd();
	return 0;
}

/*
 * printFloat( ifsh ) - prints a string from Flash memory adding an EOL
 * Parameters: 
 * 		ifsh : FlashStringHelper defined in Flash memory  		
 * 
 */
uint32_t WaspUSB::println(const __FlashStringHelper *ifsh)
{
	uint32_t n = print(ifsh);
	println();
	return n;
}


/*
 * printf(char *fmt, ... ) - prints a sequence of data formatted as the format 
 * argument specifies 
 * 
 * This function emulates the stdio.h printf() functionality in C and will send
 * the output to the Serial connection using printByte(). The resulting 
 * string sent over serial is limited to 128 chars.
 * 
 * Parameters: 
 * 		fmt : FlashStringHelper defined in Flash memory  
 * 
 * Examples:
 * 	USB.printf("%s\n", "Hello world");
 *  USB.printf("x:%d,y:%d,z:%d -bat: %d%c%c%c",
 * 												ACC.getX(),
 * 												ACC.getY(),
 * 												ACC.getZ(),  														
 * 												PWR.getBatteryLevel(),
 * 												'%',
 * 												'\r',
 * 												'\n'	);	
 * 
 */
void  WaspUSB::printf(char *fmt, ... )
{	
	secureBegin();	
	// resulting string limited to 128 chars
    char tmp[128]; 
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    printString(tmp, _uart);
    secureEnd();
}




/*
 * print - It prints a buffer specifying the length of the buffer
 * 
 */
void WaspUSB::print(uint8_t* pointer, uint16_t length)
{
	secureBegin();
	for( uint16_t i = 0; i < length; i++ )
	{
		printByte( pointer[i], _uart);
	}	
	secureEnd();
}


/*
 * print - It prints a buffer in HEX format specifying the length of the buffer
 * 
 */
void WaspUSB::printHex(uint8_t* pointer, uint16_t length)
{
	secureBegin();
	for( uint16_t i = 0; i < length; i++ )
	{		
		puthex((char)pointer[i], _uart);
	}	
	secureEnd();
}



/*
 * print - It prints a buffer specifying the length of the buffer
 * This functions adds an End Of Line after printing the buffer
 * 
 */
void WaspUSB::println(uint8_t* pointer, uint16_t length)
{
	secureBegin();
	for( uint16_t i = 0; i < length; i++ )
	{		
		printByte((char)pointer[i], _uart);
	}
	printNewline(_uart);
	secureEnd();
}



/*
 * print - It prints a buffer in HEX format specifying the length of the buffer
 * This function adds an End Of Line after printing the buffer
 * 
 */
void WaspUSB::printHexln(uint8_t* pointer, uint16_t length)
{
	secureBegin();
	for( uint16_t i = 0; i < length; i++ )
	{		
		puthex((char)pointer[i], _uart);
	}		
	printNewline(_uart);
	secureEnd();
}



/* 
 * name: secureBegin 
 * Inits UART0 securely taking account on what baudrate was previously set in 
 * UART0 before using the USB port. This helps to avoid errors with different
 * baudrate usage
 * 		
 */
void WaspUSB::secureBegin()
{
	// store previous baudrate
	_reg_ubrr0h = UBRR0H;	// USART0 Baud Rate Register High Byte
	_reg_ubrr0l = UBRR0L;	// USART0 Baud Rate Register Low Byte
	_reg_ucsr0c = UCSR0C; 	// USART0 Control and Status Register n C
	
	// No parity bit
	cbi(UCSR0C, UPM01);
	cbi(UCSR0C, UPM00);
	
	// 1 stop bit
	cbi(UCSR0C, USBS0);
	
	// begin uart according the correct baudrate
	beginSerial(USB_RATE, _uart);
	
	// switch on mux
	Utils.setMuxUSB();
}


/* 
 * name: secureEnd 
 * Inits UART0 securely taking account on what baudrate was previously set in 
 * UART0 before using the USB port. This helps to avoid errors with different
 * baudrate usage
 * 		
 */
void WaspUSB::secureEnd()
{	
	// switch back the mux to SOCKET0 if needed
	if (WaspRegister & REG_SOCKET0)
	{
		delay(3);
		Utils.setMuxSocket0();
	}
	else
	{
		delay(3);
		if (_boot_version >= 'G')
		{
			Utils.muxOFF0();
		}
	}
	
	// load previous stored registers
	UBRR0H = _reg_ubrr0h;
	UBRR0L = _reg_ubrr0l;
	UCSR0C = _reg_ucsr0c;
}



/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspUSB USB = WaspUSB();

