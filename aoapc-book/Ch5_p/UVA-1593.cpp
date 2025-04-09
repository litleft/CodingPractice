#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> word_max_len;
    vector<vector<string>> words;
    string line, word;
    while (getline(cin, line))
    {
        words.push_back(vector<string>());
        stringstream ss(line);

        int i = 0;
        while (ss >> word)
        {
            if (i >= word_max_len.size())
            {
                word_max_len.push_back(word.size());
            }
            else
            {
                word_max_len[i] = max(word_max_len[i], (int)word.size());
            }
            words.back().push_back(word);
            i++;
        }
    }

    for (auto& l : words)
    {
        for (int i = 0; i < l.size(); i++)
        {
            cout << l[i];
            if (i < l.size() - 1)
            {
                int len = word_max_len[i] - l[i].size() + 1;
                printf("%*c", len, ' ');
            }
        }
        cout << endl;
    }

    return 0;
}