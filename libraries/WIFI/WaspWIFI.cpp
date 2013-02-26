/*! \file WaspWIFI.cpp
 *  \brief Library for managing WIFI modules
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
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
 *  Version:		1.0
 *  Design:		David Gascón
 *  Implementation:	Joaquin Ruiz
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspWIFI.h"
///////////////////////////////////////////////////////////////////////////////

// Private Methods ////////////////////////////////////////////////////////////

//! Switches to command Mode
uint8_t WaspWIFI::commandMode(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t i=0;
  // Sends Enter command Mode ($$$)
  serialFlush(_uartWIFI); delay(100); //USB.println("++");
  while (serialAvailable(_uartWIFI)){}
  printString("$$$",_uartWIFI); delay(100);
  while(serialAvailable(_uartWIFI)<3){
    /*serialFlush(_uartWIFI); delay(100);
    printString("$$$",_uartWIFI); delay(100);*/
  } 
  // Waits Command Mode entered (CMD)
    while(serialAvailable(_uartWIFI)){
      if ((answer[i]=serialRead(_uartWIFI))!='\0'){
	       i++;
      }
      delay(10);
    }
  answer[i]='\0';
  // Checks the answer.
  if (contains(answer,"CMD\0"))
  {  
    USB.println(F("*CM")); beginSerial(baud_rate, _uartWIFI); delay(100);
    Utils.setLED(LED0,LED_ON);
    Utils.setLED(LED1,LED_ON);
    return 1;
  }
  else { return 0; }
}

//! Checks if 'word' is contatined in 'text'.
bool WaspWIFI::contains(char* text, char* word){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t ic, jc;
  ic=0;  jc=0;
  while (text[ic]!='\0'){ 
  // Until the end of text
    if (text[ic]==word[0]){ 
    // If the first word matches
      jc=0;
      while(word[jc]==text[jc+ic]){ 
        // While both match
        jc++;
        if (word[jc]=='\0'){ 
	         // If the word ends, they match!
	         return true;
	       }
      }
    }
    ic++;
  }
  // If the text ends, no matches.
  return false;
}

//! Reads data over the UART.
uint8_t WaspWIFI::readData(uint8_t length)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  if (serialAvailable(_uartWIFI)){ 
  // If there are data available...
    if (length!=0)while(serialAvailable(_uartWIFI)<length+3){}
    // Waits until there are lenght + 3 data in the uart.
    while(serialAvailable(_uartWIFI)){
    // While serial available over the uart...
      if ((i<512)&&((answer[i]=serialRead(_uartWIFI))!='\0')){
	     i++; //printString(".",_usb);
      }
      delay(10);
    }
  } 
  answer[i]='\0';
  // Checks the answer.
  if (contains(answer,"AOK\0")){
    /*printString("\n",_usb);*/ return 1;
  }
  else
  {
    if (contains(answer,"ERR\0")||contains(answer,"Disconn\0")||
      contains(answer,"FAILED\0"))
    {  return 0;}
    else 
    {  return 1;}
  }
}

//! Sends the command 'comm' over the UART.
uint8_t WaspWIFI::sendCommand(char* comm)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t i=0;
  // Writes 'comm' over the UART.
  serialFlush(_uartWIFI); delay(100);
  while (serialAvailable(_uartWIFI)){}
  USB.println(comm); beginSerial(baud_rate, _uartWIFI); delay(100);
  printString(comm,_uartWIFI); delay(100);
  // Waits an answer from the UART
  while (!serialAvailable(_uartWIFI)) {printString(comm,_uartWIFI); delay(100);}
  while(comm[i]!='\0'){i++;}
  // Calls readData to take and to check the answer.
  return readData(i);
}

