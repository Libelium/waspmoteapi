/*! \file WaspHash.h
    \brief Library for managing the HASH encryption library
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published 
    by the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
  
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
    Version:    	3.0
    Design:   		David Gascón
    Implementation: Alvaro Gonzalez, Yuri Carmona

 */
#ifndef WaspHash_h
#define WaspHash_h 

#include <inttypes.h>
#include "utility/md5.h"
#include "utility/md5_sbox.h"
#include "utility/sha1.h"
#include "utility/sha224.h"
#include "utility/sha256.h"
#include "utility/sha384.h"
#include "utility/sha512.h"
#include "utility/sha2_small_common.h"
#include "utility/sha2_large_common.h"

/*******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
#define SHA1 1
#define SHA224 2
#define SHA256 3
#define SHA384 4
#define SHA512 5

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspHash Class
/*!
    WaspHash Class defines all the variables and functions used to manage 
    different hash algorithm
 */

class WaspHash{  

  private:    

    

  public:
    //! class constructor
  	/*!
    	\param void
    	\return void
  	*/
    WaspHash();    

    void printMessageDigest(char* algorithm,uint8_t* hash,uint8_t size);
 
    //! Its refers to calculate MD5 Algorithm
    /*!
      takes as input a message of arbitrary length and produces as output 
      a 128-bit "fingerprint" or "message digest" of the input
     
    \param hash_message variable which to store message digest
    \param message message original 
    \param size_message size of original message
    \return void
    */			
    void md5(	uint8_t hash_message[],
				uint8_t* message,
				uint32_t size_message);    

    //! Its refers to calculate SHA Algorithms
    /*!
      takes as input a message of arbitrary length and produces as output 
      a 128-bit, 160-bit, 224-bit, 256-bit, 384-bit, 512-bit
      "fingerprint" or "message digest" of the input
    
    \param alg variable to select SHA Algoritm
    \param hash_message variable which to store message digest
    \param message message original 
    \param size_message size of original message
    \return void
    */
    void sha(	uint8_t alg,
				uint8_t hash_message[],
				uint8_t* message,
				uint32_t size_message);
    
};

extern WaspHash HASH;

#endif
