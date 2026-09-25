// FUNCTION: GOLD 0x0040dc30
// SIZE: 128
// FUNCTION: GOLDTL 0x0040eb40
// SIZE: 128

extern char* g_6b7e98;
void __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040eb40(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *x + *(float*) (*a + 0x4c), *y + *(float*) (*a + 0x50),
			     *z + *(float*) (*a + 0x54), *(float*) (*a + 0x84), *(float*) (*a + 0x88),
			     *(float*) (*a + 0x8c), *w, 0);
		return 0;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 0;
}
