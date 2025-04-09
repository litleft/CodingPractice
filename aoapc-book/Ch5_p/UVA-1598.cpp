#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_map>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>
#include <functional>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define EPS 1e-5
#define FLOAT_EQ(a, b) (abs(a - b) < EPS)

using namespace std;



struct order
{
    int id;
    int size;
    int price;
    bool b_not_s;
};

int main()
{
    int bid_price, ask_price;
    vector<order> orders;
    map<int, int> buy_p2s, sell_p2s;
    auto compare_maker = [&](bool small_price_top)
    {
        // 这里直接用&自动捕获的话，small_price_top也被作为引用捕获
        // 而下面的small_price_top传入的是临时变量，会出现未定义行为
        // return [&](int a, int b)      XXXXXX WRONG！！！
        return [&orders,small_price_top](int a, int b)
        {
            auto& o1 = orders[a];
            auto& o2 = orders[b];
            
            if (o1.price != o2.price)
            {   
                return (o1.price < o2.price) != small_price_top;
            }
            return o1.id > o2.id;
        };
    };
    using compare_func_type = function<bool(int,int)>;
    using queue_type = priority_queue<int, vector<int>, compare_func_type>;
    queue_type buy_que(compare_maker(false)),  sell_que(compare_maker(true));

    auto update_que = [&orders](int& p, queue_type& q, map<int, int>& p2s, int d_price)
    {
        while (!q.empty() && orders[q.top()].size == 0) q.pop();
        if (!q.empty())
        {
            p = orders[q.top()].price;
        }
        else
        {
            p = d_price;
        }
    };
    auto update_ask = [&]() { update_que(ask_price, sell_que, sell_p2s, 99999); };
    auto update_bid = [&]() { update_que(bid_price, buy_que, buy_p2s, 0); }; 

    auto print_quote = [&]()
    {
        printf("QUOTE %d %d - %d %d\n", buy_p2s[bid_price], bid_price, sell_p2s[ask_price], ask_price);
    };

    auto print_trade = [&](int s, int p)
    {
        printf("TRADE %d %d\n", s, p);
    };

    auto cancel_order = [&](int id)
    {
        if (id >= orders.size()) return;

        auto& o = orders[id];
        if (o.size == 0) return;

        if (o.b_not_s)
        {
            buy_p2s[o.price] -= o.size;
            o.size = 0;
            update_bid();
        }
        else
        {
            sell_p2s[o.price] -= o.size;
            o.size = 0;
            update_ask();
        }
    };

    auto on_buy_order = [&](order& o)
    {
        // TIPS 这里一定要加上empty，因为99999是合法的输入
        //      不能保证ask_price的默认最大值比o.price大 
        while (!sell_que.empty() && ask_price <= o.price && o.size > 0)
        {
            order& sell_o = orders[sell_que.top()];

            bool buy_all = o.size >= sell_o.size;
            int trade_size = buy_all ? sell_o.size : o.size;
            print_trade(trade_size, ask_price);

            o.size -= trade_size;
            sell_o.size -= trade_size;
            sell_p2s[ask_price] -= trade_size;

            if (buy_all) update_ask();
        }

        if (o.size != 0)
        {
            buy_p2s[o.price] += o.size;
            buy_que.push(o.id);
            update_bid();
        }
    };

    auto on_sell_order = [&](order& o)
    {
        while (!buy_que.empty() && bid_price >= o.price && o.size > 0)
        {
            order& buy_o = orders[buy_que.top()];

            bool supply_all = o.size >= buy_o.size;
            int trade_size = supply_all ? buy_o.size : o.size;
            print_trade(trade_size, bid_price);
            
            o.size -= trade_size;
            buy_o.size -= trade_size;
            buy_p2s[bid_price] -= trade_size;

            if (supply_all) update_bid();
        }

        if (o.size != 0)
        {
            sell_p2s[o.price] += o.size;
            sell_que.push(o.id);
            update_ask();
        }
    };

    string cmd;
    int cmd_cnt;
    int case_cnt;
    while (cin >> cmd_cnt && cmd_cnt != 0)
    {
        if (case_cnt++ > 0) cout << endl;

        bid_price = 0;
        ask_price = 99999;
        orders.clear();
        buy_p2s.clear();
        sell_p2s.clear();
        while(!buy_que.empty()) buy_que.pop();
        while(!sell_que.empty()) sell_que.pop();

        REP(cmd_id, cmd_cnt)
        {
            cin >> cmd;
            orders.emplace_back();
            if (cmd == "CANCEL")
            {
                int id;
                cin >> id;
                cancel_order(id - 1);
            }
            else
            {
                order& o = orders.back();
                o.id = cmd_id;
                cin >> o.size >> o.price;
                if (cmd == "BUY")
                {
                    o.b_not_s = true;
                    on_buy_order(o);
                }
                else
                {
                    o.b_not_s = false;
                    on_sell_order(o);
                }
            }
            print_quote();
        }
    }

    return 0;
}