//! Saves current configuration and reboots the device in order to new 
//! configuration takes effect.
uint8_t WaspWIFI::saveReboot(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Saves current configurations.
  storeData();
  // Reboots the module. (don't call reset() because this is special reboot
  // for auto-connect, etc...)
  sprintf(question, "reboot%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<15){}
  while(serialAvailable(_uartWIFI)){
    if ((answer[i]=serialRead(_uartWIFI))!='\0'){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
  // Check if the answer contains Error messages, including connection 
  // error messages.
  if (contains(answer,"ERR\0")||contains(answer,"No matching APs\0")||
    contains(answer,"FAILED\0")||contains(answer,"Found 0\0"))
  {  USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100); return 0; }
  else 
  {  return 1;}
  return 0;
}

//! Opens TCP connection, and checks that everything are going good.
uint8_t WaspWIFI::open()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t i=0;
  // Sends command 'open' to open the connection configured before.
  //serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  USB.println(F("open"));beginSerial(baud_rate, _uartWIFI); delay(100);
  printString("open\r",_uartWIFI);
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<20){}
  while(i<20){
    if ((answer[i]=serialRead(_uartWIFI))!='\0'){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
  // Checks the answer.
  if (contains(answer,"*OPEN*\0")){
    return 1;
  }
  else{
    return 0;  
  }
}

//! Opens http connection, and checks that everything are going good.
uint8_t WaspWIFI::openHTTP()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends command 'open' to open the connection configured before.
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  USB.println(F("open"));beginSerial(baud_rate, _uartWIFI); delay(100);
  printString("open\r",_uartWIFI);
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<20){}
  while(serialAvailable(_uartWIFI)){
    if ((i<512)&&((answer[i]=serialRead(_uartWIFI))!='\0')){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
  // Checks the answer.
  if (contains(answer,"*OPEN*\0")){
     USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100); return 1;
  }
  else{
    return 0;  
  }
}
	
//! Reads a broadcast message and parses it.
void WaspWIFI::parseBroadcast()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  int i=0;
  // Reboots to waits those UDP messages.
  saveReboot();
  while(1)
  {
    // Waits the UDP message (lenght ~90)
    while(serialAvailable(_uartWIFI)<90){}
    while(serialAvailable(_uartWIFI)){
      answer[i]=serialRead(_uartWIFI);
      i++;
    }
    i=0;
    // First characters = MAC address.
    while (i<6){
      USB.print(answer[i]); i++;
    }
    USB.println();
    i=60;
    // Device ID string.
    while (i<92){
      USB.print(answer[i]);
      i++;
    }
    USB.println(); 
  }
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

// Public Methods /////////////////////////////////////////////////////////////

// Constructors ///////////////////////////////////////////////////////////////

//! Class constructor. Initializes the necessary variables.
WaspWIFI::WaspWIFI()
{
  _uartWIFI=1;
  //_usb=0;
  scanTime=200;
  scanPassive=false;
  baud_rate=9600;
}

// Basic Methods //////////////////////////////////////////////////////////////



//! Powers on the module and enters in command mode.
void WaspWIFI::ON(uint8_t sock)
{
  SD.ON();				// Used in FTP operations.
  USB.ON();       // Used to debug in serialMonitor.
  if (sock==SOCKET0)
  {
    _uartWIFI=0;
    //_usb=0;

    Utils.setMuxSocket0();
    // set microcontroller pins as output
    pinMode(XBEE_PW,OUTPUT);
    //pinMode(MUX_PW,OUTPUT);
    //pinMode(MUX_USB_XBEE,OUTPUT);
  
    // set multiplexor supply on
    //digitalWrite(MUX_PW,HIGH);
    //digitalWrite(MUX_USB_XBEE,HIGH);
    digitalWrite(XBEE_PW, LOW);
    digitalWrite(XBEE_PW, HIGH);
  }
  else if (sock==SOCKET1)
  {
   /* pinMode(MUX_PW, OUTPUT);
    pinMode(MUX0, OUTPUT);      
    pinMode(MUX1, OUTPUT);   
    digitalWrite(MUX_PW, HIGH);   
    digitalWrite(MUX0, HIGH);
    digitalWrite(MUX1, HIGH);	// Is used by GPRS uart adaptator

    // Switches ON the module.
    pinMode(DIGITAL6,OUTPUT);
    digitalWrite(DIGITAL6,HIGH);
    pinMode(GPRS_PW, OUTPUT);
    digitalWrite(GPRS_PW, HIGH);
    delay(2000);
    digitalWrite(GPRS_PW, LOW);*/

    Utils.setMuxSocket1();   
    pinMode(DIGITAL6,OUTPUT);
    digitalWrite(DIGITAL6,HIGH);
    // FIXME: This will disappear in the final version
    pinMode(GPRS_PW,OUTPUT);
    digitalWrite(GPRS_PW,HIGH); 
  }
  //beginSerial(USB_RATE, _usb);
  beginSerial(baud_rate, _uartWIFI); delay(100); 	// Baud rate= 9600, uart= 1
  serialFlush(_uartWIFI); delay(100);
  readData(0);
  // Enters in command mode.
  while(commandMode()!=1){}
  
  sprintf(question, "set s p 0x4000%c",'\r');
  sendCommand(question);
}

//! Closes the UART and powers off the module.
void WaspWIFI::OFF()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Exits from command mode.
  printString("exit\r",_uartWIFI); 
  // Switches OFF the module.
  pinMode(DIGITAL6,OUTPUT);
  digitalWrite(DIGITAL6,LOW);
  delay(500);
  USB.println(F("*OFF")); beginSerial(baud_rate, _uartWIFI); delay(100);
  Utils.setLED(LED0,LED_ON);
  Utils.setLED(LED1,LED_ON);
}

// Access point configuration methods /////////////////////////////////////////

//! Sets the wlan channel, 1-13 is the valid range for a fixed channel.
uint8_t WaspWIFI::setChannel(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w c %d%c",val,'\r');
  return sendCommand(question);
}

//! Sets the authentication mode.
uint8_t WaspWIFI::setAutojoinAuth(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w a %d%c",val,'\r');
  return sendCommand(question);
}

