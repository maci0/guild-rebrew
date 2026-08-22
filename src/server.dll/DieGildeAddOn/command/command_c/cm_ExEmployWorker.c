
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

// SIZE 0x10
typedef struct coords_16 {
	int data[4];
} coords_16;

char* __cdecl sim_CreateCitizen(char, uint, int, uchar, uchar, ushort*);
void __cdecl sim_StartEntityQueryByType(uchar*);
int* __cdecl ahm_QueryEntityBuildingType(int);
int __cdecl sim_PriorityUpdate(char*, char*);
int __cdecl ahm_ResetEntityState(char*);

extern char s_cm_ExEmployWorker____Illegal_geb_1002d33c[];
extern char s_cm_ExEmployWorker____Illegal_gw__1002d318[];
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: employs a worker in a building. Resolves
 * building and worker entities, assigns the worker to the
 * building's production slot. */

// FUNCTION: SERVER 0x1000f730
int __cdecl cm_ExEmployWorker(int cmd, char* result)
{
	int random_seed;
	ushort* building_entity;
	char* citizen_entity;
	int* building_type_ptr;
	ushort* workplace_entity;
	char worker_type;

	workplace_entity = (ushort*) 0;
	*(int*) (cmd + 0x1f) = g_timestamp_0b6c;
	random_seed = rand();
	*(int*) (cmd + 0x23) = random_seed;
	srand(random_seed);
	building_entity = (ushort*) gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x10));
	if (building_entity == (ushort*) 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x4d3a,
			"cm_ExEmployWorker(): Illegal geb_id!", 1);
		return 1;
	}
	citizen_entity = (char*) gm_LookupEntityRecordById(*(int*) (cmd + 0x19));
	if (*(int*) (cmd + 0x14) != -1) {
		workplace_entity = (ushort*) gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x14));
		if (workplace_entity == (ushort*) 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x4d50,
				"cm_ExEmployWorker(): Illegal gw_id!", 1);
			return 1;
		}
	}
	else {
		if (citizen_entity != (char*) 0) {
			workplace_entity = *(ushort**) (citizen_entity + 0x170);
		}
	}

	if (citizen_entity == (char*) 0 || *(int*) (citizen_entity + 0x16c) != 0) {
		citizen_entity = sim_CreateCitizen(
			'\x06',
			(uint) *(unsigned char*) (cmd + 0x18),
			0x12,
			*(uchar*) (cmd + 0x1e),
			*(uchar*) (cmd + 0x1d),
			workplace_entity
		);
	}

	if (citizen_entity == (char*) 0) {
		if (result != (char*) 0) {
			*result = '\x02';
			result[1] = '\x01';
			*(char**) (result + 6) = citizen_entity;
		}
		return 2;
	}
	if (*(char*) (cmd + 0x1d) != '\0') {
		citizen_entity[0x165] = *(char*) (cmd + 0x1d);
	}
	if (*(char*) (cmd + 0x1e) != '\0') {
		citizen_entity[0x164] = *(char*) (cmd + 0x1e);
	}
	else {
		citizen_entity[0x164] = '\0';
	}
	citizen_entity[2] = *(char*) (cmd + 0x18);
	if (*(int*) (citizen_entity + 0x184) == 0 && workplace_entity != (ushort*) 0) {
		sim_StartEntityQueryByType((uchar*) workplace_entity);
	}
	worker_type = *(char*) (cmd + 0x1d);
	if (worker_type == '\x02' || worker_type == '\x01' || worker_type == '\x10' ||
		worker_type == '\x0f' || worker_type == '\x14' || worker_type == '\x13') {
		building_type_ptr = ahm_QueryEntityBuildingType((int) citizen_entity);
		if (*building_type_ptr == 0) {
			gm_AllocObjekt(*(int*) (citizen_entity + 4), 0x154, 1);
		}
	}
	else {
		building_type_ptr = ahm_QueryEntityBuildingType((int) citizen_entity);
		if (*building_type_ptr != 0) {
			gm_SubObjekt(*(void**) (citizen_entity + 4), (uint) *building_type_ptr, 1);
		}
	}
	*(ushort**) (citizen_entity + 0x16c) = building_entity;
	if (workplace_entity != (ushort*) 0) {
		sim_PriorityUpdate(citizen_entity, (char*) workplace_entity);
	}
	*(int*) (citizen_entity + 0x174) = 0;
	*(uint*) (citizen_entity + 0x1c8) = *(uint*) (citizen_entity + 0x1c8) & 0xffffdfff;
	ahm_ResetEntityState(citizen_entity);
	*(coords_16*) (citizen_entity + 0x1b4) = *(coords_16*) ((int) building_entity + 0x99);
	if (*(char*) (cmd + 0x1e) != '\0') {
		*(int*) (citizen_entity + 0x1b8) = *(int*) ((int) building_entity + 0x39);
	}
	if (result != (char*) 0) {
		*result = '\x01';
		result[1] = '\x01';
		*(char**) (result + 6) = citizen_entity;
	}
	return 0;
}
