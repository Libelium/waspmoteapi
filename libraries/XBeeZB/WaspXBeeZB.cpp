/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

#include "WaspXBeeZB.h"


/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_ZB /////////////////////////////////////////////////////////////////

const char	reset_network_ZB[]		PROGMEM	= 	"7E000508524E520000"; 	// AT+NR
const char	get_parent_NA_ZB[]		PROGMEM	= 	"7E000408524D5008";		// AT+MP
const char	get_rem_children_ZB[]	PROGMEM	= 	"7E000408524E4314";		// AT+NC
const char	set_device_type_ZB[]	PROGMEM	=	"7E0005085244440000";	// AT+DD
const char	get_device_type_ZB[]	PROGMEM	=	"7E0004085244441D";		// AT+DD
const char	get_payload_ZB[]		PROGMEM	=	"7E000408524E5007";		// AT+NP
const char	get_ext_PAN_ZB[]		PROGMEM	=	"7E000408524F5006"; 	// AT+OP
const char	get_opt_PAN_ZB[]		PROGMEM	=	"7E000408524F490D";		// AT+OI
const char	set_max_uni_hops_ZB[]	PROGMEM	=	"7E000508524E480000";	// AT+NH
const char	get_max_uni_hops_ZB[]	PROGMEM	=	"7E000408524E480F";		// AT+NH
const char	set_max_brd_hops_ZB[]	PROGMEM	=	"7E0005085242480000";	// AT+BH
const char	get_max_brd_hops_ZB[]	PROGMEM	=	"7E0004085242481B";		// AT+BH
const char	set_stack_profile_ZB[]	PROGMEM	=	"7E000508525A530000";	// AT+ZS
const char	get_stack_profile_ZB[]	PROGMEM	=	"7E000408525A53F8";		// AT+ZS
const char	set_period_sleep_ZB[]	PROGMEM	=	"7E00050852534E0000";	// AT+SN
const char	set_join_time_ZB[]		PROGMEM	=	"7E000508524E4A0000";	// AT+NJ
const char	get_join_time_ZB[]		PROGMEM	=	"7E000408524E4A0D";		// AT+NJ
const char	set_channel_verif_ZB[]	PROGMEM	=	"7E000508524A560000";	// AT+JV
const char	get_channel_verif_ZB[]	PROGMEM	=	"7E000408524A5605";		// AT+JV
const char	set_join_notif_ZB[]		PROGMEM	=	"7E000508524A4E0000";	// AT+JN
const char	get_join_notif_ZB[]		PROGMEM	=	"7E000408524A4E0D";		// AT+JN
const char	set_aggreg_notif_ZB[]	PROGMEM	=	"7E0005085241520000";	// AT+AR
const char	get_aggreg_notif_ZB[]	PROGMEM	=	"7E00040852415212";		// AT+AR
const char	get_assoc_indic_ZB[]	PROGMEM	=	"7E0004085241491B";		// AT+AI
const char	set_encryp_options_ZB[]	PROGMEM	=	"7E00050852454F0000";	// AT+EO
const char	get_encryp_options_ZB[]	PROGMEM	=	"7E00040852454F11";		// AT+EO
const char	set_netwk_key_ZB[]		PROGMEM	=	"7E001408524E4B0000000000000000000000000000000000";	// AT+NK
const char	set_power_mode_ZB[]		PROGMEM	=	"7E00050852504D0000";	// AT+PM
const char	get_power_mode_ZB[]		PROGMEM	=	"7E00040852504D08";		// AT+PM
const char	get_supply_Volt_ZB[]	PROGMEM	=	"7E0004085225562A";		// AT+%V
const char	set_coordinator_ZB[]	PROGMEM	=	"7E0005085243450000";	// AT+CE
const char	get_coordinator_ZB[]	PROGMEM	=	"7E0004085243451D";		// AT+CE



