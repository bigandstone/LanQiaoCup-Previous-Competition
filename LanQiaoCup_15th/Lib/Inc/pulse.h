#ifndef __pulse_h__
#define __pulse_h__

#include "main.h"
#include "tim.h"

typedef struct {
    int freq_a, freq_b; //hz and us
    int period_a, period_b;
    
    uint16_t pd;
    uint16_t ph;
    int px;
    
    uint32_t nda, ndb, nha, nhb;
    
}Pulse;

extern Pulse pulse;

void pulse_init();
void pulse_get();

void pulse_updata();
void pulse_record_nd();
void pulse_record_np();

void pulse_dec_px();
void pulse_dec_ph();
void pulse_dec_pd();
void pulse_add_px();
void pulse_add_ph();
void pulse_add_pd();

#endif
