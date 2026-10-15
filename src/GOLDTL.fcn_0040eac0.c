


extern char* g_6b7e98;
int __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

char** __cdecl fcn_0040eac0(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *(float*) (*a + 0x4c), *(float*) (*a + 0x50), *(float*) (*a + 0x54),
			     *x * 0.017453292f, *y * 0.017453292f, *z * 0.017453292f, *w, 0);
		return a;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return a;
}
