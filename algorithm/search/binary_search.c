#include <stdio.h>
#include <stdlib.h>


int binary_search(int* a, const int size, const int x){
    int low = 0, higth = size - 1, mid;
    
    while(low <= higth){
        mid = (low + higth) / 2;
        if (a[mid] == x) {
            return mid;
        } else if (a[mid] > x) {
            higth = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int binary_search_r(int* a, const int x, int left, int rigth){
    if (left <= rigth){
        int mid = (left + rigth) / 2;
        if (x < a[mid]){
            binary_search_r(a, x, left, mid - 1);
        } else if (x > a[mid]) {
            binary_search_r(a, x, mid + 1, rigth);
        } else {
            return mid;
        }
    }
}



#define ARRAY_SIZE (100)
int main(){
    
    int arr[ARRAY_SIZE] = {0};
    for (int i=0; i < ARRAY_SIZE; ++i){
        arr[i] = i * 5;
    }      
    
    int target = 99*5;
    int idx = binary_search_r(arr, target, 0, ARRAY_SIZE - 1);
    if (idx < 0){
        printf("target=%d, don't found in array\n", target);
    } else {
        printf("target=%d, found in array index=%d\n", target, idx);
    }

    return 0;
}
