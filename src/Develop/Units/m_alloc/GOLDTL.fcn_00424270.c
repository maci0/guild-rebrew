#include <string.h>

char* __cdecl m_alloc(int size, char* tag);
char* __cdecl fcn_00423ac0(int id);
int* __cdecl fcn_00423c50(int a0, int a1);
char* __cdecl fcn_00423a10(int a1);
int __cdecl fcn_00423920(unsigned int a0);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00424270 */
unsigned int __cdecl fcn_00424270(unsigned int a0, unsigned int a1)
{
	char* p;
	char* v3;
	char* v2;

	v2 = fcn_00423ac0(a0);
	if (!v2) {
		return 0xffffffff;
	}
	if (fcn_00423c50(a0, a1)) {
		return 0xffffffff;
	}
	v3 = fcn_00423a10(a0);
	p = m_alloc(0x108, (char*) 0x678fec);
	if (v3) {
		char* fill;
		*(char**) (v3 + 0x104) = p;
		if (!*(char**) (v3 + 0x104)) {
			return 0xffffffff;
		}
		fill = p;
		a0 = 0x108;
		/* Native fill core at 0x4242e4-0x424304. */
		__asm {
			mov edi, fill
			mov ebx, a0
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
		strncpy(*(char**) (v3 + 0x104), (char*) a1, 0x100);
		*(int*) (*(char**) (v3 + 0x104) + 0x100) = fcn_00423920(a1);
		*(int*) (v2 + 0x34) += *(int*) (*(char**) (v3 + 0x104) + 0x100);
		*(int*) (*(char**) 0x6b7d68 + 0x34) += *(int*) (*(char**) (v3 + 0x104) + 0x100);
		*(int*) 0x6b7d6c = *(int*) 0x6b7d6c + 1;
	} else {
		char* fill;
		*(char**) (v2 + 0x38) = p;
		if (!*(char**) (v2 + 0x38)) {
			return 0xffffffff;
		}
		fill = p;
		a0 = 0x108;
		/* Native fill core at 0x424389-0x4243a9. */
		__asm {
			mov edi, fill
			mov ebx, a0
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
		strncpy(*(char**) (v2 + 0x38), (char*) a1, 0x100);
		*(int*) (*(char**) (v2 + 0x38) + 0x100) = fcn_00423920(a1);
		*(int*) (v2 + 0x34) += *(int*) (*(char**) (v2 + 0x38) + 0x100);
		*(int*) (*(char**) 0x6b7d68 + 0x34) += *(int*) (*(char**) (v2 + 0x38) + 0x100);
		*(int*) 0x6b7d6c = *(int*) 0x6b7d6c + 1;
	}
	return 0;
}
