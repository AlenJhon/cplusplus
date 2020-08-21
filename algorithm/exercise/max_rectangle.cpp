#include <iostream>
#include <stack>
#include <string.h> //for memset

/*
 * 题目
 * 给定一个整型矩阵map，其中的值只有0和1两种，求其中全是1的所有矩形区域中，最大的矩形区域为1的数量
 * 求解思路
 * 1.求解每一列中从上到下连续是1的个数，遍历一趟就能知道结果
 * 2.从第一步中得出的结果继续使用单调栈找出一行中最大的矩形，
 * 单调栈，一排数，一个个入栈，
 * 如果遇到当前要加入的数小于等于栈顶，说明栈顶可以弹出了，
 * 已经能获得栈顶所表示的位置所能扩展的左右边界了，等于的时候可能不准确但是没有关系，后面的相等元素总有一个是准确的，
 * 如果大于栈顶入栈
 * */


using namespace std;

#define MAX(x,y) (x)>=(y)?(x):(y)

int MaxRecFromBotton(int* pBotton, int len){
	if (!pBotton || len < 1){
		return 0;
	}
	int maxArea = 0;
	stack<int> s;
	for (int i=0; i < len; ++i){
		while (!s.empty() && pBotton[i] <= pBotton[s.top()]){
			int j = s.top();
			s.pop();
			int k = s.empty() ? -1 : s.top();
			int curArea = (i - k - 1) * pBotton[j];
			maxArea =  MAX(maxArea, curArea);
		}
		s.push(i);
	}

	while (!s.empty()){
		int j = s.top();
		s.pop();
		int k = s.empty() ? -1 : s.top();
		int curArea = (len - k - 1) * pBotton[j];//
		maxArea = MAX(maxArea, curArea);
	}
	return maxArea;
}

int MaxRecSize(int prec[][5], int len, int hei){
	if (!prec || len < 1 || hei < 1){
		return 0;
	}
	int iMaxArea = 0;
	int* pheight = new int[len];
	memset(pheight, 0, len * sizeof(int));

	for (int i=0; i < hei; ++i){
		for (int j=0; j < len; ++j){
			pheight[j] = prec[i][j] == 0 ? 0 : pheight[j] + 1;
		}

		iMaxArea = MAX(MaxRecFromBotton(pheight, len), iMaxArea);
	}
	return iMaxArea;
}



int main() {
	int arr[5][5] = {
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 1,
		1, 1, 1, 1, 0,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
	};	
	cout << MaxRecSize(arr, 5, 5) << endl;
    return 0;
}