const char* const table_ZB[] PROGMEM = 	  
{   	
	reset_network_ZB,		// 0
	get_parent_NA_ZB,		// 1
	get_rem_children_ZB,	// 2
	set_device_type_ZB,		// 3
	get_device_type_ZB,		// 4
	get_payload_ZB,			// 5
	get_ext_PAN_ZB,			// 6
	get_opt_PAN_ZB,			// 7
	set_max_uni_hops_ZB,	// 8
	get_max_uni_hops_ZB,	// 9
	set_max_brd_hops_ZB,	// 10
	get_max_brd_hops_ZB,	// 11
	set_stack_profile_ZB,	// 12
	get_stack_profile_ZB,	// 13
	set_period_sleep_ZB,	// 14
	set_join_time_ZB,		// 15
	get_join_time_ZB,		// 16
	set_channel_verif_ZB,	// 17
	get_channel_verif_ZB,	// 18
	set_join_notif_ZB,		// 19
	get_join_notif_ZB,		// 20
	set_aggreg_notif_ZB,	// 21
	get_aggreg_notif_ZB,	// 22
	get_assoc_indic_ZB,		// 23
	set_encryp_options_ZB,	// 24
	get_encryp_options_ZB,	// 25
	set_netwk_key_ZB,		// 26
	set_power_mode_ZB,		// 27
	get_power_mode_ZB,		// 28
	get_supply_Volt_ZB,		// 29  	
	set_coordinator_ZB,		// 30	
	get_coordinator_ZB,		// 31  	
};





/******************************************************************************
 * Class methods
 ******************************************************************************/


/*
 * 
 */
void	WaspXBeeZB::init( uint8_t uart_used	)
{
	protocol=ZIGBEE;
	uart=uart_used;
	
	pos=0;
	discoveryOptions=0x00;
	awakeTime[0]=AWAKE_TIME_ZIGBEE_H;
	awakeTime[1]=AWAKE_TIME_ZIGBEE_L;
	sleepTime[0]=SLEEP_TIME_ZIGBEE_H;
	sleepTime[1]=SLEEP_TIME_ZIGBEE_L;
	scanTime[0]=SCAN_TIME_ZIGBEE;
	scanChannels[0]=SCAN_CHANNELS_ZIGBEE_H;
	scanChannels[1]=SCAN_CHANNELS_ZIGBEE_L;
	timeEnergyChannel=TIME_ENERGY_CHANNEL_ZIGBEE;
	encryptMode=ENCRYPT_MODE_ZIGBEE;
	powerLevel=POWER_LEVEL_ZIGBEE;
	timeRSSI=TIME_RSSI_ZIGBEE;
	sleepOptions=SLEEP_OPTIONS_ZIGBEE;
	associationIndication=1;

	parentNA[0]=0xFF;
	parentNA[1]=0xFE;
	deviceType[0]=0x00;
	deviceType[1]=0x03;
	deviceType[2]=0x00;
	deviceType[3]=0x00;
	for(it=0;it<8;it++)
	{
		operating64PAN[it]=0x00;
	}
	maxUnicastHops=0x1E;
	maxBroadcastHops=0x00;
	stackProfile=0;
	joinTime=0xFF;
	channelVerification=0x00;
	joinNotification=0x00;
	aggregateNotification=0xFF;
	encryptOptions=0;
	for(it=0;it<16;it++)
	{
		networkKey[it]=0x00;
	}
	powerMode=4;
	
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
	apsEncryption=0;
}

/*
 Function: Reset the Network
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NR command
 Parameters: 
       reset --> Possible values are 0/1
         0: reset the node network interface
         1: reset the entirely network
*/
uint8_t WaspXBeeZB::resetNetwork(uint8_t reset)
{
    int8_t error=2;       
    error_AT=2;    
    char buffer[20];
    
    flush();
    
    // reset_network_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[0])));
    
    gen_data(buffer,reset);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    return error;
}

