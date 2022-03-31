#pragma once

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


class IMU{
    private:
        int IMU_pin;
        float savedAngles;
        Adafruit_MPU6050 MPU;
    public:
        IMU(int IMU_pin, Adafruit_MPU6050 MPU){};
        float getAngle(float, float,float,float);
        float readuIMU();

};

