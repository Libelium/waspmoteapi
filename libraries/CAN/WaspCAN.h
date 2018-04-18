/*! \file WaspCAN.h
    \brief  Library for managing CAN Bus modules

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    Version:			3.2
    Design:				David Gascón
    Implementation:		Luis Antonio Martín Nuez & Ahmad Saad
*/

#ifndef WaspCAN_h
#define WaspCAN_h


/***********************************************************************
 * Includes
 ***********************************************************************/


/***********************************************************************
 * Definitions & Declarations
 ***********************************************************************/

 #define DEBUGMODE 0

 // define print message
 #define PRINT_CAN(str)	USB.print(F("[CAN] ")); USB.print(str);


#define CAN_CS		34
#define CAN_INT		45

//**********************************************************************
// MCP2515 Opcodes
//**********************************************************************

#define SPI_RESET			0xC0
#define SPI_READ			0x03
#define SPI_READ_RX			0x90
#define SPI_WRITE			0x02
#define SPI_WRITE_TX		0x40
#define SPI_RTS				0x80
#define SPI_READ_STATUS		0xA0
#define SPI_RX_STATUS		0xB0
#define SPI_BIT_MODIFY		0x05

#define CAN_LISTEN_ONLY_MODE	0x01
#define CAN_LOOPBACK_MODE		0x02
#define CAN_SLEEP_MODE			0x03
#define CAN_NORMAL_MODE			0x04

/***********************************************************************
                                MCP2515 REGISTERS
************************************************************************/

//**********************************************************************
// Message acceptance filters registers - Buffer 0
//**********************************************************************
#define RXF0SIDH                0x00
#define RXF0SIDL                0x01
#define RXF0EID8                0x02
#define RXF0EID0                0x03
#define RXF1SIDH                0x04
#define RXF1SIDL                0x05
#define RXF1EID8                0x06
#define RXF1EID0                0x07
#define RXF2SIDH                0x08
#define RXF2SIDL                0x09
#define RXF2EID8                0x0A
#define RXF2EID0                0x0B

