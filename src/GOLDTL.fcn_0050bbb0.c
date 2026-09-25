extern float g_6628a0;
extern float g_665368;
extern double g_665be8;
extern double g_6629c8;
// FUNCTION: GOLDTL 0x0050bbb0
// SIZE: 82

float __cdecl fcn_0050bbb0(int idx)
{
	char* p;
	float v;

	p = (char*) 0x7f4ca0 + idx * 0x21c;
	if (p == 0) {
		return g_6628a0;
	}
	v = *(unsigned char*) (p + 0x80);
	if (v <= g_665368) {
		return g_6628a0;
	}
	return (float) (v * g_665be8 + g_6629c8);
}
