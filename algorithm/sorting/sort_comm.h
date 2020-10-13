#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void print_array(int *arr, int sz)
{
    int i = 0;
    for (; i < sz; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int generic_array(int *out_arr, int sz)
{
    srand(time(NULL));
    int i = 0;
    for (; i < sz; ++i)
    {
        out_arr[i] = (rand() % RAND_MAX) % 10000;
    }
}

void swap(int *a, int *b)
{
    // *a ^= *b;
    // *b ^= *a;
    // *a ^= *b;

    // *a ^= *b ^= *a ^= *b;

    int temp = *a;
    *a = *b;
    *b = temp;
}

bool compare_array(int* a, int alen, int* b, int blen)
{
    int len = alen < blen ? alen : blen;
    for (int i = 0; i < len; ++i)
    {
        if (a[i] != b[i])
        {
            printf("compare array failed.\n");
            return false;
        }
    }
    printf("compare array ok.\n");
    return true;
}