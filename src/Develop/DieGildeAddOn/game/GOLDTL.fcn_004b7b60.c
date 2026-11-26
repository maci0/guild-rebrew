#include <string.h>

extern unsigned char g_773d75;

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004b7b60 */
int __cdecl fcn_004b7b60(int* request)
{
	char buf[0x400];
	unsigned short* e;
	int v;

	e = gm_LookupEntityRecordById(request[0]);
	if (e == 0)
		return 1;
	if (gm_HasActiveSpecialObject(e, 0x290) != 0)
		return 0x400;
	v = (int) ((gm_RandomMod(3) + 1.0) * gm_WalkEntityChain(*e) * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, gm_RandomMod(0xf) + 2, v);
	cm_RequestTransferCurrencyNoKill(-1, request[0], g_773d75, v);
	he_PostEntityMessage(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
