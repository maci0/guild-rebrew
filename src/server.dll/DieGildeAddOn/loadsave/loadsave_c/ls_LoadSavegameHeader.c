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
extern int DAT_100a8c34;
extern int DAT_10035450;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
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

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// FUNCTION: SERVER 0x10012470
// ls_LoadSavegameHeader

int __cdecl ls_LoadSavegameHeader(int ctx, char* buf)
{
	char* alloc_buf;
	int i;

	alloc_buf = (char*) m_AllocTracked(0xe100, &g_1002d4fc);
	if (!ls_ReadVfsDataChecked(buf, 4, 1, (void*) ctx)) {
		return 0;
	}
	g_save_version = *(int*) buf;
	if (!ls_ReadVfsDataChecked(buf + 4, 1, 1, (void*) ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(buf + 5, 0x20, 1, (void*) ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(buf + 0x28, 8, 1, (void*) ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(buf + 0x30, 1, 1, (void*) ctx)) {
		return 0;
	}
	if (g_save_version >= 0x10033) {
		if (!ls_ReadVfsDataChecked(buf + 0x31, 1, 1, (void*) ctx)) {
			return 0;
		}
	}
	if (g_save_version >= 0x10028) {
		if (!ls_ReadVfsDataChecked(buf + 0x32, 0xe, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x40, 0x10, 1, (void*) ctx)) {
			return 0;
		}
		if (g_save_version >= 0x10054) {
			if (!ls_ReadVfsDataChecked(buf + 0x50, 0x10, 1, (void*) ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(buf + 0x63, 1, 1, (void*) ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(buf + 0x64, 4, 1, (void*) ctx)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(buf + 0x60, 1, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x61, 1, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x62, 1, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x68, 4, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x6c, 1, 1, (void*) ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(buf + 0x6d, 1, 1, (void*) ctx)) {
			return 0;
		}
		if (g_save_version >= 0x1002b) {
			if (!ls_ReadVfsDataChecked(buf + 0x70, 4, 1, (void*) ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(buf + 0x74, 4, 1, (void*) ctx)) {
				return 0;
			}
		}
		else {
			*(int*) (buf + 0x70) = -1;
			*(int*) (buf + 0x74) = -1;
		}
		if (g_save_version >= 0x10034) {
			char* score_ptr = buf + 0x78;
			for (i = 0; i < 8; i++) {
				if (!ls_ReadVfsDataChecked(score_ptr, 4, 1, (void*) ctx)) {
					return 0;
				}
				score_ptr = score_ptr + 4;
			}
		}
		if (!ls_ReadVfsDataChecked(alloc_buf, 0xe100, 1, (void*) ctx)) {
			return 0;
		}
	}
	if (alloc_buf != (char*) 0) {
		m_FreeTracked(alloc_buf);
	}
	if (g_save_version < 0x10025) {
		return 0;
	}
	if (g_save_version >= 0x10038) {
		if (!ls_ReadVfsDataChecked(buf + 0x98, 4, 1, (void*) ctx)) {
			return 0;
		}
	}
	else {
		*(int*) (buf + 0x98) = 2;
	}
	if (g_save_version >= 0x10039) {
		if (!ls_ReadVfsDataChecked(buf + 0x9c, 0x60, 1, (void*) ctx)) {
			return 0;
		}
	}
	else {
		*(int*) (buf + 0x9c) = g_1002d4f0;
		*(int*) (buf + 0xa0) = g_1002d4f4;
		*(char*) (buf + 0xa4) = g_1002d4f8;
	}
	return 1;
}

/* Loads existing entities from a save file. Reads entity
 * records in bulk and links them into the runtime entity
 * tables. */
