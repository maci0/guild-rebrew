char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);
int __cdecl fcn_004a4550(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

// FUNCTION: GOLDTL 0x4a03d0
// SIZE: 221
// FUNCTION: GOLD 0x004a0990
// SIZE: 224
int __cdecl fcn_004a03d0(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7)
{
	unsigned char c;
	char* g;

	*o1 = -100.0f;
	*o2 = -100.0f;
	c = e[0x169];
	if (c < 0x1e && c > 0x21) {
		return 0;
	}
	if (c == 0x1e) {
		g = gm_StartFilteredEntitySearch(1, 5, 0x17);
	} else if (c == 0x1f) {
		g = gm_StartFilteredEntitySearch(1, 5, 0x18);
	} else if (c == 0x20) {
		g = gm_StartFilteredEntitySearch(1, 5, 0x19);
	} else {
		g = gm_StartFilteredEntitySearch(1, 5, 0x1a);
	}
	if (!g) {
		return 0;
	}
	if (g[0x5c] < fcn_0042e410(0x10) + 0x32) {
		fcn_004a4550(o1, o2, a3, e, a5, a6, a7);
		*o1 = *o1 * 3.0f;
		*o2 = *o2 * 3.0f;
		return 1;
	}
	return fcn_004a4410(o1, o2, a3, e, a5, a6, a7);
}
