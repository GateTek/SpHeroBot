#ifndef Robot_h
#define Robot_h

#include <Arduino.h>
#include <math.h>
#include "definitions.h"

#include "I2C.h"
#include "Debug.h"
#include "Moviment.h"

class Robot {
  public:
    void begin();
    bool check();
    bool checkBattery();
    void go();
    void rotate(bool dir);

    void delay(unsigned int t);
  private:
    float getBattery();
    Moviment mov = Moviment(SPEED);
};

#endif
