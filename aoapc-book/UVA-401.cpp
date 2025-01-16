#include <ctype.h>
#include <cstdio>
#include <string.h>

const char reverse_char[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char* msg[] = {"not a palindrome", "a regular palindrome", "a mirrored string", "a mirrored palindrome"};

char get_reverse(char c)
{
    if (isalpha(c)) return reverse_char[c - 'A'];
    else return reverse_char[c - '0' + 26 - 1];
}

int main()
{
    char str[30];
    while(scanf("%s", str) != EOF)
    {
        int len = strlen(str);
        int mirror = 1;
        int palind = 1;
        for(int i = 0; i < (len + 1) / 2; i++)
        {
            if (str[i] != str[len - 1 - i]) palind = 0;
            if (get_reverse(str[i]) != str[len - i - 1]) mirror = 0;
        }
        printf("%s -- is %s.\n\n", str, msg[mirror * 2 + palind]);
    }

    return 0;
}

