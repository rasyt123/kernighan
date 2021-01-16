#include <stdio.h>
#define MAXLINE 1000
int getlines(char str[], int maxline);

char line[MAXLINE];
main()
{
    int maxerline;
    int len;
    char line[MAXLINE];
    while ((len = getlines(line, MAXLINE)) > 0) {
        printf("%s", line);
    }
}

int getlines(char s[], int lim)
{
    int c, i, j;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    for (j = i - 1; (s[j] == '\t' || s[j] == ' ' || s[j] == '\0' || s[j] == '\n') && j >= 0; j--) {
        s[j] = '\0';
    }
    if (s[j] == '\0') {
        return i;
    }
    ++j;
    s[j] = '\n';
    ++j;
    s[j] = '\0';
    return i;
}
