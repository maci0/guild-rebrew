// FUNCTION: GOLD 0x004f2660
// SIZE: 189
// FUNCTION: GOLDTL 0x004f4770
// SIZE: 189

extern float g_665370;
extern float g_6628cc;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);

float __cdecl fcn_004f4770(char* p)
{
	float v;

	v = 0.0f;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x20f)) {
		v = 30.0f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x21f)) {
		v = v + 10.0f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x222)) {
		v = v + 15.0f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x223)) {
		v = v + 25.0f;
	}
	return v * 0.0125f * g_6628cc + 0.5f;
}
