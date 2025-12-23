//********************** Projekt-Includes ******************************

/**
 * Main loop function that handles Modbus TCP client connections, data reading, and web server responses.
 * 
 * The function performs the following tasks:
 * 1. Reads data from the client and writes it to the Serial.
 * 2. Manages the connection to the Modbus TCP server and reads data from it.
 * 3. Processes the data read from the Modbus TCP server and updates the global array.
 * 4. Manages the connection to the Modbus KEBA TCP server and reads data from it.
 * 5. Processes the data read from the Modbus KEBA TCP server and updates the global array.
 * 6. Handles incoming HTTP requests from the web client and sends an HTML response.
 * 7. Manages the connection to the MySQL database and inserts data into it.
 * 
 * The function uses the following global variables:
 * - client: WiFi client for Modbus TCP connection.
 * - modbusTCPClient: Modbus TCP client instance.
 * - Modbusserver: IP address of the Modbus server.
 * - globalArray: Array of structures holding Modbus data.
 * - modbusTCPClientKEBA: Modbus TCP client instance for KEBA.
 * - ModbusserverKEBA: IP address of the KEBA Modbus server.
 * - globalArrayKEBA: Array of structures holding KEBA Modbus data.
 * - server: WiFi server instance for handling HTTP requests.
 * - conn: MySQL connection instance.
 * - server_addr: IP address of the MySQL server.
 * - user: MySQL username.
 * - password: MySQL password.
 * - INSERTSQL: SQL query string for inserting data.
 * - INSERTSQLKEBA: SQL query string for inserting KEBA data.
 * - countSQL: Counter for SQL insert operations.
 * - num_fails: Counter for failed MySQL connection attempts.
 * - MAX_FAILED_CONNECTS: Maximum number of allowed failed MySQL connection attempts.
 * - charArray: Array for storing bytes read from Modbus.
 * - floatValue: Float value converted from charArray.
 * - val: Integer value converted from charArray.
 * - val32: 32-bit integer value converted from charArray.
 * - count: Number of bytes available to read from Modbus.
 * - value: Value read from Modbus.
 * - value2: Second value read from Modbus (if available).
 * 
 * The function also includes several helper functions:
 * - kostalState: Function to get the state description based on address and value.
 * - kostalread: Function to read data from the Kostal device.
 * - kebaread: Function to read data from the KEBA device.
 * - sqlinsert: Function to insert data into the MySQL database.
 * - sqlinsertKeba: Function to insert KEBA data into the MySQL database.
 * - lowPin3: Function to perform a low-level reset.
 */
#define MAIN
#include "kostal.h"

/* Dies ist das MAIN */

WiFiClient client;
WiFiClient client1;
WiFiClient client2;
WiFiClient client3;
WiFiServer server(80);
long count, value, value2, val;
int32_t val32;
float floatValue;
char charArray[4];
char ssid[] = SECRET_SSID; // your network SSID (name)
char pass[] = SECRET_PASS; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;
int status = WL_IDLE_STATUS;
char wserver[] = "example.com"; // host name for example.com (using DNS)
MySQL_Connection conn((Client *)&client1);
ModbusTCPClient modbusTCPClient(client);
ModbusTCPClient modbusTCPClientKEBA(client2);
IPAddress ModbusserverKEBA(192, 168, 0, 85); // update with the IP Address of your Modbus server
IPAddress Modbusserver(192, 168, 0, 87); // update with the IP Address of your Modbus server
IPAddress server_addr(192, 168, 0, 10);   // IP of the MySQL *server* here
char user[] = SECRET_MYSQLUSER;          // MySQL user login username
char password[] = SECRET_MYSQLPWD;       // MySQL user login password
// char INSERTSQL[500];
constexpr auto timeServer{"pool.ntp.org"};
const int NTP_PACKET_SIZE = 48; // NTP timestamp is in the first 48 bytes of the message
int num_fails;

