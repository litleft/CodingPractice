#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    using namespace std;
    const int max_col = 60;
    int max_len = 0, n;
    vector<string> words;
    string word;
    while (cin >> n)
    {
        max_len = 0;
        words.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> word;
            words.push_back(word);
            if (word.size() > max_len)
            {
                max_len = word.size();
            }
        }
        sort(words.begin(), words.end());

        int col = (max_col + 2) / (max_len + 2);
        int row = (n + col - 1) / col;
        cout << "------------------------------------------------------------" << endl;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                int idx = j * row + i;
                if (idx < n)
                {
                    cout << words[idx];
                    int space = max_len - words[idx].size();
                    if (j < col - 1)
                    {
                        space += 2;
                    }
                    for (int k = 0; k < space; k++)
                    {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }
    }

    return 0;
}