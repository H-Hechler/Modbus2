/*------------------- Mehrfach Defines verhindern ----------------------------*/
#ifndef KOSTAL_H_
#define KOSTAL_H_

#ifdef MAIN
#define EXTERN 
#else
#define EXTERN extern
#endif


#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"
#define MAX_STRING_LEN 50
#include <iostream>
#include <string>
#include <SPI.h>
#include <stdint.h>
#include <WiFi.h>
#include <ArduinoRS485.h>  // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "arduino_secrets.h"
#include "array.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFiUdp.h>
#include <mbed_mktime.h>
#include <String.h>



// Time zone info
#define TZ_INFO "UTC1"
#define MAX_FAILED_CONNECTS 20
// Declare InfluxDB client instance with preconfigured InfluxCloud certificate



extern WiFiClient client;
extern WiFiClient client1;
extern WiFiServer server;
extern WiFiUDP Udp;
extern long count, value, value2, val;
extern float floatValue;
extern char charArray[4];
extern char ssid[];  // your network SSID (name)
extern char pass[];  // your network password (use for WPA, or use as key for WEP)
extern int keyIndex;
extern int status;
extern char wserver[];  // host name for example.com (using DNS)
EXTERN char INSERTSQL[500] ;
EXTERN int countSQL;



/* extern unsigned int localPort = 2390; // local port to listen for UDP packets
// IPAddress timeServer(162, 159, 200, 123); // pool.ntp.org NTP server
extern constexpr auto timeServer { "pool.ntp.org" };
extern const int NTP_PACKET_SIZE = 48; // NTP timestamp is in the first 48 bytes of the message
extern byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets
 *//*------------------- Kostal read------------------------------*/


int kostalread();
void lowPin3();
void highPin3();
char* kostalState(int Adress, long val);
void sqlinsert();
void setNtpTime();
void releaseNTP();
unsigned long sendNTPpacket(const char *address);
unsigned long parseNtpPacket();
String getLocaltime();
void printWifiStatus();
#endif