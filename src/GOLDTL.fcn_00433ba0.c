extern char* g_1042320;
extern char g_1052a40[];

int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLD 0x00433f40 */
/* ADDRESS: GOLDTL 0x00433ba0 */
char* __cdecl fcn_00433ba0(const char* name)
{
	char* p;

	for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
		if (fcn_0065f220(name, p) == 0) {
			return p;
		}
	}
	return 0;
}
