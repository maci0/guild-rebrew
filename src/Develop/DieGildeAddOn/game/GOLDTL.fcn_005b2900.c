extern char g_774a80[];
extern char g_6b5c60[];
extern char g_7f4ca4[];
#include "Develop/DieGildeAddOn/game/game_player.h"




void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl amt_NotifyOfficeSwap(void* first, void* second, void* third)
{
	if (*(char*) ((char*) second + 2) == 6) {
		io_FormatTextBuffer(g_774a80, 0x1dcc, *(unsigned short*) first, *(unsigned short*) third);
		fcn_00545d40(*(int*) ((char*) second + 4), -1, g_774a80, 0, 0x5fd, g_6b5c60);
		return;
	}
	if (*(char*) ((char*) third + 2) == 6) {
		io_FormatTextBuffer(g_774a80, 0x1dcc, *(unsigned short*) first, *(unsigned short*) second);
		fcn_00545d40(*(int*) ((char*) third + 4), -1, g_774a80, 0, 0x5fd, g_6b5c60);
		return;
	}
	if (*(char*) ((char*) first + 2) != 6) {
		io_FormatTextBuffer(g_774a80, 0x1dcd, *(unsigned short*) first, *(unsigned short*) second,
		    *(unsigned short*) third);
		fcn_00545d40(*(int*) (g_7f4ca4 + 540 * *(unsigned short*) ((char*)&g_774970)), -1,
		    g_774a80, 0, 0x5fe, g_6b5c60);
	}
}
unsigned char _dpad_774a80[2200];
