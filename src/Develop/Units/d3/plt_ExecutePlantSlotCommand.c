#include "Develop/Units/d3/d3_object.h"
extern int g_7728f8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* lpGebaeudePROT;
extern signed char d3_BuildingCategorySceneIndices[];

#include "Develop/DieGildeAddOn/auxillary/plant.h"
int __cdecl plt_CheckZoneAvailability(void*, unsigned int, unsigned int, unsigned int);
char* __cdecl plt_FindRecord(void*, unsigned int, unsigned int);
char* __cdecl plt_SetPlantMapSlot(void*, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl d3_SelectSceneContext(int, int);

void __cdecl init_SetPflanzenMap(char*, int);


/* ADDRESS: GOLDTL 0x004ca0c0 */
/* ADDRESS: GOLDDE 0x004b78a0 */
int __cdecl plt_ExecutePlantSlotCommand(int cmd, char* result)
{
	char status;
	void* entity;
	char* rec;
	char* found;
	int needs_create;
	int saved;

	saved = d3_CurrentContextIndex;
	status = '\x02';
	found = (char*) 0x0;
	needs_create = 0;

	if (nt_ClientSocket != -1)
		g_7728f8 = *(int*) (cmd + 0x10);
	entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x14));
	if (entity != (void*) 0x0) {
		rec = plt_FindPlantInfo(*(unsigned short*) (cmd + 0x1a));

		if ((rec == (char*) 0x0) || (*(unsigned char*) (cmd + 0x1c) != 0) ||
			(plt_CheckZoneAvailability(
				 *(void**) ((char*) entity + 0x71),
				 *(unsigned char*) (cmd + 0x18),
				 *(unsigned char*) (cmd + 0x19),
				 (unsigned char) rec[0x42]
			 ) != 0)) {
			needs_create = 1;
		}

		if (*(unsigned char*) (cmd + 0x1c) != 0) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if ((found != (char*) 0x0) && (*(int*) (found + 0x10) != -1)) {
				return 1;
			}
		}
		else if (*(int*) (cmd + 0x1d) != -1) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if (found != (char*) 0x0 && *(int*) (found + 0x10) == *(int*) (cmd + 0x1d)) {
				d3_SelectSceneContext(d3_BuildingCategorySceneIndices[lpGebaeudePROT[*(unsigned char*) entity + *(unsigned char*) entity * 0x24c]], 1);
				d3_DestroyObject((D3_OBJECT*) (*(void**) (found + 0x14)));
				*(void**) (found + 0x14) = 0;
				init_SetPflanzenMap(found, 0);
				*(int*) (found + 0x10) = -1;
				d3_SelectSceneContext(saved, 1);
			}
			if (result == (char*) 0x0) {
				return 0;
			}
			*(char**) (result + 6) = found;
			*result = '\x01';
			result[1] = '\x05';
			return 0;
		}

		if (needs_create != 0) {
			d3_SelectSceneContext(d3_BuildingCategorySceneIndices[lpGebaeudePROT[*(unsigned char*) entity + *(unsigned char*) entity * 0x24c]], 1);
			found = plt_SetPlantMapSlot(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19),
				*(unsigned short*) (cmd + 0x1a),
				*(unsigned char*) (cmd + 0x1c)
			);
			d3_SelectSceneContext(saved, 1);
		}

		if (found != (char*) 0x0) {
			status = '\x01';
			*(int*) (found + 4) = *(int*) ((char*) entity + 1);
			if (*(unsigned char*) (cmd + 0x1c) != 0) {
				*(int*) (found + 0x10) = *(int*) (cmd + 0x1d);
			}
		}
	}

	if (result != (char*) 0x0) {
		*(char**) (result + 6) = found;
		*result = status;
		result[1] = '\x05';
	}

	return 0;
}
