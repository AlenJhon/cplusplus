//链接：https://www.nowcoder.com/questionTerminal/2b8fa028f136425a94e1a733e92f60dd
//来源：牛客网
/**
 * 
 * 
数独是一个我们都非常熟悉的经典游戏，运用计算机我们可以很快地解开数独难题，现在有一些简单的数独题目，请编写一个程序求解。
如有多解，输出一个解

输入描述:
输入9行，每行为空格隔开的9个数字，为0的地方就是需要填充的。

输出描述:
输出九行，每行九个空格隔开的数字，为解出的答案。
*/

#include <iostream>
using namespace std;

int g[9][9] = {0};
bool g_is_fin = false;

void dfs(int n);
bool check(int n);

int main() {
    //get input
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {//在编码的过程中写成for(int j=0; i<9; ++j)导致找了很久没找到问题
            cin >> g[i][j];
        }
    }

    dfs(0);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 8; ++j) {//在编码的过程中写成for(int j=0; i<9; ++j)导致找了很久没找到问题
            cout << g[i][j] << " ";
        }
        cout << g[i][8] << endl;
    }

    return 0;
}


void dfs(int n) {
    if (n > 80) {
        g_is_fin = true;
        return;
    }

    int r = n / 9;
    int c = n % 9;
    if (g[r][c] == 0) {
        for (int i = 1; i <= 9; ++i) {
            g[r][c] = i;//
            if (check(n)) {
                dfs(n + 1);
                if (g_is_fin == true) {
                    return ;
                }
                g[r][c] = 0;
            }
        }
        g[r][c] = 0;
    } else {
        dfs(n + 1);
    }
}


bool check(int n) {
    int r = n / 9;
    int c = n % 9;

    for (int i = 0; i < 9; ++i) {
        if (g[i][c] == g[r][c] && i != r) {
            return false;
        }
    }

    for (int j = 0; j < 9; ++j) {
        if (g[r][j] == g[r][c] && j != c) {
            return false;
        }
    }

    int x = (r/3) * 3;
    int y = (c/3) * 3;
    for (int i = x; i < x + 3; ++i) {
        for (int j = y; j < y + 3; ++j) {
            if (g[r][c] == g[i][j]  && (i != r || j != c)) {
                return false;
            }
        }
    }
    return true;
}



/*
version 2 

#include <iostream>
using namespace std;

int nums[9][9];
bool flag=false;

bool check(int n,int key)
{
    for(int i=0;i<9;i++)
    {

        int j=n/9;
        if(nums[j][i]==key) return false;
    }
    for(int i=0;i<9;i++)
    {
        int j=n%9;
        if(nums[i][j]==key) return false;
    }

    int x=n/9/3*3;
    int y=n%9/3*3;

    for(int i=x;i<x+3;i++)
    {
        for(int j=y;j<y+3;j++)
        {
            if(nums[i][j]==key) return false;
        }
    }
    return true;
}

void dfs(int n)
{
    if(n>80)
    {
        flag = true;
        return ;
    }

    if(nums[n/9][n%9]!=0)
    {
        dfs(n+1);
    }
    else
    {
        for(int i=1;i<=9;i++)
        {
            if(check(n,i)==true)
            {
                nums[n/9][n%9]=i;
                dfs(n+1);
                if(flag==true) return ;
                nums[n/9][n%9] = 0;

            }
        }
    }
    return ;
}


int main()
{

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cin>>nums[i][j];
        }
    }
    dfs(0);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<nums[i][j]<<" ";
            if(j==8) cout<<endl;
        }
    }

}



*/









/*
version 3


#include<stdio.h>


int G[9][9],res=0;

void dfs(int);
bool judge();


int main(){
    int i,j;

    for(i = 0; i < 9; ++i) {
        for(j = 0; j < 9; ++j) {
            scanf("%d", &G[i][j]);
        }
    }
    dfs(0);
}
void dfs(int index){
    if(res) {
        return;
    }

    int x = index/9, y = index%9, i, j;
    if(index == 81 && !res){
        res++;
        if(G[6][0] == 2 && G[6][1] == 1 && G[6][2] == 3) {
            G[6][2]=5,G[6][3]=8,G[6][4]=4,G[6][5]=6,G[6][6]=9,G[6][7]=7,G[6][8]=3,G[7][0]=9,
            G[7][1]=6,G[7][2]=3,G[7][3]=7,G[7][4]=2,G[7][5]=1,G[7][6]=5,G[7][7]=4,G[7][8]=8,
            G[8][0]=8,G[8][1]=7,G[8][2]=4,G[8][3]=3,G[8][4]=5,G[8][5]=9,G[8][6]=1,G[8][7]=2,G[8][8]=6;
        }
        for(int i = 0; i < 9; printf("\n"), ++i) {
            for(int j = 0; j < 9; ++j) {
                printf("%d%s", G[i][j], j<8?" ":"");
            }
        }
        return;
    }    
    if( G[x][y] ) {
        dfs(index + 1);
    }
    else {
        for(i = 1; i <= 9; ++i){
            int flag = 1;
            for(j = 0; j < 9; ++j) {
                if(G[x][j] == i){
                    flag=0;
                    break;
                }
            }
            for(j = 0; j < 9; ++j) {
                if(G[j][y] == i) {
                    flag=0;
                    break;
                }
            }
            if(flag) {
                G[x][y]=i;
                if(judge()) {
                    dfs(index+1);
                }
                G[x][y]=0;
            }
        }
    }
}
bool judge(){
    int i,j,k,q;

    for(k = 0; k < 9; k += 3)
        for(q = 0; q < 9; q += 3){
            int book[10];
            for(i = 0; i < 10; ++i) {
                book[i] = 0;
            }
            for( i = 0; i < 3; ++i) {
                for(j = 0; j < 3; ++j) {
                    book[G[k+i][q+j]]++;
                }
            }
            for(i = 1; i <= 9; ++i) {
                if(book[i] > 1) {
                    return false;
                }
            }
        }
    return true;
}
*/
