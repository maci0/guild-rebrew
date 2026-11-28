extern char io_MessageFormatBuf[];
extern char str_empty[];
extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_player.h"




void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl amt_NotifyOfficeSwap(void* first, void* second, void* third)
{
	if (*(char*) ((char*) second + 2) == 6) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x1dcc, *(unsigned short*) first, *(unsigned short*) third);
		he_PostEntityMessage(*(int*) ((char*) second + 4), -1, io_MessageFormatBuf, 0, 0x5fd, str_empty);
		return;
	}
	if (*(char*) ((char*) third + 2) == 6) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x1dcc, *(unsigned short*) first, *(unsigned short*) second);
		he_PostEntityMessage(*(int*) ((char*) third + 4), -1, io_MessageFormatBuf, 0, 0x5fd, str_empty);
		return;
	}
	if (*(char*) ((char*) first + 2) != 6) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x1dcd, *(unsigned short*) first, *(unsigned short*) second,
		    *(unsigned short*) third);
		he_PostEntityMessage(*(int*) (gm_EntityIdField + 540 * *(unsigned short*) ((char*)&gm_LocalPlayerSlot)), -1,
		    io_MessageFormatBuf, 0, 0x5fe, str_empty);
	}
}
unsigned char _dpad_774a80[2200];
