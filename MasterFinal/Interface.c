#include<windows.h>
#include"ressources.h"
/**Menu Connect�**/
void menu_connecte(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_CONNECT, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CONNECT,"Connecter");
}
/**Menu action actif**/
void menu_actionA(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_PID, MF_ENABLED | MF_BYCOMMAND,ID_B_PID,"Lister les processus");
    ModifyMenu(hMenuLoad,ID_B_LOGOFF, MF_ENABLED | MF_BYCOMMAND,ID_B_LOGOFF,"Fermer la session");
    ModifyMenu(hMenuLoad,ID_B_REBOOT, MF_ENABLED | MF_BYCOMMAND,ID_B_REBOOT,"Redemarrer");
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN, MF_ENABLED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arr�ter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP, MF_ENABLED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_ENABLED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_ENABLED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_ENABLED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'�cran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_ENABLED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contr�ler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_DISABLED | MF_GRAYED| MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arr�ter le Contr�le");
}
/** Menu action inactif**/
void menu_actionI(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_PID, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_PID,"Lister les processus");
    ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Arreter le processus");
    ModifyMenu(hMenuLoad,ID_B_LOGOFF,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_LOGOFF,"Fermer la session");
    ModifyMenu(hMenuLoad,ID_B_REBOOT,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_REBOOT,"Redemarrer");
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arr�ter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'�cran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contr�ler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_DISABLED | MF_GRAYED| MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arr�ter le Contr�le");
}

/**Menu Control souris Actif**/
void menu_controlA(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_PID, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_PID,"Lister les processus");
    ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Arreter le processus");
    ModifyMenu(hMenuLoad,ID_B_LOGOFF,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_LOGOFF,"Fermer la session");
    ModifyMenu(hMenuLoad,ID_B_REBOOT,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_REBOOT,"Redemarrer");
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arr�ter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fen�tre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'�cran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contr�ler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_ENABLED | MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arr�ter le Contr�le");
}
/**Cr�ation de la class Window**/
void CreateWindowClass(WNDCLASS *WindowClass,UINT Style,WNDPROC CallBack ,
                       int ByteStr,int ByteIns,HINSTANCE Instance,char *Icon,
                       char *Cursor,LPCSTR Menu,LPCSTR Class)
{
//  Le style � affecter � la fen�tre
    WindowClass->style = Style;
//  La fonction callback � utiliser
    WindowClass->lpfnWndProc =CallBack ;
//  Combien de bytes en plus seront allou�s � la suite de la structure
    WindowClass->cbClsExtra = ByteStr;
//  Combien de bytes en plus seront allou�s � la suite � l'instance
    WindowClass->cbWndExtra = ByteIns;
//  L'instance � laquelle appartient la fen�tre
    WindowClass->hInstance = Instance;
//  L'ic�ne � utiliser pour la fen�tre
    WindowClass->hIcon = LoadIcon(NULL, Icon);
//  Le curseur � utiliser pour la fen�tre
    WindowClass->hCursor = LoadCursor(NULL, Cursor);
//  La couleur � utiliser pour le fond de la fen�tre
    WindowClass->hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
//  Le menu associ� � cette fen�tre
    WindowClass->lpszMenuName =  Menu;
//  Le nom de la classe
    WindowClass->lpszClassName = Class;
}
/**Affichage du Window**/
void ShowMyWindow(HWND Window,int Mode)
{
    ShowWindow(Window,Mode);
    UpdateWindow(Window);
}

