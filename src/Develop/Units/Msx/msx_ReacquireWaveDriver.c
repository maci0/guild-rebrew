


int __cdecl msx_FindWaveDriverIndex(int);
extern int msx_Initialized;
__declspec(dllimport) int __stdcall AIL_digital_handle_reacquire(int);
__declspec(dllimport) int __stdcall PostMessageA(int, unsigned int, int*, int);

/* ADDRESS: GOLDDE 0x00424da0 */
void __cdecl msx_ReacquireWaveDriver(int* audio, int window, unsigned int message)
{
	if (msx_Initialized != 0 && message >= 0x400 && msx_FindWaveDriverIndex((int) audio) >= 0 && AIL_digital_handle_reacquire(*audio) == 0) {
		PostMessageA(window, message, audio, 0);
	}
}
