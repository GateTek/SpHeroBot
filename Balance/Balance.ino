#include "definitions.h"
#include "Debug.h"
#include "Balance.h"

SerialDebug Debug;
SoftWire I2C_1(PB6, PB7, SOFT_STANDARD);
TwoWire I2C_2(2);

Robot robot;

void scan() {
  byte error, address;
  int nDevices;
  Debug.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++) {
    I2C_1.beginTransmission(address);
    error = I2C_1.endTransmission();
    if (error == 0) {
      Debug.print("I2C device found at address 0x");
      if (address < 16) Debug.print("0");
      Debug.println(String(address, HEX));
      nDevices++;
    }
    else if (error == 4) {
      Debug.print("Unknown error at address 0x");
      if (address < 16) Debug.print("0");
      Debug.println(String(address, HEX));
    }    
  }
  if (nDevices == 0) Debug.println("No I2C devices found");
  else Debug.println("done");
}

void setup() {
  //I/O initialization
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //Hardware initialization
  Serial.begin(115200);
  I2C_1.begin();
  I2C_2.begin();
  Debug.println("Hardware initialization done.", LVL_INFO);

  //Check that everything is working
  bool ok = robot.check() && robot.checkBattery();
  Debug.println("Check done.", LVL_INFO);
  if(!ok) Debug.println("Something is not working correctly. Proceed at your own risk!",LVL_WARN);

  digitalWrite(LED_BUILTIN, ok);
  
  //Software initialization
  robot.begin();
  Debug.setLevel(LVL_DEBUG);
  Debug.println("Software initialization done.", LVL_INFO);
  
  Debug.println("STARTING!", LVL_INFO);  
}

void loop() {
  //TODO
}
