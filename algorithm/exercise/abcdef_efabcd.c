#include <stdio.h>

/*
//abcdef -> efabcd
*/

void reverse(char* arr, int l, int r) {
    int lidx = l, ridx = r;
    while (lidx < ridx) {
        char tch = arr[lidx];
        arr[lidx] = arr[ridx];
        arr[ridx] = tch;
        lidx ++;
        ridx --;
    }
}

//这个交换不是反转，是两个区域的元素从起始位置开始，按序一个一个交换下去
void reverse2(char* arr, int l, int r, int n) {
    int xchange = n;
    int lstart = l, rstart = r;
    while (xchange--) {
        char tch = arr[lstart];
        arr[lstart] = arr[rstart];
        arr[rstart] = tch;
        lstart ++;
        rstart ++;
    }
}

//abcdef -> efabcd
void move_char_seq(char* arr, int sz, int mvsz) {
    int left = sz - mvsz;
    reverse(arr, 0, left-1);
    reverse(arr, left, sz-1);
    reverse(arr, 0, sz-1);
}

//在第一种的基础上做的优化，更少的交换次数
void move_char_seq2(char* arr, int sz, int mvsz) {
    int left = 0, right = sz - mvsz;
    int xnum = mvsz;
    if (xnum > right) 
        xnum = right;

    while (left < sz) {

        reverse2(arr, left, right, xnum);
        left += xnum;
    }
}


void print_array(char* arr, int sz) {
    int i;
    for ( i=0; i < sz; ++i){
        printf("%c ", arr[i]);
    }
    printf("\n");
}

int main(){
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    print_array(arr, 6);
    // move_char_seq(arr, 6, 2);
    // move_char_seq2(arr, 6, 4);
    move_char_seq2(arr, 6, 2);
    print_array(arr, 6);
    return 0;
}