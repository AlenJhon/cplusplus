#include <iostream>
using namespace std;

class TESTSIZE {
private:
    bool is_x;
    int  ia;
    int  ib;
    int  ic;
    bool is_y;
};

struct stTESTSIZE {
    bool is_x;
    int ia;
    int ib;
    int ic;
    bool is_y;
};

// test in bit 64 os
class szx1 {
    //index1 8 Bytes
    int *m_pBuff;// sizeof() == 8

    //index2 8 Bytes
    char m_bProperty;
    char m_bx;
    int m_iNextIndex;

    // index 3  8 Bytes
    int m_iPreIndex;
    int m_ix;
};

// template <typename _Type>
// void ShowBaseTypeSize(_Type t){
//     cout << "sizeof()=" << sizeof(t) << endl;
// }

void TestSizeofClass(){
    cout << "TESTSIZE=" << sizeof(TESTSIZE) << endl;
    cout << "stTESTSIZE=" << sizeof(stTESTSIZE) << endl;
    cout << "sizeof(szx1)=" << sizeof(szx1) << endl;
    cout << "sizeof(int)=" << sizeof(int) << endl;
    cout << "sizeof(long)=" << sizeof(long) << endl;
    cout << "sizeof(double)=" << sizeof(double) << endl;
    cout << "sizeof(float)=" << sizeof(float) << endl;
    cout << "sizeof(short)=" << sizeof(short) << endl;

    if (nullptr == NULL){
        cout << "nullptr == NULL ok ." << endl;
    }
}