/*
 Function: Returns the 16b parent´s network address
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the MP command. Stores in global "parentNA" variable 
         the 16b parent address
*/
uint8_t WaspXBeeZB::getParentNetworkAddress()
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // get_parent_NA_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[1])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        parentNA[0]=data[0];
        parentNA[1]=data[1];
    }
    return error;
}

/*
 Function: Returns the number of children which can still connect to the current device
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NC command. Stores in global "remainingChildren" variable the number of
	 remaining children which can connect to this device
*/
uint8_t WaspXBeeZB::getRemainingChildren()
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // get_rem_children_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[2])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        remainingChildren=data[0];
    }
    return error;
}

/*
 Function: Set the current device type
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the DD command
 Parameters:
   type: current device type (0-0xFFFFFFFF)
*/
uint8_t WaspXBeeZB::setDeviceType(uint8_t* type)
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    //set_device_type_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[3])));
    
    gen_data(buffer,type);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        for(it=0;it<4;it++)
        {
            deviceType[it]=type[it];
        }
    }
    return error;
}

/*
 Function: Get the current device type
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the DD command. Stores in global "deviceType" variable the current device type
*/
uint8_t WaspXBeeZB::getDeviceType()
{
    int8_t error=2;
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[4])));//get_device_type_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        for(it=0;it<4;it++)
        {
            deviceType[it]=data[it];
            delay(20);
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
uint8_t WaspXBeeZB::getPayloadBytes()
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // get_payload_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[5])));
    
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
 Function: Get the 64-bit Operating PAN ID
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the OP command. Stores in global "operating64PAN" variable the 
   64b PAN ID
*/
uint8_t WaspXBeeZB::getOperating64PAN()
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // get_ext_PAN_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[6])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        for(it=0;it<8;it++)
        {
            operating64PAN[it]=data[it];            
        }
    }  
    return error;
}

/*
 Function: Get the 16-bit Operating PAN ID
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the OI command. Stores in global "operating16PAN" variable 
	the 16b PAN ID
*/
uint8_t WaspXBeeZB::getOperating16PAN()
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // get_opt_PAN_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[7])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        for(it=0;it<2;it++)
        {
            operating16PAN[it]=data[it];            
        }
    }  
    return error;
}

/*
 Function: Set the maximum hops limit
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NH command
 Parameters:
   hops: max number of hops that an unicast message can make (0x00-0xFF)
*/
uint8_t WaspXBeeZB::setMaxUnicastHops(uint8_t hops)
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[8])));//set_max_uni_hops_ZB
    
    gen_data(buffer,hops);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
		maxUnicastHops=hops;
    }
    return error;
} 

/*
 Function: Get the maximum hop limits
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NH command. Stores in global "error" variable 
         any error happened while execution
*/
uint8_t WaspXBeeZB::getMaxUnicastHops()
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[9])));//get_max_uni_hops_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        maxUnicastHops=data[0];
    }
    return error;
}
  
/*
 Function: Set the maximum number of hops for each broadcast data transmission
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the BH command
 Parameters:
   bhops: max number of hops a bradcast message can make (0x00-0x20)
*/
uint8_t WaspXBeeZB::setMaxBroadcastHops(uint8_t bhops)
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // set_max_brd_hops_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[10])));
    
    gen_data(buffer,bhops);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        maxBroadcastHops=bhops;
    }
    return error;
}

/*
 Function: Get the maximum number of hops for each broadcast data transmission
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the BH command. Stores in global "maxBroadcastHops" variable 
 the max number of broadcast hops
*/
uint8_t WaspXBeeZB::getMaxBroadcastHops()
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[11])));//get_max_brd_hops_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        maxBroadcastHops=data[0];
    }
    return error;
} 

/*
 Function: Set the ZigBee Stack profile
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the ZS command
 Parameters:
   profile: choosen stack profile (0-2)
*/
uint8_t WaspXBeeZB::setStackProfile(uint8_t profile)
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[12])));//set_stack_profile_ZB
    
    gen_data(buffer,profile);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        stackProfile=profile;
    }
    return error;
}

