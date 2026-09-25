// FUNCTION: GOLD 0x004ef260
// SIZE: 194
// FUNCTION: GOLDTL 0x004f11c0
// SIZE: 194

extern float g_6652d4;
extern float g_6652c8;
extern float g_6652d0;
extern float g_662960;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);

void __cdecl fcn_004f11c0(char* p, float* o1, float* o2)
{
	float x;
	float y;

	x = 0.02f;
	y = 0.2f;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x25c)) {
		x = 0.02f - 0.003f;
		y = 0.17f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x25f)) {
		x -= g_6652d4;
		y -= g_6652c8;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x260)) {
		x -= g_6652d0;
		y -= g_662960;
	}
	*o1 = x;
	*o2 = y;
}
