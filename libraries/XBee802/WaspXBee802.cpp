/*
 *  Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspXBee802.h"


/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_802 /////////////////////////////////////////////////////////////////

const char set_retries_802[] 	PROGMEM  	= "7E0005085252520000";	// AT+RR
const char get_retries_802[] 	PROGMEM 	= "7E00040852525201";   // AT+RR
const char set_delay_slots_802[] PROGMEM 	= "7E00050852524E0000";	// AT+RN
const char get_delay_slots_802[] PROGMEM 	= "7E00040852524E05";   // AT+RN
const char set_mac_mode_802[] 	PROGMEM 	= "7E000508524D4D0000";	// AT+MM
const char get_mac_mode_802[] 	PROGMEM 	= "7E000408524D4D0B";   // AT+MM
const char set_energy_thres_802[] PROGMEM 	= "7E0005085243410000";	// AT+CA
const char get_energy_thres_802[] PROGMEM 	= "7E00040852434121";   // AT+CA
const char get_CCA_802[] 		PROGMEM 	= "7E0004085245431D";   // AT+EC
const char reset_CCA_802[] 		PROGMEM 	= "7E000508524543001D";	// AT+EC
const char get_ACK_802[] 		PROGMEM 	= "7E0004085245411F";	// AT+EA
const char reset_ACK_802[]		PROGMEM 	= "7E000508524541001F";	// AT+EA


const char* const table_802[] PROGMEM = 	  
{   
	set_retries_802,		// 0
  	get_retries_802,		// 1
  	set_delay_slots_802,	// 2
  	get_delay_slots_802,	// 3
  	set_mac_mode_802,		// 4
	get_mac_mode_802,		// 5
 	set_energy_thres_802,	// 6
 	get_energy_thres_802,	// 7
 	get_CCA_802,			// 8
 	reset_CCA_802,			// 9
 	get_ACK_802,			// 10
 	reset_ACK_802,			// 11
};



/******************************************************************************
 * Class methods
 ******************************************************************************/

/*
 Function: It initializes the necessary variables
 Parameters:
	'uart_used' : specifies the UART where the data are sent to 
 Returns: void
*/
void WaspXBee802::init(	uint8_t uart_used	)
{
	// set protocol and socket used for XBee module
	protocol=XBEE_802_15_4;
	uart=uart_used;

	pos=0;
	discoveryOptions=0x00;
	awakeTime[0]=AWAKE_TIME_802_15_4_H;
	awakeTime[1]=AWAKE_TIME_802_15_4_L;
	sleepTime[0]=SLEEP_TIME_802_15_4_H;
	sleepTime[1]=SLEEP_TIME_802_15_4_L;
	scanTime[0]=SCAN_TIME_802_15_4;
	scanChannels[0]=SCAN_CHANNELS_802_15_4_H;
	scanChannels[1]=SCAN_CHANNELS_802_15_4_L;
	encryptMode=ENCRYPT_MODE_802_15_4;
	powerLevel=POWER_LEVEL_802_15_4;
	timeRSSI=TIME_RSSI_802_15_4;
	sleepOptions=SLEEP_OPTIONS_802_15_4;
	retries=0;
	delaySlots=0;
	macMode=0;
	energyThreshold=0x2C;
	counterCCA[0]=0x00;
	counterCCA[1]=0x00;
	counterACK[0]=0x00;
	counterACK[1]=0x00;

	counter=0;
	data_length=0;
	it=0;		
	rxFrameType=0;
	frameNext=0;
	replacementPolicy=XBEE_OUT;	
	error_AT=2;
	error_RX=2;
	error_TX=2;
	clearFinishArray();
	clearCommand();
}


/*
 Function: Set the maximum number of retries to execute in addition to the
           three retries defined in the 802.15.4 protocol
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the RR command
 Parameters:
   retry: number of retries (0-6)
*/
uint8_t WaspXBee802::setRetries(uint8_t retry)
{
    int8_t error=2;
    error_AT=2; 

    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[0])));//set_retries_802
   
    gen_data(buffer,retry);
    gen_checksum(buffer);
    error=gen_send(buffer);

    if(!error)
    {
        retries=retry;
    }
    return error;
}

/*
 Function: Get the retries that specifies the RR command
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "retries" variable the number of retries
*/
uint8_t WaspXBee802::getRetries()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;
    
    //get_retries_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[1])));
    if(buffer==NULL)return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    

    if(!error)
    {
        retries=data[0];
    }
    return error;
}

/*
 Function: Set the minimun value of the back-off exponent in CSMA/CA
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the RN command
 Parameters:
   exponent: value of the back-off exponential (0-3)
*/
uint8_t WaspXBee802::setDelaySlots(uint8_t exponent)
{
	int8_t error=2;
   	char buffer[20];
	error_AT=2;
   	
   	// set_delay_slots_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[2])));
	if(buffer==NULL)return 1;

	gen_data(set_delay_slots_802,exponent);
	gen_checksum(set_delay_slots_802);
	error=gen_send(set_delay_slots_802);
	
    if(!error)
    {
        delaySlots=exponent;
    }
    
    return error;
}

