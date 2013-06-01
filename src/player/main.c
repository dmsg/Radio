#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "radio.h"

char *program = NULL;

void usage(void)
{
	printf("Usage:\n"
		"  %s config\n", basename(program));
}		

int main(int argc, char **argv)
{
	program = argv[0];

	if(argc != 2) {
		usage();
		exit(1);
	}
    
	int n,ret,i=0,count,file_sockfd,header_sockfd;
	char ip[30]={0};
	FILE *config_pf=NULL;
	int file_fd;
	struct sockaddr_in file_conaddr;
	struct sockaddr_in header_conaddr;
	char *pline=NULL;

	radio_header file_header;
	radio_config radio_config_arr[2]={0};
	radio_unit    file_unit;

	memset(ip,0,sizeof(ip));
	bzero(&file_header, sizeof(file_header));
	bzero(&file_unit, sizeof(file_unit));
	bzero(&file_conaddr, sizeof(file_conaddr));
	bzero(&header_conaddr, sizeof(header_conaddr));



	config_pf=fopen(argv[1], "rb");
	if(config_pf==NULL)
	{
		perror("fopen");
	}
	
	while((ret=getline(&pline ,&n ,config_pf))>0)
	{
		if(strncmp(pline,"#",1)!=0)
		{
			sscanf(pline,"%d %s %d %[0-9,.]:%d",&radio_config_arr[i].channel, radio_config_arr[i].fname, &radio_config_arr[i].bandwidth,ip, &radio_config_arr[i].port);
			radio_config_arr[i].ip=inet_addr(ip);
			memset(ip, 0, sizeof(ip));
			i++;
		}
	}	
     
	fclose(config_pf);
	
	header_conaddr.sin_family=AF_INET;
	header_conaddr.sin_port=htons(radio_config_arr[0].port);
	header_conaddr.sin_addr.s_addr=radio_config_arr[0].ip;

	file_conaddr.sin_family=AF_INET;
	file_conaddr.sin_port=htons(radio_config_arr[1].port);
	file_conaddr.sin_addr.s_addr=radio_config_arr[1].ip;

	file_fd=open(radio_config_arr[1].fname , O_RDONLY);
	if(file_fd<0)
	{
		perror("open");
		exit(1);
	}

	read(file_fd, &file_header, sizeof(radio_header));

	file_sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(file_sockfd<0)
	{
		perror("socket");
		exit(1);
	}

	header_sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(header_sockfd<0)
	{
		perror("scoket");
		exit(1);
	}

	count=file_header.fsize/1024+1;
	while(1)
	{
		for(i=0;i<count;i++)
		{
			read(file_fd, file_unit.data, 1024);

			file_unit.index=i;
			sendto(file_sockfd, &file_unit, sizeof(file_unit), 0, (struct sockaddr *)&file_conaddr, sizeof(file_conaddr));
			bzero(&file_unit, sizeof(file_unit));

			sendto(header_sockfd, &file_header, sizeof(file_header), 0, (struct sockaddr *)&header_conaddr, sizeof(header_conaddr));
			sleep(1);
		}
		lseek(file_fd, sizeof(file_header), SEEK_SET);
	}

	return 0;
}	
