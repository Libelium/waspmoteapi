/*
 *  Revised for Waspmote by D. Cuartielles & A. Bielsa, 2009
 *
 *  Copyright (c) 2005 David A. Mellis
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
 *  Design:		David Gascón
 *  Implementation:	David A.Mellis, David Cuartielles, Alberto Bielsa
 */


#include <avr/io.h>
#include "wiring_private.h"
#include "pins_waspmote.h"

// On the Wasp board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.
//
// ATMEL ATMEGA1281 / WASP
//
//                  
//                               A  G  A  P  P  P  P  P  P  P  P  G  V  P  P  P
//                               V  N  R  F  F  F  F  F  F  F  F  N  C  A  A  A
//                               C  D  F  0  1  2  3  4  5  6  7  D  C  0  1  2
//
//                              _64_63_62_61_60_59_58_57_56_55_54_53_52_51_50_49__
//                             /O                                                 |
//   (   )             PG5   1|                                                   |48 PA3
//   (D 0)             PE1   2|                                                   |47 PA4
//   (   )             PE1   3|                                                   |46 PA5
//   (   )             PE2   4|                                                   |45 PA6
//   (   )             PE3   5|                                                   |44 PA7
//   (   )             PE4   6|                                                   |43 PG2
//   (   )             PE5   7|                                                   |42 PC7
//   (   )             PE6   8|                                                   |41 PC6
//   SOFT LED (LED4) - PE7   9|                                                   |40 PC5
//   (   )             PB0  10|                                                   |39 PC4
//   (   )             PB1  11|                                                   |38 PC3
//   (   )             PB2  12|                                                   |37 PC2
//   (   )             PB3  13|                                                   |36 PC1 - SOFT LED (LED3)
//   (   )             PB4  14|                                                   |35 PC0
//   (   )             PB5  15|                                                   |34 PG1
//   (   )             PB6  16|                                                   |33 PG0
//                            |___________________________________________________| 
//                               17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
//  
//                               P  P  P  R  V  G  X  X  P  P  P  P  P  P  P  P
//                               B  G  G  S  C  N  T  T  D  D  D  D  D  D  D  D
//                               7  3  4  T  C  D  2  1  0  1  2  3  4  5  6  7 
//


#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint8_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	&DDRA,
	&DDRB,
	&DDRC,
	&DDRD,
	&DDRE,
	&DDRF,
	&DDRG,
};

const uint8_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	&PORTA,
	&PORTB,
	&PORTC,
	&PORTD,
	&PORTE,
	&PORTF,
	&PORTG,
};

