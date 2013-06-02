#include <common.h>
#include <command.h>
#include <net.h>

int do_radio (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	IPaddr_t ser_ip;
	unsigned short ser_port;

	if (argc != 3) {
		printf("Wrong arguments!\n");
		return -1;
	}

	ser_ip = string_to_ip(argv[1]);
	ser_port = (unsigned short)simple_strtoul(argv[2], NULL, 10);

	printf("Reading data from %s:%d\n",
		argv[1], ser_port);
	printf("Radio...\n");
	return 0;
}

U_BOOT_CMD(
	radio,	3,	0,	do_radio,
	"radio\t- Do multicast radio\n",
	NULL
);

