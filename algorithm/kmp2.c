#include <stdio.h>
#include <string.h>

#if 0
void make_next2(const char *pattern, int *next){
    int m = strlen(pattern);
    next[0] = -1;
    int k = -1, j = 0;

    //前缀和后缀的公共最大子串个数 右移动一位了
    //example next 0   0   0   1   2   0  ->   next -1   0   0   0   1   2
    while( j < m - 1){
        if (k == -1 || pattern[j] == pattern[k]){
            ++k;
            ++j;
            next[j] = k;
        }
        else {
            k = next[k];
        }
    }
    return;
}
int kmp2(const char *text, const char *pattern, int *next){

    make_next2(pattern, next);
    
    int i = 0, j = 0;// i是 text的索引, j 是pattern索引
    int n = strlen(text);
    int m = strlen(pattern);

    while( i < n && j < m){

        // next 数组中最小的是-1
        if (j == -1 || text[i] == pattern[j]){
            i++;
            j++;
        }
        else{
            j = next[j];//pattern向右移动 m - next[j]
        }
    }

    if (j == m){
        return i - j;
    }
    return -1;
}
#endif


int make_next(const char *pattern, int *next){

    int m = strlen(pattern);
    int k = -1, j = 0;
    next[0] = -1; // 前缀 和后缀最大公共的子串数量向右移动一位

    //m - 1 最后一个不需要考虑 被右移动了 
    while( j < m-1 ){

        if(k == -1 || pattern[k] == pattern[j]){
            ++k;
            ++j;
            next[j] = k;
        }else{
            k = next[k];
        }
    }
    return 0;
}

int kmp(const char *text, const char *pattern, int *next){

    make_next(pattern, next);
    // for(int x = 0; x < strlen(pattern); x++){
    //     printf("%4d", next[x]);
    // }
    // printf("\n");

    int n = strlen(text);
    int m = strlen(pattern);
    int i = 0, j = 0; // i is text index, j is pattern index and array elment data

    while(i < n && j < m){

        //j == -1 
        if(j == -1 || text[i] == pattern[j]){
            ++i;
            ++j;
        }else {
            j = next[j];
        }

        if(j == m){// 满足条件就跳出
            break;
        }
    }

    if(j == m){
        // return i - j + 1;
        return i - j;
    }
    return -1;
}

int main(void){

    int next[20] = {0};
    const char *text = "abcdefgsaddfdaferqefadsvdsadqwerqefsadfd";
    const char *pattern = "erqe";

    printf("text before kmp strlen:%d\n", strlen(text));
    int idx = kmp(text, pattern, next);
    printf("kmp return idx:%d\n", idx);

    for(int i = 0; i < strlen(pattern); i++){
        printf("%4d", next[i]);
    }
    printf("\n");

    return 0;
}



