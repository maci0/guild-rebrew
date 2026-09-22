// FUNCTION: GOLDTL 0x40c780
// SIZE: 64

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040c780(int** pp, int** pp2, int** pp3)
{
	void* g;

	if (*pp == 0) {
		g = *(void**) 0x6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), (void*) 0x675be8);
		return 0;
	}
	((int (__cdecl*) (int, int)) * pp)(*pp2, *pp3);
	return 1;
}
