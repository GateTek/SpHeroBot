#include "Balance.h";

/**
 * Begins all sensors.
 */
void Robot::begin() {  
  mov.begin();
}

/**
 * Check if every sensor is connected and working.
 * @return TRUE if everything is ok
 */
bool Robot::check() {
  return mov.check();
}

/**
 * Check if the battery is charged enough for the robot to work
 * @return TRUE if the battery voltage is higher than 11 volts
 */
bool Robot::checkBattery() {
  float battery = getBattery();
  bool ok = getBattery()>11.f;
  Debug.println(String("Battery voltage: ")+battery+"v.",LVL_INFO);
  if(!ok) Debug.println("Critical battery level!", LVL_WARN);
  return ok;
}

void Robot::go(){
  mov.go();
}

/**
 * Rotates the robot by 90 degrees.
 * @param dir TRUE to turn right, false to turn left
 */
void Robot::rotate(bool dir) {
  mov.rotate(dir);
}
 
/**
 * Reads the battery current voltage.
 * @return The already corrected battery voltage in Volts.
 */
float Robot::getBattery() {
  return ((analogRead(B_PIN) * (3.3f / 4095.0f)) * (B_R1+B_R2))/B_R2;
}


/**
 * Idles for the given time.
 * Instead of doing nothing this function keep updating filters.
 * @param t Time in milliseconds to wait.
 */
void Robot::delay(unsigned int t) {
  unsigned int end = millis() + t;
  while (end > millis()) mov.idle();
}
