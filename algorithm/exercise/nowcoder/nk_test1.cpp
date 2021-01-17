#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n<3 || n>7) {
            cout << -1 << endl;
            return 0;
        }
        
        int num, tmp, res, idx=0;
        string s;
        bool find = false;
        int start, end;
        
        start = pow(10, n-1);
        end = pow(10, n) - 1;
        cout << start << end << endl;

        for (int i=start; i<=end; ++i){
            num = i;
            string s = to_string(num);
            size_t len = s.size();
            tmp = num;
            res = 0;
            while (len--){
                res += int(pow(tmp%10, 3));
                tmp /= 10;
            }
            
            if (num ==  res){
                if (idx == m){
                    find = true;
                    cout << res << endl;
                    return 0;
                }
                idx += 1;
            }
        }
        if (!find){
            cout << "xxxx" << endl;
            cout << res*m << endl;
        }
    }
    return 0;
}