#include <stdio.h>
#include <stdbool.h>                    // using bool in c
#define MAX(i1, i2) (i1 > i2 ? i1 : i2) // macro
/* making a bigint datatype which have following attributes i) sign -----for no. to be negative or positive
   ii) size of array ----*i)capacity (total no. of slots of an array) *ii)no. of digits (no. of slots occupied of an array)
   iii) for character array of digit we use character pointer (optimum way to use memory) */

#ifndef BIGINT_H
#define BIGINT_H

typedef struct
{
   bool sign;
   unsigned int capacity;
   unsigned int nofdigits;
   char *digits;
} bigint;

extern const bigint BIGINT_ZERO;

bigint allocateBigint(unsigned int capacity);

bigint strToBigint(char *str);

bigint newBigint(int i);
bigint newPositiveBigint(unsigned int i);

char *bigintPtrToString(bigint *i);
char *bigintToString(bigint i);
char compareBigint(bigint i1, bigint i2);
bigint addBigint(bigint i1, bigint i2); // 2 variable ka name same ,aak scope mai ni le skte(redeclaration error) agar scope alag hai toh le skte becoz aak tym pe aak hi active dusra dimished (used wala) aur jo use hoga aagey same name wala woh abhi call ni hua toh scene hi ni.
bigint subtractBigint(bigint i1, bigint i2);

#endif
