#include "vl53.h"
#include "config.h"

#include "Adafruit_VL53L0X.h"
#include <Wire.h>

static Adafruit_VL53L0X lox = Adafruit_VL53L0X();
static config_t* l_config;

static uint8_t threshold_count = 0;
static uint8_t sneeze_trigger = 0;

static uint32_t last_time;

void init_vl53(void)
{
    l_config = get_config();
    if (!lox.begin(VL53L0X_I2C_ADDR, false, &Wire, Adafruit_VL53L0X::VL53L0X_SENSE_DEFAULT)) {
        while(1);
    }
}

uint16_t get_dist_mm_vl53(void)
{
    VL53L0X_RangingMeasurementData_t measure;

    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
        return measure.RangeMilliMeter;
    } else {
        return 0;
    }
}

uint8_t trigger_get_vl53(void)
{
    return sneeze_trigger;
}

void trigger_reset_vl53(void)
{
    sneeze_trigger = 0;
}

void tick_vl53(void)
{
    if(millis() - last_time > l_config->data.vl53_update_interval) {
        last_time = millis();
        if(sneeze_trigger == 0){
            if(get_dist_mm_vl53() < l_config->data.vl53_trigger_distance)
            {
                if(threshold_count++ > l_config->data.vl53_trigger_count){
                    sneeze_trigger = 1;
                    threshold_count = 0;
                }
            }else{
                threshold_count = 0;
            }
        }
    }
}