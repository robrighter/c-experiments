#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void handle_signal(int s){

	if(s == SIGBUS){
		printf("Got a SIGBUS\n");
	}
	if(s == SIGSEGV){
		printf("Got a segmentation violation\n");
	}
	if(s == SIGILL) {
		printf("Got an illegal instruction signal\n");
	}
	if(s == SIGINT) {
		printf("Got me a SIGINT so exiting 1\n");
		/*exit(1);*/
	}
}

int main(){
	int *p = NULL;
	union { char a[10]; int i; } u;
	signal( SIGBUS, handle_signal );
	signal( SIGSEGV, handle_signal );
	signal( SIGILL, handle_signal );
	signal( SIGINT, handle_signal );
	
	/*****************
	SEGV
	*p = 0;
	
	SIGBUS
	p = (int*) &(u.a[9]);
	*p = 17;

	*****************/
	
	while(1){
		sleep(10);
	}

	return 0;
}

