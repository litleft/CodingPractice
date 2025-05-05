#include "tools.hpp"

enum struct state_t : uint_8
{
    uninstall,
    install_ex,
    install_im,
};

const string indent = "   ";

// install order
const int header = -1;
const int tail = -2;
int head_next;
int tail_prev;

struct package
{
    string name;
    vector<int> depends;

    state_t state;
    int ref_cnt;

    int prev_ins;
    int next_ins;

    package(const string& name_) 
        : name(name_)
        , depends()
        , state(state_t::uninstall)
        , ref_cnt(0)
        , prev_ins(header)
        , next_ins(tail)
    {}
};

map<string, int> name2id;
vector<package> packages;

int get_id(const string& name)
{
    auto it = name2id.find(name);
    if (it == name2id.end())
    {
        int id = packages.size();
        name2id[name] = id;
        packages.emplace_back(name);
        return id;
    }
    else
    {
        return it->second;
    }
}

void link(int a, int b)
{
    if (a == header)
    {
        head_next = b;
    }
    else
    {
        packages[a].next_ins = b;
    }
    if (b == tail)
    {
        tail_prev = a;
    }
    else
    {
        packages[b].prev_ins = a;
    }
}

void dfs_install(int id)
{
    auto& pkg = packages[id];
    if (pkg.state == state_t::uninstall)
    {
        for (int dep_id : pkg.depends)
        {
            dfs_install(dep_id);
        }

        cout << indent << "Installing " << pkg.name << endl;
        pkg.state = state_t::install_im;
        link(tail_prev, id);
        link(id, tail);
    }
    pkg.ref_cnt++;
}

void install(int id)
{
    auto& pkg = packages[id];
    switch (pkg.state)
    {
        case state_t::install_im:
        case state_t::install_ex:
            cout << indent << pkg.name << " is already installed." << endl;
            break;
        case state_t::uninstall:
        {
            dfs_install(id);
            pkg.state = state_t::install_ex;
            pkg.ref_cnt--;
            break;
        }
    }
}

void dfs_uninstall(int id)
{
    auto& pkg = packages[id];
    if (pkg.ref_cnt == 0)
    {
        cout << indent << "Removing " << pkg.name << endl;
        pkg.state = state_t::uninstall;
        link(pkg.prev_ins, pkg.next_ins);

        for (int dep_id : pkg.depends)
        {
            packages[dep_id].ref_cnt--;

            if (packages[dep_id].state == state_t::install_im)
            {
                dfs_uninstall(dep_id);
            }
        }
    }
}

void uninstall(int id)
{
    auto& pkg = packages[id];
    switch (pkg.state)
    {
        case state_t::install_ex:
        case state_t::install_im:
            dfs_uninstall(id);
            if (pkg.ref_cnt > 0)
            {
                cout << indent << pkg.name << " is still needed." << endl;
            }
            break;
        case state_t::uninstall:
            {
                cout << indent << pkg.name << " is not installed." << endl;
                break;
            }
    }
}

void list_install()
{
    int cur = head_next;
    while (cur != tail)
    {
        cout << indent << packages[cur].name << endl;
        cur = packages[cur].next_ins;
    }
}

int main()
{
    stringstream ss;
    string line, token;
    while (getline(cin, line))
    {
        name2id.clear();
        packages.clear();
        link(header, tail);

        while (true)
        {
            cout << line << endl;
            ss.str(line);
            ss.clear();
            ss >> token;

            if (token == "END")
            {
                break;
            }
            else if (token == "DEPEND")
            {
                ss >> token;
                int id = get_id(token);
                while (ss >> token)
                {
                    int dep_id = get_id(token);
                    packages[id].depends.push_back(dep_id);
                }
            }
            else if (token == "INSTALL")
            {
                ss >> token;
                int id = get_id(token);
                install(id); 
            }
            else if (token == "REMOVE")
            {
                ss >> token;
                int id = get_id(token);
                uninstall(id);
            }
            else if (token == "LIST")
            {
                list_install();
            }

            getline(cin, line);
        }
    }
}