// GLOBAL: GOLDTL 0x7f3b40
extern char g_7f3b40[];
// GLOBAL: GOLD 0x76faa0
extern char g_7f3b40[];
// GLOBAL: GOLDTL 0x7f3b00
extern signed char g_7f3b00[];
// GLOBAL: GOLD 0x76fa60
extern signed char g_7f3b00[];
// FUNCTION: GOLD 0x0050d460
// SIZE: 37
// FUNCTION: GOLDTL 0x510900
// SIZE: 37

char __cdecl fcn_00510900(void)
{
	int i;

	for (i = 0; i < 0xb7; i++) {
		((int*) g_7f3b40)[i] = -1;
	}
	for (i = 0; i < 17; i++) {
		((short*) g_7f3b00)[i] = -1;
	}
	return 0;
}
