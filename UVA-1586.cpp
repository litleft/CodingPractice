#include <iostream>
#include <iomanip>
#include <string.h>
#include <cctype>
#include <unordered_map>

using namespace std;

int main()
{
    const std::unordered_map<char, float> mol_table = {
        {'C', 12.01f}, {'H', 1.008f}, {'O', 16.00}, {'N', 14.01}
    };

    int case_count;
    cin >> case_count;

    char seq[100];

    for (int c = 0; c < case_count; c++)
    {
        cin >> seq;

        int cur_c = 0;
        float cur_g = 0.0f;
        float g = 0.0f;

        int i = 0;
        while(true)
        {
            bool end = seq[i] == '\0';

            if (end || isdigit(seq[i]) == 0)
            {
                g += cur_g * (float)(cur_c > 0 ? cur_c : 1);

                if (end) break;

                cur_g = mol_table.at(seq[i]);
                cur_c = 0;
            }
            else
            {
                cur_c = cur_c * 10 + (int)(seq[i] - '0');
            }
            i++;
        }
        cout << fixed << setprecision(3) << g << endl;
    }
}