/**
 * 有个未排序的数组，元素具有正数和负数，经过排序之后要让正负数相间，原有的相对位置不变
 * 【1， 2， 3， -2， -4， -6， 7， 8】 => 【1，-2， 2， -4， 3， -6， 7， 8】
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int* arr, int l, int r){
    int lidx = l, ridx = r;
    while (lidx < ridx) {
        int ti = arr[lidx];
        arr[lidx] = arr[ridx];
        arr[ridx] = ti;
        lidx++;
        ridx--;
    }
}

void xxsort(int* arr, int sz) {
    int *parr = (int*)malloc(sizeof(int) * sz);
    memset(parr, 0, sizeof(int)*sz);

    int l = 0, r = sz - 1;
    int i = 0;
    for (; i < sz; ++i) {
        if (arr[i] > 0) {
            parr[r--] = arr[i];
        } else {
            parr[l++] = arr[i];
        }
    }

    reverse(parr, r+1, sz-1);
    memcpy(arr, parr, sizeof(int)*sz);
    free(parr);
}

//
//这个交换不是反转，是两个区域的元素从起始位置开始，按序一个一个交换下去
void reverse2(int* arr, int l, int r, int n){
    int xchange = n;
    int lstart = l, rstart = r;
    while (xchange--){
        int ti = arr[lstart];
        arr[lstart] = arr[rstart];
        arr[rstart] = ti;
        lstart++;
        rstart++;
    }
}
void move_pos_seq2(int* arr, int sz, int mvsz){
    int left = 0, right = sz - mvsz;
    int xnum = mvsz;
    if (xnum > right)
        xnum = right;

    while (left < sz){
        reverse2(arr, left, right, xnum);
        left += xnum;
    }
}

//找到一个 123-1-2-3，正数连续和负数连续的串
void find_positive_nagative_seq(int* arr, int sz, int* seq, int pst_num, int ngt_num){
    //负数在后面才有必要调换
    int idx = 0;
    while (idx < sz) {
        
    }
}

//实现方式有问题
void xxsort2(int* arr, int sz){
    int *lptr, *rptr, *posptr=arr;
    int llen=0, rlen=0, pos=0;
    int lok=0, rok=0;
    do {
        lok = 0;
        rok = 0;
        llen = 0;
        rlen = 0;
        while (pos < sz){
            if (posptr[pos] > 0){
                if (rlen > 0) {
                    rok = 1;
                }

                if (lok != 1) {
                    if (llen == 0) {
                        lptr = posptr + pos;
                    }
                    llen++;
                }
            } else {
                if (llen > 0){
                    lok = 1;
                }

                if (rok != 1) {
                    if (rlen == 0) {
                        rptr = posptr + pos;
                    }
                    rlen++;
                }

            }

            pos ++;
            if (lok == 1 && rok == 1){
                break;
            }
        }
        if (rptr > lptr && rlen > 0) {
            move_pos_seq2(lptr, rlen + llen, rlen);
        }
        rptr = lptr = NULL;
        printf("llen=%d,rlen=%d\n", llen, rlen);
    } while (llen > 0 && rlen > 0);
}


void print_array(int *arr, int sz){
    int i;
    for (i = 0; i < sz; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // int arr[] = {1,2,3,-2,-4,-6,7,8};
    int arr[] ={1,-1,2,-2,3,-3,4,-4};
    int sz = sizeof(arr)/sizeof(int);
    print_array(arr, sz);
    // xxsort(arr, sz);
    xxsort2(arr, sz);
    print_array(arr, sz);
    return 0;
}