#include <stdio.h>
#include <string.h>
#include "../include/radio.h"
char *program = NULL;

void usage(void)
{
	printf("Usage:\n"
		"  %s config\n", program);
}		

int main(int argc, char **argv)
{
	if(argc != 2) {
		usage();
		exit(1);
	}
    
	int n,ret,i=0;
	FILE *config_pf=NULL;
	int file_fd;

	char *pline=NULL;
	radio_header file_header;
	radio_config   radio_config_arr[2]={0};
	program = argv[0];

	bzero(&file_header, sizeof(file_header));

	config_pf=fopen(argv[1],"rb");
	if(config_pf==NULL)
	{
		perror("fopen");
	}
	
	while((ret=getline(&pline ,&n ,config_pf))>0)
	{
		if(strncmp(pline,"#",1)!=0)
		{
			sscanf(pline,"%d %s %d %[0-9,.]:%d",&radio_config_arr[i].channel,radio_config_arr[i].fname,&radio_config_arr[i].bandwidth,&radio_config_arr[i].ip,&radio_config_arr[i].port);
			i++;
		}
	}	

	fclose(config_pf);




	return 0;
}	