const uint8_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PORT,
	&PINA,
	&PINB,
	&PINC,
	&PIND,
	&PINE,
	&PINF,
	&PING,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	//			PORT	PIN		WASP API PIN		DESCRIPTION
	PE	,	//	PE	0	**	0	**	USB_XBEE_RX
	PE	,	//	PE	1	**	1	**	USB_XBEE_TX
	PE	,	//	PE	3	**	2	**	DIGITAL1
	PE	,	//	PE	4	**	3	**	DIGITAL0
	PC	,	//	PC	4	**	4	**	DIGITAL7
	PC	,	//	PC	5	**	5	**	DIGITAL8
	PC	,	//	PC	6	**	6	**	DIGITAL6
	PC	,	//	PC	7	**	7	**	DIGITAL5
	PA	,	//	PA	2	**	8	**	DIGITAL2
	PA	,	//	PA	3	**	9	**	DIGITAL4
	PA	,	//	PA	4	**	10	**	DIGITAL3
	PD	,	//	PD	5	**	11	**	DIGITAL9
	PD	,	//	PD	6	**	12	**	LED0
	PC	,	//	PC	1	**	13	**	LED1
	PF	,	//	PF	1	**	14	**	ANA0
	PF	,	//	PF	2	**	15	**	ANA1
	PF	,	//	PF	3	**	16	**	ANA2
	PF	,	//	PF	4	**	17	**	ANA3
	PF	,	//	PF	5	**	18	**	ANA4
	PF	,	//	PF	6	**	19	**	ANA5
	PF	,	//	PF	7	**	20	**	ANA6
	PF	,	//	PF	0	**	21	**	BAT_MONITOR
	PA	,	//	PA	1	**	22	**	XBEE_PW
	PD	,	//	PD	7	**	23	**	XBEE SLEEP
	PE	,	//	PE	5	**	24	**	SENS_PW_5V
	PA	,	//	PA	6	**	25	**	BAT_MONITOR_PW
	PE	,	//	PE	2	**	26	**	SENS_PW_3v3
	PA	,	//	PA	5	**	27	**	MEM_PW
	PC	,	//	PC	0	**	28	**	SD_PRESENT
	PB	,	//	PB	0	**	29	**	SD_SS
	PB	,	//	PB	1	**	30	**	SD_SCK
	PB	,	//	PB	2	**	31	**	SD_MOSI
	PB	,	//	PB	3	**	32	**	SD_MISO
	PB	,	//	PB	4	**	33	**	SERID_PW
	PB	,	//	PB	5	**	34	**	SERID_IN
	PA	,	//	PA	0	**	35	**	GPS_PW
	PB	,	//	PB	6	**	36	**	GPS_RX
	PB	,	//	PB	7	**	37	**	GPS_TX
	PE	,	//	PE	6	**	38	**	RDY_ACC
	PE	,	//	PE	7	**	39	**	RST_RTC
	PD	,	//	PD	0	**	40	**	I2C_SCL
	PD	,	//	PD	1	**	41	**	I2C_SDA
	PC	,	//	PC	3	**	42	**	GPRS_PW
	PD	,	//	PD	2	**	43	**	GPRS_RX
	PD	,	//	PD	3	**	44	**	GPRS_TX
	PA	,	//	PA	7	**	45	**	BOOT PIN
	PC	,	//	PC	2	**	46	**	PWON
	PD	,	//	PD	4	**	47	**	FREE PIN
	PG	,	//	PG	2	**	48	**	RTC_PW
	PG	,	//	PG	1	**	49	**	RTC_SLEEP
  	PG	,	//	PG	0	**	50	**	LOW_BAT_MON
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	//	PIN				PORT	PIN		WASP API PIN		DESCRIPTION
	_BV(	0	)	,	//	PE	0	**	0	**	USB_XBEE_RX
	_BV(	1	)	,	//	PE	1	**	1	**	USB_XBEE_TX
	_BV(	3	)	,	//	PE	3	**	2	**	DIGITAL1
	_BV(	4	)	,	//	PE	4	**	3	**	DIGITAL0
	_BV(	4	)	,	//	PC	4	**	4	**	DIGITAL7
	_BV(	5	)	,	//	PC	5	**	5	**	DIGITAL8
	_BV(	6	)	,	//	PC	6	**	6	**	DIGITAL6
	_BV(	7	)	,	//	PC	7	**	7	**	DIGITAL5
	_BV(	2	)	,	//	PA	2	**	8	**	DIGITAL2
	_BV(	3	)	,	//	PA	3	**	9	**	DIGITAL4
	_BV(	4	)	,	//	PA	4	**	10	**	DIGITAL3
	_BV(	5	)	,	//	PD	5	**	11	**	DIGITAL9
	_BV(	6	)	,	//	PD	6	**	12	**	LED0
	_BV(	1	)	,	//	PC	1	**	13	**	LED1
	_BV(	1	)	,	//	PF	1	**	14	**	ANA0
	_BV(	2	)	,	//	PF	2	**	15	**	ANA1
	_BV(	3	)	,	//	PF	3	**	16	**	ANA2
	_BV(	4	)	,	//	PF	4	**	17	**	ANA3
	_BV(	5	)	,	//	PF	5	**	18	**	ANA4
	_BV(	6	)	,	//	PF	6	**	19	**	ANA5
	_BV(	7	)	,	//	PF	7	**	20	**	ANA6
	_BV(	0	)	,	//	PF	0	**	21	**	BAT_MONITOR
	_BV(	1	)	,	//	PA	1	**	22	**	XBEE_PW
	_BV(	7	)	,	//	PD	7	**	23	**	XBEE SLEEP
	_BV(	5	)	,	//	PE	5	**	24	**	SENS_PW_5V
	_BV(	6	)	,	//	PA	6	**	25	**	BAT_MONITOR_PW
	_BV(	2	)	,	//	PE	2	**	26	**	SENS_PW_3v3
	_BV(	5	)	,	//	PA	5	**	27	**	MEM_PW
	_BV(	0	)	,	//	PC	0	**	28	**	SD_PRESENT
	_BV(	0	)	,	//	PB	0	**	29	**	SD_SS
	_BV(	1	)	,	//	PB	1	**	30	**	SD_SCK
	_BV(	2	)	,	//	PB	2	**	31	**	SD_MOSI
	_BV(	3	)	,	//	PB	3	**	32	**	SD_MISO
	_BV(	4	)	,	//	PB	4	**	33	**	SERID_PW
	_BV(	5	)	,	//	PB	5	**	34	**	SERID_IN
	_BV(	0	)	,	//	PA	0	**	35	**	GPS_PW
	_BV(	6	)	,	//	PB	6	**	36	**	GPS_RX
	_BV(	7	)	,	//	PB	7	**	37	**	GPS_TX
	_BV(	6	)	,	//	PE	6	**	38	**	RDY_ACC
	_BV(	7	)	,	//	PE	7	**	39	**	RST_RTC
	_BV(	0	)	,	//	PD	0	**	40	**	I2C_SCL
	_BV(	1	)	,	//	PD	1	**	41	**	I2C_SDA
	_BV(	3	)	,	//	PC	3	**	42	**	GPRS_PW
	_BV(	2	)	,	//	PD	2	**	43	**	GPRS_RX
	_BV(	3	)	,	//	PD	3	**	44	**	GPRS_TX
	_BV(	7	)	,	//	PA	7	**	45	**	BOOT PIN
	_BV(	2	)	,	//	PC	2	**	46	**	PWON
	_BV(	4	)	,	//	PD	4	**	47	**	FREE PIN
	_BV(	2	)	,	//	PG	2	**	48	**	RTC_PW
	_BV(	1	)	,	//	PG	1	**	49	**	RTC_SLEEP
	_BV(	0	)	,	//	PG	0	**	50	**	LOW_BAT_MON

};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	//			PORT	PIN		WASP API PIN		DESCRIPTION
	NOT_ON_TIMER	,	//	PE	0	**	0	**	USB_XBEE_RX
	NOT_ON_TIMER	,	//	PE	1	**	1	**	USB_XBEE_TX
	TIMER3A		,	//	PE	3	**	2	**	DIGITAL1
	TIMER3B		,	//	PE	4	**	3	**	DIGITAL0
	NOT_ON_TIMER	,	//	PC	4	**	4	**	DIGITAL7
	NOT_ON_TIMER	,	//	PC	5	**	5	**	DIGITAL8
	NOT_ON_TIMER	,	//	PC	6	**	6	**	DIGITAL6
	NOT_ON_TIMER	,	//	PC	7	**	7	**	DIGITAL5
	NOT_ON_TIMER	,	//	PA	2	**	8	**	DIGITAL2
	NOT_ON_TIMER	,	//	PA	3	**	9	**	DIGITAL4
	NOT_ON_TIMER	,	//	PA	4	**	10	**	DIGITAL3
	NOT_ON_TIMER	,	//	PD	5	**	11	**	DIGITAL9
	NOT_ON_TIMER	,	//	PD	6	**	12	**	LED0
	NOT_ON_TIMER	,	//	PC	1	**	13	**	LED1
	NOT_ON_TIMER	,	//	PF	1	**	14	**	ANA0
	NOT_ON_TIMER	,	//	PF	2	**	15	**	ANA1
	NOT_ON_TIMER	,	//	PF	3	**	16	**	ANA2
	NOT_ON_TIMER	,	//	PF	4	**	17	**	ANA3
	NOT_ON_TIMER	,	//	PF	5	**	18	**	ANA4
	NOT_ON_TIMER	,	//	PF	6	**	19	**	ANA5
	NOT_ON_TIMER	,	//	PF	7	**	20	**	ANA6
	NOT_ON_TIMER	,	//	PF	0	**	21	**	BAT_MONITOR
	NOT_ON_TIMER	,	//	PA	1	**	22	**	XBEE_PW
	NOT_ON_TIMER	,	//	PD	7	**	23	**	XBEE SLEEP
	NOT_ON_TIMER	,	//	PE	5	**	24	**	SENS_PW_5V
	NOT_ON_TIMER	,	//	PA	6	**	25	**	BAT_MONITOR_PW
	NOT_ON_TIMER	,	//	PE	2	**	26	**	SENS_PW_3v3
	NOT_ON_TIMER	,	//	PA	5	**	27	**	MEM_PW
	NOT_ON_TIMER	,	//	PC	0	**	28	**	SD_PRESENT
	NOT_ON_TIMER	,	//	PB	0	**	29	**	SD_SS
	NOT_ON_TIMER	,	//	PB	1	**	30	**	SD_SCK
	NOT_ON_TIMER	,	//	PB	2	**	31	**	SD_MOSI
	NOT_ON_TIMER	,	//	PB	3	**	32	**	SD_MISO
	NOT_ON_TIMER	,	//	PB	4	**	33	**	SERID_PW
	NOT_ON_TIMER	,	//	PB	5	**	34	**	SERID_IN
	NOT_ON_TIMER	,	//	PA	0	**	35	**	GPS_PW
	NOT_ON_TIMER	,	//	PB	6	**	36	**	GPS_RX
	NOT_ON_TIMER	,	//	PB	7	**	37	**	GPS_TX
	NOT_ON_TIMER	,	//	PE	6	**	38	**	RDY_ACC
	NOT_ON_TIMER	,	//	PE	7	**	39	**	RST_RTC
	NOT_ON_TIMER	,	//	PD	0	**	40	**	I2C_SCL
	NOT_ON_TIMER	,	//	PD	1	**	41	**	I2C_SDA
	NOT_ON_TIMER	,	//	PC	3	**	42	**	GPRS_PW
	NOT_ON_TIMER	,	//	PD	2	**	43	**	GPRS_RX
	NOT_ON_TIMER	,	//	PD	3	**	44	**	GPRS_TX
	NOT_ON_TIMER	,	//	PA	7	**	45	**	BOOT PIN
	NOT_ON_TIMER	,	//	PC	2	**	46	**	PWON
	NOT_ON_TIMER	,	//	PD	4	**	47	**	FREE PIN
	NOT_ON_TIMER	,	//	PG	2	**	48	**	RTC_PW
	NOT_ON_TIMER	,	//	PG	1	**	49	**	RTC_SLEEP
	NOT_ON_TIMER	,	//	PG	0	**	50	**	LOW_BAT_MON

};

