#if !defined(OLED_LIB_H)
#define OLED_LIB_H

#if defined(ARDUINO)

#include "U8X8Lib.h"

#define U8X8_DrawString(x, y, str) u8x8.drawString(x, y, str)
#define U8X8_Clear() u8x8.llear()

#else

#if defined(ESP_PLATFORM)

#include "u8x8.h"

inline u8x8_t u8x8;

#define U8X8_DrawString(x, y, str) u8x8_DrawString(&u8x8, x, y, str)
#define U8X8_Clear() u8x8_ClearDisplay(&u8x8)

#endif	/* ESP_PLATFORM */

#if defined(PICO_BUILD)

#include "u8x8.h"

inline u8x8_t u8x8;

#define U8X8_DrawString(x, y, str) u8x8_DrawString(&u8x8, x, y, str)
#define U8X8_Clear() u8x8_ClearDisplay(&u8x8)

#endif	/* PICO_BUILD */

#endif	/* ARDUINO */

size_t drawString(char x, char y, const char *str);
void newScreen(const char* title);
void clearLine(char line);
void erase(char x, char y, char len);
size_t drawNumber(char x, char y, int val);
size_t drawNumber(char x, char y, unsigned long val);
size_t drawFloat(char x, char y, float floatNumber, uint8_t dp);

#endif	/* OLED_LIB_H */
