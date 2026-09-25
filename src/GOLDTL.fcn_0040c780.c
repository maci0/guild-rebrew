extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f1b68
extern char g_675be8[];
// FUNCTION: GOLD 0x0040b860
// SIZE: 64
// FUNCTION: GOLDTL 0x40c780
// SIZE: 64

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040c780(int** pp, int** pp2, int** pp3)
{
	void* g;

	if (*pp == 0) {
		g = g_6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), g_675be8);
		return 0;
	}
	((int (__cdecl*) (int, int)) * pp)(*pp2, *pp3);
	return 1;
}
