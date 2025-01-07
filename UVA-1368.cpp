#include <cstdio>
#include <string.h>

inline int to_ind(char c)
{
    switch (c)
    {
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
    default:
        printf("WTF!!!\n");
        return 0;
    }
}

inline char to_char(int ind)
{
    const char char_map[4] = {'A','C','G','T'};
    return char_map[ind];
}

int main()
{
    // 4 <= m <= 50
    int case_count, m, n;
    scanf("%d", &case_count);

    char buf[1000];
    int data[1000][4];
    for (int c = 0; c < case_count; c++)
    {
        scanf("%d %d", &n, &m);
        memset(data, 0, 1000 * 4 * 4);

        for (int i = 0; i < n; i++)
        {
            scanf("%s", buf);
            for (int j = 0; j < m; j++)
            {
                data[j][to_ind(buf[j])]++;
            }
        }

        memset(buf, 0, 1000);

        int dis = 0;
        for (int i = 0; i < m; i++)
        {
            int max = 0, max_j = 0, sum = 0;
            for (int j = 0; j < 4; j++)
            {
                sum += data[i][j];
                if (data[i][j] > max)
                {
                    max = data[i][j];
                    max_j = j;
                }
            }
            dis += sum - max;
            buf[i] = to_char(max_j);
        }
        
        printf("%s\n%d\n", buf, dis);
    }

    return 0;
}