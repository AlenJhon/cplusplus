#include <iostream>

using namespace std;

struct OP_ONE
{
    char op;
    uint16_t param1;
    uint16_t param2;
};


void action(OP_ONE* opOne, int* pstu) {
    if (opOne->op == 'Q') {
        int max = 0;
        int end = opOne->param1 > opOne->param2 ? opOne->param1 : opOne->param2;
        int start = opOne->param1 < opOne->param2 ? opOne->param1 : opOne->param2;
        for (int j=start-1; j < end; ++j){
            if (pstu[j] > max) 
                max = pstu[j];
        }
        cout << max << endl;
    }
    if (opOne->op == 'U') {
        pstu[opOne->param1-1] = opOne->param2;
    }
}


int main(int iargc, char* argv[])
{
    int stuNum = 0;
    int paramNum = 0;
    while (cin >> stuNum) {

        // cin >> stuNum;
        cin >> paramNum;
        int* pstu = new int[stuNum];
        OP_ONE* pparam = new OP_ONE[paramNum];

        int tmp = 0;

        int idx = 0;
        while (stuNum--) {
            cin >> tmp;
            pstu[idx++] = tmp;
        }

        idx = 0;
        while (paramNum--) {
            cin >> pparam[idx].op;
            cin >> pparam[idx].param1;
            cin >> pparam[idx].param2;
            // action(&pparam[idx-1], pstu);

            ++idx;
        }
    

        for(int i=0; i<idx; ++i){
            action(&pparam[i], pstu);
        }
        delete []pstu;
        delete []pparam;
    }



    return 0;
}