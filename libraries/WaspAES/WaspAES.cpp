/*
 *  Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.3
 *  Design:			David Gascón
 *  Implementation:	Alvaro Gonzalez, Yuri Carmona
 *
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspAES.h"

/*******************************************************************************
 * Class methods
*******************************************************************************/

/// Constructors ///////////////////////////////////////////////////////
WaspAES::WaspAES()
{	
	Seed = 0x00;
	Magic = 0x5c;
}

/// Private Methods ////////////////////////////////////////////////////////////


/*
 * 
 * 
 */
uint8_t WaspAES::random8bit()
{

  Seed = derechazo(Seed, 3);
  Seed += Magic;

  return Seed;
}



/*
 * 
 * 
 */
uint8_t WaspAES::derechazo(uint8_t val, int nr)
{
  uint8_t tmp;
  while(nr--)
  {
  tmp = val & 1;
  tmp <<= 1;
  val |= tmp;
  }
  return val;
}



/*
 * Its refers to encryption messages with ECB mode
 * In ECB mode is separated from message in blocks of 16 bytes and cipher each 
 * one individually
 * 
 * 'original_data' is the unencrypted message
 * 'size' is  the number of bytes that should occupy the message 
 * 'keySize' is the size of the key, this value can be 128, 192 or 256
 * 
 */
void WaspAES::ECBEncrypt(	uint8_t *original_data
							, uint16_t size
							, uint16_t keySize)
{

	// In ECB mode is separated from message in blocks of 
	// 16 bytes and cipher each one individually
	uint16_t index,index2;
	index = 0;
	index2 = 0;
	while( index < size )
	{
		// get the first 16-Byte block from original 
		// message to be encrypted separately 
		for (int i =0; i<16;i++)
		{
			block_data[i] = original_data[index];
			index++;
		}
    
		// Encrypt the selected 16-Byte block
		switch(keySize)
		{
			case 128:						
					aes128_enc(block_data, &ctx128);
					break;
			case 192:
					aes192_enc(block_data, &ctx192);
					break;
			case 256:
					aes256_enc(block_data, &ctx256);
					break;
		}	
		
		for (int i = 0; i<16;i++)
		{
			original_data[index2] = block_data[i];
			index2++;
		}
	}
}


/*
 * ECBDecrypt
 * 
 * Its refers to decryption messages with ECB mode
 * In ECB mode is separated from message in blocks of 16 bytes and 
 * decodec each one individually
 * 
 * 'original_data' is the encrypted message
 * 'size' is  the number of bytes that should occupy the message 
 * 'keySize' is the size of the key, this value can be 128, 192 or 256
 * 
 */
void WaspAES::ECBDecrypt(	uint8_t *original_data
							, uint16_t size
							, uint16_t keySize)
{
	// In ECB mode the message is separated into blocks of 
	// 16 bytes and cipher each one individually so in decryption, 
	// each 16-Byte block has to be decrypted
	uint16_t index,index2;
	index = 0;
	index2 = 0;

	while(index<size)
	{
		// copy a new 16-byte block from encrypted message
		for (int i =0; i<16; i++)
		{
			block_data[i] = original_data[index];
			index++;
		}
      
		// Decrypt depending on the key size
		switch(keySize)
		{
			case 128:
					aes128_dec(block_data, &ctx128);
					break;
			case 192:
					aes192_dec(block_data, &ctx192);
					break;
			case 256:
					aes256_dec(block_data, &ctx256);
					break;
		}
      
		for (int i = 0; i<16; i++)
		{
			original_data[index2] = block_data[i];
			index2++;
		}
	}
}

/*
 * CBCEncrypt - Encrypt message using CBC mode
 * 
 * In CBC mode the message is divided into blocks of 16 bytes, to 1 block
 * Applied to the XOR and calculated its block cipher with block
 * Encryption XOR obtained is applied to the second data block in clear
 * And the result is encrypted with AES given, the result will be the 2nd block
 * Encryption, so on.
 * 
 * This function is:
 * 	1 - separated data block of 16 bytes,
 * 	2 - XOR operation is performed with the IV / block precesor
 * 	3 - was called to the encryption function
 * 	4 - Once all blocks are encrypted will join
 * 	5 - forms the encrypted message and returns
 * 
 */
