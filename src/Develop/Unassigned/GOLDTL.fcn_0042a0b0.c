


void __cdecl fcn_0042ad00(void);
void __cdecl fcn_0042a760(void);
void __cdecl fcn_0042a350(void);
__declspec(dllimport) void __stdcall AIL_shutdown(void);
extern int g_6b7f90;

int __cdecl fcn_0042a0b0(void)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		fcn_0042ad00();
		fcn_0042a760();
		fcn_0042a350();
		AIL_shutdown();
		g_6b7f90 = r;
	} else {
		r = -1;
	}
	return r;
}
