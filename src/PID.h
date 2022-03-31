#include <Arduino.h>

double kp = 0.3;
double kd = 0;
double ki = 0;

double currentPIDTime = 0;
double lastTime = 0;
double lastError = 0;
double eTime = 0;
double cum = 0;

int baseLineAngle = 0.9;

float PID_speed(float angle){
    float speed;
    int error = angle - baseLineAngle;
    currentPIDTime = millis();
    eTime = currentPIDTime - lastTime;
    cum += error*eTime;
    speed = kp * error + kd * ((error-lastError)/eTime) + ki * cum;
    lastError = error;
    lastTime = currentPIDTime;
    return speed;
}