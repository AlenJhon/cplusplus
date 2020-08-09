#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b){
    *a ^= *b ^= *a ^= *b;
}


void show(int* a, const int left, const int right){
#if 0
    for (int i=left; i <= right; ++i){
        printf("%d ", a[i]);
    }
    printf("\n");
#endif
}

void merge(int* a, const int n, const int left, const int right){
    int* tmpa = (int*)malloc(n * sizeof(int));
    memset(tmpa, 0, sizeof(int) * n);

    //printf("n=%d, left=%d, right=%d\n", n, left, right);
    show(a, left, right);
    int idx  = left;
    int L = left;
    int R = ((left + right) / 2) + 1;
    
    int lbound = R;
    int rbound = right + 1;
    while (L < lbound && R < rbound){
        if (a[L] <= a[R]){
            tmpa[idx++] = a[L++];
        } else {
            tmpa[idx++] = a[R++];
        }
    }    
    
    if (R == rbound){
        while (L < lbound){
            tmpa[idx++] = a[L++];
        }
    } else {
        while (R < rbound){
            tmpa[idx++] = a[R++];
        }
    }

    for (idx = left; idx < right + 1; ++idx)
        a[idx] = tmpa[idx];
    
    show(a, left, right);
    free(tmpa);
}


/*
 * @param a array to sort
 * @param n number of elements in the array
 * @param left index to sort from
 * @param right index to sort till
 */

void merge_sort(int* a, const int n, const int left, const int right){
    if (right - left == 1){
        if(a[right] < a[left])
            swap(&a[left], &a[right]);
    } else if (left != right){
        int mid = (left + right) / 2;
        merge_sort(a, n, left, mid);
        show(a, left, mid);

        merge_sort(a, n, mid+1, right);
        show(a, mid+1, right);        

        merge(a, n, left, right);
    }
}


int main(){
    //int a = 10, b = 20;
    //swap(&a, &b);
    //printf("a=%d,b=%d\n", a, b);
    
    int arr[10] = {-19, 9, 100, 7, -18, 0, 10, 9, 66, -1};
    int n = 10;

    for (int i=0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    merge_sort(arr, n, 0, n-1);

    for (int i=0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}



