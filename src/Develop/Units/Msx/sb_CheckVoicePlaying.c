extern int sb_WaveDriver;



int __cdecl msx_GetSampleStatus(int);

int __cdecl sb_CheckVoicePlaying(int* voice)
{
	int status;

	status = 0;
	if (sb_WaveDriver == 0) {
		return 1;
	}
	if (voice != 0 && *voice != 0 && msx_GetSampleStatus(*voice) == 4) {
		status = -1;
	}
	return status;
}
