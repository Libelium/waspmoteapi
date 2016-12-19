/*! \file WaspSensorParking.h
    \brief Library for managing the Parking Sensor Board
    
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
  
    Version:		3.0
    Design:			David Gascón
    Implementation:	Alberto Bielsa, Manuel Calahorra

*/

 /*! \def WaspSensorParking_h
    \brief The library flag
    
  */
#ifndef WaspSensorParking_h
#define WaspSensorParking_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <WaspConstants.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! 	\def SENS_PARKING_X
	\brief Sensor Types. Sensor Parking X axis input
*/
#define SENS_PARKING_X	ANALOG1
/*! 	\def SENS_PARKING_Y
	\brief Sensor Types. Sensor Parking Y axis input
*/
#define SENS_PARKING_Y	ANALOG2
/*! 	\def SENS_PARKING_Z
	\brief Sensor Types. Sensor Parking Z axis input
*/
#define SENS_PARKING_Z	ANALOG5
/*! 	\def SENS_PARKING_T
	\brief Sensor Types. Sensor Parking Temperature input
*/
#define SENS_PARKING_T	ANALOG7


/*! 	\def PARKING_SET_RESET_X
	\brief Sensor Types. Sensor Parking X set/reset output
*/
#define PARKING_SET_RESET_X	DIGITAL2
/*! 	\def PARKING_SET_RESET_Y
	\brief Sensor Types. Sensor Parking Y set/reset output
*/
#define PARKING_SET_RESET_Y	DIGITAL1
/*! 	\def PARKING_SET_RESET_Z
	\brief Sensor Types. Sensor Parking Z set/reset output 
*/
#define PARKING_SET_RESET_Z	DIGITAL3


/*! 	\def PARKING_THRESHOLD
	\brief Sensor Types. Reference Threshold for state estimation
*/
#define PARKING_THRESHOLD	20

/*! 	\def PARKING_EMPTY
	\brief Sensor Types. Empty lot state
*/
#define PARKING_EMPTY		0
/*! 	\def PARKING_OCCUPIED
	\brief Sensor Types. Occupied lot state
*/
#define PARKING_OCCUPIED	1


/*! 	\def PARKING_ADDRESS_COEFX2
	\brief EEPROM Address. X axis degree two compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFX2		186;
/*! 	\def PARKING_ADDRESS_COEFY2
	\brief EEPROM Address. Y axis degree two compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFY2		190;
/*! 	\def PARKING_ADDRESS_COEFZ2
	\brief EEPROM Address. Z axis degree two compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFZ2		194;
/*! 	\def PARKING_ADDRESS_COEFX
	\brief EEPROM Address. X axis degree one compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFX		198;
/*! 	\def PARKING_ADDRESS_COEFY
	\brief EEPROM Address. Y axis degree one compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFY		202;
/*! 	\def PARKING_ADDRESS_COEFZ
	\brief EEPROM Address. Z axis degree one compensation coefficient Address
*/
#define PARKING_ADDRESS_COEFZ		206;
/*! 	\def PARKING_ADDRESS_CONSTX
	\brief EEPROM Address. X axis constant compensation coefficient Address
*/
#define	PARKING_ADDRESS_CONSTX		210;
/*! 	\def PARKING_ADDRESS_CONSTY
	\brief EEPROM Address. Y axis constant compensation coefficient Address
*/
#define	PARKING_ADDRESS_CONSTY		214;
/*! 	\def PARKING_ADDRESS_CONSTZ
	\brief EEPROM Address. Z axis constant compensation coefficient Address
*/
#define	PARKING_ADDRESS_CONSTZ		218;


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspSensorParking Class
/*!
	WaspSensorParking Class defines all the variables and functions used for managing the Parking Sensor Board
 */
class WaspSensorParking
{
	private:

	
	public:

	//! Variable : compensation coeficient for the X axis
  	/*!
	It specifies the degree two compensation coefficient reference that will be
	taken to calculate the reference for the X axis
	\sa calculateReference, loadReference
   	*/
	float  coefX2;
	//! Variable : compensation coeficient for the Y axis
  	/*!
	It specifies the degree two compensation coefficient reference that will be
	taken to calculate the reference for the Y axis
	\sa calculateReference, loadReference
   	*/
	float  coefY2;
	//! Variable : compensation coeficient for the Z axis
  	/*!
	It specifies the degree two compensation coefficient reference that will be
	taken to calculate the reference for the Z axis
	\sa calculateReference, loadReference
   	*/
	float  coefZ2;
	//! Variable : compensation coeficient for the X axis
  	/*!
	It specifies the degree one compensation coefficient reference that will be
	taken to calculate the reference for the X axis
	\sa calculateReference, loadReference
   	*/
	float  coefX;
	//! Variable : compensation coeficient for the Y axis
  	/*!
	It specifies the degree one compensation coefficient reference that will be
	taken to calculate the reference for the Y axis
	\sa calculateReference, loadReference
   	*/
	float  coefY;
	//! Variable : compensation coeficient for the Z axis
  	/*!
	It specifies the degree one compensation coefficient reference that will be
	taken to calculate the reference for the Z axis
	\sa calculateReference, loadReference
   	*/
	float  coefZ;
	//! Variable : compensation coeficient for the X axis
  	/*!
	It specifies the constant coefficient reference that will be taken to calculate
	the reference for the X axis
	\sa calculateReference, loadReference
   	*/
	float  constX;
	//! Variable : compensation coeficient for the Y axis
  	/*!
	It specifies the constant coefficient reference that will be taken to calculate
	the reference for the Y axis
	\sa calculateReference, loadReference
   	*/
	float  constY;
	//! Variable : compensation coeficient for the Z axis
  	/*!
	It specifies the constant coefficient reference that will be taken to calculate
	the reference for the Z axis
	\sa calculateReference, loadReference
   	*/
	float  constZ;


