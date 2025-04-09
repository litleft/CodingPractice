#include <iostream>
#include <limits.h>

using namespace std;
using ll = long long;

bool is_valid(ll sp, ll sq, int a, int b)
{
    return (sp + (sp << a)) >= (sq << b);
}

ll get_k(ll sp, ll sq, int a, int b, int n)
{
    ll op = sp * (n - 1);
    ll oq = (op + (op << a)) >> b;
    return oq + sq;
}

int main()
{
    int n, sp, sq;
    while (cin >> n >> sp >> sq)
    {
        ll k = LLONG_MAX;
        int a_min, b_min;
        for (int a = 0; a < 32; a++)
        {
            for (int b = 0; b < 32; b++)
            {
                if (!(is_valid(sp, sq, a, b))) continue;

                ll res = get_k(sp, sq, a, b, n);
                if (res < k)
                {
                    k = res;
                    a_min = a;
                    b_min = b;
                }
            }
        }

        printf("%lld %d %d\n", k, a_min, b_min);
    }

    return 0;
}