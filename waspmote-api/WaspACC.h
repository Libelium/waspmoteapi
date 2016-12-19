/*! \file WaspACC.h
    \brief Library for managing the accelerometer LIS331DLH
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
  
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
    Version:		3.0
    Design:			David Gascón
    Implementation:	David Cuartielles, Alberto Bielsa, Marcos Yarza

*/
  
 
/*! \def WaspACC_h
    \brief The library flag
    
 */
#ifndef WaspACC_h
#define WaspACC_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def FS_2G
    \brief Full-scale selecion +-2g
 */
#define FS_2G 2

/*! \def FS_4G
    \brief Full-scale selecion +-4g
 */
#define FS_4G 4

/*! \def FS_8
    \brief Full-scale selecion +-8g
 */
#define FS_8G 8

/*! \def cbi
    \brief Function definition to set a register bit to '0'
    
    'sfr' is the register. 'bit' is the register bit to change
 */
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

/*! \def sbi
    \brief Function definition to set a register bit to '1'
    
    'sfr' is the register. 'bit' is the register bit to change
 */
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



/*! \def WHO_AM_I
    \brief Who Am I Register Address    
    Device identification register. This register contains the device identifier 
    that for LIS331DLH is set to 0x32
 */
#define WHO_AM_I	0x0F


/*! \def CTRL_REG1
    \brief Control Register 1 Address    
    This register contains configuration parameters as powering accelerometer 
    or enabling the different axis
 */
/*! \def CTRL_REG2
    \brief Control Register 2 Address     
    This register contains configuration parameters related with the high-pass 
    filter   
 */
/*! \def CTRL_REG3
    \brief Control Register 3 Address    
    This register contains configuration parameters as enabling interruptions 
    or data type
 */
/*! \def CTRL_REG4
    \brief Control Register 4 Address    
    This register contains configuration parameters related with the Full-scale 
    selection, data type, self test parameters and SPI interface mode
 */
/*! \def CTRL_REG5
    \brief Control Register 5 Address    
    This register contains configuration parameters related with the turn-on 
    mode selection for sleep to wake function
 */
#define CTRL_REG1 	0x20
#define CTRL_REG2 	0x21
#define CTRL_REG3 	0x22
#define CTRL_REG4 	0x23
#define CTRL_REG5 	0x24




/*! \def HP_FILTER_RESET
    \brief High Pass Filter Register Address    
    Dummy register. Reading at this address zeroes instantaneously the content 
    of the internal high pass-filter. If the high pass filter is enabled all 
    three axes are instantaneously set to 0g. This allows to overcome the 
    settling time of the high pass filter
 */
#define HP_FILTER_RESET 0x25


/*! \def STATUS_REG
    \brief Status Register Address    
    This register indicates X, Y and Z axis data overrun and X, Y and Z axis 
    new data available
 */
#define STATUS_REG 	0x27


/*! \def OUT_X_L
    \brief X axis acceleration register lower bits address    
    The value is expressed as two’s complement
 */
/*! \def OUT_X_H
    \brief X axis acceleration register higher bits address    
    The value is expressed as two’s complement
 */
/*! \def OUT_Y_L
    \brief Y axis acceleration register lower bits address    
    The value is expressed as two’s complement
 */
/*! \def OUT_Y_H
    \brief Y axis acceleration register higher bits address    
    The value is expressed as two’s complement
 */
/*! \def OUT_Z_L
    \brief Z axis acceleration register lower bits address    
    The value is expressed as two’s complement
 */
/*! \def OUT_Z_H
    \brief Z axis acceleration register higher bits address    
    The value is expressed as two’s complement
 */
#define OUT_X_L		0x28
#define OUT_X_H		0x29
#define OUT_Y_L 	0x2A
#define OUT_Y_H 	0x2B
#define OUT_Z_L 	0x2C
#define OUT_Z_H 	0x2D


/*! \def INT1_CFG
    \brief Address for the Interrupt 1 configuration register    
 */
/*! \def INT1_SRC
    \Interrupt 1 source register. Read only register.
    Reading at this address clears INT1_SRC IA bit (and the interrupt signal on 
    INT 1 pin) and allows the refreshment of data in the INT1_SRC register if 
    the latched option was chosen    
 */
