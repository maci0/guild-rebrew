// GLOBAL: GOLDTL 0x6b7e98
extern char g_6b7e98[];
// GLOBAL: GOLD 0x6332b8
extern char g_6b7e98[];
// GLOBAL: GOLDTL 0x6761a4
extern char g_6761a4[];
// GLOBAL: GOLD 0x5f2124
extern char g_6761a4[];
// FUNCTION: GOLD 0x0040cba0
// SIZE: 64
// FUNCTION: GOLDTL 0x40dad0
// SIZE: 55

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040dad0(int** pp)
{
	void* g;

	if (*pp == 0) {
		g = *(void**) g_6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), (void*) g_6761a4);
		return 0;
	}
	return *((int*) *pp + 0x128 / 4) == 0;
}
