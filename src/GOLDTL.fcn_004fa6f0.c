// FUNCTION: GOLD 0x004f8300
// FUNCTION: GOLDTL 0x4fa6f0

extern char g_1043370[];

char __cdecl fcn_0045b990(char*, int, int*, int*, int*);

int __cdecl fcn_004fa6f0(int a1, int* a2, int* a3)
{
	char* g;
	int div;
	int tmp;

	g = (*(char**)g_1043370);
	div = *(int*) (g + 0x20) / 8;
	if (fcn_0045b990(g, a1, a2, a3, &tmp) != 0) {
		*a2 /= div;
		*a3 /= div;
		return 1;
	}
	return 0;
}
