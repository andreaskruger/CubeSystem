#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <PID.h>
#include <Filter.h>

Adafruit_MPU6050 mpu;
#define dt 0.01
#define pi 3.14159265
#define plane 1

float savedAngle;

void init_IMU(){
    Serial.println("Init MPU6050.");
    if(!mpu.begin()){
        Serial.println("No MPU found.");
        while(1){
            delay(10);
        }
    }
    Serial.println("MPU6050 found, continue.");
}

float getAngle(float gyro, float accX,float accY,float accZ){
    savedAngle += gyro * dt;
    float pitchAcc = atan2f(accY,accZ*(180/pi));
    savedAngle = savedAngle*0.98 + pitchAcc*0.02;
}

float readIMU(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a,&g,&temp);
    float gyroX = g.gyro.x;
    float gyroY = g.gyro.y;
    float gyroZ = g.gyro.z;
    float accX = a.acceleration.x;
    float accY = a.acceleration.y;
    float accZ = a.acceleration.z;

    return PID_speed(getAngle(gyroX,accX,accY,accZ));
}

