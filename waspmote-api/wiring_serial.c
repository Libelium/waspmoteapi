/*
 *  Copyright (c) 2005-2006 David A. Mellis
 *  Modified for Waspmote by Libelium, 2018
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
 * 	Version:	3.1
 */
 

#include "wiring_private.h"

#ifndef __WASPCONSTANTS_H__
	#include "WaspConstants.h"
#endif


// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which rx_buffer_head is the index of the
// location to which to write the next incoming character and rx_buffer_tail
// is the index of the location from which to read.
#define RX_BUFFER_SIZE_0 512
#define RX_BUFFER_SIZE_1 512

	unsigned char rx_buffer0[RX_BUFFER_SIZE_0];
	unsigned char rx_buffer1[RX_BUFFER_SIZE_1];
	int rx_buffer_head0 = 0;
	int rx_buffer_tail0 = 0;
	int rx_buffer_head1 = 0;
	int rx_buffer_tail1 = 0;

// connects the internal peripheral in the processor and configures it
void beginSerial(long baud, uint8_t portNum)
{
	if (portNum == 0) {
		setIPF_(IPUSART0);
		UBRR0H = ((F_CPU / 16 + baud / 2) / baud - 1) >> 8;
		UBRR0L = ((F_CPU / 16 + baud / 2) / baud - 1);
		
		// enable rx and tx
		sbi(UCSR0B, RXEN0);
		sbi(UCSR0B, TXEN0);
		
		// enable interrupt on complete reception of a byte
		sbi(UCSR0B, RXCIE0);
		
		
	} else {
		setIPF_(IPUSART1);
		UBRR1H = ((F_CPU / 16 + baud / 2) / baud - 1) >> 8;
		UBRR1L = ((F_CPU / 16 + baud / 2) / baud - 1);
	
		// enable rx and tx
		sbi(UCSR1B, RXEN1);
		sbi(UCSR1B, TXEN1);
		
		// enable interrupt on complete reception of a byte
		sbi(UCSR1B, RXCIE1);
	}
	// defaults to 8-bit, no parity, 1 stop bit
}

// disconnects the internal peripheral in the processor
void closeSerial(uint8_t portNum)
{
	if (portNum == 0) {
		// turn off the internal peripheral, but also the interface
		// resetIPF is just turning off the clock, what is not helping
		// to save power, you gotta get rid of all the pull-ups in the sytem
		resetIPF_(IPUSART0);
 		cbi(UCSR0B, RXEN0);
                cbi(UCSR0B, TXEN0);
	} else {
		// turn off the internal peripheral, but also the interface
		// resetIPF is just turning off the clock, what is not helping
		// to save power, you gotta get rid of all the pull-ups in the sytem
		resetIPF_(IPUSART1);
 		cbi(UCSR1B, RXEN1);
                cbi(UCSR1B, TXEN1);
	}
}

void serialWrite(unsigned char c, uint8_t portNum)
{
	if (portNum == 0) {
		while (!(UCSR0A & (1 << UDRE0)))
			;

		UDR0 = c;
	} else {
		while (!(UCSR1A & (1 << UDRE1)))
			;

		UDR1 = c;
	}
}

int serialAvailable(uint8_t portNum)
{
	if (portNum == 0)
		return (RX_BUFFER_SIZE_0 + rx_buffer_head0 - rx_buffer_tail0) % RX_BUFFER_SIZE_0;
	else
		return (RX_BUFFER_SIZE_1 + rx_buffer_head1 - rx_buffer_tail1) % RX_BUFFER_SIZE_1;
}

int serialRead(uint8_t portNum)
{
	if (portNum == 0) {
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head0 == rx_buffer_tail0) {
			return -1;
		} else {
			unsigned char c = rx_buffer0[rx_buffer_tail0];
			rx_buffer_tail0 = (rx_buffer_tail0 + 1) % RX_BUFFER_SIZE_0;
			return c;
		}
	}
	else {
		// if the head isn't ahead of the tail, we don't have any characters
		if (rx_buffer_head1 == rx_buffer_tail1) {
			return -1;
		} else {
			unsigned char c = rx_buffer1[rx_buffer_tail1];
			rx_buffer_tail1 = (rx_buffer_tail1 + 1) % RX_BUFFER_SIZE_1;
			return c;
		}
	}
}

void serialFlush(uint8_t portNum)
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.
	if (portNum == 0){
		rx_buffer_tail0=0;
		rx_buffer_head0 = rx_buffer_tail0;
	}
	else{
		rx_buffer_tail1=0;
		rx_buffer_head1 = rx_buffer_tail1;
	}
}

ISR(USART0_RX_vect)
{
		unsigned char c = UDR0;
		
		int i = (rx_buffer_head0 + 1) % RX_BUFFER_SIZE_0;
		
		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail0) {
			rx_buffer0[rx_buffer_head0] = c;
			rx_buffer_head0 = i;
		}
}

ISR(USART1_RX_vect)
{
		unsigned char c = UDR1;

		int i = (rx_buffer_head1 + 1) % RX_BUFFER_SIZE_1;

		// if we should be storing the received character into the location
		// just before the tail (meaning that the head would advance to the
		// current location of the tail), we're about to overflow the buffer
		// and so we don't write the character or advance the head.
		if (i != rx_buffer_tail1) {
			rx_buffer1[rx_buffer_head1] = c;
			rx_buffer_head1 = i;
		}
}

void printMode(int mode, uint8_t portNum)
{
	// do nothing, we only support serial printing, not lcd.
}

void printByte(unsigned char c, uint8_t portNum)
{
	serialWrite(c, portNum);
}

void printNewline(uint8_t portNum)
{
	printByte('\r', portNum);
	printByte('\n', portNum);
}

void printString(const char *s, uint8_t portNum)
{
	while (*s)
		printByte(*s++, portNum);
}

void printIntegerInBase(unsigned long n, unsigned long base, uint8_t portNum)
{ 
	unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
	unsigned long i = 0;

	if (n == 0) {
		printByte('0', portNum);
		return;
	} 

	while (n > 0) {
		buf[i++] = n % base;
		n /= base;
	}

	for (; i > 0; i--)
		printByte(buf[i - 1] < 10 ?
			'0' + buf[i - 1] :
			'A' + buf[i - 1] - 10, portNum);
}


void puthex(char ch, uint8_t portNum) {
    char ah,al;

    ah = (ch & 0xf0) >> 4;
    if(ah >= 0x0a) {
	ah = ah - 0x0a + 'A';
    } else {
	ah += '0';
    }
    al = (ch & 0x0f);
    if(al >= 0x0a) {
	al = al - 0x0a + 'A';
    } else {
	al += '0';
    }
    printByte(ah, portNum);
    printByte(al, portNum);
}



void printInteger(long n, uint8_t portNum)
{
	if (n < 0) {
		printByte('-', portNum);
		n = -n;
	}

	printIntegerInBase(n, 10, portNum);
}

void printHex(unsigned long n, uint8_t portNum)
{
	printIntegerInBase(n, 16, portNum);
}

void printOctal(unsigned long n, uint8_t portNum)
{
	printIntegerInBase(n, 8, portNum);
}

void printBinary(unsigned long n, uint8_t portNum)
{
	printIntegerInBase(n, 2, portNum);
}

/* Including print() adds approximately 1500 bytes to the binary size,
 * so we replace it with the smaller and less-confusing printString(),
 * printInteger(), etc.
void print(const char *format, ...)
{
	char buf[256];
	va_list ap;
	
	va_start(ap, format);
	vsnprintf(buf, 256, format, ap);
	va_end(ap);
	
	printString(buf);
}
*/
