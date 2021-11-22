#include <Arduino.h>
#include <LiquidCrystal.h>
#include "lcd.h"

LiquidCrystal* lcd;

void init_lcd(int rs, int en, int d4, int d5, int d6, int d7)
{
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
}

void tick_lcd(void)
{
    lcd->setCursor(0, 0);
    lcd->print("Hello World!");
}