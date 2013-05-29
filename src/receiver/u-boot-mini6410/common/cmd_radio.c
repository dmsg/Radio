#include <common.h>
#include <command.h>

#if (CONFIG_COMMANDS & CFG_CMD_RADIO)

#include <mmc.h>

int do_radio (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	printf("Radio...\n");
	return 0;
}

U_BOOT_CMD(
	radioinit,	1,	0,	do_radio,
	"radioinit - initialize radio\n",
	NULL
);

#endif