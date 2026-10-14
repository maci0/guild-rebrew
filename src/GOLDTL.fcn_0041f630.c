

typedef struct I41f630 I41f630;
// SIZE 0x4
struct I41f630 {
	int (__stdcall** vt)(I41f630*, int);
};

char* __cdecl fcn_0041f9b0(int);

int __cdecl fcn_0041f630(int a1, int a2)
{
	char* p;
	I41f630* o;

	p = fcn_0041f9b0(a1);
	if (p != 0) {
		o = *(I41f630**) (p + 0x130);
		return o->vt[0x4c / 4](o, a2 ? -1 : 0) >= 0;
	}
	return 0;
}
