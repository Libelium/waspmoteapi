/*! \file WaspRSA.cpp
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

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif


// Constructors ////////////////////////////////////////////////////////////////
WaspRSA::WaspRSA()
{
  // Nothing to do here
}

/*
 * encrypt(char* modulus,char* public_key, char* message, char* encrypted_message) 
 *
 * Parameters: 
 *    modulus : Modulus of public key to calculate RSA algortitm
 *    public_key: Plublic key to encrypt plaintext message.
 *    message: Plaintext message before calculating RSA Algorithm
 *    encrypted_message: Ciphertext message after calculating RSA Algorithm
 */
uint64_t* WaspRSA::encrypt(char* modulus,char* public_key, char* message){
   // char* cosa;
	//! Variables Declaration
    mpi M, E, N, X;
    uint64_t encrypted_message[16];
    //! Variable initialization
    mpi_init( &M, &E, &N, &X, NULL );

    //! Plain Message 
    mpi_read_string( &M, 16, message);

    //! Public Key
    mpi_read_string( &E, 16, public_key);
          
    //! Modulus
    mpi_read_string( &N, 16, modulus);

    //! X = M^E mod N
    mpi_exp_mod( &X, &M, &E, &N, NULL ) ;

    int i;

    USB.println(encrypted_message[1],HEX);
    for(i=0;i<16;i++){
        encrypted_message[i] = X.p[i];
    }
    mpi_free(&X,&M,&E,&N, NULL );
    return encrypted_message;
}

/*
 * decrypt(char* encrypted_message, char* private_key, char* modulus, char* prime_p, char* prime_q,
                  char* dp, char* dq, char* qinv, uint64_t* decrypted_message, uint16_t size)
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
 uint64_t* WaspRSA::decrypt(char* encrypted_message, char* private_key, char* modulus, char* prime_p, char* prime_q,
                  char* dp, char* dq, char* qinv){
	//! Variables Declaration
	mpi I;		//!  Input Cipher Message 
	mpi K;		//!  Private Key 		
	mpi M;		//!  Modulus 			
	mpi P;      //!  1st prime factor  
    mpi Q;      //!  2nd prime factor  
    mpi DP;     //!  D % (P - 1)       
    mpi DQ;     //!  D % (Q - 1)       
    mpi QP;     //!  1 / (Q % P)       
	
    uint64_t decrypted_message[16];
    uint8_t i;
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

    mpi_free(&I,&K,&M,&P,&Q,&DP,&DQ,&QP,&T1, &T2, NULL );
    USB.println(encrypted_message[1],HEX);
    for(i=0;i<16;i++){
        decrypted_message[i] = T.p[i];
    }
    return decrypted_message;
}

void WaspRSA::renewall(uint8_t* renewal_key, uint8_t* new_key, uint8_t size_new_key){

}
// Preinstantiate Objects /////////////////////////////////////////////////////

WaspRSA RSA = WaspRSA();

///////////////////////////////////////////////////////////////////////////////
