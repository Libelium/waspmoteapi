/*! \file WaspWIFI.h
    \brief Library for managing WIFI modules
    
    Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.8
    Design:			David Gascón
    Implementation:	Joaquín Ruiz, Yuri Carmona

 */
 
/*! \def WaspWIFI_h
    \brief The library flag
    
 */

#ifndef WaspWIFI_h
#define WaspWIFI_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/


//! TIMEOUT FOR FTP TRANSMISSIONS //
#define FTP_TIMEOUT 30000

//! BAUD RATES //
#define WIFI_BAUDRATE	115200

//! AUTHENTICATION MODES //

#define OPEN 		0
#define	WEP			1
#define WPA1		2
#define WPAMIX		3
#define WPA2		4
#define ADHOC		6

//! JOIN MODES //

#define MANUAL			0
#define AUTO_STOR		1
#define AUTO_BEST		2	// not reliable (deprecated)
#define CREATE_ADHOC	4	// not reliable (deprecated)

//! DHCP OPTIONS //

#define DHCP_OFF	0
#define DHCP_ON		1
#define AUTO_IP		2   // Ad-hoc networks
#define DHCP_CACHE	3

//! CONNECTION OPTIONS //

#define CLIENT_SERVER	2   //00010 (TCP)
#define CLIENT			8   //01000 (TCP)
#define HTTP			16  //10000 (HTTP)
#define UDP				1   //00001 (UDP)
#define SECURE			4   //00100 (UDP)

//! FLAGS OPTIONS //

#define TCP_STATUS	1   //00000001  TCP connections are kept open when the
			    //connection to the access point is lost.
#define TCP_NODELAY	2   //00000010  Nagle's algorithm, named after John 
			    //Nagle, is a means of improving the efficiency of
			    //TCP/IP networks by reducing the number
			    //of packets that need to be sent over the network.
#define TCP_RETRY	4   //00000100  Enables the TCP retry. 96 packets.
#define UDP_RETRY	8   //00001000  Retry if no ACK from UDP.
#define DNS_CACHE	16  //00010000
#define ARP_CACHE	32  //00100000
#define UDP_AUTO_PA	64  //01000000  UDP auto pairing enabled.
#define BYTE_STAMP	128 //10000000  8 byte timestamp to UDP or TCP packets.

//! DNS OPTIONS //

#define MAIN		0
#define AUX		1

//! HTTP OPTIONS //

#define IP		1   // HTTP is specified by an IP address.
#define DNS		2   // HTTP is specified by a DNS address.

//! FTP OPTIONS //

#define FTP_PASIVE	0
#define FTP_ACTIVE	1

//! DEBUG MODE //
//~ #define DEBUG_WIFI 		// Debug flag
#define QUIET		0   // No messages printed when wakes up or powers up.
#define ALL			1   // All status messages.
#define CRITICAL	2   // Only critical network AP connection level status
						// is output.
#define IP_STATUS	4   // DHCP and IP address status information.

//! READ WITH TIMEOUT / WITHOUT TIMEOUT//

#define BLO		0   // Read without timeout
#define NOBLO		1   // Read with timeout

//! OTA CONSTANTS //
#define CHECK_VERSION	// when defined it enables the version cheking
const char OTA_ver_file[]	= "UPGRADE.TXT";	// Server's file
const char NO_OTA[] = "NO_FILE";	// No file in server pattern indicator


/******************************************************************************
 * Class
 *****************************************************************************/
//! WaspWIFI Class
/*!
	WaspWIFI Class defines all the variables and functions used to manage
	WIFI modules. 
 */

class WaspWIFI
{
  // Data Types ///////////////////////////////////////////////////////////////
  //! Specifies the data type for IP addresses "255.255.255.255"
  typedef char ipAddr[15];
  
  // PRIVATE //////////////////////////////////////////////////////////////////
  private:	
    
    // VARIABLES //////////////////////////////////////////////////////////////
  
    //! Specifies the number of port that uart and usb have.
    uint8_t _uartWIFI; 
    
    //! Specifies the dhcp option
    uint8_t _dhcpOpts;  

    //! Specifies the time of AP scanning (in ms).
    uint16_t scanTime;

