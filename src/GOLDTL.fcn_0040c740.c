extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f1b3c
extern char g_675bbc[];
// FUNCTION: GOLD 0x0040b820
// FUNCTION: GOLDTL 0x40c740

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040c740(int** pp, int** pp2)
{
	void* g;

	if (*pp == 0) {
		g = g_6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), g_675bbc);
		return 0;
	}
	((int (__cdecl*) (int)) * pp)(*pp2);
	return 1;
}
