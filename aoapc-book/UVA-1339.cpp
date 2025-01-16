#include <cstdio>
#include <algorithm>
#include <string.h>

int main()
{
    int cnta[26], cntb[26];
    char a[101], b[101];

    while (scanf("%s", a) != EOF)
    {
        scanf("%s", b);

        memset(cnta, 0, 4 * 26);
        memset(cntb, 0, 4 * 26);

        int len = strlen(a);
        for (int i = 0; i < len; i++)
        {
            cnta[a[i] - 'A']++;
            cntb[b[i] - 'A']++;
        }

        std::sort(cnta, cnta + 26);
        std::sort(cntb, cntb + 26);


        bool suc = true;
        for (int i = 0; i < 26; i++)
        {
            if (cnta[i] != cntb[i])
            {
                suc = false;
                break;
            }
        }

        printf(suc ? "YES\n" : "NO\n");
    }

    return 0;
}