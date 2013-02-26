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
 

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

class HardwareSerial
{
  private:
    uint8_t _uart;
    void printNumber(unsigned long, uint8_t, uint8_t);
    void printFloat(double, uint8_t, uint8_t);
  public:
    HardwareSerial(uint8_t);
    void begin(long, uint8_t);
    uint8_t available(uint8_t);
    int read(uint8_t);
    void flush(uint8_t);
    void print(char, uint8_t);
    void print(const char[], uint8_t);
    void print(uint8_t, uint8_t);
    void print(int, uint8_t);
    void print(unsigned int, uint8_t);
    void print(long, uint8_t);
    void print(unsigned long, uint8_t);
    void print(long, int, uint8_t);
    void print(double, uint8_t);
    void println(uint8_t);
    void println(char, uint8_t);
    void println(const char[], uint8_t);
    void println(uint8_t, uint8_t);
    void println(int, uint8_t);
    void println(long, uint8_t);
    void println(unsigned long, uint8_t);
    void println(long, int, uint8_t);
    void println(double, uint8_t);
};

extern HardwareSerial Serial;
extern HardwareSerial Serial1;

#endif

