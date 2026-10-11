// FUNCTION: GOLD 0x005a8b70
// FUNCTION: GOLDTL 0x005b1ff0

#include "g_774a78.h"

extern struct Node* g_774a78;
extern char s_6ab408[];

void __cdecl fcn_005b1ef0(void);
int __cdecl ls_ReadVfsDataChecked(void*, int, int, int);
char* __cdecl m_alloc(int, char*);

/* The record zero-fill is the original's hand-written block-fill prelude;
 * no msvc6 C memset spelling emits it (docs/codegen-walls.md section 6b). */
int __cdecl fcn_005b1ff0(int fh)
{
	int count;
	int i;
	char* e;
	int k;

	fcn_005b1ef0();
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
		if (g_774a78 != 0) {
			*(char**) (p + 0x48) = (char*) g_774a78;
		}
		g_774a78 = (Node*) p;
	}
	for (e = (char*) g_774a78; e != 0; e = *(char**) (e + 0x48)) {
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
	fcn_005b1ef0();
	return 0;
}
