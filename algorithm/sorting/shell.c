#include <stdio.h>

void shell_sort(long* arr, int len) {

    for (int gap = len/2; gap > 0; gap /= 2) {
        //select sort
        for (int i = gap; i < len; ++i) {
            int j = i;
            long key = arr[j];
            while ( j-gap >= 0  && key < arr[j - gap]) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            if (j != i){
                arr[j] = key;
            }
        }
    }

}


int main() {
    const int len = 10;
    long arr[len] = {12,99,77,21,88,66,44,33,11,22};

    for (int i=0; i<len; ++i){
        printf("%ld ", arr[i]);
    }
    printf("\n");

    shell_sort(arr, len);

    for (int i=0; i<len; ++i){
        printf("%ld ", arr[i]);
    }
    printf("\n");

    return 0;
}