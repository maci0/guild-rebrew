// FUNCTION: GOLDTL 0x4b4ad0
// SIZE: 154

typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float g_6628a0;

void __cdecl fcn_004b53c0(int, int, stat12*);

int __cdecl fcn_004b4ad0(int a1)
{
	stat12 s;

	fcn_004b53c0(a1, 0x13, &s);
	if (s.f < g_6628a0)
		return 0;
	fcn_004b53c0(a1, 4, &s);
	if (s.n > 0 && s.f < g_6628a0)
		return 0;
	fcn_004b53c0(a1, 0x10, &s);
	if (s.n > 0 && s.f < g_6628a0)
		return 0;
	return 1;
}
