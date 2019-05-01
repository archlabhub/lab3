#ifndef lcd_char_included

#define lcd_char_included
#include "lcd_utils.h"

/* functions to write strings and characters to the lcd */
void lcd_writeString(const char *string, u_char x, u_char yMajor);
void lcd_writeChar(char c, u_char x, u_char yMajor);

#endif // lcd_char_included
