extern int g_6b7d7c;



void __cdecl sb_StartVoice(int*, int, int);
int __cdecl msx_ResumeSample(int);

void __cdecl sb_ResumeOrStartVoice(int* voice)
{
	if (g_6b7d7c != 0 && voice[0] != 0) {
		if (*(int*) (voice[1] + 0x38) == 0) {
			sb_StartVoice(voice, 0, 0);
			return;
		}
		msx_ResumeSample(voice[0]);
	}
}
