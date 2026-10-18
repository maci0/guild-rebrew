


extern unsigned char* g_868050;
extern int g_7747b4;
extern float g_6628a8;

float __cdecl fcn_0050b8d0(unsigned char* p, int k, int a, int b)
{
	float r;
	unsigned char* t;

	r = g_6628a8;
	t = g_868050 + k * 0x24d;
	if (a != -1) {
		r = (float) (t[0x229 + a] * 896);
	} else if (b != -1) {
		r = (float) (t[0x233 + b] * 896);
	}
	if (p[2] == 6 || p[2] == 7) {
		r = (float)(r * (1.0 - (2 - g_7747b4) * 0.25));
	}
	return r;
}
