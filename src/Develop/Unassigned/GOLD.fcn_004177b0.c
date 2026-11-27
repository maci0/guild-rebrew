void __cdecl sb_StopVoice(int*, int);
void __cdecl d3snd_SetVoiceFlag0x10(int*, int);

/* ADDRESS: GOLD 0x004177b0 */
void __cdecl d3snd_StopSourceVoice(char* p)
{
	if (*(void**) (p + 0x34) != 0) {
		sb_StopVoice(*(int**) (p + 0x34), 0);
		*(int*) (*(char**) (p + 0x34) + 0x14) |= 8;
		d3snd_SetVoiceFlag0x10(*(int**) (p + 0x34), 0);
		*(int*) (p + 0x34) = 0;
	}
	if (*(void**) (p + 0x38) != 0) {
		*(int*) (*(char**) (p + 0x38) + 0x20c) = 0;
		*(int*) (p + 0x38) = 0;
	}
}
