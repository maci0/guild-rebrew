// FUNCTION: GOLDTL 0x41f2f0

typedef struct I41f2f0 I41f2f0;
// SIZE 0x4
struct I41f2f0 {
	int (__stdcall** vt)(I41f2f0*, int);
};

char* __cdecl fcn_0041f9b0(int);

int __cdecl fcn_0041f2f0(int a1, int a2)
{
	char* p;
	I41f2f0* o;
	int r;

	p = fcn_0041f9b0(a1);
	if (p != 0) {
		o = *(I41f2f0**) (p + 0x130);
		r = o->vt[0x90 / 4](o, a2 ? -1 : 0);
		if (r == 0 || r == 1) {
			return 1;
		}
	}
	return 0;
}
