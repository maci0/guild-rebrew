


extern int cut_SkipMode;
int __cdecl ch_DestroyCharacter(void);

int __cdecl cut_DestroyActiveCharacter(void)
{
	if (cut_SkipMode != 0) {
		return 1;
	}
	return ch_DestroyCharacter();
}
