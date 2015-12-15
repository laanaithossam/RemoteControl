#include <stdio.h>
#include <windows.h>
#include <pthread.h>
#include <commctrl.h>

#include "ressources.h"
#include "Interface.h"
#include "Functions.h"
#include "Sockets.h"
#include "Process.h"
#include "Powering.h"
#include "Funs.h"

/**Déclarations d'un Thread pour l'écoute**/
pthread_t ThreadAccept;
HINSTANCE Inst;
HWND Status;
HMENU hMenuLoad;
int Soc=0;
char Ip[100];
char Host[100];
int Pid=0;
LRESULT iPid;
LRESULT iSoc;
typedef struct LPPOINT
{
    long x;
    long y;

}Point;

Point Pos;
int MoveMouse=0;
BOOL APIENTRY aPropos_procedure(HWND Dialog,UINT Message,WPARAM wParam,LPARAM lParam)
{
    switch (Message)
    {
        case WM_INITDIALOG:
        return TRUE;
        case WM_COMMAND:
            if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDOK)
            {
                EndDialog(Dialog,0);
                return TRUE;
            }
        return 0;
        default:
        return FALSE;
    }
}

LRESULT CALLBACK Accueil_Form_Event(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
    //Déclarations
    int Result;
    switch (Message)
    {
        case WM_CREATE:
            Status = CreateStatusWindow(WS_CHILD | WS_VISIBLE, "",Window, -1);
            ListPid =CreateWindow(WC_LISTVIEW,
                                "",
                                WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                500,30, 150,400,Window,(HMENU)IDC_LISTPID,Inst,NULL);
                                ZeroMemory(&Lpc,sizeof(LV_COLUMN));
                                ZeroMemory(&Lpi,sizeof(LV_ITEM));

                                Lpc.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;             // Type du Mask
                                Lpc.cx=0x28;                                            // Espace entre les colonnes
                                Lpc.pszText="Processus";                                // Text 1
                                Lpc.cx=0x42;                                            // Largeur de la colonne
                                SendMessage(ListPid,LVM_INSERTCOLUMN,0,(LPARAM)&Lpc);   // Insertion de la colonne
                                Lpc.pszText="Pid";                                      // Colonne suivante
                                SendMessage(ListPid,LVM_INSERTCOLUMN,1,(LPARAM)&Lpc);  // ...
                                Lpi.mask=LVIF_TEXT;   // Text Style
                                Lpi.cchTextMax = 256; // Max size of test
            menu_actionI(hMenuLoad);
        return 0;

        /*case WM_MENUSELECT:
           {
            if(LOWORD(wParam) == ID_B_CONNECT)
            return 0;
           }
        */

        case WM_SIZE:
        {
              RECT sbRect;
              UINT sbheight;
              GetWindowRect(Status, &sbRect);
              sbheight = sbRect.bottom - sbRect.top;
              MoveWindow(Status, 0, HIWORD(lParam)-sbheight, LOWORD(lParam),sbheight, TRUE);
        }
        return 0;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_B_CONNECT:

                    ListClient =CreateWindow(WC_LISTVIEW,
                                "",
                                WS_CHILD | LVS_REPORT | LVS_EDITLABELS|WS_VISIBLE,
                                10,30,194,420,Window,(HMENU)IDC_LISTCLIENT,Inst,NULL);
                                ZeroMemory(&Lcc,sizeof(LV_COLUMN));
                                ZeroMemory(&Lci,sizeof(LV_ITEM));
                                Lcc.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;                                             Lcc.cx=0x28;
                                Lcc.pszText="Ip";
                                Lcc.cx=0x50;
                                SendMessage(ListClient,LVM_INSERTCOLUMN,0,(LPARAM)&Lcc);
                                Lcc.pszText="Host";
                                Lcc.cx=0x42;
                                SendMessage(ListClient,LVM_INSERTCOLUMN,1,(LPARAM)&Lcc);
                                Lcc.pszText="Socket";
                                Lcc.cx=0x30;
                                SendMessage(ListClient,LVM_INSERTCOLUMN,2,(LPARAM)&Lcc);
                                Lci.mask=LVIF_TEXT;   // Text Style
                                Lci.cchTextMax = 256; // Max size of test
                    SendMessage(Status, SB_SETTEXT, 0,(LONG)"Connecté");
                    pthread_create(&ThreadAccept,NULL, (void *(*)(void*))InitSocket,NULL);
                    menu_connecte(hMenuLoad);
                    menu_actionI(hMenuLoad);
                break;

                case ID_B_PID:
                    ListView_DeleteAllItems(ListPid);
                    SavePid(Soc);
                    ShowMyWindow(ListPid,SW_SHOW);
                break;

                case ID_B_LOGOFF:
                    LogOff(Soc);
                    SendMessage(ListClient,LVM_DELETEITEM,iSoc,0);
                break;
                case ID_B_REBOOT:
                    Reboot(Soc);
                    SendMessage(ListClient,LVM_DELETEITEM,iSoc,0);
                break;
                case ID_B_SHUTDOWN:
                    Shutdown(Soc);
                    SendMessage(ListClient,LVM_DELETEITEM,iSoc,0);
                break;
                case ID_B_SLEEP:
                    PowerState(Soc);
                case ID_B_WIZZ :
                    Wizz(Soc);
                break;
                case ID_B_CLOSE :
                    CloseWindowA(Soc);
                break;
                case ID_B_SCREENOFF :
                    ScreenOff(Soc);
                break;
                case ID_B_CONTROLMOUSE:
                    MoveMouse=1;
                    menu_controlA(hMenuLoad);
                break;
                case ID_B_STOPCONTROLMOUSE:
                    MoveMouse=0;
                    menu_actionA(hMenuLoad);
                break;
                case ID_B_KILL:
                    Result=KillPid(Soc,Pid);
                    if(Result!=0)
                    {
                        SendMessage(ListPid,LVM_DELETEITEM,iPid,0);
                        ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Arrêter le processus");
                    }
                    else
                    {
                        MessageBox(Window,"Impossible d'arrêter ce processus",
                        "Error",MB_OK|MB_ICONINFORMATION);
                    }
                break;

                case ID_B_QUIT:
                    MessageBox(Window, "Merci, et à bientôt", "Master 2009", MB_ICONINFORMATION);
                    SendMessage(Window, WM_DESTROY, 0, 0);
                break;

                case ID_DIALOG_APROPOS:
                    DialogBox(Inst, "APROPOS", Window, (DLGPROC)aPropos_procedure);
                break;
            }
        return 0;

        case WM_MOUSEMOVE:
            if(MoveMouse)
            {
                menu_controlA(hMenuLoad);
                GetCursorPos((LPPOINT)&Pos);
                MoveCursor(Soc,Pos.x,Pos.y);
            }
        return 0;

        case WM_NOTIFY:

                    switch(LOWORD(wParam))
                    {
                        case IDC_LISTCLIENT:
                                            // ListView cliquée?

                            if(((LPNMHDR)lParam)->code == NM_CLICK)
                            {
                                if(TestIselect(&iSoc,"Aucun client selectionné",ListClient,Window))
                                {
                                    ListView_GetItemText(ListClient,iSoc,2,Lci.pszText,Lci.cchTextMax);
                                    Soc=atoi(Lci.pszText);
                                    ListView_GetItemText(ListClient,iSoc,1,Lci.pszText,Lci.cchTextMax);
                                    strcpy(Host,Lci.pszText);
                                    ListView_GetItemText(ListClient,iSoc,0,Lci.pszText,Lci.cchTextMax);
                                    strcpy(Ip,Lci.pszText);
                                    strcat(Host,"       ");
                                    strcat(Host,Ip);
                                    menu_actionA(hMenuLoad);
                                    SendMessage(Status, SB_SETTEXT, 0,(LONG)Host);
                                }
                                    else
                                    {
                                        menu_actionI(hMenuLoad);
                                        SendMessage(Status, SB_SETTEXT, 0,(LONG)"Connecté");
                                    }
                            }

                        break;

                        case IDC_LISTPID:

                            if(((LPNMHDR)lParam)->code == NM_CLICK)
                            {
                                if(TestIselect(&iPid,"Aucun Processus selectionné",ListPid,Window))
                                {
                                    ListView_GetItemText(ListPid,iPid,1,Lpi.pszText,Lpi.cchTextMax);
                                    Pid=atoi(Lpi.pszText);
                                    ModifyMenu(hMenuLoad,ID_B_KILL, MF_ENABLED | MF_BYCOMMAND,ID_B_KILL,"Killer le processus");
                                }
                                    else
                                    {
                                        ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Killer le processus");
                                    }
                            }
                            if(((LPNMHDR)lParam)->code == NM_KILLFOCUS)
                                {
                                    ModifyMenu(hMenuLoad,ID_B_KILL, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND,ID_B_KILL,"Killer le processus");
                                }

                        break;
                    }
        return 0;

        case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        default:
        return DefWindowProc(Window, Message, wParam, lParam);
    }

            //NotificationControl(Window,Message,wParam,lParam);

}

