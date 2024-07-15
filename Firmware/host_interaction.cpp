//
// Created by lselter on 15/07/2024.
//



//#include "ultralcd.h"


#ifdef __cplusplus

#include <stdint.h>


#include "Configuration.h"
#include "config.h"
#include "Marlin.h"

#if defined(BUFFERED_LCD)
#warning "BUFFERED_LCD"
#include "host_interaction.h"

char lcd_buffer[(LCD_WIDTH + 1)][ LCD_HEIGHT];
char* lcd_buffer_flat = (char*)lcd_buffer;


void write_char_to_buffer(char c, uint8_t address) {
    address += address/LCD_WIDTH;
    lcd_buffer_flat[address] = c;
}
void echo_current_display() {
    for (uint_fast8_t i = 0; i < LCD_HEIGHT; i++) {
        // Calculate the start index of the current line in lcd_buffer
        uint8_t startIndex =( i * LCD_WIDTH) + i; //account for eol null char
        SERIAL_ECHOLN(lcd_buffer_flat[startIndex]);
    }
}

#endif // END BUFFERED_LCD
#if defined(HOST_INTERACTION)
extern  uint8_t lcd_click_trigger;
extern bool lcd_longpress_trigger;
extern int8_t lcd_encoder_diff;
void press_button() {
    lcd_click_trigger = 1;

}
void long_press_button(){
    lcd_longpress_trigger =1;

}
void change_encoder(const int_least8_t value,const uint8_t pulses) {
    //update the encoder status with the new value multiplied by the number of pulses per step
    lcd_encoder_diff += value * pulses;

}
#endif // END HOST_INTERACTION

#endif // END C++ only section
