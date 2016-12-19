/*! \file WaspRFID.cpp
 *  \brief Library for managing RFID modules
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
 *  Version:			3.0
 *  Design:				David Gascón
 *  Implementation:		Ahmad Saad, Javier Solobera
 */

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include "WaspRFID13.h"

 //***********************************************************
 // Constructor									   			 *
 //***********************************************************
 	WaspRFID::WaspRFID(){/*void constructor*/}
 //***********************************************************
 // Public Methods										     *
 //***********************************************************
	
//! Switches ON the modelue and assigns the UART
/*!
 \param uint8_t socket: The uart por used
*/ 	
void WaspRFID::ON(uint8_t socket)
{	
	// set uart
	_uart = socket;
    
	// select multiplexer
    if (_uart == SOCKET0) 	Utils.setMuxSocket0();
    if (_uart == SOCKET1) 	Utils.setMuxSocket1();
    
    // open uart
    beginSerial(RFID_RATE, _uart);
	
    // power on the socket
    PWR.powerSocket(_uart, HIGH);
    
    // update Waspmote Register
	if (_uart == SOCKET0)	WaspRegister |= REG_SOCKET0;
	if (_uart == SOCKET1)	WaspRegister |= REG_SOCKET1;

	serialFlush(_uart);
	delay(100);
	getFirmware();
	configureSAM();
}

//! Switches OFF the module and closes the UART.
/*!
*/
void WaspRFID::OFF(void)
{
	// close UART
	closeSerial(_uart);
	
	// unselect multiplexer 
    if (_uart == SOCKET0)	Utils.setMuxUSB();
    if (_uart == SOCKET1)	Utils.muxOFF1();
    
    // switch module OFF
	PWR.powerSocket(_uart, LOW);
	
	// update Waspmote Register
	if (_uart == SOCKET0)	WaspRegister &= ~(REG_SOCKET0);
	if (_uart == SOCKET1)	WaspRegister &= ~(REG_SOCKET1);

}

	
//!The goal of this command is to detect as many targets (maximum MaxTg)
//! as possible in passive mode. 
/*! 	
 \param uint8_t *UID : Card identifier pointer 
 \param uint8_t *ATQ : Answer to Request pointer. 
 \return Number of targets detected
*/  
uint8_t WaspRFID::init(uint8_t *UID , uint8_t *ATQ)   //! Request InListPassive 
{
	USB.flush();

	dataTX[0] = 0x04; // Length
	lengthCheckSum(dataTX); // Length Checksum
	dataTX[2] = HOSTTOPN532;
	dataTX[3] = INLISTPASSIVETARGET; // Code
	dataTX[4] = 0x01; //MaxTarget
	dataTX[5] = 0x00; //BaudRate = 106Kbps
	dataTX[6] = 0x00; // Clear checkSum position
	checkSum(dataTX); 
	
	sendTX(dataTX , 7 ,23);	
	
	for (int i = 17; i < (21) ; i++)
	{
		_UID[i-17] = dataRX[i];
		 UID[i-17] = _UID[i-17];
	}
	
	ATQ[0] = dataRX[13];
	ATQ[1] = dataRX[14];
	
	if ((dataRX[9]== 0xD5) & (dataRX[10] == 0x4B) & (dataRX[11] == 0x01)) {		 
		return 0;       
	} else {
		return 1;
	}
}

//!A block must be authenticated before read and write operations 
/*! 	
 \param  uint8_t blockAddress: The block to be authenticated.
 \param  uint8_t keyAcces: A vector pointer with the keyAcces needed to autenticate.
 \return 0 on success, 1 otherwise.
*/	 
uint8_t WaspRFID::authenticate(uint8_t *UID, uint8_t blockAddress, uint8_t *keyAccess)
{
	dataTX[0] = 0x0F;
	lengthCheckSum(dataTX);
	dataTX[2] = HOSTTOPN532;
	dataTX[3] = INDATAEXCHANGE; // inDataEchange
	dataTX[4] = 0x01; //Number of targets
	dataTX[5] = AUTH_WITH_KEYA; // Authentication code
	dataTX[6] = blockAddress;

	for (int i = 0; i<6 ; i++) {
		dataTX[i + 7] = keyAccess[i];
	}

	dataTX[13] = UID[0];  
	dataTX[14] = UID[1];
	dataTX[15] = UID[2];  
	dataTX[16] = UID[3]; 

	dataTX[17] = 0x00;
	checkSum(dataTX);
	
		sendTX(dataTX , 18 ,14);
		
	if ((dataRX[9]== 0xD5) & (dataRX[10] == 0x41) & (dataRX[11] == 0x00)) {		 
		return 0;       
	} else {
		return 1;        
	}
}	         

