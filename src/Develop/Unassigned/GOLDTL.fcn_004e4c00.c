


extern int g_772f3c;
extern int g_772f64;
extern int g_772f68;
extern int g_6b89c0;

void __cdecl fcn_004597f0(int, int);
void __cdecl fcn_00459b40(int);

void __cdecl fcn_004e4c00(void)
{
	if (g_772f3c == 0) {
		if (g_772f64 != 0) {
			fcn_004597f0(g_772f68, g_772f64);
		}
		fcn_00459b40(g_772f68);
		g_6b89c0 = 0;
	}
}