//**********************************************************************
//Digital outputs/inputs registers
//**********************************************************************
#define BFPCTRL                 0x0C
#define TXRTSCTRL               0x0D
//**********************************************************************
//CAN-bus control and status registers
//**********************************************************************
#define CANSTAT                 0x0E
#define CANCTRL                 0x0F
//**********************************************************************
//Message acceptance filters registerts - Buffer 1
//**********************************************************************
#define RXF3SIDH                0x10
#define RXF3SIDL                0x11
#define RXF3EID8                0x12
#define RXF3EID0                0x13
#define RXF4SIDH                0x14
#define RXF4SIDL                0x15
#define RXF4EID8                0x16
#define RXF4EID0                0x17
#define RXF5SIDH                0x18
#define RXF5SIDL                0x19
#define RXF5EID8                0x1A
#define RXF5EID0                0x1B
//**********************************************************************
//Error counters registers
//**********************************************************************
#define TEC                     0x1C
#define REC                     0x1D
//**********************************************************************
//Message acceptance masks registers
//**********************************************************************
#define RXM0SIDH                0x20
#define RXM0SIDL                0x21
#define RXM0EID8                0x22
#define RXM0EID0                0x23
#define RXM1SIDH                0x24
#define RXM1SIDL                0x25
#define RXM1EID8                0x26
#define RXM1EID0                0x27
//**********************************************************************
//Bit timing registers
//**********************************************************************
#define CNF3                    0x28
#define CNF2                    0x29
#define CNF1                    0x2A
//**********************************************************************
//Interrups registers
//**********************************************************************
#define CANINTE                 0x2B
#define CANINTF                 0x2C
//**********************************************************************
//Error flags registers
//**********************************************************************
#define EFLG                    0x2D
//**********************************************************************
//Message transmission registers - buffer --> 0
//**********************************************************************
#define TXB0CTRL                0x30
#define TXB0SIDH                0x31
#define TXB0SIDL                0x32
#define TXB0EID8                0x33
#define TXB0EID0                0x34
#define TXB0DLC                 0x35
#define TXB0D0                  0x36
#define TXB0D1                  0x37
#define TXB0D2                  0x38
#define TXB0D3                  0x39
#define TXB0D4                  0x3A
#define TXB0D5                  0x3B
#define TXB0D6                  0x3C
#define TXB0D7                  0x3D
//**********************************************************************
//Message transmission registers - buffer --> 1
//**********************************************************************
#define TXB1CTRL                0x40
#define TXB1SIDH                0x41
#define TXB1SIDL                0x42
#define TXB1EID8                0x43
#define TXB1EID0                0x44
#define TXB1DLC                 0x45
#define TXB1D0                  0x46
#define TXB1D1                  0x47
#define TXB1D2                  0x48
#define TXB1D3                  0x49
#define TXB1D4                  0x4A
#define TXB1D5                  0x4B
#define TXB1D6                  0x4C
#define TXB1D7                  0x4D
//**********************************************************************
//Message transmission registers - buffer --> 2
//**********************************************************************
#define TXB2CTRL                0x50
#define TXB2SIDH                0x51
#define TXB2SIDL                0x52
#define TXB2EID8                0x53
#define TXB2EID0                0x54
#define TXB2DLC                 0x55
#define TXB2D0                  0x56
#define TXB2D1                  0x57
#define TXB2D2                  0x58
#define TXB2D3                  0x59
#define TXB2D4                  0x5A
#define TXB2D5                  0x5B
#define TXB2D6                  0x5C
#define TXB2D7                  0x5D
//**********************************************************************
//Message reception registers - buffer --> 0
//**********************************************************************
#define RXB0CTRL                0x60
#define RXB0SIDH                0x61
#define RXB0SIDL                0x62
#define RXB0EID8                0x63
#define RXB0EID0                0x64
#define RXB0DLC                 0x65
#define RXB0D0                  0x66
#define RXB0D1                  0x67
#define RXB0D2                  0x68
#define RXB0D3                  0x69
#define RXB0D4                  0x6A
#define RXB0D5                  0x6B
#define RXB0D6                  0x6C
#define RXB0D7                  0x6D
//**********************************************************************
//Message reception registers - buffer --> 1
//**********************************************************************
#define RXB1CTRL                0x70
#define RXB1SIDH                0x71
#define RXB1SIDL                0x72
#define RXB1EID8                0x73
#define RXB1EID0                0x74
#define RXB1DLC                 0x75
#define RXB1D0                  0x76
#define RXB1D1                  0x77
#define RXB1D2                  0x78
#define RXB1D3                  0x79
#define RXB1D4                  0x7A
#define RXB1D5                  0x7B
#define RXB1D6                  0x7C
#define RXB1D7                  0x7D
//**********************************************************************
//Control registers
//**********************************************************************
//!*************************************************************
//! BFPCTRL
//!*************************************************************
#define B1BFS		5
#define B0BFS		4
#define B1BFE		3
#define B0BFE		2
#define B1BFM		1
#define B0BFM		0

