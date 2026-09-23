// FUNCTION: GOLDTL 0x402340
// SIZE: 37

extern int (__stdcall *g_662350)(int, int, int, int, int, int);

void __cdecl fcn_00402340(int a1, int a2)
{
	int h;

	h = *(int*) 0x675170;
	if (h != -1) {
		g_662350(h, a1, a2, 0, 0x1552000, 0x10);
	}
}
