#include <iostream>
#include <string>
using namespace std;

int convhex(char c) {
    if (c == 'A' || c == 'a') {
        return 10;
    } else if (c == 'B' || c == 'B') {
        return 11;
    } else if (c == 'C' || c == 'c') {
        return 12;
    } else if (c == 'D' || c == 'd') {
        return 13;
    } else if (c == 'E' || c == 'e') {
        return 14;
    } else if (c == 'F' || c == 'f') {
        return 15;
    }
    char tmp[10] = {0};
    snprintf(tmp, 10, "%c", c);
    return atoi(tmp);//no need care else case
}

int main() {
    string str;
    int n = 0;
    int tmp = 1;
    while (cin >> str) {
        tmp = 1;
        for (int i = str.size()-1; i > 1; --i) {
            n += convhex(str[i])*tmp;
            tmp *= 16;
        }
        cout << n << endl;
        n = 0 ;
    }
    return 0;
}