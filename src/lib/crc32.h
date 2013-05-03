#ifndef _H_CRC32_H
#define _H_CRC32_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define P_16 0xA001
#define P_32 0xEDB88320L
#define FILE_SIZE 1024*1024*16

typedef enum {
	CRC32 = 0,
	CRC16
} CRCTYPE;

/* get a file's crc32 value */
unsigned int get_file_crc(char *file);

/* get memory crc32 value */
unsigned int get_crc32(unsigned int crcinit, unsigned char * bs, unsigned int bssize);

#undef _H_CRC32_H
#endif
