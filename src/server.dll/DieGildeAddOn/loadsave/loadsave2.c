#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_101de454; /* 0x101de454 */
extern int g_101de55c; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
char s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580[] = "ls_ID2Ptr(): Stadtspieler Id not found";
char s_D__Develop_DieGildeAddOn_loadsav_1002d550[] = "D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c";
char s_ls_ID2Ptr____Houston__wir_haben_e_1002d520[] = "ls_ID2Ptr(): Houston, wir haben ein Problem...";
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// FUNCTION: SERVER 0x100127d0
// ls_LoadExistingEntities

void __cdecl gm_CleanupObjectEntities(void);
extern unsigned short* g_query_base; /* 0x100a8c34 */
extern int g_query_limit; /* 0x10035450 */

int __cdecl ls_LoadExistingEntities(int arg1)
{
	int count;
	int i;
	unsigned char* p;

	gm_CleanupObjectEntities();
	if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) arg1)) {
		return 0;
	}
	for (i = 0; i < count; i++) {
		p = (unsigned char*) g_query_base + i * 0x43;
		if (!ls_ReadVfsDataChecked(p, 2, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 2, 4, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 6, 4, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0xa, 4, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0xe, 4, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0x12, 1, 1, (void*) arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(p + 0x13, 1, 1, (void*) arg1)) {
			return 0;
		}
		p += 0x1c;
		if (!ls_ReadVfsDataChecked(p, 0x1f, 1, (void*) arg1)) {
			return 0;
		}
	}
	g_query_limit = count;
	return 1;
}

/* Loads building entity state from a save file. Reads
 * building type, owner, upgrade level, and production
 * state for each building entity. */

extern int g_citizen_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

#if 0 /* split to loadsave_c/ls_LoadEntities.c */
int __cdecl ls_LoadEntities(int arg1)
{
	int stream;
	int read_result;
	int inner_result;
	unsigned short entity_slot;
	int entity_index;
	int ref_value;

	stream = arg1;
	read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) arg1);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) &arg1, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	g_citizen_count = arg1;
	read_result = ls_ReadVfsDataChecked((void*) 0x10035470, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) 0x10035474, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	if (g_file_version > 0x10016) {
		for (read_result = (int) 0x10035478; read_result < (int) 0x10035498; read_result += 4) {
			inner_result = ls_ReadVfsDataChecked((void*) read_result, 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
		}
	}
	entity_index = 0;
	if (0 < arg1) {
		do {
			read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) stream);
			if (read_result == 0) {
				return 0;
			}
			read_result = (entity_slot & 0xffff) * 0x21c;
			*(unsigned short*) (read_result + 0x100358a0) = entity_slot;
			if (g_file_version < 0x1003e) {
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
			if (g_file_version > 0x1003a) {
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
			if (g_file_version > 0x10030) {
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
			if (g_file_version > 0x10023) {
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
			if (g_file_version < 0x10020) {
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
			if (g_file_version < 0x1003e) {
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
			if (g_file_version < 0x10049) {
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
			if (g_file_version > 0x10029) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a90), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_file_version > 0x10020) {
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
			if (g_file_version > 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a94), 0x18, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_file_version > 0x10035) {
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
		} while (entity_index < arg1);
	}
	return 1;
}
#endif

/* Loads town-level data from a save file. Reads town name,
 * treasury, population, building counts, and political
 * state (offices, elections). */

