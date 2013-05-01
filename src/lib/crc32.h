#ifndef _H_CRC32_H
#define _H_CRC32_H

/* get a file's crc32 value */
int get_file_crc(char *file);

/* get memory crc32 value */
int get_crc(void *src, int size);

#undef _H_CRC32_H
