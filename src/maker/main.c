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
	int crc = 0, bytes_read;
	char buf[BUFSIZ], rad_file[16];
	radio_header rad_hdr;
	FILE *rad, *img;

	program = argv[0];
	printf("Radio maker\n");
	
	if(argc != 2) {
		usage();
		exit(1);
	}

	memset(&rad_hdr, 0, sizeof(radio_header));
	strcpy(rad_hdr.fname,argv[1]);
	rad_hdr.fsize = get_file_size(rad_hdr.fname);
	rad_hdr.crc32 = get_file_crc(rad_hdr.fname);

	sprintf(rad_file, "%s.rad", rad_hdr.fname);

	rad = fopen(rad_file, "wb+");
	img = fopen(rad_hdr.fname, "rb");

	fwrite(&rad_hdr, sizeof(radio_header), 1, rad);
	while((bytes_read = fread(buf, 1, BUFSIZ, img)) > 0) {
		fwrite(buf, bytes_read, 1, rad);
		memset(buf, 0, BUFSIZ);
		printf("%d wrote.\n", bytes_read);
	}

	fclose(img);
	fclose(rad);
	return 0;
}

