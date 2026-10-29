extern char g_7d1d80[];
extern char g_7d1d80[];
extern char g_7dc440[];
extern char g_7dc440[];

/* ADDRESS: GOLD 0x0053d860 */
/* ADDRESS: GOLDTL 0x00545580 */
int __cdecl fcn_00545580(int a1, int a2, int a3)
{
	if (a1 < 0 || a1 >= 0xa7) {
		return 1;
	}
	((int*) g_7d1d80)[a1] = a2;
	((int*) g_7dc440)[a1] = a3;
	return 0;
}
