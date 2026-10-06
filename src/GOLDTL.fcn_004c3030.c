// FUNCTION: GOLD 0x004c2760
// FUNCTION: GOLDTL 0x4c3030

extern int g_774934;
extern char* g_772d34;
extern float g_681750;
extern float g_664e80;

int __cdecl fcn_004c2de0(int, int, int, int);
void __cdecl fcn_00423670(int, int, int);
void __cdecl fcn_00423890(int, int);

int __cdecl fcn_004c3030(int a, int b, int c, int d)
{
	int h;

	if (g_774934 == 0)
		return 0;
	if (g_772d34 != 0 && *(int*) (g_772d34 + 8) != 0)
		return 0;
	h = fcn_004c2de0(a, b, c, d);
	if (h != 0) {
		fcn_00423670(h, 0, 0);
		fcn_00423890(h, (int) (g_681750 * g_664e80));
	}
	return h;
}
