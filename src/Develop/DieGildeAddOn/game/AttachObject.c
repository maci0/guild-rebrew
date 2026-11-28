#include "Develop/DieGildeAddOn/game/ch_script.h"



#include <string.h>

void __cdecl ch_SetBodyAttachment(char* e, int slot, int v);

/* `slot` is left unset for an unknown name; the reference reads it from the
 * homed parameter slot. */
/* ADDRESS: GOLDDE 0x0040ce00 */
int __cdecl AttachObject(char** a, const char* name, int* v)
{
	int slot;

	if (*a == 0) {
		return 0;
	}
	if (strcmp(name, "d3_LeftHand") == 0) {
		slot = 1;
	} else if (strcmp(name, "d3_RightHand") == 0) {
		slot = 2;
	} else if (strcmp(name, "d3_Head") == 0) {
		slot = 3;
	}
	ch_SetBodyAttachment(*a, slot, *v);
	return 1;
}
