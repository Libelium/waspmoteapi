/*! \file WaspGPRS_SIM928A.h
    \brief Library for managing the SIM928A module
    
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

 /*! \def WaspGPRS_SIM928A_h
    \brief The library flag
    
  */
#ifndef WaspGPRS_SIM928A_h
#define WaspGPRS_SIM928A_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <WaspGPRS_Pro_core.h>
#include <inttypes.h>

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspGPRS_SIM928A Class
/*!
	WaspGPRS_SIM928A Class defines all the variables and functions used to manage SIM928A module
 */
class WaspGPRS_SIM928A : public WaspGPRS_Pro_core
{
	private:	
	
	public:
		
		float longitude;		
		float latitude;	

		float altitude;		
		char UTC_time[11];		
		char date[9];			
		int8_t sats_in_view;
		int8_t sats_in_use;
		float speedOG;			
		float courseOG;		
		
		float HDOP;
		float PDOP;
		float VDOP;
		
		int GPS_status;
		int fix_status;
		int SNR;
		int mode;				//A=Autonomous, D=DGPS, E=DR, N = Output Data Not Valid R = Coarse Position

	
	WaspGPRS_SIM928A();    


	//! This function switches on the GPS engine
	/*!
	\return		1 if success
				0 if error
	*/
	int8_t GPS_ON();
	
	//! This function switches off the GPS engine
	/*!
	\return		1 if success
				0 if error
	*/
	int8_t GPS_OFF();

	//! This function reads the data from satellites
	/*!
	\param bool parse: '0' raw string in buffer_GPRS and '1' for GPS data parsed and stored in variables
	\return		1 if success
				-1 if timeout
				-2 if error
	*/
	int8_t getGPSData(bool parse);

	//! This function checks if the GPS position is fixed or not
	/*!
	\param	char* buffer: string pointer to store the information data
	\return 	'0' if timeout
				'1' if GPS status is fixed
				'2' if GPS status is not fixed
	 */
	int8_t checkGPS();
	
	
	//! This function checks if the position is fixed until time out
	/*!
	\return		0 if not connected
				1 if connected
	*/
	uint8_t waitForGPSSignal();
		
	//! This function checks if the position is fixed until time out
	/*!
	\param	long timeout: max time to wait in seconds
	\return		0 if not connected
				1 if connected
	*/
	uint8_t waitForGPSSignal(long timeout);
	
	//! This function sets time and date from the GPS to the RTC.
	//! GPS has to be initialized first and got the time/date
	/*!
	\return		1 if success
				0 otherwise
	*/
	bool setRTCTimeFromGPS();
	
};

extern WaspGPRS_SIM928A GPRS_SIM928A;

#endif
