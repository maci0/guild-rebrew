extern int g_774934;
extern float g_681750;

int* __cdecl fcn_004c2de0(int, int, int, int);
int __cdecl fcn_00423890(int*, int);
void __cdecl fcn_004c0a80(int*, int);

// FUNCTION: GOLD 0x004c27d0
// SIZE: 89
// FUNCTION: GOLDTL 0x4c30a0
// SIZE: 89

int* __cdecl fcn_004c30a0(int a, int b, int c, int d, int e)
{
	int* p;

	if (g_774934 == 0)
		return 0;
	p = fcn_004c2de0(a, b, c, d);
	if (p != 0) {
		fcn_00423890(p, (int) (g_681750 * 127.0f));
		fcn_004c0a80(p, e);
	}
	return p;
}
