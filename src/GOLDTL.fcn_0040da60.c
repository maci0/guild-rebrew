extern char* g_6b7e98;
/* ADDRESS: GOLD 0x005f20fc */
extern char g_67617c[];



void __cdecl fcn_00404a00(void*, int, int, int, int, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040da60(void** a1, int* a2, int* a3, int* a4, int* a5)
{
	void* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_67617c);
		return 1;
	}
	fcn_00404a00(p, 4, *a2, *a3, *a4, *a5);
	return 0;
}
