#include <iostream>
#include <queue>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)

int main()
{
    int n;
    queue<int> q;
    while (cin >> n && n != 0)
    {
        REP(i, n)
        {
            q.push(i + 1);
        }

        cout << "Discarded cards:";
        while (q.size() > 1)
        {
            cout << " " << q.front();
            q.pop();
            q.push(q.front());
            q.pop();
            if (q.size() > 1)
                cout << ",";
        }
        cout << endl;
        cout << "Remaining card: " << q.front() << endl;
        
        if (q.size() > 0)
            q.pop();
    }
}