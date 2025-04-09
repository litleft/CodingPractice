#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int kase_cnt;
    cin >> kase_cnt;

    for (int kase = 0; kase < kase_cnt; kase++)
    {
        queue<int> jobs;
        vector<int> heap;

        int n, idx;
        cin >> n >> idx;
        for (int i = 0; i < n; i++)
        {
            int priority;
            cin >> priority;
            jobs.push(priority);
            heap.push_back(priority);
        }

        sort(heap.begin(), heap.end(), greater<int>());
        int cur_heap_idx = 0;
        int time = 0;

        while (true)
        {
            int priority = jobs.front();
            jobs.pop();

            if (heap[cur_heap_idx] == priority)
            {
                cur_heap_idx++;
                time++;
                if (idx == 0)
                    break;
                idx--;
            }
            else
            {
                jobs.push(priority);
                if (idx == 0)
                    idx = jobs.size() - 1;
                else
                    idx--;
            }
        }

        cout << time << endl;
    }
}