#include <iostream>
#include <cstdio>

int main()
{
    bool right = true;
    char c;
    while(scanf("%c", &c) != EOF)
    {
        if (c != '"') printf("%c", c);
        else
        {
            if (right)
            {
                printf("``");
                right = false;
            }
            else
            {
                printf("''");
                right = true;
            }
        }
    }
    return 0;
}