#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_774a80[];
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl he_NotifyAblassPurchase(void* entity, void* recipient, int church, int payout, int cost)
{
	char t;
	int tag;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		if (*(char*) ((char*) recipient + 0xc) == 0) {
			tag = 0x20b7;
		} else {
			tag = ((*(int*)&gm_GameTime) >= 0x75) ? 0x20b9 : 0x20b8;
		}
		io_FormatTextBuffer(g_774a80, 0x20b6, *(unsigned short*) entity, church, cost, payout, tag);
		fcn_00545d40(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5ff, g_6b5c60);
	}
}
