/*
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
 *  Implementation:	Alvaro Gonzalez
 *
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

/*******************************************************************************
 * Class methods
*******************************************************************************/

/// Constructors ///////////////////////////////////////////////////////
WaspAES::WaspAES(){
   // nothing to do here
}

/// Private Methods ////////////////////////////////////////////////////////////



uint8_t WaspAES::random8bit()
{

  Seed = derechazo(Seed, 3);
  Seed += Magic;

  return Seed;
}

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

void WaspAES::ECBEncrypt(uint8_t *original_data,uint16_t size,uint16_t keySize){

// In ECB mode is separated from message in blocks of 16 bytes and cipher each one individually

  uint16_t index,index2;
  index = 0;
  index2 = 0;
  while( index < size ){

    for (int i =0; i<16;i++){
      block_data[i]=original_data[index];
      index++;
    }
    // Encrypt
    switch(keySize){
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

    for (int i = 0; i<16;i++){
      original_data[index2] = block_data[i];
      index2++;
    }
  }
}

/*
 *
*/
void WaspAES::ECBDecrypt(uint8_t *original_data,uint16_t size,uint16_t keySize){

  // In ECB mode is separated from message in blocks of 16 bytes and cipher each one individually

  uint16_t index,index2;
  index = 0;
  index2 = 0;

  while(index<size){

      for (int i =0; i<16;i++){
	block_data[i]=original_data[index];
	index++;
      }
      // Decrypt
      switch(keySize){
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
      for (int i = 0; i<16;i++){
	original_data[index2] = block_data[i];
	index2++;
      }
  }
}

/*
 *
*/
void WaspAES::CBCEncrypt(uint8_t *original_data,uint16_t size, uint8_t *InitialVector,uint16_t keySize){
///////////////////////////
// In CBC mode the message is divided into blocks of 16 bytes, to 1 block
// Applied to the XOR and calculated its block cipher with block
// Encryption XOR obtained is applied to the second data block in clear
// And the result is encrypted with AES given, the result will be the 2nd block
// Encryption, so on.
//
// This function is:
// 1 - separated data block of 16 bytes,
// 2 - XOR operation is performed with the IV / block precesor
// 3 - was called to the encryption function
// 4 - Once all blocks are encrypted will join
// 5 - forms the encrypted message and returns
//
///////////////////////////

  uint8_t IV[16];
  uint8_t Plain_text[16];
  uint8_t Previous_block[16];

  uint16_t index,index2;
  index = 0;
  index2 = 0;

  //Assign Initial Vector to IV variable
  assignBlock(IV,InitialVector);

  while(index<size){
    // Encrypt
    for (int i =0; i<16;i++){
      Plain_text[i]= original_data[index];
      index++;
    }
    if (index == 16){
      XOR(Plain_text,IV,block_data);
    }else {
      XOR(Plain_text,Previous_block,block_data);
    }

    switch(keySize){
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

    assignBlock(Previous_block,block_data);

    for (int i = 0; i<16;i++){
      original_data[index2] = block_data[i];
      index2++;
    }
  }
}

/*
 *
*/
void WaspAES::CBCDecrypt(uint8_t *original_data,uint16_t size, uint8_t *InitialVector,uint16_t keySize){
///////////////////////////
// In CBC mode the message is divided into blocks of 16 bytes, to 1 block
// Applied to the XOR and calculated its block cipher with block
// Encryption XOR obtained is applied to the second data block in clear
// And the result is encrypted with AES given, the result will be the 2nd block
// Encryption, so on.
//
// This function is:
// 1 - separated data block of 16 bytes,
// 2 - XOR operation is performed with the IV / block precesor
// 3 - was called to the encryption function
// 4 - Once all blocks are encrypted will join
// 5 - forms the encrypted message and returns
//
///////////////////////////


  uint8_t IV[16];
  uint8_t Plain_text[16];
  uint8_t Previous_block[16];

  uint16_t index,index2;
  index = 0;
  index2 = 0;

  //Assign Initial Vector to IV variable
  assignBlock(IV,InitialVector);

  while(index < size){
    //Decrypt
    for (int i =0; i<16;i++){
      block_data[i]= original_data[index];
      index++;
    }

    assignBlock(Previous_block,block_data);

    switch(keySize){
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

    if (index == 16){
      XOR(block_data,IV,Plain_text);
    }else {
      XOR(block_data,Previous_block,Plain_text);
    }

    for (int i = 0; i<16;i++){
      original_data[index2] = Plain_text[i];
      index2++;
    }
  }
}

/*
 *
*/
void WaspAES::paddingEncrypt(uint8_t *original_data,uint16_t size,uint16_t size_original,uint8_t mode){
// Padding the last block
// Opcion padding mode:
// 		1 - PKCS5
//		2 - ZEROS


  uint8_t padding;

  // Encrypt
  if (mode == PKCS5){

    ///////////////////////////////////////////////////////////////////////////////////////
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
    ///////////////////////////////////////////////////////////////////////////////////////

    if (size_original < size){

      padding = size_original % 16;
      // If the block is completed not padding
      for (uint16_t i = size_original; i < size; i++){

	  switch(padding){
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

    } else if( mode == ZEROS ) { // ZEROS

	///////////////////////////////////////////////////////////////////////
	// EL METODO DE RELLENADO - ZEROS
	//
	// Size = Teoric original Message
	// size_original = original message size
	// El tamaño del mensaje es menor que el tamaño del los bloques.
	// se rellena con ceros hasta completar el bloque(16 bytes)
        ///////////////////////////////////////////////////////////////////////
	if (size_original < size){
	  // Rellenar con ceros
	  for (uint16_t i = size_original; i < size; i++){
	    original_data[i] = 0x00;
	  }

	}
      } else if (mode == X923){
	///////////////////////////////////////////////////////////////////////
	// EL METODO DE RELLENADO - Ansi X.923
	//
	// Los bytes faltantes son rellenados con ceros y el ultimo byte indica
	// el número de ceros añadidos
	uint8_t count=0;
	if (size_original < size-1){
	  // Rellenar con ceros menos el ultimo byte
	  for (uint16_t i = size_original; i < size-1; i++){
	    original_data[i] = 0x00;
	    count++;
	  }
	    switch(count){
	      case 1:
		count = 0x01;
		break;
	      case 2:
		count = 0x02;
		break;
	      case 3:
		count = 0x03;
		break;
	      case 4:
		count = 0x04;
		break;
	      case 5:
		count = 0x05;
		break;
	      case 6:
		count = 0x06;
		break;
	      case 7:
		count = 0x07;
		break;
	      case 8:
		count = 0x08;
		break;
	      case 9:
		count = 0x09;
		break;
	      case 10:
		count = 0x0A;
		break;
	      case 11:
		count = 0x0B;
		break;
	      case 12:
		count = 0x0C;
		break;
	      case 13:
		count = 0x0D;
		break;
	      case 14:
		count = 0x0E;
		break;
	      case 15:
		count = 0x0F;
		break;
	    }
	    original_data[size-1] = count;
	}
      }
}

/*
 *
*/
o_message WaspAES::paddingDecrypt(uint8_t *original_data,uint16_t size,uint8_t mode){
  o_message m;
  uint8_t index = size-1;
  uint16_t count = 0;
  // Decrypt
  if (mode == PKCS5) {
    // PKCS5
    while (original_data[index] == original_data[size-1] ){
      index--;
      count++;
    }

    for (uint16_t x = 0; x < (size-count); x++){
       m.txt[x] = original_data[x];
    }

    m.size_txt = size-count;
    return m;

  }else if (mode == ZEROS) {
    // ZEROS

    while (original_data[index] == 0x00 ){
      index--;
      count++;
    }
    m.size_txt = size - count;

    for (uint8_t x = 0; x < m.size_txt; x++){
       m.txt[x] = original_data[x];
    }
    return m;

  }

  return m;
}

/*
 *
*/
void WaspAES::XOR(uint8_t *a, uint8_t *b, uint8_t *c){
  for(int i = 0; i < 16; i++){
    c[i] = a[i] ^ b[i];
  }
}

/*
 *
*/
void WaspAES::assignBlock(uint8_t *a, uint8_t *b){
  for(int i=0; i < 16; i++){
    a[i] = b[i];
  }
}

/*
 *
*/
uint8_t WaspAES::sizeOfBlocks(char* message){

  uint8_t lenght;
  float aux;

  lenght = strlen(message);

  aux = lenght / 16;

  if (aux == 0){
    return 16;
  }else {
    return aux*16+16;
  }
}

/*
 *
*/
uint8_t WaspAES::init(char* Password, uint16_t keySize){
  uint8_t* key;

  // Key Initialition
  switch(keySize){
    case 128:
      key = (uint8_t*) calloc(16,sizeof(uint8_t));
      if (strlen(Password) < 17) {
      	for (uint16_t i=0; i < strlen(Password);i++){
      	  key[i] = Password[i];
      	}
      	if (strlen(Password) < 16){
      	  for(int aux = strlen(Password); aux < 16; aux++){
      	    key[aux] = 0;
      	  }
      	}
      }
    	aes128_init(key, &ctx128);
      break;

    case 192:
      key = (uint8_t*) calloc(24,sizeof(uint8_t));
      if (strlen(Password) < 25) {
      	for (uint16_t i = 0; i < strlen(Password);i++){
      	  key[i] = Password[i];
      	}
      	if (strlen(Password) < 24){
      	  for(int aux = strlen(Password); aux < 24; aux++){
      	    key[aux] = 0;
      	  }
      	}
      }
      aes192_init(key, &ctx192);
      break;

    case 256:

      key = (uint8_t*) calloc(32,sizeof(uint8_t));
      if (strlen(Password) < 33) {
      	for (uint16_t i = 0; i < strlen(Password);i++){
      	  key[i] = Password[i];
      	}
      	if (strlen(Password) < 32){
      	  for(int aux = strlen(Password); aux < 32; aux++){
      	    key[aux] = 0;
      	  }
      	}
      }
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
    USB.print("  ");
    USB.printHex(data[x]);
    USB.print("  ");
  }
  USB.println();

}

/*
 * printMessage(data,size) - print a message with data "data" and size "size"
 * Parameters:
 *    data: Data of Matrix
 *    size: Size of Matrix
*/

void WaspAES::printMessage(uint8_t* data, uint16_t size){
  USB.print(" \"");
  for (uint16_t x = 0; x < size; x++)
  {
	USB.printHex(data[x]);
  }
  USB.println("\"");
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
uint8_t WaspAES::encrypt(uint16_t KeySize,char* Password,char original_message[],uint8_t* encrypted_message,uint8_t mode,uint8_t padding){

  // Varibales Declaration
  uint16_t size;
  size = sizeOfBlocks(original_message);
  uint8_t original_data[size];


  if (init(Password,KeySize)){
    // convert to uint8_t
    for (uint16_t i = 0; i < strlen(original_message); i++){
      original_data[i] = original_message[i];
    }

    // Padding the block??
    if (strlen(original_message) < size ) {
      paddingEncrypt(original_data,size,strlen(original_message),padding);
    }

    if (mode == ECB){
      ECBEncrypt(original_data,size,KeySize);
    }

    // convert to char
    for (uint16_t i=0; i < size+1;i++){
      encrypted_message[i] = original_data[i];
    }

    return 1;

  }else{
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
uint8_t WaspAES::encrypt(uint16_t keySize,char* password,char original_message[],uint8_t* encrypted_message,uint8_t mode,uint8_t padding,uint8_t* initialVector){

  // Variables declaration
  uint16_t size;
  size = sizeOfBlocks(original_message);
  uint8_t original_data[size];

  if (init(password,keySize)){

    // Convert original message to uint8_t format
    for (uint16_t i = 0; i < strlen(original_message); i++){
      original_data[i] = original_message[i];
    }
    if (strlen(original_message) < size ) { // Se necesita rellenar el bloque
      paddingEncrypt(original_data,size,strlen(original_message),padding);
    }

    if (mode == CBC){
       CBCEncrypt(original_data,size,initialVector,keySize);
    }

    // Convert original_data to char format
    for (uint16_t i=0; i < size+1;i++){
      encrypted_message[i] = original_data[i];
    }
    return 1;

  }else{
    return 0;
  }
}

/*
 * decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[], uint8_t size,
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
uint8_t WaspAES::decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[], uint8_t size,
		      uint8_t original_message[], uint16_t *original_size,
		      uint8_t mode,uint8_t padding,uint8_t* InitialVector){
  o_message decrypted_message;

  if (init(Password,KeySize)){

    uint8_t original_data[size];

    for (uint16_t x = 0; x < size; x++){
      original_data[x] = encrypted_message[x];
    }
     if (mode == CBC){
      CBCDecrypt(original_data,size,InitialVector,KeySize);
    }


    decrypted_message = paddingDecrypt(original_data,size,padding);

    for (uint8_t k = 0; k<decrypted_message.size_txt; k++){
       original_message[k] = decrypted_message.txt[k];
    }

    *original_size = decrypted_message.size_txt;
    return 1;

  }else{
    return 0;
  }

}
/*
 * decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[], uint8_t size,
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
 * Examples:
 *  AES.decrypt(128,"libelium","Libelium",8,original_message,8,ECB,PKCS5)
 *
 */
void WaspAES::decrypt(uint16_t KeySize,char* Password,uint8_t encrypted_message[], uint8_t size,
          uint8_t original_message[], uint16_t *original_size,
          uint8_t mode,uint8_t padding){

  o_message decrypted_message;

  if (init(Password,KeySize)){

    uint8_t original_data[size];

    for (uint16_t x = 0; x < size; x++){
      original_data[x] = encrypted_message[x];
    }
     if (mode == ECB){
      ECBDecrypt(original_data,size,KeySize);
    }

    decrypted_message = paddingDecrypt(original_data,size,padding);

    for (uint8_t k = 0; k<decrypted_message.size_txt; k++){
       original_message[k] = decrypted_message.txt[k];

    }

    *original_size = decrypted_message.size_txt;
  }else{
    USB.println("Wrong Key Size");
  }


}

 void WaspAES::seedGenerator(uint8_t* seed){

  seed[0] = random8bit();
  seed[1] = random8bit();
  }
// Preinstantiate Objects //////////////////////////////////////////////////////
WaspAES AES = WaspAES();
