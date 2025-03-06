#include "BlinkingLed.h"
#include "Config.h"
#include "Globals.h"
#include <Arduino.h>
#include <stdio.h>
#include "LedControl.h"
#include "ButtonControl.h"

void run_blinking_led()
{
    if (!led1State)
    {
        led2State = !led2State;
        setLed(LED_2_PIN, led2State);
    }
    else
    {
        setLed(LED_2_PIN, false);
    }
    lastTaskTime[1] = millis();
}

void run_blinking_led_buttons()
{
    if (isButtonPressed(BUTTON_INC_PIN, incButtonPressed) && counter < 60)
    {
        counter++;
        printf("Blink count increased to: %d\n", counter);
    }
    if (isButtonPressed(BUTTON_DEC_PIN, decButtonPressed) && counter > 1)
    {
        counter--;
        printf("Blink count decreased to: %d\n", counter);
    }
    lastTaskTime[2] = millis();
}