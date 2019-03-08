/*! \file WaspRSA.cpp
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

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspRSA.h"


// Constructors ////////////////////////////////////////////////////////////////
WaspRSA::WaspRSA()
{
  // Nothing to do here
}

/*
 * encrypt(char* modulus,char* public_key, char* message, char* encrypted_message) 
 *
 * The theory says that the encrypted message is calculated as follows:
 * 	X = M^E (mod N)
 * 
 * Where:
 * 	'M' stands for the original message
 * 	'E' stands for the public exponent
 * 	'N' stands for the modulus
 * 	'X' stands for the encrypted message
 * 
 * Read more: http://www.physicsforums.com
 * 
 * Parameters: 
 *    message: Plaintext message before calculating RSA Algorithm
 *    public_key: Public key to encrypt plaintext message.
 *    modulus : Modulus of public key to calculate RSA algortitm
 *    encrypted_message: Ciphertext message after calculating RSA Algorithm
 */
int WaspRSA::encrypt(	char* message
						, char* exponent
						, char* modulus
						, char* encrypted_message
						, int slen )
{   
	//! Variables Declaration
	//! 'M' for message
	//! 'E' for RSA public exponent
	//! 'N' for RSA public modulus
	//! 'X' for encrypted result
    mpi M, E, N, X;
    
    //! Variable initialization
    mpi_init( &M, &E, &N, &X, NULL );

    //! Plain Message 
    mpi_read_string( &M, 16, message); 

    //! Public Key
    mpi_read_string( &E, 16, exponent);
    
    //! Modulus
    mpi_read_string( &N, 16, modulus);
 
    //! X = M^E mod N
    mpi_exp_mod( &X, &M, &E, &N, NULL ) ;    
    
	// Export result to a string   
	int aux_slen = slen;
    mpi_write_string(&X, 16, encrypted_message, &aux_slen );  
    
    // free structures
    mpi_free(&X,&M,&E,&N, NULL );
    
    return strlen(encrypted_message);
}


/*
 * encrypt(char* modulus,char* public_key, char* message, char* encrypted_message) 
 *
 * The theory says that the encrypted message is calculated as follows:
 * 	X = M^E (mod N)
 * 
 * Where:
 * 	'M' stands for the original message
 * 	'E' stands for the public exponent
 * 	'N' stands for the modulus
 * 	'X' stands for the encrypted message
 * 
 * Read more: http://www.physicsforums.com
 * 
 * Parameters: 
 *    message: Plaintext message before calculating RSA Algorithm
 *    public_key: Public key to encrypt plaintext message.
 *    modulus : Modulus of public key to calculate RSA algortitm
 *    encrypted_message: Ciphertext message after calculating RSA Algorithm
 */
int WaspRSA::encrypt( uint8_t* message
						, uint16_t length
						, char* exponent
						, char* modulus
						, char* encrypted_message
						, int slen )
{   
	//! Variables Declaration
	//! 'M' for message
	//! 'E' for RSA public exponent
	//! 'N' for RSA public modulus
	//! 'X' for encrypted result
    mpi M, E, N, X;
    
    //! Variable initialization
    mpi_init( &M, &E, &N, &X, NULL );

    //! Plain Message 
    mpi_read_binary( &M, message, length); 

    //! Public Key
    mpi_read_string( &E, 16, exponent);
    
    //! Modulus
    mpi_read_string( &N, 16, modulus);
 
    //! X = M^E mod N
    mpi_exp_mod( &X, &M, &E, &N, NULL ) ;    
    
	// Export result to a string   
	int aux_slen = slen;
    mpi_write_string(&X, 16, encrypted_message, &aux_slen );  
    
    // free structures
    mpi_free(&X,&M,&E,&N, NULL );
    
    return strlen(encrypted_message);
}








/*
 * printMessage 
 * 
 * Function to print the encrypted messages 
 * 
 */
void WaspRSA::printMessage(	char* encrypted_message )
{
	int len = strlen(encrypted_message);	
	
	for(int i = 0; i < len ; i++)
	{
		USB.print( encrypted_message[i]);
		if( ((i+1)%32)==0) USB.println();
	}
	USB.println();
	
}


// Preinstantiate Objects /////////////////////////////////////////////////////

WaspRSA RSA = WaspRSA();

///////////////////////////////////////////////////////////////////////////////
