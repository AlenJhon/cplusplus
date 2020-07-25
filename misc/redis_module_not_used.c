#include <stdio.h>
#include <unistd.h>

#define REDISMODULE_NOT_USED(V) ((void) V)

int
main(void) {
	

	REDISMODULE_NOT_USED(NULL);
	
	while(1) sleep(5);

	return 0;
}
