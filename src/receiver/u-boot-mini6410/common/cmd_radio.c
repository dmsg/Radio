#include <common.h>
#include <command.h>

int do_radio (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	printf("Radio...\n");
	return 0;
}

U_BOOT_CMD(
	radio,	1,	0,	do_radio,
	"radio - Do multicast radio\n",
	NULL
);

