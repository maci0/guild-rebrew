// FUNCTION: GOLD 0x004b4a00
// FUNCTION: GOLDTL 0x4b4b70

typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float g_6628a0;

void __cdecl fcn_004b53c0(int, int, stat12*);

int __cdecl fcn_004b4b70(int a1)
{
	stat12 s;

	fcn_004b53c0(a1, 0x15, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	fcn_004b53c0(a1, 0x14, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	fcn_004b53c0(a1, 0x12, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	return 1;
}
