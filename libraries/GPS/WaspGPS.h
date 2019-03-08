/*! \file WaspGPS.h
    \brief Library for managing the GPS v2.0 JN3 receiver

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

    Version:		3.2
    Design:			David Gascón
    Implementation:	Javier Siscart

*/

/*! \def WaspGPS_h
    \brief The library flag

 */
#ifndef WaspGPS_h
#define WaspGPS_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

 /*! \def GPS_DEBUG
    \brief Enables debug mode.
	Setting this constant to 1 some debug messages will be pronted by USB
	Commenting this line, the debug messages will be disabled.
 */
 //#define GPS_DEBUG 1

 // define print message
 #define PRINT_GPS(str)	USB.print(F("[GPS] ")); USB.print(str);


/*! \def OSP_MODE
    \brief Enables OSP mode.
    In this mode, the communication is done using binary mode and
	OSP commands can be sent / received to the module.

 */

/*! \def NMEA_MODE
    \brief Enables NMEA mode.
    In this mode, the module answers with the default NMEA sentences used
    by the GPS library functions. THis is the default mode of the module.

 */

 /*! \def UNKNOWN_MODE
    \brief Not KNOWN mode.
    Used when turning ON the module, to allow turning by default to NMEA mode.

 */
#define OSP_MODE 0
#define NMEA_MODE 1
#define UNKNOWN_MODE 2

/*! \def GPS_ON
    \brief GPS power mode: ON.
    Using GPS_ON makes GPS module to switch on.
 */

/*! \def GPS_OFF
    \brief GPS power mode: OFF
   	Using GPS_OFF makes GPS module to switch off.
 */
#define GPS_ON 	0
#define GPS_OFF 1

/*! \def GPS_SIGNAL_TIMEOUT
	\brief Time out in seconds for waiting to get signal
	The waitForSignal method checks if receiver is connected to some
	satellite until this time out is reached or connection is stablished.

*/
#define GPS_SIGNAL_TIMEOUT	60

/*! \def GPS_BUFFER_SIZE
    \brief internal 'inBuffer' size.
 */
#define GPS_BUFFER_SIZE 160

/*! \def MAX_SIZE
    \brief max amount of arguments in Wasp
 */
#define MAX_SIZE 20

/*! \def FILE_EPHEMERIS
    \brief File used to save and load ephemeris: "EPHEM.TXT"
 */
#define FILE_EPHEMERIS "EPHEM.TXT"


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspGPS Class
/*!
	WaspGPS Class defines all the variables and functions used to manage GPS
	v2.0, the JN3 receiver from Telit.
 */
class WaspGPS
{

/// private methods //////////////////////////
private:

	//! Variable: Baudrate used to init the UART and communicate with GPS receiver
    /*!
    Possible values are 4800,9600,19200,38400,57600,115200.
    4800 is the only value supported now by the API.
    The reason is GPS receiver always starts at 4800bps, so it would be
    necessary to open UART at 4800, change speed, close UART and open it again
    at new speed.
    If a higher speed wants to be used, previously explained reason has to be
    managed properly.
     */
	uint32_t _baudRate;

    //! Variable : UART used to communicate with GPS receiver
    /*!
    Possible values are: 0 or 1.
    UART used now to communicate with GPS is UART1, so '1' must be set.
     */
    uint8_t _uart;

    //! Variable : Communication mode. Two possibilities available ->
    //! binary mode (OSP) or NMEA mode.
    /*!
    Possible values are NMEA_MODE and OSP_MODE
     */
    uint16_t _commMode;

    //! Variable : Power mode used for GPS receiver
    /*!
    Possible values are related below.
    \sa	 GPS_ON, GPS_OFF
     */
    uint8_t _pwrMode;

    //! Variable : the frame checksum
    /*!
     */
    uint8_t _checksum;

    //! Variable : for storing the frame checksum
    /*!
     */
    uint8_t _checkSUM[2];

    //! Variable : buffer to store incoming data
    /*!
    */
    char _dataBuffer[GPS_BUFFER_SIZE];

    //! It powers up GPS module and opens selected UART to communicate with it
    /*!
    \param void
    \return void
    \sa init()
    */
    void begin(void);

