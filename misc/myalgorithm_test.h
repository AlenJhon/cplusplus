#pragma once

#include <cstdio>
#include "myalgorithm.h"

bool TestBubbleSort()
{
    const int iLen = 10;
    int iArr[iLen] = {2, 5, 10, -9, -8, 0, 4, 8, 1, 19};

    int iLoopCount = BubbleSort(iArr, iLen);
    ////int iLoopCount = BubbleSort1(iArr, iLen);

    printf_s("iLoopCount:%d\n", iLoopCount);
    for (int i = 0; i < iLen; i++)
    {
        printf_s("%d\t", iArr[i]);
    }
    printf_s("\n");

    return true;
}

bool TestBinarySearch()
{
    const int iLen = 10;
    int iArr[iLen] = {-19, -9, -8, 0, 2, 6, 8, 9, 10, 19};
    int iTarget = -19;
    int iTargetIndex = -1;

    printf_s("iArr: ");
    for (int i = 0; i < iLen; i++)
    {
        printf_s("%d\t", iArr[i]);
    }
    printf_s("\n");

    int iRet = BinarySearch(iArr, iLen, iTarget, &iTargetIndex);
    if (!iRet)
    {
        printf_s("BinarySearch don't find iTarget:%d \n", iTarget);
        return false;
    }

    if (iTargetIndex < 0 && iTargetIndex >= iLen)
    {
        printf_s("invalid iTargetIndex:%d\n", iTargetIndex);
        return false;
    }

    if (iArr[iTargetIndex] != iTarget)
    {
        printf_s("iArr[%d]:%d != iTarget:%d don't match \n", iTargetIndex, iArr[iTargetIndex], iTarget);
        return false;
    }

    printf_s("find :%d in iArr[%d]:%d success .\n", iTarget, iTargetIndex, iArr[iTargetIndex]);
    printf_s("TestBinarySearch success .\n");

    return true;
}

bool TestQuickSort()
{
    const int iLen = 10;
    int iArr[iLen] = {2, 5, 10, -9, -8, 0, 4, 8, 1, 19};

    QuickSort(iArr, 0, iLen - 1);

    printf_s("iArr: ");
    for (int i = 0; i < iLen; i++)
    {
        printf_s("%d\t", iArr[i]);
    }
    printf_s("\n");
    return true;
}

bool TestSizeofx()
{
    sizeofxx xx;
    printf_s("%d\n", sizeof(xx));
}
