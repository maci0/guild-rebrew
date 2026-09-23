// GLOBAL: GOLDTL 0x100f1dc
extern char g_100f1dc[];
// GLOBAL: GOLD 0xf8a668
extern char g_100f1dc[];
// FUNCTION: GOLD 0x0052f370
// SIZE: 30
// FUNCTION: GOLDTL 0x534c20
// SIZE: 30

void __cdecl fcn_00535550(void);
void __cdecl fcn_00535560(void);

void __cdecl fcn_00534c20(void)
{
	int v;

	v = *(int*) g_100f1dc;
	if (v == 0x767) {
		fcn_00535550();
	} else if (v == 0x768) {
		fcn_00535560();
	}
}