void WaspAES::CBCEncrypt(	uint8_t *original_data,
							uint16_t size,
							uint8_t *InitialVector,
							uint16_t keySize)
{
	uint8_t IV[16];
	uint8_t Plain_text[16];
	uint8_t Previous_block[16];

	uint16_t index,index2;
	index = 0;
	index2 = 0;

	//Assign Initial Vector to IV variable
	assignBlock(IV,InitialVector);

	while( index < size )
	{
		// Copy 16B block
		for (int i =0; i<16 ; i++)
		{
			Plain_text[i] = original_data[index];
			index++;
		}
		
		// Perform XOR with corresponding IV block
		if ( index == 16)
		{
			// the first time the XOR is done with the Original IV
			XOR( Plain_text, IV, block_data);
		}
		else 
		{
			// the rest of the times, the XOR is done with 
			// the previous encrypted block
			XOR( Plain_text, Previous_block, block_data);
		}

		switch(keySize)
		{
			case 128:
				aes128_enc(block_data, &ctx128);
				break;
			case 192:
				aes192_enc(block_data, &ctx192);
				break;
			case 256:
				aes256_enc(block_data, &ctx256);
				break;
		}

		assignBlock( Previous_block, block_data);

		for (int i = 0; i<16;i++)
		{
			original_data[index2] = block_data[i];
			index2++;
		}
	}
}

/*
 * CBCDecrypt - Decrypt message using CBC mode 
 * 
 * In CBC mode the message is divided into blocks of 16 bytes, to 1 block
 * Applied to the XOR and calculated its block cipher with block
 * Encryption XOR obtained is applied to the second data block in clear
 * And the result is encrypted with AES given, the result will be the 2nd block
 * Encryption, so on.
 * 
 * This function is:
 * 	1 - separated data block of 16 bytes,
 * 	2 - XOR operation is performed with the IV / block precesor
 * 	3 - was called to the encryption function
 * 	4 - Once all blocks are encrypted will join
 * 	5 - forms the encrypted message and returns
 * 
 */
void WaspAES::CBCDecrypt(	uint8_t *original_data,
							uint16_t size,
							uint8_t *InitialVector,
							uint16_t keySize)
{
	uint8_t IV[16];
	uint8_t Plain_text[16];
	uint8_t Previous_block[16];

	uint16_t index,index2;
	index = 0;
	index2 = 0;

	//Assign Initial Vector to IV variable
	assignBlock(IV,InitialVector);

	while( index < size )
	{
		// Copy a 16B block from the encrypted message
		for (int i =0; i<16;i++)
		{
			block_data[i] = original_data[index];
			index++;
		}		

		switch(keySize)
		{
			case 128:
				aes128_dec(block_data, &ctx128);
				break;
			case 192:
				aes192_dec(block_data, &ctx192);
				break;
			case 256:
				aes256_dec(block_data, &ctx256);
				break;
		}

		if (index == 16)
		{
			XOR( block_data, IV, Plain_text);
		}
		else 
		{
			XOR( block_data, Previous_block, Plain_text);
		}

		// Copy a 16B block of the original encrypted message to be 
		// used as IV in the following decrypted block
		for (int i = 0; i<16 ; i++)
		{
			block_data[i] = original_data[i+index-16];
		}
		
		assignBlock( Previous_block, block_data);

		for (int i = 0; i<16;i++)
		{
			original_data[index2] = Plain_text[i];
			index2++;
		}
	}
}

/*
 * paddingEncrypt
 * 
 * It refers to padding of incomplete blocks in encryption process
 * When the length of a message is not multiple of 16, blocks should be filled 
 * up to a number multiple of 16.  
 * 
 * Padding the last block.
 * Option padding mode:
 * 	1 - PKCS5
 * 	2 - ZEROS
 */
