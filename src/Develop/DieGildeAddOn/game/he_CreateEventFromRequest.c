


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xa0
struct blob160 {
	int v[0x28];
};

// SIZE 0x14c
#include <string.h>
#include "Develop/DieGildeAddOn/game/he_action.h"





















// SIZE 0xf8
struct spawn {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int value;
	int params[6];
	struct pos14 pos;
	unsigned char flags;
	char pad37;
	int extra[8];
	struct blob160 blob;
};

extern void (__cdecl* he_EventCreateHandlers[])(HE_ACTION*);
extern char he_EventDispatchHandlers[];
#include "Develop/client_types.h"

extern unsigned char* g_7d1980[];
extern int g_7749d0;
extern int he_LastEventSlot;
extern int g_7749d8;
extern int g_7dc424;

char* __cdecl gm_LookupEntityRecordById(int);

/* ADDRESS: GOLDDE 0x0052c660 */
HE_ACTION* __cdecl he_CreateEventFromRequest(struct spawn* t)
{
	char* e;
	int i;
	int j;
	int k;
	HE_ACTION* u;

	e = 0;
	if (t->kind >= 0xa7 || he_EventCreateHandlers[t->kind] == 0 || ((int*)he_EventDispatchHandlers)[t->kind] == 0) {
		return 0;
	}
	if (t->owner != -1) {
		e = gm_LookupEntityRecordById(t->owner);
		if (e == 0) {
			return 0;
		}
	}
	for (i = 0; i < 1024; i++) {
		if (((HE_ACTION*)he_ActionSlots)[i].kind == 0) {
			break;
		}
	}
	if (i == 1024) {
		return 0;
	}
	u = &((HE_ACTION*)he_ActionSlots)[i];
	if (i > he_LastEventSlot) {
		he_LastEventSlot = i;
	}
	if (t->owner == -1) {
		u->owner = -1;
		u->house = 0xffff;
	} else {
		u->owner = *(int*) (e + 4);
		u->house = *(unsigned short*) e;
	}
	if (t->flags & 8) {
		for (j = 0; j < 256; j++) {
			if (((HE_ACTION**)g_7d1980)[j] == 0) {
				break;
			}
		}
		if (j == 256) {
			return 0;
		}
		((HE_ACTION**)g_7d1980)[j] = u;
		if (j > g_7749d8) {
			g_7749d8 = j;
		}
	}
	u->kind = t->kind;
	u->serial = g_7749d0++;
	u->unk_10 = t->value;
	for (k = 0; k < 12; k++) {
		u->unk_14[k] = t->params[k];
	}
	memcpy(u->position, &t->pos, sizeof(t->pos));
	u->flags = t->flags;
	u->unk_70 = 0;
	u->slot = 0;
	u->data = 0;
	u->unk_84 = -1;
	for (k = 0; k < 8; k++) {
		u->unk_8c[k] = t->extra[k];
	}
	memcpy(u->unk_ac, &t->blob, sizeof(t->blob));
	he_EventCreateHandlers[t->kind](u);
	g_7dc424++;
	return u;
}
