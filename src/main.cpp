#include <Arduino.h>

#include "config.h"
#include "sneezectl.h"
#include "lcd.h"
#include "vl53.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "startup.h"

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

#define air_pump 3
#define sound_board 5
#define dose_pump 6
#define release_valve 9
#define red_led 10
#define green_led 11

#define heartbeat 13

uint8_t heartbeat_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SB_T1, OUTPUT);
  pinMode(SB_T2, OUTPUT);
  pinMode(SB_T3, OUTPUT);
  pinMode(SB_T4, OUTPUT);

  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  pinMode(heartbeat, OUTPUT);

  init_config();
  init_sneeze(dose_pump, air_pump, release_valve, sound_board, red_led, green_led);
  //init_lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
  init_vl53();
  analogWrite(red_led, 255);
  initValve(release_valve);
  analogWrite(green_led, 0);
}

void loop() {
  digitalWrite(heartbeat, heartbeat_state);
  heartbeat_state = !heartbeat_state;

  if(trigger_get_vl53()){
    start_sneeze();
    trigger_reset_vl53();
  }

  tick_sneeze();
  //tick_lcd();
  tick_vl53();
}