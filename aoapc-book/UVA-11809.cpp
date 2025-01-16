#include <cstdio>
#include <cmath>

int main()
{
    double m_cache[10];
    for (int m = 0; m <= 9; m++)
    {
        m_cache[m] = std::log2(1.0 - std::pow(2.0, -(m + 1)));
    }

    double cache[10][31];
    for (int e = 1; e <= 30; e++)
    {
        double cache_ = (std::pow(2.0, e) - 1);
        for (int m = 0; m <= 9; m++)
        {
            cache[m][e] = cache_ + m_cache[m];
        }
    }

    const double log10_2 = std::log2(10.0);

    char s1[100], s2[100];
    while (scanf(" %[^e] %*[e] %s", s1, s2) && s1[0] != '0') 
    {
        double value = std::log2(atof(s1)) + atof(s2) * log10_2;

        bool suc = false;
        int m, e;
        for (e = 1; e <= 30; e++)
        {
            for (m = 0; m <= 9; m++)
            {
                if (std::abs(cache[m][e] - value) < 1e-4)
                {
                    suc = true;
                    break;
                }
            }
            if (suc) break;
        }
        printf("%d %d\n", m, e);
    }

    return 0;
}