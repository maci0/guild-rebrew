#ifndef CLIENT_ACTIONS_H
#define CLIENT_ACTIONS_H

extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;
extern char* gm_CityEntity;

char* __cdecl gm_FindPublicTreasury(int modus);
int __cdecl RunBuergermeister(char* objekt, char* ziel, char* aktion);

#endif
