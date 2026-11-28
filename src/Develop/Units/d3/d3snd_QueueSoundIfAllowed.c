extern char cut_SkipMode[];


int __cdecl d3snd_QueueSound(void);

/* ADDRESS: GOLDDE 0x004d14c0 */
int __cdecl d3snd_QueueSoundIfAllowed(void)
{
	if (*(int*) &cut_SkipMode != 0) {
		return 0;
	}
	return d3snd_QueueSound();
}
