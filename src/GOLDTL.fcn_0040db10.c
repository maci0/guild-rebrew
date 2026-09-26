extern char* g_6b7e98;
// GLOBAL: GOLDTL 0x6761c8
extern char g_6761c8[];
// FUNCTION: GOLD 0x0040cbe0
// SIZE: 64
// FUNCTION: GOLDTL 0x40db10
// SIZE: 64

void __cdecl fcn_00425bf0(int*, int, char*);
void __cdecl fcn_00406120(void*);

int __cdecl fcn_0040db10(void* a1)
{
	void* p;

	p = *(void**) a1;
	if (p == 0) {
		fcn_00425bf0(((int*)g_6b7e98), *(int*) ((char*) ((int*)g_6b7e98) + 0x118), g_6761c8);
	} else {
		fcn_00406120(p);
	}
	return 0;
}
