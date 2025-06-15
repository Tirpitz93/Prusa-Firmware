#ifndef NOZZLE_DIAMETER_H
#define NOZZLE_DIAMETER_H
#include <eeprom.h>

enum class ClNozzleDiameter : uint_least8_t {
    _Diameter_150 = 15,
    _Diameter_250 = 25,
    _Diameter_400 = 40,
    _Diameter_600 = 60,
    _Diameter_800 = 80,
    _Diameter_1000 = 100,
    _Diameter_1200 = 120,
    _Diameter_1400 = 140,
    _Diameter_Undef = EEPROM_EMPTY_VALUE
};

struct ClNozzleDiameterInfo {
    ClNozzleDiameter diameter;
    uint16_t diameter_uM;
    const char *label;
};

extern const ClNozzleDiameterInfo nozzle_diameter_info[];
extern const size_t nozzle_diameter_info_count;

void lcd_nozzle_diameter_cycle(void);

const char *nozzle_diameter_label(ClNozzleDiameter d);

#define SETTINGS_NOZZLE \
    do { \
        MENU_ITEM_TOGGLE_P(_T(MSG_NOZZLE_DIAMETER), nozzle_diameter_label(oNozzleDiameter), lcd_nozzle_diameter_cycle); \
    } while (0)

#endif //NOZZLE_DIAMETER_H