//!*************************************************************
//! TXRTSCTRL
//!*************************************************************
#define B2RTS		5
#define B1RTS		4
#define B0RTS		3
#define B2RTSM		2
#define B1RTSM		1
#define B0RTSM		0
//!*************************************************************
//! CANSTAT
//!*************************************************************
#define OPMOD2		7
#define OPMOD1		6
#define OPMOD0		5
#define ICOD2		3
#define ICOD1		2
#define ICOD0		1
//!*************************************************************
//! CANCTRL
//!*************************************************************
#define REQOP2		7
#define REQOP1		6
#define REQOP0		5
#define ABAT		4
#define CLKEN		2
#define CLKPRE1		1
#define CLKPRE0		0
//!*************************************************************
//! CNF3
//!*************************************************************
#define SOF			7
#define WAKFIL		6
#define PHSEG22		2
#define PHSEG21		1
#define PHSEG20		0
//!*************************************************************
//! CNF2
//!*************************************************************
#define BTLMODE		7
#define SAM			6
#define PHSEG12		5
#define PHSEG11		4
#define PHSEG10		3
#define PHSEG2		2
#define PHSEG1		1
#define PHSEG0		0
//!*************************************************************
//! CNF1
//!*************************************************************
#define SJW1		7
#define SJW0		6
#define BRP5		5
#define BRP4		4
#define BRP3		3
#define BRP2		2
#define BRP1		1
#define BRP0		0
//!*************************************************************
//! CANINTE
//!*************************************************************
#define MERRE		7
#define WAKIE		6
#define ERRIE		5
#define TX2IE		4
#define TX1IE		3
#define TX0IE		2
#define RX1IE		1
#define RX0IE		0
//!*************************************************************
//! CANINTF
//!*************************************************************
#define MERRF		7
#define WAKIF		6
#define ERRIF		5
#define TX2IF		4
#define TX1IF		3
#define TX0IF		2
#define RX1IF		1
#define RX0IF		0
//!*************************************************************
//! EFLG
//!*************************************************************
#define RX1OVR		7
#define RX0OVR		6
#define TXB0		5
#define TXEP		4
#define RXEP		3
#define TXWAR		2
#define RXWAR		1
#define EWARN		0
//!*************************************************************
//! TXBnCTRL (n = 0, 1, 2)
//!*************************************************************
#define ABTF		6
#define MLOA		5
#define TXERR		4
#define TXREQ		3
#define TXP1		1
#define TXP0		0
//!*************************************************************
//! RXB0CTRL
//!*************************************************************
#define RXM1		6
#define RXM0		5
#define RXRTR		3
#define BUKT		2
#define BUKT1		1
#define FILHIT0		0
//!*************************************************************
//! RXB1CTRL
//!*************************************************************
#define RSM1		6
#define FILHIT2		2
#define FILHIT1		1
//!*************************************************************
//! TXBnSIDL (n = 0, 1)
//!*************************************************************
#define EXIDE		3
//!*************************************************************
//! RXBnSIDL (n = 0, 1)
//!*************************************************************
#define SRR		4
#define IDE		3
//!*************************************************************
//! RXBnDLC (n = 0, 1) / TXBnDLC
//!*************************************************************
#define RTR			6
#define DLC3		3
#define DLC2		2
#define DLC1		1
#define DLC0		0

//!*************************************************************
//!					CAN in Automation (CiA)
//!*************************************************************

//**********************************************************************
// Standard OBD requests and responses
//**********************************************************************
#define ID_QUERY				0x7DF
#define ID_RESPONSE				0x7E8
//**********************************************************************
// Standars PIDs
//**********************************************************************

                                   //Mode PID	Data	ret.....Description...............min_val...max_val..units...formula

