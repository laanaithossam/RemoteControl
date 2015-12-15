#include<windows.h>
#include"ressources.h"
/**Menu Connecté**/
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
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN, MF_ENABLED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arrêter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP, MF_ENABLED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_ENABLED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_ENABLED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_ENABLED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'écran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_ENABLED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contrôler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_DISABLED | MF_GRAYED| MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arrêter le Contrôle");
}
/** Menu action inactif**/
void menu_actionI(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_PID, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_PID,"Lister les processus");
    ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Arreter le processus");
    ModifyMenu(hMenuLoad,ID_B_LOGOFF,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_LOGOFF,"Fermer la session");
    ModifyMenu(hMenuLoad,ID_B_REBOOT,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_REBOOT,"Redemarrer");
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arrêter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'écran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contrôler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_DISABLED | MF_GRAYED| MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arrêter le Contrôle");
}

/**Menu Control souris Actif**/
void menu_controlA(HMENU hMenuLoad)
{
    ModifyMenu(hMenuLoad,ID_B_PID, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_PID,"Lister les processus");
    ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Arreter le processus");
    ModifyMenu(hMenuLoad,ID_B_LOGOFF,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_LOGOFF,"Fermer la session");
    ModifyMenu(hMenuLoad,ID_B_REBOOT,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_REBOOT,"Redemarrer");
    ModifyMenu(hMenuLoad,ID_B_SHUTDOWN,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SHUTDOWN,"Arrêter");
    ModifyMenu(hMenuLoad,ID_B_SLEEP,MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SLEEP,"Mise en veille");
    ModifyMenu(hMenuLoad,ID_B_WIZZ, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_WIZZ,"Wizzer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_CLOSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CLOSE,"Fermer la fenêtre active");
    ModifyMenu(hMenuLoad,ID_B_SCREENOFF, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_SCREENOFF,"Eteindre l'écran");
    ModifyMenu(hMenuLoad,ID_B_CONTROLMOUSE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_CONTROLMOUSE,"Contrôler la souris");
    ModifyMenu(hMenuLoad,ID_B_STOPCONTROLMOUSE, MF_ENABLED | MF_BYCOMMAND,ID_B_STOPCONTROLMOUSE,"Arrêter le Contrôle");
}
/**Création de la class Window**/
void CreateWindowClass(WNDCLASS *WindowClass,UINT Style,WNDPROC CallBack ,
                       int ByteStr,int ByteIns,HINSTANCE Instance,char *Icon,
                       char *Cursor,LPCSTR Menu,LPCSTR Class)
{
//  Le style à affecter à la fenêtre
    WindowClass->style = Style;
//  La fonction callback à utiliser
    WindowClass->lpfnWndProc =CallBack ;
//  Combien de bytes en plus seront alloués à la suite de la structure
    WindowClass->cbClsExtra = ByteStr;
//  Combien de bytes en plus seront alloués à la suite à l'instance
    WindowClass->cbWndExtra = ByteIns;
//  L'instance à laquelle appartient la fenêtre
    WindowClass->hInstance = Instance;
//  L'icône à utiliser pour la fenêtre
    WindowClass->hIcon = LoadIcon(NULL, Icon);
//  Le curseur à utiliser pour la fenêtre
    WindowClass->hCursor = LoadCursor(NULL, Cursor);
//  La couleur à utiliser pour le fond de la fenêtre
    WindowClass->hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
//  Le menu associé à cette fenêtre
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

