#include "LCDOutput.h"
#include "KeypadInput.h"

const char PASSWORD[] = "DCBA";

void setup()
{
    initializeLCD();
    initializeKeypad();
    printf("Enter Password:");
}

void loop()
{
    static char input[17] = {0};
    static uint8_t inputPos = 0;

    if (kbhit())
    {
        char key = getch_nonblocking();
        if (key == '#')
        {
            input[inputPos] = '\0';
            printf("\n");
            if (strcmp(input, PASSWORD) == 0)
            {
                printf("Access Granted");
            }
            else
            {
                printf("Wrong Password");
            }
            inputPos = 0;
            delay(2000);
            clearLCD();
            printf("Enter Password:");
        }
        else if (key == '*')
        {
            inputPos = 0;
            clearLCD();
            printf("Enter Password:");
        }
        else if (inputPos < 16)
        {
            input[inputPos++] = key;
            lcd.setCursor(0, 1);
            lcd.print(input);
        }
    }
}