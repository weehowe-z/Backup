#include <stdio.h>
#include <string.h>

int main()
{
	int n = 0;
	int i = 0;
	int v = 0;
	char s[100];
	FILE *mtest;
	printf("Virtual Memory address of num: %p\n", &v);
	printf("Current num value %d\n", v);

	while(true){

		mtest = fopen("/proc/mtest", "w+");
		
		fgets(s, 80, stdin);

		if(memcmp(s, "exit", 4) == 0) break;

		else if(memcmp(s, "print", 5) == 0) {
			printf("Current num value %d\n", v);
		}

		else if(memcmp(s, "listvma", 7) == 0) {
			printf("'listvma' called, see dmesg\n");
			fprintf(mtest, "%s\n", "listvma");
		}

		else if(memcmp(s, "write", 5) == 0){
			sscanf(s, "write %d", &i);
			printf("Excute writeval 0x%lx %d\n", (unsigned long)(void*)&v, (unsigned long)i);
		  fprintf(mtest, "writeval 0x%lx %lx\n", (unsigned long)(void*)&v, (unsigned long)i);
		}

		fclose(mtest);
	}
	return 0;
}
