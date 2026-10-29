extern int g_14ce8e0;
extern int g_774654;
int __cdecl fcn_005373e0(void*, const char*);

/* ADDRESS: GOLDTL 0x005c8090 */
void __cdecl fcn_005c8090(void)
{
retry:
	if (g_14ce8e0 != 0) {
		g_774654 = 1;
	}
	if (fcn_005373e0((void*)fcn_005c8090, (const char*)0x677c7) != 0) {
		goto retry;
	}
}
