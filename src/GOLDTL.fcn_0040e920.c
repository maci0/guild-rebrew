extern char* g_6b7e98;
// GLOBAL: GOLDTL 0x6766f0
extern char g_6766f0[];
// FUNCTION: GOLDTL 0x40e920
// SIZE: 64

void __cdecl fcn_00442be0(void*);
void __cdecl fcn_00425bf0(int*, int, char*);

int __cdecl fcn_0040e920(void* a1)
{
	void* p;

	p = *(void**) a1;
	if (p != 0) {
		fcn_00442be0(p);
		return 1;
	}
	fcn_00425bf0(((int*)g_6b7e98), *(int*) ((char*) ((int*)g_6b7e98) + 0x118), g_6766f0);
	return 1;
}
