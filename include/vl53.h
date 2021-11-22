#ifndef VL53_H
#define VL53_H

#include <stdint.h>

void init_vl53(void);
uint16_t get_dist_vl53(void);

uint8_t trigger_get_vl53(void);
void trigger_reset_vl53(void);

void tick_vl53(void);

#endif // VL53_H