    //! It closes selected UART
    /*!
    \param void
    \return void
     */
    void close(void);

    //! It switches between communication modes NMEA and OSP.
    /*!
    \param uint8_t mode: OSP or NMEA
    \return 1 if ok, 0 if already in that mode
    */
    uint8_t setCommMode(uint8_t mode);

    //! It initializes GPS module with the default values
    /*!
    \param void
    \return void
    */
    uint8_t init(void);

    //! It initializes GPS module with the specified values
    /*!
    \param default location parameters
    \return void
    */
    uint8_t init(	const char*,
				const char*,
				const char*,
				const char*,
				const char*,
				const char*,
				const char*,
				const char* );

	//! It calculates the NMEA checkSum, leave out $, *, and the checkSum bytes
    /*!
	\param char *gpsString: the string containing the NMEA sentence to get the
	checksum from
	\return '1' if checksum is correct, '0' if not
	 */
	uint8_t checkNMEAMsg(const char* gpsString);

	//! It calculates the NMEA checkSum, leave out $, *, and the checkSum bytes
    /*!
	\param char *gpsString: the string containing the NMEA sentence to get the
	checksum from
	\return '1' if checksum is correct, '0' if not
	\sa setChecksum()
	 */
	uint8_t getChecksum(const char* gpsString);

	//! It calculates checksum for a secuence given as a parameter
    /*!
	\param uint8_t* buffer: the secuence to get the checksum from
	\return void. It stores in 'checkSUM' variable the result
	\sa
	 */
	void getChecksum(uint8_t* buffer);

	//! Set checksum to a NMEA command.
    /*!
    \param
    \return REturn command with checksum added.
    */
	char* setChecksum(char * command);

	//! Looks for RMC NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no RMC sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseRMC(void);

    //! Looks for GGA NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no GGA sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseGGA(void);

    //! Looks for GSA NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no GSA sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseGSA(void);

    //! Looks for GSV NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no GSV sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseGSV(void);

    //! Looks for GLL NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    //! note: NMEA sentence not enabled by default
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no GLL sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseGLL(void);

    //! Looks for VTG NEMEA sentence and parses its fields,
    //! updating the corresponding global variables.
    //! note: NMEA sentence not enabled by default
    /*!
    \param void
    \return '0' if not connected yet, '-1' if no VTG sentence parsed,
    \ '-2' if no gps data, '1' if connected.
     */
    int8_t parseVTG(void);


    //! Shows OSP data sent by the GPS module during
    //! specified time.
    /*!
    \param long time: time to be printing data
    \return void
    */
  	void showOSPRawData(unsigned long time);

	//! Shows NMEA sentences sent by GPS module during
	//! specified time.
    /*!
    \param long time: time to be printing data
    \return void
    */
	void showNMEARawData(unsigned long time);

	//! Set OSP message rate to 0.
    /*!
    \param void
    \return void
    */
	void disableOSPMsg();

	//! Sends NMEA command. Checksum calculated inside.
    /*!  Example: sendCommand("$PSRF100,0,115200,8,1,0*00");
    \param char * command: NMEA command
    \return
    */
	void sendCommand(char * command);

	//! Sends OSP command. Checksum calculated inside.
    /*! Example: A0 A2 00 03 93 00 00 00 00 B0 B3
    \param uint8_t * command: command to send
    \param uint16_t commandLength: length of the command
    \return void
    */
	void sendCommand(uint8_t * command,  uint16_t commandLength);


/// public methods and attributes //////////////////////////
public:

	//! class constructor
    /*!
    It initializes the variables with the default values.
    \param void
    \return void
    */
    WaspGPS();

    //! Variable : Flag used to determine if an error occurred while executing
    //! some function
    /*!
    Possible values are: 0 or 1.
     */
    uint16_t flag;

    //! Variable : Time extracted from NMEA GGA sentence received from GPS receiver
    /*!
    String that contains the time extracted from NMEA GGA sentence.
    To store the time 13:30:00, it is stored this way: "133000"
     */
    char timeGPS[11];

