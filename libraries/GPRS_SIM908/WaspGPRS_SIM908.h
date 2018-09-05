/*! \file WaspGPRS_SIM908.h
    \brief Library for managing the SIM900 module
    
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
    Implementation:	Alejandro Gállego

*/

 /*! \def WaspGPRS_SIM908_h
    \brief The library flag
    
  */
#ifndef WaspGPRS_SIM908_h
#define WaspGPRS_SIM908_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <WaspGPRS_Pro_core.h>
#include <inttypes.h>
	
	#define BASIC	0
	#define GGA		2
	#define GLL		4
	#define GSA		8
	#define GSV		16
	#define RMC		32
	#define VTG		64
	#define ZDA		128

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspGPRS_SIM908 Class
/*!
	WaspGPRS Class defines all the variables and functions used to manage GPRS module
 */
class WaspGPRS_SIM908 : public WaspGPRS_Pro_core
{
	private:
	
		//function with four answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param char* expectedAnswer3 : string expected to be answered by the module
	\param char* expectedAnswer4 : string expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout	
	\param int sendOnce : specifies if the data is sent once	
	\return  '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found, 
		'3' if expectedAnswer2 was found, '4' if expectedAnswer2 was found and
		'0' if no answer was found
	 */
	uint8_t sendCommand4(	const char* theText, 
							const char* expectedAnswer1, 
							const char* expectedAnswer2, 
							const char* expectedAnswer3, 
							const char* expectedAnswer4, 
							unsigned long MAX_TIMEOUT, 
							int sendOnce);
	
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param char* expectedAnswer3 : string 3 expected to be answered by the module
	\param char* expectedAnswer4 : string 3 expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout	
	\param unsigned long timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found, 
		'3' if expectedAnswer2 was found, '4' if expectedAnswer2 was found and
		'0' if no answer was found
	 */
	uint8_t waitForData(	const char* expectedAnswer1, 
							const char* expectedAnswer2, 
							const char* expectedAnswer3, 
							const char* expectedAnswer4, 
							unsigned long MAX_TIMEOUT, 
							unsigned long timeout,
							int seconds, 
							int n_answers);
	
	public:
		
		char longitude[15];		//longitude		//From basic, GGA, GLL and RMC
		//! Variable : it stores the longitude indicator E: East; W: West
		/*!
		*/ 
		char EW_indicator;		//EW_indicator	//From basic, GGA, GLL and RMC
		char latitude[14];		//latitude		//From basic, GGA, GLL and RMC
		//! Variable : it stores the latitude indicator N: North; S: South
		/*!
		*/ 
		char NS_indicator;		//NS_indicator	//From basic, GGA, GLL and RMC
		float altitude;			//altitude		//From basic
		char UTC_time[11];		//timeGPS		//From basic, GGA, GLL and RMC	//hhmmss
		char date[9];			//dateGPS		//From basic and RMC			//ddmmyy
		int TTFF;								//From basic
		int8_t num_sat;							//From basic, GGA and GSV
		float speedOG;			//speed			//From basic, RMC and VTG
		float courseOG;			//course		//From basic, RMC and VTG

		int sat_info[4][12];					//From RMC and GSV
		float MSL_altitude;						//From GGA
		float geoid_separation;					//From GGA
		float HDOP;								//From GGA and GSA
		float PDOP;								//From GSA
		float VDOP;								//From GSA
		
		char mode;								//From GLL, RMC and VTG A=Autonomous, D=DGPS, E=DR, N = Output Data Not Valid R = Coarse Position
		char manual_auto;						//From GSA //'M' for manual, 'A' for automatic
		char FIX_2D_3D;							//From GSA //'1' for not fixed, '2' for 2D fix, '3' for 3D fix

	
	WaspGPRS_SIM908();
    


	//! Start the GPS part
	//! 
	/*!
	\return
	 */
	int8_t GPS_ON();
	
	//! Stops the GPS part
	//! 
	/*!
	\return
	 */
	int8_t GPS_OFF();
	
	//! Gets GPS data
	//! 
	/*!
	\param int16_t NMEA_string: string to read from GPS module
	\param int8_t parse: '0' raw string in buffer_GPRS and '1' for GPS data parsed and stored in variables
	\return '1' if succes and '0' if error
	 */
	int8_t getGPSData(int16_t NMEA_string, int8_t parse);
	
	//! Checks GPS signal
	//! 
	/*!
	\return '1' if GPS status is unknown
		'2' if GPS status is not fixed
		'3' if GPS status is fixed in 2D mode
		'4' if GPS status is not fixed in 3D mode
	 */
	int8_t checkGPS();
	
	
	//! It checks continuously if receiver is connected to some satellite until default time out.
	//! 
	/*!
	\return It returns '1' if connected, '0' if not
	*/
	uint8_t waitForGPSSignal();
		
	//! It checks continuously if receiver is connected to some satellite until time out.
	//!
	/*!
	\param long timeout: timeout to fix the satellites defined in seconds
	\return It returns '1' if connected, '0' if not
	*/
	uint8_t waitForGPSSignal(long timeout);
	
	//! Sets time and date from the GPS to the RTC.
	//! GPS has to be initialized first and got the time/date
	/*!
	\return It returns 1 on success, 0 otherwise
	*/
	bool setRTCTimeFromGPS();
	
	
	//! convert2Degrees ( input , indicator ) - performs the conversion 
	//! from input parameters in  DD°MM.mmm’ notation to DD.dddddd° notation. 
	/*!
	\param char* input: latitude or longitude
	\param char indicator: 'N', 'S', 'W' or 'E'
	\return a float indicating the latitude or longitude in DD.dddddd° notation
	 */
	float convert2Degrees(char* input, char indicator);


	
};

extern WaspGPRS_SIM908 GPRS_SIM908;

#endif