    //! Specifies if the Ap scan is active or pasive.
    bool scanPassive;

    //! Specifies the current baud_rate of the WIFI module
    long baud_rate;
    
    //! Specifies the 'WRX' variable given by 'show stats' command
    long int WRX;
    
    //! Specifies the 'WTX' variable given by 'show stats' command
    long int WTX;
    
    //! Specifies the 'FlwSet' variable given by 'show stats' command
    int flwSet;
    
  
    char CLOS_pattern[7];
    char Disconn_pattern[8];
    char timeout_pattern[9];

    
    // INTERNAL FUNCTIONS /////////////////////////////////////////////////////

    //! Switches to command Mode
    /*!
      \param void
      \return '1' on success, '0' otherwise
    */ 
    uint8_t commandMode();

    //! Checks if 'word' is contained in 'text'.
    /*!
      \param char* text : Specifies the text to search in.
      \param char* word : Specifies the word to search in the 'text'.
      \return true on success, false otherwise.
    */
    bool contains(const char* text, char* word);

	//! Checks if 'pattern' has been received in RX buffer
    /*!
      \param char* pattern : Specifies the text to search in.
      \return '1' on success, '0' otherwise.
    */
	uint8_t checkAnswer(char* pattern);

    //! Reads data over the UART.
    /*!
      \param uint8_t len : Specifies the minimum length it is expected 
      to read.
      \return '1' on success, '0' otherwise.
    */
    uint8_t readData(uint8_t len);

    //! Sends the command 'comm' over the UART.
    /*!
      \param char* comm : Specifies the command to send over the UART.
      \return '1' on success, '0' otherwise.
    */
    uint8_t sendCommand(char* comm);
	uint8_t sendCommand(char* comm, char* pattern, unsigned long timeout);
	uint8_t sendCommand(char* comm, 
						char* pattern, 
						char* err_pattern, 
						unsigned long timeout,
						bool flush);
						
	uint8_t sendCommand(char* command, 
						char* ans1, 
						char* ans2, 
						char* ans3, 
						char* ans4, 
						uint32_t timeout);
	
	//! It inserts a delay depending on baudrate			
	void latencyDelay();
						
	//! It seeks 'pattern' inside the 'buffer' array
	bool find( uint8_t* buffer, uint16_t length, char* pattern);	
					
	//! Saves current configuration and reboots the device in order to new
    //! configuration takes effect.
    /*!
      \param void
      \return '1' on success, '0' otherwise.
    */
    uint8_t saveReboot();

    //! Opens TCP connection, and checks that everything are going good.
    /*!
      \param void
      \return '1' on success, '0' otherwise
    */ 
    uint8_t open();

    //! Opens http connection, and checks that everything are going good.
    /*!
      \param void
      \return '1' on success, '0' otherwise
    */ 
    uint8_t openHTTP();
    
    //! Reads a broadcast message and parses it.
    /*!
      \param void
      \return void
    */ 
    void parseBroadcast();

  // PUBLIC ///////////////////////////////////////////////////////////////////
  public:
    
    //! Specifies the answer that is read from the WIFI module
    char answer[513]; 
        
    //! Specifies the length of the answer received
    int length;
    
    //! Specifies the signal strength
    int rssi;

    // BASIC METHODS //////////////////////////////////////////////////////////

    //! Class constructor. Initializes the necessary variables.
    /*!
      \param void
      \return void
    */ 
    WaspWIFI();
    
    //! Opens the UART.
    
    //! Powers on the module and enters in command mode.
    /*!
      \param uint8_t sock : specifies where is the WIFI module connected
      \return void
    */ 
    bool ON(uint8_t sock);
    
    //! Closes the UART and powers off the module.
    /*!
      \param void
      \return void
    */ 
    void OFF();

    // ACCESS POINT CONFIGURATION METHODS /////////////////////////////////////
    
    //! Joins the chosen ssid.
    /*!
      \param char* ssid : specifies the name of the network to join.
      \return '1' on success, '0' otherwise.
    */
    uint8_t join(char* ssid);
    
