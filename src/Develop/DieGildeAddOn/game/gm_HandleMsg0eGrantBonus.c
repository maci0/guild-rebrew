#include <string.h>

extern unsigned char gm_ActiveTownIndex;

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004b74b0 */
/* ADDRESS: GOLDDE 0x004a5660 */
int __cdecl gm_HandleMsg0eGrantBonus(int* request)
{
	char buf[0x100];
	unsigned short* entity;
	int amount;

	entity = gm_LookupEntityRecordById(request[0]);
	if (entity == 0)
		return 1;
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0)
		return 0x400;
	amount = (int) ((gm_RandomMod(2) + 1.0) * gm_CalcPersonWealth(*entity) * 0.01);
	if (amount > gm_CalcPersonWealth(*entity))
		return 0;
	io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, amount);
	cm_RequestTransferCurrencyNoKill(-1, request[0], gm_ActiveTownIndex, amount);
	he_PostEntityMessage(*(int*) (entity + 2), *(int*) (entity + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
