#include<windows.h>
#include<stdio.h>
void BeginConnect(SOCKET S_master);
/**Fonctions Socket**/
void SetVersion(WSADATA *w)
{
    // Version de WINSOCK 2.0
    WSAStartup(MAKEWORD(2, 0), w);
}
void NewSocket(SOCKET *Socket)
{
    // Création du Socket s (protocol family:TCP/IP,Socket orienté connexion,Protocole TCP)
    *Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void SetStruct(SOCKADDR_IN *Struct,int port)
{
    // Address Family
    Struct->sin_family       = AF_INET;
    // Definition de l'adresse du serveur & Convert Ip to Int
    Struct->sin_addr.s_addr  = htonl(INADDR_ANY);
    // Definition du port
    Struct->sin_port         = htons(port);
    memset(&Struct->sin_zero, '\0', sizeof(Struct->sin_zero));

}
void Link(SOCKET Socket,SOCKADDR_IN *Struct)
{
    // Liaison entre le socket et le slave
    if (bind(Socket, (SOCKADDR *)Struct, sizeof(*Struct)) == SOCKET_ERROR)
    printf("La fonction bind a echoue.\n");
}
void Listen(SOCKET Socket)
{
    /* listen : commencer l'ecoute */
    if(listen(Socket, 0) == SOCKET_ERROR)
    printf("La fonction listen a echoue.\n");
}
void Accept(SOCKET *S_slave,SOCKET S_master,SOCKADDR_IN *Struct,int *size)
{
    *S_slave = accept(S_master, (SOCKADDR *)Struct, size);
    if (*S_slave == INVALID_SOCKET)
    printf("La fonction accept a echoue.\n");

}

int TestSocket(SOCKET S_slave)
{
    char Action[2]="";
    int n;
    strcpy(Action,"99");
    send(S_slave,Action,(int)strlen(Action), 0);
    n=recv(S_slave,Action, sizeof(Action), 0);
    return n;
}

/**Initialisation du Socket**/
void InitSocket()
{

/**Déclarations des variables pour les Sockets**/
    WSADATA wsaData;
    SOCKET S_master;
    SOCKADDR_IN Master;

    // Version Winsock
    SetVersion(&wsaData);
    // New Socket
    NewSocket(&S_master);
    // Structure du Master
    SetStruct(&Master,5050);
    // Link
    Link(S_master,&Master);
    // Listen
    Listen(S_master);
    // Connecter
    BeginConnect(S_master);

}
