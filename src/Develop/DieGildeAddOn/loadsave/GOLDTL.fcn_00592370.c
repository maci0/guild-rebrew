


// SIZE 0xc
#include "client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 g_779d00[];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

int __cdecl fcn_00592370(void* fh)
{
	int n;
	int i;

	n = 0;
	if (ls_ReadVfsDataChecked(&n, 4, 1, fh) == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (ls_ReadVfsDataChecked(&g_779d00[i].a, 1, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&g_779d00[i].b, 4, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&g_779d00[i].c, 4, 1, fh) == 0) {
			return 0;
		}
	}
	return 1;
}
