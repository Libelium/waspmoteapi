/*! \file ati_error_codes.h
  \brief Definition of the possible error codes
    
  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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

#ifndef ATI_ERRORCODE_H_
#define ATI_ERRORCODE_H_

//! ERROR CODES for the AT+i library
#define ERROR_CODE_0000 0  // Common Waspmote API timeout error
#define ERROR_CODE_0010 10 // Waspmote API: SD not present
#define ERROR_CODE_0011 11 // Waspmote API: SD file not created
#define ERROR_CODE_0012 12 // Waspmote API: SD error opening file
#define ERROR_CODE_0013 13 // Waspmote API: SD error setting file offset
#define ERROR_CODE_0014 14 // Waspmote API: SD error writing
#define ERROR_CODE_0020 20 // Waspmote API: rx buffer full
#define ERROR_CODE_0021 21 // Waspmote API: error downloading UPGRADE.TXT
#define ERROR_CODE_0022 22 // Waspmote API: filename in UPGRADE.TXT is not a 7-byte name
#define ERROR_CODE_0023 23 // Waspmote API: no FILE label is found in UPGRADE.TXT
#define ERROR_CODE_0024 24 // Waspmote API: NO_FILE is defined as FILE in UPGRADE.TXT
#define ERROR_CODE_0025 25 // Waspmote API: no PATH label is found in UPGRADE.TXT
#define ERROR_CODE_0026 26 // Waspmote API: no SIZE label is found in UPGRADE.TXT
#define ERROR_CODE_0027 27 // Waspmote API: no VERSION label is found in UPGRADE.TXT
#define ERROR_CODE_0028 28 // Waspmote API: version indicated in UPGRADE.TXT is lower/equal to Waspmote's version
#define ERROR_CODE_0029 29 // Waspmote API: file size does not match the indicated in UPGRADE.TXT
#define ERROR_CODE_0030 30 // Waspmote API: error downloading binary file    
#define ERROR_CODE_0031 31 // Waspmote API: invalid data length
#define ERROR_CODE_0041 41 // Illegal delimiter 
#define ERROR_CODE_0042 42 // Illegal value
#define ERROR_CODE_0043 43 // CR expected 
#define ERROR_CODE_0044 44 // Number expected
#define ERROR_CODE_0045 45 // CR or ‘,’ expected 
#define ERROR_CODE_0046 46 // DNS expected
#define ERROR_CODE_0047 47 // ‘:’ or ‘~’ expected 
#define ERROR_CODE_0048 48 // String expected
#define ERROR_CODE_0049 49 // ‘:’ or ‘=’ expected 
#define ERROR_CODE_0050 50 // Text expected
#define ERROR_CODE_0051 51 // Syntax error 
#define ERROR_CODE_0052 52 // ‘,’ expected
#define ERROR_CODE_0053 53 // Illegal command code 
#define ERROR_CODE_0054 54 // Error when setting parameter
#define ERROR_CODE_0055 55 // Error when getting parameter value
#define ERROR_CODE_0056 56 // User abort
#define ERROR_CODE_0057 57 // Error when trying to establish PPP
#define ERROR_CODE_0058 58 // Error when trying to establish SMTP
#define ERROR_CODE_0059 59 // Error when trying to establish POP3
#define ERROR_CODE_0060 60 // Single session body for MIME exceeds the maximum allowed
#define ERROR_CODE_0061 61 // Internal memory failure 
#define ERROR_CODE_0062 62 // User aborted the system
#define ERROR_CODE_0063 63 // ~CTSH needs to be LOW to change to hardware flow control.
#define ERROR_CODE_0064 64 // User aborted last command using ‘---’
#define ERROR_CODE_0065 65 // iChip unique ID already exists
#define ERROR_CODE_0066 66 // Error when setting the MIF parameter
#define ERROR_CODE_0067 67 // Command ignored as irrelevant
#define ERROR_CODE_0068 68 // iChip serial number already exists
#define ERROR_CODE_0069 69 // Timeout on host communication
#define ERROR_CODE_0070 70 // Modem failed to respond
#define ERROR_CODE_0071 71 // No dial tone response
#define ERROR_CODE_0072 72 // No carrier modem response
#define ERROR_CODE_0073 73 // Dial failed
#define ERROR_CODE_0074 74 // Modem connection with ISP lost -or- LAN connection lost -or- WLAN connection lost
#define ERROR_CODE_0075 75 // Access denied to ISP server
#define ERROR_CODE_0076 76 // Unable to locate POP3 server
#define ERROR_CODE_0077 77 // POP3 server timed out
#define ERROR_CODE_0078 78 // Access denied to POP3 server
#define ERROR_CODE_0079 79 // POP3 failed 
#define ERROR_CODE_0080 80 // No suitable message in mailbox
#define ERROR_CODE_0081 81 // Unable to locate SMTP server
#define ERROR_CODE_0082 82 // SMTP server timed out
#define ERROR_CODE_0083 83 // SMTP failed
#define ERROR_CODE_0084 84 // RESERVED
#define ERROR_CODE_0085 85 // RESERVED 
#define ERROR_CODE_0086 86 // Writing to internal non-volatile parameters database failed
#define ERROR_CODE_0087 87 // Web server IP registration failed
#define ERROR_CODE_0088 88 // Socket IP registration failed
#define ERROR_CODE_0089 89 // E-mail IP registration failed
#define ERROR_CODE_0090 90 // IP registration failed for all methods specified
#define ERROR_CODE_0091 91 // RESERVED
#define ERROR_CODE_0092 92 // RESERVED
#define ERROR_CODE_0093 93 // RESERVED
#define ERROR_CODE_0094 94 // In Always Online mode, connection was lost and re-established
#define ERROR_CODE_0096 96 // A remote host, which had taken over iChip through the LATI port, was disconnected
#define ERROR_CODE_0098 98 // RESERVED
#define ERROR_CODE_0099 99 // RESERVED
#define ERROR_CODE_0100 100 // Error restoring default parameters
#define ERROR_CODE_0101 101 // No ISP access numbers defined
#define ERROR_CODE_0102 102 // No USRN defined
#define ERROR_CODE_0103 103 // No PWD entered
#define ERROR_CODE_0104 104 // No DNS defined
#define ERROR_CODE_0105 105 // POP3 server not defined
#define ERROR_CODE_0106 106 // MBX (mailbox) not defined
#define ERROR_CODE_0107 107 // MPWD (mailbox password) not defined
#define ERROR_CODE_0108 108 // TOA (addressee) not defined
#define ERROR_CODE_0109 109 // REA (return e-mail address) not defined
#define ERROR_CODE_0110 110 // SMTP server not defined
#define ERROR_CODE_0111 111 // Serial data overflow
#define ERROR_CODE_0112 112 // Illegal command when modem online
#define ERROR_CODE_0113 113 // Remote firmware update attempted but not completed. The original firmware remained intact.
#define ERROR_CODE_0114 114 // E-mail parameters update rejected
#define ERROR_CODE_0115 115 // SerialNET could not be started due to missing parameters
#define ERROR_CODE_0116 116 // Error parsing a new trusted CA certificate
#define ERROR_CODE_0117 117 // Error parsing a new Private Key
#define ERROR_CODE_0118 118 // Protocol specified in the USRV parameter does not exist or is unknown
#define ERROR_CODE_0119 119 // WPA passphrase too short has to be 8-63 chars
#define ERROR_CODE_0120 120 // RESERVED
#define ERROR_CODE_0121 121 // RESERVED
#define ERROR_CODE_0122 122 // SerialNET error: Host Interface undefined (HIF=0)
#define ERROR_CODE_0123 123 // SerialNET mode error: Host baud rate cannot be determined
#define ERROR_CODE_0124 124 // SerialNET over TELNET error: HIF parameter must be set to 1 or 2
#define ERROR_CODE_0125 125 // Invalid WEP key
#define ERROR_CODE_0126 126 // Invalid parameters’ profile number
#define ERROR_CODE_0128 128 // Product ID already exists
#define ERROR_CODE_0129 129 // HW pin can not be changed after Product-ID was set 
 
#define ERROR_CODE_0200 200 // Socket does not exist
#define ERROR_CODE_0201 201 // Socket empty on receive
#define ERROR_CODE_0202 202 // Socket not in use
#define ERROR_CODE_0203 203 // Socket down
#define ERROR_CODE_0204 204 // No available sockets
#define ERROR_CODE_0206 206 // PPP open failed for socket
#define ERROR_CODE_0207 207 // Error creating socket
#define ERROR_CODE_0208 208 // Socket send error
#define ERROR_CODE_0209 209 // Socket receive error
#define ERROR_CODE_0210 210 // PPP down for socket
#define ERROR_CODE_0212 212 // Socket flush error 
#define ERROR_CODE_0215 215 // No carrier error on socket operation
#define ERROR_CODE_0216 216 // General exception
#define ERROR_CODE_0217 217 // Out of memory
#define ERROR_CODE_0218 218 // An STCP (Open Socket) command specified a local port number that is already in use
#define ERROR_CODE_0219 219 // SSL initialization/internal CA certificate loading error
#define ERROR_CODE_0220 220 // SSL3 negotiation error
#define ERROR_CODE_0221 221 // Illegal SSL socket handle. Must be an open and active TCP socket.
#define ERROR_CODE_0222 222 // Trusted CA certificate does not exist
#define ERROR_CODE_0223 223 // RESERVED 
#define ERROR_CODE_0224 224 // Decoding error on incoming SSL data
#define ERROR_CODE_0225 225 // No additional SSL sockets available
#define ERROR_CODE_0226 226 // Maximum SSL packet size (2KB) exceeded
#define ERROR_CODE_0227 227 // AT+iSSND command failed because size of stream sent exceeded 2048 bytes
#define ERROR_CODE_0228 228 // AT+iSSND command failed because checksum calculated does not match checksum sent by host
#define ERROR_CODE_0229 229 // SSL parameters are missing 
#define ERROR_CODE_0230 230 // Maximum packet size (4GB) exceeded

#define ERROR_CODE_0300 300 // HTTP server unknown
#define ERROR_CODE_0301 301 // HTTP server timeout 
#define ERROR_CODE_0302 302 // RESERVED
#define ERROR_CODE_0303 303 // No URL specified 
#define ERROR_CODE_0304 304 // Illegal HTTP host name
#define ERROR_CODE_0305 305 // Illegal HTTP port number
#define ERROR_CODE_0306 306 // Illegal URL address
#define ERROR_CODE_0307 307 // URL address too long 
#define ERROR_CODE_0308 308 // The AT+iWWW command failed because iChip does not contain a home page
#define ERROR_CODE_0309 309 // WEB server is already active with a different backlog.

#define	ERROR_CODE_0400	400 // MAC address exists
#define	ERROR_CODE_0401	401 // No IP address
#define	ERROR_CODE_0402	402 // Wireless LAN power set failed
#define	ERROR_CODE_0403	403 // Wireless LAN radio control failed
#define	ERROR_CODE_0404	404 // Wireless LAN reset failed
#define	ERROR_CODE_0405	405 // Wireless LAN hardware setup failed
#define	ERROR_CODE_0406	406 // Command failed because WiFi module is currently busy
#define	ERROR_CODE_0407	407 // Illegal WiFi channel
#define	ERROR_CODE_0408	408 // Illegal SNR threshold
#define	ERROR_CODE_0409	409 // WPA connection process has not yet completed
#define	ERROR_CODE_0410	410 // The network connection is offline (modem)
#define	ERROR_CODE_0411	411 // Command is illegal when Bridge mode is active

#define	ERROR_CODE_0500	500	// RESERVED
#define	ERROR_CODE_0501	501	// Communications platform already active
#define	ERROR_CODE_0502	502	// RESERVED
#define	ERROR_CODE_0503	503	// RESERVED
#define	ERROR_CODE_0504	504	// RESERVED
#define	ERROR_CODE_0505	505	// Cannot open additional FTP session – all FTP handles in use
#define	ERROR_CODE_0506	506	// Not an FTP session handle
#define	ERROR_CODE_0507	507	// FTP server not found
#define	ERROR_CODE_0508	508	// Timeout when connecting to FTP server
#define	ERROR_CODE_0509	509	// Failed to login to FTP server (bad username or password or account)
#define	ERROR_CODE_0510	510	// FTP command could not be completed
#define	ERROR_CODE_0511	511	// FTP data socket could not be opened
#define	ERROR_CODE_0512	512	// Failed to send data on FTP data socket
#define	ERROR_CODE_0513	513	// FTP shutdown by remote server
#define	ERROR_CODE_0514	514	// RESERVED

#define	ERROR_CODE_0550	550	// Telnet server not found
#define	ERROR_CODE_0551	551	// Timeout when connecting to Telnet server
#define	ERROR_CODE_0552	552	// Telnet command could not be completed
#define	ERROR_CODE_0553	553	// Telnet session shutdown by remote server
#define	ERROR_CODE_0554	554	// A Telnet session is not currently active
#define	ERROR_CODE_0555	555	// A Telnet session is already open
#define	ERROR_CODE_0556	556	// Telnet server refused to switch to BINARY mode
#define	ERROR_CODE_0557	557	// Telnet server refused to switch to ASCII mode
#define	ERROR_CODE_0558	558	// RESERVED
#define	ERROR_CODE_0559	559	// RESERVED
#define	ERROR_CODE_0560	560	// Client could not retrieve a ring response e-mail
#define	ERROR_CODE_0561	561	// Remote peer closed the SerialNET socket

#define	ERROR_CODE_0570	570	// PING destination not found
#define	ERROR_CODE_0571	571	// No reply to PING request

#define	ERROR_CODE_0600	600	// Port Forwarding Rule will create ambiguous NAT entry

#endif /* ATI_ERRORCODE_H_ */
