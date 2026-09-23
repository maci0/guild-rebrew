// FUNCTION: GOLDTL 0x45f790
// SIZE: 49

int __cdecl fcn_0045f7d0(void*, int);
int __cdecl fcn_0064f938(int);

int __cdecl fcn_0045f790(void* a1, int a2)
{
	int r;
	int v;

	r = fcn_0045f7d0(a1, a2);
	if (r != 0) {
		return r;
	}
	fcn_0064f938(*(int*) ((char*) a1 + 0x40));
	v = *(int*) ((char*) a1 + 0x38);
	return v == 1 ? 0 : v;
}
