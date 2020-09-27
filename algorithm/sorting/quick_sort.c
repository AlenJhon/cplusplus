#include <stdio.h>

#if 0
void swap(int* a, int* b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_sort(int* a, const int left, const int right){
    int mid, key, i= left, j= right;
    mid = (i + j) / 2;
    key = a[mid];
    if (i >= j) return;

    while (i < j){
        
        while (i < j && key > a[i]){
            i++;           
        }       

        while (i < j && key < a[j]){
            j--;
        }
    
        swap(a+i, a+j);
    }
    
    quick_sort(a, left,  j);
    quick_sort(a, j + 1, right);         
}

//建议使用这个方式
void quick_sort2(int* a, const int left, const int right){
    int i = left, j = right;
    int pivot = a[i];
    if(i >= j) return;
    
    while(i < j){

        while (i < j && pivot < a[j]) {
            j--;
        }
        a[i] = a[j];

        while (i < j && pivot > a[i]) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = pivot;

    quick_sort(a, left, i-1);
    quick_sort(a, i+1, right);
}





int main(){
    int arr[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
    int n = sizeof(arr)/sizeof(int);
    quick_sort2(arr, 0, n-1);    
    
    for (int i=0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}

#endif

/*
//2020年9月27日15:36:38 每过一段时间练手下代码

*/
#include "sort_comm.h"

int recurise_count = 0;
int recurise_count2 = 0;

void quick_sort_i(int* arr, int l, int r) 
{
    recurise_count ++;
    int i=l, j=r;
    int pivot = arr[l];
    if (l >= r)
    {
        return;
    }
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
        {
            j--;
        }
        arr[i] = arr[j];

        while (i < j && arr[i] < pivot)
        {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = pivot;

    quick_sort_i(arr, l, i-1);
    quick_sort_i(arr, i+1, r);
}

#define MAX(A,B) (((A) >= (B)) ? (A) : (B))

int find_mid(int a, int b, int c) 
{
    if ((a >= b && a <= c) || (a <= b && a >= c)){
        return a;
    } else if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    } else if ((c >= a && c <= b) || (c <= a && c >= b)) {
        return c;
    }
}

int find_index(int x, int* arr, int len, int i, int j, int k)
{
    if (i < len && x == arr[i])
    {
        return i;
    }
    else if (j < len && x == arr[j])
    {
        return j;
    }
    else if (k < len && x == arr[k])
    {
        return k;
    }
}


void quick_sort_i2(int *arr, int l, int r)
{//该方法测试不通过
    recurise_count2++;
    int i = l, j = r;
    // int pivot = arr[l];

    if (l >= r)
    {
        return;
    }
    while (i < j)
    {
        int one = rand() % r, two = rand() % r, three = rand() % r;
        printf("one=%d,two=%d,tree=%d\n", arr[one], arr[two], arr[three]);

        int pivot = find_mid(arr[one], arr[two], arr[three]);
        printf("pivot=%d\n", pivot);

        int pivot_index = find_index(pivot, arr, r + 1, one, two, three);

        while (i < j && arr[j] > pivot)
        {
            j--;
        }
        arr[pivot_index] = arr[j];

        while (i < j && arr[i] < pivot)
        {
            i++;
        }
        arr[j] = arr[i];

        arr[i] = pivot;
    }

    quick_sort_i(arr, l, i - 1);
    quick_sort_i(arr, i + 1, r);
}

void quick_sort(int* arr, int len)
{
    quick_sort_i(arr, 0, len - 1);
    // quick_sort_i2(arr, 0, len - 1);
    printf("quick_sort_i 方法被调用次数:%d\n", recurise_count);
}

void quick_sort2(int *arr, int len)
{
    // quick_sort_i2(arr, 0, len - 1);
    // quick_sort_i2(arr, 0, len - 1);
    // printf("quick_sort_i2 方法被调用次数:%d\n", recurise_count2);
}

int partition(int* arr, int lower, int upper)
{
    int i = (lower - 1);
    int pivot = arr[upper];
    int j;
    for (j = lower; j < upper; ++j)
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[upper]);
    return (i+1);
}

void quick_sort3(int* arr, int lower, int upper)
{
    if (upper > lower)
    {
        int partitionIndex = partition(arr, lower, upper);
        quick_sort3(arr, lower, partitionIndex-1);
        quick_sort3(arr, partitionIndex+1, upper);
    }
}



int main()
{
    int len = 10;
    int arr[10] = {0};
    // int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr2[10] ={0};
    generic_array(arr, len);
    for (int i=0; i < len; ++i){
        arr2[i] = arr[i];
    }
    compare_array(arr, len, arr2, len);

    print_array(arr, len);
    quick_sort(arr, len);
    print_array(arr, len);

    printf("quick_sort3 start.\n");
    print_array(arr2, len);
    quick_sort3(arr2, 0, len-1);
    print_array(arr2, len);

    compare_array(arr, len, arr2, len);
    return 0;
}

