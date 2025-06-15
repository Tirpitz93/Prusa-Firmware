#include "nozzle_diameter.h"
#include <eeprom.h>
#include <string.h>

extern ClNozzleDiameter oNozzleDiameter;

constexpr char PROGMEM nd_015[] = "0.15";
constexpr char PROGMEM nd_025[] = "0.25";
constexpr char PROGMEM nd_040[] = "0.40";
constexpr char PROGMEM nd_060[] = "0.60";
constexpr char PROGMEM nd_080[] = "0.80";
constexpr char PROGMEM nd_100[] = "1.00";
constexpr char PROGMEM nd_120[] = "1.20";
constexpr char PROGMEM nd_140[] = "1.40";

const ClNozzleDiameterInfo nozzle_diameter_info[] = {
#ifdef NOZZLE_DIAMETER_EXTENDED
    {ClNozzleDiameter::_Diameter_150, 150, nd_015},
#endif
    {ClNozzleDiameter::_Diameter_250, 250, nd_025},
    {ClNozzleDiameter::_Diameter_400, 400, nd_040},
    {ClNozzleDiameter::_Diameter_600, 600, nd_060},
    {ClNozzleDiameter::_Diameter_800, 800, nd_080},
#ifdef NOZZLE_DIAMETER_EXTENDED
    {ClNozzleDiameter::_Diameter_1000, 1000, nd_100},
    {ClNozzleDiameter::_Diameter_1200, 1200, nd_120},
    {ClNozzleDiameter::_Diameter_1400, 1400, nd_140},
#endif
};
const size_t nozzle_diameter_info_count = sizeof(nozzle_diameter_info) / sizeof(nozzle_diameter_info[0]);

const char *nozzle_diameter_label(ClNozzleDiameter d) {
    for (size_t i = 0; i < nozzle_diameter_info_count; ++i) {
        if (nozzle_diameter_info[i].diameter == d)
            return nozzle_diameter_info[i].label;
    }
    // fallback
    return nd_040;
}

void lcd_nozzle_diameter_cycle(void) {
    size_t idx = 0;
    for (; idx < nozzle_diameter_info_count; ++idx) {
        if (nozzle_diameter_info[idx].diameter == oNozzleDiameter)
            break;
    }
    // Move to next, wrap around
    idx = (idx + 1) % nozzle_diameter_info_count;
    oNozzleDiameter = nozzle_diameter_info[idx].diameter;
    uint16_t nDiameter = nozzle_diameter_info[idx].diameter_uM;

    eeprom_update_byte_notify((uint8_t *) EEPROM_NOZZLE_DIAMETER, (uint8_t) oNozzleDiameter);
    eeprom_update_word_notify((uint16_t *) EEPROM_NOZZLE_DIAMETER_uM, nDiameter);
}
