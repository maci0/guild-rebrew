extern int d3_ActiveScene;
extern int d3snd_SourceCount;

// SIZE 0x54
struct snd_418e00 {
	char pad0[0x34];
	char* voice;
	char* obj;
	int idle;
	char pad40[4];
	int fade;
	char pad48[8];
	int keep;
};

extern char* tp_SoundSources;

void __cdecl sb_StopVoice(char*, int);
void __cdecl d3snd_SetVoiceFlag0x10(char*, int);
void __cdecl d3_UpdateSoundSourceVolume(struct snd_418e00*);
void __cdecl d3_UpdateSoundSourcePan(struct snd_418e00*);
int __cdecl sb_CheckVoicePlaying(char*);
void __cdecl d3snd_StopSourceVoice(struct snd_418e00*);

/* ADDRESS: GOLD 0x00417840 */

/* Updates the positional sound sources: silences the ones outside the
 * current room, pans the others and releases finished voices. */
void __cdecl d3snd_UpdateSoundSources(void)
{
	int i;

	if (((struct snd_418e00*)tp_SoundSources) == 0) {
		return;
	}
	for (i = 0; i < d3snd_SourceCount; i++) {
		if (((struct snd_418e00*)tp_SoundSources)[i].obj == 0) {
			continue;
		}
#ifdef REBREW_GOLD
		if (*(char**) (((struct snd_418e00*)tp_SoundSources)[i].obj + 0x208) != ((char*)d3_ActiveScene)) {
#else
		if (*(char**) (((struct snd_418e00*)tp_SoundSources)[i].obj + 0x20c) != ((char*)d3_ActiveScene)) {
#endif
			if (((struct snd_418e00*)tp_SoundSources)[i].voice == 0) {
				continue;
			}
			sb_StopVoice(((struct snd_418e00*)tp_SoundSources)[i].voice, 0);
			*(unsigned int*) (((struct snd_418e00*)tp_SoundSources)[i].voice + 0x14) |= 8;
			if (((struct snd_418e00*)tp_SoundSources)[i].keep == 0) {
				d3snd_SetVoiceFlag0x10(((struct snd_418e00*)tp_SoundSources)[i].voice, 0);
				((struct snd_418e00*)tp_SoundSources)[i].voice = 0;
			}
			continue;
		}
		d3_UpdateSoundSourceVolume(&((struct snd_418e00*)tp_SoundSources)[i]);
		d3_UpdateSoundSourcePan(&((struct snd_418e00*)tp_SoundSources)[i]);
		if (((struct snd_418e00*)tp_SoundSources)[i].voice == 0 || sb_CheckVoicePlaying(((struct snd_418e00*)tp_SoundSources)[i].voice) != 0) {
			continue;
		}
		((struct snd_418e00*)tp_SoundSources)[i].idle++;
		if (((struct snd_418e00*)tp_SoundSources)[i].idle > 500 && ((struct snd_418e00*)tp_SoundSources)[i].keep == 0) {
			if (((struct snd_418e00*)tp_SoundSources)[i].fade != 0) {
				d3snd_StopSourceVoice(&((struct snd_418e00*)tp_SoundSources)[i]);
			} else {
				d3snd_SetVoiceFlag0x10(((struct snd_418e00*)tp_SoundSources)[i].voice, 0);
				*(unsigned int*) (((struct snd_418e00*)tp_SoundSources)[i].voice + 0x14) |= 8;
				((struct snd_418e00*)tp_SoundSources)[i].voice = 0;
			}
		}
	}
}