//! Sets the policy for automatically joining/associating with network 
//! access points.
uint8_t WaspWIFI::setJoinMode(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Leaves previous connection.
  leave();
  sprintf(question, "set w j %d%c",val,'\r');
  if ((sendCommand(question)==1)&&(saveReboot()==1))
  {
    // Enters in command Mode.
    while(commandMode()!=1){}
    // If auto
    if ((val==AUTO_BEST)||(val==AUTO_STOR))
    { // If Auto Best check 2 times more for the scan.
      //if (val==AUTO_BEST){ isConnected(); isConnected();}
      // Checks 3 times if it is (Auto) connected.
      //if (!isConnected()) if(!isConnected()) if(!isConnected())
      while(!isConnected()) {  Utils.setLED(LED0,LED_ON); delay(200); Utils.setLED(LED0,LED_OFF); }
    }
    else if (val==CREATE_ADHOC){
      // Checks until is correctly connected in Adhoc mode.
      while(!isConnected()){}
      // Exit from command mode.
     /* serialFlush(_uartWIFI);
      while (serialAvailable(_uartWIFI)){}
      printString("exit\r",_uartWIFI); */
    }
    return 1;
  }
}
	
//! Sets the Key or the passphrase of the wlan.
uint8_t WaspWIFI::setAuthKey(uint8_t secMode, char* pass)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  char *pass2 = (char *)malloc(27);
  char numch[2];
  uint8_t i=0, j=0;
  // If WEP, translate to HEX and sets key.
  if (secMode==WEP){
    while (i<13){
      sprintf(numch,"%x",pass[i]); 
      /*serialFlush(_usb);
      serialWrite(numch[0],_usb); serialWrite(numch[1],_usb); 
      serialWrite('\n',_usb);*/
      pass2[j]=numch[0]; j++; 
      pass2[j]=numch[1]; j++;
      i++;
    }
    pass2[26]='\0';
    sprintf(question, "set w k %s%c",pass2,'\r');
  }
  // If not, sets passphrase in ASCII.
  else
    sprintf(question, "set w p %s%c", pass, '\r'); 
  // Sends the command over the UART.
  return sendCommand(question);
}

//! Sets the link monitor timeout threshold.
uint8_t WaspWIFI::setAPretries(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w l %d%c",val,'\r');
  return sendCommand(question);
}
	
//! Sets the Scan options, but does not launch the scan.
uint8_t WaspWIFI::setScanOptions(uint16_t time, char* mask, bool passive)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  scanTime=time;
  scanPassive=passive;
  sprintf(question, "set w m %s%c",mask,'\r');
  return sendCommand(question);
}
	
//! Launches the scan.
void WaspWIFI::scan()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sets the command depending of if it is Passive.
  if (scanPassive==false)
      sprintf(question, "scan %d%c",scanTime,'\r');
  else 
      sprintf(question, "scan %d P%c",scanTime, '\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<20){}
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; answer[511]='\0'; 
  // Shows the results of the scan.
  USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Sets the ESSID of the wlan.
uint8_t WaspWIFI::setESSID(char* ssid)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w s %s%c",ssid,'\r');
  return sendCommand(question);
}
	
//! Sets the Transmission Rate.
uint8_t WaspWIFI::setTXRate(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w r %d%c",val,'\r');
  return sendCommand(question);
}
	
//! Sets the Transmission Power.
uint8_t WaspWIFI::setTXPower(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w tx %d%c",val,'\r');
  return sendCommand(question);  
}
	
//! Sets the IP Window value.
uint8_t WaspWIFI::setIPWindow(uint16_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set w w %d%c",val,'\r');
  return sendCommand(question);
}
	
//! Joins the chosen ssid.
uint8_t WaspWIFI::join(char* ssid)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Sends command to join an Access Point.
  sprintf(question, "join %s%c",ssid, '\r');
  //serialFlush(_uartWIFI); //serialFlush(_usb);
  if(sendCommand(question)){
    // Checks 3 times if it is correctly connected.
    if (!isConnected()) if(!isConnected()) if(!isConnected()) if (!isConnected()) if(!isConnected()) if(!isConnected())
    {  return 0; }
    return 1; 
  }
}
	
//! Joins a network AP from the scan list.
uint8_t WaspWIFI::joinAPnum(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Sends command to join an Access Point.
  sprintf(question, "join # %d%c",val, '\r');
  serialFlush(_uartWIFI); //serialFlush(_usb);
  if(sendCommand(question)){
    // Checks 3 times if it is correctly connected.
    if (!isConnected()) if(!isConnected()) if(!isConnected())
    {  return 0; }
    return 1; 
  }
}
	
//! If connected, leaves the connected network
uint8_t WaspWIFI::leave()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "leave%c",'\r');
  return sendCommand(question);
}
	
//! Join timer is the time in milliseconds the join function will wait for an
//! access point to complete the association process. This timer is also the 
//! timeout for the WPA handshaking process.
uint8_t WaspWIFI::setJoinTime(uint16_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set o j %d%c",val,'\r');
  return sendCommand(question);
}

// Connection Configuration Methods ///////////////////////////////////////////

