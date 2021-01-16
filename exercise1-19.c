#include <stdio.h>
#define MAXLINE 1000
int getlines(char str[], int maxline);
void reverse(char str[]);
char line[MAXLINE];
main()
{
    int maxerline;
    int len;
    char line[MAXLINE];
    while ((len = getlines(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }
}

int getlines(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
}

void reverse(char s[]) {
    int i, j, b, length;
    char c;
    length = 0;
    i = 0;
    while (s[length] != '\0') {
        ++length;
    }
    for (j = 0; j < length; j++) {
        if (s[j] == '\n') {
            --length;
        }
    }
    for (i = 0, b = length - 1; i < b; i++, b--) {
        c = s[i];
        s[i] = s[b];
        s[b] = c;
    }
}
