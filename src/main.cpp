#include <Arduino.h>
#include "sneezectl.h"

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

void setup() {
  pinMode(SB_T1, OUTPUT);
  pinMode(SB_T2, OUTPUT);
  pinMode(SB_T3, OUTPUT);
  pinMode(SB_T4, OUTPUT);

  pinMode(led_output, OUTPUT);

  init_sneeze(dose_pump, air_pump, release_valve);
}

void loop() {
  tick_sneeze();
}