//! Sends a ping to a remote specified host.
void WaspWIFI::sendPing(ipAddr ip)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command over the uart.
  sprintf(question, "ping %s 10%c",ip,'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer from the uart.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<15){}
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  // Shows the result of the ping.
  answer[i]='\0'; USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Synchronizes the time from the server.
uint8_t WaspWIFI::setTimeFromServer(ipAddr ip, uint16_t port, uint8_t interval)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1, u2, u3;
  sprintf(question, "set t a %s%c",ip,'\r');
  u1=sendCommand(question);
  sprintf(question, "set t p %d%c",port,'\r');
  u2=sendCommand(question);
  sprintf(question, "set t e %d%c",interval,'\r');
  u3=sendCommand(question);
  if ((u1==1)&&(u2==1)&&(u3==1))
    return 1;
  else
    return 0;  
}

//! Sets the sleep time and the wake time (in seconds).
uint8_t WaspWIFI::setSleep(uint8_t sTime, uint8_t sCycle)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1,u2;
  sprintf(question, "set s w %d%c",sTime,'\r');
  u1= sendCommand(question);
  sprintf(question, "set s s %d%c",sCycle,'\r');
  u2= sendCommand(question);
  if ((u1==1)&&(u2==1))
  {
    if (saveReboot()==1)
      while(commandMode()!=1){} return 1;
  }
  return 0;
}

//! Controls debug print messages. This configures the debug messages
//! printed by the WiFly module on the UART.
uint8_t WaspWIFI::setDebugMode(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set s p %d%c",val,'\r');
  return sendCommand(question);
}

//! Sets the Gateway address.
uint8_t WaspWIFI::setGW(ipAddr ip)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i g %s%c",ip,'\r');
  return sendCommand(question);
}

//! Sets the netmask.
uint8_t WaspWIFI::setNetmask(ipAddr netmask)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i n %s%c",netmask,'\r');
  return sendCommand(question);  
}

//! Sets the Remote Host.
uint8_t WaspWIFI::setRemoteHost(ipAddr ip, uint16_t port)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i h %s%c",ip,'\r');
  
  if (sendCommand(question)==1)
  {
    sprintf(question, "set i r %d%c",port,'\r');
    return sendCommand(question);
  }
  return 0;
}

//! Sets the Local Port.
uint8_t WaspWIFI::setLocalPort(uint16_t port)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i l %d%c",port,'\r');
  return sendCommand(question);  
}

//! Sets the IP address.
uint8_t WaspWIFI::setIp(ipAddr ip)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i a %s%c",ip,'\r');
  return sendCommand(question);  
}

//! Sets the DHCP options.
uint8_t WaspWIFI::setDHCPoptions(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i d  %d%c",val,'\r');
  return sendCommand(question);  
}

//! Sets the IP options.
uint8_t WaspWIFI::setIPoptions(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i f %d%c",val,'\r');
  return sendCommand(question);  
}

//! Sets the connection options. (TCP, UDP, HTTP...) Value is a bit 
//! mapped setting.
uint8_t WaspWIFI::setConnectionOptions(uint8_t val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set i p %d%c",val,'\r');
  return sendCommand(question);  
}
	
//! Sets the TCP connection password. Provides minimal authentication by 
//! requiring any remote device that connects to send and match a challenge
//! <val>. When set, all newly opened connections must first send the exact
//! characters that match the stored password, otherwise the WIFI module  
//! will close the connection.
uint8_t WaspWIFI::setTCPpassw(char* password)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set o p %s%c",password,'\r');
  return sendCommand(question);  
}

//! Sets the IP address, host and backup host of the DNS main 
//! or auxiliary server.
uint8_t WaspWIFI::setDNS(uint8_t type, ipAddr ip, char* name){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Sets the dns address.
  sprintf(question, "set d a %s%c",ip,'\r');
  if(sendCommand(question)==1)
  {
    // Depending on MAIN or AUX, sets DNS name or backup.
    if (type==MAIN)
    {
      sprintf(question, "set d n %s%c",name,'\r');
      return sendCommand(question);
    }
    else
    {
      sprintf(question, "set d b %s%c",name,'\r');
      return sendCommand(question);
    }
  }
  return 0;
}

//! Sets the FTP parameters.
uint8_t WaspWIFI::setFTP(ipAddr ip, uint16_t port, uint8_t mode, 
			 uint8_t timeout)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1, u2, u3, u4;
  sprintf(question, "set f a %s%c", ip, '\r');
  u1=sendCommand(question);
  sprintf(question, "set f r %d%c", port, '\r');
  u2=sendCommand(question);
  sprintf(question, "set f m %d%c", mode, '\r');
  u3=sendCommand(question);
  sprintf(question, "set f t %d%c", timeout*8, '\r');
  u4=sendCommand(question);
  if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1))
    return 1;
  else
    return 0;
}
	
//! Opens the ftp connection using the user and the password given.
uint8_t WaspWIFI::openFTP(char* user, char* password)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1,u2;
  sprintf(question, "set f u %s%c", user, '\r');
  u1=sendCommand(question);
  sprintf(question, "set f p %s%c", password, '\r');
  u2=sendCommand(question);
  // Reboots
  if ((u1==1)&&(u2==1)&&(saveReboot()==1))
  {
    // Enters in command mode.
    while(commandMode()!=1){}
    return 1;
  }
  return 0;
}

