


void* __cdecl fcn_00423460(void*);

void* __cdecl d3snd_GetObjectVoiceStatus(char* sound_obj)
{
	void* voice;

	if (sound_obj == 0) {
		return 0;
	}
	voice = *(void**) (sound_obj + 0x34);
	if (voice == 0) {
		return 0;
	}
	return fcn_00423460(voice);
}
