// GLOBAL: GOLDTL 0x6623b0
extern void (__stdcall* g_6623b0)(int, int);
// GLOBAL: GOLD 0x5eb320
extern void (__stdcall* g_6623b0)(int, int);
// FUNCTION: GOLD 0x0042b780
// SIZE: 55
// FUNCTION: GOLDTL 0x42a0e0
// SIZE: 55

int __cdecl fcn_0042b120(int);

int __cdecl fcn_0042a0e0(int* a1, int a2)
{
	int r = 0;

	if (fcn_0042b120((int) a1) >= 0 && a2 >= 0 && a2 <= 0x7f) {
		g_6623b0(*a1, a2);
	} else {
		r = -1;
	}
	return r;
}
