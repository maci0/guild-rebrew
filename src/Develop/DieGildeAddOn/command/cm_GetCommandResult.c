#include "Develop/client_types.h"
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];


/* ADDRESS: GOLDTL 0x004c4480 */
/* ADDRESS: GOLDDE 0x004b1e90 */
int __cdecl cm_GetCommandResult(int slot_idx)
{
	if (slot_idx >= 0 && slot_idx < 0x8000)
		return *(int*) &((unsigned char(*)[10])cm_CommandStatusQueue)[slot_idx][6];
	return 0;
}
