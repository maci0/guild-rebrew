#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntityIdField[];



void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyLawChange(void* noticeEntity, int lawName)
{
	if (*(unsigned short*) noticeEntity != *(unsigned short*) ((char*)&gm_LocalPlayerSlot)) {
		io_FormatTextBuffer(io_MessageFormatBuf, 0x20c5, *(unsigned short*) noticeEntity, lawName);
		he_PostEntityMessage(*(int*) (gm_EntityIdField + 540 * *(unsigned short*) ((char*)&gm_LocalPlayerSlot)),
		    -1, io_MessageFormatBuf, 0, 0x605, str_empty);
	}
}
