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

extern char* g_1007cd4;

unsigned short __cdecl gm_RandomMod(short);


/* ADDRESS: GOLDTL 0x004a8810 */
void __cdecl fcn_004a8810(void)
{
	if (((fcn_004a8810_game*)g_1007cd4)->fb0 != 0) {
		if (((fcn_004a8810_game*)g_1007cd4)->e[((fcn_004a8810_game*)g_1007cd4)->fb0].f24 != 0)
			((fcn_004a8810_game*)g_1007cd4)->fac = gm_RandomMod((short) ((fcn_004a8810_game*)g_1007cd4)->fa8 - (short) ((fcn_004a8810_game*)g_1007cd4)->fa4) + ((fcn_004a8810_game*)g_1007cd4)->fa4;
		else
			((fcn_004a8810_game*)g_1007cd4)->fac = gm_RandomMod((short) ((((fcn_004a8810_game*)g_1007cd4)->fa8 - ((fcn_004a8810_game*)g_1007cd4)->fa4) >> 1)) + ((fcn_004a8810_game*)g_1007cd4)->fa4;
	}
}
