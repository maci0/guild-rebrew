extern float g_699b0c;
extern int g_773de4;
extern int g_7f3e20[];
// FUNCTION: GOLDTL 0x00515f60
// SIZE: 68

int __cdecl fcn_004234e0(int, int, int, int, int, int, int);

void __cdecl fcn_00515f60(int a, int b, int c)
{
	int h;

	h = fcn_004234e0(0, a, 0, 0x3f, (int) (b * g_699b0c), 1, c);
	if (g_773de4 < 0x10) {
		g_7f3e20[g_773de4] = h;
		g_773de4++;
	}
}
