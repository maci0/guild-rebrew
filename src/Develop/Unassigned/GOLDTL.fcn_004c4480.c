#include "client_types.h"
extern COMMAND_STATUS_SLOT g_fb5760[0x8000];


/* ADDRESS: GOLDTL 0x004c4480 */
int __cdecl cm_GetCommandResult(int slot_idx)
{
	if (slot_idx >= 0 && slot_idx < 0x8000)
		return *(int*) &((unsigned char(*)[10])g_fb5760)[slot_idx][6];
	return 0;
}
