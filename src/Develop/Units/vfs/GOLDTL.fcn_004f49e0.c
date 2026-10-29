

#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char name[0xe];
	int f12;
	int target;
	short count;
	unsigned char kind;
	int f1d;
	int arg;
	int state;
	char pad29[4];
} Order;
#pragma pack()

// SIZE 0x8
#include "client_types.h"
typedef Pair_99f800 Pair;

// SIZE 0x24
typedef Slot_68ff80 Slot;

extern Slot_68ff80 g_68ff80[29];
extern int g_773d38;
extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];

int __cdecl vfs_fwrite(void *, int, int, int);

int __cdecl fcn_004f49e0(int fp)
{
	int n1;
	int n2;
	int ver;
	int i;

	ver = 0x1d;
	n1 = 0;
	n2 = 0;
	if (fp == 0) {
		return 0;
	}
	if (vfs_fwrite(&ver, 4, 1, fp) == 0) {
		return 0;
	}
	for (i = 0; i < 29; i++) {
		if (vfs_fwrite(&g_68ff80[i].v, 4, 1, fp) == 0) {
			return 0;
		}
	}
	if (vfs_fwrite(&g_773d38, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (((Order*)g_9a3800)[i].id != -1) {
			n1++;
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner != -1 && g_99f800[i].key != -1) {
			n2++;
		}
	}
	if (vfs_fwrite(&n1, 4, 1, fp) == -1) {
		return 0;
	}
	if (vfs_fwrite(&n2, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (((Order*)g_9a3800)[i].id != -1) {
			if (vfs_fwrite(&((Order*)g_9a3800)[i].id, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(((Order*)g_9a3800)[i].name, 0xe, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].f12, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].target, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].count, 2, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].kind, 1, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].f1d, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].arg, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&((Order*)g_9a3800)[i].state, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner != -1 && g_99f800[i].key != -1) {
			if (vfs_fwrite(&g_99f800[i].owner, 4, 1, fp) == -1) {
				return 0;
			}
			if (vfs_fwrite(&g_99f800[i].key, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	return 1;
}
unsigned char _dpad_99f5e0[544];