// WINMAIN(Instance actuelle,Instance Précédente,Equivalent argv,mode d'affichage)
int WINAPI WinMain (HINSTANCE Instance, HINSTANCE OldInstance,
             LPSTR argv, int Mode)
{
    // Handle de fenetre
    HWND Accueil;
    // Message Systeme
    MSG AccueilMessage;
    // Classe de Fenetres
    WNDCLASS AccueilClass;
    // Instance
    Inst=Instance;
    // Création de la classe de fenetres
    CreateWindowClass (
                        &AccueilClass,0,Accueil_Form_Event,0,0,NULL,
                        IDI_APPLICATION,IDC_ARROW,NULL,"AccueilClass"
                      );
    // Enregistrement de la classe
    RegisterClass(&AccueilClass);
    // Menu
    hMenuLoad = LoadMenu(Inst, "ACCUEIL_MENU");
    //CreateWindow("Nom Classe","Titre fenetre",Style de la fenetre,
                //Coordonnées Fentre (x,y,widht,height),Parent,Menu,Instance,Param.)
    Accueil = CreateWindow (
                            "AccueilClass", "Accueil", WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,hMenuLoad, Inst, NULL
                           );
    // Affichage de la fenetre
    ShowMyWindow(Accueil,SW_SHOW);

   //Gestion des messages
    while (GetMessage(&AccueilMessage, NULL, 0, 0))/*Récupération des évènements de toutes les fenêtres de l'instance dans message*/
    {
        TranslateMessage(&AccueilMessage); // Traduction de l'événement
        DispatchMessage(&AccueilMessage);  // Envoi du message correspondant à la fenêtre concernée

    }
    return AccueilMessage.wParam;
}
