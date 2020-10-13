#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

//O(n*n) time
//O(1)   space
void select_sort(int* arr, int sz) {
    int i = 0, j, min_pos;
    for (; i < sz-1; ++i) {
        min_pos = i;
        for (j = i+1; j < sz; ++j) {
            if (arr[j] < arr[min_pos]) min_pos = j;
        }
        if (i != min_pos) swap(&arr[i], &arr[min_pos]);
    }
}

void select_sort2(int* arr, int sz) {
    int head = 0, tail = sz-1, min_pos, max_pos;
    for (; head < tail; ++head,--tail) {
        min_pos = head;
        max_pos = tail;
        int i;
        printf("head=%d,tail=%d,min_pos=%d,max_pos=%d\n", head, tail, min_pos, max_pos);
        for (i=head+1; i <= tail; ++i) {
            if (arr[i] < arr[min_pos]) min_pos = i;
            if (arr[i] > arr[max_pos]) max_pos = i;
        }

        if (head != min_pos) swap(&arr[head], &arr[min_pos]);
        if (tail != max_pos) swap(&arr[tail], &arr[max_pos]);
    }
}

int test_swap() {
    int a = 10;
    int b = 20;
    printf("swap before a=%d,b=%d\n", a, b);
    swap(&a, &b);
    printf("swap after  a=%d,b=%d\n", a, b);
}

void print_array(int* arr, int sz){
    int i=0;
    for (; i<sz; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int generic_array(int* out_arr, int sz) {
    srand(time());
    int i = 0;
    for (; i<sz; ++i){
        out_arr[i] = (rand() % RAND_MAX) % 1000;
    }
}

int test_select_sort(){
    const int len = 10;
    int arr[len];
    generic_array(arr, len);
    print_array(arr, len);
    // select_sort(arr, len);
    select_sort2(arr, len);
    print_array(arr, len);
}

int main() {
    // test_swap();
    test_select_sort();

    return 0;
}