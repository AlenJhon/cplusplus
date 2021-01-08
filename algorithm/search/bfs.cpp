#include <bits/stdc++.h>

using namespace std;

int xx = 5, yy = 4;               //边界 5行4列
int a[100][100];                  //地图 1表示障碍 2表示访问过
int sx = 1, sy = 1, ex = 4, ey = 3; //起点，终点
int mindiff = 9999999; //用于记录起点到终点最优解/最短步数
//up (0,1) right (1,0) down (0,-1) left (-1,0)
//顺时针四个方向上的坐标偏移
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
//广度搜索算法需要借助队列来实现
queue<point> q;//定义队列

void bfs(){
    point startp = {1,1,0};//起始节点
    q.push(startp);//加入队列

    //遍历队列
    while (!q.empty())
    {
        //获取出队首位置
        int x = q.front().x;
        int y = q.front().y;
        int step = q.front().step;
        //判断是否达到目的地，并记录最小步数于mindiff
        if (x == ex && y == ey){
            if (step < mindiff)
            {
                mindiff = step;
            }
        }

        //顺时针四个方向试探
        for (int i = 0; i < 4; i++)
        {
            //计算四个方向上坐标
            int tx = x + dx[i];
            int ty = y + dy[i];
            //校验是否溢出，障碍物，走过
            if (validx(tx) && validy(ty) && a[tx][ty] != 1 && a[tx][ty] != 2)
            {
                //没有走过加入队列尾部
                a[tx][ty] = 2;
                point tmp ;
                tmp.x = tx;
                tmp.y = ty;
                tmp.step = step + 1;
                q.push(tmp);
            }
        }
        //扩展完出队
        q.pop();
    }
    
    //遍历完队列获得最优解
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
