#include "Develop/DieGildeAddOn/game/game_data.h"
extern char str_empty[];



void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyStraftatExpired(void* recipientRecord, void* messageSubject)
{
	io_FormatTextBuffer(io_MessageFormatBuf, 0x1747, *(unsigned short*) messageSubject);
	he_PostEntityMessage(*(int*) ((char*) recipientRecord + 4), -1, io_MessageFormatBuf, 0, 0x5fa, str_empty);
}
