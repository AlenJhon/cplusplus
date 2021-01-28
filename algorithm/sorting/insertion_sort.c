#include <stdio.h>

//插入排序是稳定排序,时间复杂度O(logn*n)
//思路
//1.从第二个元素开始遍历数组
//2.每个位置i元素和 i-1 ~ 0 之间一个个比对如果小于将将后移一位(选择i合适的位置)
//3.重复2步骤
void insert_sort(int* a, const int n){
    for (int i=1; i < n; ++i){
        int j = i - 1;
        int key = a[i];
        while (j >= 0 && key < a[j]){
            a[j + 1] = a[j];
            j -= 1;
        }
        a[j + 1] = key;
    }
}

int main(){
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    int n = sizeof(arr)/sizeof(int);
    
    for (int i=0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    insert_sort(arr, n);

    for (int i=0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
