#include<windows.h>
/**SLEEP,LOGOFF,REBOT,SHUTDOWN**/

void PowerState(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"6");
    send(S_slave,Action,(int)strlen(Action), 0);
}

void LogOff(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"3");
    send(S_slave,Action,(int)strlen(Action), 0);
}
void Reboot(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"4");
    send(S_slave,Action,(int)strlen(Action), 0);
}
void Shutdown(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"5");
    send(S_slave,Action,(int)strlen(Action), 0);
}

