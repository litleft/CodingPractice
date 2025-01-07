#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string.h>

int main()
{
    int case_num;
    scanf("%d", &case_num);

    std::vector<int> n_ary;
    n_ary.resize(case_num);

    for (int c = 0; c < case_num; c++)
    {
        scanf("%d", n_ary.data() + c);
    }

    std::vector<int> n_ary_orded(n_ary);
    std::sort(n_ary_orded.begin(), n_ary_orded.end());

    std::unordered_map<int, int*> log;
    int result[10];
    memset(result, 0, 40);
    int count = 0;
    for (int i = 0; i < case_num; i++)
    {
        int n = n_ary_orded[i];
        for (; count <= n; count++)
        {
            int tmp = count;
            while (tmp > 0)
            {
                int mod = tmp % 10;
                tmp = tmp / 10;
                result[mod]++;
            }
        }
        log[n] = new int[10];
        memcpy(log[n], result, 4 * 10);
    }

    for (int i = 0; i < case_num; i++)
    {
        int* data = log[n_ary[i]];
        for(int j = 0; j < 10; j++)
        {
            printf("%d", data[j]);
            if (j != 9)
            {
                printf(" ");
            }else
            {
                printf("\n");
            }
        }
        delete data;
        log.erase(n_ary[i]);
    }

    return 0;
}