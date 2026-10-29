extern int g_67bd2c;

int __cdecl fcn_00437110(int size, int a2, int a3, void** out, unsigned char levels);

/* ADDRESS: GOLDTL 0x0045bda0 */
void __cdecl fcn_0045bda0(char* a, int b, int c)
{
	unsigned char m;

	m = (a[0x54] & 4) ? 0 : g_67bd2c;
	*(int*) (a + 0x60) = b;
	fcn_00437110(*(int*) (a + 0x64), b, c, (void**) (a + 0x50), m);
}
