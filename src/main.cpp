#include <Arduino.h>
#include <IMUdata.h>
#include <ESP32Servo.h>
#include <ESC_control.h>
#include <I2C_SCANNER.h>

#define IMU_pin_1 32
#define IMU_pin_2 33
#define IMU_pin_3 34

void controlMotorMain(int pin){
  if(pin == 32){PID_speed(PID_angle(yaw[0]),getCurrentSpeed());}
  if(pin == 33){PID_speed(PID_angle(pitch[1]),getCurrentSpeed());}
  if(pin == 34){PID_speed(PID_angle(roll[2]),getCurrentSpeed());}
}

void setup(){
  Serial.begin(115200);
  while (!Serial){delay(10); }

  init_scanner();
  scan_I2C();

  pinMode(IMU_pin_1,OUTPUT);
  pinMode(IMU_pin_2,OUTPUT);
  pinMode(IMU_pin_3,OUTPUT);
  digitalWrite(IMU_pin_1,LOW);
  digitalWrite(IMU_pin_2,HIGH);
  digitalWrite(IMU_pin_3,HIGH);
  //init_ESC();
  //delay(3000);
  init_IMU();


}

void loop(){
  Serial.println("Loop");
  readIMU();
  Serial.print("Yaw1: ");
  Serial.println(yaw[0]);
  Serial.print("Yaw2: ");
  Serial.println(yaw[1]);
  Serial.print("Yaw3: ");
  Serial.println(yaw[2]);
  //controlMotorMain(32);
  //controlMotorMain(33);
  //controlMotorMain(34);
}