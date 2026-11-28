#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLDDE 0x00596d50 */
void __cdecl he_NotifyAction0x35Blocked(void* firstEntity, void* secondEntity)
{
	char t;

	t = *(char*) ((char*) firstEntity + 2);
	if (t == 6 || t != 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20bf);
		he_PostEntityMessage(*(int*) ((char*) firstEntity + 4), -1, io_MessageFormatBuf, 0, 0x5fb, str_empty);
	}
	t = *(char*) ((char*) secondEntity + 2);
	if (t == 6 || t != 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20c0, *(unsigned short*) firstEntity);
		he_PostEntityMessage(*(int*) ((char*) secondEntity + 4), -1, io_MessageFormatBuf, 0, 0x5fb, str_empty);
	}
}