/*
 Function: Get the ZigBee Stack profile
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the ZS command. Stores in global "stackProfile" variable the stack profile
*/
uint8_t WaspXBeeZB::getStackProfile()
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[13])));//get_stack_profile_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        stackProfile=data[0];
    }
    return error;
}

/*
 Function: Set the number of Sleep Periods to not assert XBee pin
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the SN command
 Parameters:
   periods: array which contains the number of sleep periods to sleep
*/
uint8_t WaspXBeeZB::setPeriodSleep(uint8_t* periods)
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[14])));//set_period_sleep_ZB
    
    gen_data(buffer,periods);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        periodSleep[0]=periods[0];
        periodSleep[1]=periods[1];
    }
    return error;
}


/*
 Function: Set the time that a Coordinator/Router allows nodes to join
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NJ command
 Parameters:
   time: time allowed for joining (0x00-0xFF)
*/
uint8_t WaspXBeeZB::setJoinTime(uint8_t time)
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
    
    // set_join_time_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[15])));
    
    gen_data(buffer,time);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        joinTime=time;
    }
    return error;
}

/*
 Function: Read the time that a Coordinator/Router allows nodes to join
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NJ command. Stores in global "joinTime" variable the time allowing join
*/
uint8_t WaspXBeeZB::getJoinTime()
{
    int8_t error=2;        
    error_AT=2;
    
    char buffer[20];
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[16])));//get_join_time_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        joinTime=data[0];
    }
    return error;
}

/*
 Function: Set the channel verification parameter
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the JV command
 Parameters:
   verif: channel verification parameter (0-1)
*/
uint8_t WaspXBeeZB::setChannelVerification(uint8_t verif)
{
    int8_t error=2;        
    error_AT=2;    
    char buffer[20];
        
    // set_channel_verif_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[17])));
    
    gen_data(buffer,verif);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        channelVerification=verif;
    }
    return error;
}

/*
 Function: Read the channel verification parameter
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the JV command. Stores in global "channelVerification" variable 
         any error happened while execution
*/
uint8_t WaspXBeeZB::getChannelVerification()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    // get_channel_verif_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[18])));
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        channelVerification=data[0];
    }
    return error;
}

/*
 Function: Set the join notification setting
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the JN command
 Parameters:
   notif: join notification setting (0-1)
*/
uint8_t WaspXBeeZB::setJoinNotification(uint8_t notif)
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[19])));//set_join_notif_ZB
    
    gen_data(buffer,notif);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        joinNotification=notif;
    }
    return error;
}

/*
 Function: Read the join notification setting
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the JN command. Stores in global "error" variable 
         any error happened while execution
*/
uint8_t WaspXBeeZB::getJoinNotification()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[20])));//get_join_notif_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        joinNotification=data[0];
    }
    return error;
}

/*
 Function: Set time between consecutive aggregate route broadcast messages
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the AR command
 Parameters:
   anotif: time between consecutive aggregate route broadcast messages (0x00-0xFF)
*/
uint8_t WaspXBeeZB::setAggregateNotification(uint8_t anotif)
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[21])));//set_aggreg_notif_ZB
    
    gen_data(buffer,anotif);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        aggregateNotification=anotif;
    }
    return error;
}

/*
 Function: Get time between consecutive aggregate route broadcast messages
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the AR command. Stores in global "aggregateNotification" variable the time
*/
uint8_t WaspXBeeZB::getAggregateNotification()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[22])));//get_aggreg_notif_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        aggregateNotification=data[0];
    }
    return error;;
}

/*
 Function: Read information regarding last node join request
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the AI command. Stores in global "associationIndication" variable 
         any error happened while execution
*/
uint8_t WaspXBeeZB::getAssociationIndication()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    flush();
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[23])));//get_assoc_indic_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        associationIndication=data[0];
    }
    return error;
}

