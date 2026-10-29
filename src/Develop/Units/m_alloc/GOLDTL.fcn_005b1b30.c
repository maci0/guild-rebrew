#include "g_774a78.h"

extern struct Node* g_774a78;
extern char s_6ab3f4[];

char* __cdecl fcn_005b1aa0(char*);
char* __cdecl m_alloc(int, char*);
int __cdecl fcn_0064d3f8(void);
void __cdecl fcn_005b1980(char*, char*);

/* 0x5b1b10 must be defined in this file ahead of 0x5b1b30: the original
 * compiler knew the callee leaves edx intact and pushed the reused `a`
 * from edx after the call. With only a prototype it reloads from the frame. */

/* ADDRESS: GOLDTL 0x005b1b10 */
char* __cdecl fcn_005b1b10(int a1)
{
	char* p;

	p = (char*) g_774a78;
	while (p != 0) {
		if (*(int*) p == a1) {
			return p + 0xc;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}

/* Both zero-fills are the original's hand-written block-fill prelude; no
 * msvc6 C memset spelling emits it (docs/codegen-walls.md section 6b). */
/* ADDRESS: GOLDTL 0x005b1b30 */
char* __cdecl fcn_005b1b30(char* a)
{
	char* p;
	char* r;

	if (g_774a78 == 0) {
		if (fcn_005b1aa0(a) == 0) {
			return 0;
		}
		p = m_alloc(0x4c, s_6ab3f4);
		if (p != 0) {
			int n;

			n = 0x4c;
			__asm {
				mov edi, p
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
			*(int*) p = *(int*) (a + 1);
			*(int*) (p + 4) = fcn_0064d3f8();
			*(float*) (p + 0x44) = 1.0f;
			fcn_005b1980(a, p);
			g_774a78 = (Node*) p;
			return p + 0xc;
		}
	}
	else {
		r = fcn_005b1b10(*(int*) (a + 1));
		if (r != 0) {
			return r;
		}
		if (fcn_005b1aa0(a) == 0) {
			return 0;
		}
		p = m_alloc(0x4c, s_6ab3f4);
		if (p == 0) {
			return 0;
		}
		{
			int n;

			n = 0x4c;
			__asm {
				mov edi, p
				mov ebx, n
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
			*(int*) p = *(int*) (a + 1);
			*(int*) (p + 4) = fcn_0064d3f8();
			*(float*) (p + 0x44) = 1.0f;
			fcn_005b1980(a, p);
			*(char**) (p + 0x48) = (char*) g_774a78;
			g_774a78 = (Node*) p;
			return p + 0xc;
		}
	}
	return 0;
}
unsigned char _dpad_774a34[68];
