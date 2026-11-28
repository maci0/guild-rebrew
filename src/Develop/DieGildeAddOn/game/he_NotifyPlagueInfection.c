#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6ab430[];



unsigned short __cdecl gm_RandomMod(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyPlagueInfection(void* recipient)
{
	char buf[0x40];
	int id;
	char t;

	id = gm_RandomMod(2);
	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		fcn_0064d41a(buf, g_6ab430, id + 3);
		io_FormatTextBuffer(io_MessageFormatBuf, id + 0x20ca);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x600, buf);
	}
}
