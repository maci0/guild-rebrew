// FUNCTION: GOLDTL 0x0040e9c0
// SIZE: 128

extern char* g_6b7e98;
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040e9c0(char** a, float* x, float* y, float* z)
{
	if (*a != 0) {
		*(float*) (*a + 0x84) = *x * 0.017453292f;
		*(float*) (*a + 0x88) = *y * 0.017453292f;
		*(float*) (*a + 0x8c) = *z * 0.017453292f;
		*(unsigned char*) (*a + 0x214) |= 4;
		return 0;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 0;
}
