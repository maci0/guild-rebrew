#include <string.h>
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern pos14_7f4c00 gm_GameTime;

struct unit;

struct unit* __cdecl he_StartHandlungSearch(int n, ...);
int __cdecl gm_RandomMod(unsigned short n);
unsigned char* __cdecl gv_FindLowestCostSlot(char* e, unsigned char lim);
int __cdecl gm_GetEntitySlotIndex(char* a, void* e);
void __cdecl cm_SendCopyEntityData(int a1);

/* ADDRESS: GOLDTL 0x004831f0 */
void __cdecl ai_StartGrabpflege(char* obj)
{
	ENTITY_RECORD* p;
	char* e;
	char* found;
	char* parent;
	char* q;
	char* r;
	int mode;
	char s[0xf8];

	mode = gm_GameTime.b;
	if ((short) mode != 7 && (short) mode != 0xc && (short) mode != 0x12) {
		*(int*) (obj + 0x1b4) &= ~0x800;
		return;
	}
	if (*(int*) (obj + 0x1b4) & 0x800) {
		return;
	}
	*(int*) (obj + 0x1b4) |= 0x800;
	if (he_StartHandlungSearch(2, 0, 0x8d, 3, *(int*) ((char*) *(int*) (obj + 0x16c) + 1)) != 0) {
		return;
	}
	e = (char*) gv_FindLowestCostSlot((char*) *(int*) (obj + 0x16c),
	    (unsigned char) (gm_RandomMod(0x40) + 0x80));
	if (e == 0) {
		return;
	}
	found = 0;
	p = (ENTITY_RECORD*) gm_EntitySlotTable;
	do {
		if ((int) &p->unk_17c >= 0x85a21c) {
			break;
		}
		if (p->entity_index != 0xffff) {
			parent = p->unk_16c;
			if (parent == (char*) *(int*) (obj + 0x16c)) {
				if (p->unk_165[0] != 0) {
					q = *(char**) p->unk_17c;
					if (q == 0 || *(unsigned char*) q == 4 || *(unsigned char*) q == 0x8c) {
						r = *(char**) (p->unk_17c + 8);
						if (r != 0 && *(int*) (r + 0x2c) == *(int*) (parent + 1)) {
							found = (char*) p;
						}
					}
				}
			}
		}
		p++;
	} while (found == 0);
	if (found == 0) {
		return;
	}
	{
		char* c;

		memset(s, 0, sizeof(s));
		c = (char*) *(int*) (obj + 0x16c);
		*(char*) (s + 4) = 0x8d;
		*(int*) (s + 8) = *(int*) (*(unsigned short*) (c + 0x27) * 0x21c + 0x7f4ca4);
		*(int*) (s + 0xc) = *(int*) (c + 1);
		*(int*) (s + 0x28) = gm_GameTime.a;
		*(int*) (s + 0x2c) = gm_GameTime.b;
		*(int*) (s + 0x30) = gm_GameTime.c;
		*(unsigned short*) (s + 0x34) = (unsigned short) gm_GameTime.d;
		*(char*) (s + 0x36) = 1;
		*(int*) (s + 0x5c) = *(int*) e;
		*(char*) (s + 0x60) = (char) gm_GetEntitySlotIndex(*(char**) (c + 0x65), e);
		*(int*) (s + 0x38) = *(int*) (found + 4);
		cm_SendCopyEntityData((int) s);
	}
}
