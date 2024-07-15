#define CATCH_CONFIG_MAIN

#include <cstring>
#include "catch2/catch_test_macros.hpp"

#define SERIAL_ECHOLN(x) printf("%s\n", x)

#include "../Firmware/host_interaction.h"

#define LCD_WIDTH  20
#define LCD_HEIGHT  4

char lcd_buffer[(LCD_WIDTH + 1) * LCD_HEIGHT];
int8_t lcd_encoder_diff;
uint8_t lcd_click_trigger;
bool lcd_longpress_trigger;

class HostInteractionFixture {
protected:
    void SetUp() {
        // Reset the lcd_buffer, lcd_click_trigger, and lcd_encoder_diff before each test
        memset(lcd_buffer, 0, sizeof(lcd_buffer));
        lcd_click_trigger = 0;
        lcd_encoder_diff = 0;
        lcd_longpress_trigger = 0;

    }
};


TEST_CASE_METHOD(HostInteractionFixture, "WriteCharToBuffer_ShouldWriteCharAtCorrectPositionLN1", "[HostInteraction]") {
    SetUp();
    write_char_to_buffer('X', 5);
    size_t expectedPosition = 5 + 5 / LCD_WIDTH;
    REQUIRE(lcd_buffer[expectedPosition] == 'X');
}


TEST_CASE_METHOD(HostInteractionFixture, "WriteCharToBuffer_ShouldWriteCharAtCorrectPositionLN2", "[HostInteraction]") {
    SetUp();
    write_char_to_buffer('X', 23);
    write_char_to_buffer('Y', 20);

    size_t expectedPosition = 24;
    REQUIRE(lcd_buffer[expectedPosition] == 'X');
    REQUIRE(lcd_buffer[20] == '\0');
    REQUIRE(lcd_buffer[21] == 'Y');
}

TEST_CASE_METHOD(HostInteractionFixture, "WriteCharToBuffer_ShouldWriteCharAtCorrectPositionLN3", "[HostInteraction]") {
    SetUp();
    write_char_to_buffer('X', 43);

    size_t expectedPosition = 45;
    REQUIRE(lcd_buffer[expectedPosition] == 'X');
}

TEST_CASE_METHOD(HostInteractionFixture, "WriteCharToBuffer_ShouldWriteCharAtCorrectPositionLN4", "[HostInteraction]") {
    SetUp();
    write_char_to_buffer('X', 66);

    size_t expectedPosition = 69;
    REQUIRE(lcd_buffer[expectedPosition] == 'X');
}

TEST_CASE_METHOD(HostInteractionFixture, "PressButton_ShouldSetClickTriggerToTrue", "[HostInteraction]") {
    SetUp();
    press_button();
    REQUIRE(lcd_click_trigger == 1);
}

TEST_CASE_METHOD(HostInteractionFixture, "LongPressButton_ShouldSetLongPressTriggerToTrue", "[HostInteraction]") {
    SetUp();
    long_press_button();
    REQUIRE(lcd_longpress_trigger == 1);
}

TEST_CASE_METHOD(HostInteractionFixture, "ChangeEncoder_ShouldUpdateEncoderDiff", "[HostInteraction]") {
    SetUp();
    lcd_encoder_diff = 0;
    change_encoder(5, 1);
    REQUIRE(lcd_encoder_diff == 5);
    change_encoder(-3, 1);
    REQUIRE(lcd_encoder_diff == 2);
    change_encoder(1, 2);
    REQUIRE(lcd_encoder_diff == 4);
    change_encoder(-2, 2);
    REQUIRE(lcd_encoder_diff == 0);
}
