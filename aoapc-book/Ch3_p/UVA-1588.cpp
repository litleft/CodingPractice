#include <cstdio>
#include <utility>
#include <string.h>
#include <algorithm>

int main()
{
    char a[101], b[101];

    while (true)
    {
        if (scanf("%s\n", a) == EOF) break;
        scanf("%s\n", b);

        int alen = strlen(a);
        int blen = strlen(b);

        if (alen > blen)
        {
            std::swap(alen, blen);
            std::swap(a, b);
        }

        int minlen = -1;
        for (int i = alen - 1; i > 0; i--)
        {
            bool suc = true;
            for (int j = 0; j < i; j++)
            {
                if (a[alen - i + j] + b[j] > '2' + '1')
                {
                    suc = false;
                    break;
                }
            }
            if (suc)
            {
                minlen = alen - i + blen;
                break;
            }
        }

        for (int i = 0; i < blen; i++)
        {
            if (minlen > 0 && i + alen > minlen)
            {
                break;
            }

            bool suc = true;
            for (int j = 0; j < alen && j < blen - i; j++)
            {
                if (a[j] + b[i + j] > '2' + '1')
                {
                    suc = false;
                    break;
                }
            }
            if (suc)
            {
                minlen = i + alen;
                break;
            }
        }

        printf("%d\n", minlen == -1 ? alen + blen : std::max(minlen, blen));
    }



    return 0;
}