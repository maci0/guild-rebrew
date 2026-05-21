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

// STUB: SERVER 0x10012eb0
// ls_LoadDynamicEntities

/* Game function - reads entity data records from VFS file */

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

/* Master entity loader: orchestrates loading all entity
 * types from a save file in the correct order (buildings
 * first, then citizens, then objects). */
