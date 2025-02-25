#include "LCDOutput.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
char currentTopLine[17] = {0};
char currentBottomLine[17] = {0};
uint8_t cursorRow = 0;
uint8_t cursorCol = 0;

void initializeLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();

    static FILE lcdout = {0};
    fdev_setup_stream(&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcdout;
}

int lcd_putchar(char c, FILE *stream)
{
    if (c == '\n')
    {
        cursorRow = (cursorRow + 1) % 2;
        cursorCol = 0;
        lcd.setCursor(cursorCol, cursorRow);
        for (int i = 0; i < 16; i++)
        {
            lcd.write(' ');
        }
        lcd.setCursor(cursorCol, cursorRow);
        (cursorRow == 0) ? (currentTopLine[0] = '\0') : (currentBottomLine[0] = '\0');
        return 0;
    }
    else if (c == '\r')
    {
        cursorCol = 0;
        lcd.setCursor(cursorCol, cursorRow);
        return 0;
    }
    if (cursorCol < 16)
    {
        lcd.write(c);
        (cursorRow == 0) ? (currentTopLine[cursorCol] = c, currentTopLine[cursorCol + 1] = '\0') : (currentBottomLine[cursorCol] = c, currentBottomLine[cursorCol + 1] = '\0');
        cursorCol++;
    }
    return 0;
}

void clearLCD()
{
    lcd.clear();
    cursorRow = cursorCol = 0;
    lcd.setCursor(0, 0);
}