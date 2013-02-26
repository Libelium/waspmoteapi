/*
 *  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
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
 */
  
  
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "wiring.h"

#include "HardwareSerial.h"

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial(uint8_t uart)
{
  if(uart == 0){
    _uart = 0;
  }else{
    _uart = 1;
  }
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(long speed, uint8_t portNum)
{
  beginSerial(speed, portNum);
}

uint8_t HardwareSerial::available(uint8_t portNum)
{
  return serialAvailable(portNum);
}

int HardwareSerial::read(uint8_t portNum)
{
  return serialRead(portNum);
}

void HardwareSerial::flush(uint8_t portNum)
{
  serialFlush(portNum);
}

void HardwareSerial::print(char c, uint8_t portNum)
{
  printByte(c, portNum);
}

void HardwareSerial::print(const char c[], uint8_t portNum)
{
  printString(c, portNum);
}

void HardwareSerial::print(uint8_t b, uint8_t portNum)
{
  printByte(b, portNum);
}

void HardwareSerial::print(int n, uint8_t portNum)
{
  print((long) n, portNum);
}

void HardwareSerial::print(unsigned int n, uint8_t portNum)
{
  print((unsigned long) n, portNum);
}

void HardwareSerial::print(long n, uint8_t portNum)
{
  if (n < 0) {
    print('-', portNum);
    n = -n;
  }
  printNumber(n, 10, portNum);
}

void HardwareSerial::print(unsigned long n, uint8_t portNum)
{
  printNumber(n, 10, portNum);
}

void HardwareSerial::print(long n, int base, uint8_t portNum)
{
  if (base == 0)
    print((char) n, portNum);
  else if (base == 10)
    print(n, portNum);
  else
    printNumber(n, base, portNum);
}

void HardwareSerial::print(double n, uint8_t portNum)
{
  printFloat(n, 2, portNum);
}

void HardwareSerial::println(uint8_t portNum)
{
  print('\r', portNum);
  print('\n', portNum);  
}

void HardwareSerial::println(char c, uint8_t portNum)
{
  print(c, portNum);
  println(portNum);  
}

void HardwareSerial::println(const char c[], uint8_t portNum)
{
  print(c, portNum);
  println(portNum);
}

void HardwareSerial::println(uint8_t b, uint8_t portNum)
{
  print(b, portNum);
  println(portNum);
}

void HardwareSerial::println(int n, uint8_t portNum)
{
  print(n, portNum);
  println(portNum);
}

void HardwareSerial::println(long n, uint8_t portNum)
{
  print(n, portNum);
  println(portNum);  
}

void HardwareSerial::println(unsigned long n, uint8_t portNum)
{
  print(n, portNum);
  println(portNum);  
}

void HardwareSerial::println(long n, int base, uint8_t portNum)
{
  print(n, base, portNum);
  println(portNum);
}

void HardwareSerial::println(double n, uint8_t portNum)
{
  print(n, portNum);
  println(portNum);
}

// Private Methods /////////////////////////////////////////////////////////////

void HardwareSerial::printNumber(unsigned long n, uint8_t base, uint8_t portNum)
{
  printIntegerInBase(n, base, portNum);
}

void HardwareSerial::printFloat(double number, uint8_t digits, uint8_t portNum) 
{ 
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-', portNum);
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
  print(int_part,portNum);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".",portNum); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint,portNum);
    remainder -= toPrint; 
  } 
}

// Preinstantiate Objects //////////////////////////////////////////////////////

HardwareSerial Serial = HardwareSerial(0);
HardwareSerial Serial1 = HardwareSerial(1);

