#include "Develop/DieGildeAddOn/game/spiel.h"



// SIZE 0xc
struct slot {
	int id;
	int item;
	unsigned char f8;
	unsigned char f9;
	unsigned char fa;
	unsigned char fb;
};

// SIZE 0x188
struct obj {
	char pad0[4];
	int handle;
	char pad8[0x17c];
	int shown;
};

extern unsigned short g_7f4c04;

struct obj* __cdecl gm_LookupEntityRecordById(int);

int __cdecl gm_IsEntityAtBuilding(struct obj*, int);
void __cdecl cm_SendEntityLookup(int);
void __cdecl cm_SendCancelCharacterActions(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl he_ReturnPoliticianFromJob(struct slot* s)
{
	struct obj* o;
	int r;

	if (s->id != -1) {
		o = gm_LookupEntityRecordById(s->id);
		if (o == 0) {
			goto clear;
		}
		gm_ResolveEntityById((void**) (&r), 0, 0, s->item);
		if (r == 0) {
			if (o->shown != 0) {
				cm_SendEntityLookup(s->id);
				cm_RequestChangeBits(o->handle, 0x1c8, 4, 0, 0x40000000);
			}
		clear:
			s->id = -1;
			s->item = -1;
			s->f8 = 0;
			s->f9 = 0;
			s->fa = 0;
			s->fb = 0;
			return 0;
		}
		if (gm_IsEntityAtBuilding(o, r) == 0 && g_7f4c04 < 0x16) {
			return 2;
		}
		if (o->shown != 0) {
			cm_SendCancelCharacterActions(o->handle);
			cm_SendEntityLookup(s->id);
		}
		s->id = -1;
		s->item = -1;
		s->f8 = 0;
		s->f9 = 0;
		s->fa = 0;
		s->fb = 0;
		cm_RequestChangeBits(o->handle, 0x1c8, 4, 0, 0x40000000);
	}
	return 0;
}
