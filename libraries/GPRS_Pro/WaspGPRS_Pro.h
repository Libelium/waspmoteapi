/*! \file WaspGPRS_Pro.h
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

 /*! \def WaspGPRS_Pro_h
    \brief The library flag
    
  */
#ifndef WaspGPRS_Pro_h
#define WaspGPRS_Pro_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>
#include <WaspGPRS_Pro_core.h>


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspGPRS_Pro Class
/*!
	WaspGPRS Class defines all the variables and functions used to manage GPRS module
 */
class WaspGPRS_Pro : public WaspGPRS_Pro_core
{
		
	public:
		
		WaspGPRS_Pro(){};
	
};

extern WaspGPRS_Pro GPRS_Pro;

#endif
