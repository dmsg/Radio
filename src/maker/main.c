#include <stdio.h>
#include "radio.h"

char *program = NULL;

void usage(void)
{
	printf("Usage:\n"
		"  %s file", program);
}

int main(int argc, char **argv)
{
	int crc = 0;
	char *fname;

	printf("Radio maker\n");
	
	if(argc != 2) {
		usage();
		exit(1);
	}

	fname = argv[1];


	return 0;
}
