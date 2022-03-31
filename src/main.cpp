#include <Arduino.h>
//#include <ESC_Control.h>
#include <rawIMU.h>
#include <PID.h>
#include "Angle_IMU.h"
#include <ESP32Servo.h>

Adafruit_MPU6050 MPU1;
Adafruit_MPU6050 MPU2;
Adafruit_MPU6050 MPU3;

IMU IMU1(32,MPU1);
IMU IMU2(33,MPU2);
IMU IMU3(34,MPU3);

Servo ESC;


void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  //init_ESC();
  ESC.attach(13,1000,2000);
  delay(3000);
  

}

void loop(){
  float pot = analogRead(12);
  pot = map(pot,0,4095,0,100);
  
  Serial.println(90 - pot/10);
  ESC.write(pot);
  delay(500);

 
  

  /*
  float speed1 = PID_speed(IMU1.readuIMU());
  float speed2 = PID_speed(IMU2.readuIMU());
  float speed3 = PID_speed(IMU3.readuIMU());
  if (speed1<0){speed1 = (speed1*-1)-90;}
  if (speed2<0){speed2 = (speed2*-1)-90;}
  if (speed3<0){speed3 = (speed3*-1)-90;}

  ESC_speed(1,speed1);
  ESC_speed(2,speed2);
  ESC_speed(3,speed3);*/
}