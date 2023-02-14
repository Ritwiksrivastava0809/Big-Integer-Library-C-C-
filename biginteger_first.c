// https://stackoverflow.com/questions/71991901/error-iso-c-forbids-converting-a-string-constant-to-char

#include "biginteger.h"
#include <stdlib.h>
#include <string.h>
// char * digits ---integer array lenge digits ki toh aak aak slot 4 byte lega but hum character array lenge digits ki toh aak aak slot one byte memory lega and hum isse operations bhi krlenge
// this technique for optimum memory is used only for digits (0 to 9)

const bigint BIGINT_ZERO = {true, 0, 0, NULL}; // const becoz ye fixed hai

bigint allocateBigint(unsigned int capacity)
{
    bigint ret;              /* use to setup the structure and allocate memory to it and set up the values(initialisation)laterly , local object valid inside this function only becoz declared inside the function*/
    ret.capacity = capacity; /* ret.capacity is for structure ,capacity is same as function argument capacity */
    ret.nofdigits = 0;
    ret.sign = true;                              // initial sign is set to positive
    ret.digits = malloc(capacity * sizeof(char)); /*allocating memory to array in heap */
    return ret;                                   // returning bigint type data (seeing function returntype)
}
/* string to bigint conversion */

bigint strToBigint(char *str)
{ /* string passed by user from main file woh yaha argument mai ayega */
    unsigned int len = strlen(str);
    unsigned int nofdigits = len;

    bool sign = true; // initially positive setted sign
    if (str[0] == '-')
    {
        sign = false; /* for negative no. string dealing */
        nofdigits--;  //- sign is not included in nofdigits
    }

    if (nofdigits == 0)
    {
        return BIGINT_ZERO; /* for empty string */
    }

    bigint ret = allocateBigint(nofdigits); // ret variable is used as bigint(datatype)(userdefined) here  /* nofdigits going to capacity as an argument (fix hogyi string jb user ne aak baar input krdiya--> capacity=nofdigits)  ,function call hui jo return hua data bigint type ka woh bigint type ke userdefined datatype wale variable mai store */
    ret.nofdigits = nofdigits;              // upar wale function ke chlne ke wjh se nofdigits 0 hogye thai but actually woh hai so isliye woh set kiya
    ret.sign = sign;                        // ret.sign ----bigint type ka  jo return hoga temporary object(variable) uska sign ,only sign denoting to temporary bool variable used to set sign according to conditions , ret is temporary variable of structure bigint,(visualise its memory as object).

    for (unsigned int i = 0; i < nofdigits; i++)
    {
        char c = str[len - 1 - i]; // c mai reverse order mai character extract krre from string.
        if (c >= '0' && c <= '9')
        {
            ret.digits[i] = c - '0'; /* digits ki jo char array bni hai jisme hum aak slot mai aak aak digit(in numerical form but in char aray(eg ('9' -'0') is '\t' for 9 is store in memory(ascii no. of '\t'is 9)),digit[0] is '\t' ,int(digit[0]) is 9,in addition operation (digit[0] +digit[1])ascii value direct add,(hamara aim ki koi bhi digit ko from string extraction (char) ko less space mai store krle and usko hum use bhi krle for operation(integer jaisa rkhle in char array) is fullfilled) for less space as compare to int array(becoz int 4 byte and char 1 byte) but aisa like no. ko char array mai store krke usko use lelo operations mai aisa bss digits ke liye kr skte becoz char c='9'ye chracter hai char c='10'character ni hai it is string) rkhenge extraction from string in such a way string ka last yaha ka first for easier operation becoz we are doing operations from left to right which is easier to look at on a computer */
        }
        else
        {                       /* extra knowledge: char c='3' then isko char array mai dala means digit[0]=c; woh 3 as a charcter first slot of char array mai jayega then ab usko print kra toh 3 print hoga as a character or int(digit[0]) means ascii value of that character */
            return BIGINT_ZERO; /* for invalid character */
        }                       // char c=3 ;in memory '\3'is stored that means ascii of 3 is stored ;cout<<c prints ascii of 3 ;cout<<(int)c means 3 as a integer----in c variable 3 as a digit is stored in char form.
    }
    return ret; // here(in this function) ret is used for biginter.
}

