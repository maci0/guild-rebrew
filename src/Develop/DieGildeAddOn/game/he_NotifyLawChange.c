#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca4[];



void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyLawChange(void* noticeEntity, int lawName)
{
	if (*(unsigned short*) noticeEntity != *(unsigned short*) ((char*)&g_774970)) {
		io_FormatTextBuffer(g_774a80, 0x20c5, *(unsigned short*) noticeEntity, lawName);
		he_PostEntityMessage(*(int*) (g_7f4ca4 + 540 * *(unsigned short*) ((char*)&g_774970)),
		    -1, g_774a80, 0, 0x605, g_6b5c60);
	}
}
