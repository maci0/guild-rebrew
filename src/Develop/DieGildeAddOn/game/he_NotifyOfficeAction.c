#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyOfficeAction(void* setter, void* recipient)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20bb, *(unsigned short*) setter);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5fd, str_empty);
	}
}
