#ifndef RELAY_H
#define RELAY_H

// Initialize relay
void relay_init();

// Turn on relay
void relay_turnOn();

// Turn off relay
void relay_turnOff();

// Check relay status
bool relay_isOn();

#endif