//! Gets the file via FTP.
uint8_t WaspWIFI::getFile(char* file, char* local_folder, char* remote_folder)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0, j=0, plong=0;
  char towrite[512];
  // Sets the directory in the FTP server to get the file.
  sprintf(question, "set f d /%s%c",remote_folder,'\r');
  if (sendCommand(question)==1)
  {
    // Sends the command that gets the file.
    sprintf(question, "ftp g %s%c", file, '\r');
    while(question[plong]!='\0'){plong++;}
    serialFlush(_uartWIFI);
    while (serialAvailable(_uartWIFI)){}
    USB.println(question); beginSerial(baud_rate, _uartWIFI); delay(100);
    printString(question,_uartWIFI);
    // Waits an answer over the uart.
    while (!serialAvailable(_uartWIFI)) {}
    plong=plong+10;
    while(serialAvailable(_uartWIFI)<plong){}
    while(serialAvailable(_uartWIFI)){
      if ((i<512)&&((answer[i]=serialRead(_uartWIFI))!='\0')){
	i++;
      }
      delay(10);
    }
    answer[i]='\0';  
    // Checks the answer (Until ERR or until *CLOS*)
    while(!(contains(answer,"timeout\0")||contains(answer,"*CLOS*\0")||
      contains(answer,"ERR\0")))
    { 
      i--;
      while(!serialAvailable(_uartWIFI)){}
      while(serialAvailable(_uartWIFI)){
	if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
	  i++;
	}
	delay(10);
      }
      answer[i]='\0';
    }
    // *CLOS* means received correctly.
    if (contains(answer,"*CLOS*\0"))
    {
      i=0;
      while (answer[i]!='*') //*OPEN*
      { i++; }
      i=i+5;
      while (answer[i]!='*') //*CLOS*
      {
	towrite[j]=answer[i];
	j++;
	i++;
      }
      towrite[j]='\0'; 
      // In 'towrite' there is the content of the file.
      USB.println(towrite); beginSerial(baud_rate, _uartWIFI); delay(100);
      // Selects SD card local folder.
      SD.cd(local_folder);
      // Creates a file in that folder.
      SD.create(file);
      // Insert that file with the content of 'towrite'.
      SD.appendln(file,towrite);
      return 1;
    }
    // Otherwise means error while 'get ftp' command.
  }
  return 0;
}

//! Uploads a file via FTP.
uint8_t WaspWIFI::uploadFile(char* file, char* local_folder,
			     char* remote_folder)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0, size, plong=0;
  // Sets the directory in the FTP server to upload the file.
  sprintf(question, "set f d /%s%c",remote_folder,'\r');
  if (sendCommand(question)==1)
  {
    // Sends the command that uploads the file.
    sprintf(question, "ftp p %s%c", file, '\r');
    while(question[plong]!='\0'){plong++;}
    serialFlush(_uartWIFI);
    while (serialAvailable(_uartWIFI)){}
    USB.println(question); beginSerial(baud_rate, _uartWIFI); delay(100);
    printString(question,_uartWIFI);
    // Waits an answer over the uart.
    while (!serialAvailable(_uartWIFI)) {}
    plong=plong+10;
    while(serialAvailable(_uartWIFI)<plong){}
    while(serialAvailable(_uartWIFI)){
      if ((i<512)&&((answer[i]=serialRead(_uartWIFI))!='\0')){
	i++;
      }
      delay(10);
    }
    answer[i]='\0';
    // Checks the answer (Until ERR or until *OPEN*)
    while(!(contains(answer,"timeout\0")||contains(answer,"OPEN\0")
      ||contains(answer,"ERR\0")))
    { 
      i=0; delay(20);
      if(serialAvailable(_uartWIFI))
	while(serialAvailable(_uartWIFI)){
	  if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
	    i++;
	  }
	  delay(10);
	}
	answer[i]='\0';
    }
    USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
    // OPEN means connected correctly and waiting the file.
    if (contains(answer,"OPEN\0"))
    {
      // Selects SD card local folder.
      SD.cd(local_folder);
      // Sends content of the file over the uart.
      size=SD.getFileSize(file);
      printString(SD.cat(file,0,size),_uartWIFI); 
      delay(100);
      // Sends *CLOS* to indicate the end of the file and connection.
      printString("*CLOS*",_uartWIFI);
      // Waits an answering CLOS to check the connection from and 
      // to the FTP server is correctly closed.
      i=1;
      while(!contains(answer,"CLOS\0"))
      { 
	i--;
	while(!serialAvailable(_uartWIFI)){}
	while(serialAvailable(_uartWIFI)){
	  if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
	    i++;
	  }
	  delay(10);
	}
	answer[i]='\0';
      } 
    USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
      return 1;
    }
    // Otherwise means error while 'put ftp' command.
  }
  return 0;
}

// Connection Configuration Methods ///////////////////////////////////////////

