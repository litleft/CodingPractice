#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;

bool str_equal(char* a, char* b, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] != b[i])
        {
            return false; 
        }
    }
    return true;
}

int main()
{
    int case_num;
    scanf("%d", &case_num);

    char str_buf[81];
    for (int c = 0; c < case_num; c++)
    {
        scanf("%s", str_buf);

        int len = strlen(str_buf);
        for (int k = 1; k <= len; k++)
        {
            if ((len % k) != 0 ) continue;
            
            bool suc = true;
            int max_peri = len / k;
            for (int i = 0; i < max_peri; i++)
            {
                if (!str_equal(str_buf, str_buf + (i * k), k))
                {
                    suc = false;
                    break;
                }
            }
            if (suc)
            {
                printf("%d\n", k);
                break;
            }
        }

        if (c != case_num - 1)
        {
            printf("\n");
        }
    }

    return 0;
}