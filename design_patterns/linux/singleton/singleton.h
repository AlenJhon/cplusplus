#ifndef SINGLETON_H_123
#define SINGLETON_H_123
#include <mutex>

class Singleton {
    static Singleton* pinstence_;
    static std::mutex mutex_;
    Singleton(){}

public:
    static Singleton* GetInstence();
};

#endif