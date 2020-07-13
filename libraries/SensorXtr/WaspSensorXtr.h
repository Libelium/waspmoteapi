/*! \file WaspSensorXtr.h
	\brief Library for managing the Xtreme sensor boards

	Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
	http://www.libelium.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 2.1 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.	If not, see <http://www.gnu.org/licenses/>.

	Version:		3.5
	Design:			David Gascón
	Implementation: Victor Boria, Javier Siscart

 */

#ifndef WaspSensorXtr_h
#define WaspSensorXtr_h

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>
#include "./utility/MCP23008.h"
#include "./utility/ADC.h"
#include <BME280.h>
#include <UltrasoundSensor.h>
#include <TSL2561.h>
#include <SDI12.h>
#include <./utility/AqualaboModbusSensors.h>
#include "ModbusMaster.h"
#include <WaspUtils.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * \def DEBUG_XTR
 * \brief Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */

#define DEBUG_XTR			0
#define PRINT_XTR(str)		USB.print(F("[XTR] ")); USB.print(str);
#define PRINTLN_XTR(str)	USB.print(F("[XTR] ")); USB.println(str);

#define SIMULATE_EUREKA				0
#define SIMULATE_WEATHER_STATION	0

//#define MANUFACTURER_TEST

// Generic _socket definitions according to MCP GPIOs
#define XTR_SOCKET_A		7
#define XTR_SOCKET_B		6
#define XTR_SOCKET_C		5
#define XTR_SOCKET_D		4
#define XTR_SOCKET_E		3
#define XTR_SOCKET_F		2

#define MCP_GP1				1		// Unconneted MCP GPIO
#define MCP_GP1				0		// Unconneted MCP GPIO


// PIN Expander definitions
#define EXPAN_ISO_EN 		17 		// ANALOG4 pin used as Digital
#define I2C_SOCKETA_EN		2		// DIGITAL1
#define I2C_SOCKETD_EN		14		// ANALOG1
#define SPI_ISO_EN			3		// DIGITAL0

#define SW_12V				8		// DIGITAL2


// 3V3 power on _sockets
#define _3V3_SOCKETA 		19
#define _3V3_SOCKETB 		18
#define _3V3_SOCKETD 		15
#define _3V3_SOCKETE		5


// SDI-12 mux
#define MUX_A				7		// DIGITAL5
#define MUX_B				9		// DIGITAL4
#define MUX_EN				20 		// ANA6


#define SWITCH_ON 			1
#define SWITCH_OFF 			0

#define ENABLED				1
#define DISABLED 			0


// ADC channel definition.
#define ADC_CH0				0		// 4-20 mA	(B)
#define ADC_CH1				1		// 4-20 mA	(F)
#define ADC_CH2				2		// RAD		(F)
#define ADC_CH3				3		// LEAF		(B)
#define ADC_CH4				4		// RAD		(E)
#define ADC_CH5				5		// DENDRO	(C)

// Dendrometer types supported (value = range in mm)
#define DENDRO_DD			11
#define DENDRO_DF			15
#define DENDRO_DC3			25


// Weather station models
#define WS_GMX100			1
#define WS_GMX101			2
#define WS_GMX200			3
#define WS_GMX240			4
#define WS_GMX300			5
#define WS_GMX301			6
#define WS_GMX400			7
#define WS_GMX500			8
#define WS_GMX501			9
#define WS_GMX531			10
#define WS_GMX541			11
#define WS_GMX550			12
#define WS_GMX551			13
#define WS_GMX600			14

//Parameters
#define PARAMETER_1 	1
#define PARAMETER_2 	2
#define PARAMETER_3		3
#define PARAMETER_4		4
#define TEMPERATURE		5


#define COMPENSATES_1		1
#define COMPENSATES_2		2
#define COMPENSATES_3		3
#define COMPENSATES_TEMP	5


// Supported sensors with Xtreme boards
#define _5TE				1
#define GS3					2
#define VP4					3
#define MPS6				4
#define SO411				5
#define SI411				6
#define _5TM				7
#define SF421				8
#define C4E					9
#define CTZN				10
#define MES5				11
#define OPTOD				12
#define PHEHT				13
#define NTU					14
#define TEROS12				15
#define TEROS11				16
#define SAC					17


