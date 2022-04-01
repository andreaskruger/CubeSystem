#include <Arduino.h>
#include <Wire.h>

const int IMU_adr_1 = 0x68;

int16_t AcX, AcY,AcZ,GyX, GyY,GyZ,returnVal;
int temperature;
int gyro_x, gyro_y, gyro_z;
long loopTimer, loopTimer2;
long acc_x, acc_y, acc_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
double accelPitch;
double accelRoll;
double accelYaw;
double freq, dt;
double tau = 0.98;
double roll = 0;
double pitch = 0;
double yaw = 0;
double gyroRoll, gyroPitch, gyroYaw;
float accel_x, accel_y, accel_z;
float rotation_x, rotation_y, rotation_z;


// 250 deg/s --> 131.0, 500 deg/s --> 65.5, 1000 deg/s --> 32.8, 2000 deg/s --> 16.4
long scaleFactorGyro = 32.8;
 
// 2g --> 16384 , 4g --> 8192 , 8g --> 4096, 16g --> 2048
long scaleFactorAccel = 8192;


void IMU_init(int MPU_adr){
  Wire.begin(21,22,4000000);
  Wire.beginTransmission(MPU_adr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
 
  // Configure the accelerometer
  // Wire.write(0x__);
  // Wire.write; 2g --> 0x00, 4g --> 0x08, 8g --> 0x10, 16g --> 0x18
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x08);
  Wire.endTransmission();
 
  // Configure the gyro
  // Wire.write(0x__);
  // 250 deg/s --> 0x00, 500 deg/s --> 0x08, 1000 deg/s --> 0x10, 2000 deg/s --> 0x18
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  loopTimer = micros();
  loopTimer2 = micros();

  Serial.println("Setup for IMU done.");
}

int readAccX(int MPU_adr){
  Wire.beginTransmission(0x3B);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readAccY(int MPU_adr){
  Wire.beginTransmission(0x3D);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readAccZ(int MPU_adr){
  Wire.beginTransmission(0x3F);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readGyX(int MPU_adr){
  Wire.beginTransmission(0x43);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readGyY(int MPU_adr){
  Wire.beginTransmission(0x45);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readGyZ(int MPU_adr){
  
  Wire.beginTransmission(0x47);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
void readAllIMUValues(){
  AcX = readAccX(IMU_adr_1);
  AcY = readAccY(IMU_adr_1);
  AcZ = readAccZ(IMU_adr_1);
  GyX = readGyX(IMU_adr_1);
  GyY = readGyY(IMU_adr_1);
  GyZ = readGyZ(IMU_adr_1);
}

void calibrateIMU_init(){
    for (int cal_int = 0; cal_int < 3000; cal_int ++){
    if(cal_int % 200 == 0)Serial.print(".");
    readAllIMUValues();
    gyro_x_cal += gyro_x;
    gyro_y_cal += gyro_y;
    gyro_z_cal += gyro_z;
    delay(3);
  }
 
  // Average the values
  gyro_x_cal /= 3000;
  gyro_y_cal /= 3000;
  gyro_z_cal /= 3000;

}

void getReadings(){
  freq = 1/((micros() - loopTimer2) * 1e-6);
  loopTimer2 = micros();
  dt = 1/freq;
  readAllIMUValues();
  gyro_x-=gyro_x_cal;
  gyro_y-=gyro_y_cal;
  gyro_z-=gyro_z_cal;

  rotation_x = (double)gyro_x / (double)scaleFactorGyro;
  rotation_y = (double)gyro_y / (double)scaleFactorGyro;
  rotation_z = (double)gyro_z / (double)scaleFactorGyro;
 
  // Convert to g force
  accel_x = (double)acc_x / (double)scaleFactorAccel;
  accel_y = (double)acc_y / (double)scaleFactorAccel;
  accel_z = (double)acc_z / (double)scaleFactorAccel;

  // Complementary filter
  accelPitch = atan2(accel_y, accel_z) * RAD_TO_DEG; //får ut en vinkel av detta
  accelRoll = atan2(accel_x, accel_z) * RAD_TO_DEG;
  accelYaw = atan2(accel_x, accel_y) * RAD_TO_DEG;
 
  pitch = (tau)*(pitch + rotation_x*dt) + (1-tau)*(accelPitch);
  roll = (tau)*(roll - rotation_y*dt) + (1-tau)*(accelRoll);
  yaw = (tau)*(yaw + rotation_z*dt) + (1-tau)*(accelYaw);

  while (micros() - loopTimer <= 2800){}
  loopTimer = micros();
}

int getPitch(){return pitch;}
int getRoll(){return roll;}
int getYaw(){return yaw;}