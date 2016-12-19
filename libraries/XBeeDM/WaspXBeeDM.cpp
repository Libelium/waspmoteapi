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
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspXBeeDM.h"

/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_DM /////////////////////////////////////////////////////////////////

const char 	get_good_pack_DM[]		PROGMEM  = 	"7E0004085247441A";		// AT+GD
const char 	get_trans_errors_DM[]	PROGMEM  = 	"7E000408525452FF";		// AT+TR
const char 	set_network_hops_DM[]	PROGMEM  = 	"7E000508524E480000";	// AT+NH
const char 	get_network_hops_DM[]	PROGMEM  = 	"7E000408524E480F";		// AT+NH
const char 	set_network_delay_DM[]	PROGMEM  = 	"7E000508524E4E0000";	// AT+NN
const char 	get_network_delay_DM[]	PROGMEM  = 	"7E000408524E4E09";		// AT+NN
const char 	set_network_retries_DM[] PROGMEM = 	"7E000508524D520000";	// AT+MR
const char 	get_network_retries_DM[] PROGMEM = 	"7E000408524D5206";		// AT+MR
const char 	set_retries_DM[] 		PROGMEM  = 	"7E0005085252520000"; 	// AT+RR  
const char 	get_retries_DM[] 		PROGMEM  = 	"7E00040852525201";		// AT+RR


const char* const table_DM[] PROGMEM = 	  
{   	
  	get_good_pack_DM,		// 0
  	get_trans_errors_DM,	// 1
  	set_network_hops_DM,	// 2
	get_network_hops_DM,	// 3
	set_network_delay_DM,	// 4
	get_network_delay_DM,	// 5
	set_network_retries_DM,	// 6
	get_network_retries_DM,	// 7
	set_retries_DM,			// 8
	get_retries_DM,			// 9
  	
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
void WaspXBeeDM::init(	uint8_t uart_used	)
{	
	protocol=DIGIMESH;
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
	
	awakeTime[0]=AWAKE_TIME_DIGIMESH_H;
	awakeTime[1]=AWAKE_TIME_DIGIMESH_M;
	awakeTime[2]=AWAKE_TIME_DIGIMESH_L;
	sleepTime[0]=SLEEP_TIME_DIGIMESH_H;
	sleepTime[1]=SLEEP_TIME_DIGIMESH_M;
	sleepTime[2]=SLEEP_TIME_DIGIMESH_L;
	
	sleepOptions=SLEEP_OPTIONS_DIGIMESH;
	powerLevel=POWER_LEVEL_DIGIMESH;
			
	networkHops=7;
	netDelaySlots=3;
	meshNetRetries=1;

	frameNext=0;
	replacementPolicy=XBEE_OUT;
	error_AT=2;
	error_RX=2;
	error_TX=2;
	clearFinishArray();
	clearCommand();
}



/*
 * getGoodPackets
 * 
 * Read the number of good frames with valid MAC headers that are received on 
 * the RF interface
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 
 * Values: Stores in global "goodPackets" variable the number of good frames 
 * received
*/
uint8_t WaspXBeeDM::getGoodPackets()
{
    int8_t error = 2;     
    error_AT = 2;    
    char buffer[20];
    
    // get_good_pack_DM
    strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[0])));
    
    gen_data(buffer);
    error = gen_send(buffer);
    
    if(!error)
    {
        goodPackets[0] = data[0];
        goodPackets[1] = data[1];  
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
uint8_t WaspXBeeDM::getTransmisionErrors()
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_trans_errors_DM
    strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[1])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        transmisionErrors[0]=data[0];
        transmisionErrors[1]=data[1];
    } 
    return error;
}

/*
 Function: Set the maximum number of hops expected to be seen in a network route
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NH command
 Parameters:
   nhops: maximum number of hops (1-0xFF)
*/
uint8_t WaspXBeeDM::setNetworkHops(uint8_t nhops)
{
    int8_t error=2;
	error_AT=2;
	char buffer[20];
	  
	// set_network_hops_DM
    strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[2])));
    
	gen_data(buffer,nhops);
	gen_checksum(buffer);
	error=gen_send(buffer);

    if(!error)
    {
        networkHops = nhops;
    }
    return error;
}