#define EUREKA_PH			0
#define EUREKA_ORP			1
#define EUREKA_DPTH			2
#define EUREKA_COND			3
#define EUREKA_HDO			4
#define EUREKA_CHL			5
#define EUREKA_NH4			6
#define EUREKA_NO3			7
#define EUREKA_CL			8


#define C21_LOW_POWER_MODE 0
#define C21_NORMAL_POWER_MODE 1
#define C21_DISTANCE_IN_M 0
#define C21_DISTANCE_IN_FT 1
#define C21_TEMPERATURE_IN_C 0
#define C21_TEMPERATURE_IN_F 1

// EEPROM constants
const uint8_t manufacturer_code_address = 0xFA;
const uint8_t device_code_address = 0xFB;
const uint8_t serial_number_address = 0xFC;
const uint8_t xtr_eeprom_address = 0x51;

/*******************************************************************************
 * Smart Agriculture Xtreme Structs
 ******************************************************************************/
/*!
 * \struct weatherStationVector
 * \brief Struct to store data of the GILL GMX weather stations
 */

struct weatherStationVector
{
	//! Variable: stores measured wind direction in degrees
	uint16_t windDirection;

	//! Variable: stores measured corrected wind direction in degrees
	uint16_t correctedWindDirection;

	//! Variable: stores measured average wind direction in degrees
	uint16_t avgWindDirection;

	//! Variable: stores measured wind speed in m/s
	float windSpeed;

	//! Variable: stores measured average wind speed in m/s
	float avgWindSpeed;

	//! Variable: stores measured average wind gust direction in degrees
	uint16_t avgWindGustDirection;

	//! Variable: stores measured wind gust speed in m/s
	float avgWindGustSpeed;

	//! Variable: stores measured average corrected wind direction in degrees
	uint16_t avgCorrectedWindDirection;

	//! Variable: stores measured wind sensor status
	char windSensorStatus[5];

	//! Variable: stores measured precipitation total in mm
	float precipTotal;

	//! Variable: stores measured precipitation intensity in mm
	float precipIntensity;

	//! Variable: stores measured precipitation status
	uint8_t precipStatus;

	//! Variable: stores measured compass in degrees
	uint16_t compass;

	//! Variable: stores measured x tilt
	float xTilt;

	//! Variable: stores measured y tilt
	float yTilt;

	//! Variable: stores measured z orientation
	float zOrient;

	//! Variable: stores measured timestamp
	char timestamp[22];

	//! Variable: stores measured supply voltage
	float supplyVoltage;

	//! Variable: stores measured status
	char status[5];

	//! Variable: stores measured solar radiation in W/m²
	uint16_t solarRadiation;

	//! Variable: stores measured sunshine hours
	float sunshineHours;

	//! Variable: stores measured sunrise time in h:min
	char sunriseTime[6];

	//! Variable: stores measured solar noon time in h:min
	char solarNoonTime[6];

	//! Variable: stores measured sunset time in h:min
	char sunsetTime[6];

	//! Variable: stores measured position of the sun in degrees:degrees
	char sunPosition[8];

	//! Variable: stores measured twilight civil time in h:min
	char twilightCivil[6];

	//! Variable: stores measured twilight nautical time in h:min
	char twilightNautical[6];

	//! Variable: stores measured twilight astronomical time in h:min
	char twilightAstronom[6];

	//! Variable: stores measured pressure in hPa
	float pressure;

	//! Variable: stores measured pressure at sea level in hPa
	float pressureSeaLevel;

	//! Variable: stores measured pressure at station level in hPa
	float pressureStation;

	//! Variable: stores measured relative humidity in %
	uint16_t relativeHumidity;

	//! Variable: stores measured  temperature in degrees celsius
	float temperature;

	//! Variable: stores measured dew point in degrees celsius
	float dewpoint;

	//! Variable: stores measured absolute humidity in gm-3
	float absoluteHumidity;

	//! Variable: stores measured air density in Kgm-3
	float airDensity;

	//! Variable: stores measured wet bulb temperature in degrees celsius
	float wetBulbTemperature;

	//! Variable: stores measured wind chill in celsius degrees
	float windChill;

	//! Variable: stores measured heat index in celsius degrees
	uint16_t heatIndex;


	#ifdef GMX_GPS_OPTION