#define CALC_ENGINE_LOAD            0X04  //01 	04 		1 		Calculated engine load value 	  0 	100 	 % 	A*100/255
#define ENGINE_COOLANT_TEMP         0x05  //01 	05 		1 		Engine coolant temperature 	-40 	215 	°C 	A-40
#define SHORT_TERM_FUEL_1           0x06  //01 	06 		1 		Short term fuel % trim—Bank 1 	-100 (Rich) 	99.22 (Lean) 	 % 	(A-128) * 100/128
#define LONG_TERM_FUEL_1            0x07  //01 	07 		1 		Long term fuel % trim—Bank 1 	-100 (Rich) 	99.22 (Lean) 	 % 	(A-128) * 100/128
#define SHORT_TERM_FUEL_2           0x08  //01 	08 		1 		Short term fuel % trim—Bank 2 	-100 (Rich) 	99.22 (Lean) 	 % 	(A-128) * 100/128
#define LONG_TERM_FUEL_2            0x09  //01 	09 		1 		Long term fuel % trim—Bank 2 	-100 (Rich) 	99.22 (Lean) 	 % 	(A-128) * 100/128
#define O2_B1_S1_VOLTAGE            0x14  //01 	14 		2 		Bank 1, Sensor 1:Oxygen sensor voltage,Short term fuel trim 	0-100(lean)	1.275 99.2(rich) 	Volts % 	A/200(B-128) * 100/128 (if B==0xFF, sensor is not used in trim calc)
#define FUEL_PRESSURE               0x0A  //01 	0A 		1 		Fuel pressure 	0 	765 	kPa (gauge) 	A*3
#define INTAKE_M_A_PRESSURE         0x0B  //01 	0B 		1 		Intake manifold absolute pressure 	0 	255 	kPa (absolute) 	A
#define ENGINE_RPM                  0x0C  //01 	0C 		2 		Engine RPM 	0 	16,383.75 	rpm 	((A*256)+B)/4
#define VEHICLE_SPEED               0x0D  //01 	0D 		1 		Vehicle speed 	0 	255 	km/h 	A
#define TIMING_ADVANCE              0x0E  //01 	0E 		1 		Timing advance 	-64 	63.5 	° relative to #1 cylinder 	A/2 - 64
#define INTAKE_AIR_TEMP             0x0F  //01 	0F 		1 		Intake air temperature 	-40 	215 	°C 	A-40
#define MAF_AIR_FLOW_RATE           0x10  //01 	10 		2 		MAF air flow rate 	0 	655.35 	g/s 	((A*256)+B) / 100
#define THROTTLE_POSITION           0x11  //01 	11 		1 		Throttle position 	0 	100 	 % 	A*100/255
#define RUNTIME_SINCE_START         0x1F  //01 	1F 		2 		Run time since engine start 	0 	65,535 	seconds 	(A*256)+B
#define DISTANCE_WITH_MALF          0x21  //01 	21 		2 		Distance traveled with malfunction indicator lamp (MIL) on 	0 	65,535 	km 	(A*256)+B
#define FUEL_RAIL_PRESSURE_RELATIVE 0x22  //01 	22 		2 		Fuel Rail Pressure (relative to manifold vacuum) 	0 	5177.265 	kPa 	(((A*256)+B) * 10) / 128
#define FUEL_RAIL_PRESSURE_DIESEL   0x23  //01 	23 		2 		Fuel Rail Pressure (diesel) 	0 	655350 	kPa (gauge) 	((A*256)+B) * 10
#define FUEL_LEVEL                  0x2F  //01 	2F 		1 		Fuel Level Input 	0 	100 	 % 	100*A/255
#define NUM_WARMUPS_SINCE_CODES     0x30  //01 	30 		1 		# of warm-ups since codes cleared 	0 	255 	N/A 	A
#define DISTANCE_SINCE_CODES        0x31  //01 	31 		2 		Distance traveled since codes cleared 	0 	65,535 	km 	(A*256)+B
#define EVAP_SYSTEM_VAPOR_PRESSURE  0x32  //01 	32 		2 		Evap. System Vapor Pressure 	-8,192 	8,192 	Pa 	((A*256)+B)/4 (A is signed)
#define BAROMETRIC_PRESSURE         0x33  //01 	33 		1 		Barometric pressure 	0 	255 	kPa (Absolute) 	A
#define CONTROL_MODULE_VOLTAGE      0x42  //01 	42 		2 		Control module voltage 	0 	65.535 	V 	((A*256)+B)/1000
#define ABSOLUTE_LOAD_VALUE         0x43  //01 	43 		2 		Absolute load value 	0 	25,700 	 % 	((A*256)+B)*100/255
#define COMMAND_EQUIV_RATIO         0x44  //01 	44 		2 		Command equivalence ratio 	0 	2 	N/A 	((A*256)+B)/32768
#define REL_THROTTLE_POSITION       0x45  //01 	45 		1 		Relative throttle position 	0 	100 	 % 	A*100/255
#define AMBIENT_AIR_TEMPERATURE     0x46  //01 	46 		1 		Ambient air temperature 	-40 	215 	°C 	A-40
#define ABS_THROTTLE_POSITION_B     0x47  //01 	47 		1 		Absolute throttle position B 	0 	100 	 % 	A*100/255
#define ABS_THROTTLE_POSITION_C     0x48  //01 	48 		1 		Absolute throttle position C 	0 	100 	 % 	A*100/255
#define ABS_THROTTLE_POSITION_D     0x49  //01 	49 		1 		Accelerator pedal position D 	0 	100 	 % 	A*100/255
#define ABS_THROTTLE_POSITION_E     0x4A  //01 	4A 		1 		Accelerator pedal position E 	0 	100 	 % 	A*100/255
#define ABS_THROTTLE_POSITION_F     0x4B  //01 	4B 		1 		Accelerator pedal position F 	0 	100 	 % 	A*100/255
#define COMMANDED_THROTTLE_ACTUATOR 0x4C  //01 	4C 		1 		Commanded throttle actuator 	0 	100 	 % 	A*100/255
#define TIME_RUN_WITH_MIL_ON        0x4D  //01 	4D 		2 		Time run with MIL on 	0 	65,535 	minutes 	(A*256)+B
#define TIME_SINCE_T_CODES_CLEAR    0x4E  //01 	4E 		2 		Time since trouble codes cleared 	0 	65,535 	minutes 	(A*256)+B
#define FUEL_TYPE                   0x51  //01 	51 		1 		Fuel Type 				From fuel type table see below
#define ETHANOL_FUEL                0x52  //01 	52 		1 		Ethanol fuel % 	0 	100 	 % 	A*100/255
#define ABS_EVAP_SYST_VAPOUR_PRESS  0x53  //01 	53 		2 		Absoulute Evap system Vapour Pressure 	0 	327675 	kpa 	1/200 per bit
#define ENGINE_FUEL_RATE			0x5E  //01 	5E 		2 		Engine fuel rate 0 - 3212.75 		L/h		 ((A*256)+B)*0.05

