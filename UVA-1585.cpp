#include <cstdio>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);

    char buf[81];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", buf);

        int len = strlen(buf);
        int score = 0, seq = 0;
        for(int j = 0; j < len; j++)
        {
            if (buf[j] == 'X')
            {
                seq = 0;
            }
            else
            {
                seq++;
                score += seq;
            }
        }
        printf("%d\n", score);
    }

    return 0;
}