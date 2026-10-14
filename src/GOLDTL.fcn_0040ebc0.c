


extern char* g_6b7e98;
void __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040ebc0(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *(float*) (*a + 0x4c), *(float*) (*a + 0x50), *(float*) (*a + 0x54),
			     *x * 0.017453292f + *(float*) (*a + 0x84),
			     *y * 0.017453292f + *(float*) (*a + 0x88),
			     *z * 0.017453292f + *(float*) (*a + 0x8c), *w, 0);
		return 1;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 1;
}
