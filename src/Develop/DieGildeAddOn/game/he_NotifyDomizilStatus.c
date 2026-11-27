#include "Develop/DieGildeAddOn/game/game_data.h"
char g_6ab570[] = "_NACHRICHTEN_DOMIZIL_12";



void __cdecl io_FormatTextBuffer(void*, int, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl he_NotifyDomizilStatus(void* recipient, void* subject, int variant)
{
	io_FormatTextBuffer(g_774a80, 0x4070, subject, variant + 0x4071);
	he_MessageBoxQuickjump(*(int*) ((char*) recipient + 4), -1, g_774a80, 1, 0x5ec,
	    *(int*) ((char*) subject + 1), -1, 0, g_6ab570);
}