		//! Variable: stores measured  gps corrected speed in m/s
		float gpsCorrectedSpeed;

		//! Variable: stores measured  gps average corrected speed in m/s
		float gpsAvgCorrectedSpeed;

		//! Variable: stores measured gps corrected gust speed in m/s
		float gpsCorrectedGustSpeed;

		//! Variable: stores measured gps corrected gust direction in degrees
		uint16_t gpsCorrectedGustDirection;

		//! Variable: stores measured gps location
		char gpsLocation[29];

		//! Variable: stores measured gps heading in degrees
		uint16_t gpsHeading;

		//! Variable: stores measured gps speed in m/s
		float gpsSpeed;

		//! Variable: stores measured gps status
		char gpsStatus[5];

	#endif
};

/*!
 * \struct sensor5TEVector
 * \brief Struct to store data of the 5TE sensor
 */

struct sensor5TEVector
{

	//! Variable: stores measured dielectric permittivity (dimensionless) in float type
	float dielectricPermittivity;

	//! Variable: stores measured electrical conductivity in dS/m in float type
	float electricalConductivity;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};


/*!
 * \struct sensor5TMVector
 * \brief Struct to store data of the 5TM sensor
 */

struct sensor5TMVector
{

	//! Variable: stores measured dielectric permittivity (dimensionless) in float type
	float dielectricPermittivity;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorGS3Vector
 * \brief Struct to store data of the GS3 sensor
 */

struct sensorGS3Vector
{

	//! Variable: stores measured dielectric permittivity (dimensionless) in float type
	float dielectricPermittivity;

	//! Variable: stores measured electrical conductivity in μS/cm in float type
	float electricalConductivity;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorVP4Vector
 * \brief Struct to store data of the VP4 sensor
 */

struct sensorVP4Vector
{
	//! Variable: stores measured Vapor Pressure in kPa in float type
	float vaporPressure;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//! Variable: stores measured Relative Humidity in %RH in float type
	float relativeHumidity;

	//! Variable: stores measured Atmospheric Pressure in kPa in float type
	float atmosphericPressure;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorMPS6Vector
 * \brief Struct to store data of the MPS6 sensor
 */

struct sensorMPS6Vector
{
	//! Variable: stores measured Water Potential in kPa in float type (it's always a negative value)
	float waterPotential;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorSO411Vector
 * \brief Struct to store data of the SO411 sensor
 */

struct sensorSO411Vector
{
	//! Variable: stores measured calibrated oxygen in % in float type
	float calibratedOxygen;

	//! Variable: stores measured sensor body temperature in degrees Celsius in float type
	float bodyTemperature;

	//! Variable: stores measured sensor millivolts in float type
	float milliVolts;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};


/*!
 * \struct sensorSI411Vector
 * \brief Struct to store data of the SI411 sensor
 */

struct sensorSI411Vector
{
	//! Variable: stores measured Target Temperature in degrees Celsius in float type
	float targetTemperature;

	//! Variable: stores measured sensor body temperature in degrees Celsius in float type
	float sensorBodyTemperature;

	//! Variable: stores measured target millivolts in float type
	float targetMilliVolts;

	//Sensor serial number variable
	char sensorSerialNumber[14];

  //! Variable: stores correctedTemperature in degrees Celsius in float type
  float targetTemperatureCorrected;
};


/*!
 * \struct sensorSI4B1Vector
 * \brief Struct to store data of the SI411 sensor
 */

struct sensorSI4B1Vector
{
	//! Variable: stores measured Target Temperature in degrees Celsius in float type
	float targetTemperature;

	//! Variable: stores measured sensor body temperature in degrees Celsius in float type
	float sensorBodyTemperature;

	//! Variable: stores measured target millivolts in float type
	float targetMilliVolts;

	//Sensor serial number variable
	char sensorSerialNumber[14];

  //! Variable: stores correctedTemperature in degrees Celsius in float type
  float targetTemperatureCorrected;
};


/*!
 * \struct sensorSF421Vector
 * \brief Struct to store data of the SF421 sensor
 */

struct sensorSF421Vector
{
	//! Variable: stores measured Bud Temperature in degrees Celsius in float type
	float budTemperature;

