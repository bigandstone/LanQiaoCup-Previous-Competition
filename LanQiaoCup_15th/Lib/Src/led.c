#include "led.h"

Led led = {
    .state = 0xFF,
};

void led_init(){
    led_set();
}

void led_set_bit(uint8_t LD, uint8_t state){
    if(state){
        led.state |= (0x01 << (LD - 1));
    }else{
        led.state &= ~(0x01 << (LD - 1));
    }
    led_set();
}

void led_set(){
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    for(uint8_t i = 0; i < 8; i++){
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 << i, (led.state & (0x01 << i)) == 0? GPIO_PIN_RESET:GPIO_PIN_SET);
    }
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}