

int __cdecl msx_StopSample(int);

void __cdecl sb_ResetVoice(int* voice)
{
	if (*(int*) 0x6b7d7c != 0 && voice != 0) {
		msx_StopSample(voice[0]);
		voice[2] = 0;
		voice[9] = 0x7f;
		voice[10] = 0x3f;
	}
}
