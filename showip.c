#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
        {
            FILE *fp;
            char run[100];
            char fname[100];
            char ips[100];
            char interface[200]="sudo arp-scan --interface=$(ifconfig | grep -o 'w.........') --localnet | ";
            char pattern[40]="\"[0-9]+(.)[0-9]+(.)[0-9]+(.)[0-9]+\"";
            char ip[40]="grep -E -o ";
            strtok(interface,"\n");
            strtok(ip,"\n");
            strtok(pattern,"\n");
            strcat(interface,ip);
            //printf("%s",interface);
            strcat(interface,pattern);
            //printf("\n%s",interface);
            fp=popen(interface,"r");
            int i=0;
            
            while (fgets(ips,15, fp) != NULL)
            {
                i++;
                printf("%s",ips);
                fprintf(stdout,"Enter File You Want To send TO %s IP \n",ips);
                scanf("%s",fname);
                    strtok(fname,"\n");
                    strtok(ips,"\n");
                sprintf(run,"./client %s 8080 %s",ips,fname);
                system(run);
                memset(run,'\0',100);
            }
            //system(interface);
               

        }

