/*
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
	
	// switch multiplexer on
	pinMode(MUX_PW,OUTPUT);
	digitalWrite(MUX_PW,HIGH);
	
	// configure multiplexer to USB port. XBee disabled
	pinMode(MUX_USB_XBEE,OUTPUT);
	digitalWrite(MUX_USB_XBEE,LOW);
	
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
	// First: close UART
	closeSerial(_uart);
	
	// Second: configure multiplexer to XBEE port
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,HIGH);	
	
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
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	
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
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printByte(c,  _uart);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( c ) - prints a string
 * 
 */
void WaspUSB::print(const char c[])
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printString(c,  _uart);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( b ) - prints an unsigned 8-bit integer
 * 
 */
void WaspUSB::print(uint8_t b)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printByte(b,  _uart);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an integer
 * 
 */
void WaspUSB::print(int n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print((long) n);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an unsigned integer
 * 
 */
void WaspUSB::print(unsigned int n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print((unsigned long) n);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints a long integer
 * 
 */
void WaspUSB::print(long n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	if (n < 0) 
	{
		print('-');
		n = -n;
	}
	printNumber(n, 10);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an unsigned long integer
 * 
 */
void WaspUSB::print(unsigned long n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printNumber(n, 10);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n , base ) - prints a long number in the specified base
 * 
 */
void WaspUSB::print(long n, int base)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	if (base == 0)
		print((char) n);
	else if (base == 10)
		print(n);
	else
		printNumber(n, base);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * printHex( n  ) - prints a byte as a hexadecimal (%2X) format 
 * 
 */
void WaspUSB::printHex(char n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);

	puthex((char)n,0);

	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}


/*
 * print( n  ) - prints a double number
 * 
 */
void WaspUSB::print(double n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printFloat(n, 10);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an unsigned 64-bit number
 * 
 */
void WaspUSB::print(uint64_t n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printInteger(n,0);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( ) - prints an EOL and a carriage return
 * 
 */
void WaspUSB::println()
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print('\r');
	print('\n');  
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( c ) - prints a character adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(char c)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(c);
	println();  
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( c ) - prints a string adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(const char c[])
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(c);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( b ) - prints an unsigned 8-bit integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(uint8_t b)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(b);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(int n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(n);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints a long integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(long n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(n);
	println();
	delay(DELAY_TIME);  
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints an unsigned long integer adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(unsigned long n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(n);
	println();  
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n , base ) - prints a long number in the specified base adding an EOL 
 * and a  carriage return
 * 
 */
void WaspUSB::println(long n, int base)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(n, base);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints a double number adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(double n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(n);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * print( n ) - prints a 64-bit number adding an EOL and a carriage return
 * 
 */
void WaspUSB::println(uint64_t n)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printInteger(n,0);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/// Private Methods ////////////////////////////////////////////////////////////

/*
 * print( n , base ) - prints a number in the specified base
 * 
 */
void WaspUSB::printNumber(unsigned long n, uint8_t base)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printIntegerInBase(n, base,  _uart);
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * printFloat( number , digits ) - prints a 'float' number
 * Parameters: 
 * 		number : the number to print
 * 		digits : the number of non-integer part digits
 * 
 */
void WaspUSB::printFloat(double number, uint8_t digits) 
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	// Handle negative numbers
	if (number < 0.0)
	{
		print('-');
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
	print(int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
		print("."); 

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		int toPrint = int(remainder);
		print(toPrint);
		remainder -= toPrint; 
	}
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}

/*
 * printFloat( ifsh ) - prints a string from Flash memory
 * Parameters: 
 * 		ifsh : FlashStringHelper defined in Flash memory  		
 * 
 */
uint32_t WaspUSB::print(const __FlashStringHelper *ifsh)
{
	beginSerial(USB_RATE, _uart);
	const char * __attribute__((progmem)) p = (const char * ) ifsh;
	uint32_t retries = 1000;
	while( retries > 0 ) 
	{
		retries--;
		unsigned char c = pgm_read_byte(p++);
		if (c == 0) break;		
		print(c);
	}
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
	beginSerial(USB_RATE, _uart);
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
	beginSerial(USB_RATE, _uart);
	// resulting string limited to 128 chars
    char tmp[128]; 
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    USB.print(tmp);
}




/*
 * print - It prints a buffer specifying the length of the buffer
 * 
 */
void WaspUSB::print(uint8_t* pointer, uint16_t length)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	for( uint16_t i = 0; i < length; i++ )
	{
		printByte( pointer[i], _uart);
	}	
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}


/*
 * print - It prints a buffer in HEX format specifying the length of the buffer
 * 
 */
void WaspUSB::printHex(uint8_t* pointer, uint16_t length)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	for( uint16_t i = 0; i < length; i++ )
	{		
		puthex((char)pointer[i], _uart);
	}	
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}



/*
 * print - It prints a buffer specifying the length of the buffer
 * This functions adds an End Of Line after printing the buffer
 * 
 */
void WaspUSB::println(uint8_t* pointer, uint16_t length)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	print(pointer, length);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}



/*
 * print - It prints a buffer in HEX format specifying the length of the buffer
 * This function adds an End Of Line after printing the buffer
 * 
 */
void WaspUSB::printHexln(uint8_t* pointer, uint16_t length)
{
	beginSerial(USB_RATE, _uart);
	digitalWrite(MUX_PW,HIGH);
	digitalWrite(MUX_USB_XBEE,LOW);
	printHex(pointer, length);
	println();
	delay(DELAY_TIME);
	digitalWrite(MUX_USB_XBEE,HIGH);
}



/// Preinstantiate Objects /////////////////////////////////////////////////////

WaspUSB USB = WaspUSB();

