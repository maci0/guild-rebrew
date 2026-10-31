

typedef struct I41f2b0 I41f2b0;
// SIZE 0x4
struct I41f2b0 {
	int (__stdcall** vt)(I41f2b0*, int*);
};

char* __cdecl FindVideoById(int);

int __cdecl fcn_0041f2b0(int a1)
{
	char* p;
	I41f2b0* o;

	p = FindVideoById(a1);
	if (p != 0) {
		o = *(I41f2b0**) (p + 0x130);
		if (o->vt[0x8c / 4](o, &a1) >= 0 && a1 == 0) {
			return 1;
		}
	}
	return 0;
}
