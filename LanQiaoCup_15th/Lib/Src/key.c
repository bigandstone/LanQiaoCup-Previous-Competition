#include "key.h"

Key key1, key2, key3, key4;

void keys_init(){
    key_init(&key1, GPIOB, GPIO_PIN_0, 0);
    key_init(&key2, GPIOB, GPIO_PIN_1, 0);
    key_init(&key3, GPIOB, GPIO_PIN_2, 1);
    key_init(&key4, GPIOA, GPIO_PIN_0, 0);
}

void keys_process(){
    key_process(&key1);
    key_process(&key2);
    key_process(&key3);
    key_process(&key4);
}
void key_init(Key* hkey, GPIO_TypeDef* port, uint16_t pin, uint8_t long_able){
    hkey->key_flag = NONE;
    hkey->long_able = long_able;
    hkey->port = port;
    hkey->pin = pin;
    hkey->state = UNPRESSED;
    hkey->time_stamp = 0;
}

void key_process(Key* hkey){
    switch (hkey->state)
    {
    	case UNPRESSED:
            if(HAL_GPIO_ReadPin(hkey->port, hkey->pin) == GPIO_PIN_RESET){
                hkey->state = PRESSED;
                hkey->time_stamp = 0;
            }
    		break;
    	case PRESSED:
            if(HAL_GPIO_ReadPin(hkey->port, hkey->pin) == GPIO_PIN_RESET){
                hkey->time_stamp ++;
                break;
            }
            hkey->state = UNPRESSED;
            if(hkey->time_stamp < 3){
                break;
            }
            if(hkey->long_able && hkey->time_stamp >= 500){
                hkey->key_flag = LONG;
                break;
            }
            hkey->key_flag = SHORT;
    		break;
    }
}

void key_get_flag(Key* hkey, KeyFlag* key_flag){
    *key_flag = hkey->key_flag;
    hkey->key_flag = NONE;
}