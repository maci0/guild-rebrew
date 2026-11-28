#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6ab430[];
extern char gm_EntitySlotTable[];



unsigned short __cdecl gm_RandomMod(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_BroadcastPlagueOutbreak(void)
{
	char buf[0x100];
	int id;
	int p;

	id = gm_RandomMod(3);
	fcn_0064d41a(buf, g_6ab430, id);
	io_FormatTextBuffer(io_MessageFormatBuf, id + 0x20c7);
	for (p = (int) gm_EntitySlotTable + 2; p < (int) gm_EntitySlotTable + 0x65402; p += 0x21c) {
		if (*(char*) p == 6 || *(char*) p == 7) {
			he_PostEntityMessage(*(int*) (p + 2), -1, io_MessageFormatBuf, 0, 0x600, buf);
		}
	}
}
