#include "Develop/DieGildeAddOn/loadsave/g_774a78.h"

extern struct Node* hp_ProdEntryList;
extern char s_6ab3f4[];

char* __cdecl hp_LookupProdEntry(char*);
char* __cdecl m_alloc(int, char*);
int __cdecl fcn_0064d3f8(void);
void __cdecl hp_UpdateProdSetting(char*, char*);

/* 0x5b1b10 must be defined in this file ahead of 0x5b1b30: the original
 * compiler knew the callee leaves edx intact and pushed the reused `a`
 * from edx after the call. With only a prototype it reloads from the frame. */

/* ADDRESS: GOLDTL 0x005b1b10 */
char* __cdecl hp_FindProdSetting(int id)
{
	char* p;

	p = (char*) hp_ProdEntryList;
	while (p != 0) {
		if (*(int*) p == id) {
			return p + 0xc;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}

/* Both zero-fills are the original's hand-written block-fill prelude; no
 * msvc6 C memset spelling emits it (archived docs/codegen-walls.md section 6b). */
/* ADDRESS: GOLDTL 0x005b1b30 */
char* __cdecl hp_AddProdSetting(char* a)
{
	char* p;
	char* r;

	if (hp_ProdEntryList == 0) {
		if (hp_LookupProdEntry(a) == 0) {
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
			hp_UpdateProdSetting(a, p);
			hp_ProdEntryList = (Node*) p;
			return p + 0xc;
		}
	}
	else {
		r = hp_FindProdSetting(*(int*) (a + 1));
		if (r != 0) {
			return r;
		}
		if (hp_LookupProdEntry(a) == 0) {
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
			hp_UpdateProdSetting(a, p);
			*(char**) (p + 0x48) = (char*) hp_ProdEntryList;
			hp_ProdEntryList = (Node*) p;
			return p + 0xc;
		}
	}
	return 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_774a34[68];
#endif
