extern int g_6a25b4;
extern int g_6a25b8;

// FUNCTION: GOLD 0x525480
// FUNCTION: GOLDTL 0x52a2d0

void __cdecl fcn_00471e30(int);
void __cdecl fcn_004737c0(void);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_0052f7b0(void);

void __cdecl fcn_0052a2d0(void)
{
	fcn_00471e30(g_6a25b4);
	g_6a25b4 = -1;
	fcn_004737c0();
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, 1);
	}
	fcn_0052f7b0();
}
