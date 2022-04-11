#include <Arduino.h>
#include <IMUconfig.h>

MPU6050 mpu[3];

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
    Serial.println(F("Initializing I2C devices..."));
    changeDigiPin(IMU_pin_1);
    mpu[0].initialize();
    changeDigiPin(IMU_pin_2);
    mpu[1].initialize();
    changeDigiPin(IMU_pin_3);
    mpu[2].initialize();

    // wait for ready
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    while (Serial.available() && Serial.read()); // empty buffer
    while (!Serial.available());                 // wait for data
    while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    changeDigiPin(IMU_pin_1);
    devStatus[0] = mpu[0].dmpInitialize();
    Serial.println("Dev status 1: "+devStatus[0]);
    changeDigiPin(IMU_pin_2);
    devStatus[1] = mpu[1].dmpInitialize();
    Serial.println("Dev status 2: "+devStatus[1]);
    changeDigiPin(IMU_pin_3);
    devStatus[2] = mpu[2].dmpInitialize();
    Serial.println("Dev status 3: "+devStatus[2]);

    for(int i; i<3; i++){
        changeDigiPin(IMU_pin_1+i);
        mpu[i].setXGyroOffset(220);
        mpu[i].setYGyroOffset(76);
        mpu[i].setZGyroOffset(-85);
        mpu[i].setZAccelOffset(1788); // 1688 factory default for my test chip
    }
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        for (int i = 0; i < 3; i++){
            // Calibration Time: generate offsets and calibrate our MPU6050
            mpu[i].CalibrateAccel(7);
            mpu[i].CalibrateGyro(7);
            mpu[i].PrintActiveOffsets();
            // turn on the DMP, now that it's ready
            Serial.println(F("Enabling DMP..."));
            mpu[i].setDMPEnabled(true);
            dmpReady = true;

            // get expected DMP packet size for later comparison
            packetSize[i] = mpu[i].dmpGetFIFOPacketSize();
        }  
    }
}
void readBuffer(){
    for (int i = 0; i < 3; i++){
        mpu[i].resetFIFO();
        fifoCount[i] = mpu[i].getFIFOCount();
        while (fifoCount[i] < packetSize[i]){fifoCount[i] = mpu[i].getFIFOCount();}
        mpu[i].getFIFOBytes(fifoBuffer[i],packetSize[i]);
    }
}

void readIMU() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;
    for (int i = 0; i < 3; i++){
        changeDigiPin(IMU_pin_1+i);
        readBuffer();
        mpu[i].dmpGetQuaternion(&q[i], fifoBuffer[i]);
        mpu[i].dmpGetGravity(&gravity[i], &q[i]);
        mpu[i].dmpGetYawPitchRoll(ypr[i], &q[i], &gravity[i]);
        yaw[i] = ypr[i][0] * 180/PI;
        roll[i] = ypr[i][1] * 180/PI;
        pitch[i] = ypr[i][2] * 180/PI;
    }
}
