#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

#define rep_f(i, n) for (int i = 0; i < n; i++)

struct player
{
    string name;
    bool is_am;

    bool is_dq;
    int turn;
    int score[4];
    int prev2_score;
    int total_score;

    bool is_tie;
    int place;

    bool get_price;
    double price;

    player() = default;

    player(const string str)
    {
        name = str.substr(0, 20);
        is_am = name.find('*') != string::npos;

        is_dq = false;
        turn = 4;
        rep_f(i, 4)
            score[i] = 99999;
        rep_f(i, 4)
        {
            if (str[20 + i * 3 + 1] == 'D')
            {
                is_dq = true;
                turn = i;
                break;
            }
            else
            {
                score[i] = atoi(str.substr(20 + i * 3, 3).c_str());
            }
        }
        prev2_score = score[0] + score[1];
        total_score = 0;
        rep_f(i, 4)
            total_score += score[i];        

        is_tie = false;
        get_price = false;
    }

    void print()
    {
        cout << name;
        if (is_dq)
        {
            printf("%*c", 11, ' ');
        }
        else
        {
            bool has_t = is_tie && get_price;
            printf(" %-10s", (to_string(place + 1) + (has_t ? "T" : "")).c_str());
        }

        rep_f(i, 4)
        {
            if (i < turn)
            {
                printf("%-5d", score[i]);
            }   
            else
            {
                printf("%*c", 5, ' ');
            }
        }

        if (get_price)
        {
            printf("%-10d$%9.2f\n", total_score, price);
        }
        else
        {
            if (is_dq)
            {
                printf("DQ\n");
            }
            else
            {
                printf("%d\n", total_score);
            }
        }
    }
};

struct player_prev2_compare
{
    bool operator()(player const& p1, player const& p2)
    {
        return p1.prev2_score < p2.prev2_score;
    }
};

struct player_compare
{
    bool operator()(player const& p1, player const& p2)
    {
        if (p1.total_score == p2.total_score)
        {
            return p1.name < p2.name;
        }
        return p1.total_score < p2.total_score;
    }
};

int main()
{
    int case_count;
    cin >> case_count;

    string input_buf;
    double price_ratio[70];
    vector<player> players;

    rep_f(case_no, case_count)
    {
        double total_prices;
        cin >> total_prices;
        rep_f(i, 70)
            cin >> price_ratio[i];

        int players_count;
        cin >> players_count;

        players.clear();
        getline(cin, input_buf); // blank line
        for (int i = 0; i < players_count; i++)
        {
            getline(cin, input_buf);
            players.emplace_back(input_buf);
        }
        getline(cin, input_buf); // blank line

        sort(players.begin(), players.end(), player_prev2_compare());

        for (int i = 70; i < players_count; i++)
        {
            if (players[i].prev2_score != players[i-1].prev2_score)
            {
                players_count = i;
                break;
            }
        }
        for (int i = players_count - 1; i >= 0; i--)
        {
            if (players[i].turn > 1)
            {
                players_count = i + 1;
                break;
            }
        }
        players.resize(players_count);

        sort(players.begin(), players.end(), player_compare());

        int place = 0;
        int price_index = 0;

        int prev_score = -1;
        int tie_place = 0;
        vector<int> tie_player;

        bool empty_pool = true;
        double price_pool = 0;
        int pooled_player_count = 0;

        auto split_price = [&]()
        {
            if (tie_player.size() == 0) return;

            double price_splited = price_pool * total_prices / (double)pooled_player_count / 100.0;
            bool is_tie = pooled_player_count > 1;
            for (int i : tie_player)
            {
                bool can_get_price = !players[i].is_am && !players[i].is_dq;
                players[i].price = price_splited;
                players[i].get_price = can_get_price && !empty_pool;
                players[i].place = tie_place;
                players[i].is_tie = is_tie;
            }
            tie_player.clear();
            pooled_player_count = 0;
            price_pool = 0.0;
            empty_pool = true;
        };

        for (int i = 0; i < players.size(); i++, place++)
        {
            auto& p = players[i];
            if (p.is_dq) 
            {
                split_price();
                break;
            }
            if (p.total_score != prev_score)
            {
                split_price();
                prev_score = p.total_score;
                tie_place = place;
            }
            tie_player.emplace_back(i);
            if (!p.is_am)
            {
                if (price_index < 70)
                {
                    price_pool += price_ratio[price_index++];
                    empty_pool = false;
                }
                pooled_player_count++;
            }
        }
        split_price();
        
        
        printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
        printf("-----------------------------------------------------------------------\n");
        for (auto& p : players)
        {
            p.print();
        }
        if (case_no < case_count - 1) cout << endl;
    }


    return 0;
}
