#include "Develop/DieGildeAddOn/game/game_data.h"
char str_NACHRICHTEN_FRIEDHOF_12[] = "_NACHRICHTEN_FRIEDHOF_12";


int __cdecl gm_RandomMod(int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyFriedhof12(void* recipient)
{
	io_FormatTextBuffer(io_MessageFormatBuf, 0x40a8, (gm_RandomMod(3) & 0xffff) + 0x40a9);
	he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 1, 0x5fb, str_NACHRICHTEN_FRIEDHOF_12);
}
