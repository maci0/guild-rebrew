#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl he_NotifyOfficeAction(void* setter, void* recipient)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x20bb, *(unsigned short*) setter);
		fcn_00545d40(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5fd, g_6b5c60);
	}
}
