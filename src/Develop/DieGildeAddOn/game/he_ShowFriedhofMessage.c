#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_NACHRICHTEN_FRIEDHOF_00[];



void __cdecl io_FormatTextBuffer(void*, int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_ShowFriedhofMessage(void* recipient, void* a2, void* a3)
{
	io_FormatTextBuffer(io_MessageFormatBuf, 0x40af, 0x40a3, *(unsigned short*) a2,
	             *(int*) ((char*) a2 + 0x16c), *(unsigned short*) a3);
	he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5fa, str_NACHRICHTEN_FRIEDHOF_00);
}
