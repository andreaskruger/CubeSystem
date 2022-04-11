#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <cmath>

#define IMU_pin_1 32
#define IMU_pin_2 33
#define IMU_pin_3 34

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus[3];   // holds actual interrupt status byte from MPU
uint8_t devStatus[3];      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize[3];    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount[3];     // count of all bytes currently in FIFO
uint8_t fifoBuffer[3][64]; // FIFO storage buffer

Quaternion q[3];           // [w, x, y, z]         quaternion container
VectorInt16 aa[3];         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal[3];     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld[3];    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity[3];    // [x, y, z]            gravity vector
float euler[3][3];         // [psi, theta, phi]    Euler angle container
float ypr[3][3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float yaw[3],pitch[3],roll[3];


int IMU_pins[3] = {32,33,34};