//! Sets the http config and opens an HTTP connection.
uint8_t WaspWIFI::getURL(uint8_t opt, char* host, char* request)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1,u2,u3,u4,u5;
  // If the address is given by a IP address.
  if (opt==IP)
  {
    sprintf(question,"set i h %s%c",host,'\r');
    u1=sendCommand(question);
    u2=1;
  }
  // If the address is given by a URL address.
  else
  {
    sprintf(question,"set i h 0%c",'\r');
    u1=sendCommand(question);
    sprintf(question,"set d n %s%c",host,'\r');
    u2=sendCommand(question);
  }
  sprintf(question,"set i r 80%c",'\r');
  u3=sendCommand(question);
  sprintf(question,"set c r %s%c",request,'\r');
  u4=sendCommand(question);
  sprintf(question,"set o f 1%c",'\r');
  u5=sendCommand(question);
  // If everything is Ok, even it is correctly connected.
  if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(isConnected()))
  { 
    // Opens the HTTP connection.
    if(openHTTP())  
    { // Reads the answer of the HTTP query.
      read(BLO); 
      // Enters in command mode again.
      while(commandMode()!=1){} 
      return 1;
    }
  }
  return 0;  
}

//! Sets the configuration and opens a TCP client connection.
uint8_t WaspWIFI::setTCPclient(ipAddr ip_remote, uint16_t port_remote,
			       uint16_t port_local)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1,u2,u3;  
  // Configures TCP connection.
  sprintf(question,"set i h %s%c",ip_remote,'\r');
  u1=sendCommand(question);
  sprintf(question,"set i r %d%c",port_remote,'\r');
  u2=sendCommand(question);
  sprintf(question, "set i l %d%c",port_local, '\r');
  u3=sendCommand(question);
  // Checks if everything is Ok, even if It's correctly connected.
  if ((u1==1)&&(u2==1)&&(u3==1)&&(isConnected()))
  { 
    // Opens the Connection, and lets it open until calling close().
    return open();
  }
  return 0;
}
	
//! Sets the configuration and opens a TCP server connection.
uint8_t WaspWIFI::setTCPserver(uint16_t port_local)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1;
  // Configures TCP port and listens on the connection.
  sprintf(question, "set i l %d%c",port_local, '\r');
  u1=sendCommand(question);
  // Checks if everything is Ok, even if It's correctly connected.
  if ((u1==1)&&(isConnected()))
  {
    return 1;
  }
  return 0;
}
	
//! Sets the configuration and opens a UDP client connection.
uint8_t WaspWIFI::setUDPclient(ipAddr ip_remote, uint16_t port_remote, 
			       uint16_t port_local)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1,u2,u3;
  // Configures UDP host and ports.
  sprintf(question,"set i h %s%c",ip_remote,'\r');
  u1=sendCommand(question);
  sprintf(question,"set i r %d%c",port_remote,'\r');
  u2=sendCommand(question);
  sprintf(question, "set i l %d%c",port_local, '\r');
  u3=sendCommand(question);
  // Checks if everything is Ok, even if It's correctly connected.
  if ((u1==1)&&(u2==1)&&(u3==1)&&(isConnected()))
  { 
    // Exits from command mode, and then the UDP messages 
    // can be sent and received.
    sprintf(question,"exit%c",'\r');
    return sendCommand(question);
  }
  return 0;

}
	
//! Sets the configuration and opens a UDP server connection.
uint8_t WaspWIFI::setUDPserver(uint16_t port_local)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u1;
  // Configures UDP port. 
  sprintf(question, "set i l %d%c",port_local, '\r');
  u1=sendCommand(question);
  // Checks if everything is Ok, even if It's correctly connected.
  if ((u1==1)&&(isConnected()))
  {
    // Exits from command mode, and then the UDP messages 
    // can be sent and received.
    sprintf(question,"exit%c",'\r');
    return sendCommand(question);
  }
  return 0;
}
	
//! Reads data from the opened connection.
int WaspWIFI::read(uint8_t blo)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Waits an answer.
  unsigned long t1=millis();
  // if it is blocking, wait until is received
  if (blo==BLO){ 
    while(!serialAvailable(_uartWIFI)){} 
  }
  // if it isn't wait until something is received or 2 seconds
  else{
    while(!serialAvailable(_uartWIFI)){
      if (millis()-t1>2000) return 0;
    }
  }  
  while(serialAvailable(_uartWIFI)){
      if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
	i++; 
      }
   // delay(10);
    }
    answer[i]='\0'; 
  
  // Prints the answer.
    USB.print(F("R: ")); USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
  // Returns the number of characters of the answer.
  return i;
}
	
//! Sends data to the opened connection.
void WaspWIFI::send(char* data)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Writes what we want to send on the UART. 
  printString(data,_uartWIFI);
  
   // USB.print("S: "); USB.println(data); beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Sends data to the opened connection.
void WaspWIFI::send(uint8_t* data, uint16_t length)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Writes what we want to send on the UART. 
  for (int i=0; i<length; i++)
  {
    printByte(data[i],_uartWIFI);
  }
    
   // USB.print("S: "); USB.println(data); beginSerial(baud_rate, _uartWIFI); delay(100);
}


