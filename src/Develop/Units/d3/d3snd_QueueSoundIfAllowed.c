

int __cdecl d3snd_QueueSound(void);

int __cdecl d3snd_QueueSoundIfAllowed(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return d3snd_QueueSound();
}
