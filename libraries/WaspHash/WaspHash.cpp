/*!
 *  Library for managing the HASH encryption library
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
 *
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif


#include "WaspHash.h"

/*******************************************************************************
 * Class methods
*******************************************************************************/

/// Constructors ///////////////////////////////////////////////////////
WaspHash::WaspHash()
{
   // nothing to do here
}


void WaspHash::printMessageDigest(	char* algorithm
									, uint8_t* hash
									, uint8_t size)
{
	USB.print(algorithm);
	USB.print(F("\""));
	
	// print hash string in HEX format
	for (uint8_t i=0; i<size;i++)
	{
		USB.printHex(hash[i]);		
	}
	USB.println(F("\""));  
}

/*
 * md5 ( alg, hash_message, message, size_message ) -
 *
 */
void WaspHash::md5(	uint8_t hash_message[]
					, uint8_t* message
					, uint32_t size_message )
{
	md5_hash_t	hash;
	
	md5_1(&hash,message,size_message);
  
	for(uint8_t x = 0; x < 16;x++ )
	{
		hash_message[x] = hash[x];
	}
}

/*
 * sha ( alg, hash_message, message, size_message ) - calcule message digest 
 * with SHA algorithm.
 *
 */
void WaspHash::sha(	uint8_t alg
					, uint8_t hash_message[]
					, uint8_t* message
					, uint32_t size_message)
{
	switch(alg)
	{
		case SHA1:
			sha1_hash_t   hash1;
			sha1_1(&hash1,message,size_message);
			for(uint8_t x = 0; x < 20;x++ )
			{
				hash_message[x] = hash1[x];
			}     
			break;

		case SHA224:
			sha224_hash_t hash224;
			sha224_1(&hash224,message,size_message);
			for(uint8_t x = 0; x < 28;x++ )
			{
				hash_message[x] = hash224[x];
			}
			break;

		case SHA256:
			sha256_hash_t hash256;
			sha256_1(&hash256,message,size_message);
			for(uint8_t x = 0; x < 32;x++ )
			{
				hash_message[x] = hash256[x];
			}
			break;

		case SHA384:
			sha384_hash_t hash384;
			sha384_1(&hash384,message,size_message);
			for(uint8_t x = 0; x < 48;x++ )
			{
				hash_message[x] = hash384[x];
			}
			break;

		case SHA512:
			sha512_hash_t hash512;
			sha512_1(&hash512,message,size_message);
			for(uint8_t x = 0; x < 64;x++ )
			{
				hash_message[x] = hash512[x];
			}
			break;
	}
  
}

// Preinstantiate Objects //////////////////////////////////////////////////////
WaspHash HASH = WaspHash();
