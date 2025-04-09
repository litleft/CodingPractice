#include <iostream>
#include <cstdio>
#include <unordered_map>


int main()
{

    const int max_n = 100000;

    std::unordered_map<int, int> genereator;

    for(int n = 1; n <= max_n; n++)
    {
        int tmp_n = n;
        int sum = 0;
        while (tmp_n > 0)
        {
            sum += (tmp_n % 10);
            tmp_n = (tmp_n / 10);
        }
        sum += n;

        if (sum > max_n) continue;

        if (genereator.count(sum) == 0)
        {
            genereator[sum] = n;
        }
    }

    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &m);
        if (genereator.count(m) > 0)
        {
            printf("%d\n", genereator[m]);
        }
        else
        {
            printf("%d\n", 0);
        }
    }

    return 0;
}