#include<windows.h>
#include<stdio.h>
/**Killer le processus du client**/
int KillPid(SOCKET S_slave,int Pid)
{
    char Recu[1];
    char Action[2]="";
    char buffer[100];

    int n ;
    strcpy(Action,"11");
    send(S_slave,Action,(int)strlen(Action), 0);
    n = recv(S_slave, Recu, sizeof(Recu), 0);
    sprintf(buffer, "%d",Pid);
    send(S_slave, buffer, (int)strlen(buffer), 0);
    n = recv(S_slave, Recu, sizeof(Recu), 0);
    buffer[n] = '\0';
    n=atoi(buffer);
    return n;
}
