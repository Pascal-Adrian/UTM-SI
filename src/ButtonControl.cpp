#include "ButtonControl.h"
#include <Arduino.h>

bool readButton(int pin)
{
    return digitalRead(pin) == LOW;
}

bool isButtonPressed(int pin, volatile bool &lastState)
{
    bool currentState = readButton(pin);
    if (currentState && !lastState)
    {
        lastState = true;
        return true;
    }
    else if (!currentState && lastState)
    {
        lastState = false;
    }
    return false;
}