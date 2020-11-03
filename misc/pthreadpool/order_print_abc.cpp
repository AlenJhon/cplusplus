#include<iostream>
#include<vector>
#include<thread>
#include<condition_variable>
using namespace std;

std::mutex mu;
std::condition_variable cond_var;
int num = 0;

void func(char ch) {
    int n = ch - 'A';
    for (int i=0; i<10; ++i) {
        std::unique_lock<std::mutex> mylock(mu);
        cond_var.wait(mylock, [n]{return n==num;});
        cout << ch;
        num = (num+1)%3;
        mylock.unlock();
        cond_var.notify_all();
    }
}

int main() {
    std::vector<thread> pool;
    pool.push_back(thread(func, 'A'));
    pool.push_back(thread(func, 'B'));
    pool.push_back(thread(func, 'C'));
    for (auto iter=pool.begin(); iter != pool.end(); ++iter) {
        iter->join();
    }
    // for (auto iter : pool) {
    //     iter.join();
    // }
    return 0;
}