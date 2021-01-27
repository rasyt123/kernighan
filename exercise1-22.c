#include <stdio.h>
#define TABINC 8

main()
{
    int c, nb, nt, pos;

    nb = 0;
    nt = 0;
    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        //keeps track of the position in terms of the number of columns.
        if (c == ' ') {
            //if it's a blank, increment the number of blanks. If the position number is divisible by the 
            if (pos % TABINC != 0) {
                ++nb;
            }
            else {
                nb = 0;
                ++nt;
            }
        } 
        else {
            for ( ; nt > 0; --nt) {
                putchar('\t');
            }
            if (c == '\t') {
                nb = 0;
            }
            else {
                for ( ; nb > 0; --nb) {
                    putchar(' ');
                }
            }
            putchar(c);
            if (c == '\n') {
                pos = 0;
            }
            else if (c == '\t') {
                pos = pos + (TABINC - (pos - 1) % TABINC) - 1;
            }
        }
    }
}
