void __cdecl d3_UpdateDirectedEmitter();
void __cdecl d3_UpdateDriftEmitter();
void __cdecl d3_StepParticleEmitter();
#include <string.h>

#pragma optimize("y", off)

int __cdecl d3_CreateParticleSystem(int, int, int, int, int, int);
void __cdecl d3_SetEffectPosition(void*, int);
void __cdecl d3_SetEffectDirection(void*, void*, int);

/* ADDRESS: GOLDTL 0x00454460 */
/* ADDRESS: GOLDDE 0x00449d10 */
int __cdecl d3_CreateParticleEmitter(int a0, int a1, int a2, int a3, int* a4, int a5, int* a6)
{
	int* s;


	int v;

	s = 0;
	v = *a6;
	if (v == 0) {
		s = (int*) d3_CreateParticleSystem(a2, a3, (int) a4, a5, a0, (int) d3_UpdateDirectedEmitter);
	} else if (v == 1) {
		s = (int*) d3_CreateParticleSystem(a2, a3, (int) a4, a5, a0, (int) d3_UpdateDriftEmitter);
	} else if (v == 2) {
		s = (int*) d3_CreateParticleSystem(a2, a3, (int) a4, a5, a0, (int) d3_StepParticleEmitter);
	}
	if (s != 0) {
		d3_SetEffectPosition(s, a1);
		a5 = 0xa4;
		a4 = (int*) ((char*) s + 0x34);
		__asm {
			mov edi, a4
			mov esi, a6
			mov ebx, a5
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short copy_tail
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
copy_tail:
			add ecx, ebx
			rep movsb
		}
		d3_SetEffectDirection(s, (char*) s + 0x74, 0);
		if (*(unsigned char*) ((char*) s + 0xd5) & 1) {
			s[8] = 0;
			*(unsigned char*) ((char*) s + 0xd5) |= 2;
		}
	}
	return (int) s;
}
