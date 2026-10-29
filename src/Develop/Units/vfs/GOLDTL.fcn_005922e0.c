


// SIZE 0xc
#include "client_types.h"
typedef Slot_779d00 Slot;

extern Slot_779d00 g_779d00[];

unsigned int __cdecl vfs_fwrite(void*, int, int, int);

int __cdecl fcn_005922e0(int fh)
{
	int n;
	int i;

	n = 0xb;
	if (vfs_fwrite(&n, 4, 1, fh) <= 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (vfs_fwrite(&g_779d00[i].a, 1, 1, fh) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_779d00[i].b, 4, 1, fh) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_779d00[i].c, 4, 1, fh) <= 0) {
			return 0;
		}
	}
	return 1;
}
