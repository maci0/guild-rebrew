#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern int g_1002576c[];
extern int g_1002575c[];
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
extern char g_100a9820[];
extern char g_1014d8e0[];
extern char g_10139820[];
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_save_version;
extern int g_1002d4f0;
extern int g_1002d4f4;
extern char g_1002d4f8;
extern char g_1002d4fc;
extern int DAT_100a8c34;
extern int DAT_10035450;
int __cdecl ls_LoadGraveyardData(int param_1, int param_2);
int __cdecl ahm_AllocAhmInfo(int param_1, int param_2);
extern int g_file_version; /* 0x1002d4ec */
;
extern int g_entity_array_ptr; /* 0x1014d8c0 */
;
extern int g_101de454; /* 0x101de454 */
;
extern int g_101de55c; /* 0x101de55c */
;
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_101deae8;
extern int g_101deac0;
extern int g_101de560;
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov)
// ORIGIN: GAME
// SIZE: 728
// BLOCKER_DELTA: 535
// FUNCTION: SERVER 0x10012000
// ls_LoadGraveyardData

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

int __cdecl ls_LoadGraveyardData(int param_1, int param_2)
{
	int field_base;
	int ret;
	int ptr;
	int edi;
	int i;

	field_base = AllocGraveyardField(param_2);
	if (field_base == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) field_base, 4, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) (field_base + 4), 4, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) (field_base + 0x18), 1, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) (field_base + 0x19), 1, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) (field_base + 0x1a), 1, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ret = ls_ReadVfsDataChecked((void*) (field_base + 0x1b), 1, 1, (void*) param_1);
	if (ret == 0) {
		return 0;
	}
	ptr = *(int*) (field_base + 0x20);
	i = 0;
	if (0 < g_1002576c[*(int*) (field_base + 4)]) {
		edi = ptr + 0x14;
		do {
			ret = ls_ReadVfsDataChecked((void*) ptr, 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi - 0x10), 0x10, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) edi, 0x10, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x10), 5, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x18), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x1c), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x20), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x24), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x28), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 0x2c), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			i = i + 1;
			ptr = ptr + 0x44;
			edi = edi + 0x44;
		} while (i < g_1002576c[*(int*) (field_base + 4)]);
	}
	ptr = *(int*) (field_base + 0x1c);
	i = 0;
	if (0 < g_1002575c[*(int*) (field_base + 4)]) {
		edi = ptr + 8;
		do {
			ret = ls_ReadVfsDataChecked((void*) ptr, 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi - 4), 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) edi, 2, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 2), 2, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) (edi + 4), 1, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ret = ls_ReadVfsDataChecked((void*) &param_2, 4, 1, (void*) param_1);
			if (ret == 0) {
				return 0;
			}
			ptr = ptr + 0x14;
			i = i + 1;
			*(int*) (edi + 8) = *(int*) (field_base + 0x20) + param_2 * 0x44;
			edi = edi + 0x14;
		} while (i < g_1002575c[*(int*) (field_base + 4)]);
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap
// SIZE: 346
// FUNCTION: SERVER 0x100122e0
// ls_InitNewDynastyEntity

/* TODO: Add extern declarations for globals and called functions */

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 199

void ls_InitNewDynastyEntity(int param_1, int param_2, char* param_3, char* param_4)

