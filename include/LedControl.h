#ifndef LED_CONTROL_H
#define LED_CONTROL_H

void initializeLed();
void setLedState(bool state);
void setLed(int pin, bool state);

#endif