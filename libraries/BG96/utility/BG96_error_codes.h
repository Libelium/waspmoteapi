/*! \file BG96_CME_ERROR_CODEs.h
  \brief Definition of the possible error codes
    
  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
  http:// www.libelium.com
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 2.1 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public License
  along with this program. If not, see <http:// www.gnu.org/licenses/>.
 
  Version:			3.0
  Design:			David Gascon
  Implementation:	Yuri Carmona

 */

#ifndef BG96_ERRORCODE_H_
#define BG96_ERRORCODE_H_

//! ERROR CODES for the BG96 library

////////////////////////////////////////////////////////////////////////////////
// Syntax: +CME ERROR: <err> 
////////////////////////////////////////////////////////////////////////////////

// General errors:
#define BG96_CME_ERROR_0000 0  // phone failure
#define BG96_CME_ERROR_0001 1  // No connection to phone
#define BG96_CME_ERROR_0002 2  // phone-adaptor link reserved
#define BG96_CME_ERROR_0003 3  // operation not allowed
#define BG96_CME_ERROR_0004 4  // operation not supported
#define BG96_CME_ERROR_0005 5  // PH-SIM PIN required
#define BG96_CME_ERROR_0010 10 // SIM not inserted
#define BG96_CME_ERROR_0011 11 // SIM PIN required
#define BG96_CME_ERROR_0012 12 // SIM PUK required
#define BG96_CME_ERROR_0013 13 // SIM failure
#define BG96_CME_ERROR_0014 14 // SIM busy
#define BG96_CME_ERROR_0015 15 // SIM wrong
#define BG96_CME_ERROR_0016 16 // incorrect password
#define BG96_CME_ERROR_0017 17 // SIM PIN2 required
#define BG96_CME_ERROR_0018 18 // SIM PUK2 required
#define BG96_CME_ERROR_0020 20 // memory full
#define BG96_CME_ERROR_0021 21 // invalid index
#define BG96_CME_ERROR_0022 22 // not found
#define BG96_CME_ERROR_0023 23 // memory failure
#define BG96_CME_ERROR_0024 24 // text string too long
#define BG96_CME_ERROR_0025 25 // invalid characters in text string
#define BG96_CME_ERROR_0026 26 // dial string too long
#define BG96_CME_ERROR_0027 27 // invalid characters in dial string
#define BG96_CME_ERROR_0030 30 // no network service
#define BG96_CME_ERROR_0031 31 // network time-out
#define BG96_CME_ERROR_0032 32 // network not allowed - emergency calls only
#define BG96_CME_ERROR_0040 40 // network personalization PIN required
#define BG96_CME_ERROR_0041 41 // network personalization PUK required
#define BG96_CME_ERROR_0042 42 // network subset personalization PIN required
#define BG96_CME_ERROR_0043 43 // network subset personalization PUK required
#define BG96_CME_ERROR_0044 44 // service provider personalization PIN required
#define BG96_CME_ERROR_0045 45 // Service provider personalization PUK required
#define BG96_CME_ERROR_0046 46 // corporate personalization PIN required
#define BG96_CME_ERROR_0047 47 // corporate personalization PUK required

// General purpose error:
#define BG96_CME_ERROR_0100 100 // unknown
#define BG96_CME_ERROR_0770 770 // SIM invalid

// GPRS related errors to a failure to perform an Attach:
#define BG96_CME_ERROR_0103 103 // Illegal MS (#3)*
#define BG96_CME_ERROR_0106 106 // Illegal ME (#6)*
#define BG96_CME_ERROR_0107 107 // GPRS service not allowed (#7)*
#define BG96_CME_ERROR_0111 111 // PLMN not allowed (#11)*
#define BG96_CME_ERROR_0112 112 // Location area not allowed (#12)*
#define BG96_CME_ERROR_0113 113 // Roaming not allowed in this location area (#13)*

// GPRS related errors to a failure to Activate a Context and others:
#define BG96_CME_ERROR_0132 132 // service option not supported (#32)*
#define BG96_CME_ERROR_0133 133 // requested service option not subscribed (#33)*
#define BG96_CME_ERROR_0134 134 // service option temporarily out of order (#34)*
#define BG96_CME_ERROR_0148 148 // unspecified GPRS error
#define BG96_CME_ERROR_0149 149 // PDP authentication failure
#define BG96_CME_ERROR_0150 150 // invalid mobile class

#define BG96_CME_ERROR_0407 407 // File already existed

