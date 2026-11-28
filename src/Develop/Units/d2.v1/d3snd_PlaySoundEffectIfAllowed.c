extern char cut_SkipMode[];


int __cdecl d3snd_PlaySoundEffect(void);

/* ADDRESS: GOLDDE 0x004d14a0 */
int __cdecl d3snd_PlaySoundEffectIfAllowed(void)
{
	if (*(int*) &cut_SkipMode != 0) {
		return 0;
	}
	return d3snd_PlaySoundEffect();
}
