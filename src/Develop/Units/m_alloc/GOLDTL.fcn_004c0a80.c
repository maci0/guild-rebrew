#include <string.h>

#pragma optimize("y", off)

extern char s_689d24[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl m_alloc(int, char*);
void __cdecl d3snd_SetVoiceFlag0x10(char*, int);
void* __cdecl d3snd_GetLastTrackedVoice(void);

/* ADDRESS: GOLDTL 0x004c0a80 */
int __cdecl fcn_004c0a80(char* a0, int a1)
{
	char* p;
	void* q;
	int n;
	int v;

	if (a0 != 0) {
		p = m_alloc(0x10, s_689d24);
		if (p != 0) {
		n = 0x10;
		v = 0;
		/* Reviewed native fill core at 0x004c0aba-0x004c0ae7. */
		__asm {
			mov edi, p
			mov eax, v
			mov ebx, n
			mov ah, al
			shl eax, 16
			mov ecx, eax
			shr ecx, 16
			add eax, ecx
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		d3snd_SetVoiceFlag0x10(a0, 1);
		*(char**) p = a0;
		*(int*) (p + 4) = a1;
		q = d3snd_GetLastTrackedVoice();
		if (q != 0) {
			*(void**) ((char*) q + 0xc) = p;
			return 1;
		}
		g_772d34 = p;
		return 1;
	}
	}
	return 0;
}

#pragma optimize("", on)
