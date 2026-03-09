#ifndef __ui_h__
#define __ui_h__

#include "main.h"
#include "lcd.h"
#include "stdio.h"
#include "pulse.h"

typedef enum{
    DATA1,
    DATA2,
    PARA,
    RECO,
}Page;

typedef struct{
    Page current_page;
}Ui;

extern Ui ui;
extern int cnt;

void ui_init();
void ui_next_page();
void ui_switch_page();
void ui_show_updata();

void ui_show_data1();
void ui_show_data2();
void ui_show_para();
void ui_show_record();
void ui_show_buff();

#endif
