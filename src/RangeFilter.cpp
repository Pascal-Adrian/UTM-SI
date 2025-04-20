#include <Arduino.h>
#include "RangeSensor.h"

void init_range_sensor(void)
{
    pinMode(PING_PIN, OUTPUT);
    digitalWrite(PING_PIN, LOW);

    pinMode(ECHO_PIN, INPUT);
}

float get_range(void)
{
    float echo_time, measured_range;

    digitalWrite(PING_PIN, LOW);
    delayMicroseconds(50);

    digitalWrite(PING_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(PING_PIN, LOW);

    echo_time = pulseIn(ECHO_PIN, HIGH, 30000);

    if (echo_time == 0)
    {
        return MAX_RANGE_CM;
    }

    measured_range = (echo_time * SOUND_VELOCITY) / 2.0;

    return measured_range;
}