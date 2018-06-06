/*! \file WaspSensorAgrXtr.h
    \brief Library for managing the Smart Agriculture Extreme sensor board

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		3.0
    Design:			David Gascón
    Implementation: Javier Siscart, Víctor Boria

 */

#ifndef WaspSensorAgrXtr_h
#define WaspSensorAgrXtr_h

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>
#include "./utility/MCP23008.h"
#include "./utility/ADC.h"
#include <./utility/SDI12.h>
#include <BME280.h>
#include <UltrasoundSensor.h>
#include <TSL2561.h>


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * \def DEBUG_AGR_XTR
 * \brief Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */

#define DEBUG_AGR_XTR 		0
#define PRINT_AGR_XTR(str)		USB.print(F("[AGR_XTR] ")); USB.print(str);
#define PRINTLN_AGR_XTR(str)	USB.print(F("[AGR_XTR] ")); USB.println(str);

// Generic socket definitions according to MCP GPIOs
#define AGR_XTR_SOCKET_A	7
#define AGR_XTR_SOCKET_B	6
#define AGR_XTR_SOCKET_C	5
#define AGR_XTR_SOCKET_D	4
#define AGR_XTR_SOCKET_E	3
#define AGR_XTR_SOCKET_F	2

#define MCP_GP1				1			// Unconneted MCP GPIO
#define MCP_GP1				0			// Unconneted MCP GPIO


// PIN  Expander definitions
#define EXPAN_ISO_EN 		17 			// ANALOG4 pin used as Digital
#define I2C_SOCKETA_EN		2			// DIGITAL1
#define I2C_SOCKETD_EN		14			// ANALOG1
#define SPI_ISO_EN			3			// DIGITAL0

#define SW_12V				8  			// DIGITAL2
#define _12V_ON 			1
#define _12V_OFF 			0

// 3V3 power on sockets
#define _3V3_SOCKETA 		19
#define _3V3_SOCKETB 		18
#define _3V3_SOCKETD 		15
#define _3V3_SOCKETE		5

#define _3V3_ON 			1
#define _3V3_OFF 			0

// SDI-12 mux
#define MUX_A				7		// DIGITAL5
#define MUX_B				9		// DIGITAL4
#define MUX_EN				20 		// ANA6


// Supported SDI-12 sensors 
#define _5TE				1
#define GS3					2
#define VP4					3
#define MPS6				4
#define SO411				5
#define SI411				6
#define _5TM				7
#define SF421				8


// ADC channel definition. 
#define ADC_CH0				0		// 4-20 mA (B)
#define ADC_CH1				1		// 4-20 mA (F)
#define ADC_CH2				2		// RAD     (F)
#define ADC_CH3				3		// LEAF    (B)
#define ADC_CH4				4		// RAD     (E)
#define ADC_CH5				5		// DENDRO  (C)

// Dendrometer types supported (value = range in mm)
#define DENDRO_DD			11
#define DENDRO_DF			15
#define DENDRO_DC3			25



/*******************************************************************************
 * Structs
 ******************************************************************************/
/*!
 * \struct weatherStationVector
 * \brief Struct to store data of the weather station GILL GMX-240
 */

struct weatherStationVector
{
	//! Variable: stores the node letter identification in a char type
	char node_letter;
	
	//! Variable: stores measured wind direction in degrees in uint16_t type
	uint16_t wind_direction;
	
	//! Variable: stores measured corrected wind direction in degrees in uint16_t type
	uint16_t corrected_wind_direction;
	
	//! Variable: stores measured average wind direction in degrees in uint16_t type
	uint16_t average_wind_direction;
	
	//! Variable: stores measured wind speed in m/s in a string type
	char wind_speed[7];
	
	//! Variable: stores measured average wind speed in m/s in a string type
	char average_wind_speed[7];
	
	//! Variable: stores measured average wind gust direction in degrees in uint16_t type
	uint16_t average_wind_gust_direction;
	
	//! Variable: stores measured wind gust speed in m/s in a string type
	char average_wind_gust_speed[7];
	
	//! Variable: stores measured average corrected wind direction in degrees in uint16_t type
	uint16_t average_corrected_wind_direction;
	
	//! Variable: stores measured wind sensor status in a string type
	char wind_sensor_status[5];
	
	//! Variable: stores measured precipitation total in mm in a string type
	char precipitation_total[10];
	
	//! Variable: stores measured precipitation intensity in mm in a string type
	char precipitation_intensity[8];
	
	//! Variable: stores measured precipitation status in a string type
	char precipitation_status;
	
	//! Variable: stores measured compass in degrees in uint16_t type
	uint16_t compass;
	
