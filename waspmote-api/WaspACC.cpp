/*
 *  Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.0
 *  Design:			David Gascón
 *  Implementation:	David Cuartielles, Alberto Bielsa, Marcos Yarza
 */
  

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

// Variables ///////////////////////////////////////////////////////////////////

// Constructors ////////////////////////////////////////////////////////////////

WaspACC::WaspACC()
{
    // no interruption set at the beginning
    accInt=NO_INT;
}

// Public Methods //////////////////////////////////////////////////////////////

/******************************************************************************
 * QUICK BOOTING AND CONFIGURATION OF THE SENSOR
 ******************************************************************************/

/*
 * ON (void) - It opens I2C bus and powers the accelerometer
 *
 * It opens I2C bus and powers the accelerometer
 */
void WaspACC::ON(void)
{	
	ON(FS_2G);
}

/*
 * ON (void) - It opens I2C bus and powers the accelerometer
 *
 * It opens I2C bus and powers the accelerometer
 */
void WaspACC::ON(uint8_t FS_OPTION)
{	
	// join i2c bus (address optional for master)
    if( !Wire.I2C_ON )
    {
		Wire.begin();
    }
    
    accMode = ACC_ON;
	setMode(ACC_ON);
	
	// store Full-scale selection
	fsSelection = FS_OPTION;
	
	switch (FS_OPTION)
	{
		case FS_2G:
		{
			writeRegister(CTRL_REG4, B00000000);
			break;
		}
		case FS_4G:
		{
			writeRegister(CTRL_REG4, B00010000);
			break;
		}
		case FS_8G:
		{
			writeRegister(CTRL_REG4, B00110000);
			break;
		}
	}
}


/*
 * boot (void) - reboot the accelerometer
 *
 * takes for granted the accelerometer is on and forces the sensor to reboot
 * by writing to the CTRL_REG2 into the right pin it makes no tests and checks 
 * nothing from the communication, therefore returns nothing and modifies no flags
 */
void WaspACC::boot(void)
{
  // send reboot command
  writeRegister(CTRL_REG2, B10000000);
  
  // make a short pause after rebooting
  delay(1);  
  
  // set CTRL_REG2 to zero: no reboot, no filter 
  writeRegister(CTRL_REG2, B00000000);
}

/*
 * OFF (void) - closes I2C bus
 *
 * It closes I2C bus. Accelerometer uses I2C to communicate with microcontroller
 * Set the accelerometer into POWER DOWN mode 
 * It is used to keep the battery to the maximum
 */
