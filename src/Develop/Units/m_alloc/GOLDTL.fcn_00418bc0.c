#include <string.h>
#include "client_sound.h"
extern void* __cdecl m_alloc(unsigned int size, const char* file_and_line);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00418bc0 */
int __cdecl fcn_00418bc0(int a0)
{
	int result;
	unsigned int n;
	char* p;

	result = 0;
	if (g_6b5d08 != 0)
		return -1;
	if (a0 != 0)
		g_677680 = a0;
	else
		a0 = g_677680;
	n = (unsigned int) a0 * 0x54;
	p = (char*) m_alloc(n, (const char*) 0x677750);
	g_6b5d08 = (SOUND_SOURCE*) p;
	if (p == 0)
		return -1;
	a0 = g_677680 * 0x54;
	p = (char*) g_6b5d08;
	__asm {
		mov edi, p
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
	return result;
}
#pragma optimize("", on)
