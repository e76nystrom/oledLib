#include "oledLib.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>

inline char *LTOA(long val, char *s, int radix)
{
 sprintf(s, "%ld", val);
 return s;
}

size_t drawString(char x, char y, const char *str)
{
 U8X8_DrawString(x, y, str);
#if 0
 printf("x ");
 printf(static_cast<int>(x));
 printf(" y ");
 printf(static_cast<int>(y));
 printf(" \"");
 printf(str);
 printfln("\"");
#endif
 return strlen(str);
}

void newScreen(const char* title)
{
#if 0
 printf("newScreen ");
 printf(title);
 printf("\n");
#endif
 U8X8_Clear();
 drawString(0, 0, title);
}

void clearLine(char line)
{
 drawString(0, line, "                ");
#if 0
 printf("clearLine %d", static_cast<int>(line));
#endif
}

void erase(char x, char y, char len)
{
 while (len != 0)
 {
  U8X8_DrawString(x, y, " ");
  y += 1;
  len -= 1;
 }
}

size_t drawNumber(char x, char y, int val)
{
 char buf[6];
 itoa(val, buf, 10);
 drawString(x, y, buf);
#if 0
 printf(val);
 printf("\n");
#endif
 return strlen(buf);
}

size_t drawNumber(char x, char y, unsigned long val)
{
 char buf[12];
 LTOA(static_cast<long>(val), buf, 10);
 drawString(x, y, buf);
#if 0
 printf(val);
 printf("\n");
#endif
 return strlen(buf);
}

/***************************************************************************************
** Function name:           drawFloat
** Descriptions:            drawFloat, prints 7 non-zero digits maximum
***************************************************************************************/
// from https://github.com/Bodmer/TFT_ST7735
// Adapted to assemble and print a string, this permits alignment relative to a datum
// looks complicated but much more compact and actually faster than using print class

size_t drawFloat(char x, char y, float floatNumber, uint8_t dp)
{
  char str[14];               // Array to contain decimal string
  uint8_t ptr = 0;            // Initialize pointer for array
  uint8_t  digits = 1;        // Count the digits to avoid array overflow
  float rounding = 0.5;       // Round up down delta

  if (dp > 7)
   dp = 7;			// Limit the size of decimal portion

  // Adjust the rounding value
  for (uint8_t i = 0; i < dp; ++i) rounding /= 10.0;

  if (floatNumber < -rounding)    // add sign, avoid adding - sign to 0.0!
  {
    str[ptr++] = '-';	    // Negative number
    str[ptr] = 0;	    // Put a null in the array as a precaution
    digits = 0;		    // Set digits to 0 to compensate so pointer value can be used later
    floatNumber = -floatNumber; // Make positive
  }

  floatNumber += rounding; // Round up or down

  // For error put ... in string and return (all TFT_ST7735 library fonts contain . character)
  if (floatNumber >= static_cast<float>(2147483647)) {
    strcpy(str, "...");
    return drawString(x, y, str);
  }
  // No chance of overflow from here on

  // Get integer part
  auto temp = static_cast<unsigned long>(floatNumber);

  // Put integer part into array
  LTOA(static_cast<long>(temp), str + ptr, 10);

  // Find out where the null is to get the digit count loaded
  while (static_cast<uint8_t>(str[ptr]) != 0) ptr++; // Move the pointer along
  digits += ptr;                  // Count the digits

  str[ptr++] = '.'; // Add decimal point
  str[ptr] = '0';   // Add a dummy zero
  str[ptr + 1] = 0; // Add a null but don't increment pointer so it can be overwritten

  // Get the decimal portion
  floatNumber = floatNumber - static_cast<float>(temp);

  // Get decimal digits one by one and put in array
  // Limit digit count so we don't get a false sense of resolution
  uint8_t i = 0;
  while ((i < dp) && (digits < 9)) // while (i < dp) for no limit but array size must be increased
  {
    i++;
    floatNumber *= 10;       // for the next decimal
    temp = static_cast<unsigned long>(floatNumber);      // get the decimal
    LTOA(static_cast<long>(temp), str + ptr, 10);
    ptr++;
    digits++;         // Increment pointer and digits count
    floatNumber -= static_cast<float>(temp);     // Remove that digit
  }
  
  // Finally we can plot the string and return pixel length
  return drawString(x, y, str);
}
