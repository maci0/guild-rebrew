#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyStraftatExpired(void* recipientRecord, void* messageSubject)
{
	io_FormatTextBuffer(g_774a80, 0x1747, *(unsigned short*) messageSubject);
	he_PostEntityMessage(*(int*) ((char*) recipientRecord + 4), -1, g_774a80, 0, 0x5fa, g_6b5c60);
}
