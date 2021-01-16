{
    #define IN 1
    #define OUT 0
    int c, nc, state, i, j;
    state = IN;
    int charrary[10];
    nc = 0;
    for (j = 0; j < 10; ++j) {
        charrary[j] = 0;
    }
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (state == OUT) {
                ++charrary[nc];
            }
            nc = 0;
            state = IN;
        }
        else if (state == IN) {
            ++nc;
        }
    }
    for (i = 1; i < 10; ++i) {
        printf("|%2d|", i);
        for (j = 1; j <= charrary[i]; ++j) {
            putchar('*');
        }
        putchar('\n');
    }
}
