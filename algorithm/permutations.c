#include <stdio.h>

void swap(char* a, char* b){
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void permutations(char* a, int left, int rigth){
    if (left == rigth){
        for (int i=0; i < rigth; ++i){
            printf("%c", a[i]);
        }
        printf("\n");
    } else {
        for (int i=left; i < rigth; ++i){
            swap(a+left, a+i);
            permutations(a, left+1, rigth);
            swap(a+left, a+i);
        }
    }
}

int main(){
    char s[] = {"ab"};
    int rigth = sizeof(s)/sizeof(char) - 1;
    printf("rigth=%d\n", rigth);
    permutations(s, 0, rigth);
    return 0;
}
