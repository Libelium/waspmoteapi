/*! \file 	WaspLoRaWAN.h
    \brief 	Library for managing the LoRaWAN module

    Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		4.0
    Design:		David Gascón
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
	LORAWAN_NOT_JOINED = 6,
	LORAWAN_INPUT_ERROR = 7,
	LORAWAN_VERSION_ERROR = 8
};

/*! @enum ModuleTypesLoRaWAN
 * API module types
 */
enum ModuleTypesLoRaWAN
{
	RN2483_MODULE = 1,		//	EU
	RN2903_MODULE = 2,		//	US or AU
	RN2903_IN_MODULE = 3,	//	IN
	RN2903_AS_MODULE = 4,	//	AS
	ABZ_MODULE = 5,	//	JP/KR
};

/*! @enum ABZModuleBands
 * API ABZ bands
 */
enum ABZModuleBands
{
	BAND_JP923 = 0,	//	JP/KR
	BAND_KR920 = 6,	//	KR
};

/******************************************************************************
 * Class
 ******************************************************************************/
class WaspLoRaWAN : public WaspUART
{
	// private methods //////////////////////////
	private:
		#define RADIO_LORAWAN_UART_SIZE 300
		uint8_t class_buffer[RADIO_LORAWAN_UART_SIZE];

		char _command[250];

	// public methods //////////////////////////
    public:

		bool _adr;
		bool _ar;
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
		uint32_t _freq[72];
		uint32_t _radioFreq;
		uint32_t _radioFreqDev;
		uint16_t _preambleLength;
		uint16_t _dCycle[16];
		uint8_t _drrMin[72];
		uint8_t _drrMax[72];
		uint8_t _dCyclePS;
		char _radioMode[5];
		bool _crcStatus;
		uint8_t _powerIndex;
		uint8_t _dataRate;
		int8_t _radioPower;
		char _radioSF[5];
		float _radioRxBW;
		uint32_t _radioBitRate;
		char _radioCR[4];
		uint32_t _radioWDT;
		uint16_t _radioBW;
		int8_t _radioSNR;
		bool _status[72];
		uint16_t _supplyPower;
		uint32_t _upCounter;
		uint32_t _downCounter;
		uint8_t _port;
		char _data[101];
		bool _dataReceived;
		uint8_t _rx2DataRate;
		uint32_t _rx2Frequency;
		uint16_t _rx1Delay;
		uint16_t _rx2Delay;
		uint8_t _version;
		uint32_t _macStatus;
		uint8_t _maxPayload;
		uint8_t _syncWord = 0;
		int8_t _radioRSSI;

		uint8_t _OTAAError;

		uint8_t _dFormat;
		uint8_t _bandABZ;
		uint8_t _dutyCycle;
		uint16_t _cst;
		int _rssith;

		// constructor
		WaspLoRaWAN()
		{
			// assign class pointer to UART buffer
			_buffer = class_buffer;
			_bufferSize = RADIO_LORAWAN_UART_SIZE;
			_OTAAError=1;
			_bandABZ = 0;
			_upCounter = 0;
			_downCounter = 0;

			// initialize _drrMin and _drrMax
			for (uint8_t i=0;i<72;i++)
			{
				_drrMin[i] = 0;
				_drrMax[i] = 5;
			}
		};

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
		uint8_t setEUI(char* eui);
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
		uint8_t setRX2Parameters(uint8_t datarate, uint32_t frequency);
		uint8_t setRX1Delay(uint16_t delay);
		uint8_t getMACStatus();
		uint8_t showMACStatus();
		uint8_t setSyncWord(uint8_t sync);
		uint8_t getSyncWord();
		// Radio functions
		uint8_t sendRadio(char * message);
		uint8_t sendRadio(uint8_t * payload,uint16_t length);
		uint8_t receiveRadio(uint32_t timeout);
		uint8_t test_ON();
		uint8_t test_OFF();
		uint8_t getRadioSNR();
		uint8_t setRadioSF(char* sprfact);
		uint8_t getRadioSF();
		uint8_t setRadioPower(int8_t pwr);
		uint8_t getRadioPower();
		uint8_t setRadioFreq(uint32_t freq);
		uint8_t getRadioFreq();
		uint8_t setRadioMode(char* mode);
		uint8_t getRadioMode();
		uint8_t setRadioReceivingBW(float bandwidth);
		uint8_t getRadioReceivingBW();
		uint8_t setRadioBitRateFSK(uint32_t bitrate);
		uint8_t getRadioBitRateFSK();
		uint8_t setRadioFreqDeviation(uint32_t freqdeviation);
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
		uint8_t getRadioRSSI();
		uint8_t setLinkCheck(uint16_t counter);
		void convertString(char* string2convert, char* outputString);
		void convertString(uint8_t* string2convert, char* outputString);
		uint8_t sendConfirmed(uint8_t port, uint8_t* payload, uint16_t length);
		uint8_t sendUnconfirmed(uint8_t port, uint8_t* payload, uint16_t length);
		uint8_t sleep();
		uint8_t sleep(uint32_t time);
		uint8_t wakeUp();
		uint8_t setAR(char* state);
		uint8_t getAR();
		uint8_t getRX1Delay();
		uint8_t getRX2Delay();
		uint8_t getRX2Parameters(char* band);
		uint8_t getRX2Parameters();
		uint8_t getMaxPayload();
		void showFirmwareVersion();
		uint8_t setBatteryLevel();
		uint8_t setBatteryLevel(uint8_t bat);
		void showChannelStatus();
		void showChannelStatus(uint8_t channel);

		// ABZ murata module functions
		uint8_t setDataFormat(uint8_t format);
		uint8_t getDataFormat();
		uint8_t setBand(uint8_t band);
		uint8_t setDutyCycle(uint8_t state);
		uint8_t getDutyCycle();
		uint8_t setCST(uint16_t cst);
		uint8_t getCST();
		uint8_t setThresholdRSSI(int rssi);
		uint8_t getThresholdRSSI();

	private:
		// Utils
		uint32_t parseValue(uint8_t base);
		uint32_t parseIntValue();
		float parseFloatValue();


};

extern WaspLoRaWAN LoRaWAN;
#endif