//!The PN532 sends back the version of the embedded firmware.
 /*!
 \return 0 on success, 1 otherwise.
*/   
bool WaspRFID::getFirmware(void)
{
	printString("                  ", _uart);		
	
	serialFlush(_uart);
	memset(dataTX, 0x00, sizeof(dataTX));  
	dataTX[0] = 0x02; // Length
	lengthCheckSum(dataTX); // Length Checksum
	dataTX[2] = HOSTTOPN532; // CODE
	dataTX[3] = 0x02; //TFI
	checkSum(dataTX); //0x2A; //Checksum   

	sendTX(dataTX , 5 , 17);  
	
	USB.print(F("Your Firmware version is : "));
	
	for (int i = 11; i < (15) ; i++)
	{
		USB.printHex(dataRX[i]);
		USB.print(F(" "));
	}
	USB.println(); 
	
	serialFlush(_uart);
}

//!Write 16 bytes in address .
/*! 	
 \param  uint8_t address: the address where write  blockData. 
 \param  uint8_t blockData: A vector pointer with the information to write.
 \return 0 on success, 1 otherwise.
*/ 	
uint8_t WaspRFID::write(uint8_t address, uint8_t *blockData)  //!Writing 
{
	printString("                ", _uart);		

	dataTX[0] = 0x15;
	lengthCheckSum(dataTX); // Length Checksum
	dataTX[2] = HOSTTOPN532;
	dataTX[3] = 0x40;  //inDataEchange CODE
	dataTX[4] = 0x01;  //Number of targets
	dataTX[5] = MIFARE_WRITE; //Write Command
	dataTX[6] = address; //Address		
	
	for (int i = 0; i<16; i++) {
		dataTX[i+7] = blockData[i];
	}
	
	dataTX[23] = 0x00; 
	checkSum(dataTX);
	sendTX(dataTX , 24 ,14);  		


	 if ((dataRX[9]== 0xD5) & (dataRX[10] == 0x41) & (dataRX[11] == 0x00)) {
		return 0;
	 } else {
		return 1;
	 }
}


//!Read 16 bytes from  address .
/*! 	
 \param  uint8_t address: the address for reading. 
 \return 0 on success, 1 otherwise.
*/ 	
uint8_t WaspRFID::read(uint8_t address, uint8_t *readData) //!Reading 
{
	printString("                ", _uart);		
	
	dataTX[0] = 0x05;
	lengthCheckSum(dataTX); // Length Checksum
	dataTX[2] = HOSTTOPN532; // Code
	dataTX[3] = INDATAEXCHANGE; // Code
	dataTX[4] = 0x01; // Number of targets
	dataTX[5] = MIFARE_READ; //ReadCode
	dataTX[6] = address;  //Read address
	dataTX[7] = 0x00;
	checkSum(dataTX);

	sendTX(dataTX , 8, 30);  
	memset(readData, 0x00, sizeof(readData) );  

	if ((dataRX[9]== 0xD5) & (dataRX[10] == 0x41) & (dataRX[11] == 0x00)) {             
		for (int i = 12; i < 28; i++) {
			readData[i-12] = dataRX[i];
		}
		 return 0;
	} else { 
		 return 1;
	}
}	

//!Authenticates one card's sector and reads one block.
/*! 	
 \param uint8_t UID: pointer to UID. A vector with the card identifier. 
 \param  uint8_t keyAcces: A vector pointer with the keyAcces needed to autenticate.
 \param  uint8_t _data : a vector where stores the read data
 \param  uint8_t address: the address to read.
 \return 0 on success, 1 otherwise.

*/ 
uint8_t WaspRFID::readWithAuth( uint8_t *UID , 
								uint8_t *keyAccess , 
								uint8_t *data , 
								uint8_t address)
{
	_UID[0] = UID[0];
	_UID[2] = UID[2];
	_UID[1] = UID[1];
	_UID[3] = UID[3];
	
	authenticate(UID, address , keyAccess);
	return read(address, data);
}

//!Authenticates one card's sector and writes one block.
/*! 	
 \param uint8_t UID: pointer to UID. A vector with the card identifier. 
 \param  uint8_t keyAcces: A vector pointer with the keyAcces needed to autenticate.
 \param  uint8_t _data : data to write.
 \param  uint8_t address: the address where write  _data. 
 \return 0 on success, 1 otherwise.

*/ 
uint8_t WaspRFID::writeWithAuth(uint8_t *UID , 
								uint8_t *keyAccess , 
								uint8_t *data , 
								uint8_t address)
{
	_UID[0] = UID[0];
	_UID[2] = UID[2];
	_UID[1] = UID[1];	
	_UID[3] = UID[3];
	
	authenticate(UID, address , keyAccess);
	return write(address, data);
}	

