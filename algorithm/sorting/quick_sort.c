#include <stdio.h>

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
