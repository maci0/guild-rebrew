#include "Develop/client_types.h"
extern COMMAND_STATUS_SLOT cm_CommandStatusQueue[0x8000];


/* ADDRESS: GOLDTL 0x004c4450 */
/* ADDRESS: GOLDDE 0x004b1e60 */
int __cdecl cm_GetCommandStatus(int i)
{
	if (i >= 0 && i < 0x8000)
		return ((unsigned char(*)[10])cm_CommandStatusQueue)[i][0];
	return -1;
}
