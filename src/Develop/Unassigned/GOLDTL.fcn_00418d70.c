

void __cdecl sb_StopVoice(char*, int);
void __cdecl d3snd_SetVoiceFlag0x10(char*, int);

void __cdecl fcn_00418d70(char* p)
{
	if (*(char**) (p + 0x34) != 0) {
		sb_StopVoice(*(char**) (p + 0x34), 0);
		*(int*) (*(char**) (p + 0x34) + 0x14) |= 8;
		d3snd_SetVoiceFlag0x10(*(char**) (p + 0x34), 0);
		*(char**) (p + 0x34) = 0;
	}
	if (*(char**) (p + 0x38) != 0) {
		*(int*) (*(char**) (p + 0x38) + 0x210) = 0;
		*(char**) (p + 0x38) = 0;
	}
}
