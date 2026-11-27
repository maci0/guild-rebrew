#include <string.h>
#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"

extern char g_6812d0[][32];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl d3_PickRandomSceneObjectByName(char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
char* __cdecl ch_CreateAction(char*, int, int);


/* ADDRESS: GOLDTL 0x004bc410 */
void __cdecl ch_SpawnAmbientLivestock(AMBIENT_ANIMAL_SLOT* entry, int kind)
{
	float pos[4];
	char buf[0x80];
	char* ent;
	char* obj;

	fcn_0064d41a(buf, "dummy_%s", g_6812d0[kind]);
	ent = d3_PickRandomSceneObjectByName(buf);
	if (ent == 0)
		return;
	d3_TransformPoint(ent, ent + 0x4c, pos);
	if (kind == 3)
		strcpy(buf, "kuh_KUH");
	else if (kind == 7)
		strcpy(buf, "pferd_PFERD");
	else if (kind == 6)
		strcpy(buf, "schwein_SCHWEIN");
	obj = ch_CreateAtPosition(buf, pos);
	entry->objekt = obj;
	if (obj != 0) {
		*(float*) (obj + 0x1a0) = 1.0f;
		entry->pos[0] = pos[0];
		entry->pos[1] = pos[1];
		entry->pos[2] = pos[2];
		entry->kind = kind;
		*(int*) (entry->objekt + 4) = 2;
		*(int*) (*(char**) (entry->objekt + 0x34) + 0x224) = 0;
		ch_CreateAction(entry->objekt, 0x38, 1);
	}
}
