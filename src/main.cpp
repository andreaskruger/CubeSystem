#include <Arduino.h>
#include <IMUdata.h>
#include <ESP32Servo.h>
#include <ESC_control.h>
#include <I2C_SCANNER.h>

#define IMU_pin_1 32
#define IMU_pin_2 33
#define IMU_pin_3 34
Servo esc;

void controlMotorMain(int pin){
}

void setup(){
  Serial.begin(115200);
  while (!Serial){delay(10); }
  init_scanner();
  //scan_I2C();
  pinMode(IMU_pin_1,OUTPUT);
  pinMode(IMU_pin_2,OUTPUT);
  pinMode(IMU_pin_3,OUTPUT);
  digitalWrite(IMU_pin_1,HIGH);
  digitalWrite(IMU_pin_2,HIGH);
  digitalWrite(IMU_pin_3,HIGH);
  init_IMU();
  esc.attach(13);
  //init_ESC();
  //delay(3000);
  esc.writeMicroseconds(1500);
  delay(1000);
}

void loop(){
  //Serial.println("Loop");
  /*for (int i = 0; i < 2000; i++)
  {
    Serial.println(i);
    esc.writeMicroseconds(1000+i);
    delay(100);
  }*/
  
  readIMU();
  Serial.print("Yaw1: ");
  Serial.print(yaw);
  Serial.print("       Yaw2: ");
  Serial.print(yaw2);
  Serial.print("       Pitch1: ");
  Serial.print(pitch);
  Serial.print("       pitch2: ");
  Serial.print(pitch2);
  Serial.print("       Roll: ");
  Serial.print(roll);
  Serial.print("       Roll2: ");
  Serial.println(roll2);
  delay(200);
  //controlMotorMain(32);
  //controlMotorMain(33);
  //controlMotorMain(34);
}