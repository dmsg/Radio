#include "crc32.h"

static unsigned char crcbuf[16384];
static unsigned short crc_tab16[256];
static unsigned int crc_tab32[256];

static void init_crc16_tab(void);
static void init_crc32_tab(void);

static void init_crc16_tab(void)
{
	int i, j;
	unsigned short crc, c;

	for (i = 0; i < 256; i++) {
		crc = 0;
		c = (unsigned short)i;
		for (j = 0; j < 8; j++) {
			if ((crc ^ c) & 0x0001)
				crc = (crc >> 1) ^ P_16;
			else
				crc = crc >> 1;
			c = c >> 1;
		}
		crc_tab16[i] = crc;
	}
}				/* init_crc16_tab */

static void init_crc32_tab(void)
{

	int i, j;
	unsigned long crc;

	for (i = 0; i < 256; i++) {
		crc = (unsigned long)i;
		for (j = 0; j < 8; j++) {
			if (crc & 0x00000001L)
				crc = (crc >> 1) ^ P_32;
			else
				crc = crc >> 1;
		}
		crc_tab32[i] = crc;
	}
}				/* init_crc32_tab */

unsigned int get_crc16(unsigned int crcinit, unsigned char * bs, unsigned int bssize)
{
	unsigned int crc = 0;

	init_crc16_tab();
	while (bssize--) {
		crc = (crc >> 8) ^ crc_tab16[(crc & 0xff) ^ *bs++];
	}

	return crc;
}

unsigned int get_crc32(unsigned int crcinit, unsigned char * bs, unsigned int bssize)
{
	unsigned int crc = crcinit ^ 0xffffffff;

	init_crc32_tab();
	while (bssize--) {
		crc = (crc >> 8) ^ crc_tab32[(crc & 0xff) ^ *bs++];
	}

	return crc ^ 0xffffffff;
}

/* get a file's crc32 value */
unsigned int get_file_crc(char *file)
{
	int fd;
	unsigned int rdlen;
	unsigned int crc = 0;

	if ((fd = open(file, O_RDONLY)) == -1) {
		fprintf(stderr, "Open %s error.\n", file);
		exit(1);
	}

	while ((rdlen = read(fd, crcbuf, 4096)) > 0) {
		crc = get_crc16(crc, crcbuf, rdlen);
	}

	close(fd);
	return crc;
}