	//! Variable: stores measured Leaf Temperature in degrees Celsius in float type
	float leafTemperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorSF421Vector
 * \brief Struct to store data of the SF421 sensor
 */

struct DatasolMETVector
{
	//! Variable: stores measured radiation in W/m2
	uint16_t radiation;

	//! Variable: stores measured semi-cell 1 radiation in W/m2
	uint16_t semicell1Radiation;

	//! Variable: stores measured semi-cell 2 radiation in W/m2
	uint16_t semicell2Radiation;

	//! Variable: stores measured envirnoment temperature in degrees Celsius
	float environmentTemperature;

	//! Variable: stores measured solar panel temperature in degrees Celsius
	float panelTemperature;

	//! Variable: stores measured wind speed in m/s
	float windSpeed;

	//! Variable: stores necessary cleaning notice
	bool necessaryCleaningNotice;

	//! Variable: stores Peak Sun Hours (PSH)
	float peakSunHours;

	//Sensor serial number variable
	char sensorSerialNumber[11];
};

/*!
 * \struct sensorTEROS12Vector
 * \brief Struct to store data of the TEROS12 sensor
 */

struct sensorTEROS12Vector
{

	//! Variable: stores measured dielectric permittivity (dimensionless) in float type
	float calibratedCountsVWC;

	//! Variable: stores measured electrical conductivity in μS/cm in float type
	float electricalConductivity;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};


/*!
 * \struct sensor5TMVector
 * \brief Struct to store data of the 5TM sensor
 */

struct sensorTEROS11Vector
{

  //! Variable: stores measured dielectric permittivity (dimensionless) in float type
  float calibratedCountsVWC;

	//! Variable: stores measured temperature in degrees Celsius in float type
	float temperature;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};




/*!
 * \struct VegaPulsC21Vector
 * \brief Struct to store data of the Vegapuls C 21 sensor
 */

struct VegaPulsC21Vector
{

	//! Variable: stores measured stage in float type
	float stage;

	//! Variable: stores measured distance in float type
	float distance;

	//! Variable: stores measured temperature in float type
	float temperature;

	//! Variable: stores measured status in float type
	float status;

	//! Variable: stores stage reference in float type
	float stageReference;

	//! Variable: stores stage reference in float type
	uint8_t powerOperationMode;

	//! Variable: stores stage reference in float type
	uint8_t distanceUnit;

	//! Variable: stores stage reference in float type
	uint8_t temperatureUnit;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*******************************************************************************
 * Smart Water Xtreme Structs
 ******************************************************************************/


/*!
 * \struct sensorOPTODVector
 * \brief Struct to store data of the OPTOD sensor
 */

struct sensorOPTODVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured oxygen in saturation percentage
	float oxygenSAT;

	//! Variable: stores measured oxygen in mg/L
	float oxygenMGL;

	//! Variable: stores measured oxygen in ppm
	float oxygenPPM;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};




/*!
 * \struct sensorPHEHTVector
 * \brief Struct to store data of the PHEHT sensor
 */

struct sensorPHEHTVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured pH
	float pH;

	//! Variable: stores measured redox in mV
	float redox;

	//! Variable: stores measured pH in mV
	float pHMV;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};


/*!
 * \struct sensorPHEHTVector
 * \brief Struct to store data of the PHEHT sensor
 */

struct sensorSACVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured sac
	float sac;

	//! Variable: stores measured cod in mV
	float cod;

	//! Variable: stores measured pH in mV
	float bod;
	
	//! Variable: stores measured cod in mV
	float cot;

	//! Variable: stores measured pH in mV
	float uvComp;
	
	//! Variable: stores measured cod in mV
	float grComp;

	//! Variable: stores measured pH in mV
	float uvTran;
	
	//! Variable: stores measured cod in mV
	float grTran;

	//! Variable: stores measured pH in mV
	float turb;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};

/*!
 * \struct sensorC4EVector
 * \brief Struct to store data of the C4E sensor
 */

struct sensorC4EVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured conductivity in μS/cm
	float conductivity;

	//! Variable: stores measured salinity in ppt
	float salinity;

	//! Variable: stores measured total dissolved solids in ppm
	float totalDissolvedSolids;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};




/*!
 * \struct sensorNTUVector
 * \brief Struct to store data of the NTU sensor
 */

struct sensorNTUVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured turbidity in NTU
	float turbidityNTU;

