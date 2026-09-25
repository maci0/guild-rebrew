typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x8];
	int fac;
} fcn_004a8770_game;

extern fcn_004a8770_game* g_1007cd4;
extern char g_773d75;

void __cdecl fcn_004c51a0(int, int, char, int);

// FUNCTION: GOLDTL 0x4a8770
// SIZE: 58

void __cdecl fcn_004a8770(void)
{
	g_1007cd4->fa0 = g_1007cd4->fac * 3;
	fcn_004c51a0(-1, g_1007cd4->f4[1], g_773d75, g_1007cd4->fac);
}
