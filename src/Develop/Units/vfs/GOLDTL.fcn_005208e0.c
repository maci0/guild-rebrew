unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

#include "client_types.h"

extern Sample_99ec20 g_99ec20[16];
extern Cell_99ef80 g_99ef80[9][8];

/* ADDRESS: GOLDTL 0x005208e0 */
int __cdecl fcn_005208e0(char* fp)
{
	int i;
	int r;

	if (vfs_fwrite((void*) 0x99f5e0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5e4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5e8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5ec, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5f8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5fc, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f600, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f604, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99ec14, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f590, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f594, 2, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f596, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f59a, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x773d4c, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x773d50, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5a8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5ac, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b0, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5b8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5bc, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f5c0, 4, 1, fp) <= 0) {
		return 0;
	}
	for (i = 0; i < 16; i++) {
		if (vfs_fwrite(&g_99ec20[i].a, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].b, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].c, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].d, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].e, 4, 1, fp) <= 0) {
			return 0;
		}
	}
	if (vfs_fwrite((void*) 0x99f6a0, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f6e4, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f728, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f76c, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) 0x99f7b0, 0x44, 1, fp) <= 0) {
		return 0;
	}
	for (r = 0; r < 8; r++) {
		for (i = 0; i < 8; i++) {
			if (vfs_fwrite(&g_99ef80[r][i].demand, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&g_99ef80[r][i].supply, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&g_99ef80[r][i].pad4[0], 1, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&g_99ef80[r][i].pad4[4], 4, 1, fp) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}
