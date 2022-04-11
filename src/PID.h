#include <Arduino.h>

double kp = 0.3;
double kd = 0;
double ki = 0;

double currentPIDTime = 0;
double lastTime = 0;
double lastError = 0;
double eTime = 0;
double cum = 0;

int baseLineAngle = 1;


double kp_speed = 0.3;
double kd_speed = 0;
double ki_speed = 0;

double currentPIDTime_speed = 0;
double lastTime_speed = 0;
double lastError_speed = 0;
double eTime_speed = 0;
double cum_speed = 0;


float PID_speed(float speed, float currentSpeed){
    float newSpeed;
    int error = speed - currentSpeed;
    currentPIDTime_speed = millis();
    eTime = currentPIDTime_speed - lastTime_speed;
    cum += error*eTime_speed;
    newSpeed = kp_speed * error + kd_speed * ((error-lastError_speed)/eTime_speed) + ki_speed * cum_speed;
    lastError_speed = error;
    lastTime_speed = currentPIDTime_speed;
    return newSpeed;
}
float PID_angle(float angle){
    float speed;
    int error = angle - baseLineAngle;
    currentPIDTime = millis();
    eTime = currentPIDTime - lastTime;
    cum += error*eTime;
    speed = kp * error + kd * ((error-lastError)/eTime) + ki * cum;
    lastError = error;
    lastTime = currentPIDTime;
    if (speed>1500 && speed>1600){speed = 1600;}
    if (speed <1400){speed = 1400;}
    return speed;
}