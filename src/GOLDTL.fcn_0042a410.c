// FUNCTION: GOLD 0x0042bab0
// FUNCTION: GOLDTL 0x42a410

int __cdecl fcn_0042b120(int);
extern int g_6b7f90;
__declspec(dllimport) int __stdcall AIL_digital_handle_reacquire(int);
__declspec(dllimport) int __stdcall PostMessageA(int, unsigned int, int*, int);

void __cdecl fcn_0042a410(int* a1, int a2, unsigned int a3)
{
	if (g_6b7f90 != 0 && a3 >= 0x400 && fcn_0042b120((int) a1) >= 0 && AIL_digital_handle_reacquire(*a1) == 0) {
		PostMessageA(a2, a3, a1, 0);
	}
}