/* converting integer and unsigned integer to bigintger */

bigint newBigint(int i)
{
    bool sign = true; /* sign ka concern becoz integer ki range mai negative no. bhi aatey hai */
    if (i < 0)
    {
        sign = false;
        i *= -1;
    }
    bigint ret = newPositiveBigint(i);
    ret.sign = sign;

    return ret;
}
bigint newPositiveBigint(unsigned int i)
{
    /*total no. of digits*/ unsigned int copy = i;
    unsigned int nofdigits = 0;
    while (copy > 0)
    {
        nofdigits++;
        copy /= 10;
    }
    bigint ret = allocateBigint(nofdigits);
    ret.nofdigits = nofdigits;
    for (unsigned int idx = 0; idx < nofdigits; idx++, i /= 10)
    {
        ret.digits[idx] = i % 10; /* last no. ko first position pe rkhna in char array */
    }                             /* if for eg) int i=5, in first slot of char array (digit[0]) '\5' is stored(ascii value of 5) or 5 in numerical form in char array*/
    return ret;
}

/* big integer to string conversion */

char *bigintPtrToString(bigint *i)
{
    if (!i->nofdigits) /* pointer i(iss function ka pointer variable i) points to i(neeche wale function ka) kyuki usme i ka address hai(neeche wale function ke i variable ka (userdefined bigint type)) and i(neeche function wala) stores b(passed from main) toh b ke nofdigits agar 0 hai toh bigint b mai koi number store hi ni hai toh kya hi string mai convert krenge */
    {                  // here -2- i ki baat hori aak neeche wale function ke argument ki aur aak iss function ke argument ki
        return "0";
    }

    unsigned int nofchars = i->nofdigits; /* string mai utne characters honge jitne no. of digits honge */
    if (!i->sign)
    {
        nofchars++; /* for negative sign character no. should be incremented becoz nofchars se hum string kitne size ki bnana hai(memory allocate krna hai)decide krenge */
    }
    char *ret = malloc((nofchars + 1) * sizeof(char)); /* for string formation ----+1 for null character at the end of string */
    if (!ret)
    {
        return NULL; /* if memory not allocated */
    }
    unsigned int stridx = 0;
    if (!i->sign)
    {
        ret[stridx++] = '-'; /* agar sign - hua bigint ka toh pehle string mai - insert krdo */
    }
    for (unsigned int digitidx = i->nofdigits; digitidx != 0; digitidx--, stridx++)
    {
        /* string ka jo iterative pointer hai(stridx) woh forward iterate krra and bigint ya(digit ka) iterative pointer hai digitidx woh backward move becoz string mai hum sidhi character value bharenge digit mai se nikalke (digit array mai hmne upar dekha tha ulti values store hoti hai isliye usko piche se iterate krke string mai pehle dala taki actual string mile) */
        ret[stridx] = '0' + i->digits[digitidx - 1]; /* string mai sb character hi store hue like '3', yaha digitidx-1 isliye kiya becoz size-1 is last index and here size is nofdigits */
    }
    ret[nofchars] = '\0'; /* string ka last index is nofchars, one less than size(nofchars+1) */

    return ret;
}
char *bigintToString(bigint i)
{                                 /* pass by adress(through pointers) */
    return bigintPtrToString(&i); /* jo ,b main file se pass hua woh i mai store and i ka adress pass to pointer(bigint *i) */
}

//  pass by value(through object(i) directly)

//   char *bigintToString(bigint i)
// {
//     if (!i.nofdigits) /* i stores b(passed from main) toh b ke nofdigits agar 0 hai toh bigint b mai koi number store hi ni hai toh kya hi string mai convert krenge */
//     {                 // i is object in this case of bigint structure.
//         return "0";
//     }

