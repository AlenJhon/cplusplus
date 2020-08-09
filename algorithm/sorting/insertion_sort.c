#include <stdio.h>


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
