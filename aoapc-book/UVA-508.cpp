#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

int main() 
{
    char ch, code[20];
    map<char, string> dir;

    while (true)
    {
        cin >> ch;
        if (ch == '*') break;

        cin >> code;
        dir[ch] = string(code);
    }

    string word;
    map<string, vector<string>> word_dir;
    while (true)
    {
        cin >> word;
        if (word == "*") break;

        stringstream ss;
        for (char c : word)
        {
            ss << dir[c];
        }

        word_dir[ss.str()].push_back(word);
    }

    string input_code;
    while (true)
    {
        cin >> input_code;
        if (input_code == "*") break;

        auto it = word_dir.find(input_code);
        if (it != word_dir.end())
        {
            bool is_dupl = it->second.size() > 1;
            cout << it->second[0] << (is_dupl ? "!" : "") << endl;
        }
        else
        {
            string res;
            int min_dist = 1000000;
            int in_code_len = input_code.size();
            for (auto p : word_dir)
            {
                if (p.first.substr(0, in_code_len) == input_code
                    || input_code.substr(0, p.first.size()) == p.first)
                {
                    int dist = abs((int)p.first.size() - in_code_len);
                    if (dist < min_dist)
                    {
                        min_dist = dist;
                        res = p.second[0];
                    }
                }
            }

            cout << res << "?" << endl;
        }
    }

    return 0;
}