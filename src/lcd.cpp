#include <Arduino.h>
#include <LiquidCrystal.h>
#include "lcd.h"
#include "sneezectl.h"

static LiquidCrystal* lcd;

static lcd_states lcd_state = L_STARTUP;
static uint32_t last_update;

#define LCD_UPDATE_INTERVAL 100

void init_lcd(int rs, int en, int d4, int d5, int d6, int d7)
{
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    last_update = millis();
}

void tick_lcd(void)
{
    if(millis() - last_update > LCD_UPDATE_INTERVAL){ //Slow LCD refresh rate
        last_update = millis();
        switch(lcd_state)
        {
            case L_STARTUP:
                lcd_state = L_INFO;
                break;
            case L_INFO:
                lcd->clear();
                lcd->setCursor(0, 0);
                lcd->print("ME&T");
                lcd->setCursor(0, 1);
                lcd->print("Sneezeman");
                if(get_sneeze_state() != S_IDLE){
                    lcd_state = L_INFO_SNEEZE;
                }
                break;
            case L_INFO_SNEEZE:
                lcd->clear();
                lcd->setCursor(0, 0);
                lcd->print("Sneezing...");
                if(get_sneeze_state() == S_IDLE){
                    lcd_state = L_INFO;
                }
                break;
        }
    }
}