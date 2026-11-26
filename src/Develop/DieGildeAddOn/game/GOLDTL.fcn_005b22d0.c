#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

/* ADDRESS: GOLD 0x005a8e50 */
void __cdecl fcn_005b22d0(void* noticeEntity)
{
	char entityKind;

	entityKind = *(char*) ((char*) noticeEntity + 2);
	if (entityKind == 6 || entityKind == 7) {
		io_FormatTextBuffer(g_774a80, 0x20bd);
		he_PostEntityMessage(*(int*) ((char*) noticeEntity + 4), -1, g_774a80, 0, 0x5ec, g_6b5c60);
	}
}