    //! Variable : Date extracted from NMEA RMC sentence received from GPS receiver
    /*!
    String that contains the date extracted from NMEA RMC sentence.
    To store the date 23rd of March 1994, it is stored this way: "230394"
     */
    char dateGPS[7];

    //! Variable : Clock drift of the GPS receiver used to initialize it
    /*!
    Value in Hz. Use '0' to use the last value saved, if not available 96250Hz
    will be used.
     */
    char* clkOffset;

    //! Variable : GPS Time of Week used to initialize it
    /*!
    Time of week specified in seconds.
     */
    char* timeOfWeek;

    //! Variable : Extended GPS Week Number used to initialize it
    /*!
     */
    char* weekNo;

    //! Variable : Channel Counter used to initialize it
    /*!
     */
    char* channel;

    //! Variable : Reset Configuration
    /*!
     */
    char* resetCfg;

    //! Variable : Default Latitude. + = North (Range 90 to -90). Expressed in
    //! degrees. Example-->37.3875111
    /*!
     */
    char* coordinateLat;

    //! Variable : Default Longitude. + = East (Range 180 to -180). Expressed
    //! in degrees. Example-->-121.97232
    /*!
     */
    char* coordinateLon;

    //! Variable : Default Altitude position. Expressed in meters. Example-->0
    /*!
     */
    char* coordinateAl;

    //! Variable : it stores the latitude given by the GPS module
    /*!
     */
    char latitude[11];

    //! Variable : it stores the latitude indicator N: North; S: South
    /*!
     */
    char NS_indicator;

    //! Variable : it stores the longitude given by the GPS module
    /*!
     */
    char longitude[11];

    //! Variable : it stores the longitude indicator E: East; W: West
    /*!
     */
    char EW_indicator;

    //! Variable : it stores the speed given by the GPS module
    /*!
     */
    char speed[MAX_SIZE];

    //! Variable : it stores the altitude given by the GPS module
    /*!
     */
    char altitude[MAX_SIZE];

    //! Variable : it stores the course given by the GPS module
    /*!
     */
    char course[MAX_SIZE];

    //! Variable : it stores mode field of RMC and GLL NMEA sentence
    /*!
     */
	char RMCMode[2];

    //! Variable : global to show if connected of not,
    //! depending RMC status parameter (A connected, V disconected)
    /*!
    */
    int8_t signalStatus;

    //! Variable : state field of RMC sentence. Same as status
    /*!
    */
    char state[2];

    //! Variable : Satellites used field in GGA
    /*!
    */
    char satellites[3];

    //! Variable : Accuracy field of GGA sentence
    /*!
    */
    char accuracy[4];

    //! Variable : Mode 1 field of GSA sentence
    /*!
    */
    char GSAMode1[2];

    //! Variable : Mode 2 field of GSA sentence
    /*!
    */
    char GSAMode2[2];

    //! Variable : Position dilution of precision of GSA sentence
    /*!
    */
    char PDOPAccuracy[4];

    //! Variable : Horizontal dilution of precision of GSA sentence
    /*!
    */
    char HDOPAccuracy[4];

    //! Variable : Vertical dilution of precision of GSA sentence
    /*!
    */
    char VDOPAccuracy[4];

    //! Variable : satellites used in GSV sentence.
    /*!
    */
    char satellitesInView[4];

	//! It sets UART1's multiplexor to GPS and open the serial port
    /*!
    \param void
    \return void
    \sa close(), begin()
    */
    uint8_t ON();

    //! It closes UART1 and powers off the GPS module
    /*!
    \param void
    \return void
    \sa close(), begin()
     */
    void OFF();

    //! It sets the current internal Power Mode on the GPS
    /*!
    \param uint8_t mode : power mode to set the GPS. Possible values are GPS_ON,
    GPS_OFF
    \return void
    \sa getMode()
     */
    void setMode(uint8_t);

    //! It gets the current internal Power Mode on the GPS
    /*!
    \param void
    \return 'pwrMode' variable that contains the power mode on use
    \sa setMode()
     */
    uint8_t getMode(void);

    //! It gets the communication mode in use
    /*!
    \param void
    \return 'commMode' variable that contains the communication mode on use
    \sa setCommMode()
     */
    uint8_t getCommMode(void);

