#include <iostream>
#include <string>
#include <string.h>

using namespace std;

bool is_all_blank(const string& str)
{
    for (char c : str)
    {
        if (c != ' ')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    const int max_word_len = 100;

    int case_no;
    string ans, input;
    bool gussed[26];

    while (cin >> case_no && case_no != -1)
    {
        cin >> ans >> input;

        int game_state = 0;
        int chance = 7;
        memset(gussed, 0, 26);

        for (int i = 0; input[i] != '\0'; i++)
        {
            if (gussed[input[i] - 'a'])
            {
                continue;
            }
            gussed[input[i] - 'a'] = true;

            int ind = ans.find(input[i]);
            if (ind != -1)
            {
                do
                {
                    ans[ind] = ' ';
                    ind = ans.find(input[i], ind + 1);
                } while (ind != -1);

                if (is_all_blank(ans))
                {
                    game_state = 1;
                    break;
                }
            }
            else
            {
                chance--;
                if (chance == 0)
                {
                    game_state = -1;
                    break;
                }
            }
        }

        printf("Round %d\n", case_no);
        switch (game_state)
        {
        case -1:
            printf("You lose.\n");
            break;
        case 0:
            printf("You chickened out.\n");
            break;
        case 1:
            printf("You win.\n");
            break;
        }
    }

    return 0;
}