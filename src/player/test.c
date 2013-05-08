#include<stdio.h>
#include "../include/radio.h"
 #include <sys/types.h>     
        #include <sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#define MYIP "192.168.9.150"
#define MULIP "224.0.0.4"
int main()
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in selfaddr,conaddr;
	radio_unit buf;
	struct ip_mreq mreq;

	bzero(&selfaddr,sizeof(selfaddr));
	bzero(&conaddr,sizeof(conaddr));
	bzero(&buf,sizeof(buf));

	selfaddr.sin_family=AF_INET;
	selfaddr.sin_port=htons(1235);
	selfaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	len=sizeof(conaddr);

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bind(sockfd,(struct sockaddr *)&selfaddr,sizeof(selfaddr));
	
	mreq.imr_multiaddr.s_addr=inet_addr(MULIP);
	mreq.imr_interface.s_addr=inet_addr(MYIP);

	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
		
	

	while(1)
	{
		recvfrom(sockfd,(void *)&buf,sizeof(buf),0,(struct sockaddr *)&conaddr,&len);
		printf("buf=%s\n",buf.data);
		sleep(1);
		}
	return 0;
}
