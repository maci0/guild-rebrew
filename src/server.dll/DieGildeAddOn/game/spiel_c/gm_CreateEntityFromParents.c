#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl __ftol(void);

typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
;
void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl _getpid(void);
void __cdecl vfs_EntityCleanup(char*);
void __cdecl free_block(int);
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);

// STUB: SERVER 0x10018850
// gm_CreateEntityFromParents

int __cdecl gm_CreateEntityFromParents(int father_id, int mother_id, int gender, int entity_type, int location)
{
	char work_buf[0x41c];
	int var_10;
	int var_14;
	int var_18;
	int var_1c;
	int var_20;
	int var_24;
	int var_28;

	(void) work_buf;

	var_10 = 0;
	var_14 = 0;
	var_18 = 0;
	var_1c = 0;
	var_20 = 0;
	var_24 = 0;
	var_28 = 0;

	return 0;
}

/* Queries the sum of a specific field across entities
 * matching a filter. Used for aggregate calculations
 * like total production or population counts. */
