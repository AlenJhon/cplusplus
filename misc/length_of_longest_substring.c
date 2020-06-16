#include <stdio.h>
#include <string.h>





int 
length_of_longest_substring(char *s) {

    if (!s || s[0] == '\0') return 0;

    char *start = s;
    char *end = start;
    char *pos = start + 1;
    int max_len = 1;

    while(*pos) {
        end = pos;
        char *x = start;
        for ( ; x < end; x++) {
            if(*x == *end) {
                if (end - start  > max_len) 
                       max_len = end - start ;
                       //printf("%c - %c %d\n", *end, *start, max_len);
                start += x - start + 1;
                break;
            }
        }
        if (end - start + 1  > max_len) 
            max_len = end - start + 1;
        pos += 1;
    }
    return max_len;

}


#define LEN 128
int length_of_longest_substring2(char *s) {

    int hset[LEN]; //存储数组下标
    int start = 0, count = 0, max = 0;
    memset(hset, -1, sizeof(hset));
    int i = 0;
    for (; i < strlen(s); i++) {
        if (hset[s[i]] >= start) {
            start = hset[s[i]] + 1; // 更新为重复字符的下一个位置
            count = i - start; // 重置计数器
        }
        hset[s[i]] = i;
        count++;
        if (count > max) {
            max = count;
        }
    }
    return max;

}


#define ASCII_NUM 128
int length_of_longest_substring3(const char *s) {
    
    if(!s || s[0] == '\0') return 0;
    
    
    int index[ASCII_NUM] = {-1};
    memset(index, -1, sizeof(index));

    int i = 0;
    //for (; i < 128; i++) {
    //    printf("%d ", index[i]);
    //}
    //printf("\n");
    

    int max = 0, start = 0, count = 0;
    for(i = 0; i < strlen(s); i++) {
        if (index[ s[i] ] >= start) {
            start = index[ s[i] ] + 1;
            count = i - start;
        }
        index[s[i]] = i;
        count ++;
        if (count > max) {
            max = count;
        }
    }
    return max;   
}








int 
main(void) {

    if ( length_of_longest_substring3("abcabcbb") != 3) {
        printf("test abcabcbb failed  return != 3\n");
    }else {
        printf("check abcabcbb ok.\n");
    }

    
    if ( length_of_longest_substring3("pwwkew") != 3 ) {
        printf("test input pwwkew failed return != 3\n");
    }else {
        printf("chect pwwkew ok. \n");
    }    

    if ( length_of_longest_substring3("au") != 2) {
        printf("test input au failed return != 2\n");
    } else {
        printf("check au ok .\n");
    }
    
    if ( length_of_longest_substring3("") != 0 ) {
        printf("test input \"\" failed .");
    } else {
        printf("check \"\" ok .\n");
    }

    //#printf("max substring:%d\n", length_of_longest_substring("abcabcbb")); 
    //#printf("max substring:%d\n", length_of_longest_substring("pwwkew")); 
    //#printf("max substring:%d\n", length_of_longest_substring("au")); 
    //#printf("max substring:%d\n", length_of_longest_substring("")); 
    //printf("max substring:%d\n", length_of_longest_substring2("abcabcbbcdefg")); 

    return 0;
}
