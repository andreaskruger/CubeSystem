#include <Arduino.h>
#include <Wire.h>

int16_t AcX, AcY,AcZ,GyX, GyY,GyZ,returnVal;

void IMU_init(int MPU_adr){
  Wire.begin(21,22,4000000);
  Wire.beginTransmission(MPU_adr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
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
int readGyX(int MPU_adr){
  Wire.beginTransmission(0x45);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}
int readGyX(int MPU_adr){
  Wire.beginTransmission(0x47);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_adr);
  Wire.requestFrom(MPU_adr,2,true);
  returnVal = Wire.read() <<8 | Wire.read();
  return returnVal;
}