#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUMBCOPY for (i=0;i<65536;i++) destination[i] = source[i]
#define SMARTCOPY memcpy(destination, source, 65536)


int main() {
	char source[65536] = { 'a' };
	char destination[65536] = {'b'};
	int i,j;
	for(j=0; j<100000; j++){
		DUMBCOPY;
	}

	printf("Done.");

	return 0;
}
