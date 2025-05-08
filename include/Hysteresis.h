#ifndef HYSTERESIS_H
#define HYSTERESIS_H

extern float temperatureSetPoint;
extern float temperatureHysteresisRange;

bool temperatureHysteresis(int temp);
void setTemperatureSetPoint(float setPoint);
void setTemperatureHysteresisRange(float hysteresisRange);
float getTemperatureSetPoint();
float getTemperatureHysteresisRange();

#endif