#ifndef Moviment_h
#define Moviment_h

#include <Arduino.h>
#include "definitions.h"
#include "Motor.h"
#include "IMU.h"
#include "Debug.h"

class Moviment {
  public:
    Moviment (uint16_t speed);
    void begin();
    bool check();
    void go();
    void go (bool invert);
    void rotate();
    void rotation(bool invert);
    int rotate (bool invert);
    int rotate (bool invert, float angle);
    void stop();
    void setSpeed(uint16_t speed);
    void setK(int rightK, int leftK);
    void idle();
  private:
    uint16_t bound (uint32_t n, uint16_t max);
    float endAngle(float angle, bool invert, float end);
    void rotationSpeed(bool direction , float endRotation);
    void rotationSpeed(uint16_t speed, bool invert);
    Motor motor1 = Motor(M1_IN1, M1_IN2);
    Motor motor2 = Motor(M2_IN1, M2_IN2);
    Motor motor3 = Motor(M3_IN1, M3_IN2);
    IMU orientation;
    uint16_t speed;
    int kR;
    int kL;
    float direzione;
    float fill;
};

#endif
