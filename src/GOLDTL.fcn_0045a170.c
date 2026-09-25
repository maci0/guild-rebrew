extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl fcn_00459be0(int a);
int __cdecl fcn_00459d00(char* p, int b);

// FUNCTION: GOLDTL 0x45a170
// SIZE: 71
int __cdecl fcn_0045a170(void)
{
	int n;
	unsigned int i;
	char* p;

	n = 0;
	fcn_00459be0(0x14);
	p = g_104049c;
	for (i = 0; i < g_10404a0; i++, p += 0x70) {
		if (*(int*) (p + 0x40) > 0) {
			n += fcn_00459d00(p, 0);
		}
	}
	return n;
}
