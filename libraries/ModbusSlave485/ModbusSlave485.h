/* file ModbusSlave485.cpp
 * 
 * ModbusSlave library implementing a Modbus RTU Slave for Waspmote
 * Modified by S.Marco. mailto:sammarcoarmengol@gmail.com
 * Based on the work published by jpmzometa at 
 * http://sites.google.com/site/jpmzometa/arduino-mbrt
 * 
 * Based also on http://pcscada.com.au by P.Costigan email: phil@pcscada.com.au
 * 
 * These library of functions are designed to enable a program send and
 * receive data from a device that communicates using the Modbus protocol.
 * 
 * Copyright (C) 2000 Philip Costigan  P.C. SCADA LINK PTY. LTD.
 * 
 * This file is part of ModbusSlave.
 * 
 * ModbusSlave is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * 
 * The functions included here have been derived from the 
 * Modbus Specifications and Implementation Guides
 * 
 * http://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf
 * http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b.pdf
 * http://www.modbus.org/docs/PI_MBUS_300.pdf
 * 
 ****************************************************************************/

/****************************************************************************
 * BEGIN MODBUS RTU SLAVE FUNCTIONS
 ****************************************************************************/

#ifndef MODBUS_SLAVE_H
#define MODBUS_SLAVE_H

#include <inttypes.h>

class ModbusSlave485 {
	
private:
  unsigned char slave;
  char txenpin;

  unsigned int crc(unsigned char *buf, unsigned char start, unsigned char cnt);
  void build_read_packet(unsigned char function, unsigned char count, unsigned char *packet);
  void build_write_packet(unsigned char function, unsigned int start_addr, unsigned char count, unsigned char *packet);
  void build_write_single_packet(unsigned char function, unsigned int write_addr, unsigned int reg_val, unsigned char* packet);
  void build_error_packet(unsigned char function,unsigned char exception, unsigned char *packet);
  void modbus_reply(unsigned char *packet, unsigned char string_length);
  int send_reply(unsigned char *query, unsigned char string_length);
  int receive_request(unsigned char *received_string);
  int modbus_request(unsigned char *data);
  int validate_request(unsigned char *data, unsigned char length, unsigned int regs_size);
  int write_regs(unsigned int start_addr, unsigned char *query, int *regs);
  int preset_multiple_registers(unsigned int start_addr,unsigned char count,unsigned char *query,int *regs);
  int read_holding_registers(unsigned int start_addr, unsigned char reg_count, int *regs);
  int write_single_register(unsigned int write_addr, unsigned char *query, int *regs);  
  void configure(long baud, char parity, char txenpin);
  
public:
/* 
 * configure(slave, baud, parity, txenpin)
 *
 * sets the communication parameters for of the serial line.
 *
 * slave: identification number of the slave in the Modbus network (1 to 127)
 * baud: baudrate in bps (typical values 9600, 19200... 115200)

 */
  void configure(unsigned char slave, long baud);

/*
 * update(regs, regs_size)
 * 
 * checks if there is any valid request from the modbus master. If there is,
 * performs the requested action
 * 
 * regs: an array with the holding registers. They start at address 1 (master point of view)
 * regs_size: total number of holding registers, i.e. the size of the array regs.
 * returns: 0 if no request from master,
 * 	NO_REPLY (-1) if no reply is sent to the master
 * 	an exception code (1 to 4) in case of a modbus exceptions
 * 	the number of bytes sent as reply ( > 4) if OK.
 */
  int update(int *regs, unsigned int regs_size); 

  // empty constructor
  ModbusSlave485()
  {
  
  }

};

#endif
