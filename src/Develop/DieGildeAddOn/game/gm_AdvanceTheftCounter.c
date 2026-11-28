#include <string.h>

#include "Develop/client_types.h"

extern char gm_EntitySlotTable[];
extern pos14_7f4c00 gm_GameTime;
extern int d3_CurrentContextIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int __cdecl gm_WalkEntityChain(int);
extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern unsigned short* __cdecl gm_QueryEntities(int, int, ...);
extern void __cdecl cm_RequestChangeBits(int, int, int, int, int);
extern void __cdecl io_FormatTextBuffer(char*, char*, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
extern void __cdecl cm_BeginPacketFieldDelta(char*, int);
extern void __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, short, void*);
extern void __cdecl cm_RequestChangeAttribute(void);
extern void __cdecl cm_SendCopyEntityData(void*);
extern unsigned short __cdecl gm_RandomMod(int);
extern void __cdecl gm_AddTime(void*, int, int, int);
extern char s_6903e8[];
extern unsigned char gm_PlayerCount;

#pragma optimize("y", off)


/* Erhoeht den Diebstahls-Zaehler eines Objekts und schickt je nach
 * Objektart ein Aendern-Paket 0x69 oder die Quickjump-Meldung. */
/* ADDRESS: GOLDTL 0x004f6d60 */
void __cdecl gm_AdvanceTheftCounter(unsigned int entityIndex)
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

	slot = (char*) &((ENTITY_RECORD*) gm_EntitySlotTable)[entityIndex & 0xffff];
	if (*(unsigned short*) slot == 0xffff) {
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
	v = gm_WalkEntityChain((int) entityIndex);
	count = *(unsigned char*) (slot + 0xd);
	limit = count + 1;
	if (limit > 0xa) {
		limit = 0xa;
	}
	if (v > *(int*) ((char*) 0x6653a0 + limit * 4) && count == 1) {
		found = gm_StartFilteredEntitySearch(1, 5, 0xf);
		if (found == 0) {
			return;
		}
		alloc = gm_QueryEntities((int) *(unsigned int*) ((char*) found + 0x5d), 2, 6, 0, 0x110);
		if (alloc == 0) {
			return;
		}
		cm_RequestChangeBits(*(int*) (slot + 4), 0x1c8, 4, 0x4000, 0);
		if (*(char*) (slot + 2) == 6 || *(char*) (slot + 2) == 7) {
			io_FormatTextBuffer(text, (char*) 0x161d, *(unsigned short*) slot);
			he_MessageBoxQuickjump(*(int*) (slot + 4), -1, text, 0, 0x5fd,
					       *(int*) ((char*) found + 1),
					       *(int*) ((char*) alloc + 2), 0, s_6903e8);
		}
		return;
	}
	if (v > *(int*) ((char*) 0x6653a0 + limit * 4) && count < 9) {
		*((unsigned char*)&entityIndex + 3) = count + 1;
		if (*(char*) (slot + 2) != 6 && *(char*) (slot + 2) != 7) {
			cm_BeginPacketFieldDelta(slot, *(int*) (slot + 4));
			cm_AppendPacketFieldDelta(1, 1, 0xd, ((unsigned char*)&entityIndex + 3));
			cm_RequestChangeAttribute();
		} else {
			{
			char* fill_dst;
			int fill_count;
			fill_dst = msg;
			fill_count = 0xf8;
			__asm {
                mov edi, fill_dst
                mov ebx, fill_count
                xor eax, eax
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
			}
			*(unsigned char*) (msg + 4) = 0x69;
			*(int*) (msg + 8) = *(int*) (slot + 4);
			*(int*) (msg + 0x28) = gm_GameTime.a;
			*(int*) (msg + 0x2c) = gm_GameTime.b;
			*(int*) (msg + 0x30) = gm_GameTime.c;
			*(short*) (msg + 0x34) = gm_GameTime.d;
			*(int*) (msg + 0xc) = -1;
			*(unsigned char*) (msg + 0x36) = 9;
			*(short*) (msg + 0x2c) = 7;
			*(int*) (msg + 0x2e) = 0;
			*(char*) (msg + 0x58) = *((unsigned char*)&entityIndex + 3);
			*(int*) (msg + 0x5c) = *(int*) (slot + 4);
			cm_SendCopyEntityData(msg);
		}
		if (*(char*) (slot + 2) != 5 && *(char*) (slot + 2) != 6
		    && *(char*) (slot + 2) != 7) {
			return;
		}
		other = (char*) 0x7f4ca2;
		v = 0;
		do {
			if (v >= gm_PlayerCount) {
				return;
			}
			if ((*other == 6 || *other == 7) && other - 2 != slot) {
				{
				char* fill_dst;
				int fill_count;
				fill_dst = msg;
				fill_count = 0xf8;
				__asm {
                mov edi, fill_dst
                mov ebx, fill_count
                xor eax, eax
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
				}
				*(int*) ((char*) msg + 8) = *(int*) (other + 2);
				*(int*) (msg + 0x28) = gm_GameTime.a;
				*(int*) (msg + 0x2c) = gm_GameTime.b;
				*(int*) (msg + 0x30) = gm_GameTime.c;
				*(unsigned char*) (msg + 4) = 0x69;
				*(int*) (msg + 0xc) = -1;
				*(unsigned char*) (msg + 0x36) = 9;
				*(short*) (msg + 0x34) = gm_GameTime.d;
				*(short*) (msg + 0x2c) = 7;
				*(int*) (msg + 0x2e) = 0;
				if (*(char*) (slot + 2) == 5) {
					gm_AddTime(msg + 0x28, gm_RandomMod(4),
						     gm_RandomMod(8) * 7, 0);
				}
				*(char*) (msg + 0x58) = *((unsigned char*)&entityIndex + 3);
				*(int*) (msg + 0x5c) = *(int*) (slot + 4);
				cm_SendCopyEntityData(msg);
				v++;
			}
			other += sizeof(ENTITY_RECORD);
		} while ((int) other < 0x85a0a2);
	}
}

#pragma optimize("", on)
