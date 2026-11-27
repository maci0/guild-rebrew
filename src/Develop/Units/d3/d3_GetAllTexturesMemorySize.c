extern char* g_104049c;
extern unsigned int g_10404a0;

void __cdecl d3_ResetMemoryCountFlags(int a);
int __cdecl d3_GetTextureMemorySize(char* p, int b);

/* ADDRESS: GOLDTL 0x0045a170 */
int __cdecl d3_GetAllTexturesMemorySize(void)
{
	int n;
	unsigned int i;
	char* p;

	n = 0;
	d3_ResetMemoryCountFlags(0x14);
	p = g_104049c;
	for (i = 0; i < g_10404a0; i++, p += 0x70) {
		if (*(int*) (p + 0x40) > 0) {
			n += d3_GetTextureMemorySize(p, 0);
		}
	}
	return n;
}
