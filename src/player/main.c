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
    
	int n,ret,i=0,count,sockfd;
	FILE *config_pf=NULL;
	int file_fd;
	strcut sockaddr_in conaddr;

	char *pline=NULL;
	radio_header file_header;
	radio_config   radio_config_arr[2]={0};
	radio_unit    file_unit;
	program = argv[0];

	bzero(&file_header, sizeof(file_header));
	bzero(&file_unit, sizeof(file_unit));
	bzero(&conaddr, sizeof(conaddr));

	conaddr.sin_famliy=AF_INET;
	conaddr.sin_port=1235;


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

	conaddr.sin_addr.s_addr=radio_config_arr[1].ip;

	file_fd=open(radio_config_arr[1].fname ,RDONLY);
	if(file_fd<0)
	{
		perror("file_fd");
	}

	read(file_fd,&file_header,sizeof(radio_header));

	sockfd=socket(AF_INET,SOCK_DGRAM,0)
	if(sockfd<0)
	{
		perror("socket");
	}
	

	count=file_header.fsize/1024+1;
	while(1)
	{
		for(i=0;i<count;i++)
		{
			read(file_fd,file_unit.data,1024);
			file_unit.index=i;
			sendto(sockfd,&fiel_unit,sizeof(file_unit),0,(struct sockaddr *)&conaddr,sizeof(conaddr);)
			
			
		}
		
	}


	return 0;
}	
