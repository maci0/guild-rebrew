extern unsigned char g_6a375c;
extern int g_772620;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);


/* ADDRESS: GOLDTL 0x0047d1e0 */
int __cdecl fcn_0047d1e0(void)
{
	int n;
	char* p;

	n = 0;
	for (p = fcn_005463a0(1, 0, 0xb); p != 0; p = he_fn_Handlung()) {
		if (p[0xf1] == 0)
			n++;
	}
	return g_6a375c * g_772620 + n;
}
