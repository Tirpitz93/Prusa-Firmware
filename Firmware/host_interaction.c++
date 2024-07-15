//
// Created by lselter on 15/07/2024.
//

#include <stdint.h>
#include "host_interaction.h"
#include "Marlin.h"

#ifdef __cplusplus
extern int8_t  lcd_encoder_diff;    // Encoder diff
extern uint8_t  lcd_click_trigger;
void echo_current_display() {
    char line[LCD_WIDTH+1];
    for (uint_fast8_t i = 0; LCD_HEIGHT > i; i++) {
        strcpy(line, lcd_buffer + i*LCD_WIDTH);
        SERIAL_ECHO(line);
        if (i % LCD_WIDTH == 0) {
            SERIAL_ECHOLN("");
        }
    }
}

void press_button() {
    lcd_click_trigger = 1;

}
void long_press_button(){
    lcd_longpress_trigger =1;

}
void change_encoder(int_least8_t value) {
    //update the encoder status with the new value multiplied by the number of pulses per step
    lcd_encoder_diff += value*ENCODER_PULSES_PER_STEP;
//    lcd_knob_update();
}


#endif // END C++ only section