/*
 Function: Get the minimum value of the back-off exponent in CSMA/CA
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "delaySlots" variable the back-off exponent
*/
uint8_t WaspXBee802::getDelaySlots()
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;
    
    // get_delay_slots_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[3])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        delaySlots=data[0];
    }
    return error;
}

/*
Function: Set the Mac Mode, choosen between the 4 options (0/1/2/3)
Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
Values: Change the MM command
Parameters:
  mac: set the mac mode to use (0-3)
*/
uint8_t WaspXBee802::setMacMode(uint8_t mac)
{
    int8_t error=2;
    char buffer[20];
    error_AT=2;

	// set_mac_mode_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[4])));
    if(buffer==NULL) return 1;
    gen_data(buffer,mac);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        macMode=mac;
    }
    return error;
}

/*
Function: Get the Mac Mode
Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
Values: Stores in global "macMode" variable the Mac Mode
*/
uint8_t WaspXBee802::getMacMode()
{
    int8_t error=2;    
    char buffer[20]; 
    error_AT=2;

	// get_mac_mode_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[5])));
    if(buffer==NULL) return 1;
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        macMode=data[0];
    }
    return error;
}

/*
 Function: Set the CA threshold in the CCA process to detect energy on the channel
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the CA command
 Parameters:
   threshold: CA threshold in the CCA process (0x00-0x50)
*/
uint8_t WaspXBee802::setEnergyThreshold(uint8_t threshold)
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// set_energy_thres_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[6])));
    if(buffer==NULL) return 1;

    gen_data(buffer,threshold);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        energyThreshold=threshold;
    }
    return error;
}

/*
 Function: Get the Energy Threshold used in the CCA process
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "energyThreshold" variable any error happened while execution
*/
uint8_t WaspXBee802::getEnergyThreshold()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// get_energy_thres_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[7])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        energyThreshold=data[0];
    } 
    return error;
}

/*
 Function: It gets the number of times too much energy has been found on the channel
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "counterCCA" variable number of times too much energy has been found
*/
uint8_t WaspXBee802::getCCAcounter()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// get_CCA_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[8])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        counterCCA[0]=data[0];
        counterCCA[1]=data[1];
    } 
    return error;
}

/*
 Function: Reset the CCA counter
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EC command
*/
uint8_t WaspXBee802::resetCCAcounter()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// reset_CCA_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[9])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        counterCCA[0]=0;
        counterCCA[1]=0;
    }
    return error;
}

/*
 Function: Get the number of times there has been an ACK failure
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "counterACK" variable the number of times there has been an ACK failure
*/
uint8_t WaspXBee802::getACKcounter()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// get_ACK_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[10])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        counterACK[0]=data[0];
        counterACK[1]=data[1];
    } 
    return error;
}

/*
 Function: Reset the ACK counter
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EA command
*/
uint8_t WaspXBee802::resetACKcounter()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];

	// reset_ACK_802
    strcpy_P(buffer, (char*)pgm_read_word(&(table_802[11])));
    if(buffer==NULL) return 1;

    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        counterACK[0]=0;
        counterACK[1]=0;
    }
    return error;
}



/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * 
 * Parameters: 
 *   packet :	A struct of packetXBee type
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 
 * --> DIGI's XBee Packet inner structure:
 * 
 * StartDelimiter(1B) + Length(2B) +  Frame Data(variable) + Checksum(1B)
 *  ______________     ___________     __________________     __________
 * |              |   |     |     |   |					 |   |			|
 * |	0x7E	  | + | MSB | LSB | + |    Frame Data    | + |	1 Byte	|
 * |______________|   |_____|_____|   |__________________|   |__________|
 * 
 * Remarks: 
 * It is necessary to set the MY address to 0xFFFF when sending in
 * order to insert the source mac address within the packet. Thus, the
 * receiver will be able to know the source's mac address
