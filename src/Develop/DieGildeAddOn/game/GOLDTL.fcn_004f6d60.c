#include <string.h>

#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern int g_6b8010;

extern int __cdecl gm_WalkEntityChain(int);
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern unsigned short* __cdecl fcn_00502cd0(int, int, ...);
extern void __cdecl fcn_004c5420(int, int, int, int, int);
extern void __cdecl io_FormatTextBuffer(char*, char*, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
extern void __cdecl fcn_004c4510(char*, int);
extern void __cdecl fcn_004c4570(unsigned char, unsigned char, short, void*);
extern void __cdecl fcn_004c5360(void);
extern void __cdecl fcn_004c5530(void*);
extern unsigned short __cdecl gm_RandomMod(int);
extern void __cdecl fcn_00500bb0(void*, int, int, int);
extern char s_6903e8[];

#pragma optimize("y", off)


/* Erhoeht den Diebstahls-Zaehler eines Objekts und schickt je nach
 * Objektart ein Aendern-Paket 0x69 oder die Quickjump-Meldung. */
/* ADDRESS: GOLDTL 0x004f6d60 */
void __cdecl fcn_004f6d60(unsigned int a0)
{
	char text[0x200];
	char msg[0xf8];
	char* slot;
	char* other;
	unsigned short* found;
	unsigned short* alloc;
	int count;
	int v;
	int limit;
	char* fill_dst;
	int fill_count;

	slot = g_7f4ca0 + (a0 & 0xffff) * 0x21c;
	if (*(short*) slot == -1) {
		return;
	}
	if (*(unsigned char*) (slot + 2) >= 0xa) {
		return;
	}
	if (*(char*) (slot + 8) == 0) {
		return;
	}
	if (*(unsigned char*) (slot + 2) == 0) {
		return;
	}
	v = gm_WalkEntityChain((int) a0);
	count = *(unsigned char*) (slot + 0xd);
	limit = count + 1;
	if (limit > 0xa) {
		limit = 0xa;
	}
	limit = *(int*) ((char*) 0x6653a0 + limit * 4);
	if (v <= limit) {
		return;
	}
	if (count == 1) {
		found = gm_StartFilteredEntitySearch(1, 5, 0xf);
		if (found == 0) {
			return;
		}
		alloc = fcn_00502cd0((int) *(unsigned int*) ((char*) found + 0x5d), 2, 6, 0, 0x110);
		if (alloc == 0) {
			return;
		}
		fcn_004c5420(*(int*) (slot + 4), 0x1c8, 4, 0x4000, 0);
		if (*(char*) (slot + 2) == 6 || *(char*) (slot + 2) == 7) {
			io_FormatTextBuffer(text, (char*) 0x161d, *(unsigned short*) slot);
			he_MessageBoxQuickjump(*(int*) (slot + 4), -1, text, 0, 0x5fd,
					       *(int*) ((char*) found + 1),
					       *(int*) ((char*) alloc + 2), 0, s_6903e8);
		}
		return;
	}
	if (count >= 9) {
		return;
	}
	*((unsigned char*)&a0 + 3) = count + 1;
	if (*(char*) (slot + 2) != 6 && *(char*) (slot + 2) != 7) {
		fcn_004c4510(slot, *(int*) (slot + 4));
		fcn_004c4570(1, 1, 0xd, ((unsigned char*)&a0 + 3));
		fcn_004c5360();
	} else {
		fill_dst = msg;
		fill_count = 0xf8;
		__asm {
            mov edi, fill_dst
            xor eax, eax
            mov ebx, fill_count
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short L_fill_tail0
            rep stosb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep stosd
        L_fill_tail0:
            add ecx, ebx
            rep stosb
        }
		*(int*) (msg + 0x2c) = g_7f4c00.b;
		*(int*) (msg + 0x28) = g_7f4c00.a;
		*(short*) (msg + 0x34) = g_7f4c00.d;
		*(int*) (msg + 0x30) = g_7f4c00.c;
		*(unsigned char*) (msg + 4) = 0x69;
		*(int*) (msg + 8) = *(int*) (slot + 4);
		*(int*) (msg + 0xc) = -1;
		*(unsigned char*) (msg + 0x36) = 9;
		*(short*) (msg + 0x2c) = 7;
		*(int*) (msg + 0x2e) = 0;
		*(char*) (msg + 0x58) = *((unsigned char*)&a0 + 3);
		*(int*) (msg + 0x5c) = *(int*) (slot + 4);
		fcn_004c5530(msg);
	}
	if (*(char*) (slot + 2) != 5 && *(char*) (slot + 2) != 6
	    && *(char*) (slot + 2) != 7) {
		return;
	}
	other = (char*) 0x7f4ca2;
	v = 0;
	do {
		if (v >= *(unsigned char*) 0x6a375c) {
			return;
		}
		if ((*other == 6 || *other == 7) && other - 2 != slot) {
			fill_dst = msg;
			fill_count = 0xf8;
			__asm {
            mov edi, fill_dst
            xor eax, eax
            mov ebx, fill_count
            lea ecx, [edi+edi*2]
            and ecx, 3
            sub ebx, ecx
            jle short L_fill_tail1
            rep stosb
            mov ecx, ebx
            and ebx, 3
            shr ecx, 2
            rep stosd
        L_fill_tail1:
            add ecx, ebx
            rep stosb
        }
			*(int*) (msg + 0x2c) = g_7f4c00.b;
			*(int*) (msg + 0x28) = g_7f4c00.a;
			*(short*) (msg + 0x34) = g_7f4c00.d;
			*(int*) (msg + 0x30) = g_7f4c00.c;
			*(unsigned char*) (msg + 4) = 0x69;
			*(int*) ((char*) msg + 8) = *(int*) (other + 2);
			*(int*) (msg + 0xc) = -1;
			*(unsigned char*) (msg + 0x36) = 9;
			*(short*) (msg + 0x2c) = 7;
			*(int*) (msg + 0x2e) = 0;
			if (*(char*) (slot + 2) == 5) {
				limit = gm_RandomMod(8);
				fcn_00500bb0(msg + 0x28, gm_RandomMod(4), limit * 7, 0);
			}
			*(char*) (msg + 0x58) = *((unsigned char*)&a0 + 3);
			*(int*) (msg + 0x5c) = *(int*) (slot + 4);
			fcn_004c5530(msg);
			v++;
		}
		other += 0x21c;
	} while ((int) other < 0x85a0a2);
}

#pragma optimize("", on)
