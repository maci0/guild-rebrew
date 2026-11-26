

void* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int  __cdecl gm_HasActiveSpecialObject(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl gm_ApplyWealthPercentDebit(void* noticeRequest)
{
	char buf[0x400];
	double d;
	int v;
	void* entity;
	int n;

	entity = gm_LookupEntityRecordById(*(int*) noticeRequest);
	if (entity == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0) {
		return 0x400;
	}
	v = gm_RandomMod(2);
	d = (double) v + *(double*) 0x6629c8;
	n = (int) (((double) gm_WalkEntityChain(*(unsigned short*) entity) * d) *
	    *(double*) 0x6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) noticeRequest + 4) + 0x12e7, n);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) noticeRequest, *(char*) 0x773d75, n);
	he_PostEntityMessage(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
