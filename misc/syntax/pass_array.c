#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
本小程序目的是观察数组在函数中的多种传递方式差异
*/

//通过int* 传递数组
void print_array(int* arr, int len) {
    printf("arr = %p \n", arr);
    for(int i=0; i<len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_array2(int arr[], int len) {
    printf("arr = %p \n", arr);
    for(int i=0; i<len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void print_arr2_v1(int (*arr)[10][10], int len) {
    printf("arr=%p\n", arr);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", (*arr)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print_arr2_v4(arr2, len);
void print_arr2_v2(int arr[][10], int len) {
    printf("arr=%p\n", arr);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print_arr2_v4(arr2, len);
void print_arr2_v3(int arr[10][10], int len) {
    printf("arr=%p\n", arr);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print_arr2_v4(arr2, len);
void print_arr2_v4(int (*arr)[10], int len) {
    printf("arr=%p\n", arr);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//error: cannot convert ‘int (*)[10]’ to ‘int**’
void print_arr2_v5(int* arr[10], int len) {
    printf("arr=%p\n", arr);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    srand(time(NULL));
    
    const int len = 10;
    int arr[len] = {0};
    for(int i = 0; i < len; ++i) {
        arr[i] = rand() % 1000;
    }
    print_array(arr, len);
    print_array2(arr, len);
    
    
    //二维数组
    int arr2[len][len] = {0};
    for (int i = 0; i < len; ++i) {
    	for (int j = 0; j < len; ++j) {
    	    arr2[i][j] = rand()%1000;    
    	}
    }
    print_arr2_v1(&arr2, len);
    print_arr2_v2(arr2, len);
    print_arr2_v3(arr2, len);
    print_arr2_v4(arr2, len);
    // print_arr2_v5(arr2, len);
    
    
    return 0;
}
