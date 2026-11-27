extern int g_67bd2c;

int __cdecl fcn_00437110(int size, int a2, int a3, void** out, unsigned char levels);

/* ADDRESS: GOLDTL 0x0045bda0 */
void __cdecl d3_CreateTextureSurface(char* obj, int b, int c)
{
	unsigned char levels;

	levels = (obj[0x54] & 4) ? 0 : g_67bd2c;
	*(int*) (obj + 0x60) = b;
	fcn_00437110(*(int*) (obj + 0x64), b, c, (void**) (obj + 0x50), levels);
}
