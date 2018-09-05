/*
 *  Copyright (c) 2005 David A. Mellis
 * 	Revised for Waspmote by D. Cuartielles & A. Bielsa, 2009
 * 	Revised for Waspmote by Libelium, 2016
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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	D.Mellis, D. Cuartielles, M. Yarza, Y. Carmona
 */

#ifndef Pins_Waspmote_h
#define Pins_Waspmote_h

#include <avr/pgmspace.h>

// GIVE NAMES TO THE WHOLE PINOUT FOR WASP
//	DESCRIPTION			PIN		PORT		PIN		WASP API PIN		DESCRIPTION
#define	USB_XBEE_RX		0	//	PE	0	**	0	**	USB_XBEE_RX
#define	USB_XBEE_TX		1	//	PE	1	**	1	**	USB_XBEE_TX
#define	DIGITAL1		2	//	PE	3	**	2	**	DIGITAL1        -- PWM1 BEFORE
#define	DIGITAL0		3	//	PE	4	**	3	**	DIGITAL0        -- PWM2 BEFORE
#define	DIGITAL7		4	//	PC	4	**	4	**	DIGITAL7        -- DIG0 BEFORE
#define	DIGITAL8		5	//	PC	5	**	5	**	DIGITAL8        -- DIG1 BEFORE
#define	DIGITAL6		6	//	PC	6	**	6	**	DIGITAL6        -- DIG2 BEFORE
#define	DIGITAL5		7	//	PC	7	**	7	**	DIGITAL5        -- DIG3 BEFORE
#define	DIGITAL2		8	//	PA	2	**	8	**	DIGITAL2        -- DIG4 BEFORE
#define	DIGITAL4		9	//	PA	3	**	9	**	DIGITAL4        -- DIG5 BEFORE
#define	DIGITAL3		10	//	PA	4	**	10	**	DIGITAL3        -- DIG6 BEFORE
#define	MUX_USB_XBEE	11	//	PD	5	**	11	**	DIGITAL9        -- DIG7 BEFORE
#define	LED0			12	//	PD	6	**	12	**	LED0
#define	LED1			13	//	PC	1	**	13	**	LED1
#define	ANA0			14	//	PF	1	**	14	**	ANA0
#define	ANA1			15	//	PF	2	**	15	**	ANA1
#define	ANA2			16	//	PF	3	**	16	**	ANA2
#define	ANA3			17	//	PF	4	**	17	**	ANA3
#define	ANA4			18	//	PF	5	**	18	**	ANA4
#define	ANA5			19	//	PF	6	**	19	**	ANA5
#define	ANA6			20	//	PF	7	**	20	**	ANA6
#define	BAT_MONITOR		21	//	PF	0	**	21	**	BAT_MONITOR
#define	SOCKET0_PW		22	//	PA	1	**	22	**	SOCKET0_PW
#define	MUX_PW			23	//	PD	7	**	23	**	MUX_PW (Waspmote v12)
#define	MUX1_PW			23	//	PD	7	**	23	**	MUX1_PW (Waspmote v15)
#define	SENS_PW_5V		24	//	PE	5	**	24	**	SENS_PW_5V
#define	BAT_MONITOR_PW	25	//	PA	6	**	25	**	BAT_MONITOR_PW
#define	SENS_PW_3V3		26	//	PE	2	**	26	**	SENS_PW_3v3
#define	MEM_PW			27	//	PA	5	**	27	**	MEM_PW
#define	SD_PRESENT		28	//	PC	0	**	28	**	SD_PRESENT
#define	SD_SS			29	//	PB	0	**	29	**	SD_SS
#define	SD_SCK			30	//	PB	1	**	30	**	SD_SCK
#define	SD_MOSI			31	//	PB	2	**	31	**	SD_MOSI
#define	SD_MISO			32	//	PB	3	**	32	**	SD_MISO
#define	HIB_PIN			33	//	PB	4	**	33	**	HIB_PIN
#define	SOCKET0_SS		34	//	PB	5	**	34	**	SOCKET0_SS
#define	GPS_PW			35	//	PA	0	**	35	**	GPS_PW
#define	MUX1_0			36	//	PB	6	**	36	**	MUX1_0
#define	MUX1_1			37	//	PB	7	**	37	**	MUX1_1
#define	RDY_ACC			38	//	PE	6	**	38	**	RDY_ACC
#define	RST_RTC			39	//	PE	7	**	39	**	RST_RTC
#define	I2C_SCL			40	//	PD	0	**	40	**	I2C_SCL
#define	I2C_SDA			41	//	PD	1	**	41	**	I2C_SDA
#define	GPRS_PW			42	//	PC	3	**	42	**	GPRS_PW
#define	MUX_RX			43	//	PD	2	**	43	**	GPS/Socket1/Aux1/Aux2_RX
#define	MUX_TX			44	//	PD	3	**	44	**	GPS/Socket1/Aux1/Aux2_TX
#define	XBEE_MON		45	//	PA	7	**	45	**	XBEE_MON
#define	GPRS_PIN		46	//	PC	2	**	46	**	GPRS_PIN
#define	XBEE_SLEEP		47	//	PD	4	**	47	**	XBEE_SLEEP
#define MUX0_PW			48	//	PG	2	**	48	**	MUX0_PW (Waspmote v15)
#define RTC_PW			48	//	PG	2	**	48	**	RTC_PW (Waspmote v12)
#define	RTC_SLEEP		49	//	PG	1	***	49	**	RTC_SLEEP
#define	POWER_3V3		50	//	PG	0	**	50	**	MAIN POWER_3V3 (Waspmote v15)
#define CHG_IND			51	//  PG  3   **  51  **  CHG_IND (Waspmote v15)
#define SPI_ON			52	//  PG  4   **  52  **  SPI_ON (Waspmote v15)

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER2  5
#define TIMER2A 6
#define TIMER2B 7
#define TIMER3A 8
#define TIMER3B 9
#define TIMER3C 10

extern const uint8_t PROGMEM port_to_mode_PGM[];
extern const uint8_t PROGMEM port_to_input_PGM[];
extern const uint8_t PROGMEM port_to_output_PGM[];

extern const uint8_t PROGMEM digital_pin_to_port_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[];

extern const uint8_t PROGMEM digital_pin_to_timer_PGM[];

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
// 
// These perform slightly better as macros compared to inline functions
//
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) ( (volatile uint8_t *)( (uint16_t)pgm_read_byte( (port_to_output_PGM + (P)))) )
#define portInputRegister(P) ( (volatile uint8_t *)( (uint16_t)pgm_read_byte( port_to_input_PGM + (P))) )
#define portModeRegister(P) ( (volatile uint8_t *)( (uint16_t)pgm_read_byte( port_to_mode_PGM + (P))) )

#endif
