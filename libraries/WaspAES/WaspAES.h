/*! \file WaspAES.h
    \brief Library for managing the encryption

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		3.3
    Design:			David Gascón
    Implementation:	Alvaro Gonzalez, Yuri Carmona

 */
#ifndef WaspAES_h
#define WaspAES_h


#include <inttypes.h>
#include "utility/aes.h"

/*******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
#define ENCRYPTION_DEBUG

#define PRINT_AES(str)	USB.print(F("[AES] ")); USB.print(str);



/*! \def AES_128
 * Encryption option: 128-bit key size
 */
/*! \def AES_192
 * Encryption option: 128-bit key size
 */
/*! \def AES_256
 * Encryption option: 128-bit key size
 */
const uint16_t AES_128 = 128;
const uint16_t AES_192 = 192;
const uint16_t AES_256 = 256;


/*! \def ECB
 * Encryption Mode: The simplest of the encryption modes is the electronic
 * codebook (ECB) mode. The message is divided into blocks, and each block is
 * encrypted separately.
 */
/*! \def CBC
 * Encryption Mode: In CBC mode, each block of plaintext is XORed with the
 * previous ciphertext block before being encrypted
 */
#define ECB 1
#define CBC 2


/*! \def PKCS5
 * Padding mode: Padding is in whole bytes. The value of each added byte is the
 * number of bytes that are added, i.e. N bytes, each of value N are added.
 * Example:
 * 	01
 * 	02 02
 * 	03 03 03
 * 	04 04 04 04
 * 	05 05 05 05 05
 * 	etc.
 */
/*! \def ZEROS
 * Padding mode: All the bytes that are required to be padded are padded with zero
 * Example: In the following example the block size is 8 bytes and padding is
 * required for 4 bytes
 * 	... | DD DD DD DD DD DD DD DD | DD DD DD DD 00 00 00 00 |
 */
#define PKCS5	3
#define ZEROS	4


typedef struct {
    uint16_t txt[100];
    uint16_t size_txt;
}o_message;


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspAES Class
/*!
    WaspAES Class defines all the variables and functions used to manage AES
    algorithm
 */
class WaspAES{

  private:

	uint8_t Seed;
	uint8_t Magic;

    /*! \def data
  	\brief Variable used to store the data before and after of encryption
    */
    uint8_t block_data[16];

    /*! \def Variable used to store the keys
  	\brief (Size 16*11, 11 = 10 round and initial)
    */
    aes128_ctx_t ctx128;
    aes192_ctx_t ctx192;
    aes256_ctx_t ctx256;

    //! Its refers to encryption messages with ECB mode
    /*!
      In ECB mode is separated from message in blocks of 16 bytes and
      cipher each one individually

    \param original_data : unencrypted message
    \param size : number of bytes that should occupy the message
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void ECBEncrypt(uint8_t *original_data,uint16_t size,uint16_t keySize);

    //! Its refers to decryption messages with ECB mode
    /*!
      In ECB mode is separated from message in blocks of 16 bytes and
      decodec each one individually

    \param original_data : encrypted message
    \param size : number of bytes that should occupy the message
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void ECBDecrypt(uint8_t *original_data,uint16_t size,uint16_t keySize);

    //! It refers to encryption messages with CBC mode
    /*!
      // In CBC mode divides the message into blocks of 16 bytes,
      at 1 block is applied to the XOR operation and calculates
      the block cipher with block cipher obtained was applied XOR
      with the second block of data into clear and
      the result given is encrypted with AES,
      the result will be the 2 nd block cipher, so on.

    \param original_data : unencrypted message
    \param size : number of bytes that should occupy the message
    \param InitialVector : Initial Vector use to cipher in CBC mode.
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void CBCEncrypt(uint8_t *original_data
					, uint16_t size
					, uint8_t *InitialVector
					, uint16_t keySize);


    //! It refers to decryption messages with CBC mode
    /*!
      // In CBC mode divides the message into blocks of 16 bytes,
      at 1 block is applied to the XOR operation and calculates
      the block cipher with block cipher obtained was applied XOR
      with the second block of data into clear and
      the result given is encrypted with AES,
      the result will be the 2 nd block cipher, so on.

    \param original_data : unencrypted message
    \param size : number of bytes that should occupy the message
    \param InitialVector : Initial Vector use to cipher in CBC mode.
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void CBCDecrypt(uint8_t *original_data
					, uint16_t size
					, uint8_t *InitialVector
					, uint16_t keySize);

    //! It refers to padding of incomplete blocks in encryption process
    /*!
    // When the length of a message is not multiple of 16,
    blocks should be filled up to a number multiple of 16.

    \param original_data : message without cipher
    \param size : number of bytes that should occupy the message
    \param size_original : original message size, less or equal to original_data
    \param mode : Padding mode. PKCS7, Zeros, X923
    \return void
    */
    void paddingEncrypt(uint8_t *original_data,
						uint16_t size,
						uint16_t size_original,
						uint8_t mode);


