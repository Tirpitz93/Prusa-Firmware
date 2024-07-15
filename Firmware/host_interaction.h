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

void echo_current_display();

void change_encoder(int_least8_t value);
void press_button();
void long_press_button();


#endif // END C++ only section

#endif //PRUSA_FIRMWARE_HOST_INTERACTION_H
