// FUNCTION: GOLDTL 0x4609c0
// SIZE: 57

typedef void (__cdecl* Fn2)(int, int);
// SIZE 0x4

void __cdecl fcn_0045fc50(void*, void*, int);

int __cdecl fcn_004609c0(void* a1, void* a2)
{
	char* p;

	p = (char*) a2;
	fcn_0045fc50(a1, a2, 0);
	(*(Fn2*) (p + 0x24))(*(int*) (p + 0x28), *(int*) ((char*) a1 + 0x28));
	(*(Fn2*) (p + 0x24))(*(int*) (p + 0x28), *(int*) ((char*) a1 + 0x24));
	(*(Fn2*) (p + 0x24))(*(int*) (p + 0x28), (int) a1);
	return 0;
}
