#include <stdio.h>
#include <windows.h>

#define PAGESIZE 4096
#define QUARTERGIGA (256*1024*1024)
#define MAXGIGA  6

int main(void)
{
	int i;
	printf("start\n");

	HANDLE hmap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_EXECUTE_READWRITE,
		2, 0, // 8GB
		NULL);

	printf("hmap: %p\n", hmap);


	for(i=0; i<4*MAXGIGA; ++i){
		long long int offset = ((long long int) i) * QUARTERGIGA;
		printf("mapping %.2f GB, %llu", ((float)i+1)/4, offset);
		char *p = (char*)MapViewOfFile(
			hmap,
			FILE_MAP_ALL_ACCESS,
			(DWORD)(offset >> 32),
			(DWORD)(offset & 0xffffffff),
			QUARTERGIGA);
		if(p==NULL){
			printf(" failed\n");
			break;
		}
		printf(" ok");
		int j;
		for(j=0; j<QUARTERGIGA; j+=PAGESIZE){
			p[j] = i;
		}
		printf(" writen\n");
		UnmapViewOfFile(p);
	}

	printf("write ok\n");
	fflush(stdout);

	for(i=0; i<4*MAXGIGA; ++i){
		long long int offset = ((long long int) i) * QUARTERGIGA;
		printf("mapping %.2f GB", ((float)i+1)/4);
		char *p = (char*)MapViewOfFile(
			hmap,
			FILE_MAP_ALL_ACCESS,
			(DWORD)(offset >> 32),
			(DWORD)(offset & 0xffffffff),
			QUARTERGIGA);
		if(p==NULL){
			printf(" failed\n");
			break;
		}
		printf(" ok");
		int j;
		for(j=0; j<QUARTERGIGA; j+=PAGESIZE){
			if(p[j] != i){
				printf("p[%d] != %d\n", j, i);
				break;
			}
		}
		printf(" read ok\n");
		UnmapViewOfFile(p);
	}

	fflush(stdout);
	getchar();

	CloseHandle(hmap);
	return 0;
}
