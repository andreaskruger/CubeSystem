#include <Arduino.h>
#include <rawIMU.h>
#include <PID.h>
#include <ESP32Servo.h>
#include <ESC_control.h>

const int IMU_adr_1 = 0x68;

int pitch = 0;
int roll = 0;
int yaw = 0;

void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  //init_ESC();
  init_ESC();
  delay(3000);
  IMU_init(IMU_adr_1);
  calibrateIMU_init();
}

void loop(){
  getReadings();
  pitch = getPitch();
  roll = getRoll();
  yaw = getYaw();

}