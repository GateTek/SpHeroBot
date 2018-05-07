#include "Moviment.h"

/**
 * Sets the movement speed and default parameters.
 */
Moviment::Moviment (uint16_t speed) {
  this->speed = speed;
  fill = 0;
}

/**
 * Makes the robot ready to move.
 */
void Moviment::begin() {
  motor1.begin();
  motor2.begin();
  motor3.begin();
  orientation.begin();
  delay(100);
  orientation.calibrate();
  delay(100);
  orientation.start(100);
}

/**
 * Checks if the sensors are ready to be read from.
 * @return
 */
bool Moviment::check() {
  return orientation.check();
}
 
/**
 * Moves the robot forward.
 */
void Moviment::go() {
  go(false);
}

/**
 * Moves the robot forward or backward.
 * @param invert Forward if TRUE, backward if FALSE.
 */
void Moviment::go(bool invert) {
  //TODO
}

/**
 * Rotates the robot by 90 degrees to the right.
 */
void Moviment::rotate() {
  rotate(false);
}

/**
 * Makes the robot rotate until stop is called.
 * @param invert Rotates right if FALSE, left if TRUE.
 */
void Moviment::rotation(bool invert){
  //TODO
}

/**
 * Rotates the robot by 90 degrees.
 * @param invert Rotates right if FALSE, left if TRUE.
 */
int Moviment::rotate(bool invert) {
  return rotate(invert, 90);
}

/**
 * Rotates the robot by a given number degrees.
 * @param invert Rotates right if FALSE, left if TRUE.
 * @param angle The angle by.
 */
int Moviment::rotate(bool invert , float angle) {
  Debug.println("rotate start");
  orientation.start(100);
  float end = endAngle(orientation.yaw(), invert , angle);
  end-=fill;
  if (!invert) {
    if (end > (360 - angle)) {
      rotationSpeed(ROTATION_SPEED, invert);
      while (orientation.yaw() > 5) {};
      delay(100);
    }
    while (orientation.yaw() > end) {
      rotationSpeed(ROTATION_SPEED, invert);
    }
    stop();
    while (orientation.yaw() <= (end)) {
      rotationSpeed(!invert, end);
    }
  }
  else {
    if (end < angle) {
      rotationSpeed(ROTATION_SPEED, invert);
      while (orientation.yaw() < 355) {};
      delay(100);
    }
    while (orientation.yaw() < end) {
      rotationSpeed(ROTATION_SPEED, invert);
    }
    stop();
    while (orientation.yaw() >= (end)) {
      rotationSpeed(!invert, end);
    }
  }
  stop();
  setK(0, 0);
  fill=(orientation.yaw()-end);
  Debug.println("rotate end");
  return 0;
}

/**
 * Stops the motor.
 */
void Moviment::stop() {
  motor1.stop();
  motor2.stop();
  motor3.stop();
}

/**
 * Adjust the speed of the motors.
 * @param speed The speed, from 0 to 65535.
 */
void Moviment::setSpeed(uint16_t speed) {
  this->speed = bound((speed) , 65535);
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
}

/**
 * Set the rotation coefficient.
 * @param rightK Right coefficient.
 * @param leftK Left coefficient.
 */
void Moviment::setK(int rightK, int leftK) {
  kR = rightK;
  kL = leftK;
}

/**
 * Calculates the angle in which the robot has to stop.
 * @param angle Actual angle.
 * @param invert Rotates right if FALSE, left if TRUE.
 * @param end The end angle of the rotation.
 * @return The angle to turn of.
 */
float Moviment::endAngle(float angle, bool invert, float end) {
  float ris = angle;
  if (invert) {
    ris += end;
    return (ris > 360) ? ris - 360 : ris;
  }
  else {
    ris -= end;
    return (ris < 0) ? ris + 360 : ris;
  }
}

/**
 * Adjust the rotation speed, based on the distance from the given angle.
 * @param invert Rotates right if FALSE, left if TRUE.
 * @param endRotation The end angle of the rotation.
 */
void Moviment::rotationSpeed(bool invert, float endRotation) {
  direzione = orientation.yaw();
  if (endRotation - direzione > 0) setK(FIRST_K + ((endRotation - direzione) * ROTATION_P), SECOND_K + ((endRotation - direzione) * ROTATION_P));
  else setK(SECOND_K + ((direzione - endRotation) * ROTATION_P), FIRST_K + ((direzione - endRotation) * ROTATION_P));
  //TODO
}

/**
 * Sets the motor rotation speed to the given one.
 * @param speed Speed of the motors, from 0 to 65535.
 * @param invert Rotates right if FALSE, left if TRUE.
 */
void Moviment::rotationSpeed(uint16_t speed, bool invert) {
  //TODO
}

/**
 * Bound n to max.
 * Cap down n to not overflow the max value.
 * @param n The number given.
 * @param max The max value that n should be.
 * @return The capped value.
 */
uint16_t Moviment::bound(uint32_t n, uint16_t max) {
  return (n > max) ? max : n;
}

/**
 * Does idle operation, aka does nothing.
 */
void Moviment::idle() {
  orientation.update();
}
