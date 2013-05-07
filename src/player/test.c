#include<stdio.h>
 #include <sys/types.h>     
        #include <sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#define MYIP "192.168.9.150"
#define MULIP "224.0.0.0"
int main()
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in selfaddr,conaddr;
	char buf[100]={0};
	struct ip_mreq mreq;

	bzero(&selfaddr,sizeof(selfaddr));
	bzero(&conaddr,sizeof(conaddr));

	selfaddr.sin_family=AF_INET;
	selfaddr.sin_port=htons(1235);
	selfaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	len=sizeof(selfaddr);

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bind(sockfd,(struct sockaddr *)&selfaddr,sizeof(selfaddr));
	
	mreq.imr_multiaddr.s_addr=inet_addr(MULIP);
	mreq.imr_interface.s_addr=inet_addr(MYIP);

	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
		
	

	recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&conaddr,&len);
	while(1)
	{
		printf("buf=%s\n",buf);
		sleep(1);
		}
	return 0;
}
