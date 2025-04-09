#include <cstdio>
#include <string.h>
#include <algorithm>

const int maxn = 1001;
int answer[maxn];
int cache[maxn];
int dig_ans[9];
int dig_cac[9];

int main()
{
    int game = 0;
    int n;
    while(scanf("%d", &n) == 1 && n != 0)
    {
        printf("Game %d:\n", ++game);

        memset(dig_ans, 0, 4 * 9);
        
        for (int i = 0; i < n; i++)
        {
            scanf("%d", answer + i);
            dig_ans[answer[i] - 1]++;
        }

        while(true)
        {
            for (int i = 0; i < n; i++)
            {
                scanf("%d", cache + i);
            }

            if (cache[0] == 0) break;

            memset(dig_cac, 0, 4 * 9);
            int a = 0, b = 0;
            for (int i = 0; i < n; i++)
            {
                if (cache[i] == answer[i])
                {
                    a++;
                }
                dig_cac[cache[i] - 1]++;
            }


            for (int i = 0; i < 9; i++)
            {
                b += std::min(dig_ans[i], dig_cac[i]);
            }

            printf("    (%d,%d)\n", a, b - a);
        }
    }

    return 0;
}