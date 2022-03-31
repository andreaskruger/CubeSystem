#include "Angle_IMU.h"

#define dt 0.01
#define pi 3.1415

/*IMU::IMU(int IMU_pin, Adafruit_MPU6050 MPU){
    this->IMU_pin = IMU_pin;
    pinMode(IMU_pin, OUTPUT);
    this->MPU=MPU;
}*/
/*
float getAngle(float gyro, float accX,float accY,float accZ){
    savedAngles += gyro*dt;
    float pitchAcc = atan2f(accY,accZ*(180/pi));
    savedAngles = savedAngles*0.98 + pitchAcc*0.02;
    return savedAngles;
}

float readIMU(){
    digitalWrite(IMU_pin,HIGH);
    sensors_event_t a, g, temp;
    MPU.getEvent(&a,&g,&temp);
    float gyroX = g.gyro.x;
    float gyroY = g.gyro.y;
    float gyroZ = g.gyro.z;
    float accX = a.acceleration.x;
    float accY = a.acceleration.y;
    float accZ = a.acceleration.z;
    float angle = getAngle(gyroX,accX,accY,accZ);
    digitalWrite(IMU_pin,LOW);
    return angle;
}*/