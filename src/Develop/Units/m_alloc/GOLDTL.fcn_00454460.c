#include <string.h>

#pragma optimize("y", off)

int __cdecl fcn_004524e0(int, int, int, int, int, int);
void __cdecl fcn_004526d0(void*, int);
void __cdecl fcn_004526f0(void*, void*, int);

/* ADDRESS: GOLDTL 0x00454460 */
int __cdecl fcn_00454460(int a0, int a1, int a2, int a3, int* a4, int a5, int* a6)
{
	int* s;


	int v;

	v = *a6;
	if (v == 0) {
		s = (int*) fcn_004524e0(a2, a3, (int) a4, a5, a0, 0x452c60);
	} else if (v == 1) {
		s = (int*) fcn_004524e0(a2, a3, (int) a4, a5, a0, 0x453470);
	} else if (v == 2) {
		s = (int*) fcn_004524e0(a2, a3, (int) a4, a5, a0, 0x453d80);
	} else {
		return 0;
	}
	if (s != 0) {
		fcn_004526d0(s, a1);
		a4 = (int*) ((char*) s + 0x34);
		a5 = 0xa4;
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
		fcn_004526f0(s, (char*) s + 0x74, 0);
		if (*(unsigned char*) ((char*) s + 0xd5) & 1) {
			s[8] = 0;
			*(unsigned char*) ((char*) s + 0xd5) |= 2;
		}
	}
	return (int) s;
}