void WaspAES::paddingEncrypt(	uint8_t *original_data
								, uint16_t size
								, uint16_t size_original
								, uint8_t mode)
{
	uint8_t padding;

	// Encrypt
	if (mode == PKCS5)
	{
		////////////////////////////////////////////////////////////////////////
		// Padding #PKSC
		//
		// if 1 mod k = k-1  -- added -- 01
		// if 1 mod k = k-2  -- added -- 02 02
		// if 1 mod k = k-3  -- added -- 03 03 03
		// if 1 mod k = k-4  -- added -- 04 04 04 04
		// if 1 mod k = k-5  -- added -- 05 05 05 05 05
		// if 1 mod k = k-6  -- added -- 06 06 06 06 06 06
		// ...
		// if 1 mod k = 0    -- added -- 0k 0k 0k ..
		////////////////////////////////////////////////////////////////////////

		if (size_original < size)
		{
			padding = size_original % 16;
			
			// If the block is completed not padding
			for (uint16_t i = size_original; i < size; i++)
			{
				switch(padding)
				{
					case 1:
						original_data[i] = 0x0F;
						break;
					case 2:
						original_data[i] = 0x0E;
						break;
					case 3:
						original_data[i] = 0x0D;
						break;
					case 4:
						original_data[i] = 0x0C;
						break;
					case 5:
						original_data[i] = 0x0B;
						break;
					case 6:
						original_data[i] = 0x0A;
						break;
					case 7:
						original_data[i] = 0x09;
						break;
					case 8:
						original_data[i] = 0x08;
	    				  break;
					case 9:
						original_data[i] = 0x07;
						break;
					case 10:
						original_data[i] = 0x06;
						break;
					case 11:
						original_data[i] = 0x05;
						break;
					case 12:
						original_data[i] = 0x04;
						break;
					case 13:
						original_data[i] = 0x03;
						break;
					case 14:
						original_data[i] = 0x02;
						break;
					case 15:
						original_data[i] = 0x01;
						break;
					case 0:
						original_data[i] = 0x10;
						break;
				}
			}
		}

    } 
    else if( mode == ZEROS ) 
    { 
		// ZEROS

		////////////////////////////////////////////////////////////////////////
		// EL METODO DE RELLENADO - ZEROS
		//
		// Size = Teoric original Message
		// size_original = original message size
		// El tamaño del mensaje es menor que el tamaño del los bloques.
		// se rellena con ceros hasta completar el bloque(16 bytes)
        ////////////////////////////////////////////////////////////////////////
		if (size_original < size)
		{
			// Fill with zeros
			for (uint16_t i = size_original; i < size; i++)
			{
				original_data[i] = 0x00;
			}
		}
    } 
}

/*
 *
*/
o_message WaspAES::paddingDecrypt(	uint8_t *original_data
									, uint16_t size
									, uint8_t mode)
{
	o_message m;
	uint8_t index = size-1;
	uint16_t count = 0;
  
	// Decrypt
	if (mode == PKCS5) 
	{
		// PKCS5
		while (original_data[index] == original_data[size-1] )
		{
			index--;
			count++;
		}

		for (uint16_t x = 0; x < (size-count); x++)
		{
			m.txt[x] = original_data[x];
		}

		m.size_txt = size-count;
		return m;

	}
	else if (mode == ZEROS) 
	{
		// ZEROS
		while (original_data[index] == 0x00 )
		{
			index--;
			count++;
		}
		m.size_txt = size - count;

		for (uint8_t x = 0; x < m.size_txt; x++)
		{
			m.txt[x] = original_data[x];
		}
		return m;
	}

	return m;
}

/*
 *
*/
void WaspAES::XOR(uint8_t *a, uint8_t *b, uint8_t *c)
{
  for(int i = 0; i < 16; i++)
  {
    c[i] = a[i] ^ b[i];
  }
}

/*
 *
*/
void WaspAES::assignBlock(uint8_t *a, uint8_t *b)
{
  for(int i=0; i < 16; i++){
    a[i] = b[i];
  }
}



/* sizeOfBlocks
 * 
 * Calculate length in Bytes of the encrypted message. This is calculated thanks 
 * to the original message in 'message'.
 *
 */
uint16_t WaspAES::sizeOfBlocks(char* message)
{
	uint16_t length;	
	length = strlen(message);
	return sizeOfBlocks(length);
}



/* sizeOfBlocks
 * 
 * Calculate length in Bytes of the encrypted message. This is calculated thanks 
 * to the original message in 'message'.
 *
 */
uint16_t WaspAES::sizeOfBlocks(uint16_t length)
{
	float aux;	
	
	aux = (length-1) / 16;
	
	if (aux == 0)
	{
		return 16;
	}
	else 
	{
		return aux*16+16;
	}
}