	//! Variable: stores measured turbidity in mg/l
	float turbidityMGL;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};





/*!
 * \struct sensorCTZNVector
 * \brief Struct to store data of the CTZN sensor
 */

struct sensorCTZNVector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured conductivity in mS/cm
	float conductivity;

	//! Variable: stores measured salinity in ppt
	float salinity;

	//! Variable: stores measured conductivity not compensated with temperature in mS/cm
	float conductivityNotCompensated;

	//Sensor serial number variable
	char sensorSerialNumber[14];
 };



/*!
 * \struct sensorMES5Vector
 * \brief Struct to store data of the MES5 sensor
 */

struct sensorMES5Vector
{
	//! Variable: stores measured temperature in Celsius degrees
	float temperature;

	//! Variable: stores measured sludge blanket in %
	float sludgeBlanket;

	//! Variable: stores measured supended solids in g/L
	float suspendedSolids;

	//! Variable: stores measured turbidity in FAU
	float turbidityFAU;

	//Sensor serial number variable
	char sensorSerialNumber[14];
};


/*!
 * \struct sensorEurekaVector
 * \brief Struct to store data of the Eureka sensor
 */
struct sensorEurekaVector
{
	// sensor variables
	float ph;
	float orp;
	float depth;
	float spCond;
	float chl;
	float nh4;
	float no3;
	float cl;
	float hdo;
	float temperature;
	char ME_date[10];
	char ME_time[10];

	char pressure[10];

	char model[20];

	char version[7];

	//Sensor serial number variable
	char sensorSerialNumber[9];


};


/*******************************************************************************
 * Smart Agriculture Xtreme Classes
 ******************************************************************************/

/*!
 * \class WaspSensorXtr
 * \brief class for Xtreme boards
 */
class WaspSensorXtr
{
	public:
		//! Constructor
		WaspSensorXtr();

		/*
		* Bit:		| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
		* _socket: 	| A | B | C | D | E | F | - | - |
		*/
		uint8_t socketRegister;					//variable to store information about _sockets used by sensors
		uint8_t stateRegister12v;				//variable to store information about _sockets with 12v enabled
		bool redefinedSocket;					//flag to detect redefinitions of _socket by more than one sensor
		bool bmeIsolatorEnabledSocketA;			//flag to detect two bme sensors connected at the same time to i2c
		bool bmeIsolatorEnabledSocketD;			//flag to detect two bme sensors connected at the same time to i2c
		bool luxesIsolatorEnabledSocketA;		//flag to detect two luxes sensors connected at the same time to i2c
		bool luxesIsolatorEnabledSocketD;		//flag to detect two luxes sensors connected at the same time to i2c
		bool ultrasoundIsolatorEnabledSocketA;	//flag to detect two ultrasound sensors connected at the same time to i2c
		bool ultrasoundIsolatorEnabledSocketD;	//flag to detect two ultrasound sensors connected at the same time to i2c
		uint32_t readBoardSerialNumber();
		uint8_t writeEEPROM(uint8_t address, uint8_t value);
		int8_t readEEPROM(uint8_t address);
		uint8_t boardSerialNumber[4];			//Serial number in Xtreme board

	 	void ON();
	 	void ON(uint8_t power);
	 	void OFF();
	 	void set3v3(uint8_t _socket, uint8_t _state);
	 	void set12v(uint8_t _socket, uint8_t _state);
	 	void setMux(uint8_t _socket, uint8_t _state);

	private:


};

extern WaspSensorXtr SensorXtr;


/*!
 * \class Decagon_5TE
 * \brief class for 5TE sensor
 */
class Decagon_5TE
{
	public:
		// constructor
		Decagon_5TE(uint8_t _socket);

		sensor5TEVector sensor5TE;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Decagon_5TM
 * \brief class for 5TM sensor
 */
class Decagon_5TM
{
	public:
		// constructor
		Decagon_5TM(uint8_t _socket);

		sensor5TMVector sensor5TM;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class Decagon_GS3
 * \brief class for GS3 sensor
 */
class Decagon_GS3
{
	public:
		// constructor
		Decagon_GS3(uint8_t _socket);

