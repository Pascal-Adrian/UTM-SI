#include <Arduino.h>
#include "led_control.h"
#include "uart.h"
#include <stdio.h>

void setup()
{
  initializeUart();
  initializeLed();
  printf("LED Control System Ready\n");
  printf("Commands: 'led on' or 'led off'\n");
}

void loop()
{
  char command[32];
  char state[4];

  if (scanf("%s %s", command, state) == 2)
  {
    if (strcmp(command, "led") == 0)
    {
      if (strcmp(state, "on") == 0)
      {
        setLedState(true);
        printf("Command confirmed: LED turned ON\n");
      }
      else if (strcmp(state, "off") == 0)
      {
        setLedState(false);
        printf("Command confirmed: LED turned OFF\n");
      }
      else
      {
        printf("Invalid state. Use 'on' or 'off'\n");
      }
    }
    else
    {
      printf("Invalid command. Use 'led on' or 'led off'\n");
    }
    while (getchar() != '\n')
      ;
  }
}