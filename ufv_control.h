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

#define PAN_SERVO_ENABLE 2

Servo null1;
Servo null2;
Servo panServo;

void motor_init();
void servo_init();
void control_motor(String direction, int value);
void move_servo(String plane, int value);

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
    null1.attach(PAN_SERVO_ENABLE, 1000, 2000);
    null2.attach(PAN_SERVO_ENABLE, 1000, 2000);
    panServo.attach(PAN_SERVO_ENABLE, 1000, 2000); // attaches the servo on pin 18 to the servo object
    panServo.write(90);
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
    Serial.printf("Writing %u\n", value);
}

void move_servo(String plane, int value)
{
    panServo.write(value);
    Serial.printf("Position: %d\n", value);
}