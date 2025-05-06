#include "MotorDriver.h"
#include "Arduino.h"

// Motor control pins
int ENA = 2; // PWM pin for speed control
int IN1 = 3; // Direction control 1
int IN2 = 4; // Direction control 2

// Current motor power state (-100 to 100)
int currentPower = 0;

// Initialize the motor control pins
void motorInit(int enaPin, int in1Pin, int in2Pin)
{
    ENA = enaPin;
    IN1 = in1Pin;
    IN2 = in2Pin;

    // Initialize motor control pins
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    // Initial motor state - stopped
    motorStop();
}

// Set motor power and direction (-100 to 100)
void motorSet(int power)
{
    // Constrain power to valid range
    power = constrain(power, -100, 100);
    currentPower = power;

    // Set direction based on power sign
    if (power > 0)
    {
        // Forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else if (power < 0)
    {
        // Backward
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        // Stop
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
    }

    // Set motor speed using PWM (map -100,100 to 0,255)
    int pwmValue = map(abs(power), 0, 100, 0, 255);
    analogWrite(ENA, pwmValue);
}

// Stop the motor immediately
void motorStop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    currentPower = 0;
}

// Set motor to maximum power in current direction
void motorMax()
{
    if (currentPower > 0)
    {
        motorSet(100);
    }
    else if (currentPower < 0)
    {
        motorSet(-100);
    }
    // If currently stopped, do nothing
}

// Increase motor power by 10%
void motorInc()
{
    // If power is positive, increase by 10
    if (currentPower > 0)
    {
        motorSet(min(100, currentPower + 10));
    }
    else if (currentPower < 0)
    {
        // If power is negative, decrease by 10 (moving toward zero)
        motorSet(min(0, currentPower - 10));
    }
}

// Decrease motor power by 10%
void motorDec()
{
    // If power is negative, increase by 10 (moving toward zero)
    if (currentPower < 0)
    {
        motorSet(max(-100, currentPower + 10));
    }
    else
    {
        // If power is positive or zero, decrease by 10
        motorSet(max(0, currentPower - 10));
    }
}

// Get current motor power value
int motorGetPower()
{
    return currentPower;
}