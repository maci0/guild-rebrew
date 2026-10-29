extern int g_6b5de0;

/* ADDRESS: GOLDTL 0x0041baa0 */
int __cdecl fcn_0041baa0(void)
{
	int hr = (int) 0x80004005;

	if (g_6b5de0 != 0) {
		hr = (*(int (__stdcall**) (int)) (*((int*) g_6b5de0) + 0xc))(g_6b5de0);
	}
	return hr;
}
