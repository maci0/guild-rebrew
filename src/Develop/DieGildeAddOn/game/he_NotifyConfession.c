#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x00596bd0 */
void __cdecl he_NotifyConfession(void* entity, void* recipient, int church)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20ba, *(unsigned short*) entity, church);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 0, 0x5ec, str_empty);
	}
}
