#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
/**Menu Connecté**/
void menu_connecte(HMENU hMenuLoad);
/**Menu action actif**/
void menu_actionA(HMENU hMenuLoad);
/** Menu action inactif**/
void menu_actionI(HMENU hMenuLoad);
void menu_controlA(HMENU hMenuLoad);
/**Création de la class Window**/
void CreateWindowClass(WNDCLASS *WindowClass,UINT Style,WNDPROC CallBack ,
                       int ByteStr,int ByteIns,HINSTANCE Instance,char *Icon,
                       char *Cursor,LPCSTR Menu,LPCSTR Class);
/**Affichage du Window**/
void ShowMyWindow(HWND Window,int Mode);

#endif // FONCTIONS_H_INCLUDED
