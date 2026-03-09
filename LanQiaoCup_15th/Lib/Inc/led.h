#ifndef __led_h__
#define __led_h__

#include "main.h"
#include "gpio.h"

typedef struct{
    uint8_t state;
}Led;

extern Led led;

void led_init();
void led_set_bit(uint8_t LD, uint8_t state);

void led_set();

#endif
