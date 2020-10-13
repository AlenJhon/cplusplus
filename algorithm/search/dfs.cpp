#include <cstdio>
#include <cstring>

using namespace std;

int xx=5,yy=4;//边界
int a[100][100];//地图 1表示障碍 2表示访问过
int sx=1,sy=1,p=4,q=3;//起点，终点
int min = 9999999;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

bool validx(int x){
    if (x>=1 && x<=xx){
        return true;
    }
    return false;
}
bool validy(int y){
    if (y>=1 && y<=yy){
        return true;
    }
    return false;
}

void dfs(int x, int y, int step){
    if (x==p && y==q){
        if (step < min){
            min = step;
        }
        printf("到达终点\n");
        return;
    }

    //顺时针试探
    for(int i=0; i<4; i++){
        int tx = x + dx[i];
        int ty = y + dy[i];
        printf("x=%d,y=%d\n", tx, ty);
        if (validx(tx) && validy(ty) && a[tx][ty] != 1 && a[tx][ty] != 2)
        {
            a[tx][ty] = 2;
            dfs(tx, ty, step+1);
            a[tx][ty] = 0;
        }
    }
    return;
}


//这个题目适合用bfs广度优先搜索算法做
int main(){
    memset(a, 0, sizeof(a));
    int m = 5, n= 4;//5行4列
    
    //障碍物填充
    a[1][3] = 1;
    a[3][3] = 1;
    a[4][2] = 1;
    a[5][4] = 1;
    dfs(sx, sy, 0);
    printf("min=%d\n", min);

    return 0;
}
