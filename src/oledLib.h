#if !defined(OLED_LIB_H)
#define OLED_LIB_H

#if defined(ARDUINO)
#include "U8X8Lib.h"
#else

#if defined(PICO_BUILD)
#endif	/* PICO_BUILD */

#if define(ESP_PLATFORM)
#endif	/* ESP_PLATFORM */

#endif	/* ARDUINO */

size_t drawString(char x, char y, const char *str);
void newScreen(const char* title);
void clearLine(char line);
void erase(char x, char y, char len);
size_t drawNumber(char x, char y, int val);
size_t drawNumber(char x, char y, unsigned long val);
size_t drawFloat(char x, char y, float floatNumber, uint8_t dp);

#endif	/* OLED_LIB_H */