/*! \def INT1_THS
    \brief Interrupt 1 threshold  address    
 */
/*! \def INT1_DURATION
    \brief Interrupt 1 duration value register address      
 */
#define INT1_CFG 		0x30
#define INT1_SRC 		0x31
#define INT1_THS 		0x32
#define INT1_DURATION 	0x33


/*! \def INT1_THS_val
    \brief Free-Fall Threshold. 
    When a free-fall event is caused, the acceleration measurements along all 
    the axes go to zero. INT1_THS_val limits a “free-fall zone” which is defined 
    around the zero-g level and where all accelerations are small enough to 
    generate the interrupt.
    When Full scale is +-2g, 16mg is aproximately INT1_THS_val=0x01. 
    Full scale selection implies a conversion which is made inside setFF function    
    Default value is set to 448mg which is expresed as INT1_THS_val=0x1C
 */
/*! \def INT1_DURATION_val
    Minimum Free-Fall event duration to be recognised in order to avoid 
    false detections.
    Event time is calculated as: time(seconds)=INT1_DURATION_val/ODR
	Default value is INT1_DURATION_val  0x03. If ODR is set to 50 Hz, this means
	that the minimum event duration is set to: 3/50=60ms
 */
/*! \def INT1_CFG_val
    \brief Free Fall Configuration    
    Free Fall Interruption Configuration, setting Z,Y,X High interrupt event
 */
#define INT1_THS_val		0x1C
#define INT1_DURATION_val  	0x03
#define INT1_CFG_val		0x95



/*! \def AOI
    \brief AND/OR Combination of interrupt events    
    This bit is contained in INT1_CFG. 
	When (AOI=0 ; _6D=0) then OR combination of interrupts events
	When (AOI=0 ; _6D=1) then 6 direction movement recognition
	When (AOI=1 ; _6D=0) then AND combination of interrupts events
	When (AOI=1 ; _6D=1) then 6 direction position recognition	
 */
/*! \def _6D
    \brief 6 direction detection function enable
    This bit is contained in INT1_CFG.
	When (AOI=0 ; _6D=0) then OR combination of interrupts events
	When (AOI=0 ; _6D=1) then 6 direction movement recognition
	When (AOI=1 ; _6D=0) then AND combination of interrupts events
	When (AOI=1 ; _6D=1) then 6 direction position recognition	
 */
/*! \def ZHIE
    \brief Enable interrupt generation on Z high event    
    This bit is contained in INT1_CFG. '1' enables Z High event interruption
 */
/*! \def ZLIE
    \brief Z Low event interruption    
    This bit is contained in INT1_CFG. '1' enables Z Low event interruption
 */
/*! \def YHIE
    \brief Y High event interruption    
    This bit is contained in INT1_CFG. '1' enables Y High event interruption
 */
/*! \def YLIE
    \brief Y Low event interruption    
    This bit is contained in INT1_CFG. '1' enables Y Low event interruption
 */
/*! \def XHIE
    \brief X High event interruption    
    This bit is contained in INT1_CFG. '1' enables X High event interruption
 */
/*! \def XLIE
    \brief X Low event interruption    
    This bit is contained in INT1_CFG. '1' enables X Low event interruption
 */
#define AOI   	128
#define	_6D		64
#define ZHIE  	32
#define ZLIE  	16
#define YHIE  	8
#define YLIE  	4
#define XHIE  	2
#define XLIE  	1



/*! \def SIGNED_12_BITS
    \brief Accelerometer ADC modes. Signed 12 bits in this case
    
    This is the DAS bit in the CTRL2 register
 */
/*! \def UNSIGNED_16_BITS
    \brief Accelerometer ADC modes. Unsigned 16 bits in this case
    
    This is the DAS bit in the CTRL2 register
 */
#define SIGNED_12_BITS 		0
#define UNSIGNED_16_BITS 	1



/*! \def ACC_ON
    \brief Accelerometer Operation modes. ON in this case
 */
/*! \def ACC_POWER_DOWN
    \brief Accelerometer Operation modes. OFF in this case
 */
/*! \def ACC_LOW_POWER_1
    \brief Accelerometer Operation modes. Low-power 1 - data rate 0.5Hz
 */
/*! \def ACC_LOW_POWER_2
    \brief Accelerometer Operation modes. Low-power 1 - data rate 1Hz
 */
