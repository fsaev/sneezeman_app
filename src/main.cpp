#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "sneezectl.h"
#include "lcd.h"
#include "vl53.h"

#define LCD_RS 12
#define LCD_EN 11
#define LCD_RW 10
#define LCD_DB4 5
#define LCD_DB5 4
#define LCD_DB6 3
#define LCD_DB7 2

#define SB_T1 14
#define SB_T2 15
#define SB_T3 16
#define SB_T4 17

#define dose_pump 9
#define air_pump 8
#define release_valve 7

#define led_output 6
#define heartbeat 13

uint8_t heartbeat_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SB_T1, OUTPUT);
  pinMode(SB_T2, OUTPUT);
  pinMode(SB_T3, OUTPUT);
  pinMode(SB_T4, OUTPUT);

  pinMode(led_output, OUTPUT);

  pinMode(heartbeat, OUTPUT);

  init_config();
  init_sneeze(dose_pump, air_pump, release_valve);
  init_lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
  init_vl53();
}

void loop() {
  digitalWrite(heartbeat, heartbeat_state);
  heartbeat_state = !heartbeat_state;

  if(trigger_get_vl53()){
    start_sneeze();
    trigger_reset_vl53();
  }

  tick_sneeze();
  tick_lcd();
  tick_vl53();
}