#include <iostream>
#include <unordered_set>
#include <set>

using namespace std;

int main()
{
    string word;
    unordered_set<string> dict;
    set<string> compound;

    while (cin >> word)
    {
        dict.insert(word);
    }
    for (auto& w : dict)
    {
        for (int i = 1; i < w.size(); i++)
        {
            string prefix = w.substr(0, i);
            string suffix = w.substr(i);
            if (dict.find(prefix) != dict.end() && dict.find(suffix) != dict.end())
            {
                compound.insert(w);
                break;
            }
        }
    }
    for (auto& w : compound)
    {
        cout << w << endl;
    }
    return 0;
}