    //! It checks if the receiver is connected to sattelites
    /*!
    \param void
    \return '1' if connected, '0' if not.
    \sa init()
     */
    uint8_t check();

    //! It checks if the receiver is connected to satellites until
    //! connection is stablished or GPS_SIGNAL_TIMEOUT is reached
    /*!
    \param void
    \return '1' if connected, '0' if not.
     */
    bool waitForSignal();

    //! It checks if the receiver is connected to satellites until
    //! connection is stablished or timeout parameter is reached
    /*!
    \param long timeout defines the time to wait
    \return '1' if connected, '0' if not.
     */
    bool waitForSignal(unsigned long timeout);

    //! It gets the current time given by GPS
    /*!
    \param void
    \return the currect time in a string with the following structure--> "hhmmss.mmmm"
    \sa getDate(), extractTime(), extractDate()
     */
    char* getTime(void);

    //! It gets the current date given by GPS
    /*!
    \param void
    \return the currect date in a string with the following structure--> "ddmmyy"
    \sa getDate(), extractTime(), extractDate()
    */
    char* getDate(void);

    //! It gets the Latitude from the GPS
    /*!
    \param void
    \return the Latitude in a string, expressed as ddmm.mmmm
     */
    char* getLatitude(void);

    //! It performs the conversion from input parameters in  DD°MM.mmm’ notation
    //! to DD.dddddd° notation.
    /*!
    \param char* input : is a string indicating the latitude/longitude in
	DDmm.mmmm' notation for latitude and DDDmm.mmmm' notation for longitude
	\param char indicator : is a char indicating 'N' for North, 'S' for South,
	'E' for East and 'W' for West
    \return the Latitude/Longitude in a float expressed in degrees
     */
    float convert2Degrees(char* input, char indicator);

    //! It gets the Longitude from the GPS
    /*!
    \param void
    \return the Longitude in a string, expressed as ddmm.mmmm
     */
    char* getLongitude(void);

    //! It gets the Speed from the GPS
    /*!
    \param void
    \return the Speed in a string, expressed in kilometers per hour
     */
    char* getSpeed(void);

    //! It gets the Altitude from the GPS
    /*!
    \param void
    \return the Altitude in a string, expressed in meters
     */
    char* getAltitude(void);

    //! It gets the Course from the GPS
    /*!
    \param void
    \return the True Track made good, expressed in degrees
     */
    char* getCourse(void);

    //! It gets the latitude, longitude, altitude, speed, course, time and date
    /*!
    \param void
    \return '1' if success, '0' if error
     */
    int8_t getPosition();

    //! It sets RTC time from GPS
    /*!
    \param void
    \return void
     */
    void setTimeFromGPS(void);

    //! Saves Ephemeris data into default file on SD card
    /*!
    \param void
    \return -3 if no ephem data,, -2 if error creating SD card file,
	\ -1 if no SD, 0 if error writting into file, 1 on success
    */
	int8_t saveEphems();

	//! Saves Ephemeris data into SD card
    /*!
    \param const char * filename: file name on SD card
    \return -3 if no ephem data,, -2 if error creating SD card file,
	\ -1 if no SD, 0 if error writting into file, 1 on success
    */
	int8_t saveEphems(const char * filename);

	//! Loads Ephemerids data stored in the default file on SD card.
    /*!
    \param void
    \return return 0 if error reading file, -1 if no SD, -2 if no file.
    */
	int8_t loadEphems();

    //! Loads Ephemerids data stored in the SD card.
    /*!
    \param const char * filename: file name on SD card
    \return return 0 if error reading file, -1 if no SD, -2 if no file.
    */
    int8_t loadEphems(const char* filename);

  	//! Shows data directly from GPS module. NMEA or Binary
    /*!
    \param uint8_t mode: NMEA_MODE or OSP_MODE
    \param unsigned long time: time to show data in seconds.
    \return void
    */
  	void showRawData(uint8_t mode, unsigned long time);

  	//! Gets firmware version of GPS module
    /*!
    \param void
    \return Firmware version
    */
	char * getFirmwareVersion();

};

extern WaspGPS GPS;

#endif
