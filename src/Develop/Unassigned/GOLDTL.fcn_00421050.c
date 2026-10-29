extern int g_14cbca0;
extern int g_14cbcb0;
extern int g_6b7d40;
extern void (__stdcall *g_662374)(int, int);
extern void (__stdcall *g_66234c)(int);
extern void (__stdcall *g_662360)(void);

/* ADDRESS: GOLD 0x00424c30 */
/* ADDRESS: GOLDTL 0x00421050 */
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
