#include "singleton.h"

Singleton* Singleton::pinstence_ = nullptr;
std::mutex Singleton::mutex_;
Singleton* Singleton::GetInstence() {
    if (pinstence_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pinstence_ == nullptr) {
            pinstence_ = new Singleton();
        }
    }
    return pinstence_;
}