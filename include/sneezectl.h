#ifndef SNEEZECTL_H
#define SNEEZECTL_H

enum sneeze_states
{
    S_IDLE,
    S_PRIME,
    S_PUMP,
    S_HOLD,
    S_RELEASE
};

void init_sneeze(int dose_pwm, int air_pwm, int release_valve);
void start_sneeze(void);
enum sneeze_states get_sneeze_state(void);
void tick_sneeze(void);

#endif // SNEEZECTL_H