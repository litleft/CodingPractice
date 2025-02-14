#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    map<string, string> dict;
    set<string> ans;

    string buf;
    while (cin >> buf)
    {
        if (buf == "#") break;

        string key = buf;
        for (int i = 0; i < key.length(); i++)
        {
            key[i] = tolower(key[i]);
        }
        sort(key.begin(), key.end());
        
        if (dict.find(key) == dict.end())
        {
            dict[key] = buf;
            ans.insert(buf);
        }
        else
        {
            ans.erase(dict[key]);
        }
    }

    for (auto p = ans.begin(); p != ans.end(); p++)
    {
        cout << *p << endl;
    }
}