    //! Joins a network AP from the scan list.
    /*!
      \param uint8_t val : specifies the number of network from the scan list
      to join.
      \return '1' on success, '0' otherwise.
    */
    uint8_t joinAPnum(uint8_t val);
    
    //! If connected, leaves the connected network
    /*!
      \param void
      \return '1' on success, '0' otherwise
    */
    uint8_t leave();
    
    //! Sets the wlan channel, 1-13 is the valid range for a fixed channel.
    /*!
      \param uint8_t val : Specifies the number of channel to set, range 1-13.
      \return '1' on success, '0' otherwise
    */
    uint8_t setChannel(uint8_t val);
    
    //! Sets the ESSID of the wlan.
    /*!
      \param char* ssid : specifies the name of the wlan to join.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setESSID(char* ssid);
   
    //! Sets the Key or the passphrase of the wlan.
    /*!
      \param uint8_t val : specifies the authentication mode (WEP, WPA1,
      WPAMIX, WPA2).
      \param char* pass : specifies the key (13 ASCII chars) or the passphrase
      (1-64 chars).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setAuthKey(uint8_t secMode, char* pass);

    //! Sets the authentication mode.
    /*!
      \param uint8_t val : specifies the authentication mode (OPEN, WEP, WPA1,
      WPAMIX, WPA2, ADHOC).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setAutojoinAuth(uint8_t val);
    
    //! Sets the policy for automatically joining/associating with network  
    //! access points.
    /*!
      \param uint8_t val : specifies the joining mode (MANUAL, AUTO_STOR,
      AUTO_BEST, CREATE_ADHOC).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setJoinMode(uint8_t val);
    
    //! Sets the link monitor timeout threshold.
    /*!
      \param uint8_t val : specifies the number of retries.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setAPretries(uint8_t val);
    
    //! Sets the Scan options, but does not launch the scan.
    /*!
      \param uint8_t time : Scan time (in ms).
      \param char* mask : Channel mask used for scanning channels with the 
      auto-join.
      \param bool passive : Enables or disables the pasive scan.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setScanOptions(uint16_t time, char* mask, bool passive);
    
    //! Launches the scan.
    /*!
      \param void
      \return void
    */ 
    void scan();
    
    //! Sets the Transmission Rate.
    /*!
      \param uint8_t val : specifies the wireless data rate (0..15).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setTXRate(uint8_t val);
    
    //! Sets the Transmission Power.
    /*!
      \param uint8_t val : specifies the Wi-Fi transmit power (0..12).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setTXPower(uint8_t val);
    
    //! Sets the IP Window value.
    /*!
      \param uint16_t val : specifies the the IP maximum buffer window size.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setIPWindow(uint16_t val);
      
    //! Join timer is the time in milliseconds the join function will wait for
    //! an access point to complete the association process. This timer is also
    //! the timeout for the WPA handshaking process.
    /*!
      \param uint16_t val : specifies the time in miliseconds the join function
      will wait.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setJoinTime(uint16_t val);

    // CONNECTION CONFIGURATION METHODS ///////////////////////////////////////

    //! Sends a ping to a remote specified host.
    /*!
      \param ipAddr ip : specifies the IP address of the host.
      \return void
    */
    void sendPing(ipAddr ip);
        
    //! Performs a DNS query on the supplied hostname.
    /*!
      \param char* name : specifies the hostname.
      \return void
    */ 
    int resolve(char* name);

