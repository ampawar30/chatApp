#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
void AdHoc(char *dev)
{

 char *stopNM="sudo service network-manager stop" ,setDown[50], ahMode[50], channel[50],essid[50],key[50],setUp[50],setIP[50];
 char *wdev;

 wdev=strtok(dev,"\n");
 
 sprintf(setDown,"sudo ip link set %s down",wdev);
 sprintf(ahMode,"sudo iwconfig %s mode ad-hoc",wdev);
 sprintf(channel,"sudo iwconfig %s channel 1",wdev);
 sprintf(essid,"sudo iwconfig %s essid 'JADU'",wdev);
 sprintf(key,"sudo iwconfig %s key 1234567890",wdev);
 sprintf(setUp,"sudo ip link set %s up",wdev);
 sprintf(setIP,"sudo ip addr add 192.168.1.219 dev %s",wdev);
 
 system(stopNM);
 system(setDown);
 system(ahMode);
 system(channel);
 system(essid);
 system(key);
 system(setUp);
 system(setIP);

}

int main()
{
    FILE *fp=NULL;
    char wdev[20];
    system("ifconfig | grep -o 'wl.....' > .wdev ");
    fp=fopen(".wdev","r");
   
    memset(wdev,'\0',20);
    fgets(wdev,20,fp);
    AdHoc(wdev);

    return 0;
}
