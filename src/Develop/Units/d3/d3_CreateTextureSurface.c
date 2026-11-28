extern int g_67bd2c;

int __cdecl d3_CreateDeviceTexture(int size, int a2, int a3, void** out, unsigned char levels);

/* ADDRESS: GOLDTL 0x0045bda0 */
/* ADDRESS: GOLDDE 0x00450e60 */
void __cdecl d3_CreateTextureSurface(char* obj, int b, int c)
{
	unsigned char levels;

	levels = (obj[0x54] & 4) ? 0 : g_67bd2c;
	*(int*) (obj + 0x60) = b;
	d3_CreateDeviceTexture(*(int*) (obj + 0x64), b, c, (void**) (obj + 0x50), levels);
}
