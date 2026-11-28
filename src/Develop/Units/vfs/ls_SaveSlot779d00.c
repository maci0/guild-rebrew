


// SIZE 0xc
#include "Develop/client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 main_CameraBookmarks[];

unsigned int __cdecl vfs_fwrite(void*, int, int, int);

/* ADDRESS: GOLDDE 0x00577f90 */
int __cdecl ls_SaveSlot779d00(int fh)
{
	int n;
	int i;

	n = 0xb;
	if (vfs_fwrite(&n, 4, 1, fh) <= 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (vfs_fwrite(&main_CameraBookmarks[i].a, 1, 1, fh) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&main_CameraBookmarks[i].b, 4, 1, fh) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&main_CameraBookmarks[i].c, 4, 1, fh) <= 0) {
			return 0;
		}
	}
	return 1;
}
