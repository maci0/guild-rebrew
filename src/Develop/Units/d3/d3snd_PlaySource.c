


#include <stdio.h>

void __cdecl sb_SetVoiceLoopCount(char* o, int v);
int __cdecl sb_StartVoice(char* o, int a, int b);
void __cdecl sb_ResumeOrStartVoice(char* o);

/* ADDRESS: GOLDDE 0x00416ff0 */
void __cdecl d3snd_PlaySource(char* r, int a2, int a3, int a4)
{
	char buf[0x100];

	if (r == 0 || *(char**) (r + 0x34) == 0) {
		return;
	}
	if (*(int*) (*(char**) (r + 0x34) + 4) == 0) {
		sprintf(buf, "Entry-Handle missing for %s", r);
		sprintf(buf, "3dSound-Handle is attached to %s", *(char**) (r + 0x38));
		return;
	}
	*(int*) (*(char**) (r + 0x34) + 0xc) = a3;
	*(int*) (r + 0x44) = a3;
	sb_SetVoiceLoopCount(*(char**) (r + 0x34), a3);
	*(int*) (r + 0x4c) = a4;
	if (*(int*) (r + 0x50) == 0) {
		sb_StartVoice(*(char**) (r + 0x34), a2, a4);
		*(int*) (r + 0x3c) = 0;
		return;
	}
	sb_ResumeOrStartVoice(*(char**) (r + 0x34));
	*(int*) (r + 0x3c) = 0;
}
