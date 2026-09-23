// GLOBAL: GOLDTL 0x14a5c6c
extern int g_14a5c6c[];
// GLOBAL: GOLDTL 0x68d934
extern char g_68d934[];
// FUNCTION: GOLDTL 0x4e75a0
// SIZE: 87

void __cdecl fcn_0064d41a(void*, void*, int, int, int, int);

void __cdecl fcn_004e75a0(void* a1, void* a2)
{
	fcn_0064d41a(a2, g_68d934,
	    g_14a5c6c[*(unsigned char*) ((char*) a1 + 0x166)],
	    g_14a5c6c[*(unsigned char*) ((char*) a1 + 0x167)],
	    g_14a5c6c[*(unsigned char*) ((char*) a1 + 0x168)],
	    g_14a5c6c[*(unsigned char*) ((char*) a1 + 0x169)]);
}
