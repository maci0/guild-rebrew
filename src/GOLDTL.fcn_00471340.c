extern char g_1038140[];

void __cdecl fcn_004767f0(int a, int b, int c, int d, int e, int f, int g, int h);

// FUNCTION: GOLDTL 0x471340
// SIZE: 98
void __cdecl fcn_00471340(int k)
{
	char* base;
	char** pp;
	int j;

	base = g_1038140 + k * 0x2bc;
	pp = (char**) (base + 0x1ac);
	for (j = 2; j != 0; j--) {
		fcn_004767f0(0, 0, *(int*) (*pp + 4), *(int*) (*pp + 8), *(int*) (*pp + 0x20), 0, 0, *(int*) ((char*) pp - 8));
		pp++;
	}
	base[0x1b4] = 0;
	base[0x1f4] = 0;
}
