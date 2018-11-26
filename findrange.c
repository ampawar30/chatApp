#include"header.h"
#include<signal.h>
#define MSG "RAW"
#define MAXLINE 8 
#define fname "listip"
#define PORTS 65302
FILE *nfp;
int neiboursold[255];  
int neiboursnew[255];
void *sendPackets() { 
    	int sockfd; 
    	char address[13];
   	sprintf(address,"192.168.1.");
  	struct sockaddr_in servaddr; 
	
   	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{ 
        	perror("socket creation failed"); 
        	exit(EXIT_FAILURE); 
    	} 
    	memset(&servaddr, 0, sizeof(servaddr)); 
      
    	servaddr.sin_family = AF_INET; 
    	servaddr.sin_port = htons(PORTS);
    	servaddr.sin_addr.s_addr = inet_addr("192.168.1.255"); 
	
       	int broadcastPermission = 1;
    	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,sizeof(broadcastPermission)) < 0)
        	printf("setsockopt() failed"); 
	while(1)
	{
		
    		sendto(sockfd, (const char *)MSG, sizeof(MSG),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
   		sleep(3);
	}
	close(sockfd);
}
void * updateNeibourTable()
{
	int i;
	nfp=fopen(fname,"w");
	if(nfp==NULL)
	for(i=0;i<255;i++)
	{
		neiboursold[i]=0;
		neiboursnew[i]=0;
		fprintf(nfp,"%c",0x0);
	}
	fseek(nfp,0,SEEK_SET);
	fflush(nfp);
    	while(1)
	{
		for(i=0;i<255;i++)
			{
			neiboursold[i]=neiboursnew[i];
			neiboursnew[i]=0;
			if(neiboursold[i])
			{
				fprintf(nfp,"%c",0x1);
			}
			else
			{	
				fprintf(nfp,"%c",0x0);
			}
			}
		fflush(nfp);
		fseek(nfp,0,SEEK_SET);
		sleep(5);
	}		
 
}

void * receivePackets() 
{ 
    	int sockfd,last_addr; 
	pthread_t update;
	pthread_create(&update,NULL,updateNeibourTable,NULL);
    	char buffer[MAXLINE],address[13],addr[INET_ADDRSTRLEN];
   	sprintf(address,"192.168.1.");
   	struct sockaddr_in servaddr; 

    	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{ 
        	perror("socket creation failed"); 
        	exit(EXIT_FAILURE); 
    	} 
    	memset(&servaddr, 0, sizeof(servaddr)); 
    
    	servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = INADDR_ANY; 
    	servaddr.sin_port = htons(PORTS);
	
    	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
    	{
        	perror("bind failed");
        	exit(EXIT_FAILURE);
    	}

	while(1)
	{
    		int n,len;
		recvfrom(sockfd,(char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len); 
 		inet_ntop(AF_INET,&(servaddr.sin_addr), addr, INET_ADDRSTRLEN);	
			strcpy(buffer,"      ");
			if((strncmp(address,addr,10)==0))
			{
				last_addr=atoi(addr+10);
				fprintf(stdout,"\n %d is online",last_addr);
				if(last_addr>0&&last_addr<255&&last_addr!=my_addr)
					neiboursnew[last_addr]=1;
			}

		
	}
	pthread_join(update,NULL);
	close(sockfd); 
	
} 

int main()
{	
	int p1,p2;
	char c;
	if((p1=fork())==0)
	{
		receivePackets();
	}
	else{
		if((p2=fork())==0)
		{
			sendPackets();
		}
		printf("\n press enter to exit");
		scanf("%c",&c);
		kill(p1,SIGKILL);
		kill(p2,SIGKILL);
		printf("\n exited successfully..");
	}
}
