#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED
/**Fonctions Socket**/
void SetVersion(WSADATA *w);
void NewSocket(SOCKET *Socket);
void SetStruct(SOCKADDR_IN *Struct,int port);
void Link(SOCKET Socket,SOCKADDR_IN *Struct);
void Listen(SOCKET Socket);
void Accept(SOCKET *S_slave,SOCKET S_master,SOCKADDR_IN *Struct,int *size);
int TestSocket(SOCKET S_slave);
/**Initialisation du Socket**/
void InitSocket();
#endif // SOCKETS_H_INCLUDED
