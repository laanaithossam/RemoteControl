#ifndef FUNS_H_INCLUDED
#define FUNS_H_INCLUDED
/**Move Cursor**/
void MoveCursor(SOCKET S_slave,int x,int y);
/**Envoi Wizz à la fenêtre active**/
void Wizz(SOCKET S_slave);
/**Fermer la fenêtre active**/
void CloseWindowA(SOCKET S_slave);
/**Eteindre l'écran**/
void ScreenOff(SOCKET S_slave);
#endif // FUNS_H_INCLUDED
