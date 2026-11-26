


void __cdecl sb_StopVoice(void*);

void __cdecl d3snd_StopObjectVoice(char* sound_obj)
{
	void* voice;

	if (sound_obj == 0) {
		return;
	}
	voice = *(void**) (sound_obj + 0x34);
	if (voice == 0) {
		return;
	}
	sb_StopVoice(voice);
}
