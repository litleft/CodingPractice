#include <cstdio>
#include <vector>
#include <map>

using std::vector;
using std::map;

int main()
{
    int a, b;
    while (true)
    {
        if (scanf("%d %d", &a, &b) == EOF)
        {
            break;
        }

        int a_d_b = a / b;
        int a_m_b = a % b;

        int cyc_start = -1, cyc_len = 0;
        int divd = a_m_b * 10, divs = b;
        vector<int> res;
        map<int, int> divd_cache;
        while (true)
        {
            if (divd_cache.count(divd) > 0)
            {
                cyc_start = divd_cache.at(divd);
                cyc_len = res.size() - cyc_start;
                break;
            }

            if (divd == 0)
            {
                cyc_start = res.size();
                cyc_len = 1;
                res.emplace_back(0);
                break;
            }

            int r = divd / divs;
            int m = divd % divs;
            divd_cache[divd] = res.size();
            res.emplace_back(r);
            divd = m * 10;
        }

        printf("%d/%d = %d.", a, b, a_d_b);
        for (int i = 0; i < cyc_start; i++)
        {
            printf("%d", res[i]);
        }
        printf("(");
        for (int i = 0; i < cyc_len && i < 50 - cyc_start; i++)
        {
            printf("%d", res[i + cyc_start]);
        }
        if (cyc_len > 50)
        {
            printf("...)\n");
        }
        else
        {
            printf(")\n");
        }

        printf("   %d = number of digits in repeating cycle\n\n", cyc_len);
    }

    return 0;
}