/*
 Function: Configure options for encryption
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EO command
 Parameters:
   eoptions: options for encryption (0x00-0xFF)
*/
uint8_t WaspXBeeZB::setEncryptionOptions(uint8_t eoptions)
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    // set_encryp_options_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[24])));
    
    gen_data(buffer,eoptions);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        encryptOptions=eoptions;
    }
    return error;
}

/*
 Function: Read options for encryption
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the EO command. Stores in global "encrypOptions" variable 
         any error happened while execution
*/
uint8_t WaspXBeeZB::getEncryptionOptions()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[25])));//get_encryp_options_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        encryptOptions=data[0];
    }
    return error;
}

/*
 Function: Set the 128-bit AES encryption key
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NK command
 Parameters:
   key: 16 position array that contains the 128b AES key (0-0xFFFFFFFFFFFFFFFF)
*/
uint8_t WaspXBeeZB::setNetworkKey(const char* key)
{
    int8_t error=2;        
    error_AT=2;
    char buffer[50];    
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[26])));//set_netwk_key_ZB
    
    gen_data(buffer,key);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
	for(it=0;it<16;it++)
	{
		networkKey[it]=key[it];
	}
    }
    return error;
}

/*
 Function: Set the power mode of the device
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the PM command
 Parameters:
   power: power mode (0-1)
*/
uint8_t WaspXBeeZB::setPowerMode(uint8_t power)
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    // set_power_mode_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[27])));
    
    gen_data(buffer,power);
    gen_checksum(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        powerMode=power;
    }
    return error;
}

/*
 Function: Read the power mode of the device
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the PM command. Stores in global "powerMode" variable the power mode 
*/
uint8_t WaspXBeeZB::getPowerMode()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
    
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[28])));//get_power_mode_ZB
    
    gen_data(buffer);
    error=gen_send(buffer);
    
    if(error==0)
    {
        powerMode=data[0];
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
uint8_t WaspXBeeZB::getSupplyVoltage()
{
    int8_t error=2;        
    error_AT=2;
    char buffer[20];
        
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[29])));//get_supply_Volt_ZB
    
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
 Function: Sets the Application Layer Encryption
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t WaspXBeeZB::setAPSencryption(uint8_t mode)
{
    int8_t error=0;
        
    if(mode==XBEE_ON) apsEncryption=1;
    else if(mode==XBEE_OFF) apsEncryption=0;
    
    error_AT=0;
    
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
uint8_t WaspXBeeZB::sendXBeePriv(struct packetXBee* packet)
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
    
    // Create the XBee frame
    TX[0]=0x7E;
    TX[1]=0x00;
    
    // set frame ID as 0x01, so response message will be sent
    TX[4]=0x01;
    
    it=0;
    error_AT=2;      

    if( (packet->mode==BROADCAST) || (packet->mode==UNICAST) )
    {
		// fragment length
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
			
			// set reserved bytes
            TX[13]=0xFF;
            TX[14]=0xFE;
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
            
            // set destination network address if known
            if (packet->MY_known==1) 
            {
				TX[13]=packet->naD[0];
                TX[14]=packet->naD[1];    
            }
            else
            {
                TX[13]=0xFF;
                TX[14]=0xFE;
            }
        }

		// set broadcast radius as 0x00, so it will be set to 
		// the maximum hops value (NH command)
        TX[15]=0x00;
        
        // set Options depending on the selected option 
        if( apsEncryption) TX[16]=0x20;
        else TX[16]=0x00;
        
        it=0;
        
		// generate RF Data payload which is composed by [Api header]+[Data]
		genDataPayload(packet,TX,17);
        
        // set checksum
        TX[packet->data_length+17]=getChecksum(TX);
    }
    else // CLUSTER Type
    {
		// fragment length
        TX[2]=20+packet->data_length; 
        
        // set frame Type
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
        
        // set destination network address if known
        if (packet->MY_known==1) 
        {
			TX[13]=packet->naD[0];
            TX[14]=packet->naD[1];
        }
        else
        {
            TX[13]=0xFF;
            TX[14]=0xFE;
        }
        TX[15]=packet->SD;
        TX[16]=packet->DE;
        TX[17]=packet->CID[0];
        TX[18]=packet->CID[1];     
        TX[19]=packet->PID[0];
        TX[20]=packet->PID[1]; 
         
        // set broadcast radius as 0x00, so it will be set to 
		// the maximum hops value (NH command)   
        TX[21]=0x00;        
       
		// set Options depending on the selected option 
        if( apsEncryption) TX[22]=0x20;
        else TX[22]=0x00;

        it=0;
        
		// generate RF Data payload which is composed by [Api header]+[Data]
		genDataPayload(packet,TX,23);
        
        // set checksum
        TX[packet->data_length+23]=getChecksum(TX);
         
    }
    
    // Generate the escaped API frame (it is necessary because AP=2)  
    gen_frame_ap2(packet,TX,protegido,tipo);
    
	#if DEBUG_XBEE > 0
	USB.print(F("[debug] TX:"));
    for(uint16_t i = 0; i < (packet->data_length+tipo+protegido) ; i++)
	{
		USB.printHex(TX[i]);
	}
	USB.println();
	#endif
    
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
	error_TX = txZBStatusResponse();
	error = error_TX; 
	
    packet->deliv_status=delivery_status;
    packet->discov_status=discovery_status;
    packet->true_naD[0]=true_naD[0];
    packet->true_naD[1]=true_naD[1];
    packet->retries=retries_sending;
   
    return error;
}