#include <inttypes.h>

/***********************************************************************
 * Class
 ***********************************************************************/

class WaspCAN
{

	private:
		// Write a register of the MCP2515 using SPI
		void writeRegister( char direction, char data );
		// Read a register of the MCP2515 using SPI
		char readRegister(char direction);
		// Modify a bit of the MCP2515 using SPI
		void bitModify(char direction, char mask, char data);
		// Check the status of the MCP2515 registers
		char readStatus(char type);
		// Check if the buffers are empty
		bool checkFreeBuffer(void);
		// Reset MCP2515
		void reset(void);


	public:

/***********************************************************************
					Data structure
 ***********************************************************************/
		typedef struct{
				unsigned int id;
				struct
				{
				  char rtr : 1;
				  char length : 4;
				}header;

				uint8_t data[8];
		}messageCAN;

		// Receive buffer
		messageCAN messageRx;
		// Trasmit buffer
		messageCAN messageTx;

/***********************************************************************
					Functions
***********************************************************************/
		// Empty constructor
		WaspCAN(void);
		// Powers the CAN Bus module and opens the SPI
		bool ON(uint16_t speed);
		// Powers OFF the CAN Bus module
		void OFF(void );
		// Check if there is any message
		uint8_t messageAvailable(void);
		// Take the CAN message
		char getMessage(messageCAN *msje);
		// Send the CAN message
		char sendMessage(messageCAN *msje);
		// CAN message print out the serial port
		void printMessage(messageCAN *msje);
		// Configure the MCP2515
		void setMode(uint8_t mode);

/***********************************************************************
					CAN in Automation (CiA)
***********************************************************************/

		uint16_t getEngineLoad();
		uint16_t getEngineCoolantTemp();
		uint16_t getFuelPressure();
		uint16_t getIntakeMAPressure();
		uint16_t getEngineRPM();
		uint16_t getVehicleSpeed();
		uint16_t getTimingAdvance();
		uint16_t getIntankeAirTemp();
		uint16_t getMAFairFlowRate();
		uint8_t getThrottlePosition();
		uint8_t getFuelLevel();
		uint8_t getBarometricPressure();
		uint16_t getEngineFuelRate();

		// General Function
		void CiARequest(uint8_t PID);
};

extern WaspCAN CAN;

#endif
