#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

struct sen_id
{
    int web_idx;
    int sen_idx;

    bool operator<(const sen_id & o) const
    {
        if (web_idx == o.web_idx) return sen_idx < o.sen_idx;
        return web_idx < o.web_idx;
    }
};

struct web_relative_info
{
    set<sen_id> sen_related;
    set<int> web_related;
};

#define REP(i, n) for ( int i = 0; i < (int)n; i++)
template<typename... Args>
struct pack { };

vector<string> sentences;

template<class container>
void print(container con)
{
    int last_web = -1;
    for (auto& it : con)
    {
        if (last_web == -1) last_web = it.web_idx;
        else if (last_web != it.web_idx)
        {
            last_web = it.web_idx;
            cout << "----------" << endl;
        }
        cout << sentences[it.sen_idx] << endl;
    }
}

int main()
{
    vector<int> web_b;
    vector<int> web_l;

    map<string, web_relative_info> dict;
    set<string> words;
    string line, word;

    int web_cnt;
    cin >> web_cnt;
    getline(cin, line);
    REP(web_idx, web_cnt)
    {
        web_b.emplace_back(sentences.size());
        int web_sentences_cnt = 0;

        while (getline(cin, line) && line != "**********")
        {
            web_sentences_cnt++;
            int sen_idx = sentences.size();
            sentences.push_back(line);

            REP(i, line.size())
            {
                if (isalpha(line[i]))
                {
                    line[i] = tolower(line[i]);
                }
                else
                {
                    line[i] = ' ';
                }
            }

            stringstream ss(line);
            words.clear();
            while (ss >> word)
            {
                words.insert(word);
            }

            for (auto& w : words)
            {
                dict[w].web_related.insert(web_idx);
                dict[w].sen_related.insert({web_idx, sen_idx});
            }
        }

        web_l.emplace_back(web_sentences_cnt);
    }

    int cmd_cnt;
    cin >> cmd_cnt;
    string key1, rel, key2;

    auto print_mid = []()
    {
        cout << "----------" << endl;
    };

    auto print_nores = []()
    {
        cout << "Sorry, I found nothing." << endl;
    };

    getline(cin, line);
    REP(cmd, cmd_cnt)
    {
        getline(cin, line);
        bool fisrt_match = true;

        if (line.size() > 4 && line.substr(0,3) == "NOT")
        {
            string key = line.substr(4);
            auto it = dict.find(key);
            int res_cnt = 0;
            REP(web_idx, web_cnt)
            {
                if (it != dict.end() && it->second.web_related.count(web_idx) != 0)
                    continue;
                
                if (fisrt_match) fisrt_match = false;
                else print_mid();

                for (int i = 0; i < web_l[web_idx]; i++)
                {
                    cout << sentences[i + web_b[web_idx]] << endl;
                }
                res_cnt++;
            }
            if (res_cnt == 0) print_nores();
        }
        else
        {
            stringstream ss(line);
            ss >> key1;
            if (ss >> rel)
            {
                ss >> key2;
                set<int> related_web;
                set<sen_id> related_sen;

                using set_it = set<int>::iterator;
                using ins_it = insert_iterator<set<int>>;
                #define SET_OP_PAR set_it p1, set_it p2, set_it p3, set_it p4, ins_it p5
                #define SET_OP_ARG p1, p2, p3, p4, p5
                #define SET_OP_ANONY(func) [] (SET_OP_PAR) { func(SET_OP_ARG); }
                #define DO_JOB_WITH_OP(func) do_job_with_set_op(SET_OP_ANONY(func))
                using set_op_type = function<void(SET_OP_PAR)>;
                
                // 通过用匿名函数包裹，把需要模板化的函数 如（set_union, set_intersection)
                // 传入到重复的逻辑当中，如果有auto的匿名函数（C++14），会写的更方便
                // PS. 这里只是尝试玩一下，其实直接用ifelse就行了

                auto do_job_with_set_op = [&](set_op_type func)
                {
                    static set<int> empty;

                    auto it1 = dict.find(key1);
                    auto it2 = dict.find(key2);

                    auto& web1 = it1 == dict.end() ? empty : it1->second.web_related;
                    auto& web2 = it2 == dict.end() ? empty : it2->second.web_related;

                    func(web1.cbegin(), web1.cend(),
                            web2.cbegin(), web2.cend(),
                            inserter(related_web, related_web.begin()));
                    
                    using map_it_type = map<string, web_relative_info>::iterator;
                    auto insert_sen = [&](map_it_type it)
                    {
                        if (it != dict.end())
                        {
                            for (auto& i : it->second.sen_related)
                            {
                                if (related_web.count(i.web_idx) > 0)
                                {
                                    related_sen.insert(i);
                                }
                            }
                        }
                    };

                    if (related_web.empty()) print_nores();
                    else
                    {
                        insert_sen(it1);
                        insert_sen(it2);
                        print(related_sen);
                    }
                };

                if (rel == "OR")
                {
                    DO_JOB_WITH_OP(set_union);
                }
                else
                {
                    DO_JOB_WITH_OP(set_intersection);
                }
            }
            else
            {
                auto it = dict.find(key1);
                if (it == dict.end())
                {
                    print_nores();
                }
                else
                {
                    print(it->second.sen_related);
                }
            }
        }
    
        cout << "==========" << endl;
    }

}