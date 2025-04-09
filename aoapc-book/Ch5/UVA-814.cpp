#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>

#include <algorithm>
#include <cmath>

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define FORD(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)

using namespace std;

struct msg
{
    char cmd; // S for send
    int code;
    string par;
};

const int ok_code = 250;
const int no_code = 550;
const int data_code = 354;
const int quit_code = 221;

struct mta
{
    string name;
    set<string> users;

    mta* connection;
    msg msg_buf;

    inline void send_to(mta* other, string const& from, vector<string> const& to, string const& data)
    {
        printf("Connection between %s and %s\n", name.c_str(), other->name.c_str());
        connection = other;

        send_cmd('H');
        send_cmd('M', from);
        int real_users = 0;
        for (auto const& t : to)
        {
            send_cmd('R', t);
            if (connection->msg_buf.code == ok_code)
            {
                real_users++;
            }
        }
        if (real_users > 0)
        {
            send_cmd('D');
            send_cmd('.', data);
        }
        send_cmd('Q');
    }

    void send_cmd(char cmd, string const& par = "")
    {
        msg_buf.cmd = cmd;
        msg_buf.par = par;

        switch (cmd)
        {
        case 'H':
            printf("     HELO %s\n", name.c_str());
            break;
        case 'M':
            printf("     MAIL FROM:<%s@%s>\n", msg_buf.par.c_str(), name.c_str());
            break;
        case 'R':
            printf("     RCPT TO:<%s@%s>\n", msg_buf.par.c_str(), connection->name.c_str());
            break;
        case 'D':
            printf("     DATA\n");
            break;
        case 'Q':
            printf("     QUIT\n");
            break;
        case '.':
            printf("%s     .\n", msg_buf.par.c_str());
            break;
        default:
            printf("Unknown command: %c\n", msg_buf.cmd);
            break;
        }

        connection->recv_cmd(msg_buf);
    }


    void recv_cmd(msg const& msg)
    {
        switch (msg.cmd)
        {
        case 'H': send_code(ok_code); break;
        case 'M': send_code(ok_code); break;
        case 'R': handle_rcpt(msg); break;
        case 'D': send_code(data_code); break;
        case '.': send_code(ok_code); break;
        case 'Q': send_code(quit_code); break;
        default: printf("Unknown command: %c\n", msg.cmd); break;
        }
    }

    inline void send_code(int code)
    {
        msg_buf.code = code;
        printf("     %d\n", msg_buf.code);
    }

    inline void handle_rcpt(msg const& msg)
    {
        if (users.find(msg.par) != users.end())
        {
            send_code(ok_code);
        }
        else
        {
            send_code(no_code);
        }
    }
};

void split(string const& s, string & users, string & server)
{
    size_t pos = s.find('@');
    users = s.substr(0, pos);
    server = s.substr(pos + 1);
}

int main()
{
    map<string, mta> mtas;
    string buf;
    while (cin >> buf && buf != "*")
    {
        cin >> buf;
        mta& m = mtas[buf];
        m.name = buf;
        int n;
        cin >> n;
        REP(i, n)
        {
            cin >> buf;
            m.users.insert(buf);
        }
    }

    vector<string> rect_servers;
    map<string, vector<string>> recv_users_map;
    set<string> recv_users;

    string from_ser, from_user;
    string to_ser, to_user;
    
    while (cin >> buf && buf != "*")
    {
        split(buf, from_user, from_ser);

        rect_servers.clear();
        recv_users_map.clear();
        recv_users.clear();

        while (cin >> buf && buf != "*")
        {
            if (recv_users.find(buf) != recv_users.end())
            {
                continue;
            }
            recv_users.insert(buf);

            split(buf, to_user, to_ser);
            if (recv_users_map.find(to_ser) == recv_users_map.end())
            {
                rect_servers.push_back(to_ser);
                recv_users_map[to_ser] = vector<string>();
            }
            recv_users_map[to_ser].push_back(to_user);
        }

        getline(cin, buf); // skip the newline
        string data = "";
        while (getline(cin, buf) && buf != "*")
        {
            data += "     " + buf + "\n";
        }

        for (auto const& serv : rect_servers)
        {
            mta* recv_ser = &mtas[serv];
            auto& users = recv_users_map[serv]; 
            mtas[from_ser].send_to(recv_ser, from_user, users, data);
        }
    }

    return 0;
}