#include <stdio.h>


int main() {
	int sub = 0x08049108 - 0x08048094;
	//int text_len = 0x72;
	printf("0x08049108 - 0x08048094 = hex=%x , dec=%d , text=%d, sub-text=%d\n", sub, sub, 0x72, sub - 0x72);
	return 0;
}