void WaspACC::OFF(void)
{
	setMode(ACC_POWER_DOWN);	
	if( Wire.I2C_ON && RTC.isON!=1)
	{
		 PWR.closeI2C();
		 RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

/*******************************************************************************
 * CHECK ACCELEROMETER'S STATUS
 ******************************************************************************/

/*
 * getStatus (void) - gets the accelerometer status
 *
 * returns a byte containing the status of the accelerometer as read from
 * the proper register. It won't activate any flags by itself, but activates
 * ACC_COMM_ERROR in case there was an error writing to the register
 */
uint8_t WaspACC::getStatus(void)
{
  return (uint8_t) readRegister(STATUS_REG);
}

/*
 * check (void) - checks if there is an accelerometer on board
 *
 * sends the accelerometer dummy register on 0x0F that should always answer 0x32
 *
 * This function can be used to determine if the accelerometer is on the board
 * but also to check if it is still working properly. Any answer other than
 * 0x32 means there is an error
 *
 * since it calls readRegister, check won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::check(void)
{
  return (uint8_t) readRegister(WHO_AM_I);
}

/*******************************************************************************
 * HANDLE THE CONFIGURATION REGISTERS, BOTH READ AND WRITE
 *******************************************************************************/

/*
 * getCTRL1 (void) - checks accelerometer's control register 1: CTRL_REG1
 *
 * returns the contents of CTRL_REG1. Since it calls readRegister, getCTRL1 
 * won't activate any flags by itself, but the other functions will activate 
 * ACC_COMM_ERROR in case there was an error communicating to the register
 */
uint8_t WaspACC::getCTRL1(void)
{
  return (uint8_t) readRegister(CTRL_REG1);
}

/*
 * setCTRL1 (void) - sets accelerometer's control register 1: CTRL_REG1
 *
 * sets the contents of CTRL_REG1, returns 1 if error
 * since it calls writeRegister, setCTRL1 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setCTRL1(uint8_t val)
{
  return (uint8_t) writeRegister(CTRL_REG1, val);
}

/*
 * getCTRL2 (void) - checks accelerometer's control register 2: CTRL_REG2
 *
 * returns the contents of control register 2
 * since it calls readRegister, getCTRL2 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::getCTRL2(void)
{
  return (uint8_t) readRegister(CTRL_REG2);
}

/*
 * setCTRL2 (void) - sets accelerometer's control register 2: CTRL_REG2
 *
 * sets the contents of control register 2, returns 1 if error
 * since it calls writeRegister, setCTRL2 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setCTRL2(uint8_t val)
{
  return (uint8_t) writeRegister(CTRL_REG2, val);
}

/*
 * getCTRL3 (void) - checks accelerometer's control register 3: CTRL_REG3
 *
 * returns the contents of control register 3
 * since it calls readRegister, getCTRL3 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::getCTRL3(void)
{
  return (uint8_t) readRegister(CTRL_REG3);
}

/*
 * setCTRL3 (void) - sets accelerometer's control register 3: CTRL_REG3
 *
 * sets the contents of control register 3, returns 1 if error
 * since it calls writeRegister, setCTRL3 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setCTRL3(uint8_t val)
{
  return (uint8_t) writeRegister(CTRL_REG3, val);
}

/*
 * getCTRL4 (void) - checks accelerometer's control register 4: CTRL_REG4
 *
 * returns the contents of control register 4
 * since it calls readRegister, getCTRL4 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::getCTRL4(void)
{
  return (uint8_t) readRegister(CTRL_REG4);
}

/*
 * setCTRL4 (void) - sets accelerometer's control register 4: CTRL_REG4
 *
 * sets the contents of control register 4, returns 1 if error
 * since it calls writeRegister, setCTRL4 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setCTRL4(uint8_t val)
{
  return (uint8_t) writeRegister(CTRL_REG4, val);
}

/*
 * getCTRL5 (void) - checks accelerometer's control register 5: CTRL_REG5
 *
 * returns the contents of control register 5
 * since it calls readRegister, getCTRL5 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::getCTRL5(void)
{
  return (uint8_t) readRegister(CTRL_REG5);
}

/*
 * setCTRL4 (void) - sets accelerometer's control register 5: CTRL_REG5
 *
 * sets the contents of control register 5, returns 1 if error
 * since it calls writeRegister, setCTRL5 won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setCTRL5(uint8_t val)
{
  return (uint8_t) writeRegister(CTRL_REG5, val);
}

/*
 * setSamplingRate (rate) - sets the accelerometer's sampling rate
 *
 * writes, inside the CTRL1 the sampling rate desired
 * since it calls writeRegister, setADCmode won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setSamplingRate(uint8_t rate)
{
	// get actual CTRL_REG1
	uint8_t aux = readRegister(CTRL_REG1);
	aux &= B11100111;
	
	// Depending on the rate selected change CTRL_REG1
	switch( rate )
	{
		case ACC_RATE_50:	aux |= rate;
							break;
		case ACC_RATE_100:	aux |= B00001000;
							break;
		case ACC_RATE_400:	aux |= B00010000;
							break;
		case ACC_RATE_1000:	aux |= B00011000;
							break;
	}
	return writeRegister(CTRL_REG1, aux);
}

/*******************************************************************************
* INTERRUPTS REGISTERS
*******************************************************************************/

/*
 * getINT1CFG (void)
 *
 * returns the contents of interrupt 1 control reg
 */
uint8_t WaspACC::getINT1CFG(void)
{
  return (uint8_t) readRegister(INT1_CFG);
}
/*
 * getINT1SRC (void) 
 *
 * returns the contents of interrupt 1 source reg
 */
uint8_t WaspACC::getINT1SRC(void)
{
  return (uint8_t) readRegister(INT1_SRC);
}
/*
 * getINT1THS (void) 
 *
 * returns the contents of interrupt 1 threshold reg
 */
uint8_t WaspACC::getINT1THS(void)
{
  return (uint8_t) readRegister(INT1_THS);
}
/*
 * getINT1DURATION (void) 
 *
 * returns the contents of interrupt 1 duration reg
 */
uint8_t WaspACC::getINT1DURATION(void)
{
  return (uint8_t) readRegister(INT1_DURATION);
}


/*******************************************************************************
 * GET ACCELERATION ON THE THREE AXIS
 ******************************************************************************/

/*
 * getX (void) - checks accelerometer's acceleration on OX 
 *
 * returns the combined contents of data registers OUT_X_H and OUT_X_L as an
 * integer according to ADC's configuration
 * A conversion is made depending on the full-scale selection (fsSelection)
 *
 * since it calls readRegister, getX won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
int16_t WaspACC::getX(void)
{	
	int32_t aux = 	((int8_t)readRegister(OUT_X_H)*256) +
					(uint8_t)readRegister(OUT_X_L);
	return fsSelection * 1000 * aux/32768;
}

/*
 * getY (void) - checks accelerometer's acceleration on OY 
 *
 * returns the combined contents of data registers OUT_Y_H and OUT_Y_L as an
 * integer according to ADC's configuration
 * A conversion is made depending on the full-scale selection (fsSelection)
 *
 * since it calls readRegister, getY won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
int16_t WaspACC::getY(void)
{
	int32_t aux =	((int8_t)readRegister(OUT_Y_H)*256) +
					(uint8_t)readRegister(OUT_Y_L);
	return fsSelection * 1000 * aux/32768;
}

/*
 * getZ (void) - checks accelerometer's acceleration on OZ
 *
 * returns the combined contents of data registers OUT_Z_H and OUT_Z_L as an
 * integer according to ADC's configuration
 * A conversion is made depending on the full-scale selection (fsSelection)
 *
 * since it calls readRegister, getZ won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
int16_t WaspACC::getZ(void)
{
	int32_t aux =	((int8_t)readRegister(OUT_Z_H)*256) +
					(uint8_t)readRegister(OUT_Z_L);
	return fsSelection * 1000 * aux/32768;
}

/*******************************************************************************
 * HANDLE ACCELEROMETER'S WORK MODES                                           *
 ******************************************************************************/

/*
 * getMode (void) - checks accelerometer's work mode
 *
 * returns the value for the accelerometer's work mode, the possibilites are:
 * - ACC_ON: normal mode
 * - ACC_POWER_DOWN: turn ACC off
 * - ACC_LOW_POWER_1
 * - ACC_LOW_POWER_2
 * - ACC_LOW_POWER_3
 * - ACC_LOW_POWER_4
 * - ACC_LOW_POWER_5
 *
 * It doesn't call any other functions and therefore it won't activate any flags
 */
uint8_t WaspACC::getMode()
{
  return accMode;
}

/*
 * setMode (uint8_t) - sets accelerometer's work mode
 *
 * configures the accelerometer to a new work mode, the possibilites are:
 * - ACC_HIBERNATE: go on the lowest power mode possible. This mode has no 
 *  interrupt calls and therefore won't disturb the processor if anything
 *  happened
 * - ACC_ON: read/send at a constant pace upon request
 * - ACC_CUSTOM: user defined work mode, should be programmed in here
 *
 * since it calls writeRegister, setAccMode won't activate any flags by itself, 
 * but the other functions will activate ACC_COMM_ERROR in case there 
 * was an error communicating to the register
 */
uint8_t WaspACC::setMode(uint8_t mode)
{
	accMode = mode;
	
	switch (mode)
	{
		case ACC_ON:			
					// turn power ON		
					// Normal mode is selected (PM2=0; PM1=0; PM0=1)
					// ODR is set to 50 Hz (DR1=0; DR0=0)
					// X-Y-Z axis are enabled
					writeRegister(CTRL_REG1, B00100111); 
					isON = 1;			
					break;
			
		case ACC_POWER_DOWN:	
					// turn power off 
					writeRegister(CTRL_REG1,B00000000); 
					isON = 0;
					break;
			
		case ACC_LOW_POWER_1:		
					// turn lo power mode. ODR=0.5 Hz
					writeRegister(CTRL_REG1, B01000111);
					isON = 1;		
					break;
			
		case ACC_LOW_POWER_2:
					// turn lo power mode. ODR=1 Hz
					writeRegister(CTRL_REG1, B01100111);
					isON = 1;
					break;
			
		case ACC_LOW_POWER_3:
					// turn lo power mode. ODR=2 Hz
					writeRegister(CTRL_REG1, B10000111);
					isON = 1;
					break;
			
		case ACC_LOW_POWER_4:
					// turn lo power mode. ODR=5 Hz
					writeRegister(CTRL_REG1, B10100111);
					isON = 1;
					break;
			
		case ACC_LOW_POWER_5:
					// turn lo power mode. ODR=10 Hz
					writeRegister(CTRL_REG1, B11000111);
					isON = 1;		
					break;
		
		default:	return 0;
			
	}	
		
	// go out with no error, leaves room to implement an error function
	return 1;
}

/*
 * setSleepToWake (void) - sets accelerometer's Sleep to Wake mode
 *
 * The sleep to wake function, in conjunction with Low Power mode, allows
 * further reduction of system power consumption
 * When the sleep to wake function is activated, the LIS331DLH is able to
 * automatically wake up as soon as the interrupt event has been detected,
 * increasing the output data rate and bandwidth. With this feature the system
 * can be efficiently switched from Low Power mode to full performance,
 * depending on user-selectable
 * 
 */
uint8_t WaspACC::setSleepToWake(void)
{
	
	return writeRegister(CTRL_REG5, B00000011);	
}

/*
 * unSetSleepToWake (void) - unsets accelerometer's Sleep to Wake mode
 *
 * The sleep to wake function, in conjunction with Low Power mode, allows
 * further reduction of system power consumption
 * When the sleep to wake function is activated, the LIS331DLH is able to
 * automatically wake up as soon as the interrupt event has been detected,
 * increasing the output data rate and bandwidth. With this feature the system
 * can be efficiently switched from Low Power mode to full performance,
 * depending on user-selectable
 * 
 */
uint8_t WaspACC::unSetSleepToWake(void)
{
	
	return writeRegister(CTRL_REG5, B00000000);
}

/*******************************************************************************
 * SPECIFIC WASP FUNCTIONS TO HANDLE EVENTS
 ******************************************************************************/

/*
 * setFF (void) - sets the Free Fall interrupt
 */
uint8_t WaspACC::setFF(void)
{
	// reboot ACC in order to clean the ACC Interruption 
	// pin in the it has been locked to '1'
	boot();
	delay(100);

	// clear the FF interrupt if active
	unsetFF();
   
	// configure the different registers to 
	// handle acceleration detection on the X, Y, or Z axis
				
	// set latch interrupt request: when an interrupt condition is applied,
	// the interrupt signal remains high even if the condition returns to a 
	// non-interrupt status, until a reading of the INTx_SRC register is performed.
	writeRegister(CTRL_REG2,0x00);
	writeRegister(CTRL_REG3,0x04);		
  
	// set Free-Fall threshold. Beware of the full scale selection!
	uint8_t val=INT1_THS_val*2/fsSelection;
	writeRegister(INT1_THS, val); 		
	 
	// set minimum event duration	
	writeRegister(INT1_DURATION, INT1_DURATION_val);	 
	
	// set interrupt configuration	
	writeRegister(INT1_CFG, INT1_CFG_val); 
    
    // Free-Fall interruption set
	accInt=FF_INT;	
	
    delay(100);
	// attach the hardware interrupt to the pin
	enableInterrupts(ACC_INT);

	return flag;
}

/*
 * unsetFF (void) - clears and unsets the Free Fall interrupt
 */
uint8_t WaspACC::unsetFF(void)
{
	// set CTRL_REG3 to zero
	writeRegister(CTRL_REG3, 0x00);  
  
  	// read INT1_SRC register in order to clear the interrupt flag
	readRegister(INT1_SRC); 
  
	// detach the event 
	detachInt();
	
	// no interruption set
	accInt=NO_INT;
	
	return flag;
}

/*
 * setIWU (void) - sets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::setIWU(void)
{
	// clear the FF interrupt if active
	unsetIWU();
   
	// configure the different registers to 
	// handle acceleration detection on the X, Y, or Z axis
	writeRegister(CTRL_REG3,0x00);
  
	writeRegister(INT1_THS,0x10);  
	writeRegister(INT1_DURATION,0x00);  
	writeRegister(INT1_CFG,0x0A); 
	
	// attach the hardware interrupt to the pin
	enableInterrupts(ACC_INT);
	
	// IWU interruption set
	accInt=IWU_INT;

	return flag;
}

/*
 * unsetIWU (void) - clears and unsets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::unsetIWU(void)
{
	// set CTRL_REG3 to zero
	writeRegister(CTRL_REG3, 0x00);  
  
  	// read INT1_SRC register in order to clear the interrupt flag
	readRegister(INT1_SRC); 

	// detach the event 
	detachInt();
	
	// no interruption set
	accInt=NO_INT;
	
	return flag;
}

/*
 * set6DMovement (void) - sets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::set6DMovement(void)
{
	// clear the FF interrupt if active
	unset6DMovement();
   
	// configure the different registers to 
	// handle acceleration detection on the X, Y, or Z axis
	writeRegister(CTRL_REG3,0x04);
  
	writeRegister(INT1_THS,0x30);  // threshold
	writeRegister(INT1_DURATION,0x00); // event duration
	writeRegister(INT1_CFG,0x7F);  // 6D movement recognition in 3-axes
	
	// attach the hardware interrupt to the pin
	enableInterrupts(ACC_INT);
	
	// 6D Movement interruption set
	accInt=_6DMOV_INT;

	return flag;
}

/*
 * unset6DPosition (void) - clears and unsets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::unset6DMovement(void)
{
	// set CTRL_REG3 to zero
	writeRegister(CTRL_REG3, 0x00);  
  
  	// read INT1_SRC register in order to clear the interrupt flag
	readRegister(INT1_SRC); 

	// detach the event 
	detachInt();
	
	// no interruption set
	accInt=NO_INT;
	
	return flag;
}

/*
 * set6DPosition (void) - sets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::set6DPosition(void)
{
	// clear the FF interrupt if active
	unset6DPosition();
   
	// configure the different registers to 
	// handle acceleration detection on the X, Y, or Z axis
	writeRegister(CTRL_REG3,0x04);
  
	writeRegister(INT1_THS,0x21);  // threshold
	writeRegister(INT1_DURATION,0x00);  // event duration
	writeRegister(INT1_CFG,0xFF);  // 6D position recognition in 3-axes

	// attach the hardware interrupt to the pin
	enableInterrupts(ACC_INT);

	// 6D Position interruption set
	accInt=_6DPOS_INT;

	return flag;
}

/*
 * unset6DPosition (void) - clears and unsets the Inertial Wake-UP interrupt
 */
uint8_t WaspACC::unset6DPosition(void)
{
	// set CTRL_REG3 to zero
	writeRegister(CTRL_REG3, 0x00);
  
	// read INT1_SRC register in order to clear the interrupt flag
	readRegister(INT1_SRC); 

	// detach the event 
	detachInt();
		
	// no interruption set
	accInt=NO_INT;
  
	return flag;
}




/*******************************************************************************
 * HANDLING HARDWARE INTERRUPTS
 *******************************************************************************/

/*
 * attachInt(void) - configure the specific hardware interrupt for the acc
 *
 * the default interrupt functions are defined inside WInterrupts.c
 */
void WaspACC::attachInt(void)
{
	enableInterrupts(ACC_INT);
}

/*
 * detachInt(void) - unset the specific hardware interrupt for the acc
 */
void WaspACC::detachInt(void)
{
	disableInterrupts(ACC_INT);
}



/*******************************************************************************
 * LOW LEVEL READ AND WRITE REGISTERS
 *******************************************************************************/

// reads a register from the accelerometer
// returns its value or -1 if error
int16_t WaspACC::readRegister(uint8_t regNum) 
{
	// reset the flag
	flag &= ~(ACC_ERROR_READING);

	uint8_t aux = 0;
	Wire.beginTransmission(i2cID);
	Wire.write(regNum);
	Wire.endTransmission();

	Wire.requestFrom(i2cID, 1);
	if(Wire.available())
	{
		aux = Wire.read();
		return aux;
	}

	// error, activate the reading flag
	flag |= ACC_ERROR_READING;

	return -1;
}

// writes a byte to a register in the accelerometer
// returns 1 on success; 0 if error
uint8_t WaspACC::writeRegister(uint8_t address, uint8_t val)
{
	// reset the flag
	flag &= ~(ACC_ERROR_WRITING);

	Wire.beginTransmission(i2cID);
	Wire.write(address);
	Wire.write(val);
	Wire.endTransmission();

	if (readRegister(address) != val)
	{
		// error, activate the reading flag
		flag |= ACC_ERROR_WRITING;

		return 0;
	}

	// exit with no error
	return 1;
}

// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspACC ACC = WaspACC();

