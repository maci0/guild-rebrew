#include "Develop/DieGildeAddOn/game/ch_script.h"


void __cdecl ch_SetBodyAttachment(int, int, int);

/* ADDRESS: GOLDDE 0x0040c360 */
int __cdecl GiveObject(int* a1, int* a2)
{
	if (*a1 == 0) {
		return 0;
	}
	ch_SetBodyAttachment(*a1, 2, *a2);
	return 1;
}
