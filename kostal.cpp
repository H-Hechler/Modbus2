#include "kostal.h"

const int ledPin = LED_BUILTIN;
//const int ledPinR = D2;
int ledState = LOW; // ledState used to set the LED
int ledPinR = D2;
int pinLow = LOW; // ledState used to set the LED
int pinHigh = HIGH; // ledState used to set the LED
int kostalread()
{
   for (int i = 0; i < 106; ++i) {
    Serial.print(globalArray[i].Description);
    if (globalArray[i].Format = 64)
      Serial.print(globalArray[i].fval);
    else
      Serial.print(globalArray[i].ival);
    Serial.println(globalArray[i].Unit);
    // Serial.println(val);
    // Serial.print(value);

    // Serial.print("+++");
    // Serial.println(value2);
    // Serial.print(charArray[1],HEX);
    // Serial.print(charArray[0],HEX);
    // Serial.print(charArray[3],HEX);
    // Serial.print(charArray[2],HEX);
  }


  pinMode(ledPin, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  
  if (ledState == LOW)
  {
    ledState = HIGH;
  }
  else
  {
    ledState = LOW;
  }

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
  

  auto now = std::chrono::system_clock::now();

  // Zeitpunkt in lokale Zeit umwandeln
  std::time_t current_time = std::chrono::system_clock::to_time_t(now);

  // Lokale Zeit in eine Zeitstruktur konvertieren
  std::tm local_tm = *std::localtime(&current_time);
  Serial.println(std::asctime(&local_tm));
}
char *kostalState(int Adress, long val)
{
  // inverterState
  char *retVal;
  if (Adress = 15)
  {
    switch (val)
    {

    case 0:
    {
      retVal = "Off";
      break;
    }
    case 1:
    {
      retVal = "Init";
      break;
    }
    case 2:
    {
      retVal = "IsoMeas";
      break;
    }
    case 3:
    {
      retVal = "GridCheck";
      break;
    }
    case 4:
    {
      retVal = "StartUp";
      break;
    }
    case 5:
    {
      retVal = "-";
      break;
    }
    case 6:
    {
      retVal = "FeedIn";
      break;
    }
    case 7:
    {
      retVal = "Throttled";
      break;
    }
    case 8:
    {
      retVal = "ExtSwitchOff";
      break;
    }
    case 9:
    {
      retVal = "Update";
      break;
    }
    case 10:
    {
      retVal = "Standby";
      break;
    }
    case 11:
    {
      retVal = "GridSync";
      break;
    }
    case 12:
    {
      retVal = "GridPreCheck ";
      break;
    }
    case 13:
    {
      retVal = "GridSwitchOff";
      break;
    }
    case 14:
    {
      retVal = "Overheating";
      break;
    }
    case 15:
    {
      retVal = "Shutdown";
      break;
    }
    case 16:
    {
      retVal = "ImproperDcVoltage";
      break;
    }
    case 17:
    {
      retVal = "ESB";
      break;
    }
    case 18:
    {
      retVal = "Unknown";
      break;
    }

    default:

      break;
    }
  }

  // 0x00 Idle
  // 0x01 n/a
  // 0x02 Emergency Battery Charge
  // 0x04 n/a
  // 0x08 Winter Mode Step 1
  // 0x10 Winter Mode Step
  else if (Adress = 104)
  {
    switch (val)
    {
    case 0:
    {
      retVal = "Idle";
      break;
    }
    case 1:
    {
      retVal = "n/a";
      break;
    }
    case 2:
    {
      retVal = "Emergency Battery Charge";
      break;
    }
    case 4:
    {
      retVal = "n/a";
      break;
    }
    case 8:
    {
      retVal = "Winter Mode Step 1";
      break;
    }
    case 16:
    {
      retVal = "Winter Mode Step 2";
      break;
    }
    case 17:
    {
      retVal = "ESB";
      break;
    }
    case 18:
    {
      retVal = "Unknown";
      break;
    }

    default:

      break;
    }
  }
  // PSSB-fuse-state
  // 0x00 Fuse fail
  // 0x01 Fuse ok
  // 0xFF Unchecked
  else if (Adress = 202)
  {
    switch (val)
    {
    case 0:
    {
      retVal = "Fuse fail";
      break;
    }
    case 1:
    {
      retVal = "Fuse ok";
      break;
    }
    case 255:
    {
      retVal = "Unchecked";
      break;
    }
    default:
      break;
    }
  }

  return retVal;
  // State of energy manager3
}

void sqlinsert()
{
  strcpy(INSERTSQL, "INSERT INTO Kostal.kostal (Total_DC_power,Home_own_consumption_from_grid,Total_home_consumption_Grid,\
  Total_home_consumption_PV,Home_own_consumption_from_PV,Total_home_consumption) VALUES(");
  strcat(INSERTSQL, globalArray[7].sVal);
  strcat(INSERTSQL, ",");
  strcat(INSERTSQL, globalArray[10].sVal);
  strcat(INSERTSQL, ",");
  strcat(INSERTSQL, globalArray[12].sVal);
  strcat(INSERTSQL, ",");
  strcat(INSERTSQL, globalArray[13].sVal);
  strcat(INSERTSQL, ",");
  strcat(INSERTSQL, globalArray[14].sVal);
  strcat(INSERTSQL, ",");
  strcat(INSERTSQL, globalArray[15].sVal);
  strcat(INSERTSQL, ")");
  Serial.println(INSERTSQL);
}
void sqlinsertKeba()
{
  strcpy(INSERTSQLKEBA, "INSERT INTO Kostal.Keba (Charging_state,Cable_state,Error_code,\
  Charging_current_phase_1,Charging_current_phase_2,Charging_current_phase_3,\
  Serial_number,Product_type_and_features,Firmware_version,Active_power,\
  Total_energy,Voltage_phase_1,Voltage_phase_2,Voltage_phase_3,\
  Power_factor,Max_charging_current,Max_supported_current,RFID_card,\
  Charged_energy,Phase_switching_source,Phase_switching_state) VALUES(");
  strcat(INSERTSQLKEBA, globalArrayKEBA[0].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[1].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[2].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[3].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[4].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[5].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[6].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[7].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[8].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[9].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[10].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[11].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[12].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[13].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[14].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[15].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[16].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[17].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[18].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[19].sVal);
  strcat(INSERTSQLKEBA, ",");
  strcat(INSERTSQLKEBA, globalArrayKEBA[20].sVal);
  strcat(INSERTSQLKEBA, ")");
  Serial.println(INSERTSQLKEBA);
}

  void lowPin3(){
    digitalWrite(ledPinR, pinLow);
  }
   void highPin3(){
    digitalWrite(ledPinR, pinHigh);
  }
int kebaread()
{
   for (int i = 0; i < 20; ++i) {
    Serial.print(globalArrayKEBA[i].Description);
    Serial.print(" : ");
    Serial.print(globalArrayKEBA[i].ival);
    Serial.println(globalArrayKEBA[i].Unit);
    // Serial.println(val);
    // Serial.print(value);

    // Serial.print("+++");
    // Serial.println(value2);
    // Serial.print(charArray[1],HEX);
    // Serial.print(charArray[0],HEX);
    // Serial.print(charArray[3],HEX);
    // Serial.print(charArray[2],HEX);
  }
}
  //Wifi Status
  //-------
void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}