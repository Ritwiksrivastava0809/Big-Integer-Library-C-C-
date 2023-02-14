#include <stdio.h>
#include "biginteger.h"

int main()
{
    bigint b = strToBigint("3362671368287817871777787333333338177387838354");
    bigint b1 = newPositiveBigint(1542);

    printf("%d\n", b.sign);
    printf("%d\n", b.capacity);
    printf("%d\n", b.nofdigits);
    printf("%d\n", b.digits[0]);
    printf("%d\n", b.digits[1]);

    bigint b2 = newBigint(-1234);
    printf("%s\n", bigintToString(b2));

    bigint b3 = newBigint(-12367);
    bigint b4 = newBigint(5326);
    bigint b5 = newBigint(5326);
    // printf("%c\n", compareBigint(b3, b4));             // wrong becoz -1 is not a character(but hum -1 return krare so iska dhyan rkho) (no ascii value for -1)and no. is stored like '\255' so printing it gives ascii of 255,similar for 0 and 1('\1' and '\0') printing vaalues at ascii 1 and 0 doesnt make sense we want our ans in 1,0,-1 format according to situation.
    printf("%d\n", (int)compareBigint(b3, b4));        // typecasting char type jo return hora into int and ab int type hua toh %d use(taki -1 ab as a integer hojaye lfda gya char ka )
    printf("%s\n", bigintToString(addBigint(b4, b5))); // addBigint return bigint type value and passed into bigint to string (convert bigint in string)
    printf("%s\n", bigintToString(subtractBigint(b4, b2)));
    return 0;
}