/*
 * setKnownDestination(paq, address) - It sets MY_Known flag to '1' and sets 
 * the destination network address to the packet to be sent.
 * 
 * Parameters:
 * 	paq : This is the packet to be set
 * 	address : pointer to the destination address 
 * 
 * Returns nothing 
 */
void WaspXBeeZB::setKnownDestination(packetXBee* paq, const char* address)
{
	uint8_t i=0;
    char aux[2];
    uint8_t MY_address[2];
		
	// convert from string to hexadecimal
	for(int j=0; j<2; j++)
    {
        aux[i-j*2]=address[i];
        aux[(i-j*2)+1]=address[i+1];
        MY_address[j]=Utils.str2hex(aux);
        i+=2;
    }
    
    setKnownDestination(paq, MY_address);	
}

/*
 * setKnownDestination(paq, address) - It sets MY_Known flag to '1' and sets 
 * the destination network address to the packet to be sent.
 * 
 * Parameters:
 * 	paq : This is the packet to be set
 * 	address : pointer to the destination address 
 * 
 * Returns nothing 
 */
void WaspXBeeZB::setKnownDestination(packetXBee* paq, uint8_t* address)
{	
	// set known MY address flag
	paq->MY_known=1;	

    paq->naD[0]=address[0];
    paq->naD[1]=address[1];	
}




/*
 Function: Set/read if this device is a coordinator (1) or not (0)
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the NJ command
 Parameters:
   input: if this device is a coordinator (1) or not (0)
*/
uint8_t WaspXBeeZB::setCoordinator(uint8_t input)
{
    int8_t error = 2;        
    error_AT = 2;    
    char buffer[20];
    
    // set_coordinator_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[30])));
    
    gen_data(buffer,input);
    gen_checksum(buffer);
    error = gen_send(buffer);
    
    if (error == 0)
    {
        coordinatorEnable = input;
    }
    return error;
}



/*
 Function: Read the time that a Coordinator/Router allows nodes to join
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the NJ command. Stores in global "joinTime" variable the time allowing join
*/
uint8_t WaspXBeeZB::getCoordinator()
{
    int8_t error = 2;        
    error_AT = 2;    
    char buffer[20];
    
    // get_coordinator_ZB
    strcpy_P(buffer, (char*)pgm_read_word(&(table_ZB[31])));
    
    gen_data(buffer);
    error = gen_send(buffer);
    
    if (error == 0)
    {
        coordinatorEnable = data[0];
    }
    return error;
}


WaspXBeeZB	xbeeZB = WaspXBeeZB();
