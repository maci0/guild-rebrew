// FUNCTION: SERVER 0x1000f730
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), jump condition swap
// ORIGIN: GAME
// SIZE: 515
// CFLAGS: /O2 /Gd
// SYMBOL: _EmployWorkerAtBuilding

/*
// BLOCKER_DELTA: 436
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 515B
 *    CFlags: 
 *    Symbol: _EmployWorkerAtBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int EmployWorkerAtBuilding(int param_1,char *param_2)
 * 
 * {
 *   int random_seed;
 *   ushort *building_entity;
 *   char *citizen_entity;
 *   uint *building_type_ptr;
 *   int *extraout_EAX;
 *   ushort *workplace_entity;
 *   uint log_line;
 *   char worker_type;
 *   
 *                     / * Employs a worker at a building. Looks up building and optionally workplace
 *                        entity, creates citizen via CreateCitizen if needed, sets worker type and
 *                        gender, assigns to building, copies position coordinates from building to
 *                        citizen entity. * /
 *   workplace_entity = (ushort *)0x0;
 *   *(undefined4 *)(param_1 + 0x1f) = g_timestamp_0b6c;
 *   random_seed = rand();
 *   *(int *)(param_1 + 0x23) = random_seed;
 *   crt_thread_set_alt(random_seed);
 *   building_entity = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x10));
 *   if (building_entity == (ushort *)0x0) {
 *     citizen_entity = s_cm_ExEmployWorker____Illegal_geb_1002d33c;
 *     log_line = 0x4d3a;
 * LAB_1000f7a9:
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,log_line,citizen_entity,1);
 *     return 1;
 *   }
 *   citizen_entity = (char *)LookupEntityRecordById(*(int *)(param_1 + 0x19));
 *   if (*(int *)(param_1 + 0x14) == -1) {
 *     if (citizen_entity != (char *)0x0) {
 *       workplace_entity = *(ushort **)(citizen_entity + 0x170);
 *       goto LAB_1000f7ca;
 *     }
 *   }
 *   else {
 *     workplace_entity = StartFilteredEntitySearch(1,1,*(int *)(param_1 + 0x14));
 *     if (workplace_entity == (ushort *)0x0) {
 *       citizen_entity = s_cm_ExEmployWorker____Illegal_gw__1002d318;
 *       log_line = 0x4d50;
 *       goto LAB_1000f7a9;
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int g_timestamp_0b6c;

extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);
extern void* __cdecl StartFilteredEntitySearch(int, ...);
extern int __cdecl LookupEntityRecordById(int);
extern int __cdecl LogMessageInternal(const char*, uint, const char*, int);
extern char* __cdecl sim_CreateCitizen(char, uint, int, uchar, uchar);
extern void __cdecl StartEntityQueryByType(uchar*);
extern int* __cdecl QueryEntityBuildingType(int);
extern void* __cdecl AllocGameObject(int, uint, int);
extern int __cdecl SubObjekt(void*, uint, int);
extern int __cdecl priority_update(char*, char*);
extern int __cdecl reset_entity_state(char*);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExEmployWorker____Illegal_geb_1002d33c[];
extern char s_cm_ExEmployWorker____Illegal_gw__1002d318[];

int EmployWorkerAtBuilding(int param_1, char* param_2)
{
	int random_seed;
	ushort* building_entity;
	char* citizen_entity;
	int* building_type_ptr;
	ushort* workplace_entity;
	uint log_line;
	char worker_type;

	workplace_entity = (ushort*) 0;
	*(int*) (param_1 + 0x1f) = g_timestamp_0b6c;
	random_seed = rand();
	*(int*) (param_1 + 0x23) = random_seed;
	crt_thread_set_alt(random_seed);
	building_entity = (ushort*) StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x10));
	if (building_entity == (ushort*) 0) {
		citizen_entity = s_cm_ExEmployWorker____Illegal_geb_1002d33c;
		log_line = 0x4d3a;
	LAB_1000f7a9:
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, log_line, citizen_entity, 1);
		return 1;
	}
	citizen_entity = (char*) LookupEntityRecordById(*(int*) (param_1 + 0x19));
	if (*(int*) (param_1 + 0x14) == -1) {
		if (citizen_entity != (char*) 0) {
			workplace_entity = *(ushort**) (citizen_entity + 0x170);
		}
	}
	else {
		workplace_entity = (ushort*) StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x14));
		if (workplace_entity == (ushort*) 0) {
			citizen_entity = s_cm_ExEmployWorker____Illegal_gw__1002d318;
			log_line = 0x4d50;
			goto LAB_1000f7a9;
		}
	}

	if ((citizen_entity == (char*) 0) || (*(int*) (citizen_entity + 0x16c) != 0)) {
		citizen_entity = sim_CreateCitizen(
			'\x06',
			(uint) * (unsigned char*) (param_1 + 0x18),
			0x12,
			*(uchar*) (param_1 + 0x1e),
			*(uchar*) (param_1 + 0x1d)
		);
	}

	if (citizen_entity == (char*) 0) {
		if (param_2 != (char*) 0) {
			*param_2 = '\x02';
			param_2[1] = '\x01';
			*(char**) (param_2 + 6) = citizen_entity;
		}
		return 2;
	}
	if (*(char*) (param_1 + 0x1d) != '\0') {
		citizen_entity[0x165] = *(char*) (param_1 + 0x1d);
	}
	if (*(char*) (param_1 + 0x1e) == '\0') {
		citizen_entity[0x164] = '\0';
	}
	else {
		citizen_entity[0x164] = *(char*) (param_1 + 0x1e);
	}
	citizen_entity[2] = *(char*) (param_1 + 0x18);
	if ((*(int*) (citizen_entity + 0x184) == 0) && (workplace_entity != (ushort*) 0)) {
		StartEntityQueryByType((uchar*) workplace_entity);
	}
	worker_type = *(char*) (param_1 + 0x1d);
	if ((((worker_type == '\x02') || (worker_type == '\x01')) || (worker_type == '\x10')) ||
		((worker_type == '\x0f' || (worker_type == '\x14')) || (worker_type == '\x13'))) {
		building_type_ptr = QueryEntityBuildingType((int) citizen_entity);
		if (*building_type_ptr == 0) {
			AllocGameObject(*(int*) (citizen_entity + 4), 0x154, 1);
		}
	}
	else {
		building_type_ptr = QueryEntityBuildingType((int) citizen_entity);
		if (*building_type_ptr != 0) {
			SubObjekt(*(void**) (citizen_entity + 4), (uint) *building_type_ptr, 1);
		}
	}
	*(ushort**) (citizen_entity + 0x16c) = building_entity;
	if (workplace_entity != (ushort*) 0) {
		priority_update(citizen_entity, (char*) workplace_entity);
	}
	*(int*) (citizen_entity + 0x174) = 0;
	*(uint*) (citizen_entity + 0x1c8) = *(uint*) (citizen_entity + 0x1c8) & 0xffffdfff;
	reset_entity_state(citizen_entity);
	*(int*) (citizen_entity + 0x1b4) = *(int*) ((int) building_entity + 0x99);
	*(int*) (citizen_entity + 0x1b8) = *(int*) ((int) building_entity + 0x9d);
	*(int*) (citizen_entity + 0x1bc) = *(int*) ((int) building_entity + 0xa1);
	if (*(char*) (param_1 + 0x1e) != '\0') {
		*(int*) (citizen_entity + 0x1b8) = *(int*) ((int) building_entity + 0x39);
	}
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(char**) (param_2 + 6) = citizen_entity;
	}
	return 0;
}
