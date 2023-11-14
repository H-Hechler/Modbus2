#include <SPI.h>
#include <WiFi.h>
#include <stdint.h>
// #include <WiFi101.h> // for MKR1000

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include "arduino_secrets.h" 


char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0; 
int status = WL_IDLE_STATUS;  
char server[] = "example.com";       // host name for example.com (using DNS)    
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
    long read = modbusTCPClient.requestFrom(71,HOLDING_REGISTERS,0x98,2 );
    unsigned int hexValue = 0x47F12000;
    if (read == -1) {
      Serial.print("Failed to requestFrom! ");
      Serial.println(modbusTCPClient.lastError());
      //Serial.println(read);
    }
    else{
      long count = modbusTCPClient.available();
         Serial.print("available: ");
      Serial.println(count);
      long value = modbusTCPClient.read();
      long value2 = modbusTCPClient.read();
      // Verwenden Sie die String-Klasse, um die 'long'-Zahl in eine Zeichenkette zu konvertieren.
 // String strValue = String(value);
// Ein char-Array zum Speichern der einzelnen Bytes des long-Werts
  char charArray[4];

  // Teilen Sie den long-Wert in seine Bytes auf
  charArray[1] = (value >> 8) & 0xFF;  // Das höchstwertige Byte
  charArray[0] = (value >> 0) & 0xFF;
  charArray[3] = (value2 >> 8) & 0xFF;
  charArray[2] = value2 & 0xFF;  // Das niederwertige Byte
  // Hier können Sie 'charArray' verwenden, um die Bytes zu übertragen oder anzuzeigen.
  //byte byteArray[4];

//byteArray[3]= (value >> (3 * 8)) & 0xFF;
//byteArray[2]= (value >> (2 * 8)) & 0xFF;
//byteArray[1]= (value >> (1 * 8)) & 0xFF;
//byteArray[0]= (value >> (0 * 8)) & 0xFF;




//long swappedValue = ((byteArray[3]) << 24) |
//                   ((byteArray[2]) << 16) |
//                   ((byteArray[1]) << 8) |
//                   (byteArray[0]);
//  for (int i = 0; i < 4; i++) {
//    Serial.print(charArray[i], HEX);  // HEX-Ausgabe für Debugging
//    Serial.print(" ");
//  }
 // Serial.println("");
 //for (int i = 0; i < 4; i++) {
//    Serial.print(byteArray[i]);  // HEX-Ausgabe für Debugging
//    Serial.print(" ");
//  }

float floatValue;
//long longValue;
//memcpy(&floatValue, &hexValue, sizeof(floatValue));

 memcpy(&floatValue, &charArray, sizeof(charArray)); //copy 4 bytes in buf into data variable);

//   Serial.println("");
   Serial.print("value: ");
   Serial.println(value);
   Serial.print("valueH: ");
   Serial.println(value,HEX);
   Serial.print("valueH: ");
   Serial.println(value2,HEX);
  Serial.println( charArray[0],HEX);
  Serial.println( charArray[1],HEX);
  Serial.println( charArray[2],HEX);
  Serial.println( charArray[3],HEX);
//   Serial.print("swappedValue: ");
//   Serial.println(swappedValue);
   Serial.print("floatValue: ");
   Serial.println(floatValue);
   delay(1000);
    }

    // wait for 1 second
    /*delay(1000);
    read = modbusTCPClient.holdingRegisterRead(71,0x90 );
    if (read == -1) {
      Serial.print("Failed to requestFrom! ");
      Serial.println(modbusTCPClient.lastError());
      Serial.println(read);
    }
    else{
   
      Serial.print("Worktime");
      Serial.println(read);
    }
    delay(3000);*/

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
