


void __cdecl sb_StopVoice(void*);

/* ADDRESS: GOLDDE 0x004170b0 */
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
