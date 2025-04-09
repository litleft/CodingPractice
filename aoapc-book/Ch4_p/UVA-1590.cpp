#include <cstdio>

using namespace std;

int get_highest_bit(int a)
{
    int res = 0;
    while (a)
    {
        a >>= 1;
        res++;
    }
    return res;
}


int main()
{
    int m;
    while (scanf("%d", &m) != EOF)
    {
        int ip[4];
        int mask_bit = 32;
        unsigned char mask[4];
        int network[4];

        for (int i = 0; i < m; i++)
        {
            scanf("%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);

            if (i == 0)
            {
                for (int j = 0; j < 4; j++)
                {
                    mask[j] = 255;
                    network[j] = ip[j];
                }
            }
            else
            {
                for (int j = 0; j < 4; j++)
                {
                    int xor_res = (ip[j] ^ network[j]);
                    int highest_bit = get_highest_bit(xor_res);
                    if (highest_bit == 0) continue;

                    int cur_mask = 8 - highest_bit + 8 * j;
                    if (cur_mask < mask_bit)
                    {
                        mask_bit = cur_mask;
                        for (int k = 0; k < j; k++)
                        {
                            network[k] = ip[k];
                            mask[k] = 255;
                        }
                        network[j] = ip[j] & (255 << highest_bit);
                        mask[j] = 255 << highest_bit;
                        for (int k = j + 1; k < 4; k++)
                        {
                            network[k] = 0;
                            mask[k] = 0;
                        }
                    }
                }
                
            }
        }

        printf("%d.%d.%d.%d\n", network[0], network[1], network[2], network[3]);
        printf("%d.%d.%d.%d\n", mask[0], mask[1], mask[2], mask[3]);
    }

    return 0;
}