/*! \def ACC_LOW_POWER_3
    \brief Accelerometer Operation modes. Low-power 1 - data rate 2Hz
 */
/*! \def ACC_LOW_POWER_4
    \brief Accelerometer Operation modes. Low-power 1 - data rate 5Hz
 */
/*! \def ACC_LOW_POWER_5
    \brief Accelerometer Operation modes. Low-power 1 - data rate 10Hz
 */
#define ACC_ON 				1
#define ACC_POWER_DOWN 		2
#define ACC_LOW_POWER_1 	3
#define ACC_LOW_POWER_2		4
#define ACC_LOW_POWER_3 	5
#define ACC_LOW_POWER_4 	6
#define ACC_LOW_POWER_5 	7



/*! \def ACC_ERROR_READING
    \brief Flag values. Error reading register in this case
 */
/*! \def ACC_ERROR_READING
    \brief Flag values. Error writing register in this case
 */
#define ACC_ERROR_READING 		1
#define ACC_ERROR_WRITING 		2



/*! \def ACC_RATE_50
    \brief 50Hz Sampling Rate
 */
/*! \def ACC_RATE_100
    \brief 100Hz Sampling Rate
 */
/*! \def ACC_RATE_400
    \brief 400Hz Sampling Rate
 */
/*! \def ACC_RATE_1000
    \brief 1000Hz Sampling Rate
 */
#define ACC_RATE_50	 	0
#define ACC_RATE_100 	1
#define ACC_RATE_400 	2
#define ACC_RATE_1000 	3


/*! \def NO_INT
    \brief No interruption set
 */
/*! \def FF_INT
    \brief Free Fall interruption set
 */
/*! \def IWU_INT
    \brief Inertial Wake-Up interruption set
 */
/*! \def _6DMOV_INT
    \brief 6D Movement interruption set
 */
/*! \def _6DPOS_INT
    \brief 6D Position interruption set
 */
#define NO_INT 				0
#define FF_INT 				1
#define IWU_INT 			2
#define _6DMOV_INT		 	3
#define _6DPOS_INT			4


/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspACC Class
/*!
	WaspACC Class defines all the variables and functions used to manage 
	LIS3LV02DL accelerometer
 */
class WaspACC
{
 
private:

    //! Variable : Accelerometer Operation Mode
    /*!
	  Possible values are ACC_ON, ACC_HIBERNATE and ACC_CUSTOM
     */ 
    uint8_t accMode;
    
    //! Variable : Full-scale selection attribute
    /*!
	  Possible values are ACC_ON, ACC_HIBERNATE and ACC_CUSTOM
     */ 
    uint8_t fsSelection;      

public:

    //! class constructor
    /*!
	  It does nothing
	  \param void
	  \return void
     */ 
    WaspACC();    

    
    //! Variable : status flag, used to see if there has been an error while 
    //! reading/writing or if there has been a hardware interrupt
    /*!
	  Possible values are ACC_ERROR_READING or ACC_ERROR_WRITING
     */ 
    volatile uint8_t flag;
    
    //! Variable : interrupt flag, used to check which interrupt got active
    /*!
    	Its structure is:
                      (MSB)  7   6   5   4   3   2   1   0  (LSB)
                             XX  XX  XX  XX  XX  TH  DD  FF
                      TH - threshold, DD - direction change, FF - free fall
     */ 
    uint8_t flagInt;
    
    //! Variable : It stores if the ACC is ON(1) or OFF(0)
    /*!    
    */
    uint8_t isON;
    
    //! Variable : Accelerometer Interruption state
    /*!
	  Possible values are ACC_ON, ACC_HIBERNATE and ACC_CUSTOM
     */ 
    uint8_t accInt;
    
    //! Variable : Int1 threshold variable 
    /*! Depending on the full scale selected, the reference value is different:
     * 		Full scale		Reference mode LSB value (mg)
     * 			2						16
     * 			4						31
     * 			8						63 		
     */ 
    uint8_t _int1_ths;
    
    //! Variable : Threshold set in mg units
    /*! 
     */ 
    uint16_t _threshold;  
    
    
    //! It opens I2C bus and powers the accelerometer
    /*!
    \param void
    \return void
    \sa boot(), close(), begin()
     */ 
    void ON();
    
