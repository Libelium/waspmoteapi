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
 *  Implementation:	Yuri Carmona
 */


#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspXBee900.h"

/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_900 /////////////////////////////////////////////////////////////////

const char	get_RF_errors_900[]		PROGMEM	 = 	"7E0004085245520E";
const char 	get_good_pack_900[]		PROGMEM  = 	"7E0004085247441A";
const char 	get_channel_RSSI_900[]	PROGMEM  = 	"7E0005085252430000";
const char 	get_trans_errors_900[]	PROGMEM  = 	"7E000408525452FF";
const char 	get_temperature_900[]	PROGMEM  = 	"7E00040852545001";
const char 	get_supply_Volt_900[]	PROGMEM  = 	"7E0004085225562A";
const char	restore_compiled_900[]	PROGMEM  = 	"7E00040852523122";


const char* const table_900[] PROGMEM= 	  
{   
	get_RF_errors_900,		// 0
  	get_good_pack_900,		// 1
  	get_channel_RSSI_900,	// 2
  	get_trans_errors_900,	// 3  
	get_temperature_900,	// 4
	get_supply_Volt_900,	// 5
	restore_compiled_900	// 6
  	
};


/******************************************************************************
 * Class methods
 ******************************************************************************/

/*
 * Function: It initalizes all the necessary variables including its parent's 
 * variables
 * 
 * Parameters:
 * 'protocol_used' : specifies the protocol used in the XBee module 
 * 'uart_used' : specifies the UART where the data are sent to (SOCKET0 or SOCKET1)
 * Returns: void
*/
void WaspXBee900::init(	uint8_t uart_used )
{	
	protocol=XBEE_900;
	uart=uart_used;
	
	data_length=0;
	it=0;
	rxFrameType=0;
	
	pos=0;
	discoveryOptions=0x00;
	
	scanTime[0]=SCAN_TIME_DIGIMESH_H;
	scanTime[1]=SCAN_TIME_DIGIMESH_L;
	encryptMode=ENCRYPT_MODE_DIGIMESH;
	timeRSSI=TIME_RSSI_DIGIMESH;
	
	frameNext=0;
	replacementPolicy=XBEE_OUT;	
	error_AT=2;
	error_RX=2;
	error_TX=2;
	clearFinishArray();
	clearCommand();
}

/*
 Function: Read the number of times the RF receiver detected a CRC or length error
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "errorsRF" variable number of times CRC or length error
*/
uint8_t WaspXBee900::getRFerrors()
{
	int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_RF_errors_900
    strcpy_P(buffer, (char*)pgm_read_word(&(table_900[0])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        errorsRF[0]=data[0];
        delay(20);
        errorsRF[1]=data[1];
        delay(20);       
    } 
    return error;
}

/*
 Function: Read the number of good frames with valid MAC headers that are 
 received on the RF interface
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "goodPackets" variable the number of good frames received
*/
uint8_t WaspXBee900::getGoodPackets()
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_good_pack_900
    strcpy_P(buffer, (char*)pgm_read_word(&(table_900[1])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        goodPackets[0]=data[0];
        delay(20);
        goodPackets[1]=data[1];
        delay(20);       
    } 
    return error;
}

/*
 Function: Reads the DBM level of the designated channel
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "channelRSSI" variable the DBM level of the designated channel
 Parameters:
   channel --> The channel to get the DBM value
*/
uint8_t WaspXBee900::getChannelRSSI(uint8_t channel)
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_channel_RSSI_900
    strcpy_P(buffer, (char*)pgm_read_word(&(table_900[2])));
    
    gen_data(buffer,channel);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        channelRSSI=data[1];
        delay(20);
    } 
    return error;
}

/*
 Function:  Read the number of MAC frames that exhaust MAC retries without ever 
 receiving a MAC acknowledgement message from the adjacent node
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "transmisionErrors" variable the number of MAC frames 
 that exhaust	 
*/
uint8_t WaspXBee900::getTransmisionErrors()
{
    int8_t error=2;     
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_900[3])));//get_trans_errors_900
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        transmisionErrors[0]=data[0];
        delay(20);
        transmisionErrors[1]=data[1];
        delay(20);       
    } 
    return error;
}


/*
 Function: Read module temperature in Celsius. Negatives temperatures can be 
 returned
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the TP command. Stores in global "temperature" variable the 
 readed temp in Celsius
*/
uint8_t WaspXBee900::getTemperature()
{
    int8_t error=2;
	error_AT=2;
	char buffer[20];	    
		    
	// get_temperature_900
	strcpy_P(buffer, (char*)pgm_read_word(&(table_900[4])));
	gen_data(buffer);
	error=gen_send(buffer);

    if(error==0)
    {
            temperature[0]=data[0];
            delay(20);
            temperature[1]=data[1];    
            delay(20);
    }
    return error;
}

