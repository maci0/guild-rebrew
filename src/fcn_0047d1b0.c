// GLOBAL: GOLDTL 0x773d50
extern char g_773d50[];
// GLOBAL: GOLD 0x6f1ba0
extern char g_773d50[];
// GLOBAL: GOLDTL 0x6640c0
extern char g_6640c0[];
// GLOBAL: GOLD 0x5ece40
extern char g_6640c0[];
// FUNCTION: GOLD 0x0047dcf0
// SIZE: 48
// FUNCTION: GOLDTL 0x47d1b0
// SIZE: 39

int __cdecl fcn_0047d1b0(void)
{
	int v;

	v = (int) (*(float*) g_773d50 * *(double*) g_6640c0);
	if (v < 5) {
		return 5;
	}
	if (v > 0x10) {
		return 0x10;
	}
	return v;
}