    //! It opens I2C bus and powers the accelerometer
    /*!
    \param void
    \return void
    \sa boot(), close(), begin()
     */ 
    void ON(uint8_t FS_OPTION);
    
    //! It reboots the accelerometer
    /*!
    \param void
    \return void
    \sa init(), close()
     */ 
    void boot();
    
    //! It closes I2C bus
    /*!
    \param void
    \return void
    \sa init(), boot()
     */ 
    void OFF();
    
    //! It gets the accelerometer status
    /*!
    \param void
    \return a byte containing the accelerometer status as read from the proper 
    register. It won't activate any flags by itself, but activates 
    ACC_COMM_ERROR in case there was an error writing to the register
    \sa check()
     */ 
    uint8_t getStatus();
    
    //! It checks if accelerometer is working properly
    /*!
    \param void
    \return a byte containing the register value. If this value is different 
    from '0x3A', the accelerometer is not working properly
    \sa getStatus()
     */
    uint8_t check();

    //! It gets the CTRL1 register
    /*!
    \param void
    \return a byte containing the register value.
    \sa setCTRL1(uint8_t val)
     */
    uint8_t getCTRL1();
    
    //! It sets the CTRL1 register
    /*!
    \param uint8_t val : value to set the CTRL1 register to
    \return '1' on success, '0' on error
    \sa getCTRL1()
     */
    uint8_t setCTRL1(uint8_t val);
    
    //! It gets the CTRL2 register
    /*!
    \param void
    \return a byte containing the register value.
    \sa setCTRL2(uint8_t val)
     */
    uint8_t getCTRL2();
    
    //! It sets the CTRL2 register
    /*!
    \param uint8_t val : value to set the CTRL2 register to
    \return '1' on success, '0' on error
    \sa getCTRL2()
     */
    uint8_t setCTRL2(uint8_t val);
    
    //! It gets the CTRL3 register
    /*!
    \param void
    \return a byte containing the register value.
    \sa setCTRL3(uint8_t val)
     */
    uint8_t getCTRL3();
    
    //! It sets the CTRL3 register
    /*!
    \param uint8_t val : value to set the CTRL3 register to
    \return '1' on success, '0' on error
    \sa getCTRL3()
     */
    uint8_t setCTRL3(uint8_t val);
    
    //! It gets the CTRL4 register
    /*!
    \param void
    \return a byte containing the register value.
    \sa setCTRL4(uint8_t val)
     */
    uint8_t getCTRL4();
    
    //! It sets the CTRL4 register
    /*!
    \param uint8_t val : value to set the CTRL4 register to
    \return '1' on success, '0' on error
    \sa getCTRL4()
     */
    uint8_t setCTRL4(uint8_t val);
    
    //! It gets the CTRL5 register
    /*!
    \param void
    \return a byte containing the register value.
    \sa setCTRL5(uint8_t val)
     */
    uint8_t getCTRL5();
    
    //! It sets the CTRL5 register
    /*!
    \param uint8_t val : value to set the CTRL5 register to
    \return '1' on success, '0' on error
    \sa getCTRL5()
     */
    uint8_t setCTRL5(uint8_t val);
    
    //! It reads a register from the accelerometer
    /*!
    \param uint8_t address : register address
    \return register value or '-1' if error
    \sa writeRegister(uint8_t address, uint8_t val)
     */
    int16_t readRegister(uint8_t address);
    
    //! It writes a register to the accelerometer
    /*!
    \param uint8_t address : register address
    \param uint8_t val : value to write
    \return '1' on success, '0' on error
    \sa readRegister(uint8_t val)
     */
    uint8_t writeRegister(uint8_t address, uint8_t val);
    
    //! It sets the accelerometer's sampling rate
    /*!
    \param uint8_t rate : ACC_RATE_40, ACC_RATE_160, ACC_RATE_640, ACC_RATE_2560
    \return '1' on success, '0' if error
     */
    uint8_t setSamplingRate(uint8_t rate);
    
    //! It gets the acceleration on OX
    /*!
    \param void
    \return the combined contents of data registers outXhigh and outXlow as an 
    integer according to ADC's configuration
    \sa getY(), getZ()
     */
    int16_t getX();
    
