


#include "Develop/DieGildeAddOn/loadsave/g_774a78.h"

extern struct Node* hp_ProdEntryList;
extern char s_6ab408[];

void __cdecl ls_FreeList774a78(void);
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
char* __cdecl m_alloc(int, char*);

/* The record zero-fill is the original's hand-written block-fill prelude;
 * recorded C memset probes did not emit it (archived docs/codegen-walls.md section 6b). */
/* ADDRESS: GOLDDE 0x005969f0 */
int __cdecl ls_LoadList774a78(void* fh)
{
	int count;
	int i;
	char* e;
	int k;

	ls_FreeList774a78();
	if (ls_ReadVfsDataChecked(&count, 4, 1, fh) == 0) {
		return 0;
	}
	for (i = 0; i < count; i++) {
		char* p;
		int n;

		p = m_alloc(0x4c, s_6ab408);
		if (p == 0) {
			goto fail;
		}
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
		*(int*) p = -1;
		if (hp_ProdEntryList != 0) {
			*(char**) (p + 0x48) = (char*) hp_ProdEntryList;
		}
		hp_ProdEntryList = (Node*) p;
	}
	for (e = (char*) hp_ProdEntryList; e != 0; e = *(char**) (e + 0x48)) {
		if (ls_ReadVfsDataChecked(e, 4, 1, fh) == 0) {
			goto fail;
		}
		if (ls_ReadVfsDataChecked(e + 4, 4, 1, fh) == 0) {
			goto fail;
		}
		if (ls_ReadVfsDataChecked(e + 0x44, 4, 1, fh) == 0) {
			goto fail;
		}
		for (k = 0; k < 7; k++) {
			if (ls_ReadVfsDataChecked(e + 0xc + k * 8, 4, 1, fh) == 0) {
				goto fail;
			}
			if (ls_ReadVfsDataChecked(e + 0x10 + k * 8, 1, 1, fh) == 0) {
				goto fail;
			}
		}
	}
	return 1;
fail:
	ls_FreeList774a78();
	return 0;
}
