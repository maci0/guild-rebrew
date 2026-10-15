#include "Develop/DieGildeAddOn/game/ch_script.h"



#include <string.h>

void __cdecl fcn_00407800(char* e, int slot, int v);

/* `slot` is left unset for an unknown name; the reference reads it from the
 * homed parameter slot. */
int __cdecl fcn_0040e000(char** a, const char* name, int* v)
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
	fcn_00407800(*a, slot, *v);
	return 1;
}
