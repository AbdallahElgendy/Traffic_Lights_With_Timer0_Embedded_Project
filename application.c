/* 
 * File:   application.c
 * Author: Abdallah Saad
* Created on August 7, 2022, 10:39 PM
 */

#include "application.h"


timer0_t timer0_counter_obj = {
    .TMR0_InterruptHandler = NULL ,
    .timer0_mode = TIMER0_COUNTER_MODE,
    .timer0_counter_edge = TIMER0_COUNTER_RISING_EDGE_CFG,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
    .timer0_preload_value = 0
};

uint8 flag = 0 ; 
uint16 counter_value ; 



int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    ret = Timer0_Init(&timer0_counter_obj);
    ret = lcd_8bit_send_string_pos(&lcd_1, 1, 5, "Traffic Lights");
    ret = lcd_8bit_send_string_pos(&lcd_1, 3, 1, "Remaining ");
    ret = lcd_8bit_send_string_pos(&lcd_1, 3, 14, "Sec");
    
    while(1){
        ret =Timer0_Read_Value(&timer0_counter_obj , &counter_value) ; 
        
        if((counter_value <= 10)&&(flag == 0)){
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 11,((10 - counter_value)/10+'0'));
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 12,((10 - counter_value)%10+'0'));
            ret = led_turn_on(&led3) ; 
            ret = led_turn_off(&led2) ; 
            ret = led_turn_off(&led1) ; 
            
            if( counter_value == 10){
                flag ++; 
                ret = Timer0_Write_Value(&timer0_counter_obj , 0) ; 
            }
        }
        else if((counter_value <= 7)&&(flag == 1)){
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 11,((7 - counter_value)/10+'0'));
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 12,((7 - counter_value)%10+'0'));
            ret = led_turn_on(&led2) ; 
            ret = led_turn_off(&led3) ; 
            ret = led_turn_off(&led1) ; 
            if( counter_value == 7){
                flag ++; 
                ret = Timer0_Write_Value(&timer0_counter_obj , 0) ; 
            }
        }
        else if((counter_value <= 5)&&(flag == 2)){
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 11,((5 - counter_value)/10+'0'));
            ret = lcd_8bit_send_char_data_pos(&lcd_1, 3, 12,((5 - counter_value)%10+'0'));
            ret = led_turn_on(&led1) ; 
            ret = led_turn_off(&led2) ; 
            ret = led_turn_off(&led3) ; 
            if( counter_value == 5){
                flag  = 0 ; 
                ret = Timer0_Write_Value(&timer0_counter_obj , 0) ;  
            }
        }
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize() ; 
    
}




