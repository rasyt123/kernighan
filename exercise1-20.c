#include <stdio.h>
void detab(int n);
main()
{
    int bign;
    bign = 3;
    detab(bign);
}


void detab(int n)
{
    int currentposition, i, tabcount, c, numberofblanks;
    numberofblanks = 0;
    currentposition = 0; 
    while ((c = getchar()) != EOF) {
        ++currentposition;
        if (c == '\t') {
            tabcount = (n - ((currentposition - 1) % n));
            for (i = 0; i < tabcount; i++) {
                    putchar(' ');
            }
        }
        else {
            putchar(c);
        }
    }
}
