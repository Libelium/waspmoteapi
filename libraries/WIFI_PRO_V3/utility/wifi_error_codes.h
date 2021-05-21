/*! \file ati_error_codes.h
  \brief Definition of the possible error codes
    
  Copyright (C) 2021 Libelium Comunicaciones Distribuidas S.L.
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
  Implementation:	Yuri Carmona

 */

#ifndef ATI_ERRORCODE_H_
#define ATI_ERRORCODE_H_

//! CME ERROR CODES
#define ERROR_CODE_0	3  	// Common Waspmote API timeout error
#define ERROR_CODE_3	3  	// Common Waspmote API timeout error
#define ERROR_CODE_902	902	// Waspmote API: SD not present
#define ERROR_CODE_903	903	// Waspmote API: SD file not created
#define ERROR_CODE_904	904	// Waspmote API: SD error opening file
#define ERROR_CODE_905	905	// Waspmote API: SD error setting file offset
#define ERROR_CODE_906	906	// Waspmote API: SD error writing
#define ERROR_CODE_907	907	// Waspmote API: rx buffer full
#define ERROR_CODE_908	908	// Waspmote API: error downloading UPGRADE.TXT
#define ERROR_CODE_909	909	// Waspmote API: filename in UPGRADE.TXT is not a 7-byte name
#define ERROR_CODE_910	910	// Waspmote API: no FILE label is found in UPGRADE.TXT
#define ERROR_CODE_911	911	// Waspmote API: NO_FILE is defined as FILE in UPGRADE.TXT
#define ERROR_CODE_912	912	// Waspmote API: no PATH label is found in UPGRADE.TXT
#define ERROR_CODE_913	910	// Waspmote API: no SIZE label is found in UPGRADE.TXT
#define ERROR_CODE_914	914	// Waspmote API: no VERSION label is found in UPGRADE.TXT
#define ERROR_CODE_915	915	// Waspmote API: version indicated in UPGRADE.TXT is lower/equal to Waspmote's version
#define ERROR_CODE_916	916	// Waspmote API: file size does not match the indicated in UPGRADE.TXT
#define ERROR_CODE_917	917	// Waspmote API: error downloading binary file    
#define ERROR_CODE_918	918	// Waspmote API: invalid data length
#define ERROR_CODE_919	919	// Illegal delimiter 
#define ERROR_CODE_920	920	// Illegal value
#define ERROR_CODE_921	921	// CR expected 
#define ERROR_CODE_922	922	// Number expected
#define ERROR_CODE_923	923	// CR or ‘,’ expected 
#define ERROR_CODE_924	924	// DNS expected
#define ERROR_CODE_925	925	// ‘:’ or ‘~’ expected 
#define ERROR_CODE_926	926	// String expected
#define ERROR_CODE_927	927	// ‘:’ or ‘=’ expected 
#define ERROR_CODE_928	928	// Text expected
#define ERROR_CODE_929	929	// Syntax error 
#define ERROR_CODE_930	930	// ‘,’ expected
#define ERROR_CODE_931	931	// Illegal command code 
#define ERROR_CODE_932	932	// Error when setting parameter
#define ERROR_CODE_933	933	// Error when getting parameter value

#endif /* ATI_ERRORCODE_H_ */
