#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLD 0x005a8e50 */
void __cdecl he_NotifyObjektMessage(void* noticeEntity)
{
	char entityKind;

	entityKind = *(char*) ((char*) noticeEntity + 2);
	if (entityKind == 6 || entityKind == 7) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20bd);
		he_PostEntityMessage(*(int*) ((char*) noticeEntity + 4), -1, io_MessageFormatBuf, 0, 0x5ec, str_empty);
	}
}