    //! Synchronizes the time from the server.
    /*!
      \param ipAddr ip : specifies the time server address.
      \param uint16_t port : specifies the time server port number.
      \param uint8_t interval : the module will get the time every 'interval'
      minutes.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setTimeFromServer(ipAddr ip, uint16_t port, uint8_t interval);
    
    //! Sets the sleep time and the wake time (in seconds).
    /*!
      \param uint8_t sTime : specifies the time the wifi module is sleeping.
      \param uint8_t sCycle : specifies the time the wifi module will wait 
      until get slept again.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setSleep(uint8_t sTime, uint8_t sCycle);
    
    //! Controls debug print messages. This configures the debug messages
    //! printed by the WiFly module on the UART.
    /*!
      \param uint8_t val : specifies the mode of debug messages (QUIET, ALL,
      CRITICAL, IP_STATUS (default=ALL)).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setDebugMode(uint8_t val);
    
    //! Sets the Gateway address.
    /*!
      \param ipAddr ip : specifies the gateway IP address. If DHCP is turned on,
      the gateway IP address is assign and overwritten during association with
      the access point.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setGW(ipAddr ip);
    
    //! Sets the netmask.
    /*!
      \param ipAddr netmask : specifies the network mask. If DHCP is turned on,
      the netmask is assign and overwritten during association with the access
      point.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setNetmask(ipAddr netmask);
	    
    //! Sets the Remote Host.
    /*!
      \param ipAddr ip : specifies the ip address of the remote host.
      \param uint16_t port : specifies the port of the remote host.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setRemoteHost(ipAddr ip, uint16_t port);
    
    //! Sets the Local Port.
    /*!
      \param uint16_t port : specifies the local port.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setLocalPort(uint16_t port);
    
    //! Sets the IP address.
    /*!
      \param ipAddr ip : specifies the local ip address.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setIp(ipAddr ip);
    
    //! Sets the DHCP options.
    /*!
      \param uint8_t val : specifies the way the ip address is going to be
      solved. DHCP_OFF (Manual), DHCP_ON (Autom.), AUTO_IP (Adhoc-networks),
      DHCP_CACHE (Memory).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setDHCPoptions(uint8_t val);

    //! Sets the TCP/IP functions. Value is a bit mapped register.
    /*!
      \param uint8_t val : specifies the TCP/IP function or functions.
      TCP_STATUS, TCP_NODELAY,
      TCP_RETRY, UDP_RETRY, DNS_CACHE, ARP_CACHE, UDP_AUTO_PA, BYTE_STAMP.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setIPoptions(uint8_t val);
    
    //! Sets the connection options. (TCP, UDP, HTTP...) Value is a bit mapped
    //! setting.
    /*!
      \param uint8_t val : specifies the IP protocol. CLIENT_SERVER (TCP), 
      CLIENT (TCP), HTTP, UDP, SECURE (UDP).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setConnectionOptions(uint8_t val);
    
    //! Sets the TCP connection password. Provides minimal authentication by
    //! requiring any remote device that connects to send and match a challenge
    //! <val>. When set, all newly opened connections must first send the exact
    //! characters that match the stored password, otherwise the WIFI module 
    //! will close the connection.
    /*!
      \param char* password : specifies the password.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setTCPpassw(char* password);
    
    //! Sets the IP address, host and backup host of the DNS main or auxiliary
    //! server.
    /*!
      \param uint8_t type : specifies if the DNS server is main or auxiliary
      server.
      \param ipAddr ip : specifies the DNS IP address.
      \param char* name : specifies the DNS address name.
      \return '1' on success, '0' otherwise.
    */
    uint8_t setDNS(uint8_t type, ipAddr ip, char* name);
    
    //! Sets the FTP parameters.
    /*!
      \param ipAddr ip : specifies the FTP server IP address.
      \param uint16_t port : specifies the FTP server port.
      \param uint8_t mode : specifies the FTP mode, FTP_PASIVE or FTP_ACTIVE.
      \param uint8_t timeout : specifies the ftp timeout value (in seconds).
      \return '1' on success, '0' otherwise.
    */
    uint8_t setFTP(ipAddr ip, uint16_t port, uint8_t mode, uint8_t timeout);
    

    // CONNECTION OPERATIONS //////////////////////////////////////////////////

    //! Sets the http config and opens an HTTP connection.
    /*!
      \param uint8_t opt : specifies if the host is given by an IP address 
      (IP), or is given by a DNS name or webpage (DNS).
      \param char* host : specifies the IP address host or URL host.
      \param int port : specifies the server port 
      \param char* request : specifies the string that is sent to the 
      remote host.
      \return '1' on success, '0' otherwise.
      */
    uint8_t getURL(	uint8_t opt, char* host, char* request); 
    uint8_t getURL(	uint8_t opt, char* host, int port, char* request);
					