//! Closes current connection.
uint8_t WaspWIFI::close()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Enters in command mode.
  while(commandMode()!=1){}
  // Send command 'close'.
  sprintf(question,"close%c",'\r');
  return sendCommand(question);
}

//! Configures and sends broadcast packages.
uint8_t WaspWIFI::sendAutoBroadcast(ipAddr ip_network, uint16_t port_remote, 
				    uint8_t interval, char* id)
{ 
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u0, u1, u2, u3, u4;
  // Configure Broadcast settings.
  u0=setConnectionOptions(UDP);
  sprintf(question, "set b a %s%c",ip_network, '\r');
  u1=sendCommand(question);
  sprintf(question, "set b i %d%c",interval, '\r'); //2-256
  u2=sendCommand(question);
  sprintf(question, "set b p %d%c",port_remote, '\r');
  u3=sendCommand(question);
  sprintf(question, "set o d %s%c",id, '\r');
  u4=sendCommand(question);
  if ((u0==1)&&(u1==1)&&(u2==1)&&(u3==1)&&(u4==1))
    // If everything Ok, automatically UDP broadcast messages are sent.
    return 1;
  else
    return 0;
}
	
//! Configures and opens an adhoc connection.
uint8_t WaspWIFI::setAdhocOptions(uint16_t beacon, uint16_t probe_interval)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t u0, u1, u2;
  // Configure ADHOC settings.
  u0=setDHCPoptions(AUTO_IP);
  sprintf(question, "set a b %d%c",beacon,'\r');
  u1=sendCommand(question);
  sprintf(question, "set a p %d%c",probe_interval, '\r');
  u2=sendCommand(question);
  if ((u0==1)&&(u1==1)&&(u2==1))
    // If everything correct, call join_mode -> create_AdHoc.
    return setJoinMode(CREATE_ADHOC);
  else
    return 0;
}

// Device Configuration ///////////////////////////////////////////////////////

//! Reboots the device (ON-OFF-ON).
void WaspWIFI::reset()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint8_t i=0;
  // Sends reboot command.
  sprintf(question, "reboot%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<8){}
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
  // Enters in command mode.
  while(commandMode()!=1){}
}
	
//! Restores the default settings of the device.
void WaspWIFI::resetValues()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Sends reset command.
  sprintf(question, "factory RESET%c",'\r');
  sendCommand(question); 
  // Resets to take effect.
  reset();
  // Sets default print mode.
  sprintf(question, "set s p 0x4000%c",'\r');
  sendCommand(question);
}
	
//! Sleeps the device.
void WaspWIFI::sleep()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)) {}
  printString("sleep\r",_uartWIFI);
}
	
//! Wakes the device and enters in command mode.
void WaspWIFI::wake()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  // Write something on the UART.
 // serialFlush(_uartWIFI);
//  while (serialAvailable(_uartWIFI)) {}
  // Waits an answer from the module.
  while(!serialAvailable(1)){serialWrite('.',_uartWIFI);/*serialWrite('.',_usb);*/}
  while(serialAvailable(1)){
    serialWrite(serialRead(1),0);
    delay(10);
  }
  // Enters in command mode.
  while(commandMode()!=1){}
}
	
//! Synchronizes the time.
void WaspWIFI::synchronizeTime()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "time%c",'\r');
  sendCommand(question);  
}
	
//! Performs a DNS query on the supplied hostname.
void WaspWIFI::resolve(char* name)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends lookup command.
  sprintf(question, "lookup %s%c",name,'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer from the module.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  // Prints the result of the query.
  answer[i]='\0';    
  USB.print(F("R: ")); USB.println(answer); beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Sets the UART baud rate.
void WaspWIFI::setBaudRate(int val)
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "set u b %d%c",val,'\r');
  sendCommand(question);
}
	
//! Saves current configuration.
void WaspWIFI::storeData()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  sprintf(question, "save%c",'\r');
  sendCommand(question);
}

// Status Information /////////////////////////////////////////////////////////

