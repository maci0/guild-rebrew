

void __cdecl d3snd_StopSourceVoice(int);

void __cdecl d3snd_StopSourceVoiceSafe(int a1)
{
	if (a1 == 0) {
		return;
	}
	d3snd_StopSourceVoice(a1);
}
