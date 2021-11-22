#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

struct data_def
{
    uint32_t vl53_update_interval;
    uint32_t vl53_trigger_distance;
    uint8_t vl53_trigger_count;
};

typedef struct
{
    uint8_t version;
    struct data_def data;
    uint16_t crc;
} __attribute__((packed)) config_t;

void init_config(void);
void default_config(void);

void read_config();
void write_config();

config_t* get_config();


#endif // CONFIG_H