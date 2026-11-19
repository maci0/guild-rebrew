#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b21d0(void* entity, void* recipient, int a3)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x20ba, *(unsigned short*) entity, a3);
		fcn_00545d40(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5ec, g_6b5c60);
	}
}
