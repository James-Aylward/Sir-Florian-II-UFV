/*
Functions that are responsible for controlling the UFV
*/

#pragma once

#include "Arduino.h"
#include "esp32-hal-ledc.h"
#include <string>

#define MOTOR_ENABLE 15
#define MOTOR_A 12
#define MOTOR_B 13
#define MOTOR_CHANNEL 3
#define MOTOR_RES 8
#define MOTOR_FREQ 30000

void motor_init();
void control_motor(String direction, int value);

void motor_init()
{
    pinMode(MOTOR_A, OUTPUT);
	pinMode(MOTOR_B, OUTPUT);
	ledcSetup(MOTOR_CHANNEL, MOTOR_FREQ, MOTOR_RES);
	ledcAttachPin(MOTOR_ENABLE, MOTOR_CHANNEL);
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