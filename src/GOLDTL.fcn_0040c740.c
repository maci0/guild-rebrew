// FUNCTION: GOLDTL 0x40c740
// SIZE: 57

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040c740(int** pp, int** pp2)
{
	void* g;

	if (*pp == 0) {
		g = *(void**) 0x6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), (void*) 0x675bbc);
		return 0;
	}
	((int (__cdecl*) (int)) * pp)(*pp2);
	return 1;
}
