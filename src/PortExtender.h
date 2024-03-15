#ifndef PortExtender_H_
#define PortExtender_H_

#include <Arduino.h>

#define PCF8574A_ADRESS 0x3F

// LED
#define OFF 0
#define GREEN 1
#define RED 2
#define BLUE 4

//buttons
#define buttonA 0
#define buttonB 1
#define buttonC 2
#define buttonD 3




class portExp {
public:
  portExp(uint8_t SlaveAddress=PCF8574A_ADRESS);
  void init();
  void LED(uint8_t statusLED);
  void buzzer(uint8_t buzzerStatus);
  void buzzerBeep();
  
  uint8_t allButton();
  uint8_t readButton(uint8_t buttonNr);
  void waitButton_Press(uint8_t buttonNr);
  void waitButton_PressAndRelease(uint8_t buttonNr);


private:
  uint8_t readGPIO(void);
  void writeGPIO(uint8_t dataGPIO);
  uint8_t _SlaveAddress;
};



#endif /* PortExtender_H_ */
