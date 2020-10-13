#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//buble sort
//o(n*n)

#define IS_EXCHANGE 1

void bubble_sort(int *pdata, int ilength)
{
    int itemp = 0;
#ifdef IS_EXCHANGE
    char is_exchange = 0;
#endif
    int loop_count = 0;
    int exchange_count = 0;
    for (int i = 0; i < ilength-1; i++)
    {
#ifdef IS_EXCHANGE
        is_exchange = 0;
#endif
        for (int j = 0; j < ilength - 1 - i; j++)
        {
            loop_count += 1;
            if (pdata[j] > pdata[j + 1])
            {
                itemp = pdata[j + 1];
                pdata[j + 1] = pdata[j];
                pdata[j] = itemp;
#ifdef IS_EXCHANGE
                is_exchange = 1;
#endif
                exchange_count += 1;
            }
        }
#ifdef IS_EXCHANGE
        if (is_exchange == 0) 
        {
            printf("发生了数据队列是有序的退出循环\n");
            break;
        }
#endif
    }

    printf("总共循环次数：%d,交互次数:%d\n", loop_count, exchange_count);
    return;
}


int generic_array(int *out_arr, int sz)
{
    srand(time(NULL));
    int i = 0;
    for (; i < sz; ++i)
    {
        out_arr[i] = (rand() % RAND_MAX) % 1000;
    }
}

void print_array(int *arr, int sz)
{
    int i = 0;
    for (; i < sz; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


//test train code
void swap(int *a, int *b)
{
    // *a ^= *b;
    // *b ^= *a;
    // *a ^= *b;

    *a ^= *b ^= *a ^= *b;
}

void bubble_sort_t(int *arr, int len)
{
    char is_change = 0;
    for (int i = 0; i < len - 1; ++i)
    {
        is_change = 0;
        for (int j = 0; j < len - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                // int temp = arr[j];
                // arr[j] = arr[j+1];
                // arr[j+1] = temp;
                swap(arr + j, arr + j + 1);
                is_change = 1;
            }
        }
        if (is_change == 0)
        {
            break;
        }
    }
    return;
}

int main()
{
    // int simple_arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int simple_arr[10] ={0};
    int sz = 10;
    generic_array(simple_arr, sz);
    print_array(simple_arr, sz);
    // bubble_sort(simple_arr, sz);
    bubble_sort_t(simple_arr, sz);
    print_array(simple_arr, sz);

    return 0;
}

