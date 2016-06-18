#include <stdio.h>
#include <stdlib.h>

int main() {
	int Mb = 0;
	while ( malloc(1<<20)){
		printf("Allocated %d Mb total\n",++Mb);
	}
	printf("Done.");

	return 0;
}
