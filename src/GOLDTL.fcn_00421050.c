/* ADDRESS: GOLD 0x01460ae0 */
extern int g_14cbca0;
/* ADDRESS: GOLD 0x01460af0 */
extern int g_14cbcb0;
/* ADDRESS: GOLD 0x00633160 */
extern int g_6b7d40;
/* ADDRESS: GOLD 0x005eb2c8 */
extern void (__stdcall *g_662374)(int, int);
/* ADDRESS: GOLD 0x005eb2b0 */
extern void (__stdcall *g_66234c)(int);
/* ADDRESS: GOLD 0x005eb2b8 */
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
