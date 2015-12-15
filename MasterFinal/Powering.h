#ifndef POWERING_H_INCLUDED
#define POWERING_H_INCLUDED

/**SLEEP,LOGOFF,REBOT,SHUTDOWN**/
void PowerState(SOCKET S_slave);
void LogOff(SOCKET S_slave);
void Reboot(SOCKET S_slave);
void Shutdown(SOCKET S_slave);

#endif // POWERING_H_INCLUDED
