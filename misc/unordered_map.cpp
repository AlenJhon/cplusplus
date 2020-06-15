#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    //std::unordered_map<int , int> umpTest;

    //for (int i=1; i < 10; i++) {
    //    umpTest[ i ] += i + 100;
    //}
    //
    //for (auto it : umpTest) {
    //    std::cout << it.first << " " << it.second << endl;
    //}


    
    std::unordered_map<int , std::vector<int*>> umpTest2;
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    for (int i = 1; i < 10; i++) {
        umpTest2[i].push_back( &array[i] );
    }

    for (auto it : umpTest2) {  
        cout << it.first << " " << *(it.second[0]) << endl;
    }

    
    return 0;
}