/*
 * 	init 
 * 
 * This function sets up the password filling with zeros until it reacehs the 
 * proper length depending on the 'keySize'. The possibilities are 128bits, 
 * 192bits and 256bits.
 * 
 * After padding with zeros, then an initialization function is called in order 
 * to create all the round keys which are stored in the proper context struct
 * 
 */ 
uint8_t WaspAES::init(char* password, uint16_t keySize)
{	
	return init((uint8_t*)password, strlen(password), keySize);
}

/*
 * 	init 
 * 
 * This function sets up the password filling with zeros until it reacehs the 
 * proper length depending on the 'keySize'. The possibilities are 128bits, 
 * 192bits and 256bits.
 * 
 * After padding with zeros, then an initialization function is called in order 
 * to create all the round keys which are stored in the proper context struct
 * 
 */ 
uint8_t WaspAES::init(uint8_t* password, uint16_t length, uint16_t keySize)
{
	uint8_t key[32];
	memset( key, 0x00, sizeof(key) );
	
	// Key Initialition with ZEROS until the proper length
	switch(keySize)
	{
		case 128:
			// key size to be used: 16 Bytes
			if (length < 17) 
			{
				for (uint16_t i=0; i < length;i++)
				{
					key[i] = password[i];
				}
				if (length < 16)
				{
					for(int aux = length; aux < 16; aux++)
					{
						key[aux] = 0;
					}
				}
			}
			// Once the password is padded with zeros
			// generate the round keys from the 128 bit key 
			aes128_init(key, &ctx128);	
			break;

		case 192:
			// key size to be used: 24 Bytes
			if (length < 25) 
			{
				for (uint16_t i = 0; i < length;i++)
				{
					key[i] = password[i];
				}
				if (length < 24)
				{
					for(int aux = length; aux < 24; aux++)
					{
						key[aux] = 0;
					}
				}
			}
			// Once the password is padded with zeros
			// generate the round keys from the 192 bit key 
			aes192_init(key, &ctx192);
			break;

		case 256:
			// key size to be used: 32 Bytes
			if (length < 33) 
			{
				for (uint16_t i = 0; i < length;i++)
				{
					key[i] = password[i];
				}
				if (length < 32)
				{
					for(int aux = length; aux < 32; aux++)
					{
						key[aux] = 0;
					}
				}
			}
			// Once the password is padded with zeros
			// generate the round keys from the 256 bit key 
			aes256_init(key, &ctx256);
			break;

		default:
			return 0;
	}
	return 1;

}

/// Public Methods /////////////////////////////////////////////////////////////

/*
 * printMatrix(data,size) - print a matrix with data "data" and size "size"
 * Parameters:
 *    data: Data of Matrix
 *    size: Size of Matrix
*/
void WaspAES::printMatrix(uint8_t* data,uint16_t size){

  for (uint16_t x = 0; x < size; x++)
  {
    if ((x % 4) == 0)
    {
      USB.println();
    }
    USB.print(F("  "));
    USB.printHex(data[x]);
    USB.print(F("  "));
  }
  USB.println();

}

/*
 * printMessage(data,size) - print a message with data "data" and size "size"
 * Parameters:
 *    data: Data of Matrix
 *    size: Size of Matrix
*/

void WaspAES::printMessage(uint8_t* data, uint16_t size)
{
	USB.print(F(" \""));
	for (uint16_t x = 0; x < size; x++)
	{
		USB.printHex(data[x]);
	}
	USB.println(F("\""));
}

/*
 * encrypt(keySize,password,original_message,encrypted_message, mode, padding)
 * - encrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message.
 *    original_message: Plaintext message before calculating AES Algorithm
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    mode: cipher mode, two ways: ECB
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *
 * Examples:
 *  AES.encrypt(128,"libelium","Libelium",encrypted_message,ECB,PKCS5)
 *
 */
uint8_t WaspAES::encrypt(	uint16_t keySize
							, char* password
							, char original_message[]
							, uint8_t* encrypted_message
							, uint8_t mode
							, uint8_t padding)
{
	// Calculate length of the original message
	uint16_t original_length;
	original_length = strlen(original_message);

	return encrypt(	keySize,
					password,
					(uint8_t*) original_message,
					original_length,
					encrypted_message,
					mode,
					padding);	
}

