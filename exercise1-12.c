main()
{
    #define IN 1
    #define OUT 0
    state = OUT;
    int c, state;
    while ((c = getchar()) != EOF) {
       if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            putchar('\n')
       } 
       else if (state == OUT) {
           state = IN;
           putchar(c)
       }
    }
}
