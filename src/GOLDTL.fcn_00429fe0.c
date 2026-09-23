// GLOBAL: GOLDTL 0x6791d0
extern int g_6791d0;
// FUNCTION: GOLDTL 0x429fe0
// SIZE: 64

void* __cdecl fcn_00426fd0(int);
void __cdecl fcn_00428230(void*);

int __cdecl fcn_00429fe0(int a1, int a2, int a3)
{
	int v;
	void* p;

	p = fcn_00426fd0(a3);
	if (p != 0) {
		fcn_00428230(p);
		v = *(int*) ((char*) p + 0x100);
		g_6791d0 = v;
		return v;
	}
	g_6791d0 = -1;
	return -1;
}
