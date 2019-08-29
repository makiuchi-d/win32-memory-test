#include <stdlib.h>
#include <stdio.h>

#define PAGESIZE 4096
#define QUARTERGIGA (256*1024*1024)
#define MAXGIGA  6

int main(void)
{
	int i;
	printf("start\n");

	for(i=0; i<4*MAXGIGA; ++i){
		printf("allocate %.2f GB", ((float)i+1)/4);
		char *p = (char*)malloc(QUARTERGIGA);
		if(p==NULL){
			printf(" failed\n");
			break;
		}
		printf(" ok");
		int j;
		for(j=0; j<QUARTERGIGA; j+=PAGESIZE){
			p[j] = 0;
		}
		printf(" writen\n");
	}

	return 0;
}
