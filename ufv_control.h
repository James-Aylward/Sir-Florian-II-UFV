/*
Functions that are responsible for controlling the UFV
*/

#pragma once

#include "Arduino.h"
#include <ESP32Servo.h>
#include "esp32-hal-ledc.h"
#include <string>

#define MOTOR_ENABLE 15
#define MOTOR_A 12
#define MOTOR_B 13
#define MOTOR_CHANNEL 0
#define MOTOR_RES 8
#define MOTOR_FREQ 20000

#define PAN_SERVO_ENABLE 0

Servo panServo;

void motor_init();
void servo_init();
void control_motor(String direction, int value);
void control_servo();

void motor_init()
{
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    ledcSetup(MOTOR_CHANNEL, MOTOR_FREQ, MOTOR_RES);
    ledcAttachPin(MOTOR_ENABLE, MOTOR_CHANNEL);
}

void servo_init()
{
    panServo.setPeriodHertz(50);
	panServo.attach(PAN_SERVO_ENABLE, 1000, 2000); // attaches the servo on pin 18 to the servo object
    panServo.write(0);
}

void control_motor(String direction, int value)
{

    if (direction == "forward")
    {
        digitalWrite(MOTOR_A, HIGH);
        digitalWrite(MOTOR_B, LOW);
    }
    else if (direction == "backward")
    {
        digitalWrite(MOTOR_B, HIGH);
        digitalWrite(MOTOR_A, LOW);
    }

    ledcWrite(MOTOR_CHANNEL, value);
}

void control_servo()
{
    for (int pos = 0; pos <= 180; pos += 20)
    {
        Serial.printf("Position: %u\n", pos);
        panServo.write(pos);    
        delay(200);
    }

    panServo.write(0);
}