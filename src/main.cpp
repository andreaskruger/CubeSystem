#include <Arduino.h>
#include <IMUdata.h>
#include <ESP32Servo.h>
#include <ESC_control.h>
#include <I2C_SCANNER.h>
#include <wifi_com.h>

#define IMU_pin_1 33
#define IMU_pin_2 34
#define IMU_pin_3 35
Servo esc;

void controlMotorMain(int pin,float angle){
  ESC_speed(pin, PID_angle(angle));
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
  while(interupt_state1){
    readIMU();
    //controlMotorMain(35,yaw);
    //controlMotorMain(36,roll2);
    Serial.print("PID yaw1: ");
    Serial.print(yaw);
    Serial.print("          Speed:");
    Serial.println(PID_angle(yaw));
  /*
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
    Serial.println(roll2);*/
    delay(200);
  }
}