/*
 * encrypt(keySize,password,original_message,encrypted_message, mode, padding)
 * - encrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message.
 *    original_message: Plaintext message before calculating AES Algorithm
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    mode: cipher mode, two ways: ECB
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *
 * Examples:
 *  AES.encrypt(128,"libelium","Libelium",encrypted_message,ECB,PKCS5)
 *
 */
uint8_t WaspAES::encrypt(	uint16_t keySize,
							char* password,
							uint8_t* original_message,
							uint16_t length,
							uint8_t* encrypted_message,
							uint8_t mode,
							uint8_t padding)
{
	// Calculate length in Bytes of the encrypted message 
	// depending on the size of the original message
	uint16_t size;
	size = sizeOfBlocks(length);
	
	uint8_t original_data[size];

	// init the password and create the round keys which are 
	// stored in the proper context attribute
	if (init(password,keySize))
	{
		// convert to uint8_t
		for (uint16_t i = 0; i < length; i++)
		{
			original_data[i] = original_message[i];
		}

		// Padding the block if the length is less than the proper size 
		if ( length < size ) 
		{
			paddingEncrypt(	original_data,
							size,
							length,
							padding);
		}		
		
		if (mode == ECB)
		{
			ECBEncrypt( original_data, size, keySize);
		}
				
		// copy result
		for (uint16_t i=0; i < size;i++)
		{
			encrypted_message[i] = original_data[i];
		}

		return 1;

	}
	else
	{
		return 0;
	}
}


/*
 * encrypt(keySize,password,original_message,encrypted_message, mode, padding,
 *          initialVector) - encrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message.
 *    original_message: Plaintext message before calculating AES Algorithm
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    mode: cipher mode, CBC
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *    initialVector:
 *
 * Examples:
 *  AES.encrypt(128,"libelium","Libelium",encrypted_message,CBC,PKCS5,IV)
 *
 */
uint8_t WaspAES::encrypt(	uint16_t keySize,
							char* password,
							char original_message[],
							uint8_t* encrypted_message,
							uint8_t mode,
							uint8_t padding,
							uint8_t* initialVector)
{
	// Calculate length of the original message
	uint16_t original_length;
	original_length = strlen(original_message);

	return encrypt(	keySize,
					password,
					(uint8_t*) original_message,
					original_length,
					encrypted_message,
					mode,
					padding,
					initialVector);	
}


/*
 * encrypt(keySize,password,original_message,encrypted_message, mode, padding,
 *          initialVector) - encrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message.
 *    original_message: Plaintext message before calculating AES Algorithm
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    mode: cipher mode, CBC
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *    initialVector:
 *
 */
uint8_t WaspAES::encrypt(	uint16_t keySize,
							char* password,
							uint8_t* original_message,
							uint16_t length,
							uint8_t* encrypted_message,
							uint8_t mode,
							uint8_t padding,
							uint8_t* initialVector)
{
	// Calculate length in Bytes of the encrypted message 
	// depending on the size of the original message
	uint16_t size;
	size = sizeOfBlocks(length);
	
	uint8_t original_data[size];

	if ( init(password,keySize) )
	{
		// Convert original message to uint8_t format
		for (uint16_t i = 0; i < length; i++)
		{
			original_data[i] = original_message[i];
		}
    
		if ( length < size ) 
		{ 
			// Se necesita rellenar el bloque
			paddingEncrypt( original_data, size, length, padding);
		}

		if (mode == CBC)
		{
			CBCEncrypt(original_data,size,initialVector,keySize);
		}

		// Copy result
		for (uint16_t i=0; i < size;i++)
		{
			encrypted_message[i] = original_data[i];
		}
		return 1;

	}
	else
	{
		return 0;
	}
}



/*
 * decrypt(uint16_t keySize,char* password,uint8_t encrypted_message[], uint8_t size,
          uint8_t original_message[], uint16_t *original_size,
          uint8_t mode,uint8_t padding,uint8_t* InitialVector)
           - decrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message. *
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    size: number of blocks
 *    original_message: Plaintext message after decrypt ciphertext
 *    original_size: size of message after decrypted.
 *    mode: cipher mode, CBC
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *    initialVector:
 *
 * Examples:
 *  AES.decrypt(128,"libelium","Libelium",8,original_message,8,CBC,PKCS5,IV)
 *
 */
