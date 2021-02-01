/**
 * 给定一个字符串abc,列举出所有字符串的组合可能(字符从排列组合)
 **/
#include <stdio.h>

void swap(char* a, char* b){
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

//是个深度优先遍历
void permutations(char* a, int left, int rigth){
    if (left == rigth){ //递归的结束条件,已经遍历到最后一个字符了
        //输出当前数组中的内容
        for (int i=0; i < rigth; ++i){
            printf("%c", a[i]);
        }
        printf("\n");
    } else {//不是最后一个字符
        //从left开始到最后一个字符都和left位置进行对换位置,并递归调用写一层
        for (int i=left; i < rigth; ++i){
            swap(a+left, a+i);
            permutations(a, left+1, rigth);
            swap(a+left, a+i);
        }
    }
}

int main(){
    char s[] = {"abc"};
    int rigth = sizeof(s)/sizeof(char) - 1;
    printf("rigth=%d\n", rigth);
    permutations(s, 0, rigth);
    return 0;
}
