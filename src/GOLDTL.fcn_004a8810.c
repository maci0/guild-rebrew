typedef struct {
	char pad0[0x24];
	int f24;
	char pad28[0xc];
} fcn_004a8810_entry;
// SIZE 0x34

typedef struct {
	fcn_004a8810_entry e[3];
	char pad9c[0x8];
	int fa4;
	int fa8;
	int fac;
	int fb0;
} fcn_004a8810_game;

extern fcn_004a8810_game* g_1007cd4;

unsigned short __cdecl fcn_0042e410(short);

// FUNCTION: GOLDTL 0x4a8810
// SIZE: 98

void __cdecl fcn_004a8810(void)
{
	if (g_1007cd4->fb0 != 0) {
		if (g_1007cd4->e[g_1007cd4->fb0].f24 != 0)
			g_1007cd4->fac = fcn_0042e410((short) g_1007cd4->fa8 - (short) g_1007cd4->fa4) + g_1007cd4->fa4;
		else
			g_1007cd4->fac = fcn_0042e410((short) ((g_1007cd4->fa8 - g_1007cd4->fa4) >> 1)) + g_1007cd4->fa4;
	}
}
