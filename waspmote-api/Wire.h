/*
 *  Modified for Waspmote by A. Bielsa, 2009
 *
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
 */
 

#ifndef TwoWire_h
#define TwoWire_h

#include <inttypes.h>

#define BUFFER_LENGTH 32

class TwoWire
{
  private:
    static uint8_t rxBuffer[BUFFER_LENGTH];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[BUFFER_LENGTH];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);
  public:
    TwoWire();
    
    uint8_t I2C_ON;
    
    void begin();
    void begin(uint8_t);
    void begin(int);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    void endTransmission(void);
    void requestFrom(uint8_t, uint8_t);
    void requestFrom(int, int);
    void send(uint8_t);
    void send(uint8_t*, uint8_t);
    void send(int);
    void send(char*);
    uint8_t available(void);
    uint8_t receive(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );
    void close();
};

extern TwoWire Wire;

#endif

