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


int main()
{
    int case_cnt;
    cin >> case_cnt;

    unordered_map<string, int> prefix2n;
    prefix2n["1"] = 0;

    unordered_set<string> input_set;
    vector<string> inputs;

    map<int, int> prefix_len2cnt;

    string prefix, buf;
    REP(case_no, case_cnt)
    {
        cin >> buf;
        int prefix_len = buf.size();

        /// TIPS1 数太大，需要使用string add，逆序存放方便后面计算
        prefix.resize(prefix_len);
        REP (i, prefix_len)
        {
            prefix[i] = buf[prefix_len - 1 - i];
        }

        inputs.push_back(prefix);
        if (prefix == "1") continue;

        input_set.insert(prefix);
        prefix_len2cnt[prefix_len]++;
    }

    vector<int> removed_len;
    int n = 2, fib2_len = 1, fib1_len = 1, fib_len;
    string fib2 = "1", fib1 = "1", fib;

    auto string_add = [&]()
    {
        fib.resize(fib1_len);
        char carry = 0;
        int i2 = 0, i1 = 0;
        while (i1 < fib1_len)
        {
            char added = i2 < fib2_len ? fib2[i2] - '0' : 0;
            added += (fib1[i1] + carry);
            if (added > '9')
            {
                added -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            fib[i1] = added;
            i1++;
            i2++;
        }
        if (carry == 1)
        {
            fib.resize(fib1_len + 1);
            fib[fib1_len] = '1';

            /// TIPS2 计算太多了，计算全部精度会超时
            ///       因为输入保证最多只有40位，这里截取前50位即可
            ///       截取后的进位很难影响到前40的数值 
            if (fib1_len == 50)
            {
                fib = fib.substr(1);
                fib2 = fib2.substr(1);
                fib1 = fib1.substr(1);
                fib2_len--;
                fib1_len--;
                fib_len = 50;
            }
            else
            {
                fib_len = fib1_len + 1;
            }
        }
        else
        {
            fib_len = fib1_len;
        }
    };

    auto next_fib = [&]()
    {
        fib2 = fib1;
        fib1 = fib;
        fib2_len = fib1_len;
        fib1_len = fib_len;
        n++;
    };

    while(!input_set.empty() && n < 100000)
    {
        string_add();

        removed_len.clear();
        for (auto& it : prefix_len2cnt)
        {
            if (it.first > fib_len)
            {
                break;
            }

            prefix = fib.substr(fib_len - it.first);
            if (input_set.count(prefix) > 0)
            {
                input_set.erase(prefix);
                prefix2n[prefix] = n;

                it.second--;
                if (it.second == 0)
                {
                    removed_len.push_back(it.first);
                }
            }
        }
        for (int i : removed_len)
        {
            prefix_len2cnt.erase(i);
        }

        next_fib();
    }
    for (auto const& it : input_set)
    {
        prefix2n[it] = -1;
    }

    REP(i, case_cnt)
    {
        printf("Case #%d: %d\n", i + 1, prefix2n[inputs[i]]);
    }
}

