// GLOBAL: GOLDTL 0x6b6008
extern unsigned char g_6b6008[3][0x100];
// GLOBAL: GOLD 0x631428
extern unsigned char g_6b6008[3][0x100];
// GLOBAL: GOLDTL 0x6b6108
extern char g_6b6108[];
// GLOBAL: GOLD 0x631528
extern char g_6b6108[];
// GLOBAL: GOLDTL 0x6b6208
extern char g_6b6208[];
// GLOBAL: GOLD 0x631628
extern char g_6b6208[];
// FUNCTION: GOLD 0x00420780
// SIZE: 64
// FUNCTION: GOLDTL 0x41bd80
// SIZE: 64

void __cdecl fcn_0041bd80(char* p)
{
	int i;

	for (i = 0; i < 0x100; i++) {
		p[i] = *(char*) ((char*) g_6b6008 + i);
		p[i + 0x100] = *(char*) (g_6b6108 + i);
		p[i + 0x200] = *(char*) (g_6b6208 + i);
	}
}
