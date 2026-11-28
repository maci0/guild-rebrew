extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

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
	p = d3_TextureBank;
	for (i = 0; i < d3_TextureBankCount; i++, p += 0x70) {
		if (*(int*) (p + 0x40) > 0) {
			n += d3_GetTextureMemorySize(p, 0);
		}
	}
	return n;
}
