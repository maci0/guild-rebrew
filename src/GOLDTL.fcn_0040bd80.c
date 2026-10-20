/* ADDRESS: GOLDTL 0x006b7fac */
extern int g_6b7fac;



#include "Develop/DieGildeAddOn/game/ch_queue.h"

void __cdecl fcn_0040bd80(char* a1)
{
	if (*(int*) (a1 + 0xc) == 0) {
		*(int*) (a1 + 0x34) = *(int*) ((char*)&g_6b7fac);
	}
	if (*(unsigned int*) ((char*)&g_6b7fac) > (unsigned int) (*(int*) (a1 + 0x34) + *(int*) (a1 + 0x30)) ||
	    *(unsigned char*) (a1 + 0x190) != 0) {
		fcn_004050c0(a1);
	}
}