{
	char random_char;
	int loop_index;
	unsigned int* fill_ptr;
	int var_2h;
	(void) var_2h;
	unsigned char stat_byte;

	if (param_1 == 0x15) {
		*(int*) (param_4 + 0x1cc) = *(int*) (param_4 + 0x1cc) | 0x1000;
		amt_FindEntity26(*(int*) (param_4 + 4));
	}
	else {
		*(int*) (param_4 + 0x1cc) = *(int*) (param_4 + 0x1cc) | 0x2000;
		amt_FindEntity27(*(int*) (param_4 + 4));
	}
	*(unsigned short*) (param_4 + 10) = (unsigned short) param_3;
	param_3 = g_100a9820;
	*(char*) (param_4 + 0xc) = 0;
	do {
		int row_offset = param_3 - g_100a9820;
		loop_index = 0;
		do {
			random_char = gm_RandomMod(0x40);
			g_100a9820[row_offset + loop_index] = random_char - 0x20;
			g_1014d8e0[row_offset + loop_index] = 0;
			loop_index++;
		} while (loop_index < 0x300);
		param_3 += 0x300;
	} while (param_3 < g_10139820);
	*(int*) (param_4 + 0x50) = 0x7fff;
	*(int*) (param_4 + 0x7c) = 0;
	*(int*) (param_4 + 0x58) = 0;
	fill_ptr = (unsigned int*) (param_4 + 0x5c);
	for (loop_index = 8; loop_index != 0; loop_index = loop_index + -1) {
		*fill_ptr = 0xffffffff;
		fill_ptr = fill_ptr + 1;
	}
	*(int*) (param_4 + 0x170) = 0;
	*(int*) (param_4 + 0x16c) = 0;
	*(int*) (param_4 + 0x1c) = 0x447a0000;
	*(int*) (param_4 + 0x14) = 0x3f800000;
	*(int*) (param_4 + 0x20) = 0x41400000;
	*(int*) (param_4 + 0x10) = 0x43a50000;
	*(int*) (param_4 + 0x18) = 0x447a0000;
	loop_index = 0;
	do {
		gm_RandomMod(0x2a);
		stat_byte = __ftol();
		*(unsigned char*) (param_4 + loop_index + 0x80) = stat_byte;
		loop_index = loop_index + 1;
	} while (loop_index < 5);
	*(char*) (param_4 + 0xd) = 9;
	gm_AddOrAccumulateObject(*(int*) (param_4 + 4), *(int*) (*(int*) 0x10035439 * 0x2f4 + 0x100a8c94), 16000000);
	gm_RandomMod(2);
	*(char*) (param_4 + 2) = 3;
	return;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 37
// FUNCTION: SERVER 0x10012440
// ls_ReadVfsDataChecked

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	unsigned int result;
	result = ReadVfsData(outBuffer, elementSize, elementCount, streamCtx);
	return result > 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 857
// ANALYSIS: ls_LoadSavegameHeader: Reads versioned savegame header from VFS stream. Allocates 0xE100 temp buffer, reads format version, player count, map name (32 bytes), timestamps, difficulty, player scores (8 entries for version > 0x10033), savegame description (96 bytes). Returns 1 on success, 0 on read failure.
// FUNCTION: SERVER 0x10012470
// ls_LoadSavegameHeader

int __cdecl ls_LoadSavegameHeader(int param_1, char* param_2)
{
	char* ebx;
	int i;

	ebx = (char*) m_AllocTracked(0xe100, &g_1002d4fc);
	if (!ls_ReadVfsDataChecked(param_2, 4, 1, (void*) param_1)) {
		return 0;
	}
	g_save_version = *(int*) param_2;
	if (!ls_ReadVfsDataChecked(param_2 + 4, 1, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 5, 0x20, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 0x28, 8, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 0x30, 1, 1, (void*) param_1)) {
		return 0;
	}
	if (g_save_version >= 0x10033) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x31, 1, 1, (void*) param_1)) {
			return 0;
		}
	}
	if (g_save_version >= 0x10028) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x32, 0xe, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x40, 0x10, 1, (void*) param_1)) {
			return 0;
		}
		if (g_save_version >= 0x10054) {
			if (!ls_ReadVfsDataChecked(param_2 + 0x50, 0x10, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x63, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x64, 4, 1, (void*) param_1)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x60, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x61, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x62, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x68, 4, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x6c, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x6d, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (g_save_version >= 0x1002b) {
			if (!ls_ReadVfsDataChecked(param_2 + 0x70, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x74, 4, 1, (void*) param_1)) {
				return 0;
			}
		}
		else {
			*(int*) (param_2 + 0x70) = -1;
			*(int*) (param_2 + 0x74) = -1;
		}
		if (g_save_version >= 0x10034) {
			i = 0;
			{
				char* score_ptr = param_2 + 0x78;
				do {
					if (!ls_ReadVfsDataChecked(score_ptr, 4, 1, (void*) param_1)) {
						return 0;
					}
					i = i + 1;
					score_ptr = score_ptr + 4;
				} while (i < 8);
			}
			ebx = *(char**) &ebx;
		}
		if (!ls_ReadVfsDataChecked(ebx, 0xe100, 1, (void*) param_1)) {
			return 0;
		}
	}
	if (ebx != (char*) 0) {
		m_FreeTracked(ebx);
	}
	if (g_save_version < 0x10025) {
		return 0;
	}
	if (g_save_version >= 0x10038) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x98, 4, 1, (void*) param_1)) {
			return 0;
		}
	}
	else {
		*(int*) (param_2 + 0x98) = 2;
	}
	if (g_save_version >= 0x10039) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x9c, 0x60, 1, (void*) param_1)) {
			return 0;
		}
	}
	else {
		*(int*) (param_2 + 0x9c) = g_1002d4f0;
		*(int*) (param_2 + 0xa0) = g_1002d4f4;
		*(char*) (param_2 + 0xa4) = g_1002d4f8;
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 282
// FUNCTION: SERVER 0x100127d0
// ls_LoadExistingEntities

// GLOBALS: SERVER 0x10035450

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
void __cdecl gm_CleanupObjectEntities(void);

int __cdecl ls_LoadExistingEntities(int param_1)
{
	int read_ok;
	int entity_index;
	int entity_count;
	int base;
	char* record_buf;
	int byte_offset;

	gm_CleanupObjectEntities();
	read_ok = ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) param_1);
	if (read_ok == 0) {
		return 0;
	}
	entity_index = 0;
	if (0 < entity_count) {
		base = DAT_100a8c34;
		byte_offset = 0;
		do {
			record_buf = (char*) (base + byte_offset);
			read_ok = ls_ReadVfsDataChecked(record_buf, 2, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 2, 4, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 6, 4, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 10, 4, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 0xe, 4, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 0x12, 1, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 0x13, 1, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			read_ok = ls_ReadVfsDataChecked(record_buf + 0x1c, 0x1f, 1, (void*) param_1);
			if (read_ok == 0) {
				return 0;
			}
			entity_index = entity_index + 1;
			byte_offset = byte_offset + 0x43;
		} while (entity_index < entity_count);
	}
	DAT_10035450 = entity_count;
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// GLOBALS: SERVER 0x100a8c34
// BLOCKER_DELTA: 274
// SIZE: 1463
// BLOCKER_DELTA: 1390
// ANALYSIS: ls_LoadBuildingEntityState: Resets all entities, then deserializes building entities from savegame stream. Per-entity: type byte, ID, name (32b), position, dimensions, owner, state fields. Special handling: 0x1E=farm (plant map), H/I/J=graveyard, K/L/M=office. Also loads auxiliary entity list with realloc. Returns 1 on success.
// FUNCTION: SERVER 0x100128f0
// ls_LoadBuildingEntityState

unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int param_1)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	unsigned int offset;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) param_1)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		offset = 0;
		neg1 = -1;
		do {
			esi = (char*) (offset + g_entity_array_ptr);

			if (!ls_ReadVfsDataChecked(esi, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x01, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x05, 0x20, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x25, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x27, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x29, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2b, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2f, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x34, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x35, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x39, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x3d, 4, 1, (void*) param_1)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ls_ReadVfsDataChecked(ebx, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ls_ReadVfsDataChecked(esi + 0x45, 4, 1, (void*) param_1)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ls_ReadVfsDataChecked(esi + 0x49, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ls_ReadVfsDataChecked(&dummy, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ls_ReadVfsDataChecked(esi + 0x4d, 4, 1, (void*) param_1)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x51, 4, 1, (void*) param_1)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x55, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(esi + 0x5a, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x5c, 1, 1, (void*) param_1)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) m_AllocTracked(0x600, (const char*) 0x1002d510);
				load_result = 0;
				do {
					if (!ls_ReadVfsDataChecked((void*) (load_result + *(int*) (esi + 0x71)), 4, 1, (void*) param_1)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 4 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 8 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 9 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xa + *(int*) (esi + 0x71)),
							2,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0x10 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xc + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xd + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					load_result += 0x18;
					*(int*) (load_result - 4 + *(int*) (esi + 0x71)) = 0;
				} while (load_result < 0x600);
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					load_result = ls_LoadGraveyardData(param_1, (int) esi);
				}
				else {
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
						return 0;
					}
					*(int*) (esi + 0x65) = AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					load_result = ahm_AllocAhmInfo(param_1, (int) esi);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
						return 0;
					}
					ahm_info = (int*) m_AllocTracked(0x3c, (const char*) 0x1002d504);
					*(int*) (esi + 0x65) = (int) ahm_info;
					*ahm_info = neg1;
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ls_ReadVfsDataChecked(esi + 0x99, 0x10, 1, (void*) param_1)) {
					return 0;
				}
			}
			else {
				int* state_ptr = (int*) (esi + 0x99);
				int zero = 0;
				*state_ptr = zero;
				*(int*) ((char*) state_ptr + 4) = zero;
				*(int*) ((char*) state_ptr + 8) = zero;
				*(int*) ((char*) state_ptr + 0xc) = zero;
				*(int*) (esi + 0xa5) = neg1;
				*state_ptr = *state_ptr | 1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
			offset += 0xa9;
		} while (current_index < entity_count);
	}

	if (!ls_ReadVfsDataChecked(&g_101de454, 4, 1, (void*) param_1)) {
		return 0;
	}

	g_101de55c = (int) realloc((void*) g_101de55c, g_101de454 * 0x60);

	load_result = 0;
	if (g_101de454 > 0) {
		current_index = 0;
		do {
			if (!ls_ReadVfsDataChecked((void*) (current_index + g_101de55c), 0x40, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((void*) (current_index + 0x40 + g_101de55c), 0x10, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked((void*) (current_index + 0x50 + g_101de55c), 0x10, 1, (void*) param_1)) {
				return 0;
			}
			load_result++;
			current_index += 0x60;
		} while (load_result < g_101de454);
	}

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout
// SIZE: 884
// FUNCTION: SERVER 0x10012eb0
// ls_LoadDynamicEntities

/* Game function - reads entity data records from VFS file */
// BLOCKER_DELTA: 807
// ANALYSIS: ls_LoadDynamicEntities: Iterates static entity slots (stride 0xAC), reads: slot index (2b), name (16b), position/state fields. Version-gated skill array (11 or 14 entries). Reads equipment, inventory, extended data. Sets default scale 1.0f for old saves. Returns 1 when past end address 0x1009b761.

int __cdecl ls_LoadDynamicEntities(void* file)
{
	char* rec;

	rec = (char*) 0x1009aca2;
	do {
		if (!ls_ReadVfsDataChecked(rec - 2, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x12, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x1002c) {
			if (!ls_ReadVfsDataChecked(rec + 0x26, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x32, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x36, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x3e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x42, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x46, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4e, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10014) {
			if (!ls_ReadVfsDataChecked(rec + 0x52, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x56, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x5a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x3a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x62, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x66, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x6a, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (g_file_version >= 0x10056) {
			if (!ls_ReadVfsDataChecked(rec + 0x5e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		else {
			*(int*) (rec + 0x5e) = 0x3f800000;
		}
		if (g_file_version >= 0x10015) {
			int count;
			int i;
			char* p;
			count = (g_file_version >= 0x10046) ? 0x11 : 0x0e;
			i = 0;
			p = rec + 0x72;
			if (count > 0) {
				do {
					if (!ls_ReadVfsDataChecked(p, 1, 1, (void*) file)) {
						return 0;
					}
					i++;
					p++;
				} while (i < count);
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x86, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x8a, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x9a, 0x0c, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0xa6, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10018) {
			if (!ls_ReadVfsDataChecked(rec + 0x6e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		rec += 0xac;
	} while (rec < (char*) 0x1009b762);

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout
// SIZE: 2268
// BLOCKER_DELTA: 2053
// GHIDRA: LoadStaticEntities
// ANALYSIS: Deserializes all static entities from savegame stream. Reads entity count, landmark pointers, then loops reading 70+ fields per entity with version-gated sections (g_save_format_version). Entity data at g_static_entities array, stride 0x21C bytes. Returns 1 on success, 0 on read failure.
// FUNCTION: SERVER 0x10013230
// ls_LoadEntities

/* GLOBAL: SERVER 0x1002d4ec */
extern int g_save_version;
/* GLOBAL: SERVER 0x10035434 */
extern int g_citizen_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

int __cdecl ls_LoadEntities(int param_1)
{
	int stream;
	int read_result;
	int inner_result;
	unsigned short entity_slot;
	int entity_index;
	int ref_value;

	stream = param_1;
	read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) param_1);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) &param_1, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	g_citizen_count = param_1;
	read_result = ls_ReadVfsDataChecked((void*) 0x10035470, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) 0x10035474, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	if (g_save_version > 0x10016) {
		read_result = (int) 0x10035478;
		do {
			inner_result = ls_ReadVfsDataChecked((void*) read_result, 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			read_result = read_result + 4;
		} while (read_result < (int) 0x10035498);
	}
	entity_index = 0;
	if (0 < param_1) {
		do {
			read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) stream);
			if (read_result == 0) {
				return 0;
			}
			read_result = (entity_slot & 0xffff) * 0x21c;
			*(unsigned short*) (read_result + 0x100358a0) = entity_slot;
			if (g_save_version < 0x1003e) {
				*(int*) (read_result + 0x10035aac) = -1;
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035aac), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a2), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a8), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a9), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358aa), 2, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358ac), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358ad), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b0), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b8), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358bc), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c0), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x1003a) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c8), 2, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358cc), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358d0), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10030) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358e0), 0x10, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f0), 2, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f8), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358fc), 0x20, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10023) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x1003591c), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035920), 5, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035928), 0xa8, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a04), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a05), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a06), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a07), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a08), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a09), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a0c) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a0c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a10) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a10), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a14), 2, 1, (void*) stream);
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a14), 4, 1, (void*) stream);
			}
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a1c) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a1c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a20), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a2c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a30), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x1003e) {
				*(int*) (read_result + 0x10035a30) = 4;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a34), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a38), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a3c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a40), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a44), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a48), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a4c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a50), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a51), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a54), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a68), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x10049) {
				*(int*) (read_result + 0x10035a6c) = 0;
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a6c), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a70), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a74), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a84), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a88), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a8c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10029) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a90), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a65), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) &ref_value, 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a24) = ref_value;
			if (g_save_version > 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a94), 0x18, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10035) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab0), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab4), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab5), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab6), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab7), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				read_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab8), 1, 1, (void*) stream);
				if (read_result == 0) {
					return 0;
				}
			}
			entity_index = entity_index + 1;
		} while (entity_index < param_1);
	}
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, stack frame choice (push vs sub esp)
// SIZE: 1361
// BLOCKER_DELTA: 1327
// ANALYSIS: ls_LoadTownData: Two phases - (1) per-player building slots (up to 62 buildings per player), (2) town records with name, timestamps, flags, population, wealth, 10 resource pairs, 10 production pairs, 4 tax rates, 4 trade routes, reputation, guild standings, 8 event records, political data. Returns 1 on success.
// FUNCTION: SERVER 0x10013b10
// ls_LoadTownData

