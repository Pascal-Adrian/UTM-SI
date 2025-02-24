#include <LCDIO.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void printMessage(const char *msg)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(msg);
    printf("%s\n", msg);
}

void printInput(const String &inp)
{
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(inp);
    printf("Input: %s\n", inp.c_str());
}