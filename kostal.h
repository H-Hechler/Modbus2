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
#include <Ethernet.h>
#define INFLUXDB_URL "http://192.168.0.9:49154"
#define INFLUXDB_TOKEN "3dqcPFWLYNoadH0O6R4TbqpOJH7mWthRUw7KrVjEXTb1pU73pv29GqKQMn0UU4BKEAbwlsNcx9eM1emWolkL1w=="
#define INFLUXDB_ORG "4bc23cd2135bf2f6"
#define INFLUXDB_BUCKET "kostal"
//#include <InfluxDbClient.h>
//#include <InfluxDbCloud.h>
// Time zone info
#define TZ_INFO "UTC1"
// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
//InfluxDBClient influxclient(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);


extern WiFiClient client;
extern long count, value, value2, val;
extern float floatValue;
extern char charArray[4];
extern char ssid[];  // your network SSID (name)
extern char pass[];  // your network password (use for WPA, or use as key for WEP)
extern int keyIndex;
extern int status;
extern char wserver[];  // host name for example.com (using DNS)
/*------------------- Kostal read------------------------------*/


int kostalread();
char* kostalState(int Adress, long val);
#endif