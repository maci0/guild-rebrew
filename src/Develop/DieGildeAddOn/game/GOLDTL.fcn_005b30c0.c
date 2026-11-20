#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6ab50c[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl he_ShowFriedhofMessage(void* recipient, void* a2, void* a3)
{
	io_FormatTextBuffer(g_774a80, 0x40af, 0x40a3, *(unsigned short*) a2,
	             *(int*) ((char*) a2 + 0x16c), *(unsigned short*) a3);
	fcn_00545d40(*(int*) ((char*) recipient + 4), -1, g_774a80, 0, 0x5fa, g_6ab50c);
}