	//! Variable: stores measured x tilt in a string type
	char x_tilt[4];
	
	//! Variable: stores measured y tilt in a string type
	char y_tilt[4];
	
	//! Variable: stores measured z orientation in a string type
	char z_orient[3];
	
	//! Variable: stores measured timestamp in a string type
	char timestamp[22];
	
	//! Variable: stores measured supply voltage in a string type
	char supply_voltage[5];
	
	//! Variable: stores measured status in a string type
	char status[5];
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

};




/*******************************************************************************
 * Constants
 ******************************************************************************/




/*******************************************************************************
 * Class
 ******************************************************************************/

/*!
 * \class WaspSensorAgrXtr
 * \brief class for Smart Agriculture Extreme
 */
class WaspSensorAgrXtr
{
 	public:
	 
	 	//! Constructor
	 	WaspSensorAgrXtr();
	 	
	 	uint8_t socketRegister;					//variable to store information about sockets used by sensors
	 	uint8_t _12vStateRegister;				//variable to store information about sockets with 12v enabled
	 	bool redefinedSocket;					//flag to detect redefinitions of socket by more than one sensor
		bool bmeIsolatorEnabledSocketA;			//flag to detect two bme sensores connected at the same time to i2c
		bool bmeIsolatorEnabledSocketD;			//flag to detect two bme sensores connected at the same time to i2c
		bool luxesIsolatorEnabledSocketA;		//flag to detect two bme sensores connected at the same time to i2c
		bool luxesIsolatorEnabledSocketD;		//flag to detect two bme sensores connected at the same time to i2c
		bool ultrasoundIsolatorEnabledSocketA;	//flag to detect two bme sensores connected at the same time to i2c
		bool ultrasoundIsolatorEnabledSocketD;	//flag to detect two bme sensores connected at the same time to i2c
		
 	private:
	 
	 	MCP23008 mcp;		// object to manage internal circuitry

 	protected:
	 
	 	WaspSDI12 sdi12;	// object to manage SDI12 communications
	 	LTC ltc;			// object to manage ADC
	 	
		/* 
		 * Bit:    | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
		 * Socket: | A | B | C | D | E | F | - | - |
		 */

	 	// variables to store information as bus address, model, etc.
	 	char address;
	 	char command[6];
	 	char model[18];
	 	char numberOfMeasures;
	 	char timeToNextMeasure[4];
		char measures[30];
	 	uint8_t _socket;
	 
	 	void ON();
	 	void ON(uint8_t power);
	 	void OFF();
	 	void set3v3(uint8_t socket, uint8_t state);
	 	void set12v(uint8_t state);
	 	void setMux();
	 	
	 	// SDI-12 functions
	 	uint8_t isSensor(uint8_t sensorName);
	 	uint8_t startSensor();
	 	uint8_t read(uint8_t sensorType);
		

};

extern WaspSensorAgrXtr AgricultureXtr;


/*!
 * \class Decagon_5TE
 * \brief class inherited from WaspSensorAgrXtr for 5TE sensor
 */
class Decagon_5TE: public WaspSensorAgrXtr
{
	public:

		Decagon_5TE(uint8_t socket);	// constructor
		sensor5TEVector sensor5TE;

		uint8_t ON();
		void OFF();
		uint8_t read();
	
	private:
		
		typedef WaspSensorAgrXtr super;
		uint8_t parse5TE();
	
};


/*!
 * \class Decagon_5TM
 * \brief class inherited from WaspSensorAgrXtr for 5TM sensor
 */
class Decagon_5TM: public WaspSensorAgrXtr
{
	public:

		Decagon_5TM(uint8_t socket);	// constructor
		sensor5TMVector sensor5TM;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parse5TM();
};

/*!
 * \class Decagon_GS3
 * \brief class inherited from WaspSensorAgrXtr for GS3 sensor
 */
class Decagon_GS3: public WaspSensorAgrXtr
{
	public:

		Decagon_GS3(uint8_t socket);	// constructor
		sensorGS3Vector sensorGS3;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseGS3();
};

/*!
 * \class Decagon_VP4
 * \brief class inherited from WaspSensorAgrXtr for VP4 sensor
 */
class Decagon_VP4: public WaspSensorAgrXtr
{
	public:

		Decagon_VP4(uint8_t socket);	// constructor
		sensorVP4Vector sensorVP4;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseVP4();
};

/*!
 * \class Decagon_MPS6
 * \brief class inherited from WaspSensorAgrXtr for MPS6 sensor
 */
class Decagon_MPS6: public WaspSensorAgrXtr
{
	public:

		Decagon_MPS6(uint8_t socket);	// constructor
		sensorMPS6Vector sensorMPS6;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseMPS6();
};


