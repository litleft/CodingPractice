#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>
#include <functional>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;


struct node
{
    int value = -1;
    int cnt_assign = 0;
    node* left = nullptr;
    node* right = nullptr;
};

struct pool_node
{
    stack<node*> pool;

    node* get()
    {
        if (pool.empty())
        {
            return new node();
        }
        node* n = pool.top();
        pool.pop();
        return n;
    }

    void ret(node* n)
    {
        n->cnt_assign = 0;
        n->left = n->right = nullptr;
        pool.push(n);
    }

    ~pool_node()
    {
        while (!pool.empty())
        {
            delete pool.top();
            pool.pop();
        }
    }
};

int main()
{
    // pool_node pool;
    string line;

    while (getline(cin, line))
    {
        int start = 0;
        node* root = new node();
        while (true)
        {
            int blk_l = line.find('(', start);
            // 输入最后可能存在空格
            if (start >= line.size() || blk_l == string::npos)
            {
                getline(cin, line);
                start = 0;
                continue;
            }

            if (line[blk_l + 1] == ')')
            {
                break;
            }
            int dot = line.find(',', blk_l + 1);
            int blk_r = line.find(')', dot+1);
            start = blk_r + 1;

            int value = atoi(line.substr(blk_l + 1, dot - blk_l - 1).c_str());
            node* cur = root;
            FOR(i, dot + 1, blk_r - 1)
            {
                if (line[i] == 'R')
                {
                    if (cur->right == nullptr)
                    {
                        cur->right = new node();
                    }
                    cur = cur->right;
                }
                else if (line[i] == 'L')
                {
                    if (cur->left == nullptr)
                    {
                        cur->left = new node();
                    }
                    cur = cur->left;
                }
            }
            cur->cnt_assign++;
            cur->value = value;
        }

        bool valid = true;
        queue<node*> que_traver;
        queue<int> que_value;
        que_traver.push(root);
        while (!que_traver.empty())
        {
            node* cur = que_traver.front(); que_traver.pop();
            if (cur->cnt_assign != 1)
            {
                valid = false;
            }
            else if (valid)
            {
                que_value.push(cur->value);
            }

            if (cur->left != nullptr) que_traver.push(cur->left);
            if (cur->right != nullptr) que_traver.push(cur->right);
            delete cur;
        }

        if (valid)
        {
            while (que_value.size() > 1)
            {
                cout << que_value.front() << " ";
                que_value.pop();
            }
            if (!que_value.empty())
            {
                cout << que_value.front();
            }
        }
        else
        {
            cout << "not complete";
        }
        cout << endl;
    }

    return 0;
}