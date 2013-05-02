#ifndef _H_RADIO_H
#define _H_RADIO_H

#include "crc32.h"

/* radio_header is the header which will be added 
** to the front of a given file. */
typedef struct radio_header {
	char fname[16];
	short fsize;
	short crc32;
}radio_header;

/* radio_unit is the unit which will be sent by radio_player,
** index begins with 0. */
typedef radio_unit{
	int index;
	char data[1024];
}radio_unit;

/* radio_config is used to parse config file. 
** '#' is selected as comment character */
typedef struct radio_config{
	int channel;
	char fname[16];
	int bandwidth;
	int ip;
	short port;
}radio_config;

int get_file_size(char *fname);
#undef _H_RADIO_H
