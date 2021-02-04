#include <stdio.h>

#define HASH_BAKUCT_SIZE (1000-1)

unsigned int hashpjw(const void* key)
{
	const char* ptr = key;
	unsigned int val = 0;
	
	while(*ptr != '\0'){
		unsigned int tmp;
		val = (val << 4) + (*ptr);
		if (tmp = (val & 0xf0000000)){
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}
	return val & HASH_BAKUCT_SIZE;
}

int main(){
	const char* p = "alen";
	printf("%s hashcode=%d\n", p, hashpjw(p));
	p = "aalen";
	printf("%s hashcode=%d\n", p, hashpjw(p));
	p = "alena";
	printf("%s hashcode=%d\n", p, hashpjw(p));
	p = "alent";
	printf("%s hashcode=%d\n", p, hashpjw(p));


	printf("A=%d,Z=%d,a=%d,z=%d", 'A','Z', 'a','z');


	return 0;
}
