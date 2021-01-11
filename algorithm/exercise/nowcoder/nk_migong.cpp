/*
题目描述
定义一个二维数组N*M（其中2<=N<=10;2<=M<=10），如5 × 5数组下所示：


int maze[5][5] = {
0, 1, 0, 0, 0,
0, 1, 0, 1, 0,
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
0, 0, 0, 1, 0,
};
它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。入口点为[0,0],既第一空格是可以走的路。


本题含有多组数据。

输入描述:
输入两个整数，分别表示二位数组的行数，列数。再输入相应的数组，其中的1表示墙壁，0表示可以走的路。数据保证有唯一解,不考虑有多解的情况，即迷宫只有一条通道。

输出描述:
左上角到右下角的最短路径，格式如样例所示。

*/
#include <iostream>
#include <queue>

using namespace std;

struct Elo
{
    int x;
    int y;
};

Elo Direct[4] = {(0,1), (1,0), (0, -1), (-1, 0)};

bool checkx(int x, int row) {
    if (x >= 0 && x < row) {
        return true;
    }
    return false;
}
bool checky(int x, int col) {
    if (x >= 0 && x < col) {
        return true;
    }
    return false;
}

////error error error error 
int main() {
    // int m[10][10]={0};
    vector<vector<int>> v;
    int row, col;
    queue<Elo> q;
    vector<vector<int>> path_best;
    vector<vector<int>> path_temp;

    while (cin >> row >> col) {
        v.clear();
        path_temp.clear();
        path_best.clear();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> v[i][j];
            }
        }

        q.push({0,0});
        while (!q.empty()) {
            int x = q.front().x;
            int y = q.front().y;
            if (x == row-1 && y == col-1) {
                if (path_temp.size() < path_best.size() || path_best.empty()) {
                    path_best = path_temp;
                }
            }

            //up right down left
            for (int z=0; z < 4; ++z) {
                int tx = x + Direct[z].x;
                int ty = y + Direct[z].y;
                if (checkx(tx, row) && checky(ty, col)) {

                    q.push({tx, ty});
                    path_temp.push_back({tx,ty});
                }
            }

            //
            q.pop();
        }
    }

    return 0;
}