#include <assert.h>
// #include <stdint.h>
#include <stdlib.h>
#include <iostream>


using namespace std;


inline int RangeRand(int lowerbound, int upperbound)
{
    assert(lowerbound <= upperbound);

    return lowerbound + (int)((upperbound - lowerbound + 1) * (rand() / (RAND_MAX + 1.0)));
}

inline int SafeRangeRand(int lowerbound, int upperbound)
{
    if (lowerbound <= upperbound)
    {
        return lowerbound + (int)((upperbound - lowerbound + 1) * (rand() / (RAND_MAX + 1.0)));
    }
    return upperbound + (int)((lowerbound - upperbound + 1) * (rand() / (RAND_MAX + 1.0)));
}




int main() {
    cout << "Hello Random ..." << endl;
    cout << "RangeRand(1,1)" << RangeRand(1, 1) << endl;
    cout << "SafeRangeRand(1,1)" << SafeRangeRand(1, 1) << endl;

    return 0;
}