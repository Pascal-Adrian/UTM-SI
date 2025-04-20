#include <Arduino.h>
#include "UART.h"
#include "Relay.h"
#include <LCDOutput.h>

void setup()
{
    // Initialize UART for serial communication
    initializeUart();

    // Initialize relay
    relay_init();

    // Initialize LCD
    initializeLCD();

    // Print welcome message
    printf("Relay Control System\n");
    printf("Available commands:\n");
    printf("- 'bulb on' : Turn the bulb on\n");
    printf("- 'bulb off' : Turn the bulb off\n");
    lcdPrintFormatted("*Relay Control*\nState: OFF");
}

void loop()
{
    char action[10];
    char target[10];

    printf("> ");

    // Read command from terminal
    if (scanf("%s %s", target, action) == 2)
    {
        printf("%s %s\n", target, action);
        // Check if command is valid
        if (strcmp(target, "bulb") == 0)
        {
            if (strcmp(action, "on") == 0)
            {
                relay_turnOn();
                printf("Bulb turned ON\n");
                lcdPrintFormatted("*Relay Control*\nState: ON");
            }
            else if (strcmp(action, "off") == 0)
            {
                relay_turnOff();
                printf("Bulb turned OFF\n");
                lcdPrintFormatted("*Relay Control*\nState: OFF");
            }
            else
            {
                printf("Unknown action: %s\n", action);
                printf("Valid actions are: 'on', 'off'\n");
            }
        }
        else
        {
            printf("Unknown target: %s\n", target);
            printf("Valid target is: 'bulb'\n");
        }
    }
    else
    {
        // Clear input buffer on error
        while (getchar() != '\n' && getchar() != EOF)
            ;
        printf("Invalid command format. Use: 'bulb on' or 'bulb off'\n");
    }

    // Small delay to prevent tight loop
    delay(100);
}