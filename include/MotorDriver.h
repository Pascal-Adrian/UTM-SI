#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// Initialize the motor control pins
void motorInit(int enaPin, int in1Pin, int in2Pin);

// Set motor power and direction (-100 to 100)
void motorSet(int power);

// Stop the motor immediately
void motorStop();

// Set motor to maximum power in current direction
void motorMax();

// Increase motor power by 10%
void motorInc();

// Decrease motor power by 10%
void motorDec();

// Get current motor power value
int motorGetPower();

#endif