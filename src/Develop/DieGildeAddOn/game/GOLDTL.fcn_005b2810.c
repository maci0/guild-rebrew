#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6ab430[];



unsigned short __cdecl gm_RandomMod(int);
int  __cdecl fcn_0064d41a(char*, char*, int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2810(void* recipient)
{
	char buf[0x40];
	int id;
	char t;

	id = gm_RandomMod(2);
	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		fcn_0064d41a(buf, g_6ab430, id + 3);
		io_FormatTextBuffer(g_774a80, id + 0x20ca);
		fcn_00545d40(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x600, buf);
	}
}
