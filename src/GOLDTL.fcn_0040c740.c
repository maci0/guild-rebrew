extern char* g_6b7e98;
/* ADDRESS: GOLD 0x005f1b3c */
extern char g_675bbc[];



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
