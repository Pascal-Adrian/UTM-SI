#include "LCDOutput.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27

void initializeLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

int lcd_putchar(char c, FILE *stream)
{
    if (c == '\n')
    {
        lcd.setCursor(0, 1);
        return 0;
    }
    lcd.write(c);
    return 0;
}

char formatted_buffer[128];

void lcdPrintFormatted(const char *format, ...)
{
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    lcd.clear();
    int col = 0, row = 0;
    lcd.setCursor(col, row);

    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        if (buffer[i] == '\n')
        {
            row++;
            if (row >= 2)
                break;
            col = 0;
            lcd.setCursor(col, row);
        }
        else
        {
            lcd.print(buffer[i]);
        }
    }
}
