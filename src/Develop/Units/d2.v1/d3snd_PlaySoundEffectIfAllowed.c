

int __cdecl d3snd_PlaySoundEffect(void);

int __cdecl d3snd_PlaySoundEffectIfAllowed(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return d3snd_PlaySoundEffect();
}
