#include <cstdio>
#include <string.h>

int main()
{
    int t;
    scanf("%d", &t);

    char seq[100];
    for (int i = 0; i < t; i++)
    {
        scanf("%s", seq);
        int len = strlen(seq);
        
        int min_start = 0;
        for (int start = 1; start < len; start++)
        {
            for (int j = 0; j < len; j++)
            {
                int cur_min = (min_start + j) % len;
                int cur = (start + j) % len;

                if (seq[cur_min] > seq[cur])
                {
                    min_start = start;
                    break;
                }
                else if (seq[cur_min] < seq[cur])
                {
                    break;
                }
            }
        }

        for (int j = 0; j < len; j++)
        {
            printf("%c", seq[(min_start + j) % len]);
        }
        printf("\n");
    }

    return 0;
}