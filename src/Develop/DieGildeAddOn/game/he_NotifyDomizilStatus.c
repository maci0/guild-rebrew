#include "Develop/DieGildeAddOn/game/game_data.h"
char str_NACHRICHTEN_DOMIZIL_12[] = "_NACHRICHTEN_DOMIZIL_12";



void __cdecl io_FormatTextBuffer(void*, int, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

/* ADDRESS: GOLDDE 0x00597e10 */
void __cdecl he_NotifyDomizilStatus(void* recipient, void* subject, int variant)
{
	io_FormatTextBuffer(io_MessageFormatBuf, 0x4070, subject, variant + 0x4071);
	he_MessageBoxQuickjump(*(int*) ((char*) recipient + 4), -1, io_MessageFormatBuf, 1, 0x5ec,
	    *(int*) ((char*) subject + 1), -1, 0, str_NACHRICHTEN_DOMIZIL_12);
}