/*
 Function: Read the maximum number of hops expected to be seen in a network route
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "networkHops" variable max number of hops
*/
uint8_t WaspXBeeDM::getNetworkHops()
{
    int8_t error=2;        
	error_AT=2;
	char buffer[20];	    
	
	// get_network_hops_DM
	strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[3])));
	gen_data(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
        networkHops = data[0];
    } 
    return error;
}

/*
 Function: Set the maximum random number of network delay slots before 
 rebroadcasting a network packet
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NN command
 Parameters:
   dslots: maximum number of delay slots (0-0x0A)
*/
uint8_t WaspXBeeDM::setNetworkDelaySlots(uint8_t dslots)
{
    int8_t error=2; 
	error_AT=2;
	char buffer[20];	    
	
	// set_network_delay_DM
	strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[4])));
	gen_data(buffer,dslots);
	gen_checksum(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
        netDelaySlots = dslots;
    }
    return error;
}

/*
 Function: Read the maximum random number of network delay slots before 
 rebroadcasting a network packet
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "netDelaySlots" variable max random number of net 
 delay slots
*/
uint8_t WaspXBeeDM::getNetworkDelaySlots()
{
    int8_t error=2;
	error_AT=2;
	char buffer[20];	    
	
	// get_network_delay_DM
	strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[5])));
	gen_data(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
        netDelaySlots = data[0];
    } 
    return error;
}



/*
 Function: Set the maximum number of network packet delivery attempts
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the MR command
 Parameters:
   mesh: maximum number of attempts (0-7)
*/
uint8_t WaspXBeeDM::setMeshNetworkRetries(uint8_t mesh)
{
    int8_t error=2; 
	error_AT=2;
	char buffer[20];	    
	
	// set_network_retries_DM
	strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[6])));
	gen_data(buffer,mesh);
	gen_checksum(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
        meshNetRetries = mesh;
    }
    return error;
}

/*
 Function: Read the maximum number of network packet delivery attempts
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "meshNetRetries" variable max number of net packet 
 delivery attempts
*/
uint8_t WaspXBeeDM::getMeshNetworkRetries()
{
    int8_t error=2;
	error_AT=2;
	char buffer[20];	    
	
	// get_network_retries_DM
	strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[7])));
	gen_data(buffer);
	error=gen_send(buffer);
    
    if(error==0)
    {
        meshNetRetries = data[0];
    } 
    return error;
}


/*	
 * setRetries
 * 
 * Set the maximum number of MAC level packet delivery attempts for unicasts. 
 * If RR is non-zero packets sent from the radio will request an acknowledgement, 
 * and can be resent up to RR times if no acknowledgements are received.
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 
 * Values: Change the RR command
 * Parameters:
 * 	retry: number of retries (0x00-0x0F). Default=0x0A
*/
uint8_t WaspXBeeDM::setRetries(uint8_t retry)
{
    int8_t error = 2;
    error_AT = 2; 
 
	// set_retries_DM
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[8])));
   
    gen_data(buffer,retry);
    gen_checksum(buffer);
    error = gen_send(buffer);

    if(!error)
    {
        retries = retry;
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
uint8_t WaspXBeeDM::getRetries()
{
    int8_t error = 2;
    char buffer[20];
    error_AT = 2;
    
    //get_retries_DM
    strcpy_P(buffer, (char*)pgm_read_word(&(table_DM[9])));
    if( buffer == NULL ) return 1;

    gen_data(buffer);
    error = gen_send(buffer);
    

    if(!error)
    {
        retries = data[0];
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
*/
uint8_t WaspXBeeDM::sendXBeePriv(struct packetXBee* packet)
{
	// Local variables
	uint8_t TX[120];
    uint8_t counter=0;    
    uint8_t protegido=0;
    uint8_t tipo=0;
    int8_t error=2;
    
    clearCommand();

    error_TX=2;
    
    // clear TX variable where the frame is going to be filled
	memset(TX,0x00,sizeof(TX));
    
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
        
        // frame ID       
        TX[3]=0x10; 
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



WaspXBeeDM	xbeeDM = WaspXBeeDM();
