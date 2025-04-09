#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)

template<class cont>
void print(char ch, cont c)
{
    int size = c.size();
    if (size == 0) return;

    cout << ch;
    int i = 0;
    for (auto it : c)
    {
        cout << it;
        if (i++ < size - 1) cout << ",";
    }
    cout << endl;
}

int main()
{
    int kase_cnt;
    cin >> kase_cnt;

    string line, key, value;
    map<string, string> dict;
    set<string> key_set;
    vector<string> add, change;

    auto get_key_value = [&](int begin)
    {
        int key_end = line.find(':', begin);
        int value_end = line.find_first_of(",}", key_end);
        key = line.substr(begin, key_end - begin);
        value = line.substr(key_end + 1, value_end - key_end - 1);
        return value_end + 1;
    };

    getline(cin, line);
    for (int kase = 0; kase < kase_cnt; kase++)
    {
        add.clear();
        change.clear();
        key_set.clear();
        dict.clear();

        getline(cin, line);
        int b = 1;
        while (b < line.size() - 1)
        {
            b = get_key_value(b);
            dict[key] = value;
            key_set.insert(key);
        }

        getline(cin, line);
        b = 1;
        while (b < line.size() - 1)
        {
            b = get_key_value(b);

            auto it = dict.find(key);
            if (it == dict.end())
            {
                add.push_back(key);
            }
            else
            {
                key_set.erase(key);
                if (it->second != value)
                {
                    change.push_back(key);
                }
            }
        }

        sort(add.begin(), add.end());
        sort(change.begin(), change.end());


        if (add.size() == 0 && change.size() == 0 && key_set.size() == 0)
        {
            cout << "No changes\n";
        }
        else
        {
            print('+', add);
            print('-', key_set);
            print('*', change);
        }
        cout << endl;
    }

    return 0;
}