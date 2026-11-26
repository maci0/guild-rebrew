

int __cdecl d3snd_QueueSound(void);

int __cdecl fcn_004e4b40(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return d3snd_QueueSound();
}
