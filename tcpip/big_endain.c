#include <stdio.h>


int main() {
    int n = 0x12345678;
    int i = 0;

    if (*(char *)&n == 0x12) {
        printf("Big Endian .\n");
    }
    if (*(char *)&n == 0x78) {
        printf("Little Endian.\n");
    }

    for (i = 0; i < 4; ++i) {
        printf("%X ", *((char *)(&n) + i));
    }
    printf("\n");
    return 0;
}
