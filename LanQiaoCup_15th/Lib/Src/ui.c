#include "ui.h"

Ui ui ={
    .current_page = DATA1,
}; 

static char buff_1[30];
static char buff_2[30];
static char buff_3[30];
static char buff_4[30];
static char buff_5[30];

void ui_init(){
    LCD_Init();
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    
    ui_show_updata();
}

void ui_next_page(){
    switch (ui.current_page)
    {
    	case DATA1:ui.current_page = PARA;
    		break;
    	case DATA2:ui.current_page = PARA;
    		break;
    	case PARA:ui.current_page = RECO;
    		break;
    	case RECO:ui.current_page = DATA1;
    		break;
    }
    LCD_Clear(Black);
}

void ui_switch_page(){
    if(ui.current_page == DATA1){
        ui.current_page = DATA2;
    }
    else if(ui.current_page == DATA2){
        ui.current_page = DATA1;
    }
}

void ui_show_updata(){
    switch (ui.current_page)
    {
    	case DATA1:ui_show_data1();
    		break;
    	case DATA2:ui_show_data2();
    		break;
    	case PARA:ui_show_para();
    		break;
    	case RECO:ui_show_record();
    		break;
    }
}

void ui_show_data1(){
    sprintf(buff_1, "        DATA");
    
    if(pulse.freq_a < 1000) sprintf(buff_2, "     A = %dHz     ",pulse.freq_a);
    else sprintf(buff_2, "     A = %.2fKHz     ",(float)pulse.freq_a/1000.00);
    if(pulse.freq_a < 0) sprintf(buff_2, "     A = NULL     ");
    
    if(pulse.freq_b < 1000) sprintf(buff_3, "     B = %dHz     ",pulse.freq_b);
    else sprintf(buff_3, "     B = %.2fKHz     ",(float)pulse.freq_b/1000.00);
    if(pulse.freq_b < 0) sprintf(buff_3, "     B = NULL     ");
    
    sprintf(buff_4, "                    ");
    sprintf(buff_5, "                    ");
    ui_show_buff();
}

void ui_show_data2(){
    sprintf(buff_1, "        DATA");
    
    if(pulse.period_a < 1000) sprintf(buff_2, "     A = %duS     ",pulse.period_a);
    else sprintf(buff_2, "     A = %.2fmS     ",(float)pulse.period_a/1000.00);
    if(pulse.period_a < 0) sprintf(buff_2, "     A = NULL     ");
    
    if(pulse.period_b < 1000) sprintf(buff_3, "     B = %duS     ",pulse.period_b);
    else sprintf(buff_3, "     B = %.2fmS     ",(float)pulse.period_b/1000.00);
    if(pulse.period_b < 0) sprintf(buff_3, "     B = NULL     ");
    
    sprintf(buff_4, "                    ");
    sprintf(buff_5, "                    ");
    ui_show_buff();
}

void ui_show_para(){
    sprintf(buff_1, "        PARA");
    
    sprintf(buff_2, "     PD = %dHz     ",pulse.pd);
    sprintf(buff_3, "     PH = %dHz     ",pulse.ph);
    sprintf(buff_4, "     PX = %dHz     ",pulse.px);
    sprintf(buff_5, "                    ");
    
    ui_show_buff();
}

void ui_show_record(){
    sprintf(buff_1, "        RECO");
    
    sprintf(buff_2, "     NDA =%d     ",pulse.nda);
    sprintf(buff_3, "     NDB =%d     ",pulse.ndb);
    sprintf(buff_4, "     NHA =%d     ",pulse.nha);
    sprintf(buff_5, "     NHB =%d     ",pulse.nhb);
    
    ui_show_buff();
}

void ui_show_buff(){
    LCD_DisplayStringLine(Line1, (u8*)buff_1);
    
    LCD_DisplayStringLine(Line3, (u8*)buff_2);
    LCD_DisplayStringLine(Line4, (u8*)buff_3);
    LCD_DisplayStringLine(Line5, (u8*)buff_4);
    LCD_DisplayStringLine(Line6, (u8*)buff_5);
}