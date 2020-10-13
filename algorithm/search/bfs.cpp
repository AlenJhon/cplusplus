#include <bits/stdc++.h>

using namespace std;

int xx = 5, yy = 4;               //边界
int a[100][100];                  //地图 1表示障碍 2表示访问过
int sx = 1, sy = 1, ex = 4, ey = 3; //起点，终点
int mindiff = 9999999;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool validx(int x)
{
    if (x >= 1 && x <= xx)
    {
        return true;
    }
    return false;
}
bool validy(int y)
{
    if (y >= 1 && y <= yy)
    {
        return true;
    }
    return false;
}

struct point {
    int x;
    int y;
    int step;
};
queue<point> q;

void bfs(){
    point startp = {1,1,0};
    q.push(startp);

    while (!q.empty())
    {
        //顺时针试探
        int x = q.front().x;
        int y = q.front().y;
        int step = q.front().step;
        if (x == ex && y == ey){
            if (step < mindiff)
            {
                mindiff = step;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (validx(tx) && validy(ty) && a[tx][ty] != 1 && a[tx][ty] != 2)
            {
                a[tx][ty] = 2;
                point tmp ;
                tmp.x = tx;
                tmp.y = ty;
                tmp.step = step + 1;
                q.push(tmp);
            }
        }
        q.pop();
    }
    printf("min=%d\n", mindiff);
}

int main(){
    memset(a, 0, sizeof(a));
    // int m = 5, n = 4; //5行4列
    xx = 5;
    yy = 4;

    //障碍物填充
    a[1][3] = 1;
    a[3][3] = 1;
    a[4][2] = 1;
    a[5][4] = 1;

    bfs();

    return 0;
}