	//! Variable : initial value for the X axis sensor
  	/*!
	It specifies the reference that will be taken to calculate the reference for
	the X axis
	\sa calibration, calculateReference
   	*/
	int  initialX;
	//! Variable : initial value for the Y axis sensor
  	/*!
	It specifies the reference that will be taken to calculate the reference for
	the Y axis
	\sa calibration, calculateReference
   	*/
	int  initialY;
	//! Variable : initial value for the Z axis sensor
  	/*!
	It specifies the reference that will be taken to calculate the reference for
	the Z axis
	\sa calibration, calculateReference
   	*/
	int  initialZ;
	//! Variable : initial value for the X axis sensor
  	/*!
	It specifies the temperature at which calibration was performed
   	*/
	int  initialT;


	//! Variable : reference index for temperature compensation
  	/*!
	It specifies the initial index for temperature compensation for the X axis
	\sa calibration, calculateReference
   	*/
	float  indexX;
	//! Variable : reference index for temperature compensation
  	/*!
	It specifies the initial index for temperature compensation for the Y axis
	\sa calibration, calculateReference
   	*/
	float  indexY;
	//! Variable : reference index for temperature compensation
  	/*!
	It specifies the initial index for temperature compensation for the Z axis
	\sa calibration, calculateReference
   	*/
	float  indexZ;


	//! Variable : reference value for the X axis
  	/*!
	It specifies the reference that will be taken to estimate the lot state for
	the X axis
	\sa calculateReference, estimateState
   	*/
	int  referenceX;
	//! Variable : reference value for the X axis
  	/*!
	It specifies the reference that will be taken to estimate the lot state for
	the Y axis
	\sa calculateReference, estimateState
   	*/
	int  referenceY;
	//! Variable : reference value for the X axis
  	/*!
	It specifies the reference that will be taken to estimate the lot state for
	the Z axis
	\sa calculateReference, estimateState
   	*/
	int  referenceZ;


	//! Variable : current value for the X axis
  	/*!
	It specifies the last read value for the X axis
	\sa readParking, readParkingSetReset, estimateState
   	*/
	int  valueX;
	//! Variable : current value for the Y axis
  	/*!
	It specifies the last read value for the Y axis
	\sa readParking, readParkingSetReset, estimateState
   	*/
	int  valueY;
	//! Variable : current value for the Z axis
  	/*!
	It specifies the last read value for the Z axis
	\sa readParking, readParkingSetReset, estimateState
   	*/
	int  valueZ;


	WaspSensorParking();
	
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


	//! It sets board power mode, setting ON/OFF the 5V switch
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\return error
	 */
	int8_t setBoardMode(uint8_t mode);

	//! It starts the application, calculating the initial values at the lot and
	//! stores them at variables initialX, initialY and initialZ, the initial
	//! temperature in initialT and the initial compensation indexes in variables
	//! indexX, indexY and indexZ
  	/*!
	\param void
	\return void
	\sa calculateReference, estimateState
	 */
	void calibration(void);

	//! It loads the coefficients of the approximation for temperature dependance
	//! from the EEPROM in variables coefX2, coefY2, coefZ2, coefX, coefY, coefZ,
	//! constX, constY and constZ
  	/*!
	\param void
	\return void
	 */
	void loadReference(void);
	
	//! It calculates the reference for each axis in function of the initial values
	//! (initialX, initialY and initialZ), the compensation coefficeints (coefX2,
	//! coefY2, coefZ2, coefX, coefY, coefZ, constX, constY and constZ) and current
	//! temperature and stores them in variables referenceX, referenceY and referenceZ
  	/*!
	\param int temperature : specifies the temperature of the sensors in Celsius degree
	\return void
	\sa readTemperature, estimateState
	 */
	void calculateReference(int temperature);

	//! It reads the output voltage of the temperature sensor and returns
	//! temperature in Celsius degree
  	/*!
	\param void
	\return int : the temperature read in Celsius degree
	\sa calculateReference
	 */
	int readTemperature(void);

	//! It reads the magnetic field sensors and returns the values read in variables
	//! valueX, valueY and valueZ
  	/*!
	\param void
	\return void
	\sa 
	 */
	void readParking(void);

	//! It applies a set and reset pulse to the magnetic field sensors and reads
	//! them, returning the values read in variables valueX, valueY and valueZ
  	/*!
	\param void
	\return void
	\sa 
	 */
	void readParkingSetReset(void);

	//! It uses the values in variables valueX, valueY, valueZ, referenceX,
	//! referenceY and referenceZ to estimate the state of the parking lot
  	/*!
	\param void
	\return estate of the lot (0 for empty, 1 for occupied)
	\sa 
	 */
	boolean estimateState(void);


};

extern WaspSensorParking SensorParking;

#endif

