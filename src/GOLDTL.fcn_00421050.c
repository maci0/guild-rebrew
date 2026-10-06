// GLOBAL: GOLD 0x1460ae0
extern int g_14cbca0;
// GLOBAL: GOLD 0x1460af0
extern int g_14cbcb0;
// GLOBAL: GOLD 0x633160
extern int g_6b7d40;
// GLOBAL: GOLD 0x5eb2c8
extern void (__stdcall *g_662374)(int, int);
// GLOBAL: GOLD 0x5eb2b0
extern void (__stdcall *g_66234c)(int);
// GLOBAL: GOLD 0x5eb2b8
extern void (__stdcall *g_662360)(void);
// FUNCTION: GOLD 0x00424c30
// FUNCTION: GOLDTL 0x421050

void __cdecl fcn_00421050(void)
{
	if (g_14cbca0 != -1) {
		g_662374(g_14cbca0, 2);
		g_66234c(g_14cbca0);
		g_14cbca0 = -1;
		g_14cbcb0 = 1;
	}
	g_662360();
	g_6b7d40 = 0;
}
