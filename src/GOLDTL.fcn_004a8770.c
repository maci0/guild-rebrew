// SIZE 0xb0
typedef struct {
	char pad0[0x4];
	int* f4;
	char pad8[0x98];
	int fa0;
	char pada4[0x8];
	int fac;
} fcn_004a8770_game;

extern char* g_1007cd4;
extern unsigned char g_773d75;

void __cdecl fcn_004c51a0(int, int, char, int);

/* ADDRESS: GOLDTL 0x004a8770 */

void __cdecl fcn_004a8770(void)
{
	((fcn_004a8770_game*)g_1007cd4)->fa0 = ((fcn_004a8770_game*)g_1007cd4)->fac * 3;
	fcn_004c51a0(-1, ((fcn_004a8770_game*)g_1007cd4)->f4[1], (*(char*)&g_773d75), ((fcn_004a8770_game*)g_1007cd4)->fac);
}