//     unsigned int nofchars = i.nofdigits; /* string mai utne characters honge jitne no. of digits honge */
//     if (!i.sign)
//     {
//         nofchars++; /* for negative sign character no. should be incremented becoz nofchars se hum string kitne size ki bnana hai(memory allocate krna hai)decide krenge */
//     }
//     char *ret = (char *)malloc((nofchars + 1) * sizeof(char)); //  ret is used for string here(char array) /* for string formation ----+1 for null character at the end of string */
//     if (!ret)
//     {                // pointer 0 means it is null ptr it is pointing nowhere.
//         return NULL; /* if memory not allocated */
//     }
//     unsigned int stridx = 0;
//     if (!i.sign)
//     {
//         ret[stridx++] = '-'; /* agar sign - hua bigint ka toh pehle string mai - insert krdo */
//     }
//     for (unsigned int digitidx = i.nofdigits; digitidx != 0; digitidx--, stridx++)
//     {
//         /* string ka jo iterative pointer hai(stridx) woh forward iterate krra and bigint ya(digit ka) iterative pointer hai digitidx woh backward move becoz string mai hum sidhi character value bharenge digit mai se nikalke (digit array mai hmne upar dekha tha ulti values store hoti hai isliye usko piche se iterate krke string mai pehle dala taki actual string mile) */
//         ret[stridx] = '0' + i.digits[digitidx - 1]; /* string mai sb character hi store hue like '3', yaha digitidx-1 isliye kiya becoz size-1 is last index and here size is nofdigits */
//     }
//     ret[nofchars] = '\0'; /* string ka last index is nofchars, one less than size(nofchars+1)(memory allocation of char array(string) in this function) */

//     return ret; // here(in this function) ret is basically char array (string) ----(return type is char*)----char array in optimal form is (char*).
// }

/* for comaprison operation */

char compareBigint(bigint i1, bigint i2)
{ // to check two number equal, lesser and greater according to it we made convention of returning 0,-1,1.
    if (i1.sign && !i2.sign)
    {             // i1 >=0,i2<0 (agar aisa hoga tbhi ye if condition chlegi)
        return 1; // char type ka return hai(return 1 in char form('\1' in memory)) , first argument is greater than second argument return 1.
    }
    else if (!i1.sign && i2.sign)
    {              // i1<0,i2>=0
        return -1; // first argument is smaller than second argument return -1.
    }
    else if (!i1.sign && !i2.sign)
    { // i1<0 ,i2<0
        // both negatives,compare positives and return oppossite(compare jb krenge positives ko toh bhi toh return 1,-1,0 (according to situation) hoga jb uska opposite krdenge toh negative ke liye case bn hi jayega )
        i1.sign = true; // making i1 and i2 positive
        i2.sign = true;
        char comparison = compareBigint(i1, i2);
        // finally ye function wapis call kiya hamne ki ab  positive i1,i2 ko compare kre jo abhi niche mai code krunga(same function mai both positive condition)
        return -comparison;
    }

    // both positive
    if (i1.nofdigits > i2.nofdigits)
    {             // first argument is greater than second argument becoz usme digits jyada hai
        return 1; // imp ---return 1 hoga not '1' as a char format (by function returntype)
    }
    else if (i2.nofdigits > i1.nofdigits)
    {
        return -1;
    }

    // same no. of digits ,compare individual digits
    unsigned int idx = i1.nofdigits; //(i2.nofdigits bhi chlega becoz nofdigits are same)
    while (idx--)
    {
        if (i1.digits[idx] > i2.digits[idx])
        { // digits array of i1 (bigint) and i2(bigint) mai digits ulte store thai hmne upar dekha tha ,so for comparing konsa number bda hai if nofdigits are same toh har individual digit ko dekhna hai ,toh hamare digit array mai digits ulte store thai toh hme piche se aak aak digit extract krke compare krna hai jaha bda digit pehle(becoz hamara actual number toh digit array ko ulta krne pe milta hai) ,waha hi return hoke while loop se bahar (becoz digit same hai toh jaha pehla digit wala no. bda(of i1 or i2) woh no. bda)
            return 1;
        }
        else if (i1.digits[idx] < i2.digits[idx])
        {
            return -1;
        }
    }
    // all digit equal
    return 0;
}

/* for addition operation */

