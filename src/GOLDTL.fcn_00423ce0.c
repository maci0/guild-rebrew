// FUNCTION: GOLDTL 0x423ce0
// SIZE: 64

void* __cdecl fcn_00423ac0(int);
int __cdecl fcn_00424700(int);

int __cdecl fcn_00423ce0(int a1)
{
	int* p;
	int r;

	r = 0;
	p = (int*) fcn_00423ac0(a1);
	if (p != 0) {
		r = p[0xd] + fcn_00424700(a1) * 12;
	}
	return r;
}
