#include <Wire.h>
#include "PortExtender.h"

portExp uIO(PCF8574A_ADRESS);     //create instance at base address


void setup() {
  Serial.begin(9600);
  Wire.begin();
  uIO.init();     // init Interface
}

void loop() {

  uIO.LED(RED);
  delay(1000);
  uIO.LED(BLUE);
  delay(1000);
  uIO.LED(GREEN);
  delay(1000);
  uIO.LED(OFF);
  delay(1000);

  uIO.LED(RED);
  delay(100);

  uIO.waitButton_PressAndRelease(buttonA);

  Serial.println("Button A pressed and released");
  uIO.LED(GREEN);
  delay(1000);
}

