#include "Relay.h"
#include <Arduino.h>

#define RELAY_PIN 7

static bool relayState = false;

void relay_init()
{
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

void relay_turnOn()
{
    digitalWrite(RELAY_PIN, HIGH);
    relayState = true;
}

void relay_turnOff()
{
    digitalWrite(RELAY_PIN, LOW);
    relayState = false;
}

bool relay_isOn()
{
    return relayState;
}