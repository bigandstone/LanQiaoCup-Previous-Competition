#ifndef __key_h__
#define __key_h__

#include "main.h"
#include "gpio.h"

typedef enum{
    UNPRESSED,
    PRESSED,
}KeyState;

typedef enum{
    NONE,
    SHORT,
    LONG,
}KeyFlag;

typedef struct {
    KeyState state;
    
    GPIO_TypeDef* port;
    uint16_t pin;
    uint8_t long_able;
    uint32_t time_stamp;
    
    KeyFlag key_flag;
}Key;

extern Key key1, key2, key3, key4;

void keys_init();
void keys_process();
void key_get_flag(Key* hkey, KeyFlag* key_flag);

void key_init(Key* hkey, GPIO_TypeDef* port, uint16_t pin, uint8_t long_able);
void key_process(Key* hkey);

#endif