*/
uint8_t WaspXBee802::sendXBeePriv(struct packetXBee* packet)
{	
	// Local variables
	uint8_t TX[300];
    uint8_t counter=0; 
    unsigned long previous=0;
    uint8_t protegido=0;
    uint8_t tipo=0;
    uint8_t estado=1;
    int8_t error=2;
    uint8_t old_netAddress[2];
    uint8_t net_Address_changed = 0;    

    error_TX = 2;
    
    // clear TX variable where the frame is going to be filled
	memset(TX,0x00,sizeof(TX));
    
    // Create the XBee frame
    TX[0] = 0x7E;
    TX[1] = 0x00;
    
    // set frame ID as 0x01, so response message will be sent
    TX[4] = 0x01;
    
    // init variables
    it = 0;
    error_AT = 2;
 
	// NOTE: It is necessary to set the MY address to 0xFFFF when sending in 
	// order to insert the source mac address within the packet. Thus, the 
	// receiver will be able to know the source's mac address
	// Initialize variable
    old_netAddress[0] = 0x00;
    old_netAddress[1] = 0x00;
 
	// BROADCAST MODE
    if( packet->mode == BROADCAST )
	{
		tipo = 15;
		
		// set packet length
		TX[2] = 11+packet->data_length; 
		
		// set TX request frame (0x00)
		TX[3] = 0x00;
	    
	    // get the backup MY address
		previous = millis();
		error_AT = 2;
		while( ((error_AT == 1) || (error_AT == 2)) && (millis()-previous<500) )
		{
			estado = getOwnNetAddress();
			
			 //avoid millis overflow problem
			if( millis() < previous ) previous=millis();
        }
			
        old_netAddress[0] = sourceNA[0];
        old_netAddress[1] = sourceNA[1];
	    
	    // disable the MY address to include the MAC address as source address
	    previous = millis();
        error_AT = 2;        
        while( ((error_AT == 1) || (error_AT == 2)) && (millis()-previous<500) )
        {
			estado=setOwnNetAddress(0xFF,0xFF);
			net_Address_changed = 1;
			
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis();
        }
        error = 2;
		
		// set BROADCAST address
        TX[5] = 0x00;
		TX[6] = 0x00;
		TX[7] = 0x00;
		TX[8] = 0x00;
		TX[9] = 0x00;
		TX[10] = 0x00;
		TX[11] = 0xFF;
		TX[12] = 0xFF;
		
		// set Options enabling ACK 
		TX[13] = 0x00;
		it = 0;
		
		// generate RF Data payload which is composed by [Api header]+[Data]
		genDataPayload(packet,TX,14);
				
		// set checksum
		TX[packet->data_length+14] = getChecksum(TX); 
    }   
    else if(packet->mode == UNICAST)
	{
		// 64-bit Destination Address
		if( packet->address_type == _64B )
		{
			tipo = 15;
			
			// set fragment length			 
			TX[2] = 11+packet->data_length;
			
			// set TX Request Frame Type (64-bit address)
			TX[3] = 0x00;
			
			// set chosen address in setDestinationParams function
			TX[5] = packet->macDH[0];
			TX[6] = packet->macDH[1];
			TX[7] = packet->macDH[2];
			TX[8] = packet->macDH[3];
			TX[9] = packet->macDL[0];
			TX[10] = packet->macDL[1];
			TX[11] = packet->macDL[2];
			TX[12] = packet->macDL[3];  
			
			// get the backup MY address
			previous = millis();
			error_AT = 2;
			while( ((error_AT == 1) || (error_AT == 2)) && (millis()-previous<500) )
			{
				estado = getOwnNetAddress();
				
				// avoid millis overflow problem
				if( millis() < previous ) previous=millis(); 
            }			
			old_netAddress[0] = sourceNA[0];
			old_netAddress[1] = sourceNA[1];
			
			// disable the MY address to include the MAC address as source address
			previous=millis();
			error_AT = 2;
			while( ((error_AT == 1) || (error_AT == 2)) && (millis()-previous<500) )
			{
				estado=setOwnNetAddress(0xFF,0xFF);
				net_Address_changed = 1;
				
				// avoid millis overflow problem
				if( millis() < previous ) previous=millis(); 
            }
			
			error = 2;
			TX[13] = 0x00;
			it = 0;

			// generate RF Data payload which is composed by [Api header]+[Data]
			genDataPayload(packet,TX,14);
					
			// setting checksum
			TX[packet->data_length+14] = getChecksum(TX);
        }
		// 16-Bit Destination Address
		else if( packet->address_type == _16B)
		{
			tipo = 9;
			
			// set TX Request frame Type (16-bit address)
			TX[3] = 0x01;
			
			// set Destination Address
			TX[5] = packet->naD[0];
			TX[6] = packet->naD[1];
			
			// Set Options enabling ACK
			TX[7] = 0x00;
			it=0;
			
			// generate RF Data payload which is composed by [Api header]+[Data]
			genDataPayload(packet,TX,8);
			
			// fragment length
			TX[2] = 5+packet->data_length;			

            // set checksum
            TX[packet->data_length+8] = getChecksum(TX);
		}
	}
	else
	{
		// no mode selected, exit with error
		return 2;
	}
   
    // Generate the escaped API frame (it is necessary because AP=2)
	gen_frame_ap2(packet,TX,protegido,tipo);
   
   	// switch MUX in case SOCKET1 is used
	if( uart == SOCKET1 )
	{
		Utils.setMuxSocket1();
	}
   
	counter = 0;
	// send frame through correspondent UART
	while( counter < (packet->data_length+tipo+protegido) )
	{
		// print byte through correspondent UART
		printByte(TX[counter], uart); 
		counter++;
	}
	counter = 0;
	
	// read XBee response to TX request
	error_TX = txStatusResponse();
    error = error_TX; 
    
    // set delivery status
	packet->deliv_status = delivery_status;
		
	// reset the backup MY address
	if( net_Address_changed == 1 )
	{
		error_AT = 2;
		previous = millis();
		while( ((error_AT == 1) || (error_AT == 2)) && (millis()-previous<500) )
		{
			estado = setOwnNetAddress(old_netAddress[0],old_netAddress[1]);
			
			//avoid millis overflow problem
			if( millis() < previous ) previous=millis(); 
		}
	}
    
    return error;
}



WaspXBee802	xbee802 = WaspXBee802();
