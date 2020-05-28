#include <cstdio>
#include <cstdlib>
#include "myalgorithm.h"

int BubbleSort(int arr[], int iLen)
{
    //稳定排序
    //时间复杂度 O(n*n)
    int iTemp;
    int iLoopCount = 0;
    int iExchangeCount = 0;
    for (int i = 0; i < iLen - 1; i++)
    {
        for (int j = 0; j < iLen - i - 1; j++)
        {
            iLoopCount += 1;
            if (arr[j] > arr[j + 1])
            {
                iExchangeCount++;
                iTemp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = iTemp;
            }
        }
    }
    printf_s("BubbleSort iExchangeCount:%d\n", iExchangeCount);
    return iLoopCount;
}

int BubbleSort1(int arr[], int iLen)
{
    //小优化，有序了不再进行遍历
    int temp;
    bool flag;
    int iLoopCount = 0;
    int iExchangeCount = 0;
    for (int i = 0; i < iLen - 1; i++)
    {
        flag = false;
        for (int j = iLen - 1; j > i; j--)
        {
            iLoopCount += 1;
            if (arr[j] < arr[j - 1])
            {
                iExchangeCount++;
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
    printf_s("BubbleSort1 iExchangeCount:%d\n", iExchangeCount);
    return iLoopCount;
}

bool BinarySearch(int arr[], int iLen, int iTarget, int *pOutIndex)
{
    //非递归二分查找
    //时间复杂度O(log n) 底数2
    int left = 0;
    int right = iLen - 1; // 注意

    int iLoopCount = 0;
    while (left <= right)
    {
        iLoopCount++;
        int mid = (right + left) / 2;
        if (arr[mid] == iTarget)
        {
            if (pOutIndex)
            {
                *pOutIndex = mid;
            }
            return true;
        }
        else if (arr[mid] < iTarget)
        {
            left = mid + 1;
        }
        else if (arr[mid] > iTarget)
        {
            right = mid - 1;
        }
    }
    printf_s("BinarySearch iLoopCount:%d\n", iLoopCount);
    return false;
}

static int iQuickSortLoopCount = 0;
void QuickSort(int arr[], int iLeft, int iRight)
{
    //时间复杂度 O(nlogn)
    if (iLeft >= iRight)
    {
        return;
    }
    int i = iLeft;
    int j = iRight;
    int iMidKey = arr[iLeft]; //假定这个是中间值，右边比它打，左边比它小
    while (i < j)
    {
        while (i < j && arr[j] > iMidKey)
        {
            j--;
            iQuickSortLoopCount++;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] < iMidKey)
        {
            i++;
            iQuickSortLoopCount++;
        }
        arr[j] = arr[i];
    }
    arr[i] = iMidKey;
    QuickSort(arr, iLeft, i - 1);
    QuickSort(arr, i + 1, iRight);

    printf_s("iQuickSortLoopCount:%d\n", iQuickSortLoopCount);
    return;
}

MYLIST *CreateMyList(int n)
{
    MYLIST *pMyList = NULL, *pCurrentNode = NULL, *pHead = NULL;
    pMyList = (MYLIST *)malloc(sizeof(MYLIST));
    if (!pMyList)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        pCurrentNode = (MYLIST *)malloc(sizeof(MYLIST));
        pCurrentNode->num = i + 1;
        pCurrentNode->pNextNode = pHead; //front insert
        pHead = pCurrentNode;
    }

    pMyList->num = n;
    pMyList->pNextNode = pHead;
    return pMyList;
}

bool DeleteMyListByVal(MYLIST *pMyList, int iVal)
{
    if (!pMyList)
    {
        return false;
    }
    MYLIST *pNode = pMyList->pNextNode;
    MYLIST *pPreNode = pMyList;
    while (pNode)
    {
        if (pNode->num == iVal)
        {
            pPreNode->pNextNode = pNode->pNextNode;
            return true;
        }
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    return false;
}
bool InsertMyListByIdx(MYLIST *pMyList, int iVal, int iIdx) //left insert
{
    if (iIdx < 0 || pMyList == NULL)
    {
        return false;
    }

    MYLIST *pTarget = (MYLIST *)malloc(sizeof(MYLIST));
    MYLIST *pNode = pMyList->pNextNode;
    MYLIST *pPreNode = pMyList;
    int iNum = 0;
    while (pNode)
    {
        if (iNum == iIdx)
        {
            pPreNode->pNextNode = pTarget;
            pTarget->pNextNode = pNode;
            return true;
        }
        iNum++;
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    return false;
}