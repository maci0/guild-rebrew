#include <string.h>

extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_LookupEntityRecordById(int id);
unsigned short __cdecl gm_RandomMod(int n);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b6650 */
int __cdecl gm_HandleMsg00DebitWealth(int* a)
{
	char buf[0x100];
	double d;
	char* t;
	int n;

	t = gm_LookupEntityRecordById(a[0]);
	if (t == 0) {
		return 1;
	}
	d = gm_RandomMod(3) + 1.0;
	n = (int) (gm_WalkEntityChain(*(unsigned short*) t) * d * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) (a + 1) + 0x12e7, n);
	cm_RequestTransferCurrencyNoKill(a[0], -1, (*(char*)&gm_ActiveTownIndex), n);
	he_PostEntityMessage(*(int*) (t + 4), *(int*) (t + 4), buf, strlen(buf) > 0x100 ? strlen(buf) > 0x100 : 0, 0x603, 0);
	return 0;
}