// Easy GPRS® related errors:
#define BG96_CME_ERROR_0550 550 // generic undocumented error
#define BG96_CME_ERROR_0551 551 // wrong state
#define BG96_CME_ERROR_0552 552 // wrong mode
#define BG96_CME_ERROR_0553 553 // context already activated
#define BG96_CME_ERROR_0554 554 // stack already active
#define BG96_CME_ERROR_0555 555 // activation failed
#define BG96_CME_ERROR_0556 556 // context not opened
#define BG96_CME_ERROR_0557 557 // cannot setup socket
#define BG96_CME_ERROR_0558 558 // cannot resolve DN
#define BG96_CME_ERROR_0559 559 // time-out in opening socket
#define BG96_CME_ERROR_0560 560 // cannot open socket
#define BG96_CME_ERROR_0561 561 // remote disconnected or time-out
#define BG96_CME_ERROR_0562 562 // connection failed
#define BG96_CME_ERROR_0563 563 // tx error
#define BG96_CME_ERROR_0564 564 // already listening
#define BG96_CME_ERROR_0568 568 // wrong PDP

// FTP related errors
#define BG96_CME_ERROR_0615 615 // FTP not connected
#define BG96_CME_ERROR_0623 623 // FTP write data closed
#define BG96_CME_ERROR_0642 642 // FTP open channel timeout
#define BG96_CME_ERROR_0643 643 // FTP communication timeout

// Network survey errors:
#define BG96_CME_ERROR_0657 657 // Network survey error (No Carrier)*
#define BG96_CME_ERROR_0658 658 // Network survey error (Busy)*
#define BG96_CME_ERROR_0659 659 // Network survey error (Wrong request)*
#define BG96_CME_ERROR_0660 660 // Network survey error (Aborted)*

// Supplementary service related error:
#define BG96_CME_ERROR_0257 257 // network rejected request
#define BG96_CME_ERROR_0258 258 // retry operation
#define BG96_CME_ERROR_0259 259 // invalid deflected to number
#define BG96_CME_ERROR_0260 260 // deflected to own number
#define BG96_CME_ERROR_0261 261 // unknown subscriber
#define BG96_CME_ERROR_0262 262 // service not available
#define BG96_CME_ERROR_0263 263 // unknown class specified
#define BG96_CME_ERROR_0264 264 // unknown network message

// AT+COPS test command related error:
#define BG96_CME_ERROR_0680 680 // LU processing
#define BG96_CME_ERROR_0681 681 // Network search aborted
#define BG96_CME_ERROR_0682 682 // PTM mode

// AT+WS46 test command related error:
#define BG96_CME_ERROR_0683 683 // Active call state
#define BG96_CME_ERROR_0684 684 // SSL already activated



////////////////////////////////////////////////////////////////////////////////
// Syntax: +CMS ERROR: <err> 
////////////////////////////////////////////////////////////////////////////////
#define BG96_CMS_ERROR_0300 300  // ME failure
#define BG96_CMS_ERROR_0301 301  // SMS service of ME reserved
#define BG96_CMS_ERROR_0302 302  // operation not allowed
#define BG96_CMS_ERROR_0303 303  // operation not supported
#define BG96_CMS_ERROR_0304 304  // invalid PDU mode parameter
#define BG96_CMS_ERROR_0305 305  // invalid text mode parameter
#define BG96_CMS_ERROR_0310 310  // SIM not inserted
#define BG96_CMS_ERROR_0311 311  // SIM PIN required
#define BG96_CMS_ERROR_0312 312  // PH-SIM PIN required
#define BG96_CMS_ERROR_0313 313  // SIM failure
#define BG96_CMS_ERROR_0314 314  // SIM busy
#define BG96_CMS_ERROR_0315 315  // SIM wrong 
#define BG96_CMS_ERROR_0316 316  // SIM PUK required
#define BG96_CMS_ERROR_0317 317  // SIM PIN2 required
#define BG96_CMS_ERROR_0318 318  // SIM PUK2 required
#define BG96_CMS_ERROR_0320 320  // memory failure
#define BG96_CMS_ERROR_0321 321  // invalid memory index
#define BG96_CMS_ERROR_0322 322  // memory full
#define BG96_CMS_ERROR_0330 330  // SMSC address unknown
#define BG96_CMS_ERROR_0331 331  // no network service
#define BG96_CMS_ERROR_0332 332  // network time-out
#define BG96_CMS_ERROR_0340 340  // no +CNMA acknowledgement expected
#define BG96_CMS_ERROR_0500 500  // unknown error

#define BG96_CME_ERROR_1000 1000 // SSL not activated
#define BG96_CME_ERROR_1001 1001 // SSL certs and keys wrong or not stored
#define BG96_CME_ERROR_1003 1003 // SSL already activated
#define BG96_CME_ERROR_1005 1005 // SSL socket error
#define BG96_CME_ERROR_1008 1008 // SSL not connected

#define BG96_ERROR_TIMEOUT 65534 // Timeout error when running a command
#define BG96_ERROR_MESSAGE 65535 // "ERROR"


#endif /* ATI_ERRORCODE_H_ */
