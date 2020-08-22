#include <stdio.h>
#include <stdlib.h>


int main() {
    const char* p = "12345699";
    printf("%llu\n", strtoull(p, NULL, 10));
    //printf("%llu\n", strtoull(NULL, NULL, 10));  // Segmentation fault
    return 0;
}