		sensorGS3Vector sensorGS3;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class Decagon_VP4
 * \brief class for VP4 sensor
 */
class Decagon_VP4
{
	public:
		// constructor
		Decagon_VP4(uint8_t _socket);

		sensorVP4Vector sensorVP4;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class Decagon_MPS6
 * \brief class for MPS6 sensor
 */
class Decagon_MPS6
{
	public:
		// constructor
		Decagon_MPS6(uint8_t _socket);

		sensorMPS6Vector sensorMPS6;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Apogee_SO411
 * \brief class for SO411 sensor
 */
class Apogee_SO411
{
	public:
		// constructor
		Apogee_SO411(uint8_t _socket);

		sensorSO411Vector sensorSO411;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class Apogee_SI411
 * \brief class for SI411 sensor
 */
class Apogee_SI411
{
	public:
		// constructor
		Apogee_SI411(uint8_t _socket);

		sensorSI411Vector sensorSI411;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Apogee_SI4B1
 * \brief class for SI4B1 sensor
 */
class Apogee_SI4B1
{
	public:
		// constructor
		Apogee_SI4B1(uint8_t _socket);

		sensorSI4B1Vector sensorSI4B1;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		uint8_t readFast();
    	float emissivityCorrection(float targetTemp, float sensorBodyTemp);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class Apogee_SF421
 * \brief class for SI421 sensor
 */
class Apogee_SF421
{
	public:
		// constructor
		Apogee_SF421(uint8_t _socket);

		sensorSF421Vector sensorSF421;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};

/*!
 * \class leafWetness
 * \brief class for Leaf Wetness sensor
 */
class leafWetness
{
	public:
		//! Constructor
		leafWetness();

		//! Variable: stores measured leaf wetness in Volts in float type
		float wetness;

		void ON();
		void OFF();
		uint8_t read();

	private:
		uint8_t socket;
};


/*!
 * \class dendrometer
 * \brief class for Dendrometer sensors
 */

class dendrometer
{
	public:
		//! Constructors
		dendrometer();
		dendrometer(uint8_t type);

		//! Variable: stores measured diameter in mm in float type
		float diameter;
		//! Variable: stores measured dendrometer reference in mm in float type
		float dendroRef;
		//! Variable: stores measured dendrometer growth in mm in float type
		float dendroGrowth;

		void ON();
		void OFF();
		float read();
		uint8_t setReference(void);
		float readGrowth(void);

	private:
		uint8_t socket;
		uint8_t dendroType;
};


/*!
 * \class weatherStation
 * \brief class for Gill GMX Weather Stations
 */

class weatherStation
{
	public:
		//! Constructor
		weatherStation();

		weatherStationVector gmx;

		void ON();
		void OFF();
		void GPS(uint8_t option);
		uint8_t read();
		uint8_t sendCommand(char* str);

		//Variable to store the station model
		//0 -> Station not recognized
		//1 -> GMX100
		//2 -> GMX240
		uint8_t stationModel = 0;
		uint8_t gps = 0;

	private:
		uint8_t socket;
};


/*!
 * \class Apogee_SU100
 * \brief class for SU100 sensor
 */
class Apogee_SU100
{
	public:
		//! Constructor
		Apogee_SU100(uint8_t _socket);

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();

	private:
		uint8_t socket;
};


/*!
 * \class Apogee_SU202
 * \brief class for SU202 sensor
 */
class Apogee_SU202
{
	public:
		//! Constructor
		Apogee_SU202(uint8_t _socket);

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();

	private:
		uint8_t socket;
};

/*!
 * \class Apogee_SQ110
 * \brief class for SQ110 sensor
 */
class Apogee_SQ110
{
	public:
		//! Constructor
		Apogee_SQ110(uint8_t _socket);

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();

	private:
		uint8_t socket;
};

/*!
 * \class Apogee_SP510
 * \brief class for SP510 sensor
 */
class Apogee_SP510
{
	public:
		//! Constructor
		Apogee_SP510(uint8_t _socket);

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();
		void heater(uint8_t state);

	private:
		uint8_t socket;
};


/*!
 * \class Datasol_MET
 * \brief class for ATERSA Datasol MET sensor
 */
class DatasolMET
{
	public:
		// constructor
		DatasolMET();

		DatasolMETVector sensorDatasolMET;

		void ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

		// For Mdobus management
		ModbusMaster datasolMetModbus;

