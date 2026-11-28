#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/entity.h"
extern int g_9b4a40[];

void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ch_SpawnEntityCharacter(char*, int, int*, int*, int, int*);
void __cdecl ch_UpdateHeldObjectAttachment(char*);
char* __cdecl gm_GetEquippedCombatGear(char*);
char* __cdecl gm_FindEntityActiveItem(char*);

/* ADDRESS: GOLDTL 0x004d1970 */
/* ADDRESS: GOLDDE 0x004bec60 */
void* __cdecl cut_SpawnCombatActor(int entityId, int dummyName)
{
	char* src;
	char* rec;
	char* obj;
	char* gear;
	char* activeItem;
	int i;
	int nameBuf;
	EntityStruct* pool;
	EntityStruct* scan;

	src = (char*) gm_LookupEntityRecordById(entityId);
	i = 0;
	pool = (EntityStruct*) g_9b4a40;
	scan = pool;
	do {
		if (scan->entity_index == 0xffff)
			goto found;
		i++; scan++;
	} while ((int) scan < (int) (pool + 32));
	return 0;
found:
	rec = (char*) &pool[i];
	pool[i] = *(EntityStruct*) src;
	*(int*) ((char*) g_9b4a40 + i * 0x21c + 0x1ac) = 0;
	*(int*) ((char*) g_9b4a40 + i * 0x21c + 0x184) = 0;
	ch_SpawnEntityCharacter(rec, d3_CurrentContextIndex, 0, 0, 0, (int*) dummyName);
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(unsigned char*) (obj + 0x240) = 4;
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(unsigned char*) (obj + 0x8d) |= 0x80;
	ch_UpdateHeldObjectAttachment(rec);
	gear = (char*) gm_GetEquippedCombatGear(src);
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	*(float*) (obj + 0x1a0) =
	    (float) ((double) *(unsigned char*) (gear + 9) * (2.0 / 7.0));
	obj = *(char**) ((char*) g_9b4a40 + i * 0x21c + 0x184);
	nameBuf = *(int*) (obj + 0x34);
	sprintf((char*) nameBuf, "cmb_%i", *(int*) ((char*) g_9b4a40 + i * 0x21c + 4));
	activeItem = (char*) gm_FindEntityActiveItem(src);
	if (activeItem != 0) {
		if (*(int*) (gear + 0x58) == 2) {
			*(int*) (activeItem + 0x20) = 6;
		} else {
			*(int*) (activeItem + 0x20) = 0x0f;
		}
	}
	return rec;
}
