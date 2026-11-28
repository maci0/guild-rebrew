#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;


#include <string.h>

unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

int __cdecl gm_HandleDebitPercentMsg(void* noticeRequest)
{
	int n;
	double d;
	char buf[0x100];
	unsigned char* p;
	int r;
	unsigned int len;

	p = gm_LookupEntityRecordById(*(int*) noticeRequest);
	if (p == 0) {
		return 1;
	}
	n = gm_RandomMod(3) & 0xffff;
	d = (double) n + 2.0;
	n = gm_WalkEntityChain(*(short*) p);
	r = (int) (((double) n * d) * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) noticeRequest + 4) + 0x12e7, r);
	cm_RequestTransferCurrencyNoKill(*(int*) noticeRequest, -1, gm_ActiveTownIndex, r);
	len = strlen(buf);
	he_PostEntityMessage(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    0x100 < len, 0x603, 0);
	return 0;
}
