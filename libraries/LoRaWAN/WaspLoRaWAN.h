/*! \file 	WaspLoRaWAN.h
    \brief 	Library for managing the LoRaWAN module
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
  
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
    Version:		0.2
    Design:			David Gascón
    Implementation:	Luis Miguel Martí

*/

#ifndef LoRaWAN_h
#define LoRaWAN_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <WaspUART.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! @enum AnswerTypesLoRaWAN
 * API answer messages
 */
enum AnswerTypesLoRaWAN
{
	LORAWAN_ANSWER_OK = 0,
	LORAWAN_ANSWER_ERROR = 1,
	LORAWAN_NO_ANSWER = 2,
	LORAWAN_INIT_ERROR = 3,
	LORAWAN_LENGTH_ERROR = 4,
	LORAWAN_SENDING_ERROR = 5,
	LORAWAN_NOT_JOINED = 6
};

/******************************************************************************
 * Class
 ******************************************************************************/
class WaspLoRaWAN : public WaspUART
{
	// private methods //////////////////////////
	private:
		char _command[250];
    	
	// public methods //////////////////////////
    public:
    
		bool _adr;
		char _eui[17];
		char _devEUI[17];
		char _appEUI[17];
		char _nwkSKey[33];
		char _appSKey[33];
		char _appKey[33];
		char _devAddr[9];
		char _band[4];
		uint8_t _retries;
		uint8_t _margin;
		uint8_t _gwNumber;
		uint32_t _freq[16];
		uint32_t _radioFreq;
		uint32_t _radioFreqDev;
		uint16_t _preambleLength;
		uint16_t _dCycle[16];
		uint8_t _drrMin[16];
		uint8_t _drrMax[16];
		uint8_t _dCyclePS;
		char _radioMode[5];
		bool _crcStatus;
		uint8_t _powerIndex;
		uint8_t _dataRate;
		uint16_t _radioPower;
		char _radioSF[5];
		float _radioRxBW;
		uint16_t _radioBitRate;
		char _radioCR[4];
		uint32_t _radioWDT;
		uint16_t _radioBW;
		int8_t _radioSNR;
		bool _status[16];
		uint16_t _supplyPower;
		uint32_t _upCounter;
		uint32_t _downCounter;
		uint8_t _port;
		char _data[101];
		bool _dataReceived;
		
		// constructor
		WaspLoRaWAN() {};
		
		// System functions
		uint8_t ON(uint8_t socket);	
		uint8_t OFF(uint8_t socket);
		uint8_t reset();				
		uint8_t factoryReset();		
		uint8_t getEUI();		
		uint8_t getAddr();		
		uint8_t getSupplyPower();
		uint8_t check();
		
		
		// LoRaWAN functions				
		uint8_t resetMacConfig(char* band);
		uint8_t setDeviceEUI();
		uint8_t setDeviceEUI(char* eui);
		uint8_t getDeviceEUI();
		uint8_t setDeviceAddr();
		uint8_t setDeviceAddr(char* addr);
		uint8_t getDeviceAddr();
		uint8_t setNwkSessionKey(char* key);
		uint8_t setAppEUI(char* eui);
		uint8_t getAppEUI();
		uint8_t setAppKey(char* key);
		uint8_t setAppSessionKey(char* key);
		uint8_t setPower(uint8_t index);
		uint8_t getPower();
		uint8_t setDataRate(uint8_t datarate);
		uint8_t getDataRate();
		uint8_t saveConfig();
		uint8_t joinABP();
		uint8_t joinOTAA();
		uint8_t sendConfirmed(uint8_t port, char* payload);
		uint8_t sendUnconfirmed(uint8_t port, char* payload);
		uint8_t setADR(char* state);
		uint8_t getADR();
		uint8_t getDutyCyclePrescaler();
		uint8_t macPause();
		uint8_t macResume();
		uint8_t setChannelFreq(uint8_t channel, uint32_t freq);
		uint8_t getChannelFreq(uint8_t channel);
		uint8_t setChannelDutyCycle(uint8_t channel, uint16_t dcycle);
		uint8_t getChannelDutyCycle(uint8_t channel);
		uint8_t setChannelDRRange(uint8_t channel, uint8_t minDR, uint8_t maxDR);
		uint8_t getChannelDRRange(uint8_t channel);
		uint8_t setChannelStatus(uint8_t channel, char* state);
		uint8_t getChannelStatus(uint8_t channel);
		uint8_t setRetries(uint8_t retries);
		uint8_t getRetries();
		uint8_t getBand();
		uint8_t getMargin();
		uint8_t getGatewayNumber();
		uint8_t setUpCounter(uint32_t counter);
		uint8_t getUpCounter();		
		uint8_t setDownCounter(uint32_t counter);
		uint8_t getDownCounter();
		
		
		// Radio functions
		uint8_t sendRadio(char * buff);
		uint8_t receiveRadio(uint32_t timeout);
		uint8_t test_ON();
		uint8_t test_OFF();
		uint8_t getRadioSNR();
		uint8_t setRadioSF(char* sprfact);
		uint8_t getRadioSF();
		uint8_t setRadioPower(uint8_t pwr);
		uint8_t getRadioPower();
		uint8_t setRadioFreq(uint32_t freq);
		uint8_t getRadioFreq();
		uint8_t setRadioMode(char* mode);
		uint8_t getRadioMode();
		uint8_t setRadioReceivingBW(float bandwidth);
		uint8_t getRadioReceivingBW();
		uint8_t setRadioBitRateFSK(uint16_t bitrate);
		uint8_t getRadioBitRateFSK();
		uint8_t setRadioFreqDeviation(uint16_t freqdeviation);
		uint8_t getRadioFreqDeviation();
		uint8_t setRadioCRC(char* state);
		uint8_t getRadioCRC();
		uint8_t setRadioPreamble(uint16_t length);
		uint8_t getRadioPreamble();
		uint8_t setRadioCR(char* codingrate);
		uint8_t getRadioCR();
		uint8_t setRadioWDT(uint32_t time);
		uint8_t getRadioWDT();
		uint8_t setRadioBW(uint16_t bandwidth);
		uint8_t getRadioBW();
		uint8_t setLinkCheck(uint16_t counter);
		
	private:		
		// Utils
		uint32_t parseValue(uint8_t base);
		uint32_t parseIntValue();		
		float parseFloatValue();
		
		
};

extern WaspLoRaWAN LoRaWAN;
#endif
