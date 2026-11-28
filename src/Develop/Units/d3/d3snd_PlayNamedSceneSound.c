#include <string.h>
int __cdecl fcn_0064f170(void*, char*, int);
void* __cdecl sb_PrepareVoice(int, char*);
int __cdecl d3snd_AttachSoundSource(void*, void*, int, float);
int __cdecl d3snd_PlaySource(int, int, int, int);
extern int d3snd_SoundEnabled;
/* ADDRESS: GOLDTL 0x00515e10 */
void __cdecl d3snd_PlayNamedSceneSound(char* p)
{
	char buf[0x100];
	int bn, br, si, v, r;
	char* s;
	char* d;

	r = fcn_0064f170(p, (char*) 0x6a1f7c, 4);
	if (r != 0)
		return;

	s = p + 4;
	d = buf;
	do {
		*d = *s;
		d++;
	} while (*s++ != 0);


	bn = (strstr(buf, (char*) 0x6a1f78) == 0);
	br = (int) strstr(buf, (char*) 0x6a1f74);
	if (br != 0) {
		br = 0x7d0;
		bn = 0;
	} else {
		br = 0;
	}

	if (d3snd_SoundEnabled != 0) {
		si = (int) sb_PrepareVoice(0, buf);
		if (si != 0) {
			v = (int)(*(float*)(p + 0x68)) + 0x32;
			r = d3snd_AttachSoundSource((void*) si, p, 0x7f, (float) v);
			if (r != 0)
				d3snd_PlaySource(r, 0, bn, br);
		}
	}

	*(int*)(p + 0x224) = 0;
	return;
}
