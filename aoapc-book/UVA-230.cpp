#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

struct book
{
    string writter;
    string title;
    int id;

    bool operator < (const book& b) const
    {
        if (writter != b.writter)
            return writter < b.writter;
        return title < b.title;
    }
};

int main()
{
    vector<book> books;
    string line;
    while (getline(cin, line) && line != "END")
    {
        book b;
        int title_idx = line.find(" by ");
        b.writter = line.substr(title_idx + 4);
        b.title = line.substr(0, title_idx);
        books.emplace_back(move(b));
    }

    sort(books.begin(), books.end());

    map<string, int> book_id;
    set<int> returned, lib;
    for (auto& b : books)
    {
        b.id = lib.size();
        lib.insert(b.id);
        book_id[b.title] = b.id;
    }

    string command, title;
    while (getline(cin, line) && line != "END")
    {
        int cmd_idx = line.find(' ');
        command = line.substr(0, cmd_idx);
        if (command == "BORROW")
        {
            title = line.substr(cmd_idx + 1);
            int id = book_id[title];
            lib.erase(id);
        }
        else if (command == "RETURN")
        {
            title = line.substr(cmd_idx + 1);
            int id = book_id[title];
            returned.insert(id);
        }
        else if (command == "SHELVE")
        {
            for (auto id : returned)
            {
                auto it = lib.lower_bound(id);
                if (it == lib.begin())
                    cout << "Put " << books[id].title << " first" << endl;
                else
                    cout << "Put " << books[id].title << " after " << books[*prev(it)].title << endl;
                lib.insert(id);
            }
            cout << "END" << endl;
            returned.clear();
        }
    }
}