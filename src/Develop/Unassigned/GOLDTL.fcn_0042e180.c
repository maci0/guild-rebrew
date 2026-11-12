#include <string.h>
extern char* g_6b7fd0;
extern char* g_6b7fd8;

static __inline void fill0_42e180(char* dst, int size)
{
	char* d;
	int n;

	n = size;
	d = dst;
	__asm {
		mov edi, d
		mov ebx, n
		xor eax, eax
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
}

/* ADDRESS: GOLDTL 0x0042e180 */
void __cdecl fcn_0042e180(void)
{
	if (g_6b7fd0 != 0 && g_6b7fd0 > g_6b7fd8) {
		g_6b7fd0 -= 0x84;
		fill0_42e180(g_6b7fd0 + 0xe, 0x30);
		fill0_42e180(g_6b7fd0 + 0x3e, 0x30);
		*(int*) (g_6b7fd0 + 0x70) = 0;
	} else {
		__asm { int 3 }
	}
}
