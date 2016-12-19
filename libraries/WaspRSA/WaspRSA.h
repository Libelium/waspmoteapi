/*! \file WaspRSA.h
 *  \brief Library for encrypting messages using the RSA algorithm
 * 	
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	Alvaro Gonzalez, Yuri Carmona
 */

 /*! \def WaspRSA_h
    \brief The library flag
    
 */
#ifndef WaspRSA_h
#define WaspRSA_h
#include "utility/bignum.h"
#include "utility/bn_mul.h"
/******************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>


/******************************************************************************
* Class
******************************************************************************/
 
//! WaspRSA Class
/*!
	WaspRSA Class defines all the variables and functions used for managing the 
	RSA algorithm
*/
class WaspRSA
{
private:


public:

	//! class constructor
  	/*! It initializes some variables
	\param void
	\return void
	*/
    WaspRSA();

   	//! It encrypt a message with RSA algorithm
  	/*! It gets the baud rate from 'USB_RATE'
	\param char* modulus: The modulus necesary to calculate encrypted message 
	with RSA algorithm
	* \param char* modulus:
	\return char*: encrypted message
	 */
    int encrypt( char* message
					, char* exponent
					, char* modulus
					, char* encrypted_message
					, int slen );
					
	int encrypt( uint8_t* message
					, uint16_t length
					, char* exponent
					, char* modulus
					, char* encrypted_message
					, int slen );
    


	void printMessage(	char* encrypted_message );


};

extern WaspRSA RSA;

#endif
