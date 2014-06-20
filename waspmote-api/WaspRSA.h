/*! \file WaspRSA.h
 *  \brief Library for encrypting messages using the RSA algorithm
 * 	
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		0.1
 *  Design:			David Gascón
 *  Implementation:	Alvaro Gonzalez
 */

 /*! \def WaspRSA_h
    \brief The library flag
    
 */
#ifndef WaspRSA_h
#define WaspRSA_h
#include "rsa/bignum.h"
#include "rsa/bn_mul.h"
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
  	/*!
		It initializes some variables
	\param void
	\return void
	*/
    WaspRSA();

   	//! It encrypt a message with RSA algorithm
  	/*!
		It gets the baud rate from 'USB_RATE'
	\param char* modulus: The modulus necesary to calculate encrypted message with RSA algorithm
	\return char*: encrypted message
	 */
    uint64_t* encrypt(char* modulus,char* public_key, char* message);
    //! It dencrypt a message with RSA algorithm
  	/*!
		It gets the baud rate from 'USB_RATE'
	\param char* modulus: The modulus necesary to calculate decrypted message with RSA algorithm
	\return char*: decrypted message
	 */

    uint64_t* decrypt(char* encrypted_message, char* private_key, char* modulus, char* prime_p, char* prime_q,
    			  char* dp, char* dq, char* qinv);


    //! It show the new AES256 secret key
  	/*!
	\param uint8_t* renewal_key: The modulus necesary to calculate decrypted message with RSA algorithm
	\param uint8_t* renewal_key:
	\param uint8_t* renewal_key:
	 */
	void renewall(uint8_t* renewal_key, uint8_t* new_key, uint8_t size_new_key);
};

extern WaspRSA RSA;

#endif