void setup()
{
  // Ini
  countSQL = 1;
  highPin3();
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  //while (!Serial)
 // {
 //   ; // wait for serial port to connect. Needed for native USB port only
 // }
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 3 seconds for connection:
    setNtpTime();
    releaseNTP();
    server.begin(); // Webserver
    delay(3000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  // Webserverconnection
  Serial.println("\nStarting connection to wserver...");
  // if you get a connection, report back via serial:
  if (client.connect(wserver, 80))
  {
    Serial.println("connected to wserver");
    // Make a HTTP request:
    client.println("GET /index.html HTTP/1.1");
    client.print("Host: ");
    client.println(wserver);
    client.println("Connection: close");
    client.println();
  }
  else
    Serial.println("NOT connected to wserver");
  //  Check server connection
  // Mysql
  Serial.println("Connecting to mysql...");
  if (conn.connect(server_addr, 3306, user, password))
  {
    delay(1000);
    // You would add your code here to run a query once on startup.
  }
  else
    Serial.println("Connection failed to mysql.");
}

void loop()
{
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }
  // Modbus connecton
  if (!modbusTCPClient.connected())
  {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    if (!modbusTCPClient.begin(Modbusserver, 1502))
    {
      Serial.println("Modbus TCP Client failed to connect!");
    }
    else
    {
      Serial.println("Modbus TCP Client connected");
    }
  }
  else
  {
    // client connected
    // write the value of 0x01, to the coil at address 0x00
    for (int i = 0; i < 106; ++i)
    {
      long read = modbusTCPClient.requestFrom(71, HOLDING_REGISTERS, globalArray[i].Adresse, globalArray[i].N1);
      if (read == -1)
      {
        Serial.print("Failed to requestFrom! ");
        Serial.println(modbusTCPClient.lastError());
      }
      else
      {
        count = modbusTCPClient.available();
        value = modbusTCPClient.read();
        if (count > 1)
          value2 = modbusTCPClient.read();
        // char Array mit Werten aus dem Modbus für float-Werte
        charArray[1] = (value >> 8) & 0xFF; // Das höchstwertige Byte
        charArray[0] = (value >> 0) & 0xFF;
        charArray[3] = (value2 >> 8) & 0xFF;
        charArray[2] = value2 & 0xFF; // Das niederwertige Byte
        //--char-Array in float konvertieren
        if (globalArray[i].Format == 64)
        {
          memcpy(&floatValue, &charArray, sizeof(charArray)); // copy 4 bytes in buf into data variable);
          globalArray[i].fval = floatValue;
          snprintf(globalArray[i].sVal, sizeof(globalArray[i].sVal), "%f", floatValue);
        }
        else if (globalArray[i].Format == 16 && count == 1)
        {
          globalArray[i].ival = value;
          snprintf(globalArray[i].sVal, sizeof(globalArray[i].sVal), "%i", value);
        }
        else if (globalArray[i].Format == 16 && count == 2)
        {
          charArray[1] = (value >> 8) & 0xFF; // Das höchstwertige Byte
          charArray[0] = (value >> 0) & 0xFF;
          charArray[3] = (value2 >> 8) & 0xFF;
          charArray[2] = value2 & 0xFF;                // Das niederwertige Byte
          memcpy(&val, &charArray, sizeof(charArray)); // copy 4 bytes in buf into data variable);
          globalArray[i].ival = val;
        }
        if (globalArray[i].Adresse == 56 || globalArray[i].Adresse == 202 || globalArray[i].Adresse == 104)
        {
          // Serial.print("Adresse == 56");
          // Serial.println(val);
          strcpy(globalArray[i].State, kostalState(56, val));
          // Serial.println(globalArray[i].State);
        }
      }
    }
    //int ret = kostalread();
    // Serial.println(localtime);
  }

    // Modbus connecton
  
  if (!modbusTCPClientKEBA.connected())
  {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus KEBA TCP server");
    if (!modbusTCPClientKEBA.begin(ModbusserverKEBA, 502))
    {
      Serial.println("Modbus TCP Client KEBA failed to connect!");
    }
    else
    {
      Serial.println("Modbus TCP Client KEBA connected");
    }
  }
  else
  {
   for (int k = 0; k < 21; ++k)
    {
 
     long read = modbusTCPClientKEBA.requestFrom(255, HOLDING_REGISTERS, globalArrayKEBA[k].Adresse, globalArrayKEBA[k].N1);
      if (read == -1)
      {
        Serial.print("Failed to requestFrom! ");
        Serial.println(modbusTCPClientKEBA.lastError());
      }
      else
      {
        count = modbusTCPClientKEBA.available();
        value = modbusTCPClientKEBA.read();
        //Serial.print("value1 = modbusTCPClientKEBA.read(); ");
        //Serial.println(value);

        if (count > 1)
        {
        value2 = modbusTCPClientKEBA.read();
        //Serial.print("count ");
        //Serial.println(count);
        //Serial.print("value2 = modbusTCPClientKEBA.read(); ");
        
        //Serial.println(value2);
        charArray[3] = (value >> 8) & 0xFF; // Das höchstwertige Byte
        charArray[2] = (value >> 0) & 0xFF;
        charArray[1] = (value2 >> 8) & 0xFF;
        charArray[0] = value2 & 0xFF; // Das niederwertige Byte
        memcpy(&val32, &charArray, sizeof(charArray)); // copy 4 bytes in buf into data variable);
        globalArrayKEBA[k].ival = val32;
        globalArrayKEBA[k].fval = (float)val32;
        Serial.println("val FLoat");
        Serial.println(globalArrayKEBA[k].fval);
        /*Serial.println("val ");
        Serial.println((u_int8_t)charArray[0]);
        Serial.println((u_int8_t)charArray[1]);
        Serial.println((u_int8_t)charArray[2]);
        Serial.println((u_int8_t)charArray[3]);
        Serial.println(val32);*/

        switch (k) {
          case 3:
          case 4:
          case 5:
          case 9:
          case 15:
         // case 16:
            snprintf(globalArrayKEBA[k].sVal, sizeof(globalArrayKEBA[k].sVal), "%f",globalArrayKEBA[k].fval/1000.0);
            break;
         // case 10:
         // snprintf(globalArrayKEBA[k].sVal, sizeof(globalArrayKEBA[k].sVal), "%f",globalArrayKEBA[k].fval/10.0);
         //   break;
          case 14:
          case 18:
            snprintf(globalArrayKEBA[k].sVal, sizeof(globalArrayKEBA[k].sVal), "%f",globalArrayKEBA[k].fval/10.0);
            Serial.println("case 18");
            Serial.println(globalArrayKEBA[k].sVal);
          break;
          default:
            snprintf(globalArrayKEBA[k].sVal, sizeof(globalArrayKEBA[k].sVal), "%i", val32);
            break;
        }
        
        }

      }
    }
    //int ret = kebaread();
  }

  //-Webserver
  WiFiClient wclient = server.available();
  if (wclient)
  {
    Serial.println("new wclient");
    // an http request ends with a blank line
    bool currentLineIsBlank = true;
    while (wclient.connected())
    {
      if (wclient.available())
      {
        char c = wclient.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          wclient.println("HTTP/1.1 200 OK");
          wclient.println("Content-Type: text/html");
          wclient.println("Connection: close"); // the connection will be closed after completion of the response
          wclient.println("Refresh: 10");       // refresh the page automatically every 5 sec
          wclient.println();
          wclient.println("<!DOCTYPE HTML>");
          wclient.println("<html>");
          wclient.println("<style>tbody tr:nth-child(even) { background-color: #e4ebf2; color: #000; }th, caption {background-color: #f1f3f4;font-weight: 700;}}</style>");
          wclient.print("<table>");
          wclient.print("<tr><th>Description</th><th>Value</th><th>Unit</th></tr>");
          // output the value of each analog input pin
          for (int k = 0; k < 106; k++)
          {
            if (globalArray[k].enabel == 1)
            {
              wclient.print("<tr>");
              wclient.print("<td>");
              wclient.print(globalArray[k].Description);
              wclient.print("</td>");
              wclient.print("<td>");
              if (globalArray[k].Format == 64)
              {
                wclient.print(globalArray[k].fval);
              }
              else
              {
                if (globalArray[k].Adresse == 56 || globalArray[k].Adresse == 202 || globalArray[k].Adresse == 104)
                {
                  wclient.print(globalArray[k].State);
                  // Serial.print("-----------------------------------------------");
                  Serial.println(globalArray[k].State);
                }
                else
                  wclient.print(globalArray[k].ival);
              }
              wclient.print("</td>");
              wclient.print("<td>");
              wclient.print(globalArray[k].Unit);
              wclient.print("</td>");
              // wclient.println("<br />");
              wclient.print("</tr>");
            }
          }
          wclient.print("</table>");
          wclient.println("</html>");
          break;
        }
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(50);
    // close the connection:
    wclient.stop();
    Serial.println("wclient disconnected");
  }
  else
    Serial.println("NO Webclient");
  // Initiate the query class instance

  // Execute the query
  bool status;
  status = conn.connected();
  if (status == true)
  {
    while (countSQL > 60)
    {
      num_fails = 0;
      Serial.println("MySQL_Cursor connected: ");
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      sqlinsert();
      cur_mem->execute(INSERTSQL);
      delete cur_mem;
     // MySQL_Cursor *cur_memKeba = new MySQL_Cursor(&conn);
     // sqlinsertKeba();
     // cur_memKeba->execute(INSERTSQLKEBA);
     // delete cur_memKeba;
      countSQL=0;
    }
    countSQL++;
  }
  else
  {
    // Try to reconnect
    conn.close();
    delay(1000);
    if (conn.connect(server_addr, 3306, user, password))
    {
      Serial.println("Connection reconecting to mysql.");
    }
    num_fails++;
    Serial.print("num_fails");
    Serial.println(num_fails);
    // restart
    if (num_fails == MAX_FAILED_CONNECTS)
    {
      Serial.println("Ok, that's it. I'm outta here. Rebooting...");
      delay(2000);
      lowPin3();
    }
  }

  delay(1000);
}
