#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;



#include <string.h>

unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x004a4e80 */
int __cdecl gm_ApplyEntityPercentDebit(void* request)
{
	int n;
	double pct;
	char buf[0x100];
	unsigned char* entity;
	int amount;
	unsigned int len;

	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	n = gm_RandomMod(4) & 0xffff;
	pct = (double) n + 2.0;
	n = gm_CalcPersonWealth(*(short*) entity);
	amount = (int) (((double) n * pct) * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7,
	    (gm_RandomMod(6) & 0xffff) + 3, amount);
	cm_RequestTransferCurrencyNoKill(*(int*) request, -1, gm_ActiveTownIndex, amount);
	len = strlen(buf);
	he_PostEntityMessage(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    0x100 < len, 0x603, 0);
	return 0;
}
