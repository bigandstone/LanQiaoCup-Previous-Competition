#include "pulse.h"

Pulse pulse = {
    .freq_a = 0,
    .freq_b = 0,
    .period_a = 0,
    .period_b = 0,
    
    .pd = 1000,
    .ph = 5000,
    .px = 0,
    
    .nda = 0,
    .ndb = 0, 
    .nha = 0, 
    .nhb = 0, 
};

static uint8_t nha_flag = 0;
static uint8_t nhb_flag = 0;
static uint8_t nda_flag = 0;
static uint8_t ndb_flag = 0;

static int raw_freq_a = 0;
static int raw_freq_b = 0;


static int freq_a_min = 0;
static int freq_a_max = 0;
static int freq_b_min = 0;
static int freq_b_max = 0;

void pulse_init(){
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
}

void pulse_get(){
    pulse_updata();
    pulse_record_nd();
    pulse_record_np();
}

void pulse_updata(){
    pulse.freq_a = raw_freq_a;
    pulse.freq_b = raw_freq_b;
    pulse.period_a = 1000000 / pulse.freq_a;//uS
    pulse.period_b = 1000000 / pulse.freq_b;//uS
}

void pulse_record_nd(){
    static uint16_t time_stamp = 0 ;
    if(time_stamp == 0){
        freq_a_min = raw_freq_a;
        freq_a_max = raw_freq_a;
        freq_b_min = raw_freq_b;
        freq_b_max = raw_freq_b;
        ndb_flag = 0;
        nda_flag = 0;
    }
    time_stamp ++;
    
    if(time_stamp >= 300) time_stamp = 0;
    freq_a_min = pulse.freq_a < freq_a_min? pulse.freq_a:freq_a_min;
    freq_b_min = pulse.freq_b < freq_b_min? pulse.freq_b:freq_b_min;
    freq_a_max = pulse.freq_a > freq_a_max? pulse.freq_a:freq_a_max;
    freq_b_max = pulse.freq_b > freq_b_max? pulse.freq_b:freq_b_max;
    
    if(freq_a_max - freq_a_min > pulse.pd && nda_flag == 0){
        pulse.nda ++;
        nda_flag = 1;
    }
    if(freq_b_max - freq_b_min > pulse.pd && ndb_flag == 0){
        pulse.ndb ++;
        ndb_flag = 1;
    }
}

void pulse_record_np(){
    if(pulse.freq_a > pulse.ph && nha_flag == 0){
        pulse.nha ++;
        nha_flag = 1;
    }else if(pulse.freq_a < pulse.ph && nha_flag == 1){
        nha_flag = 0;
    }
    if(pulse.freq_b > pulse.ph && nhb_flag == 0){
        pulse.nhb ++;
        nhb_flag = 1;
    }else if(pulse.freq_b < pulse.ph && nhb_flag == 1){
        nhb_flag = 0;
    }
}

void pulse_add_pd(){
    pulse.pd += 100;
    if(pulse.pd >= 1000) pulse.pd = 1000; 
}

void pulse_add_ph(){
    pulse.ph += 100;
    if(pulse.ph >= 10000) pulse.ph = 10000; 
}

void pulse_add_px(){
    pulse.px += 100;
    if(pulse.px >= 1000) pulse.px = 1000; 
}

void pulse_dec_pd(){
    pulse.pd -= 100;
    if(pulse.pd <= 100 ) pulse.pd = 100; 
}

void pulse_dec_ph(){
    pulse.ph -= 100;
    if(pulse.ph <= 1000) pulse.ph = 1000;
}

void pulse_dec_px(){
    pulse.px -= 100;
    if(pulse.px <= -1000) pulse.px = -1000; 
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){//1MHz every num
    if(htim == &htim2){
        raw_freq_a = 1000000 / TIM2->CNT + pulse.px;//Hz
        TIM2->CNT = 0;
    }else if(htim == &htim3){
        raw_freq_b = 1000000 / TIM3->CNT + pulse.px;//Hz
        TIM3->CNT = 0;
    }
}
