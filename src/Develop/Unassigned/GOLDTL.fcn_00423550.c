extern int g_6b7d7c;



void __cdecl fcn_00423670(int*, int, int);
int __cdecl fcn_0042a850(int);

void __cdecl sb_ResumeOrStartVoice(int* voice)
{
	if (g_6b7d7c != 0 && voice[0] != 0) {
		if (*(int*) (voice[1] + 0x38) == 0) {
			fcn_00423670(voice, 0, 0);
			return;
		}
		fcn_0042a850(voice[0]);
	}
}
