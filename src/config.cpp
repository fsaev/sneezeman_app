#include "config.h"
#include <EEPROM.h>
#include <string.h>

config_t config;

void init_config(void)
{
    memset(&config, 0, sizeof(config));
    read_config();
    if(config.version == 0){
        default_config();
    }
}

void default_config(void)
{
    config.version = 1;
    config.data = {.vl53_update_interval = 100, .vl53_trigger_distance = 150, .vl53_trigger_count = 5};
}

void read_config(void)
{

}

void write_config(void)
{

}

config_t* get_config(void)
{
    return &config;
}