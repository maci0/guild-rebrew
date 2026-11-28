


// SIZE 0xc
#include "Develop/client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 main_CameraBookmarks[];

#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

int __cdecl ls_LoadSlot779d00(void* fh)
{
	int n;
	int i;

	n = 0;
	if (ls_ReadVfsDataChecked(&n, 4, 1, fh) == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (ls_ReadVfsDataChecked(&main_CameraBookmarks[i].a, 1, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&main_CameraBookmarks[i].b, 4, 1, fh) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&main_CameraBookmarks[i].c, 4, 1, fh) == 0) {
			return 0;
		}
	}
	return 1;
}