    //! It gets the acceleration on OY
    /*!
    \param void
    \return the combined contents of data registers outYhigh and outYlow as an 
    integer according to ADC's configuration
    \sa getX(), getZ()
     */
    int16_t getY();
    
    //! It gets the acceleration on OZ
    /*!
    \param void
    \return the combined contents of data registers outZhigh and outZlow as an 
    integer according to ADC's configuration
    \sa getX(), getY()
     */
    int16_t getZ();

    //! It sets the Free Fall interrupt 
    //! using the parameters previously defined
    /*!
    \param void
    \return 'flag' variable
    \sa unsetFF()
     */
    uint8_t setFF( void );
    uint8_t setFF( uint16_t ths );
    
    //! It unsets the Free Fall interrupt
    /*!
    \param void
    \return 'flag' variable
    \sa setFF()
     */
    uint8_t unsetFF(void);
    
    //! It sets the Inertial Wake-UP interrupt 
    //! using the parameters previously defined
    /*!
    \param void
    \return 'flag' variable
    \sa unsetIWU()
     */
    uint8_t setIWU( void );
    uint8_t setIWU( uint16_t ths );
    
    //! It unsets the Inertial Wake-UP interrupt
    /*!
    \param void
    \return 'flag' variable
    \sa setIWU()
     */
    uint8_t unsetIWU(void);
    
    //! It sets the 6D Movement Recognition interrupt 
    //! using the parameters previously defined
    /*!
    \param void
    \return 'flag' variable
    \sa unset6DMovement()
     */
    uint8_t set6DMovement(void);
    
    //! It unsets the 6D Movement Recognition interrupt interrupt
    /*!
    \param void
    \return 'flag' variable
    \sa set6DMovement()
     */
    uint8_t unset6DMovement(void);
    
    //! It sets the 6D Movement Recognition interrupt 
    //! using the parameters previously defined
    /*!
    \param void
    \return 'flag' variable
    \sa unset6DPosition()
     */
    uint8_t set6DPosition(void);
    
    //! It unsets the 6D Movement Postition interrupt interrupt
    /*!
    \param void
    \return 'flag' variable
    \sa set6DPosition()
     */
    uint8_t unset6DPosition(void);
    
    //! It gets the accelerometer's work mode
    /*!
    \param void
    \return 'accMode' variable
    \sa setMode(uint8_t val)
     */
    uint8_t getMode();
    
    //! It sets accelerometer's Sleep to Wake mode
    /*!
    \param void
    \return '1' on success
    \sa unsetSleepToWake()
     */
    uint8_t setSleepToWake(void);
    
    //! It unsets accelerometer's Sleep to Wake mode
    /*!
    \param void
    \return '1' on success
    \sa setSleepToWake()
     */
    uint8_t unSetSleepToWake(void);
    
    //! It sets the accelerometer's work mode
    /*!
    \param uint8_t val : the accelerometer's work mode 
			(ACC_ON, ACC_HIBERNATE, ACC_CUSTOM)
    \return '1' on success, '0' if error
    \sa getMode()
     */
    uint8_t setMode(uint8_t val);
     
    //! It configures the specific hardware interrupt for the acc
    /*!
    \param void
    \return void
    \sa detachInt()
     */
    void attachInt(void);
    
    //! It unsets the specific hardware interrupt for the acc
    /*!
    \param void
    \return void
    \sa attachInt()
     */
    void detachInt(void);

    //! It gets the contents of INT1_CFG
    /*!
    \param void
    \return the contents of interrupt 1 configuration reg
     */
    uint8_t getINT1CFG();
    
    //! It gets the contents of INT1_SRC
    /*!
    \param void
    \return the contents of interrupt 1 source reg
     */
    uint8_t getINT1SRC();
    
    //! It gets the contents of INT1_THS
    /*!
    \param void
    \return the contents of interrupt 1 threshold reg
     */
    uint8_t getINT1THS();
        
    //! It gets the contents of INT1_DURATION
    /*!
    \param void
    \return the contents of interrupt 1 duration reg
     */
    uint8_t getINT1DURATION();
    
	//! It calculates the attribute in order to set the interruption threshold
    /*!
    \param uint16_t ths: threshold to set in mg units
    \return the value set in attribute
     */
    uint8_t calculateThreshold( uint16_t ths );
           
};

extern WaspACC ACC;

#endif

