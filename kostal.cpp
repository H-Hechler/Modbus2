#include "kostal.h"

const int ledPin = LED_BUILTIN;
int ledState = LOW;  // ledState used to set the LED

int kostalread() {
  /* for (int i = 0; i < 106; ++i) {
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
  }*/

  pinMode(ledPin, OUTPUT);
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
}
char* kostalState(int Adress, long val) {
  //inverterState
  char* retVal;
  if (Adress = 15) {
    switch (val) {

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
  else if (Adress = 104) {
    switch (val) {
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
   else if (Adress = 202) {
    switch (val) {
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
  //State of energy manager3
}

void sqlinsert(){
  strcpy(INSERTSQL, "INSERT INTO kostal.test (message) VALUES ('Hello, Arduino!')");
  

}