/*! \file WaspSensorSW.h
    \brief Library for managing the Smart Water Sensor Board
    
    Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.0

    Design:		David Gascón

    Implementation:	Alberto Bielsa, Manuel Calahorra

 */


 /*! \def WaspSensorSW_h
    \brief The library flag
    
  */
#ifndef WaspSensorSW_h
#define WaspSensorSW_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def SENS_SW_PT1000
    \brief Sensor types. PT1000 sensor
    
 */
/*! \def SENS_SW_DO
    \brief Sensor types. PT1000 sensor
    
 */
/*! \def SENS_SW_COND
    \brief Sensor types. PT1000 sensor
    
 */
/*! \def SENS_SW_PH
    \brief Sensor types. PT1000 sensor
    
 */
/*! \def SENS_SW_ORP
    \brief Sensor types. PT1000 sensor
    
 */
/*! \def SENS_SW_DI
    \brief Sensor types. PT1000 sensor
    
 */
#define	SENS_SW_PT1000			1
#define	SENS_SW_DO				2
#define	SENS_SW_COND			3
#define	SENS_SW_PH				4
#define	SENS_SW_ORP				5
#define	SENS_SW_DI				6

/*! \def SENS_SW_PT1000_VCC
    \brief PT1000 sensor supply voltage pin
    
 */
/*! \def SENS_SW_DO_VCC
    \brief Dissolved Oxygen sensor supply voltage pin
    
 */
/*! \def SENS_SW_COND_VCC
    \brief Conductivity sensor supply voltage pin
    
 */
/*! \def SENS_SW_PH_VCC
    \brief pH sensor supply voltage pin
    
 */
/*! \def SENS_SW_ORP_VCC
    \brief Oxidation reduction potential sensor supply voltage pin
    
 */
/*! \def SENS_SW_DI_VCC
    \brief Dissolved ions sensor supply voltage pin
    
 */
#define	SENS_SW_PT1000_VCC		16
#define	SENS_SW_DO_VCC			14
#define	SENS_SW_COND_VCC		19
#define	SENS_SW_PH_VCC			15
#define	SENS_SW_ORP_VCC			18
#define	SENS_SW_DI_VCC			17


/*! \def COND_MUX_0
    \brief Conductivity multiplexor pin selector 0
    
 */
/*! \def COND_MUC_1
    \brief Conductivity multiplexor pin selector 1    
 */
#define	SW_COND_MUX_0			20
#define	SW_COND_MUX_1			DIGITAL1

/*! \def SW_COND_FREQ_X
    \brief Frequency options for the conductivity sensor
 */
#define	SW_COND_FREQ_1		1
#define	SW_COND_FREQ_2		2
#define	SW_COND_FREQ_3		3
#define	SW_COND_FREQ_4		4

/*! \def SW_COND_CAL_XX
    \brief Calibration values of the conductivity sensor
 */
#define	SW_COND_CAL_01		0.0271
#define	SW_COND_CAL_02		0.0365
#define	SW_COND_CAL_03		0.0478
#define	SW_COND_CAL_04		0.0676
#define	SW_COND_CAL_05		0.1151
#define	SW_COND_CAL_06		0.1997
#define	SW_COND_CAL_07		0.3190
#define	SW_COND_CAL_08		0.3698
#define	SW_COND_CAL_09		0.5047
#define	SW_COND_CAL_10		0.5990
#define	SW_COND_CAL_11		0.6860
#define	SW_COND_CAL_12		0.7642
#define	SW_COND_CAL_13		0.8694
#define	SW_COND_CAL_14		0.8754
#define	SW_COND_CAL_15		0.9076
#define	SW_COND_CAL_16		0.9931

/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspSensorSW Class
/*!
	WaspSensorSW Class defines all the variables and functions used for
	managing the Smart Water Sensor Board
 */
class WaspSensorSW
{
	private:

	//! It contains the frequency of operation of the conductivity sensor
 	uint8_t SW_condFrequency;

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float readADC(int channel);
 
	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float readPT1000(void);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float readConductivity(void);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float resistanceConversion(float input);
	
	//! It calculates the median value of an array of a given length
  	/*!
	\param float array*   : pointer to the array containing data
	\param uint8_t length : length of the array
	\return the median value of the array
	 */	
	float median(float* array, uint8_t length);

	public:

	//! class constructor
  	/*!
		It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorSW();

	//! Turns ON the board
  	/*!
	\param void
	\return void
	 */
	void ON(void);

	//! Turns OFF the board
  	/*!
	\param void
	\return void
	 */
	void OFF(void);


	//! It sets ON/OFF the different sensor switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\param uint8_t sensor : the sensor to set ON/OFF
	\return int8_t error
	 */
	int8_t setSensorMode(uint8_t mode, uint8_t sensor);

	//! It sets ON/OFF the different sensor switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\param uint8_t sensor : the sensor to set ON/OFF
	\param uint8_t frequency : the frequency selected for the conductivity sensor
	\return int8_t error
	 */
	int8_t	setSensorMode(uint8_t mode, uint8_t sensor, uint8_t frequency);

	//! It reads the value measured by the sensor
	/*!
	\param uint16_t sensor : 	specifies the socket to set the threshold
								to ('SENS_SMART_X')
	\return the value read
	 */
	float readValue(uint8_t sensor);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float conductivityConversion(float input);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float conductivityConversion(float input, float cond_1, float cal_1, float cond_2, float cal_2);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float DOConversion(float input, float air_value, float zero_value);

	//! It reads the ADC on the Smart Water board
	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float pHConversion(float input);

	//! It reads the ADC on the Smart Water board
	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float pHConversion(float input, float cal_1, float cal_2, float cal_3);

	//! It reads the ADC on the Smart Water board
  	/*!
	\param int channel : indicates the channel of the analog-to-digital converter
	\					 to be read
	\return void
	 */
	float pHConversion(float input, float cal_1, float cal_2, float cal_3, float temp, float temp_cal);


};

extern WaspSensorSW SensorSW;

#endif

