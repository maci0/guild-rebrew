extern int* g_6b7d78;
extern int g_6b7d7c;
extern char g_14cb980[];

/* ADDRESS: GOLD 0x00426630 */
/* ADDRESS: GOLDTL 0x00422aa0 */
char* __cdecl fcn_00422aa0(void)
{
	char* p;

	p = ((char*)g_6b7d78);
	if (g_6b7d7c == 0) {
		return g_14cb980;
	}
	if (p != 0) {
		while (*(char**) (p + 0x13c) != 0) {
			p = *(char**) (p + 0x13c);
		}
	}
	return p;
}
