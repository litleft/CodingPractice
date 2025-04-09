#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <utility>

int main()
{
    using namespace std;

    int row, col;
    string line, word;
    int data[10000][10];
    while (cin >> row >> col)
    {
        getline(cin, line); // blank line
    
        int idx = 0;
        unordered_map<string, int> word2idx;

        for (int r = 0; r < row; r++)
        {
            getline(cin, line);
            istringstream iss(line);
            for (int c = 0; c < col; c++)
            {
                getline(iss, word, ',');
                if (word2idx.find(word) == word2idx.end())
                {
                    word2idx[word] = idx++;
                }
                data[r][c] = word2idx[word];
            }
        }

        map<tuple<int, int>, int> m;
        bool found = false;
        for (int i = 0; i < col && !found; i++)
        {
            for (int j = i + 1; j < col && !found; j++)
            {
                m.clear();
                for (int k = 0; k < row; k++)
                {
                    tuple<int,int> t = {data[k][i], data[k][j]};
                    if (m.count(t) > 0)
                    {
                        cout << "NO" << endl;
                        cout << m[t] + 1 << " " << k + 1 << endl;
                        cout << i + 1 << " " << j + 1 << endl;
                        found = true;
                        break;
                    }
                    else
                    {
                        m[t] = k;
                    }
                }
            }
        }
        if (!found)
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}