/*
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		0.12
 *  Design:		
 *  Implementation:	
 */
  

#ifndef __max3421e_h_
	#include "max3421e.h"
#endif

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

uint8_t MAX3421e::getVbusState( void )
{ 
    return( vbusState );
}

/*
 * Constructor
 */
MAX3421e::MAX3421e ()
{
}

/* write single byte into MAX3421 register */
void MAX3421e::regWr( uint8_t reg, uint8_t data )
{
 digitalWrite(SOCKET0_SS,LOW);
  SPDR = ( reg | 0x02 );
  while(!( SPSR & ( 1 << SPIF )));
  SPDR = data;
  while(!( SPSR & ( 1 << SPIF )));
  digitalWrite(SOCKET0_SS,HIGH);
  return;
};

/* Same as regWr but also set the AckStat bit in the command byte */
void MAX3421e::regWrAS( uint8_t reg, uint8_t data )
{
 digitalWrite(SOCKET0_SS,LOW);
  SPDR = ( reg | 0x03 );
  while(!( SPSR & ( 1 << SPIF )));
  SPDR = data;
  while(!( SPSR & ( 1 << SPIF )));
  digitalWrite(SOCKET0_SS,HIGH);
  return;
};

/* multiple-byte write                            */
/* returns a pointer to memory position after last written */
uint8_t* MAX3421e::bytesWr( uint8_t reg, uint8_t nbytes, uint8_t* data_p )
{
  digitalWrite(SOCKET0_SS,LOW);
  SPDR = ( reg | 0x02 );  //set WR bit and send register number
  while( nbytes-- ) {
    while(!( SPSR & ( 1 << SPIF )));  //check if previous byte was sent
    SPDR = ( *data_p );               // send next data byte
    data_p++;                         // advance data pointer
  }
  while(!( SPSR & ( 1 << SPIF )));
  digitalWrite(SOCKET0_SS,HIGH);
  return( data_p );
}

/* single host register read    */
uint8_t MAX3421e::regRd( uint8_t reg )
{
  digitalWrite(SOCKET0_SS,LOW);
  SPDR = reg;
  while(!( SPSR & ( 1 << SPIF )));
  SPDR = 0; //send empty byte
  while(!( SPSR & ( 1 << SPIF )));
  digitalWrite(SOCKET0_SS,HIGH);
  return( SPDR );
}

/* Same as regRd but also set the AckStat bit in the command byte    */
uint8_t MAX3421e::regRdAS( uint8_t reg )
{
  digitalWrite(SOCKET0_SS,LOW);
  SPDR = (reg|0x01);
  while(!( SPSR & ( 1 << SPIF )));
  SPDR = 0; //send empty byte
  while(!( SPSR & ( 1 << SPIF )));
  digitalWrite(SOCKET0_SS,HIGH);
  return( SPDR );
}

/* multiple-byte register read  */
/* returns a pointer to a memory position after last read   */
uint8_t* MAX3421e::bytesRd( uint8_t reg, uint8_t nbytes, uint8_t* data_p )
{
  digitalWrite(SOCKET0_SS,LOW);
  SPDR = reg;      
  while(!( SPSR & ( 1 << SPIF )));    //wait
  while( nbytes ) {
    SPDR = 0; //send empty byte
    nbytes--;
    while(!( SPSR & ( 1 << SPIF )));
    *data_p = SPDR;
    data_p++;
  }
  digitalWrite(SOCKET0_SS,HIGH);
  return( data_p );
}

/* reset MAX3421E. Returns number of cycles it took for PLL to stabilize after reset
  or zero if PLL haven't stabilized in 65535 cycles */
uint16_t MAX3421e::reset()
{
    byte tmp = 0;
    regWr( rUSBCTL, bmCHIPRES );                        //Chip reset. This stops the oscillator
    regWr( rUSBCTL, 0x00 );                             //Remove the reset
    while(!(regRd( rUSBIRQ ) & bmOSCOKIRQ )) {          //wait until the PLL is stable
        tmp++;                                          //timeout after 256 attempts
        if( tmp == 0 ) {
            return( false );
        }
    }
    return( true );
}

/* initialize MAX3421E. Set Host mode, pullups, and stuff. Returns 0 if success, -1 if not */
void MAX3421e::Spi_Init()
{
	pinMode(MEM_PW,OUTPUT);
	digitalWrite(MEM_PW,HIGH);
	//pinMode(SERID_PW,OUTPUT);
	//digitalWrite(SERID_PW,HIGH);
	pinMode(SD_SS,OUTPUT);
	digitalWrite(SD_SS,HIGH);
    
	//xbee802.ON();
	//delay(100);
	beginSerial(XBEE_RATE, 0);
	pinMode(XBEE_PW,OUTPUT);
	delay(100); 
	digitalWrite(XBEE_PW,HIGH);
	delay(100); 	

	uint8_t tmp;
  	
      // initialize SPI pins
      pinMode(XBEE_MON, INPUT);            
      pinMode(SD_SCK, OUTPUT);
      pinMode(SD_MOSI, OUTPUT);
      pinMode(SD_MISO, INPUT);
      pinMode(SOCKET0_SS, OUTPUT);
      digitalWrite( SOCKET0_SS, HIGH ); 

      /* mode 00 (CPOL=0, CPHA=0) master, fclk/2. Mode 11 (CPOL=11, CPHA=11) is also supported by MAX3421E */
      SPCR = 0x50;
      SPSR = 0x01;
      /**/
      tmp = SPSR;
      tmp = SPDR;      
      }
 


