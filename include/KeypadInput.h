#ifndef KEYPADINPUT_H
#define KEYPADINPUT_H

#include <Keypad.h>

extern Keypad keypad;
void initializeKeypad();
bool kbhit();
int getch_nonblocking();

#endif