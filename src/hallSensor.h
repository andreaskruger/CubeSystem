#include <Arduino.h>

#define interuptPin 16
float currentSpeed=0;
float RPM = 0;

void init_interuptPin(int pin){attachInterrupt(pin,interuptFunction,HIGH);}

void interuptFunction(){}
float getCurrentSpeed(){return currentSpeed;}

