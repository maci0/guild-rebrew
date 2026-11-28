


extern unsigned char gm_ActiveTownIndex;

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl gm_HasActiveSpecialObject(void*, int);

void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl gm_ApplyEntityPercentCredit(void* record)
{
	char buf[0x100];
	double pct;
	int roll;
	void* entity;
	int amount;

	entity = gm_LookupEntityRecordById(*(int*) record);
	if (entity == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0) {
		return 0x400;
	}
	if (gm_MapEntityStatRange(*(unsigned char*) ((char*) entity + 0x164)) == 7) {
		return 0x400;
	}
	roll = gm_RandomMod(4);
	pct = (double) roll + 1.0;
	amount = (int) (((double) gm_WalkEntityChain(*(unsigned short*) entity) * pct) *
	    0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) record + 4) + 0x12e7, amount);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) record, (*(char*)&gm_ActiveTownIndex), amount);
	he_PostEntityMessage(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
