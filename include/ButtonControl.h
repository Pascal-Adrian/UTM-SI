#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

bool readButton(int pin);
bool isButtonPressed(int pin, volatile bool &lastState);

#endif