    //! It refers to padding of incomplete blocks in decryption process
    /*!
    \param original_data : message without cipher
    \param size : number of bytes that should occupy the message
    \param mode : Padding mode. PKCS7, Zeros, X923
    \return o_message : struct to store decrypted message
    */
    o_message paddingDecrypt(	uint8_t *original_data,
								uint16_t size,
								uint8_t mode);

    //! It calcules XOR operation
    /*!
    \param a
    \param b
    \param c result of a XOR b
    */
    void XOR(uint8_t *a, uint8_t *b, uint8_t *c);

    void assignBlock(uint8_t *a, uint8_t *b);

    uint8_t init(char* password, uint16_t keySize);
    uint8_t init(uint8_t* password, uint16_t length, uint16_t keySize);

    uint8_t derechazo(uint8_t val, int nr);

    uint8_t random8bit();

  public:

    //! class constructor
    /*!
        It initializes some variables
    \param void
    \return void
    */
    WaspAES();

    //! It generate a seed of 2 bytes
    /*!
    \param seed seed to Encryption Libraries
    \param void
    */
    void seedGenerator(uint8_t* seed);

    //! It prints encrypted message with matrix format
    /*!
    \param data : data of matrix
    \param size : size of matrix
    \param void
    */
    void printMatrix(uint8_t* data,uint16_t size);

    //! It prints encrypted message
    /*!
    \param data : data of matrix
    \param size : size of matrix
    \param void
    */
    void printMessage(uint8_t* data,uint16_t size);

    //! Calculate the number of blocks occupied by the message
    /*!
    \param message : message to be encrypted
    \param length : length of the message to be encrypted
    */
    uint16_t sizeOfBlocks(char* message);
    uint16_t sizeOfBlocks(uint16_t length);

    //! It encrypts a message
    /*!
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \param password : Password chosen by user in char*
    \param original_message : Message wich is going to encrypted
    \param encrypted_message : Message encryped
    \param mode : mode of block cipher
    \param padding : mode of to fill the incomplete blocks
    \param InitialVector : Initial Vector use to cipher in CBC mode.
    \return void
     */
    uint8_t encrypt(uint16_t keySize,
					char* password,
					char original_message[],
					uint8_t* encrypted_message,
					uint8_t mode,
					uint8_t padding,
					uint8_t* InitialVector);

    uint8_t encrypt(uint16_t keySize,
					char* password,
					uint8_t* original_message,
					uint16_t length,
					uint8_t* encrypted_message,
					uint8_t mode,
					uint8_t padding,
					uint8_t* InitialVector);


	//! It encrypts a message
    /*!
    \param keySize : Size of the key, this value can be 128, 192 or 256
    \param password : Password choose by user in char*
    \param original_message : Message wich is going to encrypted
    \param encrypted_message : Message encryped
    \param mode : mode of block cipher
    \param padding : mode of to fill the incomplete blocks
    \return void
     */
    uint8_t encrypt(uint16_t keySize,
					char* password,
					char original_message[],
					uint8_t* encrypted_message,
					uint8_t mode,
					uint8_t padding);

    uint8_t encrypt(uint16_t keySize,
					char* password,
					uint8_t* original_message,
					uint16_t length,
					uint8_t* encrypted_message,
					uint8_t mode,
					uint8_t padding);

	//! It decrypts a message
    /*!
	\param keySize : Size of the key, this value can be 128, 192 or 256
    \param password : Password choose by user in char*
    \param encrypted_message : Message encrypted
	\param size : size of the encrypted message
    \param original_message : Message wich is going to decrypted
	\param original_size : size of the original message
    \param mode : mode of block cipher
    \param padding : mode of to fill the incomplete blocks
    \param InitialVector : initial vector por CBC mode
    \return '1' if ok; '0' if error
     */

    uint8_t decrypt(uint16_t keySize,
					char* password,
					uint8_t encrypted_message[],
					uint8_t size,
					uint8_t original_message[],
					uint16_t *original_size,
					uint8_t mode,
					uint8_t padding,
					uint8_t* InitialVector);

	uint8_t decrypt(uint16_t keySize,
					uint8_t* password,
					uint16_t password_length,
					uint8_t encrypted_message[],
					uint8_t size,
					uint8_t original_message[],
					uint16_t *original_size,
					uint8_t mode,
					uint8_t padding,
					uint8_t* InitialVector);

	//! It decrypts a message
    /*!
	\param keySize : Size of the key, this value can be 128, 192 or 256
    \param password : Password choose by user in char*
    \param encrypted_message : Message encrypted
	\param uint8_t size : size of the encrypted message
    \param original_message : Message wich is going to decrypted
	\param uint16_t *original_size : size of the original message
    \param mode : mode of block cipher
    \param padding : mode of to fill the incomplete blocks
    \return void
     */
	void decrypt(	uint16_t keySize,
					char* password,
					uint8_t encrypted_message[],
					uint8_t size,
					uint8_t original_message[],
					uint16_t *original_size,
					uint8_t mode,
					uint8_t padding);

};

/// END FUNCTIONS //////////////////////////////////////////////////////

extern WaspAES AES;

#endif
