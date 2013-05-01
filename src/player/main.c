#include <stdio.h>

char *program = NULL;

void usage(void)
{
	printf("Usage:\n"
		"\t%s config\n", program);
}		

int main(int argc, char **argv)
{
	program = argv[0];

	if(argc != 2) {
		usage();
		exit(1);
	}	

	return 0;
}	
