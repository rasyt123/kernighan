
main()
{
    int c, nl, tabs, blanks;
    nl = tabs = blanks = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
        if (c == '\t')
            ++tabs;
        if (c == ' ')
            ++blanks;
    }
    printf("%d %d %d", nl, tabs, blanks);
}
