#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <UART.h>
#include <LCDIO.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const String password = "DCBA";
String input = "";

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
    initializeUart();
    lcd.init();
    lcd.backlight();
    printMessage("Enter Password:");
}

void loop()
{
    char key = keypad.getKey();
    if (key)
    {
        if (key == '#')
        {
            char scannedInput[32] = {0};
            if (sscanf(input.c_str(), "%31s", scannedInput) == 1)
            {
                printf("Scanned Input: %s\n", scannedInput);
                if (strcmp(scannedInput, password.c_str()) == 0)
                {
                    printMessage("Access Granted");
                }
                else
                {
                    printMessage("Incorrect Password");
                }
            }
            else
            {
                printMessage("Parse error!");
            }
            delay(2000);
            input = "";
            printMessage("Enter Password:");
        }
        else if (key == '*')
        {
            input = "";
            printMessage("Enter Password:");
        }
        else
        {
            input += key;
            printInput(input);
        }
    }
}