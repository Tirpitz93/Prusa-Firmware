//
// Created by lselter on 15/07/2024.
//

#ifndef PRUSA_FIRMWARE_HOST_INTERACTION_H
#define PRUSA_FIRMWARE_HOST_INTERACTION_H
#ifdef __cplusplus
#define  EXPORT_C extern "C"
#else
#define  EXPORT_C
#endif
#ifdef __cplusplus

/*
 * M940 - Echo contents of LCD display
 */
void echo_current_display();

/*
 * M941 Store a character in the lcd buffer for later retrieval
 */
void write_char_to_buffer(char c, uint8_t address);


/*
 * M941 Send encoder input to the firmware
 */
void change_encoder(int_least8_t value, uint8_t pulses);

/*
 * M941 Send button press to the firmware
 */
void press_button();

/*
 * M941 end long button press to the firmware
 */
void long_press_button();


#endif // END C++ only section

#endif //PRUSA_FIRMWARE_HOST_INTERACTION_H
