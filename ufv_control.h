/*
Functions that are responsible for controlling the UFV
*/

#pragma once

#include "Arduino.h"
#include <string>

#define MOTOR_ENABLE 15
#define MOTOR_A 12
#define MOTOR_B 13

void control_motor(String direction, int value);

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

    if (value == 0)
        digitalWrite(MOTOR_ENABLE, LOW);
    else if (value == 1)
        digitalWrite(MOTOR_ENABLE, HIGH);
}