int __cdecl ls_LoadTownData(int file)
{
	int count;
	char* ptr;
	char* inner;
	char* base;
	int i;

	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) file)) {
			return 0;
		}
	}

	ptr = (char*) 0x1009b768;
	do {
		if (!ls_ReadVfsDataChecked(ptr - 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = ptr + 0x10;
			do {
				if (!ls_ReadVfsDataChecked(inner - 8, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner - 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x18, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x1c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x28, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x2c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x30, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x34, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x24, 4, 1, (void*) file)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

		ptr += 0x2a90;
	} while (ptr < (char*) 0x100a8c38);

	ptr = (char*) 0x100a8c88;
	do {
		base = ptr - 0x48;

		if (!ls_ReadVfsDataChecked(base, 0x20, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 8, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0xc, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x10, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x18, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x19, 1, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		inner = ptr + 0x1c;
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		i = 0;
		inner = base + 0xb4;
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		if (!ls_ReadVfsDataChecked(base + 0x104, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x105, 1, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x108;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		i = 0;
		inner = base + 0x118;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		if (!ls_ReadVfsDataChecked(base + 0x128, 4, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x12c;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 0xb);

		if (!ls_ReadVfsDataChecked(base + 0x137, 1, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x138;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 7);

		if (!ls_ReadVfsDataChecked(base + 0x13f, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x140, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x141, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x142, 1, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		inner = base + 0x144;
		do {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, (void*) file)) {
				return 0;
			}
			i++;
			inner += 0x12;
		} while (i < 8);

		if (!ls_ReadVfsDataChecked(base + 0x1d4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1d8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1dc, 0xd0, 1, (void*) file)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(base + 0x2ec, 8, 1, (void*) file)) {
				return 0;
			}
		}

		ptr += 0x2f4;
	} while (ptr < (char*) 0x100a9858);

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 491
// FUNCTION: SERVER 0x10014070
// ls_ID2Ptr

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 430
// GHIDRA: FixupEntityPointers

unsigned int ls_ID2Ptr(void)
{
	int entity_addr;
	int chain_node;
	unsigned int lookup_result;
	int resolve_result;
	int counter;
	unsigned int* ptr_iter;
	int* ref_ptr;
	int byte_offset;
	int dynamic_parent;
	int existing_parent;
	int static_parent;

	*(unsigned int*) 0x1003546c = gm_LookupEntityRecordById(*(unsigned int*) 0x1003546c);
	if (*(unsigned int*) 0x1003546c == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x1016,
			"ls_ID2Ptr(): Stadtspieler Id not found",
			1
		);
		return 0;
	}
	*(unsigned int*) 0x1003543c = (unsigned int) gm_StartFilteredEntitySearch(1, 5, 10);
	if (0x10016 < *(int*) 0x1002d4ec) {
		ptr_iter = (unsigned int*) 0x10035478;
		do {
			lookup_result = gm_LookupEntityRecordById(*ptr_iter);
			*ptr_iter = lookup_result;
			ptr_iter = ptr_iter + 1;
		} while (ptr_iter < (unsigned int*) 0x10035498);
	}
	ref_ptr = (int*) 0x10035a10;
	do {
		if (ref_ptr[-0x5c] != -1) {
			if (ref_ptr[-1] == -1) {
				ref_ptr[-1] = 0;
			}
			else {
				gm_ResolveEntityById((void**) (ref_ptr - 1), (void**) 0, (void**) 0, ref_ptr[-1]);
			}
			if (*ref_ptr == -1) {
				*ref_ptr = 0;
			}
			else {
				gm_ResolveEntityById((void**) ref_ptr, (void**) 0, (void**) 0, *ref_ptr);
			}
		}
		ref_ptr = ref_ptr + 0x87;
	} while (ref_ptr < (int*) 0x1009ae10);
	counter = 0;
	if (0 < *(int*) 0x10035450) {
		byte_offset = 0;
		do {
			entity_addr = byte_offset + *(int*) 0x100a8c34;
			if (*(char*) (*(int*) 0x101de450 + *(int*) (byte_offset + *(int*) 0x100a8c34) * 0x41) == '\x1d') {
				*(int*) (entity_addr + 0x24) = 0;
			}
			if (*(int*) (entity_addr + 6) != -1) {
				resolve_result = gm_ResolveEntityById(
					(void**) &dynamic_parent,
					(void**) &existing_parent,
					(void**) &static_parent,
					*(int*) (entity_addr + 6)
				);
				if (resolve_result == 0) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
						0x1050,
						"ls_ID2Ptr(): Houston, wir haben ein Problem...",
						1
					);
				}
				else if (dynamic_parent == 0) {
					if (existing_parent == 0) {
						resolve_result = *(int*) (static_parent + 0x178);
						if (resolve_result != 0) {
							for (chain_node = *(int*) (resolve_result + 0x3f); chain_node != 0;
								 chain_node = *(int*) (chain_node + 0x3f)) {
								resolve_result = chain_node;
							}
							goto code_r0x10014236;
						}
						*(int*) (static_parent + 0x178) = entity_addr;
					}
					else {
						resolve_result = *(int*) (existing_parent + 0x14);
						if (resolve_result == 0) {
							*(int*) (existing_parent + 0x14) = entity_addr;
						}
						else {
							for (chain_node = *(int*) (resolve_result + 0x3f); chain_node != 0;
								 chain_node = *(int*) (chain_node + 0x3f)) {
								resolve_result = chain_node;
							}
						code_r0x10014236:
							*(int*) (resolve_result + 0x3f) = entity_addr;
						}
					}
				}
				else {
					resolve_result = *(int*) (dynamic_parent + 0x5d);
					if (resolve_result != 0) {
						for (chain_node = *(int*) (resolve_result + 0x3f); chain_node != 0;
							 chain_node = *(int*) (chain_node + 0x3f)) {
							resolve_result = chain_node;
						}
						goto code_r0x10014236;
					}
					*(int*) (dynamic_parent + 0x5d) = entity_addr;
				}
			}
			counter = counter + 1;
			byte_offset = byte_offset + 0x43;
		} while (counter < *(int*) 0x10035450);
	}
	gm_EntitySetField();
	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 892
// BLOCKER_DELTA: 533
// GHIDRA: RecvGameSavegame
// FUNCTION: SERVER 0x10014260
// srv_RecvGame

int srv_RecvGame(void)
{
	int file_handle;
	int load_status;
	char* entity_state_ptr;

	file_handle = OpenVfsStream((char*) g_101deae8, (char*) g_101deac0, (int) (const char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x11fe,
			"ls_RecvGame(): Can\'t open File",
			1
		);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	ls_LoadSavegameHeader(file_handle, (char*) g_save_info);
	if (((g_save_info[1] & 2) == 0) || (0x1005a < g_save_info[0]) || (g_save_info[0] < 0x10013)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x120a,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	*(int*) 0x1003546c = 0;
	load_status = ls_ReadVfsDataChecked((void*) 0x10030b6c, 4, 1, (void*) file_handle);
	if (load_status != 0) {
		load_status = ls_ReadVfsDataChecked((void*) 0x1176408c, 4, 1, (void*) file_handle);
		if (load_status != 0) {
			load_status = ls_ReadVfsDataChecked((void*) 0x10035880, 0xe, 1, (void*) file_handle);
			if (load_status != 0) {
				load_status = ls_ReadVfsDataChecked((void*) 0x10035439, 1, 1, (void*) file_handle);
				if (load_status != 0) {
					load_status = ls_ReadVfsDataChecked((void*) 0x1003546c, 4, 1, (void*) file_handle);
					if (load_status != 0) {
						load_status = ls_ReadVfsDataChecked((void*) 0x1003542c, 4, 1, (void*) file_handle);
						if (load_status != 0) {
							load_status = ls_ReadVfsDataChecked((void*) 0x10035430, 4, 1, (void*) file_handle);
							if (load_status != 0) {
								load_status = ls_ReadVfsDataChecked((void*) 0x10035434, 4, 1, (void*) file_handle);
								if (load_status != 0) {
									ls_ReadVfsDataChecked((void*) 0x10035440, 4, 1, (void*) file_handle);
									ls_ReadVfsDataChecked((void*) 0x101de580, 0x18, 1, (void*) file_handle);
									if (g_save_version >= 0x10030) {
										ls_ReadVfsDataChecked((void*) 0x10030b70, 4, 1, (void*) file_handle);
									}
									if (g_save_version >= 0x1003d) {
										ls_ReadVfsDataChecked((void*) 0x10035408, 4, 1, (void*) file_handle);
									}
									else {
										*(int*) 0x10035408 = 1000000;
									}
									load_status = ls_LoadExistingEntities(file_handle);
									if (load_status != 0) {
										load_status = ls_LoadBuildingEntityState(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x123d,
												"LoadGame(): Can\'t load Buildings",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadDynamicEntities((void*) file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x1246,
												"srv_RecvGame(): Can\'t load Dynasties",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadEntities(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x124f,
												"srv_RecvGame(): Can\'t load Players",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										entity_state_ptr = (char*) 0x100358a2;
										do {
											if (*(unsigned short*) (entity_state_ptr - 2) != 0xffff &&
												*entity_state_ptr == '\x06') {
												*entity_state_ptr = '\x05';
											}
											entity_state_ptr = entity_state_ptr + 0x21c;
										} while ((int) entity_state_ptr < (int) 0x1009aca2);
										load_status = ls_LoadTownData(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x125b,
												"srv_RecvGame(): Can\'t load Towns",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										if (g_save_version >= 0x10045) {
											load_status = amt_fio_LoadAemter(file_handle, g_save_version);
											if (load_status == 0) {
												LogMessageInternal(
													"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
													0x1266,
													"srv_RecvGame(): Can\'t load Aemter",
													1
												);
												CloseVfsStream(file_handle);
												return 0;
											}
										}
										load_status = ls_ID2Ptr();
										if (load_status != 0) {
											CloseVfsStream(file_handle);
											return 1;
										}
										LogMessageInternal(
											"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
											0x126f,
											"srv_RecvGame(): Can\'t convert IDs to Pointers",
											1
										);
										CloseVfsStream(file_handle);
										m_FreeTracked((void*) g_101de560);
										g_101de560 = 0;
										return 0;
									}
									LogMessageInternal(
										"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
										0x1234,
										"srv_RecvGame(): Can\'t load Objects",
										1
									);
									CloseVfsStream(file_handle);
									m_FreeTracked((void*) g_101de560);
									g_101de560 = 0;
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
		0x121e,
		"srv_RecvGame(): Can\'t load Counter",
		1
	);
	CloseVfsStream(file_handle);
	m_FreeTracked((void*) g_101de560);
	g_101de560 = 0;
	return 0;
}
