// #include <iostream>
// #include <unordered_map>

// using namespace std;

// int main() {

//     char key[]= {'3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A', '2', 'r', 'R'};


//     return 0;
// }



#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string line;
    while( getline(cin,line) ) {
        if(line.find("joker JOKER") != -1) {
            cout << "joker JOKER" << endl;
        }
        else {
            int dash = line.find('-');
            string car1 = line.substr(0, dash);
            string car2 = line.substr(dash + 1);

            int c1 = count(car1.begin(), car1.end(), ' ');
            int c2 = count(car2.begin(), car2.end(), ' ');

            string first1 = car1.substr(0, car1.find(' '));
            string first2 = car2.substr(0, car2.find(' '));

            string str="345678910JQKA2jokerJOKER";
            if(c1 == c2){
                if( str.find(first1) > str.find(first2) ) {
                    cout << car1 << endl;
                }
                else {
                    cout << car2 << endl;
                }
            }else {
                if(c1 == 3)
                    cout << car1 << endl;
                else if(c2 == 3)
                    cout << car2 << endl;
                else
                    cout << "ERROR" << endl;
            }

        }
    }
}