#include <condition_variable>
#include <thread>
#include <mutex>
#include <random>
#include <stdlib.h>
#include <iostream>

using namespace std;

condition_variable cv_c, cv_p;
mutex mut;
bool full = false;
int data_;

void cunsumer()
{
    int i = 0;
    while (i++ < 100)
    {
        unique_lock<mutex> lk(mut);
        cv_c.wait(lk, [] { return full; });

        cout << "Consum " << data_ << endl;
        data_ = 0;
        full = false;
        cv_p.notify_one();
    }
}

void provider()
{
    srand(123123);
    int i = 0;
    while (i++ < 100)
    {
        unique_lock<mutex> lk(mut);
        cv_p.wait(lk, []{return full == false; });

        data_ = rand();
        full = true;
        cout << "Provide " << data_ << endl;
        cv_c.notify_one();
    }
}

int main()
{
    thread cu(cunsumer);
    thread pr(provider);

    cu.join();
    pr.join();
}