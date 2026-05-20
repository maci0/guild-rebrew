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

// STUB: SERVER 0x10016460
// gm_StartEntityQuery

unsigned short* __cdecl gm_StartEntityQuery(int param_1, int param_2, int param_3, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (DAT_101de450 == 0) {
		return (unsigned short*) 0;
	}

	flag1 = 0;
	flag2 = 0;

	DAT_10030b94 = 0x7fff;
	DAT_10030b98 = -1;
	DAT_10030b9c = (short) 0xffff;
	DAT_10030b9e = (char) 0xff;
	DAT_1003545e = 0;
	DAT_1003545c = flag1;
	DAT_1003545d = flag2;
	DAT_10035454 = 1;
	DAT_10035458 = 0;
	DAT_100a8c38 = 0;

	if (param_2 > 0) {
		arg_ptr = &param_3;

		for (i = param_2; i > 0; i--) {
			unsigned char ftype;

			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				arg_ptr++;
				DAT_10030b94 = *(unsigned short*) arg_ptr;
				break;
			case 1:
				DAT_10030b98 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				DAT_10030b9c = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 3:
				DAT_10030b9e = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				DAT_1003545e = 1;
				break;
			case 5:
				flag2 = 1;
				break;
			case 6:
				flag1 = 1;
				break;
			case 7:
				break;
			}
		}

		DAT_1003545c = flag1;
		DAT_1003545d = flag2;

		if (flag1 == 0) {
			goto check_container;
		}

		if (flag2 != 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\objekte", 0xb66, "query flags conflict", 1);
			return (unsigned short*) 0;
		}

		DAT_10035468 = DAT_100a8c34;
		return gm_NextEntityQueryMatch();
	}

check_container:
	if (param_1 != 0) {
		DAT_10035468 = DAT_100a8c34;
		return gm_NextEntityQueryMatch();
	}

	return (unsigned short*) 0;
}

/* Allocates an object slot in an entity's inventory.
 * Finds the next free slot and returns its index. */
