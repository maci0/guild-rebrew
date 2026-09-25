// GLOBAL: GOLDTL 0x14b52fc
extern int g_14b52fc;
// FUNCTION: GOLD 0x005812a0
// SIZE: 49
// FUNCTION: GOLDTL 0x5898f0
// SIZE: 49

void* __cdecl fcn_00577850(int);
void __cdecl fcn_00526120(int, int);

int __cdecl fcn_005898f0(void* a1)
{
	void* p;

	p = fcn_00577850(*(int*) ((char*) a1 + 1));
	if (p != 0) {
		fcn_00526120(g_14b52fc, 0);
	}
	return p == 0;
}
