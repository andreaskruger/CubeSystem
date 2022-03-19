#include <Arduino.h>

double kp = 0;
double kd = 0;
double ki = 0;

double currentTime = 0;
double lastTime = 0;
double lastError = 0;
double eTime = 0;
double cum = 0;

int baseLineAngle = 0;

float PID_speed(float angle){
    float speed;
    int error = angle - baseLineAngle;
    currentTime = millis();
    eTime = currentTime - lastTime;
    cum += error*eTime;
    speed = kp * error + kd * ((error-lastError)/eTime) + ki * cum;
    lastError = error;
    lastTime = currentTime;
    return speed;
}