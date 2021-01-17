#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
 
/**
 * 这个文件中是体现一个乱序数组中，求第K大的值
 * 有个算法叫bfprt就是来解决这个问题时间复杂度是线性的O（N）
 * 这个思想是这样的
 * 1.随机一个中间值（有一些对bfprt优化的算法主要是找这个中间值方式不同，如果按随机来选中间值，实现简单平均时间复杂度也能达到线性）
 * 2.将小于1中随机值放在左边，大于放在右边（跟快速排序有点像，但是快排需要两边都有序，bfprt不需要，之关心数据所在的那一边）
 * 3.如果目标大1中指定的值去右边，继续递归，循环往复，如果小于就去左边递归
*/

using namespace std;
const int N = 10005;
 
int a[N];
 
//插入排序
void InsertSort(int a[], int l, int r)
{
    for(int i = l + 1; i <= r; i++)
    {
        if(a[i - 1] > a[i])
        {
            int t = a[i];
            int j = i;
            while(j > l && a[j - 1] > t)
            {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = t;
        }
    }
}
 
//寻找中位数的中位数
int FindMid(int a[], int l, int r)
{
    if(l == r) {//就一个元素返回自己
        return l;
    }
    int i = 0;
    int n = 0;
    for(i = l; i < r - 5; i += 5)
    {
        InsertSort(a, i, i + 4);
        n = i - l;
        swap(a[l + n / 5], a[i + 2]);
    }
 
    //处理剩余元素
    int num = r - i + 1;
    if(num > 0)
    {
        InsertSort(a, i, i + num - 1);
        n = i - l;
        swap(a[l + n / 5], a[i + num / 2]);
    }
    n /= 5;
    if(n == l) return l;
    return FindMid(a, l, l + n);
}
 
//进行划分过程
int Partion(int a[], int l, int r, int p)
{
    swap(a[p], a[l]);
    int i = l;
    int j = r;
    int pivot = a[l];
    while(i < j)
    {
        while(a[j] >= pivot && i < j)
            j--;
        a[i] = a[j];
        while(a[i] <= pivot && i < j)
            i++;
        a[j] = a[i];
    }
    a[i] = pivot;
    return i;
}
 
int BFPRT(int a[], int l, int r, int k)
{
    // int p = FindMid(a, l, r);    //寻找中位数的中位数
    int p = l + rand()%r;//随机一个位置当中位数也是能实现
    int i = Partion(a, l, r, p);
 
    int m = i - l + 1;
    if(m == k) {//找到目标
        return a[i];
    }
    if(m > k) {//目标在左侧
        return BFPRT(a, l, i - 1, k);
    }
    //目标在右侧
    return BFPRT(a, i + 1, r, k - m);
}
 
int main()
{
    srand(time(NULL));
    int n, k;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &k);
    printf("The %d th number is : %d\n", k, BFPRT(a, 0, n - 1, k));
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    puts("");
    return 0;
}
 
/**
10
72 6 57 88 60 42 83 73 48 85
5
*/