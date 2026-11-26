#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6b5c60[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl he_NotifyAction0x35Blocked(void* firstEntity, void* secondEntity)
{
	char t;

	t = *(char*) ((char*) firstEntity + 2);
	if (t == 6 || t != 7) {
		io_FormatTextBuffer(g_774a80, 0x20bf);
		he_PostEntityMessage(*(int*) ((char*) firstEntity + 4), -1, g_774a80, 0, 0x5fb, g_6b5c60);
	}
	t = *(char*) ((char*) secondEntity + 2);
	if (t == 6 || t != 7) {
		io_FormatTextBuffer(g_774a80, 0x20c0, *(unsigned short*) firstEntity);
		he_PostEntityMessage(*(int*) ((char*) secondEntity + 4), -1, g_774a80, 0, 0x5fb, g_6b5c60);
	}
}