/*!
 * \class Apogee_SO411
 * \brief class inherited from WaspSensorAgrXtr for SO411 sensor
 */
class Apogee_SO411: public WaspSensorAgrXtr
{
	public:

		Apogee_SO411(uint8_t socket);	// constructor
		sensorSO411Vector sensorSO411;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseSO411();
};

/*!
 * \class Apogee_SI411
 * \brief class inherited from WaspSensorAgrXtr for SI411 sensor
 */
class Apogee_SI411: public WaspSensorAgrXtr
{
	public:

		Apogee_SI411(uint8_t socket);	// constructor
		sensorSI411Vector sensorSI411;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseSI411();
};

/*!
 * \class Apogee_SF421
 * \brief class inherited from WaspSensorAgrXtr for SI421 sensor
 */
class Apogee_SF421: public WaspSensorAgrXtr
{
	public:

		Apogee_SF421(uint8_t socket);	// constructor
		sensorSF421Vector sensorSF421;

		uint8_t ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;
		uint8_t parseSF421();
};

/*!
 * \class leafWetness
 * \brief class inherited from WaspSensorAgrXtr for Leaf Wetness sensor
 */
class leafWetness: public WaspSensorAgrXtr
{
	public:

		leafWetness();	//! Constructor
		
		//! Variable: stores measured leaf wetness in Volts in float type
		float wetness;

		void ON();
		void OFF();
		uint8_t read();

	private:

		typedef WaspSensorAgrXtr super;

};


/*!
 * \class dendrometer
 * \brief class inherited from WaspSensorAgrXtr for Dendrometer sensors
 */

class dendrometer: public WaspSensorAgrXtr
{
	public:

		dendrometer();				//! Constructor
		dendrometer(uint8_t type);	//! Constructor
		
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

		typedef WaspSensorAgrXtr super;
		uint8_t dendroType;
};


/*!
 * \class weatherStation
 * \brief class inherited from WaspSensorAgrXtr for Weather Station GMX-240
 */

class weatherStation: public WaspSensorAgrXtr
{
	public:
		weatherStation();				//! Constructor
		weatherStationVector gmx240;

		void ON();
		void OFF();
		uint8_t read();	

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class bme
 * \brief class inherited from WaspSensorAgrXtr to manage  BME280 sensor
 */
class bme: public WaspSensorAgrXtr
{
	public:

		bme(uint8_t socket);	// Constructor

		uint8_t ON();
		void OFF();
		float getTemperature();
		float getHumidity();
		float getPressure();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class ultrasound
 * \brief class inherited from WaspSensorAgrXtr to manage ultrasound sensor
 */
class ultrasound: public WaspSensorAgrXtr
{
	public:

		ultrasound(uint8_t socket);	// Constructor

		uint8_t ON();
		void OFF();
		uint16_t getDistance();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class luxes
 * \brief class inherited from WaspSensorAgrXtr to manage luxes sensor
 */
class luxes: public WaspSensorAgrXtr
{
	public:

		luxes(uint8_t socket);	// Constructor;

		uint8_t ON();
		void OFF();
		uint32_t getLuminosity();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class _4_20mA
 * \brief class inherited from WaspSensorAgrXtr to manage 4-20mA sensor
 */
class _4_20mA: public WaspSensorAgrXtr
{
	public:

		_4_20mA(uint8_t socket);	// Constructor
		
		//! Variable: stores measured  current in float type
		float current;

		uint8_t ON();
		void OFF();
		float read();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class Apogee_SU100
 * \brief class inherited from WaspSensorAgrXtr for SU100 sensor
 */
class Apogee_SU100: public WaspSensorAgrXtr
{
	public:

		Apogee_SU100(uint8_t socket);	// constructor
		
		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class Apogee_SQ110
 * \brief class inherited from WaspSensorAgrXtr for SQ110 sensor
 */
class Apogee_SQ110: public WaspSensorAgrXtr
{
	public:

		Apogee_SQ110(uint8_t socket);	// constructor

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();

	private:

		typedef WaspSensorAgrXtr super;
};

/*!
 * \class Apogee_SP510
 * \brief class inherited from WaspSensorAgrXtr for SP510 sensor
 */
class Apogee_SP510: public WaspSensorAgrXtr
{
	public:

		Apogee_SP510(uint8_t socket);	// constructor

		//! Variable: stores measured radiation voltage in volts in float type
		float radiationVoltage;
		//! Variable: stores measured radiation in umol*m-2*s-1 in float type
		float radiation;

		uint8_t ON();
		void OFF();
		float read();
		void heater(uint8_t state);

	private:

		typedef WaspSensorAgrXtr super;
};




#endif
