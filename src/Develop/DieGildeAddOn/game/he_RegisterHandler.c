extern char g_7d1d80[];
extern char g_7d1d80[];
extern char g_7dc440[];
extern char g_7dc440[];

/* ADDRESS: GOLD 0x0053d860 */
/* ADDRESS: GOLDTL 0x00545580 */
int __cdecl he_RegisterHandler(int index, int a2, int a3)
{
	if (index < 0 || index >= 0xa7) {
		return 1;
	}
	((int*) g_7d1d80)[index] = a2;
	((int*) g_7dc440)[index] = a3;
	return 0;
}
