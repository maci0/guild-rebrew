/* ADDRESS: GOLD 0x005f38a0 */
extern int d3snd_SourceCount;
/* ADDRESS: GOLD 0x00631130 */
extern char* tp_SoundSources;



void __cdecl fcn_00418d70(char*);

/* ADDRESS: GOLD 0x00417990 */
void __cdecl d3snd_StopAllObjectSounds(void)
{
	int i;
	char* source;

	for (i = 0; i < d3snd_SourceCount; i++) {
		source = tp_SoundSources + i * 0x54;
		if (*(int*) (source + 0x38) != 0) {
			fcn_00418d70(source);
		}
	}
}
