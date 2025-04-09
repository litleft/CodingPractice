#include <iostream>
#include <queue>
#include <set>

using namespace std;

int main()
{
    using ll = long long;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    set<ll> s;
    pq.push(1);
    s.insert(1);

    int i = 1;
    int ugly[3] = {2, 3, 5};
    while (true)
    {
        ll x = pq.top();
        pq.pop();
        if (i++ == 1500)
        {
            cout << "The 1500'th ugly number is " << x << "." << endl;
            break;
        }
        
        for (int j = 0; j < 3; j++)
        {
            ll x2 = x * ugly[j];
            if (!s.count(x2))
            {
                pq.push(x2);
                s.insert(x2);
            }
        }
    }
}