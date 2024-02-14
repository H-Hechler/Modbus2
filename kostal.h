/*------------------- Mehrfach Defines verhindern ----------------------------*/
#ifndef KOSTAL_H_
#define KOSTAL_H_

#ifdef MAIN
#define EXTERN
#else
#define EXTERN extern
#endif



#define MAX_STRING_LEN 50
#include <SPI.h>
#include <stdint.h>
#include <WiFi.h>
#include <ArduinoRS485.h>  // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "arduino_secrets.h"
#include "array.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//#include <Ethernet.h>


// Time zone info
#define TZ_INFO "UTC1"
// Declare InfluxDB client instance with preconfigured InfluxCloud certificate



extern WiFiClient client;
extern long count, value, value2, val;
extern float floatValue;
extern char charArray[4];
extern char ssid[];  // your network SSID (name)
extern char pass[];  // your network password (use for WPA, or use as key for WEP)
extern int keyIndex;
extern int status;
extern char wserver[];  // host name for example.com (using DNS)
extern char INSERTSQL[200] ;
/*------------------- Kostal read------------------------------*/


int kostalread();
char* kostalState(int Adress, long val);
void sqlinsert();
#endif