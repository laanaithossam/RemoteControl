#include<windows.h>
#include<stdio.h>
/**Move Cursor**/
void MoveCursor(SOCKET S_slave,int x,int y)
{
    int n;
    char Recu[1];
    char Action[2]="";
    char buffer[100];

        strcpy(Action,"7");
        send(S_slave,Action,(int)strlen(Action), 0);

        n = recv(S_slave, Recu, sizeof(Recu), 0);
        sprintf(buffer, "%d",x);
        send(S_slave, buffer, (int)strlen(buffer), 0);

        n = recv(S_slave, Recu, sizeof(Recu), 0);
        sprintf(buffer, "%d",y);
        send(S_slave, buffer, (int)strlen(buffer), 0);
        n = recv(S_slave, Recu, sizeof(Recu), 0);
}


/**Envoi Wizz à la fenêtre active**/
void Wizz(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"2");
    send(S_slave,Action,(int)strlen(Action), 0);
}

/**Ferme la fenêtre active**/
void CloseWindowA(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"8");
    send(S_slave,Action,(int)strlen(Action), 0);
}
/**Eteindre l'écran**/
void ScreenOff(SOCKET S_slave)
{
    char Action[2]="";
    strcpy(Action,"9");
    send(S_slave,Action,(int)strlen(Action), 0);
}
