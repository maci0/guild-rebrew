


#include <string.h>

// SIZE 0xf8
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x26];
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	char pad60[0x98];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









int __cdecl he_HasNoActiveAction0x9b(ENTITY_RECORD*);
char* __cdecl gm_StartFilteredEntitySearch(int, ...);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl gm_RandomFloat01(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl cm_SendCopyEntityData(struct msg*);

int __cdecl he_TryTriggerAction0x9b(int id, ENTITY_RECORD* me)
{
	float a;
	float b;
	struct msg m;
	char text[0x400];
	char* e;
	ENTITY_RECORD* h;

	if (he_HasNoActiveAction0x9b(me) != 0) {
		e = gm_StartFilteredEntitySearch(1, 1, id);
		if (e != 0) {
			h = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			a = gm_GetEntitySkill((char*) h, 2);
			b = gm_GetEntitySkill((char*) me, 2);
			if (a - b * 0.5f + gm_RandomFloat01() * 0.5 < 0.8) {
				goto refuse;
			}
			a = gm_GetEntitySkill((char*) h, 3);
			b = gm_GetEntitySkill((char*) me, 3);
			if (a - b * 0.5f + gm_RandomFloat01() * 0.5 < 0.7) {
refuse:
				io_FormatTextBuffer(text, 0x4032, me->entity_index, me->entity_index);
				fcn_00545d40(h->entity_id, -1, text, 1, 0x5fa, "_NACHRICHTEN_DOMIZIL_07");
				io_FormatTextBuffer(text, 0x4034);
				fcn_00545d40(me->entity_id, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_09");
			} else {
				io_FormatTextBuffer(text, 0x4031, me->entity_index);
				fcn_00545d40(h->entity_id, -1, text, 1, 0x5fa, "_NACHRICHTEN_DOMIZIL_06");
				io_FormatTextBuffer(text, 0x4033);
				fcn_00545d40(me->entity_id, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_09");
				memset(&m, 0, sizeof(m));
				m.kind = 0x9b;
				m.owner = h->entity_id;
				m.target = id;
				m.who = me->entity_id;
				m.other = h->entity_id;
				m.code = 2;
				cm_SendCopyEntityData(&m);
				return 1;
			}
		}
	}
	return 0;
}
