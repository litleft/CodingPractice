#include <cstdio>
#include <string>

const std::string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        int i = 1;
        for (; keyboard[i] && keyboard[i] != c; i++)
        {
        }
        if (keyboard[i] == '\0')
        {
            printf("%c", c);
        }
        else
        {
            printf("%c", keyboard[i-1]);
        }
    }
    return 0;
}