/*Initialize the MAX3421e as a Host*/
void MAX3421e::Host()
{
       /* Configure full-duplex SPI, interrupt pulse   */
      regWr( rPINCTL,( bmFDUPSPI + bmINTLEVEL + bmGPXB ));    //Full-duplex SPI, level interrupt, GPX      
      if( reset() == false ) {                                //stop/start the oscillator
      USB.println("Error: OSCOKIRQ failed to assert");
      }

      /* configure host operation */
      regWr( rMODE, bmDPPULLDN|bmDMPULLDN|bmHOST|bmSEPIRQ );    // set pull-downs, Host, Separate GPIN IRQ on GPX
      regWr( rHIEN, bmCONDETIE|bmFRAMEIE );                     //connection detection
      /* check if device is connected */
      regWr( rHCTL,bmSAMPLEBUS );                               // sample USB bus
      while(!(regRd( rHCTL ) & bmSAMPLEBUS ));                  //wait for sample operation to finish
      busprobe();                                               //check if anything is connected
      regWr( rHIRQ, bmCONDETIRQ );                              //clear connection detect interrupt                 
      regWr( rCPUCTL, 0x01 );					// Enable interruptions
}

/*Initialize the MAX3421e as a Device*/
void MAX3421e::Device()
{	
	/* Configure full-duplex SPI, interrupt pulse   */
      regWr( rPINCTL,( bmFDUPSPI + bmINTLEVEL + bmGPXB ));    //Full-duplex SPI, level interrupt, GPX      
      if( reset() == false ) {                                //stop/start the oscillator
        USB.println("Error: OSCOKIRQ failed to assert");
      }

	regWr(rEPIEN,(bmSUDAVIE|bmIN3BAVIE));			// Data available | Endpoint 3 in buffer available	
	regWr(rUSBIEN,(bmURESIE|bmURESDNIE));			// Reset interrupt enabled | Reset done interrupt
	//regWr(rUSBCTL,(bmCONNECT|bmVBGATE));			// VBGATE=1 disconnects D+ pullup if host turns off VBUS
	regWr(rUSBCTL,(bmCONNECT));				// VBGATE=1 disconnects D+ pullup 		
	regWr( rCPUCTL, 0x01 );					// Enables interruptions
}



/* probe bus to determine device presense and speed and switch host to this speed */
void MAX3421e::busprobe()
{
    uint8_t bus_sample;			
    bus_sample = regRd( rHRSL );				//Get J,K status
    bus_sample &= ( bmJSTATUS|bmKSTATUS );			//zero the rest of the byte
    switch( bus_sample ) {					//start full-speed or low-speed host 
        case( bmJSTATUS ):
            if(( regRd( rMODE ) & bmLOWSPEED ) == 0 ) {
                regWr( rMODE, MODE_FS_HOST );			//start full-speed host
                vbusState = FSHOST;
            }
            else {
                regWr( rMODE, MODE_LS_HOST);			//start low-speed host
                vbusState = LSHOST;
            }
            break;
        case( bmKSTATUS ):
            if(( regRd( rMODE ) & bmLOWSPEED ) == 0 ) {
                regWr( rMODE, MODE_LS_HOST );			//start low-speed host
                vbusState = LSHOST;
            }
            else {
                regWr( rMODE, MODE_FS_HOST );			//start full-speed host
                vbusState = FSHOST;
            }
            break;
        case( bmSE1 ):						//illegal state
            vbusState = SE1;
            break;
        case( bmSE0 ):						//disconnected state
          regWr( rMODE, bmDPPULLDN|bmDMPULLDN|bmHOST|bmSEPIRQ);
          vbusState = SE0;
          break;
        }//end switch( bus_sample )
}

/* MAX3421 state change task and interrupt handler */
uint8_t MAX3421e::Task( void )
{
    byte rcode = 0;
    byte pinvalue;    
    pinvalue = digitalRead( XBEE_MON );    
    if( pinvalue  == LOW ) {
        rcode = IntHandler();
    }
    return( rcode );    
}   


uint8_t MAX3421e::IntHandler()
{
    uint8_t HIRQ;
    uint8_t HIRQ_sendback = 0x00;
    HIRQ = regRd( rHIRQ );                  //determine interrupt source    
    if( HIRQ & bmCONDETIRQ ) {
        busprobe();
        HIRQ_sendback |= bmCONDETIRQ;
    }
    /* End HIRQ interrupts handling, clear serviced IRQs    */
    regWr( rHIRQ, HIRQ_sendback );
    return( HIRQ_sendback );
}
