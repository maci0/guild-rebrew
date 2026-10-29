extern char g_7f4ca0[];
extern char g_7f4ca0[];
extern int g_774800;
extern int g_774800;

/* ADDRESS: GOLD 0x004ce170 */
/* ADDRESS: GOLDTL 0x004cef70 */
int __cdecl fcn_004cef70(int a1, char* a2)
{
	int r;

	r = 0;
	if (*(int*) (a2 + 0x16c) == (int) (g_7f4ca0 + a1 * 540)) {
		r = 0x800;
	}
	if (*(int*) ((char*)&g_774800) != 0) {
		r = 0x800;
	}
	return r;
}
