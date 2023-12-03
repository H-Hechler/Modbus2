//********************** Projekt-Includes ******************************
#define  MAIN
#include "kostal.h"
/* Dies ist das MAIN */
WiFiClient client; 
ModbusTCPClient modbusTCPClient(client);
IPAddress Modbusserver(192, 168, 0, 87); // update with the IP Address of your Modbus server
void setup() {
    //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    // check for the WiFi module:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
   // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    delay(3000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /index.html HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
}
void loop() {
    while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // put your main code here, to run repeatedly:
  if (!modbusTCPClient.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    if (!modbusTCPClient.begin(Modbusserver,1502)) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    } 
  } else {
    // client connected
    // write the value of 0x01, to the coil at address 0x00
    int ret=kostalread();
    for (int i = 0; i < 106; ++i) {
          long read = modbusTCPClient.requestFrom(71,HOLDING_REGISTERS,globalArray[i].Adresse,globalArray[i].N1 );
        if (read == -1) {
          Serial.print("Failed to requestFrom! ");
          Serial.println(modbusTCPClient.lastError());
        //Serial.println(read);
        }
        else{
          count = modbusTCPClient.available();
          value = modbusTCPClient.read();
          if (count >1)
            value2 = modbusTCPClient.read();
          // char Array mit Werten aus dem Modbus für float-Werte
          charArray[1] = (value >> 8) & 0xFF;  // Das höchstwertige Byte
          charArray[0] = (value >> 0) & 0xFF;
          charArray[3] = (value2 >> 8) & 0xFF;
          charArray[2] = value2 & 0xFF;  // Das niederwertige Byte
          //--char-Array in float konvertieren
          
          
          if (globalArray[i].Format == 64) {
            memcpy(&floatValue, &charArray, sizeof(charArray)); //copy 4 bytes in buf into data variable);
            globalArray[i].fval=floatValue;
            Serial.print( globalArray[i].Description);
            Serial.print(globalArray[i].fval=floatValue);
            Serial.println( globalArray[i].Unit);

          }
          else if (globalArray[i].Format == 16 && count ==1) {
            Serial.print( globalArray[i].Description);
            Serial.print(value);
            Serial.println( globalArray[i].Unit);
            globalArray[i].ival=value;
          }
          else if (globalArray[i].Format == 16 && count ==2) {
            charArray[1] = (value >> 8) & 0xFF;  // Das höchstwertige Byte
            charArray[0] = (value >> 0) & 0xFF;
            charArray[3] = (value2 >> 8) & 0xFF;
            charArray[2] = value2 & 0xFF;  // Das niederwertige Byte
            memcpy(&val, &charArray, sizeof(charArray)); //copy 4 bytes in buf into data variable);
            Serial.print( globalArray[i].Description);
            Serial.println(val);
            Serial.print(value);
            
            Serial.print("+++");
            Serial.println(value2);
            Serial.print(charArray[1],HEX);
            Serial.print(charArray[0],HEX);
            Serial.print(charArray[3],HEX);
            Serial.print(charArray[2],HEX);
            Serial.println( globalArray[i].Unit);
          }
          
        }
      
    }

  delay(30000);
  

  }  
}

//-------
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
