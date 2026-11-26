


extern int g_772e70;
extern int g_772e74;
extern char g_68a930[];

unsigned short __cdecl gm_RandomMod(int);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);

void __cdecl d3snd_PlayObjectClickSound(unsigned short* e)
{
	int r;

	r = gm_RandomMod(2);
	if (*((char*) e + 2) == 0x14)
		r = 0;
	if (g_772e70 != 0 && r == 0) {
		d3snd_PlaySoundEffect(*e, g_772e70, g_68a930, -1);
		return;
	}
	if (g_772e74 != 0 && r == 1)
		d3snd_PlaySoundEffect(*e, g_772e74, g_68a930, -1);
}
