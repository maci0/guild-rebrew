__declspec(dllimport) void __stdcall EnterCriticalSection(int);
__declspec(dllimport) void __stdcall LeaveCriticalSection(int);
extern char g_14cc5a0[];
extern char g_6b71a8[];
extern char g_678164[];


int __cdecl msx_SetMasterVolume(int, int);

/* ADDRESS: GOLDDE 0x0041cd40 */
void __cdecl fcn_004c3140(void* a)
{
	if (*(int*) &g_6b71a8 != 0) {
		EnterCriticalSection((int) &g_14cc5a0);
		msx_SetMasterVolume(*(int*) &g_6b71a8, (int) a);
		*(int*) &g_678164 = (int) a;
		LeaveCriticalSection((int) &g_14cc5a0);
	}
}
