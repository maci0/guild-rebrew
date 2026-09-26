// FUNCTION: GOLDTL 0x004f49e0
// SIZE: 593

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
typedef struct {
	int owner;
	int key;
} Pair;

// SIZE 0x24
typedef struct {
	int v;
	char pad4[0x20];
} Slot;

extern Slot g_68ff80[29];
extern int g_773d38;
extern Order g_9a3800[512];
extern Pair g_99f800[0x800];

int __cdecl fcn_00430910(void *, int, int, int);

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
	if (fcn_00430910(&ver, 4, 1, fp) == 0) {
		return 0;
	}
	for (i = 0; i < 29; i++) {
		if (fcn_00430910(&g_68ff80[i].v, 4, 1, fp) == 0) {
			return 0;
		}
	}
	if (fcn_00430910(&g_773d38, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (g_9a3800[i].id != -1) {
			n1++;
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner != -1 && g_99f800[i].key != -1) {
			n2++;
		}
	}
	if (fcn_00430910(&n1, 4, 1, fp) == -1) {
		return 0;
	}
	if (fcn_00430910(&n2, 4, 1, fp) == -1) {
		return 0;
	}
	for (i = 0; i < 512; i++) {
		if (g_9a3800[i].id != -1) {
			if (fcn_00430910(&g_9a3800[i].id, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(g_9a3800[i].name, 0xe, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].f12, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].target, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].count, 2, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].kind, 1, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].f1d, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].arg, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_9a3800[i].state, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner != -1 && g_99f800[i].key != -1) {
			if (fcn_00430910(&g_99f800[i].owner, 4, 1, fp) == -1) {
				return 0;
			}
			if (fcn_00430910(&g_99f800[i].key, 4, 1, fp) == -1) {
				return 0;
			}
		}
	}
	return 1;
}
