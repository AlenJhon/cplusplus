#include <iostream>
#include <stdint.h>

using namespace std;

/**
 * 以下结构 entry_t 这样做的好处是方便寻址，按某个大小对齐 ， 提供的空间又足够使用
 *
 */


struct entry_t {
    uint32_t a:1;  // :1   修饰后该字段占用一个bit
    uint32_t b:31; // :31  占用31bit
    uint32_t c;   
};

struct entry_t_v2 {
    int a;
    int b;
    int c;
};


int main(){
    struct entry_t st;
    struct entry_t_v2 st_v2;

    st.a = 1;
    st.b = 2;
    cout << st.a << ", " << st.b << endl; // 1, 2
    cout << sizeof(st) << endl;           // 8

    cout << sizeof(st_v2) << endl;        // 12
    return 0;
}