	private:
		uint8_t sensorAddr; //!< Sensor address
		uint8_t socket;
		void initCommunication();
		void clearBuffer();

		union
		{
			uint16_t uint16t[2];
			uint32_t uint32t;
		}
		conversion;
};

/*!
 * \class Meter_TEROS12
 * \brief class for TEROS12 sensor
 */
class Meter_TEROS12
{
	public:
		// constructor
		Meter_TEROS12(uint8_t _socket);

		sensorTEROS12Vector sensorTEROS12;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Meter_TEROS11
 * \brief class for TEROS11 sensor
 */
class Meter_TEROS11
{
	public:
		// constructor
		Meter_TEROS11(uint8_t _socket);

		sensorTEROS11Vector sensorTEROS11;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};



/*!
 * \class VegaPuls_C21
 * \brief class for Vegapuls C 21 sensor
 */
class VegaPuls_C21
{
	public:
		// constructor
		VegaPuls_C21(uint8_t _socket);

		VegaPulsC21Vector VegaPulsC21;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		uint8_t readStageReference();
		uint8_t writeStageReference(char* _stageReference);

		uint8_t readPowerOperationMode();
		uint8_t writePowerOperationMode(uint8_t _pom);
		uint8_t readDistanceUnit();
		uint8_t writeDistanceUnit(uint8_t _distanceUnit);
		uint8_t readTemperatureUnit();
		uint8_t writeTemperatureUnit(uint8_t _temperatureUnit);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*******************************************************************************
 * Smart Water Xtreme Classes
 ******************************************************************************/

/*!
 * \class AqualaboWaterXtr
 * \brief class for Aqualabo sensors in Water Xtreme board
 */
class AqualaboWaterXtr
{
	public:
		//! Constructor
		AqualaboWaterXtr();

		//Modbus
		uint8_t init();
		uint8_t init(uint8_t range);
		uint8_t init(uint8_t range, uint8_t avg);
		uint8_t calibrate(uint8_t sensor, uint8_t parameter, uint8_t step, float value);
		void fillOperatorsName(char* name);
		void fillCalibrationDate(char* date);
		uint8_t restoreToFactoryCalibration(uint8_t parameter);
		uint8_t resetTemporaryCalibrationData(uint8_t returnAvgTo1);
		uint8_t searchAddress(uint8_t _sensorAddr);
		uint8_t changeAddress(uint8_t _sensorAddr);

		//Menu assisted calibration functions
		void exitCalibration();
		void exitCalibrationAndStopElectronicZero();
		void printLine();
		void printBigLine();
		uint8_t getData(char* input, uint8_t inputLength);
		boolean getDate(char* input, uint8_t inputLength, int numBytes);
		void serialClean();
		bool find( uint8_t* buffer, uint16_t length, char* pattern);

		//Parameter compensation with external values
		uint8_t enableCompensation(uint8_t compensatedParam, uint8_t extParamWithWhichCompensate, uint8_t enablingState);
		uint8_t setCompensationValue(uint8_t extParamWithWhichCompensate, float value);

	protected:
		//Parameter compensation with external values
		uint8_t compensationTemp = 0x80;
		uint8_t compensation1 = 0x80;
		uint8_t compensation2 = 0x80;
		uint8_t saveCompensationValue(uint8_t paramNumber, uint8_t _compensationTemp, uint8_t _compensation1, uint8_t _compensation2);
};


/*!
 * \class Aqualabo OPTOD
 * \brief class for OPTOD sensor
 */
class Aqualabo_OPTOD: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_OPTOD(uint8_t _socket);

		sensorOPTODVector sensorOPTOD;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};




/*!
 * \class Aqualabo PHEHT
 * \brief class for PHEHT sensor
 */
class Aqualabo_PHEHT: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_PHEHT(uint8_t _socket);

		sensorPHEHTVector sensorPHEHT;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Aqualabo PHEHT
 * \brief class for PHEHT sensor
 */
class Aqualabo_SAC: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_SAC(uint8_t _socket);

		sensorSACVector sensorSAC;
		uint8_t socket;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		
};



/*!
 * \class Aqualabo C4E
 * \brief class for C4E sensor
 */
class Aqualabo_C4E: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_C4E(uint8_t _socket);

