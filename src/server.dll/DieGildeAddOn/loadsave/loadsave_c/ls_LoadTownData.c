#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

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
extern int g_query_limit;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
;
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
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

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// STUB: SERVER 0x10013b10
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

	for (ptr = (char*) 0x1009b768; ptr < (char*) 0x100a8c38; ptr += 0x2a90) {
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

	}

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

		inner = ptr + 0x1c;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		inner = base + 0xb4;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		if (!ls_ReadVfsDataChecked(base + 0x104, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x105, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x108;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		inner = base + 0x118;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		if (!ls_ReadVfsDataChecked(base + 0x128, 4, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x12c;
		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x137, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x138;
		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

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

		inner = base + 0x144;
		for (i = 0; i < 8; i++) {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, (void*) file)) {
				return 0;
			}
			inner += 0x12;
		}

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

/* Converts an entity ID to a runtime pointer. Searches the
 * entity tables for a matching ID and returns the memory
 * address. Used during save loading to resolve references. */

