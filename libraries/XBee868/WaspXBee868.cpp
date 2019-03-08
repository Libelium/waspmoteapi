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

#include "WaspXBee868.h"

/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_868 /////////////////////////////////////////////////////////////////

const char	get_RF_errors_868[]			PROGMEM	= 	"7E0004085245520E"; // AT+ER
const char	get_good_pack_868[]			PROGMEM	= 	"7E0004085247441A"; // AT+GD
const char	get_channel_RSSI_868[]		PROGMEM	= 	"7E0005085252430000"; // AT+RC
const char	get_trans_errors_868[]		PROGMEM	= 	"7E000408525452FF"; // AT+TR
const char	get_temperature_868[]		PROGMEM	= 	"7E00040852545001"; // AT+TP
const char	get_supply_Volt_868[]		PROGMEM	= 	"7E0004085225562A"; // AT+%V
const char	get_device_type_868[]		PROGMEM	= 	"7E0004085244441D"; // AT+DD
const char	get_payload_bytes_868[]		PROGMEM	= 	"7E000408524E5007"; // AT+NP
const char	set_mult_broadcast_868[] 	PROGMEM = 	"7E000508524D540000"; // AT+MT
const char	get_mult_broadcast_868[] 	PROGMEM = 	"7E000408524D5404"; // AT+MT
const char	set_retries_868[]			PROGMEM	= 	"7E0005085252520000"; // AT+RR
const char	get_retries_868[]			PROGMEM	= 	"7E00040852525201"; // AT+RR
const char	get_duty_cycle_868[]		PROGMEM	= 	"7E0004085244431E"; // AT+DC
const char	get_reset_reason_868[]		PROGMEM	= 	"7E00040852522330"; // AT+R#
const char	get_ACK_errors_868[]		PROGMEM	= 	"7E00040852544110"; // AT+TA

const char* const table_868[] PROGMEM= 	  
{   	
	get_RF_errors_868,		// 0
	get_good_pack_868,		// 1
	get_channel_RSSI_868,	// 2
	get_trans_errors_868,	// 3
	get_temperature_868,	// 4
	get_supply_Volt_868,	// 5
	get_device_type_868,	// 6
	get_payload_bytes_868,	// 7
	set_mult_broadcast_868,	// 8
	get_mult_broadcast_868,	// 9
	set_retries_868,		// 10
	get_retries_868,		// 11
	get_duty_cycle_868,		// 12
	get_reset_reason_868,	// 13
	get_ACK_errors_868		// 14
};



/******************************************************************************
 * Class methods
 ******************************************************************************/


/*
 Function: It initalizes all the necessary variables
 Parameters:
	protocol_used : specifies the protocol used in the XBee module 
	uart_used : specifies the UART where the data are sent to (UART0 or UART1)	
 Returns: void
*/
void WaspXBee868::init(	uint8_t uart_used )
{
	// set protocol and socket used for XBee module	
	protocol=XBEE_868;
	uart=uart_used;
	
	pos=0;
	discoveryOptions=0x00;
	
	scanTime[0]=0x00;
	scanTime[1]=0x82;
	encryptMode=0;
	powerLevel=4;
	timeRSSI=0x20;

	ACKerrors[0]=0x00;
	ACKerrors[1]=0x00;
	errorsRF[0]=0x00;
	errorsRF[1]=0x00;
	goodPackets[0]=0x00;
	goodPackets[1]=0x00;
	transmisionErrors[0]=0x00;
	transmisionErrors[1]=0x00;
	maxPayloadBytes[0]=0x01;
	maxPayloadBytes[1]=0x00;
	multipleBroadcast=0x03;
	macRetries=0x0A;
	resetReason=0x00;
	
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
 Function: Read the number of times the RF receiver detected a CRC or length error
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "errorsRF" variable number of times CRC or length error
*/
uint8_t WaspXBee868::getRFerrors()
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_RF_errors_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[0])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        errorsRF[0]=data[0];
        errorsRF[1]=data[1];  
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
uint8_t WaspXBee868::getGoodPackets()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[1])));//get_good_pack_868
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(!error)
    {
        goodPackets[0]=data[0];
        goodPackets[1]=data[1]; 
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
uint8_t WaspXBee868::getChannelRSSI(uint8_t channel)
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
    
    // get_channel_RSSI_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[2])));
    
    gen_data(buffer,channel);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        channelRSSI=data[1];
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
 that exhaust MAC retries
*/
uint8_t WaspXBee868::getTransmisionErrors()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_trans_errors_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[3])));
    
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
 Function: Read module temperature in Celsius. Negatives temperatures can be 
 returned
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the TP command. Stores in global "temperature" variable the 
 read temp in Celsius
