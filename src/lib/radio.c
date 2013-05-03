#include "radio.h"

int get_file_size(char *fname)
{
	FILE *fp;
	int n;

	if((fp = fopen(fname, "r")) == NULL) {
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	n = ftell(fp);

	fclose(fp);
	return n;
}
