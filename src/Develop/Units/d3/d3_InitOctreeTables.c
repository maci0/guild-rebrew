extern unsigned short g_6b6d20[256];
extern unsigned short g_6b5e08[256];
extern unsigned short g_6b6b18[256];
extern int g_6b6714[];
extern unsigned int* g_6b6d18;

/* ADDRESS: GOLDTL 0x0041bdc0 */
/* ADDRESS: GOLDDE 0x00419a60 */
void __cdecl d3_InitOctreeTables(void)
{
	int i;

	for (i = 0; i < 0x100; i++) {
		g_6b6d20[i] = (unsigned short) ((((((((i & 0x80) << 2) | (i & 0x40)) << 2) | (i & 0x20)) * 4 | (i & 0x10)) * 2) | ((i >> 1) & 4));
		g_6b5e08[i] = (unsigned short) (((i >> 2) & 2) | (((((i & 0x80) << 2) | (i & 0x40)) << 2) | (i & 0x20)) * 4 | (i & 0x10));
		g_6b6b18[i] = (unsigned short) (((i >> 3) & 1) | (((((i & 0x80) << 2) | (i & 0x40)) << 2) | (i & 0x20)) * 2 | ((i >> 1) & 8));
	}
	for (i = -0xff; i <= 0xff; i++) {
		g_6b6714[i] = i * i;
	}
	(*(int * *)&g_6b6d18) = g_6b6714;
}