*/
uint8_t WaspXBee868::getTemperature()
{
    int8_t error=2;     
    error_AT=2;    
    char buffer[20];
 
	// get_temperature_868   
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[4])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
            temperature[0]=data[0];
            temperature[1]=data[1];    
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
uint8_t WaspXBee868::getSupplyVoltage()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
        
	// get_supply_Volt_868   
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[5])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
            supplyVoltage[0]=data[0];
            supplyVoltage[1]=data[1];   
    }
    return error;
}

/*
 Function: Get the current device type
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the DD command. Stores in global "deviceType" variable the 
 current device type. Range: 0-0xFFFFFFFF 

*/
uint8_t WaspXBee868::getDeviceType()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_device_type_868 
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[6])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        for(it=0;it<4;it++)
        {
            deviceType[it]=data[it];
        }
    }
    return error;
}

/*
 Function: Get the bytes that can be used in the payload
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NP command. Stores in global "maxPayloadBytes" variable 
 the max Payload
*/
uint8_t WaspXBee868::getPayloadBytes()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_payload_bytes_868 
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[7])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        maxPayloadBytes[0]=data[0];
        maxPayloadBytes[1]=data[1];
    }
    return error;
} 

/*
 Function: Specifies the number of additional broadcast retransmissions
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the MT command
 Parameters:
   mtrans: number of additional broadcast retransmissions (Range: 0x00-0x0F). 
   Default: 0x03
*/
uint8_t WaspXBee868::setMultipleBroadcast(uint8_t mtrans)
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // set_mult_broadcast_868 
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[8])));
    
    gen_data(buffer,mtrans);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        multipleBroadcast=mtrans;
    }
    return error;
}

/*
 Function: Gets the number of additional broadcast retransmissions
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the MT command
*/
uint8_t WaspXBee868::getMultipleBroadcast()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_mult_broadcast_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[9])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        multipleBroadcast=data[0];
    }
    return error;
}

/*
 Function: Specifies the number of retries than can be sent for a given unicast 
 RF packet
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the RR command
 Parameters:
   macretries: number of retries than can be sent for a given unicast RF packet 
   (0x00-0x0F) Default value: 0x0A
*/
uint8_t WaspXBee868::setMacRetries(uint8_t macretries)
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // set_retries_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[10])));
    
    gen_data(buffer,macretries);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        macRetries=macretries;
    }
    return error;
}

/*
 Function: Gets the number of retries than can be sent for a given unicast RF packet
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the RR command
*/
uint8_t WaspXBee868::getMacRetries()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_retries_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[11])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        macRetries=data[0];
    }
    return error;
}

/*
 Function: Get the % it has been used of available Duty Cycle
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the DC command
*/
uint8_t WaspXBee868::getDutyCycle()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_duty_cycle_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[12])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        dutyCycle=data[0];
    }
    return error;
}

/*
 Function: Tells the reason for the last module reset
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the R# command and the resetReason possibilities are:
	0 = Power up reset 
	2 = Watchdog reset 
	3 = Software reset 
	4 = Reset line reset 
	5 = Brownout reset 
*/
uint8_t WaspXBee868::getResetReason()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_reset_reason_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[13])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        resetReason=data[0];
    }
    return error;
}

/*
 Function: Specifies the number of failed ACK retries
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the TA command
*/
uint8_t WaspXBee868::getACKerrors()
{
    int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    // get_ACK_errors_868
    strcpy_P(buffer, (char*)pgm_read_word(&(table_868[14])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        ACKerrors[0]=data[0];
        ACKerrors[1]=data[1];
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
uint8_t WaspXBee868::sendXBeePriv(struct packetXBee* packet)
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
	memset(TX,0x00,sizeof(TX));
    
    // Create the XBee frame
    TX[0]=0x7E;
    TX[1]=0x00;
    
    // set frame ID as 0x01, so response message will be sent
    TX[4]=0x01;
    
    it=0;
    error_AT=2;
    
    if( (packet->mode==BROADCAST) || (packet->mode==UNICAST) )
    {		
		// set packet length
		TX[2]=14+packet->data_length; 
        
        // set Frame Type 
        TX[3]=0x10; 
        tipo=18;
        	   
        if(packet->mode==BROADCAST)
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
        
        if(packet->mode==UNICAST)
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
    else // CLUSTER Type
    {
		// set packet length
        TX[2]=20+packet->data_length;        
          
        // set Frame Type 
        TX[3]=0x11; 
		tipo=24;
        
		// set chosen address in setDestinationParams function
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
		TX[17]=packet->CID[0];
		TX[18]=packet->CID[1];     
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



WaspXBee868	xbee868 = WaspXBee868();
