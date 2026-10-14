typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

// SIZE 0x10
typedef struct coords_16 {
	int data[4];
} coords_16;

extern int g_14cbca0;
extern int g_699364;

int __cdecl rand(void);
void __cdecl srv_SeedRandom(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00508e40(int);
char* __cdecl sim_CreateCitizen(char, uint, int, uchar, uchar, ushort*);
char* __cdecl sim_StartEntityQueryByType(uchar*);
char* __cdecl fcn_005049a0(ushort*);
void __cdecl fcn_004fe470(int, int, int, int, int);
int* __cdecl ahm_QueryEntityBuildingType(char*);
char* __cdecl gm_AllocObjekt(int, int, int);
void __cdecl gm_SubObjekt(int, uint, int);
void __cdecl fcn_004ce9e0(char*);
int __cdecl sim_PriorityUpdate(char*, char*);
int __cdecl ahm_ResetEntityState(char*);

/* ADDRESS: GOLD 0x004cb250 */
/* ADDRESS: GOLDTL 0x004cbde0 */

int __cdecl fcn_004cbde0(int cmd, char* result)
{
	ushort* building_entity;
	char* citizen_entity;
	int* building_type_ptr;
	ushort* workplace_entity;
	char* q;
	char worker_type;

	workplace_entity = (ushort*) 0;
	if (g_14cbca0 != -1)
		g_699364 = *(int*) (cmd + 0x1f);
	else
		*(int*) (cmd + 0x23) = rand();
	srv_SeedRandom(*(int*) (cmd + 0x23));
	building_entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x10));
	if (building_entity == (ushort*) 0)
		return 1;
	citizen_entity = fcn_00508e40(*(int*) (cmd + 0x19));
	if (*(int*) (cmd + 0x14) != -1) {
		workplace_entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x14));
		if (workplace_entity == (ushort*) 0)
			return 1;
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
	if (*(int*) (citizen_entity + 0x184) == 0) {
		if (workplace_entity != (ushort*) 0) {
			q = sim_StartEntityQueryByType((uchar*) workplace_entity);
			if (q != 0 && *(int*) (q + 2) != -1)
				fcn_004fe470(*(int*) (citizen_entity + 4), *(int*) ((char*) workplace_entity + 1), *(int*) (q + 2), 0, 0);
		}
		else {
			q = fcn_005049a0(building_entity);
			if (q != 0 && *(int*) (q + 2) != -1)
				fcn_004fe470(*(int*) (citizen_entity + 4), *(int*) ((char*) building_entity + 1), *(int*) (q + 2), 0, 0);
		}
	}
	worker_type = *(char*) (cmd + 0x1d);
	if (worker_type == '\x02' || worker_type == '\x01' || worker_type == '\x10' ||
		worker_type == '\x0f' || worker_type == '\x14' || worker_type == '\x13') {
		building_type_ptr = ahm_QueryEntityBuildingType(citizen_entity);
		if (*building_type_ptr == 0) {
			gm_AllocObjekt(*(int*) (citizen_entity + 4), 0x154, 1);
			fcn_004ce9e0(citizen_entity);
		}
	}
	else {
		building_type_ptr = ahm_QueryEntityBuildingType(citizen_entity);
		if (*building_type_ptr != 0) {
			gm_SubObjekt(*(int*) (citizen_entity + 4), (uint) *building_type_ptr, 1);
			fcn_004ce9e0(citizen_entity);
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