bigint addBigint(bigint i1, bigint i2)
{ // 2 biginteger ko add kiya toh biginteger hi milega so thats why returntype is bigint (result of addition of two bigint)
    if (i1.sign && !i2.sign)
    {                                  // i1>0 ,i2<0 ,i1 + (-i2) =i1-i2
        i2.sign = true;                // i2 becomes positive
        return subtractBigint(i1, i2); // (i1 -(by subtract function) i2)
    }
    else if (!i1.sign && i2.sign)
    {                                  // i1<0,i2>0, (-i1)+i2=i2-i1
        i1.sign = true;                // i1 becomes positive
        return subtractBigint(i2, i1); // (i2-i1)
    }

    // now allocate memory for the bigint type variable (ret) jismehum sum rkhenge
    // nofdigits mai - sign ko ni count krte
    unsigned int nofdigits = MAX(i1.nofdigits, i2.nofdigits) + 1; // sum jo hai usme ya toh dono mai se woh number jisme jyada digits hai utne digit aayenge ya aak jyada aayega , eg) 363(3 digit) + 23(2digit) =386(3 digit) , 456(3 digit) + 645(3 digit)=1101(4 digit)---left se first digit ka sum dono no. ka agar 9 se jyada toh hi ye case generate ki dono no. mai se max nofdigits wale se 1 jyada nofdigit ayenga in sum , so hum extreme case(2 type case) ke hisab se initialise krenge if kum digit aare honge toh woh hum accordigly set krlenge
    bigint ret = allocateBigint(nofdigits);                       // sum ko memory allocate
    ret.nofdigits = nofdigits;

    bool carry = false; // initially koi carry ni lena so uski value 0 pe set
    for (unsigned int idx = 0; idx < ret.nofdigits; idx++)
    { // ye forloop  (sum,ans or ret) ke nofdigits tk chlega----MAX(i1.nofdigits,i2.nofdigits)+1 yaha tk
        // ye forward for loop isliye use becoz hamara jo i1 or i2 biginteger ka char array (pointer) wale part mai number ko ulte hi store kiya  hai (above discussed) so usko hi direct add krdenge correspondingly becoz hum actual basic maths mai kya krte no. ko sidha hi rkhte and piche se add krte toh yaha bhi wahi hoga number ko ulta krke usko aagey se add toh sum mai ulti sum(biginteger ret jisme sum store hoga) store hogi toh usko phir hum bigint to string function mai dalke bigint se string bnalenge woh bhi sidhe(front) form mai

        char res = carry ? 1 : 0; //(initial(first iteration of idx) bool carry mai 0 store becoz of false and isliye char res mai '\0'store (integer 0 in char form))
        if (idx < i1.nofdigits)
        {
            res += i1.digits[idx]; // each iteration mai res mai i1 no. ke aak digit(acc to iteration) or carry rha toh uska sum store upto this line
        }
        if (idx < i2.nofdigits)
        {
            res += i2.digits[idx]; // yaha pe aane pr upar wala res + dusre no. ka ussi iteration ke corresponding wala digit addition and storing , res ka use hum ret(biginteger hai ret toh uske char array wale part mai sum store ) mai sum insert krne ke liye krre
        }
        if (res >= 10)
        {
            carry = true; // res har particular iteration mai un  dono biginteger i1 , i2 ke uss particular corresponding digit(of that iteration) ka sum store along with carry toh if ye 10 ya usse jyada toh next iteration ke liye carry ayega isliye usko 1 set kiya(true)
            res -= 10;    // res ko 10 se kum krdenge toh end digit kya hona chahiye woh milega res mai usse hum ret mai sum ka ans store krenge of each each slot at alag alag iteration --------> 123+138=261, 8+3=11 ,11-10 =1 toh ye 1 end digit haina sum ka
        }
        else
        {
            carry = false; // if res 10 se kum toh no carry for next iteration
        }

        ret.digits[idx] = res; // woh jo hum extract krre na sum ka aak aak digit at each iteration in res woh ab hum ans (ret)ke digits wali array mai store krre har iteration mai
    }
    // removing leading zeroes
    // It means let suppose hmne no. liya 123 nd 234 inka sum aaya 357 but hmne final ans ke liye kitne no. of digits liye( MAX(i1.nofdigits,i2.nofdigits)+1)  4 digit toh jo sum ki final array hai (ret.digits wali char type ki)usme 4 digits honge aur uski size bhi 4 hogi (capacity=nofdigits)but hamare according ans toh 3 digit ka hai but jb last iteration ke liye for loop chlra hoga tb dono no. i1 and i2 ka digits khatam toh unka contribution res mai nhi ayega aur pichle iteration ka kuch carry bhi ni hua toh  res 0 hi hoga toh last iteration ke liye sum ke uss slot mai 0 set hme iss leading 0 ko hi htana hai(leading zero according to final sum jo hum display krenge (bigint se string krne ke baad jo aaya)but bigint se string krne pe uss function ke through woh leading zero automatic udega ) (basically ret mai ulta sum store toh waha last hoga 0)
    while (!ret.digits[ret.nofdigits - 1])
    {                    // last digit jbtk 0 hai tbtk delete becoz no. ko sidha krne pe ye leading hoga and leading zero ka koi matlab ni
        ret.nofdigits--; // last digit ret ka ya sum ka if 0 toh nofdigits aak se kum then loop mai hai toh next last digit(nofdigits aak se decrease hua hai so next while condition ke liye nofdigits alag) ko check.
    }

    if (!i1.sign && !i2.sign)
    {                     //(-i1)+(-i2)= -(i1+i2)
        ret.sign = false; //  jo humara ret mai ans above execution se aaya hoga woh +i1 and +i2 ke sum se bna i1+i2 hume yaha -(i1+i2)chahiye means hume jst ret ka sign opposite krna(-)baki char digit array toh as it is hi rhegi
    }

    return ret; // returning bigint ret(sum) jaha se call kiya waha pr in main file
}

