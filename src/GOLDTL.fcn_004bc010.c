typedef struct {
	int used;
	char pad4[0x1c];
	int f20;
	char pad24[0x100];
} fcn_004bc010_slot;
// SIZE 0x124

extern fcn_004bc010_slot* g_7728e8;
extern int g_7728e4;
extern int g_6b7fac;

// FUNCTION: GOLD 0x004bbb00
// SIZE: 79
// FUNCTION: GOLDTL 0x4bc010
// SIZE: 79

fcn_004bc010_slot* __cdecl fcn_004bc010(void)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (g_7728e8[i].used == 0)
			break;
	}
	if (i == 32)
		return 0;
	g_7728e4++;
	g_7728e8[i].f20 = g_6b7fac;
	return &g_7728e8[i];
}
