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

extern int g_item_def_table;
extern int g_next_object_id;
extern int g_object_count;
extern int g_current_year;
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern char* gm_AllocateObjectSlot(void);
extern short* gm_ResolveParentEntity(short*);

// STUB: SERVER 0x10016760
// gm_AllocObjekt

char* __cdecl gm_AllocObjekt(int param_1, int param_2, int param_3)
{
	int dynamic_parent;
	int existing_parent;
	int static_parent;
	char* item_def_ptr;
	char buf[0x400];
	char* esi;
	int resolve_result;
	int last_node;
	int* edi;
	char* ebx;

	esi = 0;
	existing_parent = 0;
	dynamic_parent = 0;
	static_parent = 0;
	if (g_item_def_table == 0) {
		return 0;
	}
	if (param_1 == -1) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0xcb2,
			"gm_AllocObjekt(): Versuch Objekt au\xdf"
			"erhalb einer Hirachie zu erzeugen",
			1
		);
		return 0;
	}
	resolve_result =
		gm_ResolveEntityById((void**) &dynamic_parent, (void**) &existing_parent, (void**) &static_parent, param_1);
	if (resolve_result == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb8, "gm_AllocObjekt(): Parent not found", 1);
		return 0;
	}
	if (dynamic_parent != 0) {
		edi = (int*) ((char*) dynamic_parent + 0x5d);
	}
	else if (existing_parent != 0) {
		edi = (int*) ((char*) existing_parent + 0x14);
	}
	else if (static_parent != 0) {
		edi = (int*) ((char*) static_parent + 0x178);
	}
	else {
		return 0;
	}
	if (edi != 0) {
		resolve_result = *edi;
		if (resolve_result != 0) {
			do {
				last_node = resolve_result;
				resolve_result = *(int*) (last_node + 0x3f);
			} while (resolve_result != 0);
			esi = gm_AllocateObjectSlot();
			if (esi == 0) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0xcd4,
					"gm_AllocObjekt(): Kein Platz mehr",
					1
				);
				return 0;
			}
			*(int*) (last_node + 0x3f) = (int) esi;
		}
		else {
			esi = gm_AllocateObjectSlot();
			if (esi == 0) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0xcdd,
					"gm_AllocObjekt(): Kein Platz mehr",
					1
				);
				return 0;
			}
			*edi = (int) esi;
		}
	}
	item_def_ptr = (char*) (g_item_def_table + param_2 * 0x41);
	*(short*) esi = (short) param_2;
	sprintf(buf, "----->ObjID= %i ObjProt= %i", g_next_object_id, param_2 & 0xffff);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcee, buf, 8);
	*(int*) (esi + 2) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	if (dynamic_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) dynamic_parent + 1);
	}
	else if (existing_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) existing_parent + 0xa);
	}
	else if (static_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) static_parent + 4);
	}
	*(int*) (esi + 6) = param_1;
	*(int*) (esi + 0xe) = param_3;
	esi[0x12] = 0x64;
	esi[0x13] = 0;
	*(int*) (esi + 0x14) = 0;
	*(int*) (esi + 0x3f) = 0;
	g_object_count = g_object_count + 1;
	ebx = esi + 0x1c;
	memset(ebx, 0, 31);
	if (param_2 > 0x160) {
		switch (param_2) {
		case 0x174:
		case 0x176:
			*(int*) (esi + 0x20) = 6;
			break;
		case 0x24b:
		case 0x256:
		case 0x266:
			*(int*) (ebx) = 0;
			*(int*) (esi + 0x20) = 0;
			break;
		default:
			break;
		}
	}
	else if (param_2 == 0x160) {
		*(int*) (esi + 0x20) = 0xf;
	}
	else {
		switch (param_2) {
		case 0xb8:
			*ebx = 6;
			break;
		case 300:
			*(int*) (ebx) = -1;
			*(int*) (esi + 0x20) = -1;
			*(int*) (esi + 0x24) = -1;
			*(int*) (esi + 0x28) = g_current_year - 1;
			break;
		case 0x12d:
			*(int*) (ebx) = -1;
			*(int*) (esi + 0x20) = -1;
			*(int*) (esi + 0x24) = -1;
			*(int*) (esi + 0x28) = -1;
			break;
		case 0x134:
		case 0x135:
		case 0x136:
			if (dynamic_parent != 0) {
				int eax;
				eax = *(unsigned short*) ((char*) dynamic_parent + 0x27);
				eax = eax * 3;
				eax = eax * 5;
				eax = eax * 9;
				*(int*) (esi + 0xa) = *(int*) (eax * 4 + 0x100358a4);
			}
			else if (existing_parent != 0) {
				resolve_result = (int) gm_ResolveParentEntity((short*) existing_parent);
				*(int*) (esi + 0xa) = *(int*) (resolve_result + 4);
			}
			else if (static_parent != 0) {
				*(int*) (esi + 0xa) = *(int*) ((char*) static_parent + 4);
			}
			resolve_result = gm_ResolveEntityById(
				(void**) &dynamic_parent,
				(void**) &existing_parent,
				(void**) &static_parent,
				param_1
			);
			while (resolve_result != 0 && dynamic_parent == 0) {
				if (existing_parent != 0) {
					param_1 = *(int*) ((char*) existing_parent + 6);
				}
				else if (static_parent != 0) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
						0xd3d,
						"gm_AllocObjekt(): Karren in Spieler erzeugt?!?",
						1
					);
				}
				resolve_result = gm_ResolveEntityById(
					(void**) &dynamic_parent,
					(void**) &existing_parent,
					(void**) &static_parent,
					param_1
				);
			}
			esi[0x28] = 0;
			esi[0x31] = 2;
			if (dynamic_parent != 0) {
				*(int*) (ebx) = *(int*) ((char*) dynamic_parent + 1);
			}
			else {
				*(int*) (ebx) = -1;
			}
			{
				char* child_obj;
				child_obj = gm_AllocObjekt(*(int*) (esi + 2), 0x1dd, 1);
				*(int*) (child_obj + 0xe) = (int) (*(unsigned short*) esi) - 0x133;
				child_obj[0x1c] = *(unsigned char*) esi - 0x33;
			}
			break;
		case 0x15e:
			*(int*) (esi + 0x20) = 0xf;
			break;
		default:
			break;
		}
	}
	{
		char item_class = *item_def_ptr;
		if (item_class == 0x17 || item_class == 0x20 || item_class == 0x25) {
			*(int*) (ebx) = 0;
		}
	}
	return esi;
}

/* Adds or accumulates an object. If an object of the same
 * type exists, increments its quantity; otherwise allocates
 * a new object slot. */
