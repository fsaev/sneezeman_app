#include <Arduino.h>
#include "sneezectl.h"

#define PRIME_DURATION 1750
#define PUMP_DURATION 1750
#define HOLD_DURATION 1000
#define RELEASE_DURATION 1000

uint8_t l_dose_pwm;
uint8_t l_air_pwm;
uint8_t l_release_valve;

uint32_t last_time = 0;
uint8_t flags = 0;

#define FLAG_PRIMED 1
#define FLAG_PUMPED 2

enum sneeze_states sneeze_state = S_IDLE;

void init_sneeze(int dose_pwm, int air_pwm, int release_valve)
{
    pinMode(dose_pwm, OUTPUT);
    pinMode(air_pwm, OUTPUT);
    pinMode(release_valve, OUTPUT);

    l_dose_pwm = dose_pwm;
    l_air_pwm = air_pwm;
    l_release_valve = release_valve;
}

void start_sneeze(void)
{
    if(sneeze_state != S_IDLE)
    {
        last_time = millis();
        sneeze_state = S_PRIME;
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
            break; // do nothing
        case S_PRIME:
            analogWrite(l_dose_pwm, 255);
            analogWrite(l_air_pwm, 255);

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
            }
            break;
        case S_HOLD:
            if(millis() - last_time > HOLD_DURATION)
            {
                last_time = millis();
                sneeze_state = S_RELEASE;
            }
            break;
        case S_RELEASE:
            digitalWrite(l_release_valve, HIGH);

            if(millis() - last_time > PRIME_DURATION)
            {
                digitalWrite(l_release_valve, LOW);
                sneeze_state = S_IDLE;
            }
            break;

}