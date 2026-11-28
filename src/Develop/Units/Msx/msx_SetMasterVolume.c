typedef void (__stdcall* g_6623b0_f)(int, int);
extern g_6623b0_f imp_AIL_set_digital_master_volume;
extern g_6623b0_f imp_AIL_set_digital_master_volume;



int __cdecl msx_FindWaveDriverIndex(int);

int __cdecl msx_SetMasterVolume(int* audio, int value)
{
	int result = 0;

	if (msx_FindWaveDriverIndex((int) audio) >= 0 && value >= 0 && value <= 0x7f) {
		imp_AIL_set_digital_master_volume(*audio, value);
	} else {
		result = -1;
	}
	return result;
}
