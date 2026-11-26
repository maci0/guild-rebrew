#include "Develop/DieGildeAddOn/game/game_data.h"
char g_6ab4d4[] = "_NACHRICHTEN_FRIEDHOF_12";


int __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl fcn_005b2f60(void* a1)
{
	io_FormatTextBuffer(g_774a80, 0x40a8, (gm_RandomMod(3) & 0xffff) + 0x40a9);
	he_PostEntityMessage(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5fb, g_6ab4d4);
}
