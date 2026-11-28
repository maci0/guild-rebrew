#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6ab44c[];
extern char gm_EntityIdField[];



unsigned short __cdecl gm_RandomMod(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_BroadcastReaperEvent(void)
{
	char buf[0x40];
	int id;
	int p;

	id = gm_RandomMod(2);
	fcn_0064d41a(buf, g_6ab44c, id + 0x12);
	io_FormatTextBuffer(io_MessageFormatBuf, id + 0x20cd);
	for (p = (int) gm_EntityIdField; p < (int) gm_EntityIdField + 0x65400; p += 0x21c) {
		if (*(char*) (p - 2) == 6) {
			he_PostEntityMessage(*(int*) p, -1, io_MessageFormatBuf, 0, 0x600, buf);
		}
	}
}
