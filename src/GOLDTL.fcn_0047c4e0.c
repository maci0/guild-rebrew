typedef struct fcn_0047c4e0_dev fcn_0047c4e0_dev;
typedef struct {
	char pad0[0x130];
	int(__stdcall* f130)(fcn_0047c4e0_dev*, int);
	char pad134[0x18];
	int(__stdcall* f14c)(fcn_0047c4e0_dev*, int, int, int);
} fcn_0047c4e0_vtbl;
// SIZE 0x150
struct fcn_0047c4e0_dev {
	fcn_0047c4e0_vtbl* vtbl;
};

extern int g_772618;
extern int g_772614;
extern void* g_6b5de0;

// FUNCTION: GOLDTL 0x47c4e0
// SIZE: 64

void __cdecl fcn_0047c4e0(void)
{
	if (g_772618 == 0) {
		((fcn_0047c4e0_dev*)g_6b5de0)->vtbl->f14c(((fcn_0047c4e0_dev*)g_6b5de0), 0, g_772614, 0x1c);
		((fcn_0047c4e0_dev*)g_6b5de0)->vtbl->f130(((fcn_0047c4e0_dev*)g_6b5de0), 0x144);
		g_772618 = 1;
	}
}
