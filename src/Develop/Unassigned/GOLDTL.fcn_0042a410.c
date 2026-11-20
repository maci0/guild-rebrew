


int __cdecl msx_FindWaveDriverIndex(int);
extern int g_6b7f90;
__declspec(dllimport) int __stdcall AIL_digital_handle_reacquire(int);
__declspec(dllimport) int __stdcall PostMessageA(int, unsigned int, int*, int);

void __cdecl msx_ReacquireWaveDriver(int* audio, int window, unsigned int message)
{
	if (g_6b7f90 != 0 && message >= 0x400 && msx_FindWaveDriverIndex((int) audio) >= 0 && AIL_digital_handle_reacquire(*audio) == 0) {
		PostMessageA(window, message, audio, 0);
	}
}
