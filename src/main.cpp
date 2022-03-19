#include <Arduino.h>
#include <Angle_IMU.h>
#include <ESC_Control.h>


void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
}


void loop() {
  ESC_speed(1, readIMU());
}