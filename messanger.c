#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc,char *argv[])
{

  system("clear");  
  int pid;
  char usrname[30],*uname;
  char *myargv1[]={".sender",argv[1]};
  char *myargv2[]={".reciver",argv[1]};
   char *myenv[]={"TERM=xterm-256color"};
   	
   pid=fork();
   
   if(pid==0)
   {
    execve(myargv2[0],myargv2,myenv);       
   }
   else
   {
    execve(myargv1[0],myargv1,myenv);   
   }

return 0;
}




