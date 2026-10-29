


#include "g_774a78.h"

extern struct Node* g_774a78;

int __cdecl vfs_fwrite(void*, int, int, int);

/* ADDRESS: GOLD 0x5a8a90 */
int __cdecl fcn_005b1f10(int fh)
{
	int n;
	char* p;
	int i;

	n = 0;
	for (p = (char*) g_774a78; p != 0; n++) {
		p = *(char**) (p + 0x48);
	}
	if (vfs_fwrite(&n, 4, 1, fh) == 0) {
		return 0;
	}
	for (p = (char*) g_774a78; p != 0; p = *(char**) (p + 0x48)) {
		if (vfs_fwrite(p, 4, 1, fh) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 4, 4, 1, fh) == 0) {
			return 0;
		}
		if (vfs_fwrite(p + 0x44, 4, 1, fh) == 0) {
			return 0;
		}
		for (i = 0; i < 7; i++) {
			if (vfs_fwrite(p + 0xc + i * 8, 4, 1, fh) == 0) {
				return 0;
			}
			if (vfs_fwrite(p + 0x10 + i * 8, 1, 1, fh) == 0) {
				return 0;
			}
		}
	}
	return 1;
}