	//! Sets the http config and opens an HTTP connection.
    /*!
      \param uint8_t opt : specifies if the host is given by an IP address 
      (IP), or is given by a DNS name or webpage (DNS).
      \param char* host : specifies the IP address host or URL host.
      \param int port : specifies the server port 
      \param char* url : specifies the server URL
      \param char* body : specifies the body of the request
      \return '1' on success, '0' otherwise.
      */		
    uint8_t getURL(uint8_t opt, char* host, char* url, char* body); 
    uint8_t getURL(uint8_t opt, char* host, int port, char* url, char* body); 
    
    //! Sets the http config and opens an HTTP connection.
    /*!
      \param uint8_t opt : specifies if the host is given by an IP address 
      (IP), or is given by a DNS name or webpage (DNS).
      \param char* host : specifies the IP address host or URL host.
      \param char* request : specifies the string that is sent to the 
      remote host.
      \param char* buffer : is the frame to be attached to the request sentence
      \param int len : is the length of the buffer parameter
      \return '1' on success, '0' otherwise.
      */
    uint8_t getURL(	uint8_t opt, 
					char* host, 
					char* request, 
					uint8_t* buffer, 
					uint16_t len);
					
	//! Sets the http config and opens an HTTP connection.
    /*! This function is used to send Waspmote Frames from Waspmote to Meshlium
     * using the Sensor Parser of the Meshlium machine so as to store all Data
     * Frames inside the DataBase of Meshlium.
     * 
     * These are the input parameters:
      \param uint8_t opt : specifies if the host is given by an IP address 
      (IP), or is given by a DNS name or webpage (DNS).
      \param char* host : specifies the IP address host or URL host.
      \param int port : specifies remote port
      \param char* request : specifies the string that is sent to the 
      remote host.
      \param char* buffer : is the frame to be attached to the request sentence
      \param int len : is the length of the buffer parameter
      \return '1' on success, '0' otherwise.
      */				
	uint8_t sendHTTPframe(uint8_t opt, 
							char* host, 
							int port, 
							uint8_t* frame, 
							uint16_t len);
							
	uint8_t sendHTTPframe(uint8_t opt, 
							char* host, 
							int port, 
							char* request, 
							uint8_t* frame, 
							uint16_t len);
    
    //! Sets the configuration and opens a TCP client connection.
    /*!
      \param ipAddr ip_remote : specifies the IP address of the TCP remote 
      server.
      \param uint16_t port_remote : specifies the TCP remote server port.
      \param uint16_t port_local : specifies the local port for the TCP 
      connection.
      \return '1' on success, '0' otherwise.
      */
    uint8_t setTCPclient(	ipAddr ip_remote, 
							uint16_t port_remote, 
							uint16_t port_local);
							
	uint8_t setTCPclient(	uint8_t opt, 
							char*	host,
							uint16_t port_remote,
							uint16_t port_local);
    
    //! Sets the configuration and opens a TCP server connection.
    /*!
      \param uint16_t port_local : specifies the local port for the TCP 
      connection.
      \return '1' on success, '0' otherwise.
      */
    uint8_t setTCPserver(uint16_t port_local);
    
    //! Sets the configuration and opens a UDP client connection.
    /*!
      \param ipAddr ip_remote : specifies the destination IP address of the
      UDP messages.
      \param uint16_t port_remote : specifies the destination port of the
      UDP messages.
      \param uint16_t port_local : specifies the local port for sending
      UDP messages.
      \return '1' on success, '0' otherwise.
      */
    uint8_t setUDPclient(	ipAddr ip_remote, 
							uint16_t port_remote, 
							uint16_t port_local);
							
    uint8_t setUDPclient(	uint8_t opt,
							char* host, 
							uint16_t port_remote, 
							uint16_t port_local);
    
    //! Sets the configuration and opens a UDP server connection.
    /*!
      \param uint16_t port_local : specifies the local port for receiving 
      UDP messages.
      \return '1' on success, '0' otherwise.
      */
    uint8_t setUDPserver(uint16_t port_local);
      
    //! Opens the ftp connection using user and password given.
    /*!
      \param char* user : specifies the ftp user name for accessing the FTP 
      server.
      \param char* password : specifies the ftp password for accessing the 
      FTP server.
      \return '1' on success, '0' otherwise.
    */
    uint8_t openFTP(char* user, char* password);
    
