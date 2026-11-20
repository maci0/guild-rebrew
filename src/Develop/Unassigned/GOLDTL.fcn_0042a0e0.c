typedef void (__stdcall* g_6623b0_f)(int, int);
extern g_6623b0_f g_6623b0;
extern g_6623b0_f g_6623b0;



int __cdecl msx_FindWaveDriverIndex(int);

int __cdecl fcn_0042a0e0(int* audio, int value)
{
	int result = 0;

	if (msx_FindWaveDriverIndex((int) audio) >= 0 && value >= 0 && value <= 0x7f) {
		g_6623b0(*audio, value);
	} else {
		result = -1;
	}
	return result;
}
