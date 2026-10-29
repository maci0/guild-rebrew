extern float g_773d50;
extern float g_773d50;
extern char g_6640c0[];
extern char g_6640c0[];

/* ADDRESS: GOLD 0x0047dcf0 */
/* ADDRESS: GOLDTL 0x0047d1b0 */
int __cdecl fcn_0047d1b0(void)
{
	int v;

	v = (int) (*(float*) ((char*)&g_773d50) * *(double*) g_6640c0);
	if (v < 5) {
		return 5;
	}
	if (v > 0x10) {
		return 0x10;
	}
	return v;
}
