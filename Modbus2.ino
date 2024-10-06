//********************** Projekt-Includes ******************************
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
IPAddress server_addr(192, 168, 0, 8);   // IP of the MySQL *server* here
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
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
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
  if (conn.connect(server_addr, 49155, user, password))
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
        else if (globalArray[i].Format == 16 & count == 1)
        {
          globalArray[i].ival = value;
          snprintf(globalArray[i].sVal, sizeof(globalArray[i].sVal), "%i", value);
        }
        else if (globalArray[i].Format == 16 & count == 2)
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
    int ret = kostalread();
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

     long read = modbusTCPClientKEBA.requestFrom(255, HOLDING_REGISTERS, 1014,2);
      if (read == -1)
      {
        Serial.print("Failed to requestFrom! ");
        Serial.println(modbusTCPClientKEBA.lastError());
      }
      else
      {
        count = modbusTCPClientKEBA.available();
        value = modbusTCPClientKEBA.read();
        Serial.print("value1 = modbusTCPClientKEBA.read(); ");
        Serial.println(value);

        if (count > 1)
        {
          value2 = modbusTCPClientKEBA.read();
          Serial.print("count ");
          Serial.println(count);
        Serial.print("value2 = modbusTCPClientKEBA.read(); ");
        
        Serial.println(value2);
        charArray[3] = (value >> 8) & 0xFF; // Das höchstwertige Byte
        charArray[2] = (value >> 0) & 0xFF;
        charArray[1] = (value2 >> 8) & 0xFF;
        charArray[0] = value2 & 0xFF; // Das niederwertige Byte
          memcpy(&val32, &charArray, sizeof(charArray)); // copy 4 bytes in buf into data variable);
          Serial.println("val ");
          Serial.println((u_int8_t)charArray[0]);
          Serial.println((u_int8_t)charArray[1]);
          Serial.println((u_int8_t)charArray[2]);
          Serial.println((u_int8_t)charArray[3]);
          Serial.println(val32);
        }

      }
    
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
  if (status == TRUE)
  {
    while (countSQL > 60)
    {
      num_fails = 0;
      Serial.println("MySQL_Cursor connected: ");
      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
      sqlinsert();
      cur_mem->execute(INSERTSQL);
      delete cur_mem;
      countSQL=0;
    }
    countSQL= ++ countSQL;
  }
  else
  {
    // Try to reconnect
    conn.close();
    delay(1000);
    if (conn.connect(server_addr, 49155, user, password))
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