    //! Gets the file via FTP.
    /*!
      \param char* file : specifies the name of the file to get from the FTP
      server.
      \param char* local_folder : specifies the folder of the SD card to save
      the file.
      \param char* remote_folder : specifies the folder of the FTP server that
      contains the file.
      \return '1' on success, '0' otherwise.
    */
    uint8_t getFile(char* filename, char* local_folder, char* remote_folder);
    
    //! Uploads a file via FTP.
    /*!
      \param char* file : specifies the name of the file to put into the FTP 
      server.
      \param char* local_folder : specifies the folder of the SD card that 
      contains the file.
      \param char* remote_folder : specifies the folder of the FTP server to 
      upload the file.
      \return '1' on success, '0' otherwise.
    */
    uint8_t uploadFile(char* file, char* local_folder, char* remote_folder);
  
    //! Reads data from the opened connection.
    /*!
      \param uint8_t blo : specifies if the read is blocking (BLO) or it has a
      2 seconds timeout (NOBLO).
      \return The number of characters reads.
      */
    int read(uint8_t blo);
    
    //! Reads data from the opened connection.
    /*!
      \param uint8_t blo : specifies if the read is blocking (BLO) or it has a
      2 seconds timeout (NOBLO).
      \param unsigned long time : number of milliseconds to wait until timeout
      \return The number of characters reads.
      */
    int read(uint8_t blo, unsigned long time);
    
    //! Sends data to the opened connection.
    /*!
      \param char* data : specifies the data to send.
      \return void
      */
    void send(char* data);
    
    //! Sends data to the opened connection.
    /*!
      \param uint8_t* data : specifies the data to send.
      \param uint16_t len : specifies the lenght of the data to send.
      \return void
      */
    void send(uint8_t* data, uint16_t len);

    //! Closes current connection.
    /*!
      \param void
      \return '1' on success, '0' otherwise.
      */
    uint8_t close();
    
    //! Configures and sends broadcast messages.
    /*!
      \param ipAddr ip_network : specifies the remote IP address for the 
      broadcast messages.
      \param uint16_t port_remote : specifies the remote port for receiving 
      broadcast messages.
      \param uint8_t interval : specifies the interval at which the broadcast 
      message is sent.
      \param char* id : specifies the device ID. This information is sent as 
      part of the broadcast message that is sent.
      \return '1' on success, '0' otherwise.
      */
    uint8_t sendAutoBroadcast(	ipAddr ip_network, 
								uint16_t port_remote,
								uint8_t interval, 
								char* id);
    
    //! Configures and opens an adhoc connection.
    /*!
      \param uint16_t beacon : specifies the adhoc beacon interval 
      (in milliseconds).
      \param uint16_t probe_interval : specifies the adhoc probe timeout in 
      seconds. This is the number of seconds waiting for probe responses before
      declaring "ADHOC is lost" and disabling the network interface.
      \return '1' on success, '0' otherwise.
      */
    uint8_t setAdhocOptions(uint16_t beacon, uint16_t probe_interval);
    
    // DEVICE CONFIGURATION ///////////////////////////////////////////////////
    
    //! Reboots the device (ON-OFF-ON).
    /*!
      \param void
      \return void
    */ 
    void reset();
    
    //! Restores the default settings of the device.
    /*!
      \param void
      \return void
    */ 
    void resetValues();
    
    //! Synchronizes the time.
    /*!
      \param void
      \return void
    */ 
    void synchronizeTime();
        
    //! Sets the UART baud rate. 
    /*!
      \param int val : specifies the UART baud rate. Valid settings are 
      2400, 4800, 9600, 19200, 38400, 57600,115200, 230400, 460800, 921600.
      \return void
    */ 
    uint8_t setBaudRate(long val);
    
    //! Saves current configuration.
    /*!
      \param void
      \return void
    */ 
    uint8_t storeData();

    // STATUS INFORMATION /////////////////////////////////////////////////////
        
