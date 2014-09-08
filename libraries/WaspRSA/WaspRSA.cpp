/*! \file WaspRSA.cpp
 *  \brief Library for encrypting messages using the RSA algorithm
 *
 *  Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.1
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
 * decrypt(char* encrypted_message, char* private_key, char* modulus, 
 * char* prime_p, char* prime_q, char* dp, char* dq, char* qinv, 
 * uint64_t* decrypted_message, uint16_t size)
 * 
 * Parameters: 
 *    modulus : Modulus of public key to calculate RSA algortitm
 *    private_key: private key to encrypt plaintext message.
 *    p: 1st prime factor  
 *    q: 2nd prime factor 
 *    dp: D % (P - 1) 
 *    dq: D % (Q - 1)  
 *    qp: 1 / (Q % P) 
 *    encrypted_message:                    
 */
int WaspRSA::decrypt(char* encrypted_message
						, char* private_key
						, char* modulus
						, char* prime_p
						, char* prime_q
						, char* dp
						, char* dq
						, char* qinv
						, char* decrypted_message
						, int	slen)
{
	//! Variables Declaration
	mpi I;		//!  Input Cipher Message 
	mpi K;		//!  Private Key 		
	mpi M;		//!  Modulus 			
	mpi P;      //!  1st prime factor  
    mpi Q;      //!  2nd prime factor  
    mpi DP;     //!  D % (P - 1)       
    mpi DQ;     //!  D % (Q - 1)       
    mpi QP;     //!  1 / (Q % P)       
	
	// Auxiliar Variables
    mpi T, T1, T2;
    
    // Initialitation
    mpi_init(&I,&K,&M,&P,&Q,&DP,&DQ,&QP,&T, &T1, &T2, NULL );

    // Input - Cipher Message
    mpi_read_string( &I, 16,encrypted_message);

    // Private Key
    mpi_read_string( &K,16,private_key);

    // Modulus
    mpi_read_string( &M, 16,modulus);

    // P
    mpi_read_string( &P, 16,prime_p);
 
 	// Q 
    mpi_read_string( &Q,16,prime_q);

    // dP
    mpi_read_string( &DP, 16,dp);

    // dQ
    mpi_read_string( &DQ, 16,dq);

    // QP
	mpi_read_string( &QP, 16,qinv);

    /*
     * faster decryption using the CRT
     *
     * T1 = input ^ dP mod P
     * T2 = input ^ dQ mod Q
     */
    mpi_exp_mod( &T1, &I, &DP, &P, NULL);
    mpi_exp_mod( &T2, &I, &DQ, &Q, NULL );

    /*
     * T = (T1 - T2) * (Q^-1 mod P) mod P
     */
    mpi_sub_mpi( &T, &T1, &T2 ) ;
    mpi_mul_mpi( &T1, &T, &QP ) ;
    mpi_mod_mpi( &T, &T1, &P ) ;

    /*
     * output = T2 + T * Q
     */
    mpi_mul_mpi( &T1, &T, &Q ) ;
    mpi_add_mpi( &T, &T2, &T1 ) ;   
    	
	// export result to string 
	int aux_slen = slen;
    mpi_write_string(&T, 16, decrypted_message, &aux_slen );  
    
    // free structures
    mpi_free(&I,&K,&M,&P,&Q,&DP,&DQ,&QP,&T1, &T2, NULL );    
    
    return strlen(decrypted_message);
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

void WaspRSA::renewall(	uint8_t* renewal_key
						, uint8_t* new_key
						, uint8_t size_new_key)
{

}
// Preinstantiate Objects /////////////////////////////////////////////////////

WaspRSA RSA = WaspRSA();

///////////////////////////////////////////////////////////////////////////////
