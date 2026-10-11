unsigned short* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);

// FUNCTION: GOLD 0x4941d0
// FUNCTION: GOLDTL 0x493800
int __cdecl fcn_00493800(char* p)
{
	unsigned short* a;
	unsigned short* b;
	unsigned short* c;
	float d1;
	float d2;

	a = fcn_00508e40(*(int*) (p + 0x28));
	if (!a) {
		return 1;
	}
	b = fcn_00508e40(*(int*) (p + 0x18));
	c = fcn_00508e40(*(int*) (p + 0x14));
	d1 = fcn_0050f980(*b, *a, 1);
	d2 = fcn_0050f980(*c, *a, 1);
	if (d1 - d2 > 20.0f) {
		return 1;
	}
	if (d2 - d1 > 20.0f) {
		return 0;
	}
	return gm_RandomMod(2);
}
