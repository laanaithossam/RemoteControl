#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED
/**ListView des Client**/
LV_ITEM Lci;
LV_COLUMN Lcc;
HWND ListClient;
/**ListView des Process**/
LV_ITEM Lpi;
LV_COLUMN Lpc;
HWND ListPid;

/**Test Iselect**/
void Accept(SOCKET *S_slave,SOCKET S_master,SOCKADDR_IN *Struct,int *size);

BOOL TestIselect(LRESULT *Iselect,char* msg,HWND ListView,HWND Window)
{
    *Iselect=SendMessage(ListView,LVM_GETNEXTITEM,
                        -1,LVNI_FOCUSED);

    if(*Iselect==-1) // no items
                    {
                        MessageBox(Window,msg,
                        "Error",MB_OK|MB_ICONINFORMATION);
                        return FALSE;
                    }

    else return TRUE;
}

/**Ecoute et interception des clients**/
void BeginConnect(SOCKET S_master)
{
    char Action[2]="";
    char buffer[100]="";
    int i=0;
    int quit=0;
    while(quit!=-1)
    {
            fd_set readfs;

            /* On vide l'ensemble de lecture et on lui ajoute
            la socket serveur */
            FD_ZERO(&readfs);
            FD_SET(S_master, &readfs);
            /* Si une erreur est survenue au niveau du select */
            if(select(S_master + 1, &readfs, NULL, NULL, NULL) < 0)
            {
                perror("select()");
                exit(errno);
            }
            /* On regarde si la socket serveur contient des
                informations à lire */
            if(FD_ISSET(S_master, &readfs))
            {
                /* Ici comme c'est la socket du serveur cela signifie
                forcement qu'un client veut se connecter au serveur.
                Dans le cas d'une socket cliente c'est juste des
                données qui serons reçues ici*/
                SOCKET S_slave;
                SOCKADDR_IN Slave;
                int csize = sizeof(Slave);
                Accept(&S_slave,S_master,&Slave,&csize);
                //Entrer des items dans la list-box
                SendMessage (ListClient, LB_ADDSTRING ,0,(LPARAM)inet_ntoa(Slave.sin_addr));
                Lci.iItem=i;          // choose item
                Lci.iSubItem=0;
                Lci.pszText=inet_ntoa(Slave.sin_addr);
                SendMessage(ListClient,LVM_INSERTITEM,0,(LPARAM)&Lci); // Enter text to Items
                Lci.iSubItem=1;
                strcpy(Action,"0");
                send(S_slave,Action,(int)strlen(Action), 0);
                int n = recv(S_slave, buffer, sizeof(buffer), 0);
                buffer[n]='\0';
                strcpy(Lci.pszText,buffer);
                //gethostname(Lci.pszText,Lci.cchTextMax);
                SendMessage(ListClient,LVM_SETITEM,0,(LPARAM)&Lci);
                Lci.iSubItem=2;
                sprintf(Lci.pszText,"%d",S_slave);
                SendMessage(ListClient,LVM_SETITEM,0,(LPARAM)&Lci);  // Enter text to SubItems
            }

    }
        closesocket(S_master);
        WSACleanup();
}

/**Récuperer les infos des Processus Client**/
void SavePid(SOCKET S_slave)
{
    char Action[2]="";
    char buffer[100]="";
    int i=0;
    strcpy(Action,"1");
    send(S_slave,Action,(int)strlen(Action), 0);
    int n = recv(S_slave, buffer, sizeof(buffer), 0);

        while (strcmp(buffer,"-1")!=0)
        {
            Lpi.iItem=i;          // choose item
            Lpi.iSubItem=0;
            Lpi.pszText=buffer;
            SendMessage(ListPid,LVM_INSERTITEM,0,(LPARAM)&Lpi); // Enter text to Items
            send(S_slave, "1", 1, 0);

            // PID
            n = recv(S_slave, buffer, sizeof(buffer), 0);
            buffer[n] = '\0';
            Lpi.iSubItem=1;
            Lpi.pszText=buffer;
            SendMessage(ListPid,LVM_SETITEM,0,(LPARAM)&Lpi);  // Enter text to SubItems
            send(S_slave, "1", 1, 0);

            // Process
            n = recv(S_slave, buffer, sizeof(buffer), 0);
            buffer[n] = '\0';

            i++;

        }

}

#endif // SOCKET_H_INCLUDED
