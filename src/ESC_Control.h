#include <Arduino.h>
#include <ESP32Servo.h>
#include <hallSensor.h>
#include <PID.h>

#define ESC_pin1 35
#define ESC_pin2 35
#define ESC_pin3 35

#define MIN_SPEED 1000
#define MAX_SPEED 2000
#define MID_STOP 1500

Servo esc1;
Servo esc2;
Servo esc3;

int microSpeed

void init_ESC(){
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    esc1.attach(ESC_pin1, MIN_SPEED,MAX_SPEED);
    esc2.attach(ESC_pin1, MIN_SPEED,MAX_SPEED);
    esc3.attach(ESC_pin1, MIN_SPEED,MAX_SPEED);
    pinMode(ESC_pin1, OUTPUT);
    pinMode(ESC_pin2, OUTPUT);
    pinMode(ESC_pin3, OUTPUT);
    delay(1000);
}

void ESC_speed(int ESC, float speed){
    if (speed < 0){
        speed = -1*speed;
        speedMicro = MID_STOP - speed;
    }
    if(speed>0){
        speedMicro = MID_STOP + speed;
    }
    
    if(ESC == 35){esc1.writeMicroseconds(speedMicro);}
    if(ESC == 35){esc2.writeMicroseconds(speedMicro);}
    if(ESC == 35){esc3.writeMicroseconds(speedMicro);}
}

void ESC_stop(){
    esc1.writeMicroseconds(MID_STOP);
    esc2.writeMicroseconds(MID_STOP);
    esc3.writeMicroseconds(MID_STOP);
}