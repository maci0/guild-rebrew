


extern int g_6b7f90;
void __cdecl fcn_005eaad0(void);
__declspec(dllimport) int __stdcall AIL_startup(void);
__declspec(dllimport) char* __stdcall AIL_last_error(void);

int __cdecl fcn_0042a080(void)
{
	int r = 0;

	if (g_6b7f90 == 0) {
		fcn_005eaad0();
		AIL_startup();
		AIL_last_error();
		g_6b7f90 = -1;
	} else {
		r = -1;
	}
	return r;
}
