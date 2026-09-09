#include <stdio.h>
#include "../../Units/Error/error.h"

void* __cdecl gm_LookupEntityRecordById(int);
extern unsigned short g_default_value_b;
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void __cdecl InitBuildingTypeTable(void);

/* Office slot table at 0x101de5a0, 42 entries of 0x18 bytes. */
#pragma pack(push, 1)
// SIZE 0x18
typedef struct {
	char type;         /* +0 */
	char pad0[3];
	int entityId;      /* +4 */
	char role;         /* +8 */
	char pad1[3];
	int count;         /* +0xc */
	char state;        /* +0x10 */
	char pad2[3];
	int assignmentId;  /* +0x14 */
} OfficeSlot;
#pragma pack(pop)

extern OfficeSlot g_office_slots[];

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000B820
// amt_FindEntity26

void __cdecl amt_FindEntity26(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		/* asm checks byte at slot+8 (role); stores dword at slot+4 (entityId) */
		if (g_office_slots[i].role == 0x26) {
			g_office_slots[i].entityId = val;
			return;
		}
	}
}

/* Searches for an entity with type 0x27 (specific entity class)
 * matching the given value. Used for office-related lookups. */

// FUNCTION: SERVER 0x1000B850
// amt_FindEntity27

void __cdecl amt_FindEntity27(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (g_office_slots[i].role == 0x27) {
			g_office_slots[i].entityId = val;
			return;
		}
	}
}

/* Swaps two office holders. Exchanges position assignments
 * between the entities referenced in the param array. Returns 0
 * on success, or non-zero if the swap is invalid. */

// FUNCTION: SERVER 0x1000b880
// amt_SwapOfficeHolders

int __cdecl amt_SwapOfficeHolders(int* arg1)
{
	OfficeSlot* slot_a;
	OfficeSlot* slot_b;
	char* ent_a;
	char* ent_b;
	char* ent_c;
	int i;

	ent_a = (char*) gm_LookupEntityRecordById(arg1[0]);
	if (ent_a == 0)
		return 0;
	if (*(int*) (ent_a + 0x194) < *(int*) ((char*) arg1 + 6))
		return 0;

	/* find office slot A by type byte */
	i = 0;
	while (1) {
		if (g_office_slots[i].type == *((char*) arg1 + 4)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_a = &g_office_slots[i];
	if (slot_a == 0) {
		return 0;
	}
	ent_b = (char*) gm_LookupEntityRecordById(slot_a->entityId);
	if (ent_b == 0) {
		return 0;
	}

	/* find office slot B by type byte */
	i = 0;
	while (1) {
		if (g_office_slots[i].type == *((char*) arg1 + 5)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_b = &g_office_slots[i];
	if (slot_b == 0) {
		return 0;
	}
	ent_c = (char*) gm_LookupEntityRecordById(slot_b->entityId);
	if (ent_c == 0) {
		return 0;
	}
	*(char*) (ent_b + 0x166) = slot_b->role;
	*(char*) (ent_c + 0x166) = slot_a->role;
	i = slot_a->entityId;
	slot_a->entityId = slot_b->entityId;
	slot_b->entityId = i;
	*(int*) (ent_a + 0x194) -= *(int*) ((char*) arg1 + 6);
	return 1;
}

/* Clears all entity links for an office position. Removes
 * the holder and resets associated entity references. */

// FUNCTION: SERVER 0x1000b990
// amt_ClearEntityLinks

int __cdecl amt_ClearEntityLinks(char* entity)
{
	OfficeSlot* slot;
	unsigned short default_val;
	int i;
	int result;
	int state_tmp;

	default_val = (unsigned short) g_default_value_b;
	result = 0;
	slot = (OfficeSlot*) 0x101de5a0;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].entityId == *(int*) (entity + 4)) {
			slot[i].entityId = -1;
			slot[i].assignmentId = -1;
			state_tmp = (default_val > 0xb) ? 4 : 3;
			slot[i].state = (char) state_tmp;
			slot[i].count = 0;
			result |= 1;
		}
		else if (slot[i].assignmentId == *(int*) (entity + 4)) {
			slot[i].assignmentId = -1;
			slot[i].state = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if (slot[i].role == *(char*) (entity + 0x168)) {
				if (slot[i].count > 0) {
					slot[i].count--;
					result |= 1;
				}
			}
		}
	}
	*(char*) (entity + 0x166) = 0;
	*(char*) (entity + 0x169) = 0;
	*(char*) (entity + 0x168) = 0;
	return result;
}

/* Updates entity links for an office assignment. Sets up
 * the bidirectional references between the office slot and
 * the entity holding it. */

// FUNCTION: SERVER 0x1000ba30
// amt_UpdateEntityLinks

void __cdecl amt_UpdateEntityLinks(char* entity, int arg2)
{
	OfficeSlot* slot;
	unsigned short default_val;
	int i;
	int result;

	default_val = (unsigned short) g_default_value_b;
	result = 0;
	slot = (OfficeSlot*) 0x101de5a0;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].entityId == *(int*) (entity + 4) && arg2 != 0) {
			slot[i].entityId = -1;
			slot[i].assignmentId = -1;
			slot[i].state = (default_val > 0xb) ? 4 : 3;
			slot[i].count = 0;
			result |= 1;
		}
		else if (slot[i].assignmentId == *(int*) (entity + 4)) {
			slot[i].assignmentId = -1;
			slot[i].state = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if (slot[i].role == *(char*) (entity + 0x168)) {
				if (slot[i].count > 0) {
					slot[i].count--;
					result |= 1;
				}
			}
		}
	}
	if (arg2 != 0) {
		*(char*) (entity + 0x166) = 0;
		*(char*) (entity + 0x169) = 0;
	}
	*(char*) (entity + 0x168) = 0;
}

/* File I/O loader for office data (Aemter). Reads office
 * holder assignments from a save file via VFS and populates
 * the runtime office tables. */

char s_amt_fio_LoadAemter____Can_t_load_1002a0c8[] = "amt_fio_LoadAemter(): Can't load count";
char s_D__Develop_DieGildeAddOn_game_ae_1002a0a0[] = "D:\\Develop\\DieGildeAddOn\\game\\aemter.c";
char s_amt_fio_LoadAemter____count_read_1002a06c[] = "amt_fio_LoadAemter(): count read is %i, expected %i";
char s_amt_fio_LoadAemter____Can_t_load_1002a048[] = "amt_fio_LoadAemter(): Can't load id";
char s_amt_fio_LoadAemter____Can_t_load_1002a01c[] = "amt_fio_LoadAemter(): Can't load mplayerid";
char s_amt_fio_LoadAemter____Can_t_load_10029ff4[] = "amt_fio_LoadAemter(): Can't load mamt";
char s_amt_fio_LoadAemter____Can_t_load_10029fcc[] = "amt_fio_LoadAemter(): Can't load pcount";
char s_amt_fio_LoadAemter____Can_t_load_10029fa4[] = "amt_fio_LoadAemter(): Can't load status";
char s_amt_fio_LoadAemter____Can_t_load_10029f78[] = "amt_fio_LoadAemter(): Can't load msetter";
extern int __cdecl sprintf(char*, const char*, ...);

