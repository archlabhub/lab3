#ifndef string_utils_included
#define string_utils_included

/* integer to ascii, any radix 2..36 */
char digitToAscii(unsigned digit);

char* itoa(int value, char* result, int radix);
char* utoa(int value, char* result, int radix);

#endif // string_utils_included
