#include <Arduino.h>
#include "PortExtender.h"
#include <Wire.h>


portExp::portExp(uint8_t SlaveAddress=PCF8574A_ADRESS) {
  _SlaveAddress = SlaveAddress;
}


void portExp::LED(uint8_t statusLED) {  //Startbedingung ist 0xFF = alles au

  uint8_t readBackValue = this->readGPIO() | 0x0F;  //button and buzzer to HIGH
  readBackValue |= 0x70;                            //clear LED
  if (statusLED != OFF) {
    readBackValue &= ~(statusLED << 4);  //setzt die gewählte LED
  }
  this->writeGPIO(readBackValue);
}

void portExp::buzzer(uint8_t buzzerStatus) {

  uint8_t readBackValue = this->readGPIO();

  if (buzzerStatus == 0) {
    readBackValue |= 0x80;  // set one Bit
  } else {
    readBackValue &= (0xFF - 0x80);  //delete on Bit
  }
  this->writeGPIO(readBackValue);
}

void portExp::buzzerBeep() {
  this->buzzer(1);
  delay(50);
  this->buzzer(0);
}


void portExp::init() {
  this->writeGPIO(0xFF);  ///all off, button ready to receive
  Serial.println("Init erfolgt");
}


uint8_t portExp::allButton() {
  // the pressed button return 0, none pressed 0x0F
  uint8_t readBackValue = this->readGPIO() & 0x0F;

  return readBackValue;  //return reading
}

uint8_t portExp::readButton(uint8_t buttonNr) {  // returns 1 if corresponding button is pressed

  return 1 - ((this->allButton() & (1 << buttonNr)) >> buttonNr);
}


void portExp::waitButton_Press(uint8_t buttonNr)
// waits and return once the button is pressed
{
  while (((this->allButton() & (1 << buttonNr)) >> buttonNr) == 1) {}  //button pressed
}


void portExp::waitButton_PressAndRelease(uint8_t buttonNr)
// waits and return once the button is pressed and released
{
  while (((this->allButton() & (1 << buttonNr)) >> buttonNr) == 1) {}  //button pressed
  while (((this->allButton() & (1 << buttonNr)) >> buttonNr) == 0) {}  //button released
}




uint8_t portExp::readGPIO(void) {
  Wire.requestFrom(_SlaveAddress, 1);   //request one byte
  uint8_t readBackValue = Wire.read();  //re<d itoa
  Wire.endTransmission();

  return readBackValue;
}

void portExp::writeGPIO(uint8_t dataGPIO) {
  Wire.beginTransmission(_SlaveAddress);
  Wire.write(dataGPIO);
  Wire.endTransmission();
}

//}
