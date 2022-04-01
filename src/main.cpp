#include <Arduino.h>
#include <rawIMU.h>
#include <PID.h>
#include <ESP32Servo.h>
#include <ESC_control.h>

const int IMU_adr_1 = 0x68;

#define IMU_pin_1 32
#define IMU_pin_2 33
#define IMU_pin_3 34

int pitch = 0;
int roll = 0;
int yaw = 0;

void controlMotorMain(int pin){
  digitalWrite(pin,LOW);
  getReadings();
  pitch = getPitch();
  roll = getRoll();
  yaw = getYaw();
  ESC_speed(pin,PID_speed(pitch));
  digitalWrite(pin, HIGH);
}

void setup(){
  Serial.begin(115200);
  while (!Serial){delay(10); }
  
  init_ESC();
  delay(3000);
  IMU_init(IMU_adr_1);
  calibrateIMU_init();
  pinMode(IMU_pin_1,OUTPUT);
  pinMode(IMU_pin_2,OUTPUT);
  pinMode(IMU_pin_3,OUTPUT);
}

void loop(){
  controlMotorMain(32);
  controlMotorMain(33);
  controlMotorMain(34);
  digitalWrite(IMU_pin_1,HIGH);
  digitalWrite(IMU_pin_2,HIGH);
  digitalWrite(IMU_pin_3,HIGH);
}