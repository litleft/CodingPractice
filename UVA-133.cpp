#include <cstdio>
#include <string.h>

int main()
{
    int n, k, m;
    bool marks[20];

    while (scanf("%d %d %d\n", &n, &k, &m))
    {
        if (n == 0) break;

        memset(marks, 0, 20);
        bool first = true;
        int out = 0;
        int k_start = 0;
        int m_start = n - 1;

        auto process = [&](int start, int count, bool rev)
        {
            if (out == n - 1)
            {
                for (int i = 0; i < n; i++)
                {
                    if (!marks[i])
                    {
                        return i;
                    }
                }
            }

            int i = start, c = 0;
            while (true)
            {
                if (!marks[i])
                {
                    c++;
                    if (c == count)
                    {
                        break;
                    }
                }
                i = (rev ? (i - 1 + n) : (i + 1)) % n;
            }
            return i;
        };

        while (out != n)
        {
            int k_out = process(k_start, k, false);
            int m_out = process(m_start, m, true);

            if (!first)
            {
                printf(",");
            }
            first = false;

            if (k_out == m_out)
            {
                out++;
                printf("%3d", k_out + 1);
            }
            else
            {
                out += 2;
                printf("%3d%3d", k_out + 1, m_out + 1);
            }

            marks[k_out] = marks[m_out] = true;
            k_start = (k_out + 1) % n;
            m_start = (m_out + n - 1) % n;
        }
        printf("\n");
    }

    return 0;
}

/// tips:
/// 1. (m - 1) % n 会出现负数的情况 
///