uint8_t WaspAES::decrypt(	uint16_t keySize,
							char* password, 
							uint8_t encrypted_message[], 
							uint8_t size, 
							uint8_t original_message[], 
							uint16_t *original_size, 
							uint8_t mode, 
							uint8_t padding,
							uint8_t* InitialVector)
{
	o_message decrypted_message;

	if (init(password,keySize))
	{
		uint8_t original_data[size];

		for (uint16_t x = 0; x < size; x++)
		{
			original_data[x] = encrypted_message[x];
		}
		if (mode == CBC)
		{
			CBCDecrypt(original_data,size,InitialVector,keySize);
		}

		decrypted_message = paddingDecrypt(original_data,size,padding);

		for (uint8_t k = 0; k<decrypted_message.size_txt; k++)
		{
			original_message[k] = decrypted_message.txt[k];
		}

		*original_size = decrypted_message.size_txt;
		return 1;

	}
	else
	{
		return 0;
	}
}




/*
 * decrypt(uint16_t keySize,char* password,uint8_t encrypted_message[], uint8_t size,
          uint8_t original_message[], uint16_t *original_size,
          uint8_t mode,uint8_t padding,uint8_t* InitialVector)
           - decrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message. *
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    size: number of blocks
 *    original_message: Plaintext message after decrypt ciphertext
 *    original_size: size of message after decrypted.
 *    mode: cipher mode, CBC
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *    initialVector:
 *
 * Examples:
 *  AES.decrypt(128,"libelium","Libelium",8,original_message,8,CBC,PKCS5,IV)
 *
 */
uint8_t WaspAES::decrypt(	uint16_t keySize,
							uint8_t* password, 
							uint16_t password_length, 
							uint8_t encrypted_message[], 
							uint8_t size, 
							uint8_t original_message[], 
							uint16_t *original_size, 
							uint8_t mode, 
							uint8_t padding,
							uint8_t* InitialVector)
{
	o_message decrypted_message;

	if (init(password, password_length, keySize))
	{
		uint8_t original_data[size];

		for (uint16_t x = 0; x < size; x++)
		{
			original_data[x] = encrypted_message[x];
		}
		if (mode == CBC)
		{
			CBCDecrypt(original_data,size,InitialVector,keySize);
		}
		else if (mode == ECB)
		{
			ECBDecrypt(original_data,size,keySize);
		}

		decrypted_message = paddingDecrypt(original_data,size,padding);

		for (uint8_t k = 0; k<decrypted_message.size_txt; k++)
		{
			original_message[k] = decrypted_message.txt[k];
		}

		*original_size = decrypted_message.size_txt;
		return 1;

	}
	else
	{
		return 0;
	}
}


/*
 * decrypt(uint16_t keySize,char* password,uint8_t encrypted_message[], uint8_t size,
          uint8_t original_message[], uint16_t *original_size,
          uint8_t mode,uint8_t padding,uint8_t* InitialVector)
           - decrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message. *
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    size: number of blocks
 *    original_message: Plaintext message after decrypt ciphertext
 *    original_size: size of message after decrypted.
 *    mode: cipher mode, CBC
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *
 */
void WaspAES::decrypt(	uint16_t keySize,
						char* password,
						uint8_t encrypted_message[],
						uint8_t size,
						uint8_t original_message[],
						uint16_t *original_size,
						uint8_t mode,
						uint8_t padding)
{
	o_message decrypted_message;
		
	// init the password and create the round keys which are 
	// stored in the proper context attribute
	if (init(password,keySize))
	{
		uint8_t original_data[size];
		
		// copy encrypted input message
		for (uint16_t x = 0; x < size; x++)
		{
			original_data[x] = encrypted_message[x];
		}
		
		// perform decryption
		if (mode == ECB)
		{
			ECBDecrypt(original_data,size,keySize);
		}

		decrypted_message = paddingDecrypt(original_data,size,padding);

		for (uint8_t k = 0; k<decrypted_message.size_txt; k++)
		{
			original_message[k] = decrypted_message.txt[k];
		}
		
		*original_size = decrypted_message.size_txt;
	}
	else
	{
		USB.println(F("Wrong Key Size"));
	}


}



/*
 * 
 * 
 */
void WaspAES::seedGenerator(uint8_t* seed)
{
	seed[0] = random8bit();
	seed[1] = random8bit();
}
  
  
// Preinstantiate Objects //////////////////////////////////////////////////////
WaspAES AES = WaspAES();
