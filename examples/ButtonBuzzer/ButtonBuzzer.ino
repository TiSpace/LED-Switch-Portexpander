#include <Wire.h>
#include "PortExtender.h"

portExp uIO(PCF8574A_ADRESS);  //create instance at base address


void setup() {
  Serial.begin(9600);
  Wire.begin();
  uIO.init();  // init Interface
}

void loop() {

 
  if (uIO.readButton(buttonB) ) // read button B
  {
    uIO.LED(BLUE);
    uIO.buzzerBeep();
  } else {
    uIO.LED(GREEN);
  }
}

