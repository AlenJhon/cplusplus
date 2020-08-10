#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//kmp o(m+n)
//在字符集中查找关键字起始索引
//abcdefaattssafd   find  tts
void make_next(const char *pattern, int *next)
{
    int q, k;
    int m = strlen(pattern);

    next[0] = 0;
    k = 0;
    for (q = 1; q < m; q++)
    {
        while (k > 0 && pattern[q] != pattern[k])
        {
            k = next[k - 1];
        }

        if (pattern[q] == pattern[k])
        {
            k++;
        }

        next[q] = k;
    }
}

int kmp(const char *text, const char *pattern, int *next)
{
    //check except

    int n = strlen(text);
    int m = strlen(pattern);

    make_next(pattern, next);

    int i, q=0;
    for (i = 0; i < n; i++)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = next[q - 1];
        }

        if (pattern[q] == text[i])
        {
            q++;
        }

        if (q == m)
        {
            break;
        }
    }

    if (q==m){
        return i - q + 1;
    }
    return -1;
}

//https://www.cnblogs.com/zhangtianq/p/5839909.html
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



int main(void){
    int next[20] = {0};
    const char *text = "ababxbababababcdababcabddcadfdsss";
    const char *pattern = "abcabd";

    printf("text:%d\n", strlen(text));

    // int idx = kmp(text, pattern, next);//如果pattern不存在将返回一个不存在的索引
    int idx = kmp2(text, pattern, next);
    printf("match pattern : %d\n", idx);

    for (int i = 0; i < strlen(pattern); i++)
    {
        printf("%4d", next[i]);
    }
    printf("\n");

    return 0;
}
