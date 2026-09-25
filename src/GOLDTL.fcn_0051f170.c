// FUNCTION: GOLDTL 0x0051f170
// SIZE: 772

// SIZE 0xac
typedef struct {
	short f00;
	char f02[0x10];
	char pad12[2];
	int f14;
	char pad18[4];
	int f1c;
	int f20;
	char pad24[4];
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	int f48;
	int f4c;
	int f50;
	int f54;
	int f58;
	int f5c;
	int f60;
	int f64;
	int f68;
	int f6c;
	int f70;
	char f74[0x11];
	char pad85[3];
	int f88;
	char f8c[0x10];
	char f9c[0xc];
	int fa8;
} Entry;

extern Entry g_85a0a0[16];
extern int g_6a23ac;

unsigned int __cdecl fcn_00430910(void*, int, int, void*);

int __cdecl fcn_0051f170(void* f)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (fcn_00430910(&g_85a0a0[i].f00, 2, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(g_85a0a0[i].f02, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f14, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f28, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f1c, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f20, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f2c, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f30, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f34, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f38, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f40, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f44, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f48, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f4c, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f50, 4, 1, f) <= 0) {
			return 0;
		}
		if (g_6a23ac >= 0x10014) {
			if (fcn_00430910(&g_85a0a0[i].f54, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f58, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f5c, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f3c, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f64, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f68, 4, 1, f) <= 0) {
				return 0;
			}
			if (fcn_00430910(&g_85a0a0[i].f6c, 4, 1, f) <= 0) {
				return 0;
			}
		}
		if (fcn_00430910(&g_85a0a0[i].f60, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(g_85a0a0[i].f74, 0x11, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f88, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(g_85a0a0[i].f8c, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(g_85a0a0[i].f9c, 0xc, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].fa8, 4, 1, f) <= 0) {
			return 0;
		}
		if (fcn_00430910(&g_85a0a0[i].f70, 4, 1, f) <= 0) {
			return 0;
		}
	}
	return 1;
}
