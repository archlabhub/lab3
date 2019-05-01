#include "string_utils.h"

char digitToAscii(unsigned digit)
{
  char symbol;
  if (digit < 10)
    symbol = digit + '0';
  else 
    symbol = digit - 10 + 'a';
  return symbol;
}

char* utoa(unsigned value, char* result, int radix) {
  char revString[10];
  char *revPtr = rString, *resultTmp = result;


  if (radix < 2 || radix > 36) {	/* radix invalid? */
    *result = '\0'; 		/* just return empty string */
  } else {			/* do conversion */

    /* convert one digit at a time, in reverse */
    do {		 
      *(revPtr++) = digitToAscii(value % radix);
      value /= radix;
    } while  (value);

    /* copy result */
    while (revPtr != rString)	
      *(resultTmp++) = *(--revPtr);

    /* terminate string */
    *resultTmp = 0;		
  }
  return result;
}


char* itoa(int value, char* result, int radix) {
  char revString[10];
  char *p = result;

  // check that the radix if valid
  if (radix < 2 || radix > 36) { *result = '\0'; return result; }

  if (value < 0) {		/* handle negative */
    *(p++) = '-';
    value = -value;
  }

  utoa(value, p, radix);		/* convert unsigned integer value */
  return result;
}