		sensorC4EVector sensorC4E;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};



/*!
 * \class Aqualabo NTU
 * \brief class for NTU sensor
 */
class Aqualabo_NTU: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_NTU(uint8_t _socket);

		sensorNTUVector sensorNTU;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;

};


/*!
 * \class Aqualabo CTZN
 * \brief class for CTZN sensor
 */
class Aqualabo_CTZN: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_CTZN(uint8_t _socket);

		sensorCTZNVector sensorCTZN;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Aqualabo MES5
 * \brief class for MES5 sensor
 */
class Aqualabo_MES5: public AqualaboWaterXtr
{
	public:
		// constructor
		Aqualabo_MES5(uint8_t _socket);

		sensorMES5Vector sensorMES5;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t readSerialNumber();
		void calibrationProcess(uint8_t parameter);

	private:
		WaspSDI12 sdi12Sensor = WaspSDI12(ANA2);
		uint8_t socket;
};


/*!
 * \class Eureka_Manta
 * \brief class for Eureka Manta 2
 */
class Eureka_Manta
{
	public:
		// constructor
		Eureka_Manta();

		sensorEurekaVector sensorEureka;

		uint8_t ON();
		void OFF();
		uint8_t read();
		uint8_t sendCommand(char* str);
		void configureSensor();
		uint8_t saveConfig();
		uint8_t getBarometricPressure();
		uint8_t setBarometricPressure(float pressure);


	private:
		uint8_t socket;


};


/*!
 * \class bme
 * \brief class to manage BME280 sensor
 */
class bme
{
	public:
		//! Constructor
		bme(uint8_t _socket);

		uint8_t ON();
		void OFF();
		float getTemperature();
		float getHumidity();
		float getPressure();

	private:
		uint8_t socket;
};

/*!
 * \class ultrasound
 * \brief class to manage ultrasound sensor
 */
class ultrasound
{
	public:
		//! Constructor
		ultrasound(uint8_t _socket);

		uint8_t ON();
		void OFF();
		uint16_t getDistance();

	private:
		uint8_t socket;
};

/*!
 * \class luxes
 * \brief class to manage luxes sensor
 */
class luxes
{
	public:
		//! Constructor
		luxes(uint8_t _socket);

		uint8_t ON();
		void OFF();
		uint32_t getLuminosity();

	private:
		uint8_t socket;
};

/*!
 * \class _4_20mA
 * \brief class to manage 4-20mA sensor
 */
class _4_20mA
{
	public:
		//! Constructor
		_4_20mA(uint8_t _socket);



		//! Variable: stores measured current in float type
		float current;

		uint8_t ON();
		void OFF();
		float read();

	private:
		uint8_t socket;
};


/*!
 * \class LED
 * \brief class for LED
 */
class LED
{
	public:
		// constructor
		LED(uint8_t _socket);

		//! LED Color definition
		enum ledColourEnum
		{
			GREEN		= 0,
			RED			= 1,
			YELLOW		= 2,
			OFF			= 3,
		};

		void setIndicator(uint8_t colour);
		void unsetIndicator();

		uint8_t ledState;

	private:
		uint8_t socket;
};


/*!
 * \class buzzer
 * \brief class for buzzer
 */
class buzzer
{
	public:
		// constructor
		buzzer(uint8_t _socket);

    //! Buzzer  definition
		enum buzzerEnum
		{
			OFF		= 0,
			ON		= 1,
		};

		void setBuzzer();
		void unsetBuzzer();
    void positiveBeep();
    void negativeBeep();

		uint8_t buzzerState;

	private:
		uint8_t socket;
};

/*******************************************************************************
 * Example for Modbus sensor Class
 ******************************************************************************/

class exampleModbusSensor
{
	public:
		// constructor
		exampleModbusSensor(uint8_t _sensorAddr);

		uint8_t ON();
		void OFF();
		uint8_t read(uint16_t _registerAddr, uint8_t _numOfRegisters);

		uint8_t sensorAddr;

		uint32_t value;

		// For Modbus management
		ModbusMaster modbusMasterSensor;

	private:
		void initCommunication();
		void clearBuffer();
		uint8_t socket;

		union
		{
			uint16_t uint16t[2];
			uint32_t uint32t;
		}
		conversion;
};


#endif
