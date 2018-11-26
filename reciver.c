#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
 #include<errno.h>
#define MAX 80
#define PORT 8080

typedef struct reciverSocketData
{
    int reciver_fd;
    struct sockaddr_in forward_addr,reciver_addr, client_addr;
}reciverSocketData;



reciverSocketData * reciverSocket(int port) 
{
 reciverSocketData *sock;
int on=1;
 sock=(reciverSocketData *)malloc(sizeof(reciverSocketData));
 
 sock->reciver_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sock->reciver_fd==-1)
    {
        perror("Unable to initiate listener socket");
        exit(1);
    }

 memset(&sock->reciver_addr,'0',sizeof(sock->reciver_addr));     
//int l=sizeof(struct sockaddr_in);
int l=sizeof(sock->reciver_addr);
 sock->reciver_addr.sin_family = AF_INET;
 sock->reciver_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 sock->reciver_addr.sin_port=htons(port);
// memset(&sock->reciver_addr.sin_zero, '\0', sizeof(sock->reciver_addr.sin_zero));
           
        

//int err=bind(sock->reciver_fd , (struct sockaddr *) &sock->reciver_addr ,l ); 
//printf("pas 2 %d\n",err); 
if((bind(sock->reciver_fd , (struct sockaddr *) &sock->reciver_addr , sizeof(sock->reciver_addr) )) == -1)
 {
	printf("pas 2 %i\n",errno);
     fprintf(stdout,"Address Binding Failed");
     exit(1);
 }
//exit(0);
printf("Bind |\n");
 return sock; 
}//end of receiversocketdata

void forwardMsg(reciverSocketData *sock,char *destNumber,char *fwdmsg)
{
     
     memset(&sock->forward_addr,'0',sizeof(sock->reciver_addr));
      sock->forward_addr.sin_port=htons(65302);
       sock->forward_addr.sin_family=AF_INET;
        sock->forward_addr.sin_addr.s_addr = inet_addr(destNumber) ;
         printf("Destination no =%s,msg=%s",destNumber,fwdmsg);
         sendto(sock->reciver_fd,fwdmsg,strlen(fwdmsg),0,(struct sockaddr *) &sock->forward_addr,sizeof(sock->forward_addr));
}

void func()
    {
        char buff[MAX];
	reciverSocketData *sock;
    char msg[1023],dest[20],ip[20],fwdmsg[100];
    int cnt,msglen,pid;
    	sock=reciverSocket(65302);
	    printf("bind");
        int k,n,clen,addrlen;
        struct sockaddr_in cli;
	char msgcp[100];
        addrlen=sizeof(sock->client_addr);
	char *end="@";         
	for(;;)
        {
        
	        memset(msg,'\0',1024);
 	 	recvfrom(sock->reciver_fd, msg , 1024 , 0 , (struct sockaddr *) &sock->client_addr , (socklen_t *) &addrlen );    
 	 	printf("\t%s\n",msg);
		strcpy(msgcp,msg);
 	     msglen=strlen(msg);
 	     printf("last char =\t%c\n",msg[msglen-1]);
         if(msg[msglen-1]==end[0])
         {
        cnt=0;
     	k=0;
        char *ch="+";
       
        while(1)
        {
            if(msg[k]==ch[0])
            {
                break;
            }
            else
            {
            cnt++;
            }
            k++;
        }
       
        char fwdmsg[cnt];
        strncpy(fwdmsg,msg,cnt);
		printf("fwdmsg=%s",fwdmsg);
		printf("1IP=%s\n",dest);
               strcpy(dest,msgcp+(cnt+1));
             strtok(dest,"@");
		printf("2IP=%s\n",dest);
            pid=fork();
                if(pid==0)
                {
                printf("SENDING ANOTHER HOST**************");
                forwardMsg(sock,dest,fwdmsg);
                }


         }
         else
         {
               printf("Reciver Storage =%s\t ",msg);
         }
               memset(msg,'\0',1024);
               memset(dest,'\0',1024);
               memset(fwdmsg,'\0',1024);//newly add 3:11 
           
        }
    printf("EOF\n");
}

int main()
    {
        
         func();
}
