#include <string.h>
#include "client_sound.h"
extern void* __cdecl m_alloc(unsigned int size, const char* file_and_line);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00418bc0 */
int __cdecl fcn_00418bc0(int a0)
{
	int result;
	unsigned int n;


	result = 0;
	if (tp_SoundSources == 0) {
		if (a0 != 0)
			d3snd_SourceCount = a0;
		else
			a0 = d3snd_SourceCount;
		n = (unsigned int) a0 * 0x54;
		tp_SoundSources = (SOUND_SOURCE*) m_alloc(n, (const char*) 0x677750);
		if (tp_SoundSources != 0) {
			a0 = d3snd_SourceCount * 0x54;
	__asm {
		mov edi, tp_SoundSources
		mov ebx, a0
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L418bc0fill
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L418bc0fill:
		add ecx, ebx
		rep stosb
	}
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
#pragma optimize("", on)