/*
 Function: Reads the voltage on the Vcc pin
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the %V command. Stores in global "supplyVoltage" variable the VCC
*/
uint8_t WaspXBee900::getSupplyVoltage()
{
    int8_t error=2;
    error_AT=2;
	char buffer[20];	    
	
	// get_supply_Volt_900
	strcpy_P(buffer, (char*)pgm_read_word(&(table_900[5])));
	gen_data(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
            supplyVoltage[0]=data[0];
            delay(20);
            supplyVoltage[1]=data[1];    
            delay(20);
    }
    return error;
}

/*
 Function: Restore module parameters to compiled defaults
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the R1 command.
*/
uint8_t WaspXBee900::restoreCompiled()
{
    int8_t error=2;    
    error_AT=2;
	char buffer[20];	
	
	//restore_compiled_900
	strcpy_P(buffer, (char*)pgm_read_word(&(table_900[6])));
	gen_data(buffer);
	error=gen_send(buffer);
    
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
*/
uint8_t WaspXBee900::sendXBeePriv(struct packetXBee* packet)
{
	// Local variables
	uint8_t TX[300];
    uint8_t counter=0;  
    uint8_t protegido=0;
    uint8_t tipo=0;
    int8_t error=2; 
    
    clearCommand();

    error_TX=2;
    
    // clear TX variable where the frame is going to be filled
	memset(TX,0x00,sizeof(TX) );
    
    /* Create the XBee frame */
    TX[0]=0x7E;
    TX[1]=0x00;
    
    // set frame ID as 0x01, so response message will be sent
    TX[4]=0x01;
    
    it=0;
    error_AT=2;
    

    if( (packet->mode==BROADCAST) || (packet->mode==UNICAST) )
    {
		// set fragment length for 'Transmit Request' frames (0x10)
        TX[2]=14+packet->data_length; 
      
        TX[3]=0x10; // frame Type
        tipo=18;	 
        
        // set 64-Destination Address   
        if(packet->mode == BROADCAST)
        {
			// set BROADCAST address
            TX[5]=0x00;
			TX[6]=0x00;
			TX[7]=0x00;
			TX[8]=0x00;
			TX[9]=0x00;
			TX[10]=0x00;
			TX[11]=0xFF;
			TX[12]=0xFF;	                
        }
        else if(packet->mode==UNICAST)
        {
			// set chosen address in setDestinationParams function
			TX[5]=packet->macDH[0];
			TX[6]=packet->macDH[1];
			TX[7]=packet->macDH[2];
			TX[8]=packet->macDH[3];
			TX[9]=packet->macDL[0];
			TX[10]=packet->macDL[1];
			TX[11]=packet->macDL[2];
			TX[12]=packet->macDL[3];       
        }
        
        // set frame bytes
        TX[13]=0xFF;
        TX[14]=0xFE; 
		TX[15]=0x00;	
        TX[16]=0x00;  
        it=0;
        
        // generate RF Data payload which is composed by [Api header]+[Data]
        genDataPayload(packet,TX,17);
        
        // set checksum     
        TX[packet->data_length+17]=getChecksum(TX); 
    }
    else // CLUSTER Type (Explicit Addressing Command Frame)
    {
		// set fragment length for 'Explicit Addressing Command' frames (0x11)
        TX[2]=20 + packet->data_length; 
        
        // set frame ID
        TX[3]=0x11; 
        
        tipo=24;
		TX[5]=packet->macDH[0];
		TX[6]=packet->macDH[1];
		TX[7]=packet->macDH[2];
		TX[8]=packet->macDH[3];
		TX[9]=packet->macDL[0];
		TX[10]=packet->macDL[1];
		TX[11]=packet->macDL[2];
		TX[12]=packet->macDL[3];     
	
        TX[13]=0xFF;
        TX[14]=0xFE;        
        TX[15]=packet->SD;
        TX[16]=packet->DE;
        TX[17]=0x00;
        TX[18]=packet->CID[0];     
        TX[19]=packet->PID[0];
        TX[20]=packet->PID[1];     
        TX[21]=0x00;
        TX[22]=0x00;
        it=0;
        
        // generate RF Data payload which is composed by [Api header]+[Data]
        genDataPayload(packet,TX,23);

        // set checksum
        TX[packet->data_length+23]=getChecksum(TX);  
            
    }
        
    
    // Generate the escaped API frame (it is necessary because AP=2)
    gen_frame_ap2(packet,TX,protegido,tipo);
    
    // switch MUX in case SOCKET1 is used
	if( uart==SOCKET1 )
	{
		Utils.setMuxSocket1();
	}
	
    // send frame through correspondent UART
    while(counter<(packet->data_length+tipo+protegido))
    {
		// print byte through correspondent UART
		printByte(TX[counter], uart); 
        counter++;
    }
    
    counter=0;    
   
	// read XBee's answer to TX request
	error_TX=txZBStatusResponse();
	error = error_TX; 
	
    packet->deliv_status=delivery_status;
    packet->discov_status=discovery_status;
    packet->true_naD[0]=true_naD[0];
    packet->true_naD[1]=true_naD[1];
    packet->retries=retries_sending;
    
    return error;
}





WaspXBee900	xbee900 = WaspXBee900();
