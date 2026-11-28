#include <string.h>

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern unsigned char gm_ActiveTownIndex;

void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0048e4b0 */
/* ADDRESS: GOLDDE 0x0047d380 */
int __cdecl ai_RunSecretRoomSpyKiller(char* entity, char* request, char* params)
{
	int found;
	char msg[0xf8];
	F8 filter;

	cm_RequestTransferCurrencyNoKill(-1, *(int*) (entity + 4), (*(char*)&gm_ActiveTownIndex), *(int*) (params + 8));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x99;
	*(int*) (msg + 8) = *(int*) (entity + 4);
	*(int*) (msg + 0xc) = *(int*) (request + 0xc);
	*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x2c) = (*(int*)&gm_GameTimeHour);
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	msg[0x36] = 2;
	*(int*) (msg + 0x5c) = *(int*) (request + 0xc);
	*(int*) (msg + 0x60) = -1;
	*(int*) (msg + 0x64) = -1;
	*(int*) (msg + 0x68) = 3;
	*(int*) (msg + 0x6c) = *(int*) (params + 0x10);
	found = -1;
	filter.mask = 0x7b4c4a0;
	filter.b = 0;
	ai_FindEntityInFavorRange(entity, 0, filter, 0, 100.0f, &found);
	*(int*) (msg + 0x58) = found;
	cm_SendCopyEntityData(msg);
	return 1;
}
