typedef int(__stdcall* Fn1)(void* self);

extern void* g_6b5de0;
extern int g_14ce728;

int __stdcall fcn_00610011(void* dev, int a, int b, int c, int d, int e, int f, void** out);

// FUNCTION: GOLDTL 0x437110
// SIZE: 78
int __cdecl fcn_00437110(int size, int a2, int a3, void** out, unsigned char levels)
{
	if (*out != 0) {
		g_14ce728 = ((Fn1) (*(void***) *out)[2])(*out);
		*out = 0;
	}
	return fcn_00610011(g_6b5de0, size, size, levels + 1, a3, a2, ~a3 & 1, out);
}
