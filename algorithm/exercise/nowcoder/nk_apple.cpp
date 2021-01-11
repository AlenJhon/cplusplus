/*
题目描述
题目描述

把m个同样的苹果放在n个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？（用K表示）5，1，1和1，5，1 是同一种分法。

数据范围：0<=m<=10，1<=n<=10。
本题含有多组样例输入。


输入描述:
输入两个int整数

输出描述:
输出结果，int型
*/
#include <iostream>
#include <vector>
using namespace std;

int putapples(int m, int n)
{
    //行列越界检查
    if (m<0 || m>10) return -1;
    if (n<1 || n>10) return -1;
    if (1 == n) return 1;//只有一个盘子
    if (m <= 1) return 1;//苹果小等于一个只有一种放法
    if (m <= n) n = m;//多余的盘子不考虑
    
    //定义一个二维数组n+1行，m+1列，并将每个元素初始化未0
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    dp[1] = vector<int>(m+1, 1);//将第二行都初始化成1
    //根据列数将第二行到n行的前两列都初始化成1
    for (int i = 1; i <= n; ++i){
        dp[i][0] = dp[i][1] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            dp[i][j] = dp[i-1][j] + (j-i < 0 ? 0 : dp[i][j-i]);
        }
    }
    return dp[n][m];
}

int main() 
{
    int m,n;
    while (cin >> m >> n)
    {
        cout << putapples(m, n) << endl;
    }
    return 0;
}