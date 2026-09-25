extern float g_10529d8;
extern float g_10529c4;
extern float g_10529d4;
extern float g_1043288;
extern float g_67d368;
extern int g_1015eac;
extern int g_1015ea8;
extern int g_1040490;
extern int g_1040494;

// FUNCTION: GOLDTL 0x537320
// SIZE: 144

void __cdecl fcn_00537320(int flags)
{
	if (flags & 0x40) {
		if (flags & 0x100) {
			g_1015eac = (int) (g_10529d8 * 0.5f + g_10529c4 - g_67d368 * 6.0f);
			g_1015ea8 = (int) (g_10529d4 * 0.5f + g_67d368 * 10.0f + g_1043288);
		} else {
			g_1015eac = (int) (g_10529d8 * 0.5f + g_10529c4);
			g_1015ea8 = (int) (g_10529d4 * 0.5f + g_1043288);
		}
	} else {
		g_1015eac = g_1040494 >> 1;
		g_1015ea8 = g_1040490 >> 1;
	}
}
