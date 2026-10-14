/* ADDRESS: GOLDTL 0x014b52fc */
extern int g_14b52fc;



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
