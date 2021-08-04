#include <Arduino.h>

int FAN;
int LED;

String KEY;
String VAL;
int ch;

char PAYLOAD[128] = "{\"FAN\": 96, \"LED\": 69}";

struct PAYMASTER {
  uint8_t FAN;
  uint8_t LED;
} Controller;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void debug_serialization() {
  Serial.print("FAN: ");
  Serial.print(Controller.FAN);
  Serial.print(" LED: ");
  Serial.println(Controller.LED);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 99; i++) {
    ch = PAYLOAD[i];
    //Serial.print(char(ch));
    delay(99);
    if ((ch == '{') || (ch == 32) || (ch == 34) || (ch == 39)) { // Discaed: curly brace, whitespace, quotation marks
      Serial.print(".");
    } else if (ch == ':') {
      Serial.print("Got key: ");
      Serial.println(KEY);
    } else if ((ch == 44) || (ch == '}')) { // comma
      Serial.print("Got value: ");
      Serial.println(VAL);
      if (KEY == "FAN") {
        Controller.FAN = VAL.toInt();
      } else if (KEY == "LED") {
        Controller.LED = VAL.toInt();
      }
      KEY = "";
      VAL = "";
    } else if ((ch >= '0') && (ch <= '9')) {
      /* code */
      VAL += char(ch);
    } else if (((ch >= 65) && (ch <= 90)) || ((ch > 97) && (ch < 122))) { // A-Z or a-z
      KEY += char(ch);
    }
  
  }  
  debug_serialization();
  Serial.println("Done!");
}