//!Writes one card's block and checks that.
/*! 
 \param  uint8_t _data : data to write.
 \param  uint8_t address: the address where write  _data. 
*/	
uint8_t  WaspRFID::writeAndCheck(uint8_t *data, uint8_t address)
{
	uint8_t _readData[16]; 
	
	 write(address, data);
	 read(address, _readData);
	 
	return memcmp(_readData, data, 16);	
}
	
//!Authenticates one card's sector, writes one block and checks that.
/*! 	
 \param uint8_t UID: pointer to UID. A vector with the card identifier. 
 \param  uint8_t keyAcces: A vector pointer with the keyAcces needed to autenticate.
 \param  uint8_t _data : data to write.
 \param  uint8_t address: the address where write  _data. 
*/	
uint8_t WaspRFID::writeAndCheckWithAuth(uint8_t *UID, 
										uint8_t *keyAccess, 
										uint8_t *data, 
										uint8_t address)
{
	_UID[0] = UID[0];
	_UID[1] = UID[1];
	_UID[2] = UID[2];
	_UID[3] = UID[3];
	
	authenticate(UID, address , keyAccess);
	return writeAndCheck(data, address);
}
	
//!Put the module into Power Down mode in order to save power consumption.
/*! 	
 \return true on success, false otherwise.
*/ 	
uint8_t WaspRFID::powerDown(void)
{
	printString("                ", _uart);	
	
	dataTX[0] = 0x03;
	lengthCheckSum(dataTX);  // Length Checksum
	dataTX[2] = HOSTTOPN532; // Code
	dataTX[3] = POWERDOWN;   // Code
	dataTX[4] = 0x10; 	     // Wake UP mode HFU.
	dataTX[5] = 0x00; 	     // Clear checkSum byte. 

	checkSum(dataTX);

	sendTX(dataTX , 6, 12); 
	
	if ((dataRX[9]== 0xD5) & (dataRX[10] == 0x17) & (dataRX[11] == 0x00)) {		 
		return 1;       
	} else {
		return 0;        
	}
}
	
//!Wake up from power dowm mode.
/*! 	
*/ 	
void WaspRFID::wakeUp(void)
{
	printByte(PN532_WAKEUP,_uart);	
	delay(10);
}

//!Print data stored in vectors .
/*! 	
 \param  uint8_t _data: data to print
 \param  uint8_t length: length of the _data to print.
*/	
void WaspRFID::print(uint8_t * _data, uint8_t length) 
{
	for (int i = 0; i < length ; i++)
	{
		USB.printHex(_data[i]);
		USB.print(F(" "));
	}
	USB.print(F("\n"));
}	

//!It compares 2 UIDs
/*! 	
 \param  uint8_t UID1
 \param  uint8_t UID2
*/ 
uint8_t WaspRFID::equalUIDs(uint8_t *UID1 , uint8_t *UID2)
{
	if (memcmp(UID1, UID2, 4) == 0) return 0; else return 1;
}

//!Searches one UID inside one group of UIDs
/*! 	
 \param  uint8_t vCards: a vector with several Card identifiers
 \param  uint8_t UID: the Card identifier to search. 
 \param  uint8_t nCards: number of Cards. 
*/ 
int WaspRFID::searchUID(uint8_t *vCards , uint8_t  *UID, uint8_t nCards)
{
	int card = -1;
	bool ok = false;
		
	for (int i=0; i<nCards; i++) // will chek all the 4-byte groups
	{
		for (int j=0; j<4; j++) // will check each of the 4-bye groups
		{
			if (vCards[i*4 + j] == UID[j]) // check if that byte is equal to the reference
				ok = true;
			else 
			{
				ok = false;
				break;
			}
		}	
		
		if (ok == true) // when the 4-byte analysis ended, check if the state is still ok
		{
			card = i;
			break;
		}
	}
	return card; 
}

//! Convert from a string to a pointer to uint8_t's
/*!
\param char inp: the string we want to convert 
\param uint8_t outp: the transformed pointer to unit8_t's 
\return int : returns 0 on success, -1 on failure.
*/	
int WaspRFID::string2vector(char *inp, uint8_t *outp)
{
	for (int i=0; i<16; i++) 
	{
		outp[i] = '\0'; // write 0's first
	}
	
	if (sizeof(inp) > 16) 
	{
		return -1; // this is an error
	} 
	else 
	{
		for (int i=0; i<16; i++)
		{
			outp[i] = inp[i]; // write the content of inp
			if (inp[i] == '\0')
				break;
		}
		return 0;
	}
}

