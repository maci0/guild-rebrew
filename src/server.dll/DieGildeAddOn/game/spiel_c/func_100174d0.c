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
extern char* g_entity_ptr;
void __cdecl vfs_EntityCleanup(char*);
extern unsigned short* DAT_100a8c34;
extern int DAT_10035450;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* DAT_1014d8c0;
extern int DAT_100a8c30;
extern unsigned char DAT_10035439;
extern int DAT_1003543c;
extern char* DAT_101de450;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern WORD* DAT_10035468;
extern char DAT_10035454;
extern char DAT_1003545d;
extern int DAT_10035458;
extern int DAT_10030b94;
extern int DAT_10030b98;
extern short DAT_10030b9c;
extern char DAT_10030b9e;
extern char DAT_1003545c;
extern char DAT_1003545e;
extern int DAT_100a8c38;
extern int* DAT_101398a0;
extern int* DAT_1013989c;
extern char* g_array_base;

// STUB: SERVER 0x100174d0
// gm_AllocGebaeude

int __cdecl gm_AllocGebaeude(int building_type, int location_id)
{
	(void) building_type;
	(void) location_id;
	return 0;
}