    //! Checks if the module is connected to the Access Point (Check if it
    //! has an IP address).
    /*!
      \param void
      \return true on success, false otherwise
    */ 
    bool isConnected();
    bool isConnected(unsigned long timeout);

    //! Displays connection status
    /*!
      \param void
      \return void
    */ 
    void getConnectionInfo();
    
    //! Displays current network status, association, authentication, etc.
    /*!
      \param void
      \return void
    */ 
    void getAPstatus();
    
    //! Displays current last received signal strenght.
    /*!
      \param void
      \return void
    */ 
    void getRSSI();
    
    //! Displays current statistics, packet rx/tx counters, etc.
    /*!
      \param void
      \return void
    */ 
    void getStats();
    
    //! Displays number of seconds since last powerup or reboot.
    /*!
      \param void
      \return void
    */ 
    void getUpTime();
    
    //! Displays all adhoc settings.
    /*!
      \param void
      \return void
    */ 
    void getAdhocSettings();
    
    //! Displays the broadcast settings.
    /*!
      \param void
      \return void
    */ 
    void getBroadcastSettings();
    
    //! Displays comm. settings
    /*!
      \param void
      \return void
    */ 
    void getComSettings();
    
    //! Displays DNS settings.
    /*!
      \param void
      \return void
    */ 
    void getDNSsettings();
     
    //! Displays FTP settings.
    /*!
      \param void
      \return void
    */ 
    void getFTPsettings();
    
    //! Displays IP address and port number settings.
    /*!
      \param void
      \return void
    */ 
    void getIP();
    
    //! Displays the device MAC address.
    /*!
      \param void
      \return void
    */ 
    void getMAC();
    
    //! Displays the option settings like device ID.
    /*!
      \param void
      \return void
    */ 
    void getOptionSettings();
    
    //! Displays system settings, sleep, wake timers,etc.
    /*!
      \param void
      \return void
    */ 
    void getSystemSettings();
    
    //! Displays the time server UDP address and port number.
    /*!
      \param void
      \return void
    */ 
    void getTime();
    
    //! Displays the ssid, channel and other wlan settings.
    /*!
      \param void
      \return void
    */ 
    void getWLANsettings();
    
    //! Displays the UART settings.
    /*!
      \param void
      \return void
    */ 
    void getUARTsettings();
    
    //! Returns the software release version of the WIFI module.
    /*!
      \param void
      \return void
    */ 
    void getVersion();
    
    //! Set the comm flush size
    /*!
      \param unsigned int val 
      \return void
    */ 
    uint8_t setCommSize(unsigned int val);
    
    //! Set the comm flush timer
    /*!
      \param unsigned int val 
      \return void
    */ 
    uint8_t setCommTimer(unsigned int val);
     
    //! Wait for a number of bytes to be received in the UART
    /*!
      \param int numBytes: The number of bytes to be expected 
      \return '1' if numBytes have been received. '0' if time is up and numBytes
      have not been received.
    */ 
    uint8_t waitForData(int numBytes);
    
    //! Wait for a number of bytes to be received in the UART
    /*!
      \param int numBytes: The number of bytes to be expected 
      \param unsigned long timeout: number of milliseconds before timeout
      \return '1' if numBytes have been received. '0' if time is up and numBytes
      have not been received.
    */
    uint8_t waitForData(int numBytes, unsigned long timeout);
    
    //! Seek pattern within array of bytes
    /*!
      \param uint8_t* input: Input array of bytes 
      \param char* pattern: pattern to be seeked inside the input array of bytes 
      \param int len: Length of the input array of bytes 
      \return '1' if numBytes have been received. '0' if time is up and numBytes
      have not been received.
    */ 
    int findPattern(uint8_t* input, char* pattern, int len);
    
    //! Request OTA. FTP settings must be previsouly configured: user, pass, etc.
    /*!     
      \return '1' if numBytes have been received. '0' if time is up and numBytes
      have not been received.
    */ 
    int8_t requestOTA();
    
    //! Set RTC date taken from WiFi module
    /*!     
      \return '1' on succes, '0' otherwise
    */ 
    uint8_t setRTCfromWiFi();
    
 
};

extern WaspWIFI WIFI;

#endif