bigint subtractBigint(bigint i1, bigint i2)
{
    char comparison = compareBigint(i1, i2); // 1(convention) (return wala in integer form)stored  in char form (becoz char type se return hua)('\1' in memory)after returning,similar for 0(convention)('\0' in memory) but for -1(convention)(not a character) in memory it is stored as '\255'after doing %d it gets converted into -1.
    if (!comparison)
    { // numbers are same then this if is operated (control go inside) //(comparison is  0 in char form (becoz comparison is of char type) then this if condition operates )
        return BIGINT_ZERO;
    }

    if (i1.sign && !i2.sign) // i1 - -i2 = i1+i2
    {
        i2.sign = true;
        return addBigint(i1, i2);
    }
    else if (!i1.sign && i2.sign) // -i1 - i2 = -i1 + -i2
    {
        i2.sign = false;
        return addBigint(i1, i2);
    }
    else if (!i1.sign && !i2.sign) // -i1 - -i2 = -i1 + i2 = i2 - i1
    {
        i1.sign = true;
        i2.sign = true;
        return subtractBigint(i2, i1);
    }
    else // both positive , find maximum
    {
        if (comparison < 0) // i2 > i1 ; i1 - i2 = - (i2 - i1)
        {
            bigint res = subtractBigint(i2, i1);
            res.sign = !res.sign;
            return res;
        }
    }

    // both are positive and i1 is larger
    // so we can just subtract as usual as we do
    unsigned int nofdigits = i1.nofdigits;
    bigint ret = allocateBigint(nofdigits);
    ret.nofdigits = nofdigits;

    bool carry = false;

    for (unsigned int idx = 0; idx < ret.nofdigits; idx++)
    {
        char res = carry ? -1 : 0;
        if (idx < i1.nofdigits)
        {
            res += i1.digits[idx];
        }
        if (idx < i2.nofdigits)
        {
            res -= i2.digits[idx];
        }

        // check for carry
        if (res < 0)
        {
            carry = true;
            res += 10;
        }
        else
        {
            carry = false;
        }
        // set the digit
        ret.digits[idx] = res;
    }

    // remove leading zeroes
    while (!ret.digits[ret.nofdigits - 1])
    {
        ret.nofdigits--;
    }

    return ret;
}
// -----------------------------------------------------------*******--------------------------------------------------------------------
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