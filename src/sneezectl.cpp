#include <Arduino.h>
#include "sneezectl.h"

#define PRIME_DURATION 1750
#define PUMP_DURATION 1750
#define HOLD_DURATION 800
#define RELEASE_DURATION 1000
#define SOUND_DURATION 150

static uint8_t l_dose_pwm;
static int8_t l_air_pwm;
static uint8_t l_release_valve;
static uint8_t sound_boardFX;
static uint8_t l_red_led;
static uint8_t l_green_led;

static uint32_t last_time = 0;
static uint32_t sound_time = 0;
static uint8_t flags = 0;

#define FLAG_PRIMED 1
#define FLAG_PUMPED 2

enum sneeze_states sneeze_state = S_IDLE;

void init_sneeze(int dose_pwm, int air_pwm, int release_valve, int sound_board, int red_led, int green_led)
{
    pinMode(dose_pwm, OUTPUT);
    pinMode(air_pwm, OUTPUT);
    pinMode(release_valve, OUTPUT);
    pinMode(sound_board, OUTPUT);

    l_dose_pwm = dose_pwm;
    l_air_pwm = air_pwm;
    l_release_valve = release_valve;
    sound_boardFX = sound_board;
    l_red_led = red_led;
    l_green_led = green_led;
}

void start_sneeze(void)
{
    if(sneeze_state == S_IDLE)
    {
        last_time = millis();
        sneeze_state = S_PRIME;
        Serial.println("PRIME");
    }
}

enum sneeze_states get_sneeze_state(void)
{
    return sneeze_state;
}

void tick_sneeze(void)
{
    switch(sneeze_state)
    {
        case S_IDLE:
            analogWrite(l_green_led, 255);
            analogWrite(l_red_led, 0);
            
            break; // do nothing
        case S_PRIME:
            analogWrite(l_red_led, 255);
            digitalWrite(l_release_valve, HIGH);
            analogWrite(l_dose_pwm, 255);
            analogWrite(l_air_pwm, 255);
            digitalWrite(sound_boardFX, HIGH);
            sound_time = millis();

            if(millis() - sound_time > SOUND_DURATION)
            {
                digitalWrite(sound_boardFX, LOW);
            }

            if(millis() - last_time > PRIME_DURATION)
            {
                analogWrite(l_dose_pwm, 0);
                flags |= FLAG_PRIMED;
            }

            if(millis() - last_time > PUMP_DURATION)
            {
                analogWrite(l_air_pwm, 0);
                flags |= FLAG_PUMPED;
            }

            if(flags == (FLAG_PRIMED | FLAG_PUMPED))
            {
                flags = 0;
                last_time = millis();
                sneeze_state = S_HOLD;
                Serial.println("HOLD");
            }
            break;
        case S_HOLD:
            if(millis() - last_time > HOLD_DURATION)
            {
                last_time = millis();
                sneeze_state = S_RELEASE;
                Serial.println("RELEASE");
            }
            if(millis() - sound_time > SOUND_DURATION)
            {
                digitalWrite(sound_boardFX, LOW);
            }
            break;
        case S_RELEASE:
            digitalWrite(l_release_valve, LOW);
            if((millis() - last_time > RELEASE_DURATION)&&(millis()))
            {
                last_time = millis();
                digitalWrite(l_release_valve, HIGH);
                analogWrite(l_green_led, 0);
                sneeze_state = S_IDLE;
                Serial.println("IDLE");
            }
            break;
    }
}