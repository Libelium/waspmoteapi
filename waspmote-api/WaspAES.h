/*! \file WaspAES.h
    \brief Library for managing the encryption
    
    Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.0
    Design:			David Gascón    
    Implementation:	Alvaro Gonzalez

 */
#ifndef WaspAES_h
#define WaspAES_h 

/*******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
/*! \def ECB   
*/
/*! \def CBC   
*/
/*! \def PKCS5   
*/
/*! \def ZEROS   
*/
/*! \def X923   
*/
#define AES_MAX_DATA_GLOBAL 100
#define ECB 1
#define CBC 2
#define PKCS5 3
#define ZEROS 4
#define X923 5

static uint8_t Seed = 0x00;
static uint8_t Magic = 0x5c;

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
     
    \param original_data unencrypted message
    \param size number of bytes that should occupy the message 
    \param keySize Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void ECBEncrypt(uint8_t *original_data,uint16_t size,uint16_t keySize);
      
    //! Its refers to decryption messages with ECB mode
    /*!
      In ECB mode is separated from message in blocks of 16 bytes and 
      decodec each one individually
       
    \param original_data encrypted message
    \param size number of bytes that should occupy the message 
    \param keySize Size of the key, this value can be 128, 192 or 256
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
      
    \param original_data unencrypted message
    \param size number of bytes that should occupy the message 
    \param InitialVector Initial Vector use to cipher in CBC mode.
    \param keySize Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void CBCEncrypt(uint8_t *original_data,uint16_t size, 
               uint8_t *InitialVector,uint16_t keySize);
      

    //! It refers to decryption messages with CBC mode
    /*!
      // In CBC mode divides the message into blocks of 16 bytes, 
      at 1 block is applied to the XOR operation and calculates 
      the block cipher with block cipher obtained was applied XOR
      with the second block of data into clear and 
      the result given is encrypted with AES,
      the result will be the 2 nd block cipher, so on.
      
    \param original_data unencrypted message
    \param size number of bytes that should occupy the message 
    \param InitialVector Initial Vector use to cipher in CBC mode.
    \param keySize Size of the key, this value can be 128, 192 or 256
    \return void
    */
    void CBCDecrypt(uint8_t *original_data,uint16_t size, 
               uint8_t *InitialVector,uint16_t keySize);

    //! It refers to padding of incomplete blocks in encryption process
    /*!
    // When the length of a message is not multiple of 16,
    blocks should be filled up to a number multiple of 16. 
    
    \param original_data message without cipher
    \param size number of bytes that should occupy the message 
    \param size_original original message size, less or equal 
                  to original_data
    \param mode Padding mode. PKCS7, Zeros, X923
    \return void
    */
    void paddingEncrypt(uint8_t *original_data,uint16_t size,
               uint16_t size_original,uint8_t mode);
      

    //! It refers to padding of incomplete blocks in decryption process
    /*!
    \param original_data message without cipher
    \param size number of bytes that should occupy the message 
    \param mode Padding mode. PKCS7, Zeros, X923
    \return o_message struct to store decrypted message
    */
    o_message paddingDecrypt(uint8_t *original_data,uint16_t size,
                   uint8_t mode);

    //! It calcules XOR operation 
    /*!
    \param a 
    \param b
    \param c result of a XOR b
    */
    void XOR(uint8_t *a, uint8_t *b, uint8_t *c);
      
    void assignBlock(uint8_t *a, uint8_t *b);   
      
    uint8_t init(char* Password, uint16_t keySize);  

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
    \param data data of matrix
    \param size size of matrix
    \param void
    */
    void printMatrix(uint8_t* data,uint16_t size);

    //! It prints encrypted message
    /*!
    \param data data of matrix
    \param size size of matrix
    \param void
    */
    void printMessage(uint8_t* data,uint16_t size);
    
    //! Calculate the number of blocks occupied by the message
    /*!
    \param message
    \param number of blocks
    */
    uint8_t sizeOfBlocks(char* message);   
    
    //! It encrypts a message
    /*!
    \param KeySize Size of the key, this value can be 128, 192 or 256
    \param Password Password choose by user in char*
    \param original_message Message wich is going to encrypted
    \param encrypted_message Message encryped
    \param mode mode of block cipher
    \param padding mode of to fill the incomplete blocks
    \param InitialVector Initial Vector use to cipher in CBC mode.
    \return void
     */
    uint8_t encrypt(uint16_t KeySize,char* Password,char original_message[],
		 uint8_t* encrypted_message,uint8_t mode,uint8_t padding,
		 uint8_t* InitialVector);
    
    //! Decrypt a encrypted message
  	/*!
  	\param KeySize Size of the key, this value can be 128, 192 or 256
  	\param Password Password choose by user in char*
  	\param encrypted_message Encrypted message wich is going to decrypted
  	\param length Size of encrypted message
  	\param original_message Message decrypted 
  	\param mode mode of block cipher
  	\param padding mode of to fill the incomplete blocks
  	\param InitialVector Initial Vector use to cipher in CBC mode.
  	\return void
  	 */
    
    uint8_t decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[],
      uint8_t size,uint8_t original_message[], uint16_t *oringinal_size,
      uint8_t mode,uint8_t padding,uint8_t* InitialVector);

    //! It encrypts a message
    /*!
    \param KeySize Size of the key, this value can be 128, 192 or 256
    \param Password Password choose by user in char*
    \param original_message Message wich is going to encrypted
    \param encrypted_message Message encryped
    \param mode mode of block cipher
    \param padding mode of to fill the incomplete blocks
    \return void
     */
    uint8_t encrypt(uint16_t KeySize,char* Password,char original_message[],
      uint8_t* encrypted_message,uint8_t mode,uint8_t padding);
    
    //! Decrypt a encrypted message
    /*!
    \param KeySize Size of the key, this value can be 128, 192 or 256
    \param Password Password choose by user in char*
    \param encrypted_message Encrypted message wich is going to decrypted
    \param length Size of encrypted message
    \param original_message Message decrypted 
    \param mode mode of block cipher
    \param padding mode of to fill the incomplete blocks
    \return void
     */
    
    void decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[],
      uint8_t size,uint8_t original_message[], uint16_t *oringinal_size,
      uint8_t mode,uint8_t padding);
};

/// END FUNCTIONS //////////////////////////////////////////////////////

extern WaspAES AES;

#endif
