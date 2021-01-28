#include <stdio.h>
#include <malloc.h>



int main(){
	/* output result
	 * 24 
	 * 24 
	 * 40 
	 * 56 
	 * */
	char* p = malloc(10);
	printf("%lu\n", malloc_usable_size(p));
	free(p);

	p = malloc(1);
	printf("%lu\n", malloc_usable_size(p));
	free(p);

	p = malloc(25);
	printf("%lu\n", malloc_usable_size(p));
	free(p);

	p = malloc(41);
	printf("%lu\n", malloc_usable_size(p));
	free(p);
	return 0;
}
