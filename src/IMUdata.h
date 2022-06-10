#include <Arduino.h>
#include <IMUconfig.h>

// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu1(0x68);
MPU6050 mpu2(0x68);

#define OUTPUT_READABLE_YAWPITCHROLL


#if i2CDEV_IMPLEMENTATION == I2C_ARDUINO_WIRE
    #include "Wire.h"
#endif

void changeDigiPin(int pin){
    if(pin == IMU_pin_1){
        digitalWrite(IMU_pin_1,LOW);
        digitalWrite(IMU_pin_2,HIGH);
        digitalWrite(IMU_pin_3,HIGH);
    }
    if(pin == IMU_pin_2){
        digitalWrite(IMU_pin_1,HIGH);
        digitalWrite(IMU_pin_2,LOW);
        digitalWrite(IMU_pin_3,HIGH);
    }
    if(pin == IMU_pin_3){
        digitalWrite(IMU_pin_1,HIGH);
        digitalWrite(IMU_pin_2,HIGH);
        digitalWrite(IMU_pin_3,LOW);
    }
}
void init_IMU() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize device
    changeDigiPin(32);
    
    Serial.println(F("Initializing I2C device 1..."));
    mpu1.initialize();
    // verify connection
    Serial.println(F("Testing device 1 connections..."));
    Serial.println(mpu1.testConnection() ? F("MPU6050 connection IMU 1 successful") : F("MPU6050 connection IMU 1 failed"));

    changeDigiPin(33);
    Serial.println(F("Initializing I2C device 2..."));
    mpu2.initialize();
    // verify connection
    Serial.println(F("Testing device 2 connections..."));
    Serial.println(mpu2.testConnection() ? F("MPU6050 connection IMU 2 successful") : F("MPU6050 connection IMU 2 failed"));
    // wait for ready

    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    while (Serial.available() && Serial.read()); // empty buffer
    while (!Serial.available());                 // wait for data
    while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP 1..."));
    changeDigiPin(32);

    devStatus = mpu1.dmpInitialize();
    Serial.println("Dev status 1: "+devStatus);

    mpu1.setXGyroOffset(220);
    mpu1.setYGyroOffset(76);
    mpu1.setZGyroOffset(-85);
    mpu1.setZAccelOffset(1788); 

    mpu1.CalibrateAccel(7);
    mpu1.CalibrateGyro(7);
    mpu1.PrintActiveOffsets();
    mpu1.setDMPEnabled(true);
    dmpReady = true;
    packetSize = mpu1.dmpGetFIFOPacketSize();

    Serial.println(F("Initializing DMP 2..."));
    changeDigiPin(33);
    devStatus = mpu2.dmpInitialize();
    Serial.println("Dev status 2: "+devStatus);

    mpu2.setXGyroOffset(220);
    mpu2.setYGyroOffset(76);
    mpu2.setZGyroOffset(-85);
    mpu2.setZAccelOffset(1788); 

    mpu2.CalibrateAccel(7);
    mpu2.CalibrateGyro(7);
    mpu2.PrintActiveOffsets();
    mpu2.setDMPEnabled(true);
    dmpReady2 = true;
    packetSize2 = mpu2.dmpGetFIFOPacketSize();  
     
}
void readBuffer(){
    changeDigiPin(32);
    mpu1.resetFIFO();
    fifoCount = mpu1.getFIFOCount();
    while (fifoCount < packetSize){fifoCount = mpu1.getFIFOCount();}
    mpu1.getFIFOBytes(fifoBuffer,packetSize);
    changeDigiPin(33);
    mpu2.resetFIFO();
    fifoCount2 = mpu2.getFIFOCount();
    while (fifoCount2 < packetSize2){fifoCount2 = mpu2.getFIFOCount();}
    mpu2.getFIFOBytes(fifoBuffer2,packetSize2);
}

void readIMU() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
        readBuffer();
        mpu1.dmpGetQuaternion(&q, fifoBuffer);
        mpu1.dmpGetGravity(&gravity, &q);
        mpu1.dmpGetYawPitchRoll(ypr, &q, &gravity);
        yaw = ypr[0] * 180/PI;
        roll = ypr[1] * 180/PI;
        pitch = ypr[2] * 180/PI;
        mpu2.dmpGetQuaternion(&q2, fifoBuffer2);
        mpu2.dmpGetGravity(&gravity2, &q2);
        mpu2.dmpGetYawPitchRoll(ypr2, &q2, &gravity2);
        yaw2 = ypr2[0] * 180/PI;
        roll2 = ypr2[1] * 180/PI;
        pitch2 = ypr2[2] * 180/PI;
}
