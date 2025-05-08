#include <Hysteresis.h>

float temperatureSetPoint = 30.0;       // Default set point
float temperatureHysteresisRange = 1.0; // Default hysteresis range

bool temperatureHysteresis(int temp)
{
    if (temp < temperatureSetPoint - temperatureHysteresisRange)
    {
        return true;
    }
    return false;
}

void setTemperatureSetPoint(float setPoint)
{
    temperatureSetPoint = setPoint;
}

void setTemperatureHysteresisRange(float hysteresisRange)
{
    temperatureHysteresisRange = hysteresisRange;
}

float getTemperatureSetPoint()
{
    return temperatureSetPoint;
}

float getTemperatureHysteresisRange()
{
    return temperatureHysteresisRange;
}
