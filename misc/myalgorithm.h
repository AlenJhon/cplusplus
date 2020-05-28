#pragma once

int BubbleSort(int arr[], int iLen);
int BubbleSort1(int arr[], int iLen);

bool BinarySearch(int arr[], int iLen, int iTarget, int *pOutIndex);

void QuickSort(int arr[], int iLefe, int iRight);

//list
typedef struct Node
{
    int num;
    struct Node *pNextNode;
} MYLIST;

MYLIST *CreateMyList(int n);
bool DeleteMyListByVal(MYLIST *pMyList, int iVal);
bool InsertMyListByIdx(MYLIST *pMyList, int iVal, int iIdx);