//! Checks if the module is connected to the Access Point 
//! (Check if it has an IP address).
bool WaspWIFI::isConnected()
{
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends 'get ip' command to know if the module has good IP address.
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString("get ip\r",_uartWIFI); /*USB.println("ip?");
  beginSerial(baud_rate, _uartWIFI); delay(100);*/
  // Waits an answer from the UART.
  while (!serialAvailable(_uartWIFI)) {}
  while(serialAvailable(_uartWIFI)<10){}
  while(serialAvailable(_uartWIFI)){
    if ((i<512)&&((answer[i]=serialRead(_uartWIFI))!='\0')){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
  // Checks the answer.
  if (contains(answer,"IF=UP\0"))
  {  return true;}
  else 
  {  return false;}
}

//! Displays connection status
void WaspWIFI::getConnectionInfo(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  uint8_t temp;
  // Sends command over the UART.
  sprintf(question, "show c%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0';
//  printString("\n***Connection info***\n",_usb);
  USB.print(F("Chann: ")); USB.println(answer[19]);
  // Parses the answer and shows it.
  if (int(answer[20]>=int('A')))
    temp = int(answer[20])-int('A')+10;
  else
    temp = int(answer[20])-int('0');
  if (temp&1==1)
    USB.println(F("Assoc: OK"));
  if (temp&2==2)
    USB.println(F("Authen: OK"));
  if (temp&4==4)
    USB.println(F("DNS server = contacted"));
  if (temp&8==8)
    USB.println(F("DNS found = resolved"));
  if (answer[21]=='0')
    USB.println(F("TCP status = Idle"));
  if (answer[21]=='1')
    USB.println(F("TCP status = Connected"));
  if (answer[21]=='3')
    USB.println(F("TCP status = NOIP"));
  if (answer[21]=='4')
    USB.println(F("TCP status = Connecting"));
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Displays current network status, association, authentication, etc.
void WaspWIFI::getAPstatus(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "show n%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the network information.
//  printString("\n***Network info***\n",_usb);
  while (i<126-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays current last received signal strenght.
void WaspWIFI::getRSSI(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "show r%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=10;
  // Shows the information.
//  printString("\n***Singal Strenght info***\n",_usb);
  while (i<34-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Displays current statistics, packet rx/tx counters, etc.
void WaspWIFI::getStats(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "show s%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=11;
  // Shows the information.
//  printString("\n***Statistics info***\n",_usb);
  while (i<190-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
//  printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Displays number of seconds since last powerup or reboot.
void WaspWIFI::getUpTime(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "show t%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=10;
  // Shows the information.
//  printString("\n***Seconds since last powerup or reboot***\n",_usb);
  while (i<45-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Displays all adhoc settings.
void WaspWIFI::getAdhocSettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get a%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=10;
  // Shows the information.
//  printString("\n***Adhoc settings***\n",_usb);
  while (i<40-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
//  printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}
	
//! Displays the broadcast settings.
void WaspWIFI::getBroadcastSettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get b%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=13;
  // Shows the information.
//  printString("\n***Broadcast settings***\n",_usb);
  while (i<65-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 //printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays comm. settings
void WaspWIFI::getComSettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get c%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the information.
//  printString("\n***Communications settings***\n",_usb);
  while (i<126-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays DNS settings.
void WaspWIFI::getDNSsettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get d%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the information.
//  printString("\n***DNS settings***\n",_usb);
  while (i<60-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays FTP settings.
void WaspWIFI::getFTPsettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get f%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the information.
//  printString("\n***FTP settings***\n",_usb);
  while (i<124-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays IP address and port number settings.
void WaspWIFI::getIP(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get i%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=7;
  // Shows the information.
//  printString("\n***IP Settings***\n",_usb);
  while (i<162-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays the device MAC address.
void WaspWIFI::getMAC(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get m%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the information.
//  printString("\n***MAC address***\n",_usb);
  while (i<45-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays the option settings like device ID.
void WaspWIFI::getOptionSettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get o%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=11;
  // Shows the information.
//  printString("\n***Option settings***\n",_usb);
  while (i<112-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays system settings, sleep, wake timers,etc.
void WaspWIFI::getSystemSettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get s%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=8;
  // Shows the information.
// printString("\n***System settings***\n",_usb);
  while (i<121-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays the time server UDP address and port number.
void WaspWIFI::getTime(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get t%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=9;
  // Shows the information.
//  printString("\n***Time server information***\n",_usb);
  while (i<62-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays the ssid, channel and other wlan settings.
void WaspWIFI::getWLANsettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get w%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=9;
  // Shows the information.
 // printString("\n***WLAN settings***\n",_usb);
  while (i<141-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
//  printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Displays the UART settings.
void WaspWIFI::getUARTsettings(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "get u%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=9;
  // Shows the information.
 // printString("\n***UART settings***\n",_usb);
  while (i<53-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

//! Returns the software release version of the WIFI module.
void WaspWIFI::getVersion(){
  beginSerial(baud_rate, _uartWIFI); delay(100);
  uint16_t i=0;
  // Sends the command.
  sprintf(question, "ver%c",'\r');
  serialFlush(_uartWIFI);
  while (serialAvailable(_uartWIFI)){}
  printString(question,_uartWIFI);
  // Waits an answer.
  while (!serialAvailable(_uartWIFI)) {}
  while (question[i]!='\0') {  i++; }
  i=i+5;
  while(serialAvailable(_uartWIFI)<i){}
  i=0;
  while(serialAvailable(_uartWIFI)){
    if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<512)){
      i++;
    }
    delay(10);
  }
  answer[i]='\0'; i=4;
  // Shows the information.
 // printString("\n***Version***\n",_usb);
  while (i<51-7){
    USB.print(answer[i]);
    i++;
  }
  USB.println();
 // printString("\n******************************\n",_usb);
  beginSerial(baud_rate, _uartWIFI); delay(100);
}

// Preinstantiate Objects /////////////////////////////////////////////////////

WaspWIFI WIFI=WaspWIFI();

///////////////////////////////////////////////////////////////////////////////