//! Convert from a pointer to uint8_t's to an integer 
/*!
\param char inp: the pointer to uint8_t's we want to convert
\return int : the converted integer.
*/	
int WaspRFID::vector2int(uint8_t *inp) 
{
	int length = 0; // stores the number of digits
	int outp   = 0; // stores the output

	for (int i=0; i<16; i++) {// firs, calculate the number of digits
		if (inp[i] == '\0')
			break;
		else
			length++;
	}

	for (int i=0; i < length; i++){ // iterate to add the digits
		outp = outp + (inp[i] - 48) * pow(10, (length-i-1));
	}
	
	if (length > 2) 
	{
		outp = outp + 1; // mandatory
	}
	return outp; 
}

//! Changes both keys and access conditions to one card's sector 
/*!
\param uint8_t UID: pointer to UID. A vector with the card identifier. 
\param uint8_t kelOld: the old keyAccess
\param uint8_t keyA: the new keyAcces A
\param uint8_t keyB: the new keyAccess B
\param uint8_t config: the configuration of the target 
\param uint8_t data: data to write
\param uint8_t add: address where change the keyAccess
\return uint8_t 0 success, 1 otherwise.
*/	
uint8_t WaspRFID::setKeys(uint8_t *UID,
							uint8_t *keyOld,
							uint8_t *keyA,
							uint8_t *keyB,
							uint8_t *config,
							uint8_t *data,
							uint8_t add)
{
	uint8_t state = 1; 

	if (((add+1) % 4) == 0)
	{
		state = authenticate(UID , add, keyOld);
		if (state == 0) 
		{
			for (int i = 0; i<6; i++) {
				data[i] = keyA[i];
				data[i+ 10] = keyB[i];
			}

			for (int i = 0; i<4 ; i++) {
				data[i + 6] = config[i];
			}
			state = write(add, data);
		}
	}
	return state;		
}

//***********************************************************
// Private Methods 									     *
//***********************************************************	

//!This command is used to set internal parameters of the PN532, 
 /*! 	and then to configure its behavior regarding different cases.
 \return true on success, false otherwise.
*/   
bool  WaspRFID::configureSAM(void)  //! Configure the SAM 
{
	printString("               ", _uart);		
	
	dataTX[0] = 0x05; //Length 
	lengthCheckSum(dataTX); // Length Checksum
	dataTX[2] = HOSTTOPN532;
	dataTX[3] = SAMCONFIGURATION;
	dataTX[4] = 0x01; //Normal mode
	dataTX[5] = 0x14; // TimeOUT
	dataTX[6] = 0x00; // IRQ
	dataTX[7] = 0x00; // Clean checkSum position
	checkSum(dataTX);
	
	sendTX(dataTX , 8, 13);  
			
	serialFlush(_uart);
}

//!Send data stored in dataTX
/*! 	
 \param  uint8_t dataTX : pointer to dataTX vector. 
*/ 	
void WaspRFID::sendTX(uint8_t *dataTX, uint8_t length, uint8_t outLength)
{
	printByte(PREAMBLE, _uart);
	printByte(PREAMBLE, _uart);
	printByte(STARTCODE2, _uart); 

	for (int i = 0; i<length; i++) {
		printByte(dataTX[i], _uart);
	}
		
	printByte(POSTAMBLE, _uart);			
	getACK(); 
	waitResponse();    // 1C - receive response
	getData(outLength); 
}

//!Wait for ACK response and stores it in the dataRX buffer
void WaspRFID::getACK(void)
{
	delay(5);
	waitResponse();
	
	for (int i = 0; i<5 ; i++) {		
		dataRX[i] = serialRead(_uart);
	}
}

//!Wait the response of the module
void WaspRFID::waitResponse(void)
{	
	int val = 0xFF;
	long cont = 0;
	
	while((val != PREAMBLE) && (cont < timeOut)) {
		val = serialRead(_uart);
		delay(5);
		cont ++;
	}
}

//!Get data from the module 
void  WaspRFID::getData(uint8_t outLength)
{
	for (int i=5; i < outLength; i++) {
		dataRX[i] = serialRead(_uart); // read data from the module.
	} 
}

//!Calculates the checksum and stores it in dataTX buffer
void WaspRFID::checkSum(uint8_t *dataTX)
{
	for (int i = 0; i< dataTX[0] ; i++) {
		dataTX[dataTX[0] + 2] += dataTX[i + 2];  
	}	 
		byte(dataTX[dataTX[0] + 2]= - dataTX[dataTX[0] + 2]);
}

//!Calculates the length checksum and sotres it in the buffer. 
uint8_t WaspRFID::lengthCheckSum(uint8_t *dataTX)
{
	dataTX[1] = byte(0x100 - dataTX[0]); 
}

WaspRFID RFID13=WaspRFID();

