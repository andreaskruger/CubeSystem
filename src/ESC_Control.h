#include <Arduino.h>
#include <ESP32Servo.h>
#include <hallSensor.h>
#include <PID.h>

#define ESC_pin1 32
#define ESC_pin2 32
#define ESC_pin3 32

#define MIN_SPEED 1000
#define MAX_SPEED 2000
#define MID_STOP 1500

Servo esc1;
Servo esc2;
Servo esc3;



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
    if(speed > 130 && speed > 90){speed = 130;}
    if(speed > 50 && speed <90){speed = 40;}
    if(ESC == 32){esc1.write(1);}
    if(ESC == 33){esc2.write(1);}
    if(ESC == 34){esc3.write(1);}
}

void ESC_stop(){
    esc1.write(90);
    esc2.write(90);
    esc3.write(90);
}